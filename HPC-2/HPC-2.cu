#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define N 4
#define t_per_block 2
using namespace std;

void random_ints(int *vec, int size){
    for(int i=0; i<size; i++)
        vec[i] = i;
}

void random_ints_mat(int *mat, int size){
    int k=0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            mat[i*size+j] = k++;
        }
    }
}

__global__ void addV(int *a,int *b,int *c)
{
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    c[index] = a[index]+b[index];   
}
__global__ void MulMatVec(int *vec,int *mat,int *out_vec, int n)
{
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=vec[i]*mat[(i*n)+index];
    out_vec[index] = sum;
    
}
__global__ void MulMatMat(int *a, int *b, int *c, int n)
{
    int row_index = threadIdx.y + blockIdx.y * blockDim.y;
    int col_index = threadIdx.x + blockIdx.x * blockDim.x;
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=a[(row_index*n)+i] * b[(i*n)+col_index];
    c[row_index*n + col_index]=sum;
}

int main()
{
    // ----------- Vector Addition ----------------
    int *a, *b, *c; //Vectors on host
    int *d_a, *d_b, *d_c; //Vectors on device
    int v_size = N*sizeof(int);
    
    a = (int *)malloc(v_size);
    b = (int *)malloc(v_size);
    c = (int *)malloc(v_size);
    
    cudaMalloc((void **)&d_a, v_size);
    cudaMalloc((void **)&d_b, v_size);
    cudaMalloc((void **)&d_c, v_size);
    
    random_ints(a,N);
    random_ints(b,N);
    
    cudaMemcpy(d_a, a, v_size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, v_size, cudaMemcpyHostToDevice);
    
    addV<<<N/t_per_block, t_per_block>>>(d_a, d_b, d_c);
    
    cudaMemcpy(c, d_c, v_size, cudaMemcpyDeviceToHost);
   
    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c); 
    free(a); free(b); free(c); 
    
    
    // ----------- Vector Matrix Multiplication ----------- 
    int *vec, *mat, *out_vec;
    vec = (int *)malloc(N*sizeof(int));
    mat = (int *)malloc(N*N*sizeof(int));
    out_vec = (int *)malloc(N*sizeof(int));
    
    int *d_vec, *d_mat, *d_out_vec;
    cudaMalloc((void **)&d_vec, N*sizeof(int));
    cudaMalloc((void **)&d_mat, N*N*sizeof(int));
    cudaMalloc((void **)&d_out_vec, N*sizeof(int));
    
    random_ints(vec, N);
    random_ints(mat, N*N);
    
    cudaMemcpy(d_vec, vec, N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_mat, mat, N*N*sizeof(int), cudaMemcpyHostToDevice);
    
    MulMatVec<<<N/t_per_block, t_per_block>>>(d_vec, d_mat, d_out_vec, N);
    
    cudaMemcpy(out_vec, d_out_vec, N*sizeof(int), cudaMemcpyDeviceToHost);
  
    cudaFree(d_vec); cudaFree(d_mat); cudaFree(d_out_vec); 
    free(vec); free(mat); free(out_vec); 

    // ----------- Matrix Multiplication ----------- 
    int *mat_a, *mat_b, *mat_c;
    int *d_mat_a, *d_mat_b, *d_mat_c;
    
    mat_a = (int *)malloc(N*N*sizeof(int));
    mat_b = (int *)malloc(N*N*sizeof(int));
    mat_c = (int *)malloc(N*N*sizeof(int));

    cudaMalloc((void **)&d_mat_a, N*N*sizeof(int));
    cudaMalloc((void **)&d_mat_b, N*N*sizeof(int));
    cudaMalloc((void **)&d_mat_c, N*N*sizeof(int));
    
    random_ints_mat(mat_a, N);
    random_ints_mat(mat_b, N);
    
    cudaMemcpy(d_mat_a, mat_a, N*N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_mat_b, mat_b, N*N*sizeof(int), cudaMemcpyHostToDevice);
    
    dim3 threadsPerBlock(2,2);
    dim3 blocksPerGrid(N/threadsPerBlock.x,N/threadsPerBlock.y);
    
    MulMatMat<<<blocksPerGrid,threadsPerBlock>>>(d_mat_a, d_mat_b, d_mat_c, N);
    
    cudaMemcpy(mat_c, d_mat_c, N*N*sizeof(int), cudaMemcpyDeviceToHost);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d ", mat_c[i*N + j]);
        }
        printf("\\n");
    }
    
    cudaFree(d_mat_a); cudaFree(d_mat_b); cudaFree(d_mat_c); 
    free(mat_a); free(mat_b); free(mat_c);     
    
    return 0;       
}