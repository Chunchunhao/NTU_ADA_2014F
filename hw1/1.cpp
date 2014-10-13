#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct cubic {
  long long w = 0;
  long long h = 0;
};

bool cmp( const cubic a, const cubic b ){
  if( a.w == b.w)
    return a.h > b.h;
  return a.w > b.w;
}

long long  DC( vector<cubic>::iterator, vector<cubic>::iterator, long long &); 

int main() {
  
  int tries;
  cin >> tries;
  if( tries == 0) { return 0; }

  while( tries-- ) {
    int boxesN;

    // Read boxes to memory 
    cin >> boxesN;
    if( boxesN == 0) { 
      cout << "0" << endl;
      continue; 
    }

    vector<cubic> box; 
    box.resize(boxesN);
    for( auto i=0; i < box.size(); i++) {
      cin >> box[i].w >> box[i].h ;
      if( box[i].w < box[i].h) {
        long long tmp = box[i].h;
        box[i].h = box[i].w;
        box[i].w = tmp;
      }
    }

    // Sort the Width 
    sort( box.begin(), box.end(), cmp);
    long long count = 0;
    DC(box.begin(), box.end()-1, count);
    // DP and output
    cout << count << endl;
  }
  return 0;
}

// return `the one include `
long long DC( vector<cubic>::iterator now, vector<cubic>::iterator end, long long &acum){
  if( now == end)
    return 0;
  else {
    // test c++11
    vector<cubic>::iterator next = now + 1;
    long long inclu;
    if( (now->w == next->w) && (now->h == next->h)) {
      inclu = 2 + DC( next, end, acum);
      acum += inclu;
      return inclu-1;
      
    }
    else if( (now->w >= next->w) && (now->h >= next->h)){
      inclu = 1 + DC( next, end, acum);
      acum += inclu;
      return inclu;
    }
    else if( now->h < next->h ){
      DC( next, end, acum);
      do {
        if( next == end )
          return 0;
        next = next + 1;
      } while( now->h < next->h);
      
      inclu = 1 + DC( next, end, acum);
      acum += 1; // because DC re calculate;

      vector<cubic>::iterator nextTest = next + 1;
      if( nextTest->w == next->w && nextTest->h == next->h){
        acum -=1;
        inclu -=1;
      }
      return inclu; 
    }
    else {
      inclu = DC( next, end, acum);
      acum += inclu;
      return inclu;
    }
  }
}
