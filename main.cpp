#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // std::sort
#include <cstring>
#include <iomanip>
#include "include/bPlusTree.h"
#include "include/invertedIndex.h"

#define LIM 300
#define MAX_ARRAY 1000
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
    ifstream arq3;      // arquivo 3 de entrada
    fstream binOutFile; // arquivo binario de saida

    string linha; // string para armazenar cada linha do arquivo
    string aux;
    // string word;
    Movie movies[MAX_ARRAY]; // vetor de filmes
    int conti = 0;
    BPTree node;
    BPTree nodeinv;
    InvertedIndex inv;

    int escolha = 0, indexChoice = 0;
    string nome;
    int num_aux = 0;
    int imbd_aux;

    // ******************** LENDO OS ARQUIVOS ********************
    // ******************** GERAÇÃO DA B+ E VETOR ****************
    ifstream fileExists;
    fileExists.open("data/movies.dat");
    if (fileExists)
    {

        cout << "File movies dat already exists. Opening to read." << endl;
        // leitura do arquivo binário, caso ele já exista
        binOutFile.open("data/movies.dat", ios::in | ios::binary);
        if (binOutFile.is_open())
        {

            binOutFile.read(reinterpret_cast<char *>(movies), MAX_ARRAY * sizeof(Movie));
            binOutFile.close();

            for (int k = 0; k < MAX_ARRAY; k++)
            {

                node.insert(k);
                // node.search(k);
            }
            for (int k = 0; k < MAX_ARRAY; k++)
            {

                node.bota_string(k, movies[k]);
                // node.search(k);
            }
        }
        else
        {
            cout << "Error opening the file." << endl; // Error message
        }
    }
    else
    {
        cout << "File movies dat does not exist. Reading text files and creating .dat to write." << endl;
        arq1.open("data/movies.csv"); // abre o arquivo de entrada
        arq2.open("data/genres.txt"); // abre o arquivo 2 de entrada
        arq3.open("data/link.csv");   // abre o arquivo 3 de entrada
        if (arq1.is_open() && arq2.is_open() && arq3.is_open())
        {
            cout << "Arquivos foram abertos" << endl;
            while (arq1.good() && arq2.good() && arq3.good())
            {
                for (int i = 0; i < MAX_ARRAY; i++)
                {

                    getline(arq1, linha);                     // pega linha do arquivo
                    aux = strtok((char *)linha.c_str(), ","); // separa até a primeira virgula

                    movies[conti].id = atoi(aux.c_str());

                    aux = strtok(NULL, "\n"); // pega o resto da linha

                    // chave do mapeamento inverso
                    movies[conti].map_inv = Mapeamento_Hash(aux, MAX_ARRAY);
                    strncpy(movies[conti].title, aux.c_str(), LIM);
                    getline(arq2, linha);
                    aux = strtok((char *)linha.c_str(), "\n");
                    strncpy(movies[conti].genre, aux.c_str(), LIM);

                    getline(arq3, linha);
                    aux = strtok((char *)linha.c_str(), ",");
                    aux = strtok(NULL, "\n");
                    imbd_aux = stoi(aux);
                    movies[conti].imdb = imbd_aux;

                    node.insert(conti);

                    conti++;
                }
                cout << "Arvore B+ de indices gerada com sucesso! Filmes adicionados ao vetor de estruturas com sucesso!" << endl;

                break;
            }
            arq1.close();
            arq2.close();
            arq3.close();
            for (int k = 0; k < MAX_ARRAY; k++)
            {

                node.bota_string(k, movies[k]);
            }
        }
        binOutFile.open("data/movies.dat", ios::out | ios::binary); // opening to writing in binary mode
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
    }
    // insere estruturas na árvore

    while (escolha != -1)
    {
        cout << "Escolha uma opcao:\n1-Listar filmes pelo seu id\n2-Listar filmes por ordem inversa de seu id\n"
             << "3-Busca por chave id\n4-Busca por ano\n-1-Sair\n";
        cin >> escolha;
        if (escolha == 1)
        {
            for (Movie &m : movies)
            {
                cout << "Id:" << m.id << endl;
                cout << "Titulo: " << m.title << endl;
                cout << "Genero: " << m.genre << endl;
                cout << "IMDB Link: "
                     << "https://imdb.com/title/tt" << setfill('0') << setw(7) << m.imdb << endl;
            }
        }
        else if (escolha == 2)
        {
            for (int k = MAX_ARRAY - 1; k >= 0; k--)
            {
                cout << "Id:" << movies[k].id << endl
                     << "Titulo:" << movies[k].title << endl
                     << "Genero:" << movies[k].genre << endl;
            }
        }
        else if (escolha == 3)
        {
            while (indexChoice != -1)
            {
                cout << "Escolha um index ou aperte -1 para retornar ao menu principal:";
                cin >> indexChoice;
                node.search(indexChoice - 1);
            }
        }
        // else if (escolha == 4)
        // {
        //     cout << "Digite um nome:";
        //     cin >> nome;
        //     num_aux = Mapeamento_Hash(nome, MAX_ARRAY);
        //     nodeinv.search(num_aux);
        // }
        else if (escolha == 4)
        {
            InvertedIndexFunction("data/movies.csv");
        }
    }
}
