#include <cstdio>
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

int main() {
  
  int tries;
  scanf("%d", &tries);
  if( tries == 0) { return 0; }
  while( tries-- ) {
    unsigned boxesN;
    // Read boxes to memory 
    scanf("%d", &boxesN);
    if( boxesN == 0) { 
      printf("0\n");
      continue; 
    }

    cubic *box = new cubic[boxesN];
    for( unsigned i=0; i < boxesN; i++) {
    	scanf("%d %d", &box[i].w, &box[i].h);
		if( box[i].w < box[i].h) {
        	unsigned tmp = box[i].h;
        	box[i].h = box[i].w;
        	box[i].w = tmp;
      	}
    }
    // Sort the Width 
    sort( &box[0], &box[boxesN], cmp);

 	// Do the DP
 	long long *inclu = new long long [boxesN];

 	long long total = 0;
 	inclu[boxesN-1] = 0;
 	// printf("now[%d] :( %d, %d): total: %d, this: %d \n", boxesN-1, box[boxesN-1].w, box[boxesN-1].h, total, inclu[boxesN-1]);
 	for( int i = boxesN-2; i >= 0; --i){
 		unsigned tmp = 0;
 		if( box[i].h >= box[i+1].h ){
 			int k = i+1;
 			while((box[i].w == box[k].w) && (box[i].h == box[k].h)){
 				total+=1;
 				if(k < boxesN)
 					k++;
 			}
 			tmp = box[i+1].h;
 			inclu[i] = inclu[i+1] + 1;
 			total += inclu[i];
 		}
 		else if( box[i].h < box[i+1].h ){
 			for( int j = i+2; j<boxesN; j++){
 				if( box[i].h > box[j].h && box[j].h > tmp){
 					//printf("::box[%d]: (%d, %d)_ ;; box[%d]: (%d, %d)\n ", i, box[i].w, box[i].h, j, box[j].w, box[j].h);
 					inclu[i] = inclu[j] + 1;
/***************************************************
	B U G
	不能break;
	eg: 
	1000 50 -- 4
	900 70 -- 5
	800 40 -- 1
	700 45 -- 1
	600 50 -- 1
	500 51 -- 1
	3 2 -- 0
	// should be 13
	*****************************************************/
 					// 這裡會有bug 可能會遇到更小的
 					
 					tmp = box[j].h;
 					total += inclu[i];
 					break;
 				}
 			}
 		}
 		for( k = i; k<boxesN; k++){
 			if()
 		}
 		//printf("now[%d] :( %d, %d): total: %d, this: %d \n", i, box[i].w, box[i].h, total, inclu[i]);
 	}

 	printf("%lld\n", total);
/*   long long count = 0;
    DC(box.begin(), box.end()-1, count);
    // DP and output
    cout << count << endl;
*/
  }
  return 0;
}

