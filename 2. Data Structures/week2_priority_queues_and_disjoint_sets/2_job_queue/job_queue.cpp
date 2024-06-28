#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::cout;
using std::pair;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  vector<pair<int, long long> > q;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {

    for (int i=0; i<num_workers_; i++){
      pair<int, long long> n(i, 0);
      q.push_back(n);
    }
    //cout << "finished creating priority queue\n";
    //cout << "q size: " << q.size() << "\n";
    /*for (int i=0; i<q.size(); i++){
      cout << "position: " << i << "   worker: " << q[i].first << "   finish time: " << q[i].second << "\n";
    }*/

    pair<int, long long> current;
    for (int i=0; i<jobs_.size(); i++){
      /*cout << "queue: ";
      for (int i=0; i<q.size(); i++){
        cout << "<" << q[i].first << "," << q[i].second << "> ";
      } cout << "\n";*/
      current = popTop();
      assigned_workers_.push_back(current.first);
      start_times_.push_back(current.second);
      change(jobs_[i]);
      //cout << "current: " << current.first << "\n";
    }
  }

  void change(int n){
    q[0].second = q[0].second + n;
    siftDown(0);
    return;
  }

  pair<int, long long> popTop(){

    //cout << "finished popTop\n";
    return q[0];

  }
/*
  void insert(pair<int, long long> i){

    q.push_back(i);
    //cout << "pushback\n";
    siftUp(q.size()-1);
    //cout << "finished insert\n";
    return;

  }
  
  void siftUp(int i){
    if (i == 0){
      return;
      //cout << "finished siftUp\n";
    }
    while (i > 0 && q[i].second <= q[(i-1)/2].second){
      if (q[i].second < q[(i-1)/2].second){
        pair<int, long long> temp = q[i];
        q[i] = q[(i-1)/2];
        q[(i-1)/2] = temp;
        i = (i-1)/2;
      } else if (q[i].second == q[(i-1)/2].second && q[i].first < q[(i-1)/2].second){
        pair<int, long long> temp = q[i];
        q[i] = q[(i-1)/2];
        q[(i-1)/2] = temp;
        i = (i-1)/2;;
      } else {
        break;
      }
    }
    //cout << "finished siftUp\n";
    return;
  }
  */

  void siftDown(int i){

    while (i*2+1 < q.size()){

      int min = i;
      if (q[min].second > q[i*2+1].second){
        min = i*2+1;
      } else if (q[min].second == q[i*2+1].second && q[min].first > q[i*2+1].first){
        min = i*2+1;
      }
      if ((i+1)*2 < q.size() && q[min].second > q[(i+1)*2].second){
        min = (i+1)*2;
      } else if ((i+1)*2 < q.size() && q[min].second == q[(i+1)*2].second && q[min].first > q[(i+1)*2].first){
        min = (i+1)*2;
      }
      if (min != i){
        pair<int, long long> temp = q[min];
        q[min] = q[i];
        q[i] = temp;
        i = min;
      } else {
        break;
      }

    }
    //cout << "finished sift down\n";
    return;

  }



 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}


    // TODO: replace this code with a faster algorithm.
    /*assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker]){
          next_worker = j;
          break;
        }
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }*/