#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct word_position
{
  string file_name;
  int line;
  int index;
};

class InvertedIndex
{
  map<string, vector<word_position>> Dictionary;
  vector<string> filelist;

public:
  void addfile(string filename);
  void show_files();
  void search(string word);
};
int InvertedIndexFunction(string name);