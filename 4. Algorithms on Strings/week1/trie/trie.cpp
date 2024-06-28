#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;
using std::make_pair;
using std::cout;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  edges temp;
  t.push_back(temp);

  // loop through each pattern in the intput vector
  for (int i=0; i<patterns.size(); i++){

    // set current to be the pattern that we're upto
    string current = patterns[i];
    int index = 0;

    for (int j=0; j<current.size(); j++){

      if (t[index].find(current[j]) != t[index].end()){
        
        index = t[index].find(current[j])->second;
        //cout<<"node "<<current[j]<<" found, moving to node "<<index<<"\n\n";
      } else {
        t.push_back(temp);
        t[index].insert(make_pair(current[j], t.size()-1));
        index = t.size()-1;
         //cout<<"node "<<current[j]<<" not found, creating node "<<index<<"\n\n";
      }
    }
  }


  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}