#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";

  // create a vector of all different permuatations of rotation
  vector<string> matrix;
  for (int i=0; i<text.size(); i++){

    string temp = text.substr(i) + text.substr(0, i);
    matrix.push_back(temp);

  }

  // sort the matrix into alphebetical order
  std::sort(matrix.begin(), matrix.end());

  // create a string of the last elements
  for (int i=0; i<matrix.size(); i++){

    result += matrix[i][matrix[i].size()-1];

  }


  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}