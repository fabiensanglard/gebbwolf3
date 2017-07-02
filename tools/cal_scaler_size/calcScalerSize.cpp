#include <iostream>
#include <cstdio>
using namespace std;

size_t calcScaledSize(int s) {
    size_t size = 1;
    
    if (s <=64)
       size+= s*7;
    else {
    	if (s > 152)
    		s = 152;
        float ratio = s/64.0;
        size += 64*3 + s*4; 
    }   
    return size;
}

int main() {
    size_t total=0;
	size_t numScalers=0;
	// Fine grained, every even size.
	for (int i=1 ; i < 256 ; i++) {
	    total += calcScaledSize(i*2);
	    numScalers++;
	}
	printf("size %d (#scalers =%d)\n",total,numScalers);
	
	// With optimization where every 4s of size after size 76.
	total=0;
	numScalers=0;
	for (int i=1 ; i < 256 ; i++) {
	   
	    total += calcScaledSize(i*2);
	    numScalers++;
	     if (i > 76)
	       i+=2 ;
	}
	printf("size %d (#scalers =%d)\n",total,numScalers);
	
	return 0;
}


