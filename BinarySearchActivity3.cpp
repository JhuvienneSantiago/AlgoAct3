#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

string logFileName = "bsearch_data.txt", message;
void generateArray(int arr[], int arrsize, int min, int max);
int binarySearch(const int arr[], int arrsize, int target, int &lr, int &rr, bool &dup);
void insertionSort(int arr[], int arrsize);
void displayArray(int arr[], int arrsize);
bool invalidInput();
void saveToFile(const string& message);
void saveArrayToFile(int arr[], int arrsize);

int main() {
    //Variable Delcaration for Array Generation
    int arrsize; //Size of array
    int minVal, maxVal; //Minimum and Maximum Value of Array

    //Variable Declaration for Binary Search
    int target, lr, rr; //Target value, Lower range and Upper Range for Duplicate target values
    bool dup = false; //Boolean if there is a duplicate value

    //Logs file name
    string logFileName = "bsearch_data.txt";

    //Prompt user for array size, minimum value, and maximum value;
    do{
        cout << "Input array size: ";
        cin >> arrsize;
        if(arrsize < 1){
            cout << "Array size must not be a letter, equal or below 0\n";
            continue;}
        cout << "Input minimum value: ";
        cin >> minVal;
        if(minVal < 0){
            cout << "Minimum value must not be a letter or below 0\n";
            continue;}
        cout << "Input maximum value: ";
        cin >> maxVal;
        if(maxVal < 0){
            cout << "Maximum value must not be a letter or below 0\n";
            continue;}
    } while (invalidInput() || arrsize < 1 || minVal < 0 || maxVal < 0); //Loops if user input is invalid.
    
    
    //Generate Array
    cout << "Generating Array...\n";
    int arr[arrsize]; //Array Initialization
    generateArray(arr, arrsize, minVal, maxVal); //Call Generate Array Function
    cout << "Array Generated!\n";
    saveArrayToFile(arr, arrsize);
    system("pause");
    system("cls");

    bool run = true, sorted = false;
    int choice;
    do{
        //User prompt for store menu.
        cout << "|-----------------------------------------------------------------\n";
        cout << "|======================== Decrease and Conquer ========================\n";
        cout << "|=========================== Binary Search ========================\n";
        cout << "|-----------------------------------------------------------------\n";
        cout << "|1. Display Array" << endl;
        cout << "|2. Sort Array" << endl;
        cout << "|3. Search for Value" << endl;
        cout << "|0. Exit" << endl;
        cout << "|Enter your choice: ";
        cin >> choice;
        if (invalidInput()) {
            system("cls");
            continue;
        }

        switch (choice){
            case 1:
                //Simply Displays the Array
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|======================== Display Array =========================\n";
       	        cout << "|-----------------------------------------------------------------\n\n";
                displayArray(arr, arrsize);
                system("pause");
                system("cls");
                break;
            case 2:
                //Sorts the array using insertion sort or quick sort
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|======================== Sort Array =========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "\nOriginal Array: \n";
                displayArray(arr, arrsize);
                cout << "\nSorting Array...\n";
                // sortArray(arr, 0, arrsize - 1); Sort using Quick Sort
                insertionSort(arr, arrsize); //Sort using Insertion Sort
                cout << "Array Sorted!\n\nNew Array:\n";
                saveArrayToFile(arr, arrsize);
                displayArray(arr, arrsize);
                cout << endl;
                sorted = true;
                system("pause");
                system("cls");
                break;
            case 3:{
                //Displays error if the user has not yet sorted the array using the previous function.
                if (!sorted) {
                    cout << "\nArray not yet sorted.\n";
                    system("pause");
                    system("cls");
                    break;
                }
                //Asks the user for a target value and utilizes binary search to search where the target value is indexed.
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|======================== Binary Search =========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                // Input the target value
                cout << "|Enter the target value to search for (" << minVal << " - " << maxVal << "): ";
                cin >> target;
                if (invalidInput()) {
                    system("cls");
                    continue;
                }
                system("cls");
                
                // Perform binary search
                message  = "Searching for value: " + to_string(target);
                saveToFile(message);
                int result = binarySearch(arr, arrsize, target, lr, rr, dup);
                
                // Output the result

                //Handles Duplicate Values. If there are duplicate values, displays each value and its index.
                if (dup == true){
                    message = "Duplicate Elements found.";
                    saveToFile(message);
                    cout << "Duplicate Elements found.\n";
                    for (int i = lr; i <= rr; i++){
                        message = "Element found at index: " + to_string(i);
                        saveToFile(message);
                        cout << "Element found at index: " << i << endl;
                    }
                //Displays the single result.
                } else if (result != -1 && dup == false) {
                    message = "Element found at index: " + to_string(result);
                    saveToFile(message);
                    cout << "Element found at index: " << result << endl;
                //Displays not found if value does not exist.
                } else {
                    message = "Element not found.";
                    saveToFile(message);
                    cout << "Element not found." << endl;
                }
                system("pause");
                system("cls");
                break;
            }
            case 0: 
                run = false;
                break;
            default:   
                //Shows invalid for invalid user input.
                cout << "Invalid input. Please try again.\n";
                system("pause");
                system("cls");
                break;
        }
    } while (run);
    return 0;
}

//Generates an array with random values.
void generateArray(int arr[], int arrsize, int min, int max) {
    //Seed the random number generator to generate different results each run.
    srand(time(nullptr)); 

    //Inserts a random number for each index of the array.
    for (int i = 0; i < arrsize; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

//Binary search Implementation
int binarySearch(const int arr[], int arrsize, int target, int &lr, int &rr, bool &dup) {
    int left = 0, right = arrsize - 1;
    int iteration = 1;

    while (left <= right) {
        // Calculate mid using the formula: mid = left + (right - left) / 2
        int mid = left + (right - left) / 2;

        // Display the simulation for this iteration
        cout << "Iteration " << iteration++ << ": \n";
        cout << "   Current range: [" << left << ", " << right << "]\n";
        cout << "   Mid calculation: mid = " << left << " + (" << right << " - " << left << ") / 2 = " << mid << "\n";
        cout << "   Value at mid: arr[" << mid << "] = " << arr[mid] << "\n";

        // Check if the target is found
        if (arr[mid] == target) {
        	lr = mid, rr = mid; //Left range and Right range;

            //Checks for duplicates. Iterates each values from the left of the found value to check matching duplicate values and store the lower range.
        	if (arr[lr-1] != target && arr[rr+1] != target) dup = false;
            while (lr - 1 >= 0){
        		if (arr[lr-1] == target){
        			lr--;
        			dup = true;
				}
				if (arr[lr-1] != target) break;
			}
            //Iterates each values to the right of the found value to check matching duplicate values and store the upper range.
			while (rr + 1 < arrsize){
        		if (arr[rr+1] == target){
        			rr++;
        			dup = true;
				}
				if (arr[rr+1] != target) break;
			}
            //If duplicate is true. Displays the range of the indices of the duplicate values.
			if (dup){
				cout << "   Duplicate values found at indices range " << lr << " to " << rr << ".\n\n";
				return mid;
			}
            //Displays single target value.
			else{
				cout << "   Target found at index " << mid << ".\n\n";
            	return mid;
			}
        } else if (arr[mid] < target) { //If the target value is greater than array, split the array in two and get the new left range.
            cout << "   Target is greater than arr[" << mid << "]. Adjusting left to " << mid + 1 << ".\n\n";
            left = mid + 1;
        } else { //If the target value is greater than array, split the array in two and get the new right range.
            cout << "   Target is less than arr[" << mid << "]. Adjusting right to " << mid - 1 << ".\n\n";
            right = mid - 1;
        }
    }
    //Display Target not found if not found.
    cout << "Target not found in the array.\n";
    return -1; // Target not found
}

//Insertion Sort Decrease and Conquer Implementation to sort the array
void insertionSort(int arr[], int arrsize) {
    for (int i = 1; i < arrsize; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key to one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

//Function to display array via traversing
void displayArray(int arr[], int arrsize){
    for (int i = 0; i < arrsize; ++i) cout << arr[i] << " ";
    cout << endl;
}

//Checks input if the user inputs a different data type, cin will fail and the system will remove each character and return true
bool invalidInput(){
    if (cin.fail()){
        cin.clear();
        char c;
        while (cin.get(c) && c != '\n')
        ;
        cout << "Invalid input. Please try again.\n";
        system("pause");
        return true;
    }
    return false;
}

//Saves changes to file after sorting/buying
void saveToFile(const string& message) {
    ofstream outFile(logFileName, ios::app);
    if (!outFile) {
        cerr << "Failed to open file for saving: " << logFileName << endl;
        return;
    }
    outFile << message << endl;
    outFile.close();
}

void saveArrayToFile(int arr[], int arrsize) {
    ofstream outFile(logFileName, ios::app);
    if (!outFile) {
        cerr << "Failed to open file for saving: " << logFileName << endl;
        return;
    }
    outFile << "New Array:\n";
    for (int i = 0; i < arrsize; ++i) outFile << arr[i] << " ";
    outFile << endl;
    outFile.close();
    cout << "Array has been saved to file.\n";
}