#include <iostream>
#include <string>
#include <vector>

// #define DEBUG
using namespace std;

enum Dir{isLeft, isUp, isUpisLeft, isUporLeft, nope};

struct faaa {
  int d = 0;
  char c = '-';
  Dir r = nope;
};

int main()
{
  int times;
  cin >> times;
  while( times-- ){

    // Input String
    string s1n, s2n, s1, s2;
    cin >> s1n >> s2n;

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

    int current = 0;

    // LCS
    for( auto i = 1; i < s1.length(); i++) {
      for( auto j = 1; j < s2.length(); j++) {
        if( s1[i] == s2[j] ) {
          //cout << s1[i] << endl;
          table[i][j].d = table[i-1][j-1].d + 1;
          table[i][j].c = s2[j];
          table[i][j].r = isUpisLeft;
          ++ current;
        }
        /*
        else if( table[i-1][j].d == table[i][j-1].d ) {
          // cout << "compare " << "( " << table[i-1][j].c << " , )" << table[i][j-1].c << endl;
          table[i][j].d = table[i][j-1].d;
          if( table[i-1][j].c >= table[i][j-1].c ) {
            table[i][j].r = isLeft;
            table[i][j].c = table[i-1][j].c;
          }
          else {
            table[i][j].r = isUp;
            table[i][j].c = table[i][j-1].c;
          }
        }
        */
        else if( table[i-1][j].d >= table[i][j-1].d) {
          table[i][j].d = table[i-1][j].d;
          table[i][j].c = table[i-1][j].c;
          table[i][j].r = isUp;
        }
        else { //if( table[i-1][j].d < table[i][j-1].d ) {
          table[i][j].d = table[i][j-1].d;
          table[i][j].c = table[i][j-1].c;
          table[i][j].r = isLeft;
        }

        if( table[i-1][j].d == table[i][j-1].d && table[i][j].r != isUpisLeft) {
          if( table[i-1][j].c > table[i][j-1].c ) {
            table[i][j].r = isLeft;
            table[i][j].c = table[i][j-1].c;
          }
          else if( table[i-1][j].c < table[i][j-1].c ){
            table[i][j].r = isUp;
            table[i][j].c = table[i-1][j].c;
          }
          /*
          if( s1[i] > s2[j] ) {
            table[i][j].r = isUp;
          }
          else if( s1[i] < s2[j]) {
            table[i][j].r = isLeft;
          }
          */
        }
      }
    }

    // Debug
#ifdef DEBUG
    cout << " *";
    for( auto i = 1; i < s2.length(); i++)
      cout << " " << s2[i] << " |";
    cout << endl;
    for( auto i = 1; i < s1.length(); i++) {
      cout << s1[i] << ":";
      for( auto j = 1; j < s2.length(); j++) {
        if( table[i][j].d >= 10 )
          cout << table[i][j].d % 10 << table[i][j].c;
        else
          cout << table[i][j].d << table[i][j].c ;
        switch(table[i][j].r){
          case isLeft:
            cout << "←";
            break;
          case isUp:
            cout << "↑";
            break;
          case isUpisLeft:
            cout << "↖";
            break;
          case isUporLeft:
            cout << "↔";
            break;
          case nope:
            cout << "↛";
            break;
          default:
            cout << "↛";
            break;
        }
        cout << " ";
      }
      cout << endl;
    }
    cout << " ----- " << endl;
    cout << s1n << endl;
    cout << s2n << endl;
#endif
    // Print LCS
    int ii = s1.length() - 1,
        jj = s2.length() - 1;
    string answer;
        while( ii >= 1 && jj >= 1 ) {
          switch( table[ii][jj].r ){
            case isUp:
              ii = ii - 1;
              break;
            case isLeft:
              jj = jj - 1;
              break;
            case isUpisLeft:
              // cout << table [ii][jj].c << endl;
              // answer = answer + table[ii][jj].c;
              answer += s1[ii];
              ii = ii - 1;
              jj = jj - 1;
              break;
            case nope:
              ii = ii -1;
              jj = jj -1;
              break;
            default:
              cerr << "Error !" << endl;
              break;
          }
        }
    cout << answer << endl;

  }

}
