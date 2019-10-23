#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define N 10
using namespace std;

__global__ void addV(int *a,int *b,int *c)
{
    c[threadIdx.x] = a[threadIdx.x]+b[threadIdx.x];
    
}
__global__ void MulMatVec(int *a)
{
    
}
__global__ void MulMatMat(int *a)
{
    
}

int main()
{
    
      
    cout<<endl;
    return 0;          
}