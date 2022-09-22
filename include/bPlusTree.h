#define LIM 300

// Struct para armazenar os dados do arquivo
struct Movie
{
  int id;
  char title[LIM]; // Title of the movie
  // int year;           // Year of release
  // char director[LIM]; // Director of the movie
  char genre[LIM]; // Genre of the movie
  int map_inv;
  int imdb;
};

// BPTree node;
class Node
{
  bool IS_LEAF;
  int *key, size; // size is the number of keys in the node
  Node **ptr;
  friend class BPTree;
  // const char* info[4][250];
  // string info[4];
  Movie filmes[4];

public:
  Node();
};

// BP tree internal node
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