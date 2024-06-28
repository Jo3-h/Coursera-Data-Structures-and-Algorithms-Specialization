#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::map;

void sort_characters(const string &text, vector<int> &order){

	vector<int> count(5, 0);
	map<char, int> charToIdx;
	charToIdx['$'] = 0;
	charToIdx['A'] = 1;
	charToIdx['C'] = 2;
	charToIdx['G'] = 3;
	charToIdx['T'] = 4;
	for (int i = 0; i < text.size(); i++)
	{
		count[charToIdx[text[i]]]++;
	}
	for (int i = 1; i < count.size(); i++)
	{
		count[i] += count[i - 1];
	}
	for (int i = text.size() - 1; i >= 0; i--)
	{
		int idx = charToIdx[text[i]];
		count[idx] -= 1;
		order[count[idx]] = i;
	}

}

void compute_char_myClass(const string &text, vector<int> order, vector<int> &myClass){

  myClass[order[0]] = 0;

  for (int i=1; i<text.size(); i++){
    if (text[order[i]] != text[order[i-1]]){
      myClass[order[i]] = myClass[order[i-1]] + 1;
    } else {
      myClass[order[i]] = myClass[order[i-1]];
    }
  }

}

void sort_doubled(const string &text, int l, vector<int> &order, vector<int> &myClass){

  vector<int> count(text.size(), 0);
  vector<int> newOrder(text.size());

  for (int i=0; i<text.size(); i++){
    count[myClass[i]] = count[myClass[i]] + 1;
  }
  for (int i=1; i<count.size(); i++){
    count[i] = count[i] + count [i-1];
  }
  for (int i=text.size()-1; i >= 0; i--){
    int start = (order[i] - l + text.size())%(text.size());
    int cl = myClass[start];
    count[cl] = count[cl] - 1;
    newOrder[count[cl]] = start;
  }
  order = newOrder;

}

void update_myClass(const vector<int> &order, vector<int> &myClass, int l){

  vector<int> newClass(order.size());
  newClass[order[0]] = 0;
  for (int i=1; i<order.size(); i++){
    int cur = order[i];
    int prev = order[i-1];
    int mid = cur + l;
    int midPrev = (prev + l)%(order.size());
    if ((myClass[cur] != myClass[prev]) || (myClass[mid] != myClass[midPrev])){
      newClass[cur] = newClass[prev] + 1;
    } else {
      newClass[cur] = newClass[prev];
    }
  }
  myClass = newClass;

}

void print(vector<int> in){
  for (int i=0; i<in.size(); i++){
    cout<<in[i]<<" ";
  }
  cout<<"\n";
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {

  vector<int> res;
  vector<int> order(text.size());
  vector<int> myClass(text.size());
  sort_characters(text, order);
  //print(order);
  compute_char_myClass(text, order, myClass);
  int l = 1;
  while (l < text.size()){
    sort_doubled(text, l, order, myClass);
    update_myClass(order, myClass, l);
    //print(order);
    l = 2*l;
  }
  res = order;
  return res;
}


vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {

  vector<int> result;
  int minIndex = 0;
	int maxIndex = text.size();
	while (minIndex < maxIndex) {
		int midIndex = (minIndex + maxIndex) / 2;
		int flag = text.compare(suffix_array[midIndex], std::min(text.size() - suffix_array[midIndex], pattern.size()), pattern);
		if (flag < 0) {
			minIndex = midIndex + 1;
		}
		else {
			maxIndex = midIndex;
		}
	}

	int start = minIndex;
	maxIndex = text.size();
	while (minIndex < maxIndex) {
		int midIndex = (minIndex + maxIndex) / 2;
		int flag = text.compare(suffix_array[midIndex], std::min(text.size() - suffix_array[midIndex], pattern.size()), pattern);
		if (flag > 0) {
			maxIndex = midIndex;
		}
		else {
			minIndex = midIndex + 1;
		}
	}

	int end = maxIndex;
	if (start <= end) {
		for (int i = start; i < end; i++) {
			result.push_back(suffix_array[i]);
    }
	}

  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
