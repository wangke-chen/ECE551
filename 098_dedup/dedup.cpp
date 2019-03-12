#include <dirent.h>
#include <limits.h>
#include <sys/types.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class HashTable
{
 private:
  vector<vector<string> > table;
  hash<string> hasher;

 public:
  HashTable(size_t n) { table.resize(n); }
  string isInTable(string file, unsigned int h) {
    string s;
    for (vector<string>::iterator it = table[h].begin(); it != table[h].end(); ++it) {
      if (compareFile(*it, file)) {
        s = (*it);
        return s;
      }
    }
    return s;
  }

  bool compareFile(string file1, string file2) {
    string s1 = readfile(file1);
    string s2 = readfile(file2);
    return s1 == s2;
  }

  string readfile(string file) {
    ifstream input(file.c_str());
    string input_data;
    string line;
    while (!input.eof()) {
      getline(input, line);
      input_data.append(line);
    }
    return input_data;
  }

  void output(vector<string> & filenames, ostream & shell) {
    shell << "#!/bin/bash" << endl;
    for (vector<string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
      string s = readfile(*it);
      unsigned int h = hasher(s);
      h = h % table.size();
      if (table[h].size() == 0) {
        table[h].push_back(*it);
      }
      else {
        string s = isInTable(*it, h);
        if (s.length() != 0) {
          shell << "#Removing " << *it << " (duplicate of " << s << ")." << endl;
          shell << "rm " << *it << endl;
        }
        else {
          table[h].push_back(*it);
        }
      }
    }
  }
};

void readDirectory(vector<string> & filenames, string path) {
  DIR * dir;
  struct dirent * ent = NULL;
  if ((dir = opendir(path.c_str())) == NULL) {
    cerr << "Could not open the directory.\n";
    closedir(dir);
    exit(EXIT_FAILURE);
  }
  while ((ent = readdir(dir)) != NULL) {
    string filename = ent->d_name;
    if (filename == "." || filename == "..") {
      continue;
    }
    else if (ent->d_type == DT_REG) {
      filenames.push_back(path + '/' + filename);
    }
    else if (ent->d_type == DT_DIR) {
      readDirectory(filenames, path + '/' + filename);
    }
    else {
      cerr << "Unknown file type. " << filename << " will be ignored." << endl;
      continue;
    }
  }
  closedir(dir);
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    cerr << "Usage: at least one directory.\n";
    exit(EXIT_FAILURE);
  }
  vector<string> filenames;
  for (int i = 1; i < argc; i++) {
    string path = argv[i];
    readDirectory(filenames, path);
  }
  HashTable ht(filenames.size());
  ht.output(filenames, cout);
  return EXIT_SUCCESS;
}
