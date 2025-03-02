#include<iostream>
#include<vector>
#include<ctime>
#include<fstream>
#include<sstream>
using namespace std;

struct Item {
    int id;
    int quantity;
};

//added bool and if condition for showing original and final sorted array to remove step 0
void printStep(const vector<Item>& items, int step, bool showStepLabel = true) {
    if (showStepLabel) {
        cout << "Step " << step << ": ";
    }
    for (const auto& item : items) {
        cout << "(" << item.id << ", " << item.quantity << ") ";
    }
    cout << endl;
}


void printResult(ofstream& outFile, const vector<Item>& items) {
        outFile << "ID, Quantity" << endl;
    for (const auto& item : items) {
        outFile << item.id << ", " << item.quantity << "\n" ;
    }
}

//made it so that it only shows before and after, not the whole process
void insertionSort(vector<Item>& items) {
    int n = items.size();
    for (int i = 1; i < n; i++) {
        Item key = items[i];
        int j = i - 1;
        
        // what is being inserted
        cout << "\nPass " << i << " - Key: (" << key.id << ", " << key.quantity << ")\n";

        cout << "Before sorting - ";
        printStep(items, i);

        while (j >= 0 && items[j].id > key.id) { 
            items[j + 1] = items[j];
            j--;
        }
        items[j + 1] = key;
        
        cout << "After sorting - ";
        printStep(items, i);
    }
}

//Randomizer
vector<Item> RandThings(int N) {
    vector<Item> items(N);
    srand(time(0));
    for (int i = 0; i < N; i++) {
        items[i].id = rand() % 100 + 1;
        items[i].quantity = rand() % 50 + 1;
    }
    return items;
}

int main() {
   int N;
    const int MAX_ITEMS = 90; // Set a reasonable upper limit

    cout << "----- Act 3 - Group [7] Insert Sort Program! -------\n";

    while (true) {
        string input;
        cout << "Enter number of items: ";
        getline(cin, input);

        stringstream ss(input);
        if (ss >> N && N > 0 && N <= MAX_ITEMS && ss.eof()) {
            break;
        } else {
            cout << "Invalid! Please enter a positive integer less than or equal to " << MAX_ITEMS << ": ";
        }
    }

    vector<Item> Inventory = RandThings(N);
    
    cout << "\nOriginal Array:" << endl;
    printStep(Inventory, 0, false);
    
    // Sort the inventory by item id
    insertionSort(Inventory);

    // Display the sorted inventory
    cout << "\nSorted Inventory:" << endl;
    printStep(Inventory, 0, false);

    // Check if file exists
    ifstream checkFile("sorted_inventory.txt");
    bool fileExists = checkFile.good();
    checkFile.close();

    ofstream outFile("sorted_inventory.txt");

    //file handling stuff
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    if (!fileExists){
        cout << "File 'sorted_inventory.txt' does not exist! Creating it for you... " << endl;
    }
    
    printResult(outFile, Inventory);
    outFile.close();
    cout << "Sorted results have been written to sorted_inventory.txt" << endl;
    cout << "Thank you for using our Insert Sort Program!";

    return 0;
}

