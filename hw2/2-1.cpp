#include <iostream>
#include <string>
#include <vector>
#include <cctype>
// #define DEBUG
using namespace std;

struct faaa {
  int d = 0;
  char c = '-';
};

int main()
{
  int times;
  cin >> times;
  while( times-- ){

    // Input String
    string s1n, s2n, tmp, s1, s2;
    cin >> s1n >> s2n;

    // Inverse to get Dictionary order
    for( char &c: s1n )
      s1 = c + s1;
    s1 = ' ' + s1;
    for( char &c: s2n )
      s2 = c + s2;
    s2 = ' ' + s2;

    // Amazing memo
    vector< vector< faaa > > table;
    table.resize(s1.length());
    for( auto i = 0; i < table.size(); i++)
      table[i].resize(s2.length());

    // LCS
    for( auto i = 1; i < s1.length(); i++) {
      for( auto j = 1; j < s2.length(); j++) {
        if( s1[i] == s2[j] ) {
          table[i][j].d = table[i-1][j-1].d + 1;
          table[i][j].c = '+';
        }
        else if( table[i-1][j].d > table[i][j-1].d) {
          table[i][j].d = table[i-1][j].d;
          // table[i][j].c = table[i-1][j].c;
        }
        else {
          table[i][j].d = table[i][j-1].d;
          // table[i][j].c = table[i][j-1].c;
        }
      }
    }

    // Debug
#ifdef DEBUG
    cout << s1.length();
    for( auto i = 1; i < s2.length(); i++)
      cout << " " << s2[i] << " |";
    cout << " " << s2.length() << endl;
    for( auto i = 1; i < s1.length(); i++) {
      cout << s1[i] << ":";
      for( auto j = 1; j < s2.length(); j++) {
        if( table[i][j].d >= 10 )
          cout << table[i][j].d % 10 << s1[i] << table[i][j].c;
        else
          cout << table[i][j].d << s1[i] << table[i][j].c;
        cout << " ";
      }
      cout << endl;
    }
    cout << " ----- " << endl;
    cout << "s1: " << s1n << endl;
    cout << "s2: " << s2n << endl;
#endif

    // Find and Print
    int ii = s1.length() - 1,
        jj = s2.length() - 1;
    int lscLength = table[ii][jj].d;
    int nowD = table[ii][jj].d;
    string answer;
    while( nowD >= 1 ) {
      int tmpi = ii, tmpj = jj;
      char winC = 'z' + 1;
      for( auto i = ii; i >= 1; i -- ) {
        for( auto j = jj; j >= 1; j --) {
          // cout << "(" << i << "," << j << ") : " << table[i][j].d << " " << table[i][j].c << "|| D: " << nowD << endl;
          if( table[i][j].d == nowD && table[i][j].c == '+') {
            if(  s1[i] < winC ){
              winC = s1[i];
              tmpi = i; tmpj = j;
            }
          }
          else if ( table[i][j].d != nowD)
            break;
        }
      }
      answer += winC;
      ii = tmpi - 1;
      jj = tmpj - 1;
      --nowD;
    }


    cout << answer << endl;
  }
  return 0;
}
