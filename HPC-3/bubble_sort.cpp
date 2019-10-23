#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include <chrono>
#define N 100000
using namespace std;
using namespace std::chrono;

void p_bubble_sort(int *a)
{
    omp_set_num_threads(4);
   
    static int flag;
    for(int i=0;i<N-2;i++)
    {
        flag=0;
        if(i%2==0)
        {
            #pragma omp parallel for
            for(int j=0;j<N/2;j++)
            {
                if(a[2*j]>a[2*j+1])
                {
                    swap(a[2*j],a[2*j+1]);
                    flag=1;
                }
            }
        }
        else
        {
            #pragma omp pararllel for
            for(int j=0;j<(N-1)/2;j++)
            {
                if(a[2*j+1]>a[2*j+2])
                {
                    swap(a[2*j+1],a[2*j+2]);
                    flag=1;
                }
            }
        }
        if(flag==0)
            break;
    }
}

void bubble_sort(int *a)
{
    for(int i=0;i<N;i++)
    {
        //bool flag=true;
        for(int j=0;j<N-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                swap(a[i],a[j]);   
                //flag=false;
            }              
        }
        //if(flag)
            //break;
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
    cout<<"Serial Bubble Sort - "<<endl;
    auto start = high_resolution_clock::now(); 
    bubble_sort(a);
    auto stop = high_resolution_clock::now();
    cout<<"Time Taken : "<<duration_cast<milliseconds>(stop - start).count()<<"ms"<<endl<<endl;
    
    //Parallel Bubble Sort
    cout<<"Parallel Bubble Sort - "<<endl;
    start = high_resolution_clock::now(); 
    p_bubble_sort(p_a);
    stop = high_resolution_clock::now();
    cout<<"Time Taken : "<<duration_cast<milliseconds>(stop - start).count()<<"ms"<<endl;
    
    return 0;

}