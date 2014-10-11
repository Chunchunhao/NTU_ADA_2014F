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

    //cout << "Bein : Box :: " << boxesN << endl;
    vector<cubic> box; 
    box.resize(boxesN);
    for( auto i=0; i < box.size(); i++) {
      cin >> box[i].w >> box[i].h ;
      //scanf("%lld %lld", &box[i].w, &box[i].h);
      //cout << "DAMN : " << box[i].w << " " << box[i].h << endl;
      if( box[i].w < box[i].h) {
        long long tmp = box[i].h;
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
    DC(box.begin(), box.end()-1, count);
    // DP and output
    cout << count << endl;
  }
  return 0;
}


long long DC( vector<cubic>::iterator now, vector<cubic>::iterator end, long long &acum){
  if( now == end)
    return 0;
  else {
    // test c++11
    auto next = now + 1;
    long long inclu;
    if( (now->w == next->w) && (now->h == next->h)) {
      inclu = 2 + DC( next, end, acum);
      acum += inclu;
      //cout << "WHY 0:: ( " << now->w << " , " << now->h << " ) :: [ " << acum << " , " << inclu << " ] " << endl;
      return inclu-1;
      
    }
    else if( (now->w >= next->w) && (now->h >= next->h)){
      inclu = 1 + DC( next, end, acum);
      acum += inclu;
      //cout << "WHY 1:: ( " << now->w << " , " << now->h << " ) :: [ " << acum << " , " << inclu << " ] " << endl;
      return inclu;
    }
    else if( now->h < next->h ){
      DC( next, end, acum);
      //cout << "Point :: ( " << now->w << " , " << now->h << " )" << endl;
      
      do {
        next = next + 1;
        if( next == end) { 
          //cout << "hakunamatat" << endl;
          return 0; 
        };
        //cout << "TraceBack:: ( " << next->w << " , " << next->h << " )" << endl;
      } while( now->h < next->h);
      
      inclu = 1 + DC( next, end, acum);
      
      if( now->w == next->w && now->h == next->h )
        inclu ++;
      
      //cout << "WHY 2:: ( " << now->w << " , " << now->h << " ) :: [ " << acum << " , " << inclu << " ] " << endl;
      return inclu; 
    }
    else
      inclu = DC( next, end, acum);
      acum += inclu;
      //cout << "WHY 3:: ( " << now->w << " , " << now->h << " ) :: [ " << acum << " , " << inclu << " ] " << endl;
      return inclu;
  }
}

