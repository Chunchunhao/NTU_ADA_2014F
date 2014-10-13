#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct cubic {
  unsigned w = 0;
  unsigned h = 0;
};

bool cmp( const cubic a, const cubic b ){
  if( a.w == b.w)
    return a.h > b.h;
  return a.w > b.w;
}

long long  DC( vector<cubic>::iterator, vector<cubic>::iterator, long long &, int a); 

int main() {
  
  unsigned tries;
  cin >> tries;
  if( tries == 0) { return 0; }

  while( tries-- ) {
    unsigned boxesN;

    // Read boxes to memory 
    cin >> boxesN;
    if( boxesN == 0) { 
      cout << "0" << endl;
      continue; 
    }

    //cout << "Bein : Box :: " << boxesN << endl;
    vector<cubic> box;
    box.resize(boxesN); 

    for( auto i=0; i < box.size(); i++) {
      cin >> box[i].w >> box[i].h ;
      //scanf("%lld %lld", &box[i].w, &box[i].h);
      //cout << "DAMN : " << box[i].w << " " << box[i].h << endl;
      if( box[i].w < box[i].h) {
        unsigned tmp = box[i].h;
        box[i].h = box[i].w;
        box[i].w = tmp;
      }
    }

    // Sort the Width 
    sort( box.begin(), box.end(), cmp);
   
    /*
    cout << "FUCK, Wwhat happened ?? " << endl;
    for( auto i=0; i < box.size(); i++)
      cout << "( " << box[i].w << " , " << box[i].h << " )" << endl;
    cout << "_____________________" << endl;
    */
    long long count = 0;
    DC(box.begin(), box.end()-1, count, 0);
    // DP and output
    cout << count << endl;
  }
  return 0;
}

// return `the one include `
long long DC( vector<cubic>::iterator now, vector<cubic>::iterator end, long long &acum, int a){
  if( now == end)
    return 0;
  else {
    vector<cubic>::iterator next = now + 1;
    long long inclu;
    if( (now->w >= next->w) && (now->h >= next->h) ){
      if( a == 0 ){
        vector<cubic>::iterator next = now + 1;
        while( (now->w == next->w) && (now->h == next->h)){
          acum += 1;
          if( next != end )
            next++;
          else
            break;
        }
      }
      inclu = 1 + DC( next, end, acum, 0);
      acum += inclu;
      return inclu;
    }
    else if( now->h < next->h ){
      DC( next, end, acum, 0);
      do {
        next = next + 1;
        if( next == end )
          break;
        //cout << "Point+nxt :: ( " << next->w << " , " << next->h << " )" << endl;
      } while( now->h < next->h);
      //cout << "TraceBack:: ( " << next->w << " , " << next->h << " )" << endl;

      if( next != end){
        inclu = 1 + DC( next, end, acum, 1);
        acum += 1; // because DC re calculate;
      }
      else
        inclu = 0;
      // if( now->w == next->w && now->h == next->h )
      //   inclu ++;
      //cout << "WHY 2:: ( " << now->w << " , " << now->h << " ) :: [ " << acum << " , " << inclu << " ] " << endl;
      return inclu; 
    }
  }
}
