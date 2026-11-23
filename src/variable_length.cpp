// Student Record Management System

#include <iostream>
#include <fstream> // For I/O operations
#include <string> // To use the string type
#include <vector> // To declare the avail list
#include <map> // To create a  primary index
#include <unordered_map> // To create a Secondary index
#include <cstdlib> // To use sort method
#include <sstream>
#include <iomanip>


using namespace std;

const int maxrow = 50; // Maximum number of records
int deletedRecords = 0;
map<int, int> primaryIndex; // Maps ID to the index in the records array
unordered_map<string, vector<int>> secondaryIndex; // Maps ID to the index in the records array


struct Record {
    int id;          // 4 bytes
    int score;       // 4 bytes
    string name;     // Variable length
    string DofB;     // Variable length
    bool isDeleted;  //Checks is the record deleted or not
};

// Arrays to store data
Record records[maxrow]; // Array to store records
vector<int>availList; // Creation of the avail list
int recordCount = 0;

void searchUsingSecondaryIndex(const string& name) {
    cout << "Searching for Record by Name: " << name << endl;
    cout << "===========================================" << endl;
    cout << "No       ID       Name        Score       Date of Birth" << endl;
    cout << "--------------------------------------------------------" << endl;

    if (secondaryIndex.find(name) != secondaryIndex.end()) {
        for (int idx : secondaryIndex[name]) {
            if (!records[idx].isDeleted) {
                cout << idx + 1 << "       " << records[idx].id << "       "
                     << records[idx].name << "       " << records[idx].score << "       "
                     << records[idx].DofB << endl;
            }
        }
    } else {
        cout << "No records found!" << endl;
    }
}




// Used to update primary index after addiction ,updating and deletion
void updatePrimaryIndex(Record records[], int recordCount) {
    primaryIndex.clear(); // Clear the existing index
    for (int i = 0; i < recordCount; i++) {
        primaryIndex[records[i].id] = i; // Map ID to the position in the array
    }
}

// Initialize records
void initializeRecords() {
    recordCount = 0; // Reset record count to 0 at the beginning
    availList.clear();
}
// Display free IDs from the availList
void showFreeIDs() {
    if (availList.empty()) {
        cout << "No free IDs available." << endl;
        return;
    }

    cout << "Free IDs available for reuse: ";
    for (size_t i = 0; i < availList.size(); i++) {
        cout << records[availList[i]].id; // Fetch the ID from the record at that index
        if (i < availList.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}


// Add a record
void addRecord() {

    Record newRecord;
 if (recordCount >= maxrow && deletedRecords == 0) {
        cout << "Error: No space to add new record" << endl;
        return;
    }
    cout << "Enter ID number: ";
    cin >> newRecord.id;
     // Check for duplicate ID
    for (int i = 0; i < recordCount; i++) {
        if (!records[i].isDeleted && records[i].id == newRecord.id) {
            cout << "Error: ID " << newRecord.id << " already exists. Please use a unique ID." << endl;
            showFreeIDs();
            return; // Exit the function to prevent adding a duplicate
        }
    }

    cout << "Enter name: ";
    cin.ignore();  // To clear the input buffer
    getline(cin, newRecord.name);

    cout << "Enter score: ";
    cin >> newRecord.score;

    cout << "Enter date of birth (in the form dd/mm/yyyy): ";
    cin.ignore();  // To clear the input buffer
    getline(cin, newRecord.DofB);

    newRecord.isDeleted = false ; // Marks the record as active(not deleted)
    // Checks if the avail list empty or not
    if(!availList.empty())
    {
        int reuseIndex = availList.back();
        availList.pop_back();
        records[reuseIndex] = newRecord;
        cout << "Record added at reused position " << reuseIndex + 1 << endl;
        deletedRecords -- ;
        // Update the primary index
           updatePrimaryIndex(records, recordCount);
           // Update the secondary index by adding the name
    secondaryIndex[newRecord.name].push_back(recordCount - 1);
    }

    else {
         records[recordCount] = newRecord;
    recordCount++;
    // Update the primary index
           updatePrimaryIndex(records, recordCount);
           // Update the secondary index by adding the name
    secondaryIndex[newRecord.name].push_back(recordCount - 1);



    cout<<"Record stored successfully"<<endl;

}

    }



// Display all records
void displayRecords() {
    cout << "Current Records" << endl;
    cout << "======================================" << endl;
    cout << left << setw(10) << "No"<< setw(10) << "ID"<< setw(20) << "Name"<< setw(10) << "Score" << setw(15) << "Date of Birth" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < recordCount; i++) {
        if(!records[i].isDeleted){
        cout << i + 1 << "       " << records[i].id << "       " << records[i].name
             << "       " << records[i].score << "       " << records[i].DofB << endl;
             }

    }

    if (recordCount == 0 || (recordCount == deletedRecords && availList.empty())) {
        cout << "No records found!" << endl;
    }
}

// Search for record by ID (Sequential search)
void searchRecords(int searchID) {
    cout << "Searching for Record..." << endl;
    cout << "===========================================" << endl;
    cout << "No       ID       Name        Score       Date of Birth" << endl;
    cout << "--------------------------------------------------------" << endl;

    bool found = false;
    for (int i = 0; i < recordCount; i++) {
        if (!records[i].isDeleted && records[i].id == searchID) {
            cout << i + 1 << "       " << records[i].id << "       " << records[i].name
                 << "       " << records[i].score << "       " << records[i].DofB << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No records found!" << endl;
    }
}

// Update Record
void updateRecord(int searchID) {
    for (int i = 0; i < recordCount; i++) {
        if (!records[i].isDeleted && records[i].id == searchID) {

            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, records[i].name);

            cout << "Enter new score: ";
            cin >> records[i].score;

            cout << "Enter new date of birth (in the form dd/mm/yyyy): ";
            cin.ignore();
            getline(cin, records[i].DofB);
             // Update the primary index
            updatePrimaryIndex(records, recordCount);
           // Update the secondary index by adding the name
            secondaryIndex[records[i].name].push_back(recordCount - 1);
            cout << "Record updated successfully!" << endl;
            return;
        }
    }

    cout << "ID does not exist!" << endl;
}

// Delete Record
void deleteRecord(int searchID) {
    for (int i = 0; i < recordCount; i++) {
        if (!records[i].isDeleted && records[i].id == searchID) {
            records[i].isDeleted = true;
            availList.push_back(i);
            // Update the primary index
           updatePrimaryIndex(records, recordCount);
           // Update the secondary index by adding the name
           secondaryIndex[records[i].name].push_back(recordCount - 1);
            cout<<"Record deleted successfully";
            deletedRecords++;

                return;
        }
    }
    cout << "ID doesn't exist!" << endl;
}

// Save records to a file
void saveRecordsToFile(const string &filename) {
    ofstream myFile(filename, ios::out);
    if (!myFile) {
        cerr << "Error: Could not open file '" << filename << "'" << endl;
        return;
    }

    for (int i = 0; i < recordCount; i++) {
            if(!records[i].isDeleted){
        myFile << records[i].id << ","
               << records[i].name << ","
               << records[i].score << ","
               << records[i].DofB << endl;
               }
    }


    myFile.close();
    cout << "Records saved successfully!" << endl;
}

// Load records from a file
void loadFromFile(const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    recordCount = 0;
    availList.clear();

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, score, name, DofB;

        // Extract fields separated by commas
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, score, ',');
        getline(ss, DofB, ',');

        // Assign parsed values to the Record structure
        records[recordCount].id = stoi(id);
        records[recordCount].score = stoi(score);
        records[recordCount].name = name;
        records[recordCount].DofB = DofB;
        records[recordCount].isDeleted = false;

        recordCount++;
    }

    inFile.close();
    cout << "Records loaded successfully from " << filename << endl;
}


// Searching using primary index
void searchUsingPrimaryIndex(Record records[], int searchID) {
    if (primaryIndex.find(searchID) != primaryIndex.end()) {
        int position = primaryIndex[searchID];
        cout << "Record Found!" << endl;
        cout << "ID: " << records[position].id << endl;
        cout << "Name: " << records[position].name << endl;
        cout << "Score: " << records[position].score << endl;
        cout << "Date of Birth: " << records[position].DofB << endl;
    } else {
        cout << "Record not found!" << endl;
    }
}


int main() {
    string filename = "data/users6.txt";
    loadFromFile(filename);  // Load records from file at the start
     // Update the primary index
           updatePrimaryIndex(records, recordCount);
    // Update the secondary index by adding the name
          secondaryIndex[records[recordCount - 1].name].push_back(recordCount - 1);


    int option;
    int searchID;
    string name;

    do {
        // Display menu options
        cout << "\nMenu\n";
        cout << "1 - Create Record" << endl;
        cout << "2 - Update Record" << endl;
        cout << "3 - Delete Record" << endl;
        cout << "4 - Search Record (Sequential search) " << endl;
        cout << "5 - Search Record (Primary index)" << endl;
        cout << "6 - Search Record (Secondary index)" << endl;
        cout << "7 - Display All Records" << endl;
        cout << "8 - Exit and Save" << endl;
        cout << "----------------------------" << endl;

        cout << "Select Option: ";
        cin >> option;

        // Switch statement for menu options
        switch (option) {
        case 1:
            addRecord();
            break;

        case 2:
            cout << "Enter the ID: ";
            cin >> searchID;
            updateRecord(searchID);
            break;

        case 3:
            cout << "Enter the ID you want to delete: ";
            cin >> searchID;
            deleteRecord(searchID);
            break;

        case 4:
            cout << "Enter the ID you want to search: ";
            cin >> searchID;
            searchRecords(searchID);
            break;
        case 5:
            cout << "Enter the ID you want to search(Primary Index): ";
            cin >> searchID;
            // Sort the records by ID
            //sortRecordsById(records , recordCount);
            searchUsingPrimaryIndex(records, searchID);
            break;

        case 6:
            cout << "Enter the name you want to search(Secondary Index): ";
            cin.ignore();  // To clear the input buffer
            getline(cin, name);
            searchUsingSecondaryIndex(name);
            break;


        case 7:
            displayRecords();
            break;

        case 8:
            saveRecordsToFile(filename);
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid option! Please try again." << endl;
        }
    } while (option != 8);

    return 0;
}
