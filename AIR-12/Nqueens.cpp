#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>

using namespace std;


int main(){
    int dimen, choice;
    sscanf(argv[1], "%d", &dimen);
    sscanf(argv[2], "%d", &choice);
    
    if(choice==1)
    	backtracking b(dimen);
    else if(choice==2)
    	branchnbound b(dimen);
    return 0;
}
