#include <iostream>
#include <vector>

typedef int[2] cubic;

using namespace std;

int main() {
  int n = 0;
  cin >> n;
  
  while( n -- ) {
    // Numbet of test Data
    int box_nu = 0;
    cin >> box_nu;
    vector<cubic> list[box_nu];

    // Read Input
    for(int i=0; i<box_nu; i++) {
      cin >> list[i][0] >> list[i][1];
    }
    // Process
    
    // Write Output
  };

  return 0;
}


