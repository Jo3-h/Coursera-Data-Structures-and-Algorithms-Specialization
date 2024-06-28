#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;
    int height;

    Node() {
      this->parent = NULL;
      height = 0;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  //int root;
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0){
      nodes[child_index].setParent(&nodes[parent_index]);
      nodes[child_index].key = child_index;
      nodes[child_index].height = 0;
    }
  }
  // std::cout<< "root node: "<<root;

  Node* temp;
  for (int i=0; i<n; i++){
    temp = &nodes[i];
    while (temp->parent != NULL){
      if (temp->parent->height > 0){
        nodes[i].height = nodes[i].height + temp->parent->height + 1;
        break;
      } else {
        nodes[i].height = nodes[i].height + 1;
      }
      temp = temp->parent;
      //std::cout<<"temp: "<<temp->key<<std::endl;
    }
  }
  int maxHeight = 0;
  for (int i=0; i<n; i++){
    if (nodes[i].height > maxHeight){
      maxHeight = nodes[i].height;
    }
  }
  for (int i=0; i<n; i++){
    // nodes[0].height = 9;
    //std::cout << "node "<< i << ": "<< nodes[i].height<<std::endl;

  }
  std::cout<<maxHeight + 1;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
