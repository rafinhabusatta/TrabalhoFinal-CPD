#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct info{
    string ISSUE;
    string TYPE;
    string STORY TITLE;
    string STORYLINE;
    string EVENT;
    string COVER DATE;
    string RELEASE DATE;
    string WRITER;
    string PENCILER;
    string MAIN CHARACTERS;
    string ANTAGONISTS;
    string SUPPORTING CHARACTERS
};

int main(){
    ifstream arq1; arq1.open("listamini.csv");
    string linha;
    sting word
    vector<info> vel;
    if ( arq1.is_open() ) {     
        while ( arq1.good() ) {
            arq1 >> linha;
            //cout << linha;
            stringstream str(linha);
            info inf;
            
                getline(str, word, ';');
                inf.ISSUE = word;
                
            

        }          
    }

    ofstream earq("lista-ordenada.csv", ios::out | ios::binary);
    if(!earq) {
      cout << "Cannot open file!" << endl;
      return 1;
   }

}