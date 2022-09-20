/////////////////////////////////gerar arquivo//////////////////
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // std::sort
#include <cstring>

ifstream arqx;
arqx.open("movie.csv");

if (arqx.is_open())
{
  ofstream outputFile; // Step 2. Declare an output file stream variable.
  outputFile.open("info1.txt");
  ofstream outputFile2;
  outputFile2.open("info2.txt");
  cout << "abriu" << endl;
  while (arqx.good())
  {
    getline(arqx, linha);
    aux = strtok((char *)linha.c_str(), ",\"");
    outputFile << aux << ",";
    aux = strtok(NULL, "\"");
    outputFile << aux << endl;
    aux = strtok(NULL, "\n");
    outputFile2 << aux << endl;
  }
  outputFile.close();
  outputFile2.close();
}

/////////////////////////////////gerar arquivo//////////////////
// ofstream earq("lista-ordenada.csv", ios::out | ios::binary);
// if(!earq) {
//   cout << "Cannot open file!" << endl;
//   return 1;
//}