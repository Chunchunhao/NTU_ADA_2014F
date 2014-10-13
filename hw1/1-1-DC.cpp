#include <iostream>
#include <vector>
#include <algorithm>
#include <new>

using namespace std;

struct cubic {
  long long int w = 0;
  long long int h = 0;
};
bool cmp( const cubic a, const cubic b );

bool cmp( const cubic a, const cubic b ){
  if( a.w == b.w)
    return a.h > b.h;
  return a.w > b.w;
}
long long  DC( long long int, long long int, vector<cubic>&); 

int main() {
  
  long long int tries;
  cin >> tries;
  if( tries == 0) { return 0; }
  while( tries-- ) {
    long long int boxesN;
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
        long long int tmp = box[i].h;
        box[i].h = box[i].w;
        box[i].w = tmp;
      }
    }

    // Sort the Width 
    sort( box.begin(), box.end(), cmp);
    
    long long int count = 0, rp=1;
    
    // Dealing repeat box
    count += DC( 0, boxesN-1, box );
    

    for( auto i= box.begin(); i< box.end(); i++){
      if( i->w == (i+1)->w && i->h == (i+1)->h )
        rp ++;
      else{
        count += rp * (rp-1)/2;
        rp = 1;
      }
    }
    count += rp * (rp-1)/2;

    // DP and output
    cout << count << endl;
  }
  return 0;
}

long long  DC( long long int left, long long int right, vector<cubic>& aa) {
  long long int cc=0;
  long long int mid = (left + right)/ 2;
  //cout << "LL: " << left << ", M: "<< mid << ", R: " << right << endl;
  if( left < right) {
    // Divided
    cc += DC(left, mid, aa);
    cc += DC(mid+1, right, aa);
    // Conquer
    long long int i = left;
    long long int j = mid+1;
    //long long int boxxxx[100000][2];
    cubic tmp;
    vector<cubic> boxxxx;
    //long long int** boxxxx = new long long int[100000][2];

    while( i<= mid || j<= right){
      if( i > mid ){
        //boxxxx[k][0] = aa[j].w;
        //boxxxx[k][1] = aa[j].h;
        tmp.w = aa[j].w;
        tmp.h = aa[j].h;
        boxxxx.push_back(tmp);
        j++;
      }
      else if( j > right ){
        tmp.w = aa[i].w;
        tmp.h = aa[i].h;
        boxxxx.push_back(tmp);
        i++;
      }
      else if( aa[i].h >= aa[j].h ){
        //boxxxx[k][0] = aa[i].w;
        //boxxxx[k][1] = aa[i].h;

        tmp.w = aa[i].w;
        tmp.h = aa[i].h;
        boxxxx.push_back(tmp);

        cc += right - j + 1; 
        // 有 bug? 100 20// 90 80 // 70 60 // 60 10 // 50 30//
        i++;
      }
      else {
        //boxxxx[k][0] = aa[j].w;
        //boxxxx[k][1] = aa[j].h;
        tmp.w = aa[j].w;
        tmp.h = aa[j].h;
        boxxxx.push_back(tmp);
        j++;
      }
    }
    long long int k;
    for (i = left, k=0; i <= right; i++, k++) {
        aa[i].w = boxxxx[k].w;
        aa[i].h = boxxxx[k].h;
    }
  }

  return cc;
}