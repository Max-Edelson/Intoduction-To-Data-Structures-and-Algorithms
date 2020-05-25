#include <chrono> 
#include <iostream>
#include <time.h>

using namespace std;
using namespace chrono;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b; 
	*b = temp;
}

void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
		cout << endl;
}


int partition_midpoint(int arr[], int low, int high) {
	int pivot = arr[(low + high) / 2];
	swap(&arr[(low + high) / 2], &arr[high]);
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
//		printArray(arr, 6);
		if (arr[j] < pivot) {		//if current element is smaller than the pivot
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap (&arr[i + 1], &arr[high]);

//	printArray(arr, 6);

	return (i + 1);
}

void Quicksort_midpoint(int numbers[], int low, int high) {
	if (low < high) {
		int pivot = partition_midpoint(numbers, low, high);
		Quicksort_midpoint(numbers, low, pivot - 1);
		Quicksort_midpoint(numbers, pivot + 1, high);
	}
}

int partition_median(int arr[], int low, int high) {

	int center = (low + high) / 2;

	if (arr[center] < arr[low])
		swap(&arr[center], &arr[low]);
	if (arr[high] < arr[low])
		swap(&arr[high], &arr[low]);
	if (arr[high] < arr[center])
		swap(&arr[center], &arr[high]);

	swap(&arr[center], &arr[high]);

        int pivot = arr[high]; 
        int i = (low - 1); 

        for (int j = low; j <= high - 1; j++) {
//               printArray(arr, 6); 
                if (arr[j] < pivot) {           //if current element is smaller than the pivot
                        i++;
                        swap(&arr[i], &arr[j]);
                }   
        }   
        swap (&arr[i + 1], &arr[high]);

  //      printArray(arr, 6); 

        return (i + 1); 
}

void Quicksort_medianOfThree(int numbers[], int low, int high) {
        if (low < high) {
                int pivot = partition_median(numbers, low, high);
                Quicksort_medianOfThree(numbers, low, pivot - 1); 
                Quicksort_medianOfThree(numbers, pivot + 1, high);
        }   
}

void InsertionSort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		swap(&arr[i], &arr[min]);
	}
}

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int main() {
	int arr1[50000];
	int arr2[50000];
	int arr3[50000];

	int arr[] = {10, 7, 8, 9, 1, 5};
	
	fillArrays(arr1, arr2, arr3);

	int start = clock();
	Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
	int stop = clock();

	int time = (stop - start);
	time /= 1000;
	cout << "duration of quicksort using midpoint as pivot: " << time << " milliseconds" << endl;

	start = clock();
	Quicksort_medianOfThree(arr, 0, NUMBERS_SIZE - 1); 
        stop = clock();

        time = (stop - start);
        time /= 1000;
        cout << "duration of quicksort using median as pivot: " << time << " milliseconds" << endl;

	start = clock();
        InsertionSort(arr, NUMBERS_SIZE);
        stop = clock();
 
        time = (stop - start);
        time /= 1000;
	cout << "duration of insertion sort: " << time << " milliseconds" << endl;
}
