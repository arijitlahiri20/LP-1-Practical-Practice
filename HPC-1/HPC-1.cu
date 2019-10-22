#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define N 2048
using namespace std;

__global__ void Max(int *a)
{
    int tid = threadIdx.x;
    int step_size = 1;
    int num_of_threads = blockDim.x;
    
    while(num_of_threads>0){
        if(tid<num_of_threads){
            int first = tid*step_size*2;
            int second = first+step_size;
            if(a[second]>a[first])
                a[first]=a[second];                  
        }
        step_size<<=1;
        num_of_threads>>=1;
    }
    
}
__global__ void Min(int *a)
{
    int tid = threadIdx.x;
    int step_size = 1;
    int num_of_threads = blockDim.x;
    
    while(num_of_threads>0){
        if(tid<num_of_threads){
            int first = tid*step_size*2;
            int second = first+step_size;
            if(a[second]<a[first])
                a[first]=a[second];                  
        }
        step_size<<=1;
        num_of_threads>>=1;
    }
}
__global__ void sum(int *a)
{
    int tid = threadIdx.x;
    int step_size = 1;
    int num_of_threads = blockDim.x;
    
    while(num_of_threads>0){
        if(tid<num_of_threads){
            int first = tid*step_size*2;
            int second = first+step_size;
            a[first]+=a[second];                  
        }
        step_size<<=1;
        num_of_threads>>=1;
    }
}
__global__ void mean_diff(float *a,float mean)
{
    a[threadIdx.x]-=mean;
    a[threadIdx.x]*=a[threadIdx.x];
    
}
__global__ void _std(float *a,int n)
{
    int tid = threadIdx.x;
    int step_size = 1;
    int num_of_threads = blockDim.x;
    
    while(num_of_threads>0){
        if(tid<num_of_threads){
            int first = tid*step_size*2;
            int second = first+step_size;
            a[first]+=a[second];                  
        }
        step_size<<=1;
        num_of_threads>>=1;
    }
    a[0]/=a[0]/n;
}

int main()
{
    int *a = (int *)malloc(N*sizeof(int));
    float *f = (float *)malloc(N*sizeof(float));
    //srand(time(0));
    for(int i=0;i<N;i++){
        a[i]=rand()%10;
        f[i]=float(a[i]);
    } 
    int *a_cuda;
    float *f_cuda;          
    int answer;
    
    cudaMalloc((void **)&a_cuda,N*sizeof(int));
   
    //MAX
    cudaMemcpy(a_cuda,a,N*sizeof(int),cudaMemcpyHostToDevice);
    Max<<<1,N/2>>>(a_cuda);
    cudaMemcpy(&answer,a_cuda,sizeof(int),cudaMemcpyDeviceToHost);
    cout<<"Max : "<<answer<<endl;
    
    //MIN
    cudaMemcpy(a_cuda,a,N*sizeof(int),cudaMemcpyHostToDevice);
    Min<<<1,N/2>>>(a_cuda);
    cudaMemcpy(&answer,a_cuda,sizeof(int),cudaMemcpyDeviceToHost);
    cout<<"Min : "<<answer<<endl;
    
    //SUM
    cudaMemcpy(a_cuda,a,N*sizeof(int),cudaMemcpyHostToDevice);
    sum<<<1,N/2>>>(a_cuda);
    cudaMemcpy(&answer,a_cuda,sizeof(int),cudaMemcpyDeviceToHost);
    cout<<"Sum : "<<answer<<endl;
    
    //MEAN
    float mean = float(answer)/N;
    cout<<"Mean : "<<mean<<endl;
              
    cudaFree(a_cuda);
    cudaMalloc((void **)&f_cuda,N*sizeof(float));
    float result;
    //STD
    cudaMemcpy(f_cuda,f,N*sizeof(float),cudaMemcpyHostToDevice);          
    mean_diff<<<1,N>>>(f_cuda,mean);        
    _std<<<1,N/2>>>(f_cuda,N);
    cudaMemcpy(&result,f_cuda,sizeof(float),cudaMemcpyDeviceToHost);
    cout<<"Variance : "<<result<<endl;
    cout<<"Std. Dev. : "<<sqrt(result)<<endl;
              
    cudaFree(f_cuda);    
    cout<<endl;
    return 0;          
}