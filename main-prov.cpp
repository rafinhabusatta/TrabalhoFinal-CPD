#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>    // std::sort

#include <cstring>
#define LIM 300
#define MAX_ARRAY 1000

//#include <C:\Users\tomas\OneDrive\Área de Trabalho\Cadeiras semestre 3\cpd\trabfinal\btree.cpp>
using namespace std;
int MAX = 4;
bool tem = false;


struct Movie // Movie is a struct type
{
  int id;
  char title[LIM]; // Title of the movie
  // int year;           // Year of release
  // char director[LIM]; // Director of the movie
  char genre[LIM]; // Genre of the movie
  int map_inv;
};


// CPP program to implement B* tree
// Searching on a B+ tree in C++
///////////////////////////////

// BP node

class Node
{
  bool IS_LEAF;
  int *key, size; // size is the number of keys in the node
  Node **ptr;
  friend class BPTree;
  // const char* info[4][250];
  //string info[4];
  Movie filmes[4];

public:
  Node();
};

Node *aux_node = NULL;
int chave = 0;
bool achou = false;

// BP tree
class BPTree
{

  Node *root;
  void insertInternal(int, Node *, Node *);
  Node *findParent(Node *, Node *);


public:
  BPTree();
  void search(int);
  void insert(int);
  void bota_string(int, Movie);

  void display(Node *);
  Node *getRoot();
};


Node::Node()
{

  key = new int[MAX];
  ptr = new Node *[MAX + 1];
}


BPTree::BPTree()
{

  root = NULL;
}

// Search operation

void BPTree::bota_string(int x, Movie mov)
{
  if (root == NULL)
  {
    cout << "Tree is empty\n";
  }
  else
  {
    Node *cursor = root;
    while (cursor->IS_LEAF == false)
    {
      for (int i = 0; i < cursor->size; i++)
      {
        if (x < cursor->key[i])
        {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1)
        {

          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }

    for (int i = 0; i < cursor->size; i++)
    {
      if (cursor->key[i] == x)
      {
        // cout << "Found, string put\n";
        //cout << str << endl << "----pse-----" << endl;
        //cursor->info[i] = str;
        //cout << cursor->info[i] << endl << "+++++++++++" << endl;
        cursor->filmes[i] = mov;

        return;
      }
    }
    cout << "Not found\n";
    achou = false;
  }
}


// Search operation
void BPTree::search(int x)
{
  if (root == NULL)
  {
    cout << "Tree is empty\n";
  }
  else
  {
    Node *cursor = root;
    while (cursor->IS_LEAF == false)
    {
      for (int i = 0; i < cursor->size; i++)
      {
        if (x < cursor->key[i])
        {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1)
        {

          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }

    for (int i = 0; i < cursor->size; i++)
    {
      if (cursor->key[i] == x)
      {
        cout << "Found\n"
             << endl;
        tem = true;
        cout << "Id:" << cursor->filmes[i].id << endl << "Titulo:" << cursor->filmes[i].title << endl << "Genero:" << cursor->filmes[i].genre << endl;
        //cout <<  "Mapeamento Inverso:" << cursor->filmes[i].map_inv << endl;
        return;
      }
    }
    cout << "Not found\n";
    tem = false;
  }
}


// Insert Operation - cria a b+ tree com ids dos filmes (index)
void BPTree::insert(int x)
{
  if (root == NULL)
  {

    root = new Node;
    root->key[0] = x;
    root->IS_LEAF = true;
    root->size = 1;

  }
  else
  {
    Node *cursor = root;
    Node *parent;
    while (cursor->IS_LEAF == false)
    {
      parent = cursor;
      for (int i = 0; i < cursor->size; i++)
      {
        if (x < cursor->key[i])
        {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1)
        {

          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }

    if (cursor->size < MAX)
    {
      int i = 0;
      while (x > cursor->key[i] && i < cursor->size)
        i++;
      for (int j = cursor->size; j > i; j--)
      {

        cursor->key[j] = cursor->key[j - 1];
      }
      cursor->key[i] = x;
      cursor->size++;
      cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
      cursor->ptr[cursor->size - 1] = NULL;

    }
    else
    {
      Node *newLeaf = new Node;
      int virtualNode[MAX + 1];
      for (int i = 0; i < MAX; i++)
      {

        virtualNode[i] = cursor->key[i];
      }
      int i = 0, j;
      while (x > virtualNode[i] && i < MAX)
        i++;

      for (int j = MAX + 1; j > i; j--)
      {

        virtualNode[j] = virtualNode[j - 1];
      }
      virtualNode[i] = x;
      newLeaf->IS_LEAF = true;
      cursor->size = (MAX + 1) / 2;
      newLeaf->size = MAX + 1 - (MAX + 1) / 2;
      cursor->ptr[cursor->size] = newLeaf;
      newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
      cursor->ptr[MAX] = NULL;

      for (i = 0; i < cursor->size; i++)
      {
        cursor->key[i] = virtualNode[i];
      }
      for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
      {
        newLeaf->key[i] = virtualNode[j];
      }
      if (cursor == root)
      {

        Node *newRoot = new Node;
        newRoot->key[0] = newLeaf->key[0];
        newRoot->ptr[0] = cursor;
        newRoot->ptr[1] = newLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;

      }
      else
      {

        insertInternal(newLeaf->key[0], parent, newLeaf);
      }
    }
  }
}

// Insert Operation

void BPTree::insertInternal(int x, Node *cursor, Node *child)
{
  if (cursor->size < MAX)
  {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--)
    {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--)
    {

      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;

  }
  else
  {
    Node *newInternal = new Node;
    int virtualKey[MAX + 1];
    Node *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++)
    {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX + 1; i++)
    {

      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX)
      i++;

    for (int j = MAX + 1; j > i; j--)
    {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--)
    {

      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;

    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
    {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
    {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root)
    {

      Node *newRoot = new Node;
      newRoot->key[0] = cursor->key[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;

    }
    else
    {

      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent

Node *BPTree::findParent(Node *cursor, Node *child)
{
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
  {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++)
  {
    if (cursor->ptr[i] == child)
    {
      parent = cursor;
      return parent;
    }
    else
    {

      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

// Print the tree

void BPTree::display(Node *cursor)
{
  if (cursor != NULL)
  {
    for (int i = 0; i < cursor->size; i++)
    {
      cout << cursor->key[i] << " ";
      cout << "Id:" << cursor->filmes[i].id << endl << "Titulo:" << cursor->filmes[i].title << endl << "Genero:" << cursor->filmes[i].genre << endl;
    }
    cout << "\n";
    if (cursor->IS_LEAF != true)
    {
      for (int i = 0; i < cursor->size + 1; i++)
      {

        display(cursor->ptr[i]);
      }
    }
  }
}

// Get the root

Node *BPTree::getRoot()
{

  return root;
}

int Mapeamento_Hash(std::string s, int M)
{
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
        hash = (128 * hash + s[i]) % M;
    return hash;
}


/////////////////////////////////////////////


int main()
{
  ifstream arq1;
  arq1.open("info1.txt");
  ifstream arq2;
  arq2.open("info2.txt");
  string linha;
  string word;
  vector<string> vel; // vec das strings
  //string informacao[MAX_ARRAY];
  // vector<Movie> movies;
  Movie movies[MAX_ARRAY]; // vetor de filmes
  int conti = 0;

  BPTree node;

  string aux;
  int teste[] = {2,3,4,97,2,1,5,8,4,10};
  cout << teste[0] <<" "<<teste[1] <<" "<<teste[2] <<" "<<teste[3] <<" "<<teste[4] <<" "<<teste[5] <<" "<<teste[6] <<" "<<teste[7] <<" "<<teste[8] <<" "<<teste[9] <<" " << endl;
  int n = sizeof(teste) / sizeof(teste[0]);
  sort(teste, teste+n);
  cout << teste[0] <<" "<<teste[1] <<" "<<teste[2] <<" "<<teste[3] <<" "<<teste[4] <<" "<<teste[5] <<" "<<teste[6] <<" "<<teste[7] <<" "<<teste[8] <<" "<<teste[9] <<" " << endl;
  
  
  if (arq1.is_open() && arq2.is_open())
  {
    cout << "abriu" << endl;
    while (arq1.good() && arq2.good())
    {
      for (int i = 0; i < MAX_ARRAY; i++)
      {
        getline(arq1, linha);
        aux = strtok((char *)linha.c_str(), ",");
        // cout << aux << endl;
        movies[conti].id = atoi(aux.c_str());
        //cout <<  movies[conti].id << endl;
        aux = strtok(NULL, "\n");
        ////// chave do mapeamento inverso
        movies[conti].map_inv = Mapeamento_Hash(aux, MAX_ARRAY);
        ////////
        strncpy(movies[conti].title, aux.c_str(), LIM);
        //cout << aux << endl;
        getline(arq2, linha);
        aux = strtok((char *)linha.c_str(), "\n");
        strncpy(movies[conti].genre, aux.c_str(), LIM);

        node.insert(conti);

        conti++;
      }
      cout << "teste" << endl;

      break;
    }
    arq1.close();
    arq2.close();

  }
  for (int k = 0; k < conti; k++)
  {
    

    node.bota_string(k, movies[k]); 
  }
  int escolha = 0;
  //node.display(node.getRoot());
  while (escolha != -1)
  {
    cout << "Escolha um index:";
    cin >> escolha;
    node.search(escolha);
  }

  /////////////////////////////////gerar arquivo//////////////////
  /*ifstream arqx;
  arqx.open("movie.csv");

  if (arqx.is_open())
  {
    ofstream outputFile;                  // Step 2. Declare an output file stream variable.
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
  */
 /////////////////////////////////gerar arquivo//////////////////
  // ofstream earq("lista-ordenada.csv", ios::out | ios::binary);
  // if(!earq) {
  //   cout << "Cannot open file!" << endl;
  //   return 1;
  //}

}
