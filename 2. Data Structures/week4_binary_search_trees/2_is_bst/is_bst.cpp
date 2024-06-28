#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
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

  bool IsBinarySearchTree(Node n, int min, int max) {
  // Implement correct algorithm here
  if (nodes.size() == 0){
    return true;
  }

  if (n.key < min || n.key > max){
    //cout << "fail at node with key: " << n.key << " with min: " << min << ", and max: "<<max<<"\n";
    return false;
  }
  if (n.left == -1 && n.right == -1){
    return true;
  } else if (n.left == -1){
    return IsBinarySearchTree(nodes[n.right], n.key + 1, max);
  } else if (n.right == -1){
    return IsBinarySearchTree(nodes[n.left], min, n.key - 1);
  }
  //cout << "done node: " << n.key <<"\n";
  return (IsBinarySearchTree(nodes[n.left], min, n.key - 1) && IsBinarySearchTree(nodes[n.right], n.key + 1, max));
}
};

/*bool checkLower(const vector<Node>& tree, int key, int i){
  if (tree[i].key >= key){
    cout << "compare low fal: "<< tree[i].key<< " / "<<key<<"\n";
    return false;
  }
  if (tree[i].left != -1){
    return checkLower(tree, key, tree[i].left);
  }
  if (tree[i].right != -1){
    return checkLower(tree, key, tree[i].right);
  }
  cout << "compare low tru: "<< tree[i].key<< " / "<<key<<"\n";
  return true;
}

bool checkHigher(const vector<Node>& tree, int key, int i){
  if (tree[i].key <= key){
    cout << "compare hig fal: "<< tree[i].key<< " / "<<key<<"\n";
    return false;
  }
  if (tree[i].left != -1){
    return checkHigher(tree, key, tree[i].left);
  }
  if (tree[i].right != -1){
    return checkHigher(tree, key, tree[i].right);
  }
  cout << "compare hig tru: "<< tree[i].key<< " / "<<key<<"\n";
  return true;
}*/

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
  if (tree.IsBinarySearchTree(tree.nodes[0], -2147483646, 2147483647)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
