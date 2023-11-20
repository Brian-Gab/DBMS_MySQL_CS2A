#include <iostream>
#include<string>
#include<windows.h>
#include<mysql.h>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<cctype>
#include<chrono>
#include<conio.h>

using namespace std;

//GlobalVariables-Start
string Acc_Directory = "C:\\Users\\Brian G\\Documents\\Documents\\VS\\C++\\Student Profile System\\Data\\";
//GlobalVariables-End

//birthday function - start
int calculateAge(int global_year_2, int global_int_month_2, int global_day_2);
void birthday();
bool isLeapYear(int year);
int global_year, global_day, global_int_month;
int b_year, b_day, age;
string b_month;
string global_month;

bool isLeapYear(int year){
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return true;
            }
        } else {
            return false;
        }
}
int calculateAge(int global_year_2, int global_int_month_2, int global_day_2){
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm* nowTm = std::localtime(&nowTime);

        int currentYear = nowTm->tm_year + 1900;
        int currentMonth = nowTm->tm_mon + 1;
        int currentDay = nowTm->tm_mday;

        int age = currentYear - global_year_2;

        // Adjust age based on birth month and day
        if(currentMonth < global_int_month_2 || (currentMonth == global_int_month_2 && currentDay < global_day_2))
        {
            age--;
        }

        return age;
}
void month_to_int(){
    int local_month;

    if(global_month == "January")
    {local_month = 1;}
    else if(global_month == "February")
    {local_month = 2;}
    else if(global_month == "March")
    {local_month = 3;}
    else if(global_month == "April")
    {local_month = 4;}
    else if(global_month == "May")
    {local_month = 5;}
    else if(global_month == "June")
    {local_month = 6;}
    else if(global_month == "July")
    {local_month = 7;}
    else if(global_month == "August")
    {local_month = 8;}
    else if(global_month == "September")
    {local_month = 9;}
    else if(global_month == "October")
    {local_month = 10;}
    else if(global_month == "November")
    {local_month = 11;}
    else if(global_month == "December")
    {local_month = 12;}

    global_int_month = local_month;
}
void birthday(){
    //birthday function - start
    string integer_month;
    int integer_day, integer_year;

    cout << "\033[0;93mBirth day\033[0m\n";
//Year

    cout << "Year: ";
    while(!(cin >> integer_year))
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Error. Please enter a valid year: ";
    }

    b_year = integer_year;
    global_year = integer_year;

//Year

//month na napakarami
    bool month_bool = true;
    do
    {
        cout << "Month: "; cin >> integer_month;
        transform(integer_month.begin(), integer_month.end(), integer_month.begin(), [](unsigned char c){return tolower(c);});

        if(integer_month == "january" or integer_month == "1")
        {
            b_month = "January";
            global_month = "January";
            month_bool = false;
        }
        else if(integer_month == "february" or integer_month == "2")
        {
            b_month = "February";
            global_month = "February";
            month_bool = false;
        }
        else if(integer_month == "march" or integer_month == "3")
        {
            b_month = "March";
            global_month = "March";
            month_bool = false;
        }
        else if(integer_month == "april" or integer_month == "4")
        {
            b_month = "April";
            global_month = "April";
            month_bool = false;
        }
        else if(integer_month == "may" or integer_month == "5")
        {
            b_month = "May";
            global_month = "May";
            month_bool = false;
        }
        else if(integer_month == "june" or integer_month == "6")
        {
            b_month = "June";
            global_month = "June";
            month_bool = false;
        }
        else if(integer_month == "july" or integer_month == "7")
        {
            b_month = "July";
            global_month = "July";
            month_bool = false;
        }
        else if(integer_month == "august" or integer_month == "8")
        {
            b_month = "August";
            global_month = "August";
            month_bool = false;
        }
        else if(integer_month == "september" or integer_month == "9")
        {
            b_month = "September";
            global_month = "September";
            month_bool = false;
        }
        else if(integer_month == "october" or integer_month == "10")
        {
            b_month = "October";
            global_month = "October";
            month_bool = false;
        }
        else if(integer_month == "november" or integer_month == "11")
        {
            b_month = "November";
            global_month = "November";
            month_bool = false;
        }
        else if(integer_month == "december" or integer_month == "12")
        {
            b_month = "December";
            global_month = "December";
            month_bool = false;
        }
        else{cout << "Error, invalid month." << endl;}

    } while(month_bool);
//dami naman
//day

    bool leap_year = isLeapYear(integer_year);
    bool day_bool = true;
    do
    {
        cout << "Day: "; cin >> integer_day;
        if((integer_month == "1" or integer_month == "january" or integer_month == "3" or integer_month == "march" or
            integer_month == "5" or integer_month == "may" or integer_month == "7" or integer_month == "july" or
            integer_month == "8" or integer_month == "august" or integer_month == "10" or integer_month == "october" or
            integer_month == "12" or integer_month == "december") and (integer_day >= 32 or integer_day == 0))
        {
            cout << "Error, invalid day." << endl;
        }

        else if((integer_month == "1" or integer_month == "january" or integer_month == "3" or integer_month == "march" or
            integer_month == "5" or integer_month == "may" or integer_month == "7" or integer_month == "july" or
            integer_month == "8" or integer_month == "august" or integer_month == "10" or integer_month == "october" or
            integer_month == "12" or integer_month == "december") and (integer_day <= 31 and integer_day != 0))
        {
            b_day = integer_day;
            global_day = integer_day;
            day_bool = false;
        }

        else if((integer_month == "2" or integer_month == "february") and (leap_year == false) and (integer_day >=29 or integer_day == 0))
        {
            cout << "Error, invalid day." << endl;
        }
        else if((integer_month == "2" or integer_month == "february") and (leap_year == true) and (integer_day >=30 or integer_day == 0))
        {
            cout << "Error, invalid day." << endl;
        }
        else if((integer_month == "2" or integer_month == "february") and (leap_year == true) and (integer_day <=29 and integer_day != 0))
        {
            b_day = integer_day; global_day = integer_day; day_bool = false;
        }
        else if((integer_month == "2" or integer_month == "february") and (leap_year == false) and (integer_day <=28 and integer_day != 0))
        {
            b_day = integer_day; global_day = integer_day; day_bool = false;
        }

        else if((integer_month == "4" or integer_month == "april" or integer_month == "6" or integer_month == "june" or
            integer_month == "9" or integer_month == "september" or integer_month == "11" or integer_month == "november") and (integer_day >=31 or integer_day == 0))
        {
            cout << "Error, invalid day." << endl;
        }
        else if((integer_month == "4" or integer_month == "april" or integer_month == "6" or integer_month == "june" or
            integer_month == "9" or integer_month == "september" or integer_month == "11" or integer_month == "november") and (integer_day <=30 and integer_day != 0))
        {
            b_day = integer_day; global_day = integer_day; day_bool = false;
        }
        else{cout << "Error, invalid day" << endl;}

    }while(day_bool);

    //day mas mahaba pala to
    month_to_int();
    //int inted_month = global_int_month;
    //int age = calculateAge(integer_year, inted_month, integer_day);

    //birthday and age function - end
}
//birthday function - end

void Connection(MYSQL* conn){

    if(conn)
    {
        cout << "\033[1;32mDatabase Connected Successfully!\033[0m";
    }
    else
    {
        cout << "Failed to Connect Database.";
    }
}

bool LogIn(){

    int counter2=0;

    while(counter2 != 5)
    {
        int dummy3;
        int counter1=0;
        string user,pass,u,p;
        system("color F");
        system("cls");
        cout<<"Please enter the following details"<<endl;
        cout<<"USERNAME: ";
        cin>>user;
        cout<<"PASSWORD: ";
        dummy3 = getch();

        while(dummy3 != 13)
        {
            pass.push_back(dummy3);
            cout << "*";
            dummy3 = getch();
        }

        ifstream input(Acc_Directory + "Admins\\"+ user + ".txt");
        if(!input)
        {
            system("cls");
            Sleep(1500);
            cout << "\033[1;31m<USER NOT FOUND>\033[0m" << endl;
            Sleep(2000);
            counter1=2;
        }
        else
        {
            while(input>>u>>p)
            {
                if(u==user && p==pass)
                {
                    counter1=1;
                    system("cls");
                }
                else if(p!=pass)
                {
                    counter1=2;
                    system("cls");
                }
            }
            input.close();
        }

        if(counter1==1)
        {
            cout<< "\033[1;32m<LOGIN SUCCESSFUL>\033[0m" << endl <<"Hello, "<< user;//green
            cin.get();
            Sleep(2000);
            system("cls");
            return true;
        }
        else
        {
            cout << "\033[1;31m<ACCESS DENIED>\033[0m" << endl;
            cout << "\033[1;31m<LOGIN ERROR. Please check your username and password.>\033[0m";
            Sleep(2000);
            system("cls");
            counter2++;
        }
    }

    Sleep(2000);
    return false;
}

void Register_User(){
    string reguser,regpass,ru,rp;
    int check;
    system("color 7");
    system("cls");
    cout<<"Enter the username: ";
    cin>>reguser;
    do
    {
        cout << "Enter the password (must contain 8 characters): "; cin >> regpass;
        check = regpass.length();
        if(check < 8){
            cout << "\033[1;31mPassword must contain 8 characters\033[0m" << endl;
            Sleep(1500);
        }
    } while (check < 8);
    system("cls");

    int counter1 = 5;
    while(counter1 != 0)
    {
        int dummy2;
        string root_un, root_pass;
        cout << "Enter Admin credentials to continue." << endl;
        cout << "Admin: ";
        cin >> root_un;
        cout << "Password: ";
        dummy2 = getch();
        while(dummy2 != 13)
        {
            root_pass.push_back(dummy2);
            cout << "*";
            dummy2 = getch();
        }

        if(root_un!="Joben" or root_pass!="Jobenigma_246810")
        {
            cout << "\nAdmin not found. ";
            cout << (counter1-1) << " attempt\\s remaining.";
            counter1--;
            Sleep(2000);
            system("cls");
        }
        else
        {
            cout << "Access Granted." << endl;
            ofstream reg(Acc_Directory + "Admins\\" + reguser + ".txt");
            reg << reguser << ' ' << regpass << endl;
            system("cls");
            cout << "Registration Successful\n";
            Sleep(1500);
            system("cls");
            return;
        }
    }
    Sleep(2000);
    cout << "Too many attempts. Registration Failed." << endl;
    Sleep(2000);
    system("cls");

}

void Register_Student(MYSQL* conn){
    int qstate = 0;
    stringstream this_thing;
    string f_name, l_name, m_name, stud_id, contact, bday;
    cin.ignore();

    cout << "Student's First Name: ";
    getline(cin, f_name);
    cout << "Student's Last Name: ";
    getline(cin, l_name);
    cout << "Student's Middle Name: ";
    getline(cin, m_name);

    //birthday start
    birthday();
    ostringstream b_year_str;
    ostringstream b_month_str;
    ostringstream b_day_str;

    b_year_str << global_year;
    b_month_str << global_int_month;
    b_day_str << global_day;

    string b_year_str2 = b_year_str.str();
    string b_month_str2 = b_month_str.str();
    string b_day_str2 = b_day_str.str();

    bday = b_year_str2 + "-" + b_month_str2 + "-" + b_day_str2;

    //birthday end

    cout << "Student's ID Number: ";
    cin.ignore(); getline(cin, stud_id);
    cout << "Student's Contact Number 63+: ";
    getline(cin, contact);

    this_thing << "INSERT INTO Student(First_Name,Last_Name,Middle_Name,Student_ID,Birth_Date,Contact) VALUES('"<<f_name<<"', '"<<l_name<<"', '"<<m_name<<"', '"<<stud_id<<"', '"<<bday<<"', '"<<contact<<"')";

    string query = this_thing.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    if(qstate != 0)
    {
        cout << mysql_error(conn) << endl;
        return;
    }
    else
    {
        cout << "Success." << endl;
    }
}


int main()
{
    bool main_loop = true;
    int choice1, choice2;

    MYSQL* conn;

    while(main_loop)
    {
        bool status = true;
        while(status)
        {
            cout << "===================================" << endl;
            cout << "     STUDENT DATABASE MANAGER      " << endl;
            cout << "===================================" << endl;
            cout << "Select Operation: " << endl;
            cout << "1. User Log In\n2. Register User\n3. Exit" << endl;
            cout << "Choice: ";
            cin >> choice1;

            switch(choice1){
                case 1:
                    if(LogIn())
                    {
                    conn = mysql_init(0);
                    conn = mysql_real_connect(conn, "localhost", "Joben", "Jobenigma_246810", "Student", 0, NULL, 0);

                    cout << "Setting up connection to the student database...";
                    Sleep(2000);
                    system("cls");
                    cout << "======================================" << endl;
                    cout << "|| "; Connection(conn); cout << " ||" << endl;
                    cout << "======================================" << endl << endl;
                    Sleep(3000);
                    system("cls");
                    status = false;
                    }
                    else
                    {
                        cout << "\033[1;31mToo many attempts. Restart the program.\033[0m" << endl;
                        return 0;
                    }
                    break;

                case 2:
                    Register_User();
                    break;

                case 3:
                    return 0;

                default:
                    system("cls");
                    cout << "===============" << endl;
                    cout << "Invalid Choice." << endl;
                    cout << "===============" << endl;
                    break;
            }
        }

        //Database Functions
        bool status2 = true;
        while(status2)
        {
            cout << "===================================" << endl;
            cout << "     STUDENT DATABASE MANAGER      " << endl;
            cout << "===================================" << endl;
            cout << "0. Exit" << endl;
            cout << "1. Student Lookup" << endl; //search student via name/id/contact_num
            cout << "2. Register Student" << endl; //register a student
            cout << "3. Update Student Record" << endl; //modify existing record
            cout << "4. Delete Student Record" << endl; //delete/archive a student record

            cout << "Choice: ";
            cin >> choice2;

            switch(choice2){
                case 0:
                    status2 = false;
                    break;

                case 1:
                    system("cls");

                    break;

                case 2:
                    system("cls");
                    Register_Student(conn);
                    break;

                case 3:
                    system("cls");

                    break;

                case 4:
                    system("cls");

                    break;

                default:
                    system("cls");
                    cout << "===============" << endl;
                    cout << "Invalid Choice." << endl;
                    cout << "===============" << endl;
                    break;
            }
        }
    }

    return 0;
}
