#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include <sys/time.h>
#define N 100
using namespace std;

void p_merge_sort(int *a)
{
    omp_set_num_threads(N/2);
    
    
}

void merge_sort(int *a)
{
    
}

int main()
{
    int *a=(int*)malloc(N*sizeof(int));
    int *p_a=(int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++){
        a[i]=rand()%N;
        p_a[i]=a[i];
    }
    //Serial Bubble sort
    cout<<"Serial Merge Sort - "<<endl;
    auto start = high_resolution_clock::now(); 
    merge_sort(a);
    auto stop = high_resolution_clock::now();
    cout<<"Time Taken : "<<duration_cast<microseconds>(stop - start).count()<<endl<<endl;
    
    //Parallel Bubble Sort
    cout<<"Parallel Merge Sort - "<<endl;
    start = high_resolution_clock::now(); 
    p_merge_sort(p_a);
    stop = high_resolution_clock::now();
    cout<<"Time Taken : "<<duration_cast<microseconds>(stop - start).count()<<endl;
    
    return 0;

}