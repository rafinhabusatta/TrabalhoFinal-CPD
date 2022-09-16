#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
//#include <C:\Users\tomas\OneDrive\Área de Trabalho\Cadeiras semestre 3\cpd\trabfinal\btree.cpp>
using namespace std;
int MAX = 4;

struct infor{
    string ISSUE;
    string TYPE;
    string STORY_TITLE;
    string STORYLINE;
    string EVENT;
    string COVER_DATE;
    string RELEASE_DATE;
    string WRITER;
    string PENCILER;
    string MAIN_CHARACTERS;
    string ANTAGONISTS;
    string SUPPORTING_CHARACTERS;
};
// CPP program to implement B* tree
// Searching on a B+ tree in C++
///////////////////////////////

// BP node
class Node {
  bool IS_LEAF;
  int *key, size;
  Node **ptr;
  friend class BPTree;
  string info[4]; 
  

   public:
  Node();

};

Node *aux_node = NULL;
int chave=0;
bool achou = false;

// BP tree
class BPTree {
  Node *root;
  void insertInternal(int, Node *, Node *);
  Node *findParent(Node *, Node *);

   public:
  BPTree();
  void search(int);
  void insert(int);
  void bota_string(int, string);
  void display(Node *);
  Node *getRoot();
};

Node::Node() {
  key = new int[MAX];
  ptr = new Node *[MAX + 1];
}

BPTree::BPTree() {
  root = NULL;
}

// Search operation
void BPTree::bota_string(int x, string str) {
  if (root == NULL) {
    cout << "Tree is empty\n";
  } else {
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    for (int i = 0; i < cursor->size; i++) {
      if (cursor->key[i] == x) {
        cout << "Found, string put\n";
        cout << str << endl;
        cursor->info[i]=str;
        cout << cursor->info[i] << endl;
        return;
      }
    }
    cout << "Not found\n";
    achou = false;
  }
}


// Search operation
void BPTree::search(int x) {
  if (root == NULL) {
    cout << "Tree is empty\n";
  } else {
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    for (int i = 0; i < cursor->size; i++) {
      if (cursor->key[i] == x) {
        cout << "Found\n" << endl;
        printf("%d %d\n", cursor->key[i], i);
        printf("%s\n", cursor->info[i]);
        for(int h=0; h<MAX; h++){
            printf("%s\n", cursor->info[h]);
        }
        //string texto = cursor->info[i];
        //cout << texto << endl;
        
        return;
      }
    }
    cout << "Not found\n";
    achou = false;
  }
}

// Insert Operation
void BPTree::insert(int x) {
  if (root == NULL) {
    root = new Node;
    root->key[0] = x;
    root->IS_LEAF = true;
    root->size = 1;
  } else {
    Node *cursor = root;
    Node *parent;
    while (cursor->IS_LEAF == false) {
      parent = cursor;
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    if (cursor->size < MAX) {
      int i = 0;
      while (x > cursor->key[i] && i < cursor->size)
        i++;
      for (int j = cursor->size; j > i; j--) {
        cursor->key[j] = cursor->key[j - 1];
      }
      cursor->key[i] = x;
      cursor->size++;
      cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
      cursor->ptr[cursor->size - 1] = NULL;
    } else {
      Node *newLeaf = new Node;
      int virtualNode[MAX + 1];
      for (int i = 0; i < MAX; i++) {
        virtualNode[i] = cursor->key[i];
      }
      int i = 0, j;
      while (x > virtualNode[i] && i < MAX)
        i++;
      for (int j = MAX + 1; j > i; j--) {
        virtualNode[j] = virtualNode[j - 1];
      }
      virtualNode[i] = x;
      newLeaf->IS_LEAF = true;
      cursor->size = (MAX + 1) / 2;
      newLeaf->size = MAX + 1 - (MAX + 1) / 2;
      cursor->ptr[cursor->size] = newLeaf;
      newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
      cursor->ptr[MAX] = NULL;
      for (i = 0; i < cursor->size; i++) {
        cursor->key[i] = virtualNode[i];
      }
      for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
        newLeaf->key[i] = virtualNode[j];
      }
      if (cursor == root) {
        Node *newRoot = new Node;
        newRoot->key[0] = newLeaf->key[0];
        newRoot->ptr[0] = cursor;
        newRoot->ptr[1] = newLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;
      } else {
        insertInternal(newLeaf->key[0], parent, newLeaf);
      }
    }
  }
}

// Insert Operation
void BPTree::insertInternal(int x, Node *cursor, Node *child) {
  if (cursor->size < MAX) {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--) {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--) {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  } else {
    Node *newInternal = new Node;
    int virtualKey[MAX + 1];
    Node *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++) {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX + 1; i++) {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX)
      i++;
    for (int j = MAX + 1; j > i; j--) {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root) {
      Node *newRoot = new Node;
      newRoot->key[0] = cursor->key[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    } else {
      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++) {
    if (cursor->ptr[i] == child) {
      parent = cursor;
      return parent;
    } else {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

// Print the tree
void BPTree::display(Node *cursor) {
  if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i]);
      }
    }
  }
}

// Get the root
Node *BPTree::getRoot() {
  return root;
}
/////////////////////////////////////////////

int main(){
    ifstream arq1; arq1.open("listamini.csv");
    string linha;
    string word;
    //vector <infor> vel;
    int conti=0;

    BPTree node;
    //*aux_node = node;
    linha = "batata frita";
  node.insert(5);
    node.insert(15);
  
  node.insert(25);
  
  node.insert(35);
  
  node.insert(45);
  
  node.insert(55);
  
  node.insert(40);
  
  node.insert(30);
  
  node.insert(27);
  
  node.insert(18);
  
  node.insert(67);
  
  node.insert(28);
  
  node.insert(32);
  
  node.bota_string(5,linha);

node.bota_string(15,linha);
node.bota_string(25,linha);
node.bota_string(35,linha);
node.bota_string(45,linha);
node.bota_string(55,linha);
node.bota_string(40,linha);
node.bota_string(30,linha);
node.bota_string(27,linha);
node.bota_string(18,linha);
node.bota_string(67,linha);
node.bota_string(28,linha);
node.bota_string(32,linha);
  
  node.search(99);
  node.search(15);

    //aux_node->info[chave] = "teste";
  //cout << achou << " " << chave << " " << aux_node->info[chave] << endl;
  //node.display(node.getRoot());

/*
    if ( arq1.is_open() ) {   
        //if(arq1.good()){
        //    arq1 >> linha;
        //    node.insert(conti);
        //    node.bota_string(conti, linha);
        //    conti++;
        //}
        
        while ( arq1.good() ) {
            arq1 >> linha;

            //cout << linha;
            /*stringstream str(linha);
            info inf;
            
                getline(str, word, ';');
                inf.ISSUE = word;*/
                
            

        //}          
    //}
    

    //ofstream earq("lista-ordenada.csv", ios::out | ios::binary);
    //if(!earq) {
    //  cout << "Cannot open file!" << endl;
    //  return 1;
   //}

}