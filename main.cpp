#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include <conio.h>

//PATCH 0.01: Application structure assembled.
//PATCH 0.02: Invalid characters handled.
//PATCH 0.03: Log In function completed.
//PATCH 0.04: Function for New User Registration completed.
//PATCH 0.05: Passwords blurred. --[Update from PATCH 0.06: buffers for reg_users caused some bugs]
//PATCH 0.06: 2nd Log In issue fixed(I hope).
//PATCH 0.07: Insert and Edit functions completed(I hope).
//PATCH 0.08: FIXED THE FUCKING TABLE, I mean View Table function completed.
//PATCH 0.09: TAENA AYAW MA-INSERT SA ARCHIVE TABLE.
//PATCH 0.10: Delete function completed. Program almost done.
//PATCH 0.11: Search function added. [found a bug tho, registering a letter will record as 0, which in turn prevents adding of 0 as student id]

using namespace std;

MYSQL* main_connection;
const char* main_database = "Student";
//const char* arch_database = "archive";
const char* host = "localhost";

//Credentials reg = regular, god = godmin
const char* reg_user;
const char* reg_pass;
const char* god_user;
const char* god_pass;
char buffer_reguser[100];
string buffer_regpass;
char buffer_goduser[100];
char buffer_godpass[100];

//functions
bool isLoggedIn();
void register_reguser();

void insertData();
void editData();
void viewData();
void deleteData();
void searchData();

//additional functions
void realEdit();
void realDelete();
string birthDate();
void printTableRow(const string& col1, const string& col2, const string& col3, const string& col4, const string& col5, const string& col6, const string& col7);
void archiveData_False(string stud_id, string f_name, string l_name, string m_name, string bdate, string contact);
void archiveData_True(string stud_id);

int main(){

    bool loop1, loop2;
    string choice1_str, choice2_str;
    int choice1, choice2;
    loop1 = true;
    while(loop1){
        //====================================================================================================
        system("cls");
        cout << "+================================+" << endl;
        cout << "|                                |" << endl;
        cout << "|    STUDENT DATABASE MANAGER    |" << endl;
        cout << "|                                |" << endl;
        cout << "+================================+" << endl;
        cout << "[1] Log In" << endl;
        cout << "[2] Register User" << endl;
        cout << "[3] Exit" << endl;
        cout << "> "; cin >> choice1_str;

        //GPT
        try
        {
            choice1 = stoi(choice1_str);
        }
        catch (const invalid_argument& e)
        {
            system("cls");
            cerr << "Invalid character."<< endl;
            cout << "Terminating session." << endl;
            Sleep(1000);
            return 0;
        }
        //GPT

        switch(choice1){
            default:
                system("cls");
                cout << "Invalid choice." << endl;
                Sleep(2000);
                loop1 = true;
                break;

            case 1:
                if(isLoggedIn())
                {
                    loop2 = true;
                    break;
                }
                else
                {
                    loop2 = false;
                    break;
                }

            case 2:
                if(isLoggedIn())
                {
                    register_reguser();

                    loop2 = false;
                    break;
                }
                else
                {
                    cout << "Credentials mismatched." << endl;
                    loop2 = false;
                    break;
                }

            case 3:
                loop1 = false;
                break;
        }
        //====================================================================================================

        while(loop2){
            //====================================================================================================
            system("cls");
            cout << "+------------------------------------------+" << endl;
            cout << "|       STUDENT DATABASE MANAGER           |" << endl;
            cout << "+------------------------------------------+" << endl;
            cout << "[1] Register Student Information" << endl;
            cout << "[2] Edit Student Information" << endl;
            cout << "[3] Archive Student Information" << endl;
            cout << "[4] View Database" << endl;
            cout << "[5] Search Student" << endl;
            cout << "[6] Log Out" << endl;
            cout << "> "; cin >> choice2_str;

            //GPT
            try
            {
                choice2 = stoi(choice2_str);
            }
            catch (const invalid_argument& e)
            {
                system("cls");
                cerr << "Invalid character."<< endl;
                cout << "Terminating session." << endl;
                Sleep(1000);
                return 0;
            }
            //GPT

            switch(choice2){
                default:
                    system("cls");
                    Sleep(2000);
                    cout << "Invalid Choice." << endl;
                    loop2 = true;
                    break;

                case 1:
                    //function
                    insertData();
                    break;

                case 2:
                    //function
                    editData();
                    break;

                case 3:
                    //function
                    deleteData();
                    break;

                case 4:
                    //function
                    viewData();
                    system("pause");
                    break;

                case 5:
                    //function
                    searchData();
                    break;

                case 6:
                    string confirm;
                    cout << "Confirm log out y/n: ";
                    cin >> confirm;
                    transform(confirm.begin(), confirm.end(), confirm.begin(), [](unsigned char c){return tolower(c);});

                    if(confirm == "y" or confirm == "yes"){
                        loop2 = false;
                        break;
                    }
                    else{loop2 = true; break;}
            }
            //====================================================================================================
        }

    }

}

bool isLoggedIn(){

    system("cls");
    //GPT
    buffer_regpass.clear();
    if(main_connection != nullptr)
    {
        mysql_close(main_connection);
        main_connection = nullptr;
    }
    //GPT

    cout << "[ADMIN LOG-IN]" << endl;
    cout << "Username: "; cin >> buffer_reguser;
    cout << "Password: ";

    //Password blurring
    char ch;
    while((ch = _getch()) != 13)
    {
        if(ch == 8)
        {
            if(!buffer_regpass.empty())
            {
                buffer_regpass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            buffer_regpass.push_back(ch);
            cout << "*";
        }
    }
    //password blurred

    reg_user = buffer_reguser;
    reg_pass = buffer_regpass.c_str();

    main_connection = mysql_init(nullptr);
    main_connection = mysql_real_connect(main_connection, host, reg_user, reg_pass, main_database, 0, NULL, 0);

    if(main_connection)
    {
        system("cls");
        cout << "<DATABASE CONNECTED SUCCESSFULLY>" << endl;
        Sleep(2000);
        return true;
    }
    else
    {
        system("cls");
        cout << "<FAILED TO CONNECT DATABASE>" << endl;
        cout << "Check your username and password" << endl;
        cout << "Error: " << mysql_error(main_connection) << endl;;
        Sleep(2000);
        return false;

    }
}

void register_reguser(){

    system("cls");
    cout << "Admin " << reg_user << " logged in successfully." << endl;
    string new_reg_username, new_reg_password;

    cout << "[REGISTER USER ACCOUNT]" << endl;
    cout << "Username: "; cin >> new_reg_username;
    cout << "Password: ";

    //Password blurring
    char ch;
    while((ch = _getch()) != 13)
    {
        if(ch == 8)
        {
            if(!new_reg_password.empty())
            {
                new_reg_password.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            new_reg_password.push_back(ch);
            cout << "*";
        }
    }
    //password blurred

    int qstate = 0;
    stringstream ss;
    ss << "CREATE USER '"<<new_reg_username<<"'@'%' IDENTIFIED BY '"<<new_reg_password<<"';";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(main_connection, q);

    if(qstate == 0)
    {
        system("cls");
        cout << "Username and Password recorded." << endl;
        cout << "Granting permissions..." << endl;
        Sleep(2000);

        ss.str("");
        ss << "GRANT ALL PRIVILEGES ON *.* TO '"<< new_reg_username << "'@'%';";
        query = ss.str();
        q = query.c_str();
        qstate = mysql_query(main_connection, q);
        cout << "NEW USER ACCOUNT CREATED" << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Error: " << mysql_error(main_connection) << endl;
        Sleep(5000);
    }
}

void insertData(){
    system("cls");

    //int qstate = 0;
    stringstream insertThis;
    string f_name, l_name, m_name;
    string student_id, contact_num;
    //int b_day, b_month, b_year;
    string bdate;
    cin.ignore();

    bool uniqueID = false;
    while (!uniqueID) {
        system("cls");
        cout << "Student ID: ";
        getline(cin, student_id);

        stringstream idCheckQuery;
        idCheckQuery << "SELECT COUNT(*) FROM student WHERE student_id = '" << student_id << "'";
        string idCheckQueryString = idCheckQuery.str();
        const char* idCheckQueryStr = idCheckQueryString.c_str();

        int idCheckResult = mysql_query(main_connection, idCheckQueryStr);
        if (idCheckResult == 0) {
            MYSQL_RES* result = mysql_store_result(main_connection);
            MYSQL_ROW row = mysql_fetch_row(result);
            int count = stoi(row[0]);

            if (count == 0) {
                uniqueID = true;
            } else {
                cout << "\nStudent ID already exists.\n" << endl;
                system("pause");
            }
        } else {
            cerr << "Error checking student ID: " << mysql_error(main_connection) << endl;
            return;
        }
    }

    system("cls");
    cout << "Student's First Name: ";
    getline(cin, f_name);
    cout << "Student's Last Name: ";
    getline(cin, l_name);
    cout << "Student's Middle Name: ";
    getline(cin,m_name);

    system("cls");
    cout << "Contact number (+63): ";
    getline(cin, contact_num);

    system("cls");
    bdate = birthDate();

    insertThis << "INSERT INTO student(student_id, first_name, last_name, middle_name, birth_date, contact) VALUES ('"<<student_id<<"', '"<<f_name<<"', '"<<l_name<<"', '"<<m_name<<"', '"<<bdate<<"', '"<<contact_num<<"')";
    string query = insertThis.str();
    const char* q = query.c_str();
    int qstate = mysql_query(main_connection, q);

    //Gumawa ako new table sa student named "archived". Para dalawa yung table, but pag dinelete sa student(student) merong archive dito sa student(archived)
    if(qstate != 0)
    {
        cout << "Information not inserted. Try again." << endl;
        cout << mysql_error(main_connection);
        system("pause");
    }
    else
    {
        cout << "INFORMATION INSERTED SUCCESSFULLY!" << endl;
        Sleep(2000);
    }

    archiveData_False(student_id, f_name, l_name, m_name, bdate, contact_num);
}

void editData(){
    system("cls");

    bool loop1;

    loop1 = true;
    while(loop1)
    {
        int option;

        system("cls");
        cout << "+-------------------+" << endl;
        cout << "|      UPDATE       |" << endl;
        cout << "+-------------------+" << endl;
        cout << "[1] View Table" << endl;
        cout << "[2] Update a Student Information" << endl;
        cout << "[3] Exit" << endl;
        cout << "> "; cin >> option;

        switch(option)
        {
            default:
                cout << "Invalid Choice." << endl;
                break;
            case 1:
                viewData();
                break;
            case 2:
                realEdit();
                break;
            case 3:
                loop1 = false;
                break;
        }
    }

}

void viewData(){
    system("cls");

    MYSQL_RES* result;
    MYSQL_ROW row;

    const char* q = "SELECT * FROM student";
    mysql_query(main_connection,q);
    result = mysql_store_result(main_connection);

    cout << "+------------+----------------------+----------------------+----------------------+------------+-----+------------+\n";
    cout << "|     ID     |     First Name       |       Last Name      |      Middle Name     | Birth_Date | Age |   Contact  |\n";
    cout << "+------------+----------------------+----------------------+----------------------+------------+-----+------------+\n";

    while ((row = mysql_fetch_row(result)))
    {
        cout << "|";
        printTableRow(row[0], row[1], row[2], row[3], row[4], row[6], row[5]);
        cout << endl;
    }
    cout << "+------------+----------------------+----------------------+----------------------+------------+-----+------------+\n";
}

void deleteData(){
    system("cls");

    bool loop1 = true;
    while(loop1)
    {
        int option;

        system("cls");
        cout << "+--------------------+" << endl;
        cout << "|       REMOVE       |" << endl;
        cout << "+--------------------+" << endl;
        cout << "[1] View table" << endl;
        cout << "[2] Remove Information" << endl;
        cout << "[3] Back" << endl;
        cout << "> "; cin >> option;

        switch(option)
        {
            default:
                cout << "Invalid Choice." << endl;
                break;
            case 1:
                viewData();
                break;
            case 2:
                realDelete();
                break;
            case 3:
                loop1 = false;
                break;
        }
    }
}

void searchData(){
    system("cls");

    string id;
    cout << "Student ID: ";
    cin >> id;

    MYSQL_RES* result;
    MYSQL_ROW row;

    stringstream queryThis;
    queryThis << "SELECT * FROM student WHERE student_id = '"<< id <<"';";

    string query = queryThis.str();
    const char* q = query.c_str();
    mysql_query(main_connection,q);

    result = mysql_store_result(main_connection);
    row = mysql_fetch_row(result);

    if(row != nullptr)
    {
        cout << "+------------+----------------------+----------------------+----------------------+------------+-----+------------+\n";
        cout << "|     ID     |     First Name       |       Last Name      |      Middle Name     | Birth_Date | Age |   Contact  |\n";
        cout << "+------------+----------------------+----------------------+----------------------+------------+-----+------------+\n";

        cout << "|";
        printTableRow(row[0], row[1], row[2], row[3], row[4], row[6], row[5]);
        cout << endl;
        cout << "+------------+----------------------+----------------------+----------------------+------------+-----+------------+\n";
        system("pause");
    }
    else
    {
        cout << "Student ID not found." << endl;
        system("pause");
    }

}
//additional functions
string birthDate(){

    int day, month, year;
    string month_str, day_str, year_str;
    cout << "          BIRTH DATE          " << endl;
    system("cls");
    while(month < 1 || month > 12 || day < 1 || day > 31 || year < 1900 || year > 2100)
    {
        cout << "          Birth Date          "<< endl;
        cout << "------------------------------"<< endl;
        cout << "[1] January      [7] July"     << endl;
        cout << "[2] February     [8] August"   << endl;
        cout << "[3] March        [9] September"<< endl;
        cout << "[4] April       [10] October"  << endl;
        cout << "[5] May         [11] November" << endl;
        cout << "[6] June        [12] December" << endl;
        cout << "------------------------------"<< endl;
        cout << endl;

        //VALIDITY OF DATE
        //GPT
        bool validMonth = false;
        while (!validMonth){
            cout << "Month: ";
            cin >> month_str;

            try{
                month = stoi(month_str);
                validMonth = true; // Set validMonth to true if stoi succeeds
            }catch (const invalid_argument& e){
                system("cls");
                cerr << "Invalid character." << endl;
                Sleep(1000);
            }
        }

        bool validDay = false;
        while (!validDay){
            cout << "Day: ";
            cin >> day_str;

            try{
                day = stoi(day_str);
                validDay = true; // Set validMonth to true if stoi succeeds
            }catch (const invalid_argument& e){
                system("cls");
                cerr << "Invalid character." << endl;
                Sleep(1000);
            }
        }

        bool validYear = false;
        while (!validYear){
            cout << "Year: ";
            cin >> year_str;

            try{
                year = stoi(year_str);
                validYear = true; // Set validMonth to true if stoi succeeds
            }catch (const invalid_argument& e){
                system("cls");
                cerr << "Invalid character." << endl;
                Sleep(1000);
            }
        }
        //VALIDITY OF DATE

        cout << endl;
        if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1900 || year > 2100){
            cerr << "Invalid date. Please enter a valid date.\n" << endl;
        }
    }

    string str_year, str_month, str_day;
    stringstream sy, sm, sd;
    sy << year;
    sm << month;
    sd << day;

    str_year = sy.str();
    str_month = sm.str();
    str_day = sd.str();

    string bdate = str_year + "-" + str_month + "-" + str_day;

    return bdate;
}

void realEdit(){
    system("cls");

    string choice1_str;
    int choice1;
    string column, new_val, id;

    cout << "Enter Student's ID: ";
    cin >> id;

    cout << "  Edit column     " << endl;
    cout << "------------------" << endl;
    cout << "[1] First name" << endl;
    cout << "[2] Last name"  << endl;
    cout << "[3] Middle name"<< endl;
    cout << "[4] Contact"    << endl;
    cout << "[5] Birth date" << endl;
    cout << "------------------" << endl;

    bool validItem = false;
        while (!validItem){
            cout << "> ";
            cin >> choice1_str;

            try{
                choice1 = stoi(choice1_str);
                validItem = true; // Set validMonth to true if stoi succeeds
            }catch (const invalid_argument& e){
                system("cls");
                cerr << "Invalid character." << endl;
                Sleep(1000);
            }
        }



    switch(choice1)
    {
        default:
            cout << "Invalid Choice." << endl;
            break;

        case 1:
            column = "first_name";
            cout << "New value: ";cin >> new_val;
            break;
        case 2:
            column = "last_name";
            cout << "New value: ";cin >> new_val;
            break;
        case 3:
            column = "middle_name";
            cout << "New value: ";cin >> new_val;
            break;
        case 4:
            column = "contact";
            cout << "New value: ";cin >> new_val;
            break;
        case 5:
            string bday;
            bday = birthDate();
            column = "birth_date";
            new_val = bday;
    }


    int qstate = 0;
    stringstream ss;
    ss << "UPDATE student SET "<<column<<" = '"<< new_val <<"' WHERE student_id = '"<<id<<"' ;";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(main_connection, q);

    if(qstate != 0)
    {
        cout << "Information not updated. Try again." << endl;
        Sleep(2000);
    }
    else
    {
        cout << "STUDENT INFORMATION UPDATED!" << endl;
        Sleep(2000);
    }
}

void realDelete(){
    system("cls");

    string index;
    cout << "Student ID: ";
    cin >> index;

    stringstream deleteThis;

    deleteThis << "DELETE FROM student WHERE student_id = '"<<index<<"';";
    string query = deleteThis.str();
    const char* q = query.c_str();
    mysql_query(main_connection, q);

    archiveData_True(index);
}

void printTableRow(const string& col1, const string& col2, const string& col3, const string& col4, const string& col5, const string& col6, const string& col7){
    const int colWidth = 21;
    cout << left << " " << setw(11) << col1 << "|";
    cout << left << " " << setw(colWidth) << col2 << "|";
    cout << left << " " << setw(colWidth) << col3 << "|";
    cout << left << " " << setw(colWidth) << col4 << "|";
    cout << left << " " << setw(11) << col5 << "|";
    cout << left << " " << setw(4) << col6 << "|";
    cout << left << " " << setw(11) << col7 << "|";

}

void archiveData_False(string stud_id, string f_name, string l_name, string m_name, string bdate, string contact){

    string archive_status = "false";
    stringstream archiveThis;
    archiveThis << "INSERT INTO archive(Student_ID, First_Name, Last_Name, Middle_Name, Birth_Date, Contact, is_archived) VALUES ('"<<stud_id<<"', '"<<f_name<<"', '"<<l_name<<"', '"<<m_name<<"', '"<<bdate<<"', '"<<contact<<"', '"<<archive_status<<"')";
    string query = archiveThis.str();
    const char* q = query.c_str();
    mysql_query(main_connection, q);

}

void archiveData_True(string stud_id){

    string archive_status = "true";
    stringstream archiveThis;
    string column = "is_archived";
    archiveThis << "UPDATE archive SET "<< column <<" = '"<< archive_status <<"' WHERE student_id = '"<< stud_id <<"' ;";
    string query = archiveThis.str();
    const char* q = query.c_str();
    mysql_query(main_connection, q);
}
