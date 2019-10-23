#include <mpi.h> 
#include <stdio.h> 
#define n 12 
#define key 55

//input array
int a[] = { 1, 2, 3, 4, 5, 6, 7, 9, 13, 55, 56 ,90}; 

//temporary local array
int a2[1000];
		

int binarySearch(int* array, int start, int end, int value)	//start and end index as input
{
	int mid;
	while(start<=end)
	{
		mid = (start+end)/2;
		if(array[mid]==value)
			return mid;
		else if(array[mid]>value)
			end = mid-1;
		else
			start = mid+1;
	}
	return -1;
}

int main(int argc, char* argv[]) 
{ 

	int pid, np, 
		elements_per_process, 
		n_elements_received; 
	// np -> no. of processes 
	// pid -> process id 

	MPI_Status status; 

	// Creation of parallel processes 
	MPI_Init(&argc, &argv); 

	// find out process ID, 
	// and how many processes were started 
	MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
	MPI_Comm_size(MPI_COMM_WORLD, &np); 

	// master process 
	if (pid == 0) 
	{ 
		int index, i; 
		elements_per_process = n / np; 
		
		// check if more than 1 processes are run 
		if (np > 1)
		{ 
			// distributes the portion of array 
			// to child processes to 
      for (i = 1; i < np - 1; i++) 
			{ 
				index = i * elements_per_process; 

				//send element count
				MPI_Send(&elements_per_process, 
						1, MPI_INT, i, 0, 
						MPI_COMM_WORLD); 
					
				//send subarray
				MPI_Send(&a[index], 
						elements_per_process, 
						MPI_INT, i, 0, 
						MPI_COMM_WORLD); 
			} 

			// last process adds remaining elements 
			index = i * elements_per_process; 
			int elements_left = n - index; 

			MPI_Send(&elements_left, 
					1, MPI_INT, 
					i, 0, 
					MPI_COMM_WORLD); 

			MPI_Send(&a[index], 
					elements_left, 
					MPI_INT, i, 0, 
					MPI_COMM_WORLD); 
		} 


		// master process performs own searching 
		int position = binarySearch(a, 0, elements_per_process-1, key);
		
		if(position!=-1)
			printf("Found at:%d", position);

		int tmp; 
		//check positions found by others
		//-1 if not found in subarray
		for (i = 1; i < np; i++)
		{ 
			MPI_Recv(&tmp, 1, MPI_INT, 
					MPI_ANY_SOURCE, 0, 
					MPI_COMM_WORLD, 
					&status); 
			int sender = status.MPI_SOURCE; 
			
			if(tmp!=-1)
				printf("Found at:%d by %d", (sender*elements_per_process)+tmp, sender);
		} 


	} 

	// slave processes 
	else
	{ 
		
		//get number of elements
		MPI_Recv(&n_elements_received, 
				1, MPI_INT, 0, 0, 
				MPI_COMM_WORLD, 
				&status); 
		
		// stores the received array segment 
		// in local array a2 
		MPI_Recv(&a2, n_elements_received, 
				MPI_INT, 0, 0, 
				MPI_COMM_WORLD, 
				&status); 
		
		
		
		// calculates position 
		int position = binarySearch(a2, 0, n_elements_received-1, key);
		
		// sends the position to the root process 
		MPI_Send(&position, 1, MPI_INT, 
				0, 0, MPI_COMM_WORLD); 
	} 

	// cleans up all MPI state before exit of process 
	MPI_Finalize(); 

	return 0; 
} 
