#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

unsigned long long hash(string pattern, int p, int x){

    unsigned long long res = 0;
    for (int i=0; i<pattern.size(); i++){
        res = (res*x + pattern[i]) % p;
    }
    return res;
}

bool isEqual(string one, string two, int len){
    for (int i=len; i<=two.size()+len - 1; i++){
        if (one[i] != two[i-len]){
            return false;
        }
    }
    return true;
}

std::vector<long long> T_hash(string text, int pSize, int p, int x){
    int tSize = text.size();
    std::vector<long long> res(tSize-pSize+1);
    string temp = text.substr(tSize - pSize);
    res[tSize-pSize+1] = hash(temp, p, x);
    long long power = 1;
    for (int i=1; i<=pSize; i++){
        power = (power*x)%p;
    }

    for (int i=tSize-pSize; i>=0; i--){
        res[i] = (x*res[i+1] + temp[i] - power*temp[i+pSize])%p;
        //x*res[i+1] + (temp[i]-temp[i+pSize]*power)%p;
        if (res[i] < 0){
            //res[i]=res[i]+p;
        }
    }
    return res;
}

std::vector<int> rabinKarp(Data input){
    string pattern = input.pattern;
    string text = input.text;
    int p = int(1e9) + 7;
    int x = rand() % (p-1)+1;
    std::vector<int> ans;
    std::vector<long long> thash = T_hash(text, pattern.size(), p, x);
    unsigned long long phash = hash(pattern, p, x);
    for (int i=0; i<=(text.size()-pattern.size()); i++){
        std::cout<<"t: "<<thash[i]<<"  p: "<<phash<<"\n";
        if (thash[i] != phash){
            //std::cout<<"con";
            continue;
        }
        std::cout<<"consider: "<<i<<"   ";
        if (isEqual(text, pattern, i)){
            ans.push_back(i);
            std::cout<<"add: "<<i<<"\n";
            //std::cout<<"equal";
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(rabinKarp(read_input()));
    return 0;
}
