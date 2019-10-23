#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include <chrono>
#define N 1000000
using namespace std;
using namespace std::chrono;

void merge(int* array, int start, int mid, int end)
{
  int len = (end-start)+1;
  int temp[len];
  int cur=0;
  
  int i = start;
  int j = mid+1;
  while(i<=mid && j<=end){
    if(array[i]>array[j]){
      temp[cur] = array[i];
      cur++;
      i++;
    }
    else{
      temp[cur] = array[j];
      cur++;
      j++;
    }
  }
  if(i<=mid)  {
    while(i<=mid)    {
      temp[cur] = array[i];
      i++;
      cur++;
    }
  }
  else if(j<=end) {
    while(j<=end){
      temp[cur] = array[j];
      j++;
      cur++;
    }
  }
  cur=0;
  for(i=start; i<=end; i++){
    array[i] = temp[cur];
    cur++;
  }
}

void p_merge_sort(int *a,int l, int r)
{
    omp_set_num_threads(2);        
    if(l<r)
    {
      int mid = (l+r)/2;
      #pragma omp task firstprivate(a,l,mid,r)
      p_merge_sort(a, l, mid);

      #pragma omp task firstprivate(a,l,mid,r)
      p_merge_sort(a, mid+1, r);
      #pragma omp taskwait
       merge(a, l, mid, r); 
    }
}

void merge_sort(int *a,int l,int r)
{
    if(l<r)
    {
      int mid = (l+r)/2;
      merge_sort(a, l, mid);       
      merge_sort(a, mid+1, r);
      merge(a, l, mid, r); 
    }
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
    merge_sort(a,0,N-1);
    auto stop = high_resolution_clock::now();
    cout<<"Time Taken : "<<duration_cast<microseconds>(stop - start).count()<<" micro sec"<<endl<<endl;
    
    //Parallel Bubble Sort
    cout<<"Parallel Merge Sort - "<<endl;
    start = high_resolution_clock::now(); 
    p_merge_sort(p_a,0,N-1);
    stop = high_resolution_clock::now();
    cout<<"Time Taken : "<<duration_cast<microseconds>(stop - start).count()<<" micro sec"<<endl;
    
    return 0;

}