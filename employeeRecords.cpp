#include <iostream>
#include<conio.h>
#include<limits>
#include<unistd.h>
#include<sys/stat.h>
#include<fstream>
#include<cstdlib>

using namespace std;

struct Address
{
    int HouseNum;
    string Village;
    string postOffice;
    string city;
    string state;
    int pincode;
    string country;
};

struct Employee
{
    int emp_number;
    string fatherName;
    string empName;
    int dateOfJoining;
    string department;
    int dateOfRetirement;
    Address address;
};

struct Node
{
    Employee employee;
    Node* next;
};

Node* head = NULL;     //* creating the head of our linked list 

void loadingScreen()    {

    cout << "\n\nPress any key to continue...";      // showing loading on screen
    getch();
    system("cls");

}

void inputCredentials(Node* record) {   /// takes input of all credentials
    system("cls");

    cout << "\n::ENTER YOUR DETAILS BELOW::";
    cout << "\nYOUR EMPLOYEE ID: ";
    cin >> record->employee.emp_number;
    cout << "YOUR NAME: ";
    getline(cin >> ws , record->employee.empName) ;
    cout << "YOUR FATHER'S NAME: ";
    getline(cin >> ws, record->employee.fatherName);
    cout << "DATE OF JOINING: ";
    cin >> record->employee.dateOfJoining;
    cout << "DATE OF RETIREMENT: ";
    cin >> record->employee.dateOfRetirement;
    cout << "YOUR DEPARTMENT: ";
    getline(cin >> ws, record->employee.department);
    cout << "\nENTER YOUR COMPLETE ADDRESS BELOW: ";
    cout << "\nYOUR HOUSE NUMBER: ";
    cin >> record->employee.address.HouseNum;
    cout << "YOUR VILLAGE: ";
    getline(cin >> ws, record->employee.address.Village);
    cout << "POST OFFICE: ";
    getline(cin >> ws, record->employee.address.postOffice);
    cout << "CITY: ";
    getline(cin >> ws,record->employee.address.city);
    cout << "STATE: ";
    getline(cin >> ws,record->employee.address.state);
    cout << "PIN CODE: ";
    cin >> record->employee.address.pincode;
    cout << "COUNTRY: ";
    getline(cin >> ws, record->employee.address.country);

}

void printCredentials(Node* record) {

    cout << "Your current details are as follows:\n";
    cout << "------------------------------------\n";
    cout << "\nYOUR EMPLOYEE ID: ";
    cout << record->employee.emp_number;
    cout << "\nYOUR NAME: ";
    cout << record->employee.empName ;
    cout << "\nYOUR FATHER'S NAME: ";
    cout << record->employee.fatherName;
    cout << "\nDATE OF JOINING: ";
    cout << record->employee.dateOfJoining;
    cout << "\nDATE OF RETIREMENT: ";
    cout << record->employee.dateOfRetirement;
    cout << "\nYOUR DEPARTMENT: ";
    cout << record->employee.department;
    cout << "\nENTER YOUR COMPLETE ADDRESS BELOW: ";
    cout << "\nYOUR HOUSE NUMBER: ";
    cout << record->employee.address.HouseNum;
    cout << "\nYOUR VILLAGE: ";
    cout << record->employee.address.Village;
    cout << "\nPOST OFFICE: ";
    cout << record->employee.address.postOffice;
    cout << "\nCITY: ";
    cout << record->employee.address.city;
    cout << "\nSTATE: ";
    cout << record->employee.address.state;
    cout << "\nPIN CODE: ";
    cout << record->employee.address.pincode;
    cout << "\nCOUNTRY: ";
    cout << record->employee.address.country;

}

void createBackup()  {
    
    Node* temp;
    temp = head;

    ofstream ofs;
    ofs.open("C:/Employee Records/backup.csv", ios::out | ios::trunc);

    ofs << "emp_number" << "," << "empName" << "," << "fatherName" << ","
        << "department" << "," << "dateOfJoining" << "," << "dateOfRetirement" << ","
        << "city" << "," << "country" << "," << "HouseNum" << ","
        << "pincode" << "," << "postOffice" << "," << "state" << ","
        << "Village" << endl ;
    
    do{
        if (temp->employee.emp_number != 0) {
        ofs << temp->employee.emp_number << "," << temp->employee.empName << "," << temp->employee.fatherName << ","
            << temp->employee.department << "," << temp->employee.dateOfJoining << "," << temp->employee.dateOfRetirement << ","
            << temp->employee.address.city << "," << temp->employee.address.country << "," << temp->employee.address.HouseNum << ","
            << temp->employee.address.pincode << "," << temp->employee.address.postOffice << "," << temp->employee.address.state << ","
            << temp->employee.address.Village << endl ;
        }
        temp = temp->next;
    }while(temp != NULL);

    ofs.close();

}

void addRecord()    {   // function to add a new record // adds a new node to the end of the linked list and links it to prev node

    Node* record = new Node();    
    record->next = NULL;
    if (head == NULL)   {
        head = record;
        head->next = record;
        record->next = NULL;
    }
    
    inputCredentials(record);

    Node* temp;
    temp = head;

    while(temp->next != NULL)   {
        temp = temp->next;
    }

    temp->next = record;
    record->next = NULL;
    createBackup();

    cout << "\n::Your record has been added in the database::";
    loadingScreen();

}


void updateRecord(int empNum) {

    Node* temp;
    temp = head;

    while (temp->next != NULL && temp->employee.emp_number != empNum)   {
        temp = temp->next;
    }

    if (temp->employee.emp_number == empNum)   {
        printCredentials(temp);
        loadingScreen();
        inputCredentials(temp);
        createBackup();
        cout << "\n::YOUR RECORDS HAVE BEEN UPDATED::";
        cout << "\n----------------------------------";
        cout << "\n\nYOUR UPDATED DETAILS ARE AS FOLLOWS:\n";
        printCredentials(temp);
    }
    else    {
        cout << "\n::NO RECORD EXISTS FOR EMPLOYEE " << empNum << "::";
    }
    loadingScreen();
}

void deleteRecord(int empNum) {
    
    Node* temp , *prev;
    temp = head;
    prev = head;

    while (temp->next != NULL && temp->employee.emp_number != empNum)   {
        prev = temp;
        temp = temp->next;
    }

    if (temp->employee.emp_number == empNum)   {
        printCredentials(temp);
        loadingScreen();
        prev->next = temp->next;
        delete(temp);
        createBackup();
        cout << "\n::YOUR RECORD HAS BEEN DELETED::";
        loadingScreen();
    }
    else    {
        cout << "\n::NO RECORD EXISTS FOR EMPLOYEE " << empNum << "::";
    }
    loadingScreen();

}

void readBackup()   {
    
    string line;
    ifstream ifs("C:/Employee Records/backup.csv", ios::in);
    getline(ifs,line);

    while(!ifs.eof())   {

            Node* record = new Node();    
            record->next = NULL;
            if (head == NULL)   {
                head = record;
                head->next = record;
                record->next = NULL;
            }
            line.clear();
            getline(ifs,line,',');
            record->employee.emp_number = atoi(line.c_str());
            getline(ifs,line,',');
            record->employee.empName = line;
            getline(ifs,line,',');
            record->employee.fatherName = line;
            getline(ifs,line,',');
            record->employee.department = line;
            getline(ifs,line,',');
            record->employee.dateOfJoining = atoi(line.c_str());
            getline(ifs,line,',');
            record->employee.dateOfRetirement = atoi(line.c_str());
            getline(ifs,line,',');
            record->employee.address.city = line;
            getline(ifs,line,',');
            record->employee.address.country = line;
            getline(ifs,line,',');
            record->employee.address.HouseNum = atoi(line.c_str());
            getline(ifs,line,',');
            record->employee.address.pincode = atoi(line.c_str());
            getline(ifs,line,',');
            record->employee.address.postOffice = line;
            getline(ifs,line,',');
            record->employee.address.state = line;
            getline(ifs,line,'\n');
            record->employee.address.Village = line;

            Node* temp;
            temp = head;

            while(temp->next != NULL)   {
                temp = temp->next;
            }

            temp->next = record;
            record->next = NULL;
            
    }
    ifs.close();
}

void codeInitialize()   {

    mkdir("C:/Employee Records");
    
    ifstream ifs("C:/Employee Records/backup.csv", ios::in);
    
    if(!ifs) {
        ifs.close();
        ofstream ofs;
        ofs.open("C:/Employee Records/backup.csv", ios::out | ios::app);

        ofs << "emp_number" << "," << "empName" << "," << "fatherName" << ","
            << "department" << "," << "dateOfJoining" << "," << "dateOfRetirement" << ","
            << "city" << "," << "country" << "," << "HouseNum" << ","
            << "pincode" << "," << "postOffice" << "," << "state" << ","
            << "Village" << endl ;
        
        ofs.close();
        return;
    }
    else    {
        ifs.close();
        readBackup();
        return;
    }

}

void generateReport(char choice)   {

    Node* temp;
    temp = head;
    bool flag = 0;
        switch (choice)
        {
        case 49:    {
            string state,city;   
            cout << "\nEnter your choice of state: ";
            getline(cin, state);
            cout << "\nEnter your choice of city: ";
            getline(cin, city);
            if(temp == NULL) {
                cout << "\n::THE LIST IS EMPTY::";
                loadingScreen();
                return;
            }
            while(temp != NULL)    {
                if (temp->employee.address.state == state || temp->employee.address.city == city)  {
                    printCredentials(temp);
                    cout << "\n-----------------------------\n" ;
                    temp = temp->next;
                    flag = 1;
                }
                else    {
                    temp = temp->next;
                }
            }
            
            break;
        }
        case 50:    {
            int dateOfJoining;   
            cout << "\nDate of Joining: ";
            cin >> dateOfJoining;
            if(temp == NULL) {
                cout << "\n::THE LIST IS EMPTY::";
                loadingScreen();
                return;
            }
            while(temp != NULL)    {
                if (temp->employee.dateOfJoining == dateOfJoining)  {
                    printCredentials(temp);
                    cout << "\n-----------------------------\n" ;
                    temp = temp->next;
                    flag = 1;
                }
                else    {
                    temp = temp->next;
                }
            }
            break;
        }
        case 51:    {
            int dateOfRetirement;   
            cout << "\nDate of Retirement: ";
            cin >> dateOfRetirement;
            if(temp == NULL) {
                cout << "\n::THE LIST IS EMPTY::";
                loadingScreen();
                return;
            }
            while(temp != NULL)    {
                if (temp->employee.dateOfRetirement == dateOfRetirement)  {
                    printCredentials(temp);
                    cout << "\n-----------------------------\n" ;
                    temp = temp->next;
                    flag = 1;
                }
                else    {
                    temp = temp->next;
                }
            }
            break;
        }
        default:
            cout << "\n::Wrong Choice Entered::";
            return;
            break;
        }

    if (flag == 0)  {
                cout << "\n::NO RECORDS WITH THOSE ENTRIES";
    }
    loadingScreen();
}

int main()  {   

    codeInitialize();

    while(1)    {
        system("cls");
        
        cout << "\n\n\nWELCOME TO CCET EMPLOYEE DATABASE\n" ;
        cout << "\n1. Add a new record";
        cout << "\n2. Update an existing record";
        cout << "\n3. Delete an existing record";
        cout << "\n4. Generate a report";
        cout << "\n5. Exit";
        cout << "\nYour choice: ";

        switch(getch()) {

            case 49:    {   //* for new record 
                addRecord();
                break;
            }           
            case 50:    {   //* for update
                int empNum;
                cout << "\nEnter your Employee Number: ";
                cin >> empNum;
                updateRecord(empNum);
                break;
            }
            case 51:    {   //* for deletion
                int empNum;
                cout << "\nEnter your Employee Number: ";
                cin >> empNum;
                deleteRecord(empNum);
                break;
            }
            case 52:    {   //* for report generation
                system("cls");
                cout << "\nEnter a search criteria: ";
                cout << "\n\nAvailable options:";
                cout << "\n1. Same State or same City" << endl
                     << "2. Same date of joining" << endl
                     << "3. Same date of retirement";
                cout << "\nYour choice: ";
                char c = getch();
                generateReport(c);
                break;
            }
            case 53:    {   //* code termination
                exit(0);
                break;
            }
            default:    {   //* if any other key is pressed
                cout << "\n\n::Invalid Choice Entered::";
                sleep(2);
                break;
            }

        }
    }

}