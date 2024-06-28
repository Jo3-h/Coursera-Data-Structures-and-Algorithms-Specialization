#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

typedef map<char, pair<int, bool> edges;
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

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}


}

bool check(const string &text, trie &tree, int s){

	int index = 0;
	while (index >= 0 && index < tree.size()){

		if (s > text.size()){
			//cout<<"s is out of range\n";
			return false;
		}

		char look = text[s];

		// if the node being visited is empty then we're at the end of a pattern and return true
		if (!tree[index].size()){
			//cout<<"tree has zero size at index = "<<index<<"\n";
			return true;
		}

		// else if the next character is in the tree then move to that node
		if (tree[index].find(look) != tree[index].end()){
			//cout<<"check next in pattern\n";
			index = tree[index].find(look)->second;
			s++;
			continue;
		}

		// if the node isnt a leaf and the next char isn't in the tree then return false. 
		//cout<<"no node found with this pattern\n";
		return false;

	}
	return false;

}

vector <int> solve (const string& text, int n, vector <string>& patterns)
{
	vector <int> result;

	// build a trie from the patterns
	trie tree = build_trie(patterns);

	for(edges::const_iterator it = tree[1].begin(); it != tree[1].end(); ++it){
    	//std::cout << it->first << " " << it->second << "\n";
	}

	// loop through the text
	for (int i=0; i<text.size(); i++){

		if (check(text, tree, i)){
			result.push_back(i);
			//cout<<"match this element\n";
			continue;
		}

	//cout<<"no match\n";

	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
