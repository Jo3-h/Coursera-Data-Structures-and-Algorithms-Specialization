 ----------------------void siftDown(vector<pair<int, int> > &pq, int i){

  while (pq)

}

int find(vector<int> &pq, int index){

  int i = 0; 
  while (i < pq.size()){

    // if the value has been found return the index
    if (index == pq[i].second){
      return i;
    }

    // if the value is larger than the current move to the child node. 
    i++;

  }

  return -1;
}

void changePriority(vector<pair<int, int> > &pq, int index, int value){

  // set temp to be the position in pq that needs to be changed.
  int temp = find(pq, index);

  // if find failed then return
  if (temp == -1){
    return;
  }

  // change the value of dist for this node then siftUp since value can't be changed to larger value
  pq[temp] = make_pair(value, index);
  siftUp[temp];
  return;

}

void swap(vector<pair<int, int> > &pq, int j, int i){

  // create temp variable and swap elements 
  pair<int, int> temp = pq[j];
  pq[j] = pq[i];
  pq[i] = temp;
  return;

}

void siftUp(vector<pair<int, int> > &pq, int j){

  // if trying to shift up the root node then return
  if (j == 0){
    return;
  }

  // if the node is smaller than the parent node then swap then shift up the parent node. 
  if (pq[j].first < pq[(j-1)%2].first){
    swap(pq, j, (j-1)%2);
    siftUp(pq, (j-1)%2);
  }

  // if no swaps need to be made then return
  return;

}

void add(vector<pair<int, int> > &pq, pair<int, int> n){
  pq.push_back(n);
  siftUp(pq, pq.size());
}

pair<int, int> extractMin(vector<pair<int, int> > &pq){

  pair<int, int> temp = pq[0]; 
  changePriority(pq, 0, 9999999);
  siftDown 

}
