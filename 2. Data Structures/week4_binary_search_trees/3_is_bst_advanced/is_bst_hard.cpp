#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  long long key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

struct Tree {
  vector<Node> nodes;

  bool isEmpty(){
    if (nodes.size() == 0){
      return true;
    }
    return false;
  }

  bool IsBinarySearchTree(Node n, long long min, long long max) {
  // Implement correct algorithm here
  if (n.key < min || n.key > max){
    //cout << "fail at node with key: " << n.key << " with min: " << min << ", and max: "<<max<<"\n";
    return false;
  }
  if (n.left == -1 && n.right == -1){
    return true;
  } else if (n.left == -1){
    return IsBinarySearchTree(nodes[n.right], n.key, max);
  } else if (n.right == -1){
    return IsBinarySearchTree(nodes[n.left], min, n.key - 1);
  }
  //cout << "done node: " << n.key <<"\n";
  return (IsBinarySearchTree(nodes[n.left], min, n.key - 1) && IsBinarySearchTree(nodes[n.right], n.key, max));
}
};

int main() {
  int nodes;
  cin >> nodes;
  Tree tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.nodes.push_back(Node(key, left, right));
  }
  if (tree.isEmpty()){
    cout << "CORRECT" << endl;
    return 0;
  }
  if (tree.IsBinarySearchTree(tree.nodes[0], -9223372036854775807, 9223372036854775807)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
