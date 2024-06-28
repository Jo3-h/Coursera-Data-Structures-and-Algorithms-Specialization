#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void print_vector(vector<int> a){
    for (int i=0; i<a.size(); i++){
        cout<<a[i]<<" ";
    }
}

vector<int> sliding_window(vector<int> values, int len){
    vector<int> ans;
    std::deque<int> q;
    for (int i=0; i<len; i++){

        // if q is empty then add value
        if (q.size() == 0){
            q.push_back(values[i]);
            continue;
        }

        // if value is smaller or equal to the current largest then add to back of q
        if (values[i] <= q.front()){
            while (q.size() && q.back() < values[i]){
                q.pop_back();
            }
            q.push_back(values[i]);
        }

        // if value is larger than current largest then delete all current and add to q
        if (values[i] > q.front()){
            while (q.size()){
                q.pop_back();
            }
            q.push_front(values[i]);
        }
    }


    ans.push_back(q.front());
    //q.pop_front();

    for (int i=len; i<values.size(); i++){

        // if q has size and the element coming out of the window is current biggest
        // remove from the front of the queue
        if (q.size() && values[i-len] == q.front()){
            q.pop_front();
        }

        // if q has size and new value is larger than the back element of the current window
        // then remove elements until it is the smallest in the q
        if (q.size() && values[i] > q.back()){
            while (q.size() && values[i] > q.back()){
                q.pop_back();
            }
        }

        // add element to back of q and push current largest to ans
        q.push_back(values[i]);
        ans.push_back(q.front());

    }

    return ans;
}



int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    vector<int> ans = sliding_window(A, w);
    print_vector(ans);

    return 0;
}
