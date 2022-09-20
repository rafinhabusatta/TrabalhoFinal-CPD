#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // std::sort
#include <cstring>
#include "include/bPlusTree.h"

#define LIM 300
#define MAX_ARRAY 5
using namespace std;

int Mapeamento_Hash(std::string s, int M)
{
  int hash = 0;
  for (int i = 0; i < s.length(); i++)
    hash = (128 * hash + s[i]) % M;
  return hash;
}

// ********************** MAIN *************************

int main()
{
  ifstream arq1;      // arquivo de entrada
  ifstream arq2;      // arquivo 2 de entrada
  fstream binOutFile; // arquivo binario de saida

  arq1.open("info1.txt"); // abre o arquivo de entrada
  arq2.open("info2.txt"); // abre o arquivo 2 de entrada

  string linha; // string para armazenar cada linha do arquivo
  string word;
  Movie movies[MAX_ARRAY]; // vetor de filmes
  int conti = 0;
  BPTree node;
  string aux;

  // ******************** LENDO OS ARQUIVOS ********************
  // ******************** GERAÇÃO DA B+ E VETOR ****************
  if (arq1.is_open() && arq2.is_open())
  {
    cout << "Arquivos 1 e 2 foram abertos" << endl;
    while (arq1.good() && arq2.good())
    {
      for (int i = 0; i < MAX_ARRAY; i++)
      {
        // cout << "conti" << conti << endl;
        getline(arq1, linha);
        aux = strtok((char *)linha.c_str(), ",");
        // cout << "aux" << aux << endl;
        movies[conti].id = atoi(aux.c_str());
        // cout << "movies id" << movies[conti].id << endl;
        aux = strtok(NULL, "\n");
        // cout << "aux 2.0" << aux << endl;
        ////// chave do mapeamento inverso
        // cout << "chave do mapeamento inverso" << endl;
        movies[conti].map_inv = Mapeamento_Hash(aux, MAX_ARRAY);
        // cout << movies[conti].map_inv << endl;
        ////////
        strncpy(movies[conti].title, aux.c_str(), LIM);
        // cout << aux << endl;
        getline(arq2, linha);
        aux = strtok((char *)linha.c_str(), "\n");
        strncpy(movies[conti].genre, aux.c_str(), LIM);

        node.insert(conti);

        conti++;
      }
      cout << "Arvore B+ de índices gerada com sucesso! Filmes adicionados ao vetor de estruturas com sucesso!" << endl;

      break;
    }
    arq1.close();
    arq2.close();
  }

  binOutFile.open("movies.dat", ios::out | ios::binary); // opening to writing in binary mode
  if (binOutFile.is_open())
  {
    for (int i = 0; i < MAX_ARRAY; i++)
    {
      binOutFile.write(reinterpret_cast<char *>(movies), MAX_ARRAY * sizeof(Movie)); // 2 args: source of the data you wanna write to the file and the size of the structure
      // reinterpret_cast<char *>(movies), MAX_ARRAY * sizeof(Movie)) don't need to use the address of the movie as a char address, because the array is already a char array.
    }
    binOutFile.close();
  }
  else
  {
    cout << "Error opening the file." << endl; // Error message
  }
  for (int k = 0; k < conti; k++)
  {

    node.bota_string(k, movies[k]);
  }
  int escolha = 0;
  // node.display(node.getRoot());
  while (escolha != -1)
  {
    cout << "Escolha um index:";
    cin >> escolha;
    node.search(escolha);
  }
}
