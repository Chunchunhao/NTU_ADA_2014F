#include <iostream>
#include <string>
#include <vector>

// #define DEBUG
using namespace std;

enum Dir{isLeft, isUp, isUpisLeft, isUporLeft, twoAns, nope};

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
    string s1n, s2n, tmp, s1, s2;
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
    int dup = 0; // to store the number of possible answer
    // LCS
    for( auto i = 1; i < s1.length(); i++) {
      for( auto j = 1; j < s2.length(); j++) {
        if( s1[i] == s2[j] ) {
          table[i][j].d = table[i-1][j-1].d + 1;
          table[i][j].c = s2[j];
          table[i][j].r = isUpisLeft;
        }
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
        // We need a better adjust
        if( table[i-1][j].d == table[i][j-1].d && table[i][j].r != isUpisLeft) {
          if( table[i-1][j].c > table[i][j-1].c ) {
            table[i][j].r = isLeft;
            table[i][j].c = table[i][j-1].c;
          }
          else if( table[i-1][j].c < table[i][j-1].c ){
            table[i][j].r = isUp;
            table[i][j].c = table[i-1][j].c;
          }
          else { // There 2 possible answer and optimization
            table[i][j].r = twoAns;
            table[i][j].c = table[i-1][j].c;
            if( table[i][j-1].r == isUp && table[i-1][j].r == isLeft )
              table[i][j].r = isUp;
            else if( i == 1 || j == 1 || table[i][j].d == 0)
              table[i][j].r = isUp;
            else if( table[i][j-1].r == isUp && table[i-1][j-1].r == isUp && table[i-1][j].r == twoAns)
              table[i][j].r = isUp;
            else if( table[i][j-1].r == twoAns && table[i-1][j-1].r == isLeft && table[i-1][j].r == isLeft)
              table[i][j].r = isLeft;
            else if( table[i][j-1].r == isUp && table[i-1][j-1].r == isUp && table[i-1][j].r == isUp)
              table[i][j].r = isUp;
            else if( table[i][j-1].r == isLeft && table[i-1][j-1].r == isLeft && table[i-1][j].r == isLeft)
              table[i][j].r = isLeft;
            else if( table[i][j-1].r == twoAns && table[i-1][j].r == isLeft)
              table[i][j].r = isLeft;
            else if( table[i][j-1].r == isUp && table[i-1][j].r == twoAns)
              table[i][j].r = isUp;
            else {
                int ii, jj, dd;
                int iiu, jju, iil, jjl;
                dd= table[i][j].d-1;
                // Left
                char llf, uup;

                iiu = i-1;
                jju = j;
                iil = i;
                jjl = j-1;
                FIGHTFIGHTAGAIN:
                ii = iiu; jj = jju;
                while( ii >= 1 && jj >= 1 && table[i][j].d > dd) {
                      //cout << "TB(LL): " << s1[i] << endl;
                      uup = s1[ii];
                      switch( table[ii][jj].r ){
                        case isUp:
                          ii = ii - 1;
                          break;
                        case isLeft:
                          jj = jj - 1;
                          break;
                        case isUpisLeft:
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
                iiu = ii; jju = jj;
                ii = iil; jj = jjl;
                while( ii >= 1 && jj >= 1 && table[i][j].d > dd) {
                      //cout << "TB(UU): " << s1[i] << endl;
                      llf = s1[ii];
                      switch( table[ii][jj].r ){
                        case isUp:
                          ii = ii - 1;
                          break;
                        case isLeft:
                          jj = jj - 1;
                          break;
                        case isUpisLeft:
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
                iil = ii; jjl = jj;
                if ( uup < llf )
                  table[i][j].r = isUp;
                else if ( uup > llf)
                  table[i][j].r = isLeft;
                else{
                  if( dd != 0 ){
                    --dd;
                    goto FIGHTFIGHTAGAIN;
                  }
                  else {
                    table[i][j].r = isUp;
                    //cout << "QQ : ";
                  }
                }
                //cout << "now : " << "(" << i << "," << j << ")" << " ll: " << llf << ", uu: " << uup << endl;
            }
          }
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
    cout << "s1: " << s1n << endl;
    cout << "s2: " << s2n << endl;
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
  return 0;
}
