#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	char value;
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
		for (int i=0; i<4; i++){
			next[i] = -1;
		}
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

vector<Node> make_trie(vector<string> patterns){

	Node root = Node();
	vector<Node> tree;
	tree.push_back(root);

	// loop through each pattern and create trie
	for (int i=0; i<patterns.size(); i++){

		int index  = 0;

		// loop each character of pattern
		for (int j=0; j<patterns[i].size(); j++){

			int next = letterToIndex(patterns[i][j]);
			if (tree[index].next[next] != -1){
				index = tree[index].next[next];
			} else {
				tree[index].next[next] = tree.size();
				tree.push_back(Node());
				index = tree.size()-1;
				tree[index].value = patterns[i][j];
			}

			if (j == patterns[i].size()-1){
				tree[index].patternEnd = true;
			}

		}
	}

	return tree;

}

bool match(vector<Node> tree, string text, int i){

	cout<<"----------- checking match for index "<<i<<"\n";

	int next = letterToIndex(text[i]);
	int index = tree[0].next[next];

	if (index == -1){
		return false;
	}

	if (tree[index].patternEnd){
		return true;
	}

	i++;

	while (i < text.size()){

		next = letterToIndex(text[i]);

		cout<<"tree["<<index<<"] patternEnd: "<<tree[index].patternEnd<<"\n";
		if (tree[index].patternEnd){
		//	cout<<"found match\n\n";
			return true;
		}

		if (tree[index].next[next] != -1){
			index = tree[index].next[next];
			cout<<"moving to node (index): "<<index<<"\n";
			i++;
		} else {

			return false;
		}
	}

	if (i == text.size()-1){
		return true;
	}

	//cout<<"text.size() == "<<text.size()<<"\n";
	//cout<<"i == "<<i<<"\n";
	cout<<"reached end of text size\n\n";
	return false;

}

void print(vector<Node> tree){

	for (int i=0; i<tree.size(); i++){

		cout<<"--------------- Node "<<i<<"\n";
		cout<<"end: "<<tree[i].patternEnd<<"\n";
		cout<<"next -> [";
		for (int j=0; j<4; j++){
			cout<<tree[i].next[j]<<" ";
		}
		cout<<"]\n\n";

	}
	cout<<"\n\n\n";

}

vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;

	// create trie
	vector<Node> tree = make_trie(patterns);
	//print(tree);
	for (int i=0; i<text.size(); i++){
		
		int cur = i;
		int symbol = letterToIndex(text[cur]);
		int index = 0;
		while (true){
			if (tree[index].patternEnd){
				result.push_back(i);
				break;
			} else if (tree[index].next[symbol] != NA){
				index = tree[index].next[symbol];
				cur++;
				if (cur >= text.size()){
					if (tree[index].patternEnd){
						result.push_back(i);
					}
					break;
				}
				symbol = letterToIndex(text[cur]);
			} else {
				break;
			}

		}


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
