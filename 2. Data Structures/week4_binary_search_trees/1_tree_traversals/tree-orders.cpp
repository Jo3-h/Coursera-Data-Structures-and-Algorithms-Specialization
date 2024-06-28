#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void printIn(int i){

    if (left[i] != -1){
      printIn(left[i]);
    }
    cout << key[i] << " ";
    if (right[i] != -1){
      printIn(right[i]);
    }

  }

  void printPre(int i){

    cout << key[i] << " ";
    if (left[i] != -1){
      printPre(left[i]);
    }
    if (right[i] != -1){
      printPre(right[i]);
    }
  }

  void in_order() {
    printIn(0);
    cout << "\n";
  }

  void pre_order() { 
    printPre(0);
    cout << "\n";
  }

  void printPost(int i){
    if (left[i] != -1){
      printPost(left[i]);
    }
    if (right[i] != -1){
      printPost(right[i]);
    }
    cout << key[i] << " ";
  }

  void post_order() {
    printPost(0);
    cout << "\n";
  }
};

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  t.in_order();
  t.pre_order();
  t.post_order();
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

