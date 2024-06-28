#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;

struct Query {
    string type, s;
    size_t ind;
};

struct list {
    vector<string> elements;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<list> table;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        for (int i=0; i<bucket_count; i++){
            table.resize(bucket_count);
        }
    }

    Query readQuery() const {
        Query query;
        //cout << "query: ";
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void processQuery(const Query& query) {
        if (query.type == "check"){
            list cur = table[query.ind];
            for (int i = cur.elements.size()-1; i>=0; i--){
                cout << cur.elements[i] << " ";
            } cout << "\n";
        } else if (query.type == "add"){
            int h = hash_func(query.s);
            for (int i=0; i<table[h].elements.size(); i++){
                if (table[h].elements[i] == query.s){
                    return;              
                }
            }
            table[h].elements.push_back(query.s);
        } else if (query.type == "del"){
            int h = hash_func(query.s);
            for (int i=0; i<table[h].elements.size(); i++){
                if (table[h].elements[i] == query.s){
                    table[h].elements[i] = "";
                    return;
                }
            }
        } else {
            int h = hash_func(query.s);
            for (int i=0; i<table[h].elements.size(); i++){
                if (table[h].elements[i] == query.s){
                    cout << "yes\n";
                    return;
                }
            }
        cout << "no\n";
        }
        return;
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

        /*
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
        */