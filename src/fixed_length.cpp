// Student Record Management System

#include <iostream>
#include <fstream> // For I/O operations
#include <string>// To use the string type
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <cstring> // To use strncpy function
#include <map> // To create a  primary index
#include <bits/stdc++.h> // To use sort function

using namespace std;

const int maxrow = 50; // Maximum number of records

struct Record {
    int id;           // 4 bytes
    int score;        // 4 bytes
    char name[50];    // 50 bytes
    char DofB[15];    // 15 bytes
};
map<int, int> primaryIndex; // Maps ID to the index in the records array


// Used to update primary index after addiction ,updating and deletion
void updatePrimaryIndex(Record records[], int recordCount) {
    primaryIndex.clear(); // Clear the existing index
    for (int i = 0; i < recordCount; i++) {
        primaryIndex[records[i].id] = i; // Map ID to the position in the array
    }
}


// Add a record
void addRecord(Record records[], int &recordCount) {
    if (recordCount >= maxrow) {
        cout << "Error: No space to add new record" << endl;
        return;
    }
    Record newRecord;

    cout << "Enter ID number: ";
    cin >> newRecord.id;
     // Check for duplicate ID
    for (int i = 0; i < recordCount; i++) {
        if (newRecord.id == records[i].id) {
            cout << "Error: ID " << newRecord.id << " already exists. Please use a unique ID." << endl;
            return; // Exit the function to prevent adding a duplicate
        }
    }

    cout << "Enter name (50 character MAX): ";
    cin.ignore();
    cin.getline(newRecord.name, 50);

    cout << "Enter score: ";
    cin >> newRecord.score;

    cout << "Enter date of birth (in the form dd/mm/yyyy): ";
    cin.ignore();
    cin.getline(newRecord.DofB, 15);

    // Store the record in the array
    records[recordCount] = newRecord;
    recordCount++;

    // Update the primary index
          updatePrimaryIndex(records, recordCount);

     cout<<"Record stored successfully"<<endl;

}


// Update Record
void updateRecord(Record records[], int searchID, int recordCount) {
    for (int i = 0; i < recordCount; i++) {
        if (records[i].id == searchID) {
            cout << "Enter new name (50 character MAX): ";
            cin.ignore();
            cin.getline(records[i].name, 50);

            cout << "Enter new score: ";
            cin >> records[i].score;

            cout << "Enter new date of birth (in the form dd/mm/yyyy): ";
            cin.ignore();
            cin.getline(records[i].DofB, 15);

            cout << "Record was updated successfully :)" << endl;
             // Update the primary index
           updatePrimaryIndex(records, recordCount);

            return;
        }
    }

    cout << "ID does not exist :(" << endl;
}


// Delete Record
void deleteRecords(Record records[], int searchID, int &recordCount) {
    for (int i = 0; i < recordCount; i++) {
        if (records[i].id == searchID) {
            for (int j = i; j < recordCount - 1; j++) {
                records[j] = records[j + 1];
            }
            recordCount--;

            // Update the primary index
           updatePrimaryIndex(records, recordCount);


            cout << "Record deleted successfully!" << endl;
            return;
        }
    }
    cout << "ID doesn't exist!" << endl;
}


//Search for record
void searchRecords(Record records[], int searchID, int recordCount) {
    cout << "Current Records" << endl;
    cout << "===========================================" << endl;
    cout << "No       ID       Name        Score       Date of Birth" << endl;
    cout << "--------------------------------------------------------" << endl;

    int counter = 0;
    for (int i = 0; i < recordCount; i++) {
        if (records[i].id == searchID) {
            counter++;
            cout << counter << "       " << records[i].id << "       " << records[i].name
                 << "       " << records[i].score << "       " << records[i].DofB << endl;
        }
    }

    if (counter == 0) {
        cout << "No records found!" << endl;
    }
}



// Display all records
void displayRecords(Record records[], int recordCount) {
    cout << "Current Records" << endl;
    cout << "======================================" << endl;
    cout << "No       ID       Name        Score       Date of Birth" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < recordCount; i++) {
        cout << i + 1 << "       " << records[i].id << "       " << records[i].name
             << "       " << records[i].score << "       " << records[i].DofB << endl;
    }

    if (recordCount == 0) {
        cout << "No records found!" << endl;
    }
}


void sortRecordsById(Record records[], int recordCount) {
    sort(records, records + recordCount, [](const Record &a, const Record &b){return a.id < b.id;});
}
bool binarySearch(Record records[], int low, int high, int searchID) {
    //sortRecordsById(records , recordCount);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (records[mid].id == searchID){
        cout<<"Record found"<<endl;
            cout << "No       ID       Name        Score       Date of Birth" << endl;
    cout << "--------------------------------------------------------" << endl;
               cout << mid + 1 << "       " << records[mid].id << "       " << records[mid].name
                 << "       " << records[mid].score << "       " << records[mid].DofB << endl;

            return true;
            }
         else if (records[mid].id < searchID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
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








// Save records to a file
void saveRecordsToFile(Record records[], int recordCount) {
    ofstream myFile("data/users3.txt", ios::out);
    if (!myFile) {
        cerr << "Error: Could not open file 'users.txt'" << endl;
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        myFile << records[i].id << ","
               << records[i].name << ","
               << records[i].score << ","
               << records[i].DofB << endl;
    }

    myFile.close();
    cout << "Records saved successfully!" << endl;
}

// Load records from a file
void loadFromFile(Record records[], int &recordCount, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    recordCount = 0;


    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, score, name, DoB;

        // Extract fields separated by commas
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, score, ',');
        getline(ss, DoB, ',');

        // Assign parsed values to the Record structure
        records[recordCount].id = stoi(id);
        records[recordCount].score = stoi(score);
        strncpy(records[recordCount].name, name.c_str(), sizeof(records[recordCount].name) - 1);
        records[recordCount].name[sizeof(records[recordCount].name) - 1] = '\0';
        strncpy(records[recordCount].DofB, DoB.c_str(), sizeof(records[recordCount].DofB) - 1);
        records[recordCount].DofB[sizeof(records[recordCount].DofB) - 1] = '\0';

        recordCount++;
    }

    inFile.close();
    cout << "Records loaded successfully from " << filename << endl;
}


int main() {


    Record records[maxrow];
    int recordCount = 0;
    string filename = "data/users3.txt";

    // Load records from file at the start
    loadFromFile(records, recordCount, filename);
    // Update the primary index
    updatePrimaryIndex(records, recordCount);

    int option;
    int searchID;

    do {
        // Display menu options
        cout << "\nMenu\n";
        cout << "1 - Create Record" << endl;
        cout << "2 - Update Record" << endl;
        cout << "3 - Delete Record" << endl;
        cout << "4 - Search Record" << endl;
        cout << "5 - Display All Records" << endl;
        cout << "6 - Search Record (Binary search)" << endl;
         cout << "7 - Search Record (Primary Index)" << endl;
        cout << "8 - Exit and Save" << endl;
        cout << "----------------------------" << endl;

        cout << "Select Option: ";
        // In case the user entered an invalid input
        while (!(cin >> option)) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input! Please enter a number: ";
}


        // Switch statement for menu options
        switch (option) {
        case 1:
            addRecord(records, recordCount);
            break;

        case 2:
            cout << "Enter the ID: ";
            cin >> searchID;
            updateRecord(records, searchID, recordCount);
            break;

        case 3:
            cout << "Enter the ID you want to delete: ";
            cin >> searchID;
            deleteRecords(records, searchID, recordCount);
            break;

        case 4:
            cout << "Enter the ID you want to search: ";
            cin >> searchID;
            searchRecords(records, searchID, recordCount);
            break;

        case 5:
            displayRecords(records, recordCount);
            break;

        case 6 :{
            cout<<"Enter the ID you want to search(Binary search): ";
            cin>> searchID;
            // Sort the records by ID
            sortRecordsById(records , recordCount);

            bool found= binarySearch(records , 0 , recordCount - 1 , searchID);
            if(found){

            }
            else {
            }
              // Update the primary index
           updatePrimaryIndex(records, recordCount);

            break;
        }
        case 7:
            cout << "Enter the ID you want to search(Primary Index): ";
            cin >> searchID;
            // Sort the records by ID
            //sortRecordsById(records , recordCount);
            searchUsingPrimaryIndex(records, searchID);
            break;
        case 8:
            saveRecordsToFile(records, recordCount);
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid option! Please try again." << endl;
        }
    } while (option != 8);

    return 0;
}
