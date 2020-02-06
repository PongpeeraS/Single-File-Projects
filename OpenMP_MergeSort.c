#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r);
void mergeSort(int arr[], int l, int r, int num_threads);

int main(){
	int size, i, num_threads;
	double startTime, endTime;
	
	/*Input phase: input array size (also the max value to randomize) & amount of threads to use*/
	printf("Input the amount of elements to randomize: ");
	scanf("%d", &size);
	printf("Input the amount of threads to use: ");
	scanf("%d", &num_threads);
	
	/*Initializing array to sort using random values*/
	int arr[size];
	srand(1234);
	for (i=0; i<size; i++){
		arr[i] = rand()%size;
	}
	printf("Unsorted array:\n");
	for (i=0; i<size; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");

	/*Start the merge sort process, time used by the process is recorded*/
	startTime = omp_get_wtime();
	mergeSort(arr,0,size-1, num_threads);
	endTime = omp_get_wtime();
	
	/*Display sorted array and time used*/
	printf("Sorted array:\n");
	for (i=0; i<size; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("Time to execute in parallel: %f\n\n", endTime-startTime);

	return 0;
}

/*Function to divide the array to sort*/
void mergeSort(int arr[], int l, int r, int nThreads){
	if(l<r){
		/*Calculating number of threads to split between 2 sections*/
		int m=(l+r)/2; //Calculating the middle value between 2 sections
		/*Dividing the array through recursion, OpenMP is used to separate them into sections*/
		#pragma omp parallel sections num_threads(nThreads)
		{
			#pragma omp section 
			{
				mergeSort(arr,l,m,nThreads/2);
			}
			#pragma omp section
			{
				mergeSort(arr,m+1,r,nThreads/2);
			}
		}
		merge(arr,l,m,r); //This function is outside the parallel sections since it merges and accesses the same data
	}
}

/*Function to sort & merge parts of the split array*/
void merge(int a[], int l, int m, int r){
	int i, j, k;
	int size1 = m-l+1, size2 = r-m;
	int temp1[size1], temp2[size2];
	/*Put the main array pointers into 2 temp arrays for easier operation*/
	for(i=0; i<size1; i++) //Copy first part to temporary array
		temp1[i]=a[l+i];
	for(i=0; i<size2; i++) //Copy second part to temporary array
		temp2[i]=a[m+1+i];
	i=0; j=0; k=l;
	/*Combine the arrays on the basis of order*/
	while(i<size1 && j<size2){
		if(temp1[i]<temp2[j])
			a[k++]=temp1[i++];
		else
			a[k++]=temp2[j++];
	}
	/*Combine the remainder of the two arrays*/
	while(i<size1)
		a[k++]=temp1[i++];
	while(j<size2)
		a[k++]=temp2[j++];
}
