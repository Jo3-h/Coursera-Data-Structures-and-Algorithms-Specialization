#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

struct Node {

  string edge;
  vector<int> children;
  Node(){
    
  }
  Node(const std::string& sub, vector<int> child) : edge(sub) {
      children.insert(children.end(), child.begin(), child.end());
  }

};

struct suffix_tree {

  vector<Node> nodes;

  suffix_tree(string input){
    nodes.push_back(Node());
    for (int i=0; i<input.size(); i++){
      add(input.substr(i));
    }
  }

  public:

  void add(string text){
    int n = 0;
    int i = 0;
    while (i < text.size()){
      char cur = text[i];
      int x = 0;
      int n2;
      while (true){
        vector<int> child = nodes[n].children;
        if (x == child.size()){
          n2 = nodes.size();
          nodes.push_back(Node(text.substr(i), vector<int>()));
          nodes[n].children.push_back(n2);
          return;
        }
        n2 = child[x];
        if (nodes[n2].edge[0] == cur){
          break;
        }
        x++;
      }
      string next = nodes[n2].edge;
      int j=0;
      while (j<next.size()){
        if (text[i+j] != next[j]){
            int m = n2;
            n2 = nodes.size();
            vector<int> in;
            in.push_back(m);
            nodes.push_back(Node(next.substr(0,j), in));
            nodes[m].edge = next.substr(j);
            nodes[n].children[x] = n2;
            break;

        }
        j++;
      }
      i+=j;
      n=n2;

    }

  }

};


// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself

  
  // first build a tree of suffixes.
  suffix_tree tree = suffix_tree(text);
  for (int i=0; i<tree.nodes.size(); i++){
    result.push_back(tree.nodes[i].edge);
  }


  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
