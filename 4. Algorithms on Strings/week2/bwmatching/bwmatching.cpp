#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yoursel

   int a, c, g, t, dollar;
   a = c = g = t = dollar = 0;
   occ_count_before['A'].push_back(0);
   occ_count_before['C'].push_back(0);
   occ_count_before['G'].push_back(0);
   occ_count_before['T'].push_back(0);
   occ_count_before['$'].push_back(0);
   for (int i=0; i<bwt.size(); i++){
      char cur = bwt[i];
      if (cur == 'A'){
         a++;
      } else if (cur == 'C'){
         c++;
      } else if (cur == 'G'){
         g++;
      } else if (cur == 'T'){
         t++;
      } else if (cur == '$') {
         dollar++;
      }
      occ_count_before['A'].push_back(a);
      occ_count_before['C'].push_back(c);
      occ_count_before['T'].push_back(t);
      occ_count_before['G'].push_back(g);
      occ_count_before['$'].push_back(dollar);
   }
   starts['$'] = 0;
   starts['A'] = dollar;
   starts['C'] = starts['A'] + a;
   starts['G'] = starts['C'] + c;
   starts['T'] = starts['G'] + g;

}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                      map<char, int>& starts, 
                      map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  int t = 0;
  int b = bwt.size() -1;
  string cur = pattern;
  while (t <= b){

   if (!cur.empty()){
      
   
       char sym = *(cur.end()-1);
       cur.pop_back();
       if (occ_count_before[sym][t+1] < occ_count_before[sym][b+1] || occ_count_before[sym][t] < occ_count_before[sym][b+1]){
          t = starts[sym] + occ_count_before[sym][t];
          b = starts[sym] + occ_count_before[sym][b+1] -1;

       } else {
          return 0;
       }

   } else {
      return b - t + 1;
   }

  }
  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
