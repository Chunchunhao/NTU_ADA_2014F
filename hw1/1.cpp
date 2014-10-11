#include <iostream>
#include <vector>

using namespace std;

struct cubic {
  long long w;
  long long h;
};

bool cmp( const cubic a, const cubic b ){
  if( a.w == b.w)
    return a.h > b.h;
  return a.w > b.w;
}

int DC( vector<cubic>::iterator, vector<cubic>::iterator, int &); 

int main() {
  
  int tries;
  cin >> tries;
  while( tries-- ) {
    int boxesN;

    // Read boxes to memory 
    cin >> boxesN;
    vector<cubic> box; 
    box.resize(boxesN);
    for( int i=0; i < boxesN; i++) {
      cin >> box[i].w >> box[i].h ;
      if( box[i].w < box[i].h) {
        int tmp = box[i].h;
        box[i].h = box[i].w;
        box[i].w = tmp;
      }
    }

    // Sort the Width 
    sort( box.begin(), box.end(), cmp);
   
    int count = 0;
    DC(box.begin(), box.end()-1, count);
    // DP and output
    cout << count << endl;
  }
  return 0;
}


int DC( vector<cubic>::iterator now, vector<cubic>::iterator end, int &acum){
  if( now == end)
    return 0;
  else {
    // test c++11
    auto next = now + 1;
    int inclu;
    if( (now->w >= next->w) && (now->h >= next->h)){
      inclu = 1 + DC( next, end, acum);
      if( now->w == next->w && now->h == next->h )
        inclu ++;
      acum += inclu;
      return inclu;
    }
    else
      inclu = DC( next, end, acum);
      acum += inclu;
      return inclu;
  }
}

