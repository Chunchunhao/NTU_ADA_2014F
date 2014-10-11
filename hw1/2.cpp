#include <iostream>
#include <vector>

struct block {
  int owner;
  int cash;
};

struct player {
  int goal;
  int cash;
  int suc;
};

using namespace std;

int main() {
  int tries = 0;
  cin >> tries;
  
  while( tries-- ) {
    // Numbet of test Data
    int plr, blk, evt;
    cin >> plr >> blk >> evt;
    vector<block> mine;
    mine.resize(blk);
    vector<player> miner;
    miner.resize(plr);
  
    // Goal
    for( int i=0; i<plr; i++){
      cin >> miner[i].goal;
      miner[i].cash = 0;
      miner[i].suc = 0;
    }

    // Ownership
    for( int i=0; i<blk; i++){
      cin >> mine[i].owner;
      mine[i].cash = 0;
    }

    // Event
    while( evt-- ) {
      cout << "evt: " << evt << endl;
      int bg, ed, mny;
      cin >> bg >> ed >> mny;
      mine[bg-1].cash += mny;
      if( ed < mine.size() )
        mine[ed].cash -= mny;
      cout << "evt: " << evt << " :: " << bg << " , " << ed << " , " << mine.size() << endl;
    }
     
    int mnyItr = 0;
    for( int i=0; i<blk; i++) {
      cout << "Mine : ( " << mine[i].owner << ", " << mine[i].cash <<" )" << endl;
      cout << "ptr : " << mnyItr << endl;
      cout << "ply : [[ ";
      for( int j=0; j<plr; j++) {
        cout << miner[j].cash << " ";
      }
      cout << " ]]" << endl;
      mnyItr += mine[i].cash;
      miner[mine[i].owner-1].cash += mnyItr;
    }

    for( int i=0; i<plr; i++) {
      if( miner[i].cash >= miner[i].goal )
        cout << miner[i].cash;
      else
        cout << "-1";
      if( i!= plr -1 )
        cout << " ";
    }
    cout << endl;

  };

  return 0;
}


