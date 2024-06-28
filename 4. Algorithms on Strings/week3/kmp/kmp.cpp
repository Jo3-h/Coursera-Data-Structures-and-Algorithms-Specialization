#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

vector<int> prefix_function(const string &pattern){

  vector<int> result(pattern.size(), 0);
  int border = 0;

  for (int i=1; i<pattern.size(); i++){

    while (border > 0 && pattern[i] != pattern[border]){

      border = result[border-1];

    }

    if (pattern[i] == pattern[border]){
      border = border + 1;
    } else {
      border = 0;
    }
    result[i] = border;
  }

  return result;

}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  string special = pattern + '$' + text;

  vector<int> prefix = prefix_function(special);

  for (int i=pattern.size()+1; i<special.size(); i++){
    if (prefix[i] == pattern.size()){
      result.push_back(i-2*(pattern.size()));
    }
  }

  //cout<<"\n\nstring: "<<text;
  //cout<<"\npattern: "<<pattern;
  //cout<<"\nspecial: "<<special;
  //cout<<"\nprefix[]: ";
  //for (int i=0; i<prefix.size(); i++){
  //  cout<<prefix[i]<<" ";
  //}
  //cout<<"\n";

  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
