#include <iostream>
#include <conio.h>
#include <string>
#include <chrono> 

using namespace std;
using namespace std::chrono;

int validateInput(int min, int max);
int sequentialSearch(int arr[], int key);
int binarySearch(int arr[], int size, int key);

int main() {
	const int size = 1000; // Enter array size here
	int *arr = new int[size]; // Allocate array size
	int n = sizeof(arr) / sizeof(arr[0]); 

	for (int i = 0; i <= size; i++) { // Insert integers (1-1000) in new array
		arr[i] = i + 1;
	}
	
	// Data validation here.
	int key = validateInput(1, 1000); // cout << typeid(key).name();

	// Search methods: 
	cout << "Sequential search..." << endl;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	sequentialSearch(arr, key);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(t2 - t1).count();
	cout << "Total searching time for sequential search: " << duration << " milliseconds" << endl;


	cout << "\nBinary search..." << endl;
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	binarySearch(arr, size, key);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	auto duration2 = duration_cast<milliseconds>(t4 - t3).count();
	cout << "Total searching time for binary search: " << duration2 << " milliseconds" << endl;

	_getch();
	return 0;
}

int validateInput(int min = 1, int max = 1000) { // Uses String to validate inputs, min, max being range of said input
	while (true) {
		cout << "Enter a number (1-1000): ";
		string s;
		getline(cin, s);
		char *endp = 0;
		int ret = strtol(s.c_str(), &endp, 10);
		if (endp != s.c_str() && !*endp && ret >= min && ret <= max)
			return ret;
		cout << "Invalid input. Allowed range: " << min << "-" << max << endl << endl;
	}
}

int sequentialSearch(int arr[], int key) { // Linear/sequential search
	int f = -1; // This will return if key not found, but this should never happen because of constraints

	for (int i = 0; i < 1000; i++) {
		if (arr[i] == key) {
			cout << "Key found at index: " << i << endl; 
			f = i;
			break;
		}
	}
	return f;
}

int binarySearch(int arr[], int size, int key) { // Iterative for comparison with sequential search 
	int low = 0; 
	int high = size - 1;

	while (low <= high) {
		int mid = (low + high) / 2; 
		if (key < arr[mid]) {
			high = mid - 1;
		} 
		else if (key > arr[mid]) {
			low = mid + 1;
		}
		else {
			cout << "Key found at index: " << mid << endl; // Can never find 1000, returns key not found.
			return arr[mid];
		}
	}
	cout << "Key not found." << endl;
	return -1;
}