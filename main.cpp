#include <iostream>
#include <ostream>
#include <fstream>
#include <conio.h>
#include "cusgraphics.h"
#include "user.h"
#include "loadingfnc.h"
#include "function.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class travel
{
    char title_of_itinerary[50];
    char starting_point[30];
    char destination[30];
    int days;
    int expenses;

public:
    void set_val();
    void show_val(int serial_number);
    void create_itinerary();
    void list_itinerary();
    void search_itinerary();
    void edit_itinerary();
    void delete_itinerary();
    void admin_dashboard();
    void book_form();
    int get_integer_from_user_input();
};

// this function sets the value of an object when called
void travel::set_val()
{
    std::cout << "Title of Itinerary: " << flush;
    cin >> ws;
    cin.getline(title_of_itinerary, sizeof(travel));
    std::cout << "Starting Point: ";
    cin >> ws;
    cin.getline(starting_point, sizeof(travel));
    // cin >> starting_point;
    std::cout << "Destination: ";
    cin >> ws;
    cin.getline(destination, sizeof(travel));
    // cin >> destination;
    std::cout << "Days: ";
    days = get_integer_from_user_input();
    std::cout << "Expenses: ";
    expenses = get_integer_from_user_input();
}

// this function shows the value in an object
void travel::show_val(int serial_number)
{
    std::cout << serial_number << "\t" << left << setw(45) << title_of_itinerary << left << setw(20) << starting_point << left << setw(20) << destination << left << setw(8) << days << left << setw(8) << expenses << "\n";
}

// this function is used to create itinerary
void travel::create_itinerary()
{
    travel t;
    ofstream createfile;
    createfile.open("itinerary.txt", std::ios::out | std::ios::app | std::ios::binary);
    t.set_val();
    createfile.write((char *)&t, sizeof(t));
    createfile.close();
}

// This function is used to List Itinerary
void travel::list_itinerary()
{
    ifstream fileList;
    int n = 0;
    fileList.open("itinerary.txt", std::ios::in);
    fileList.seekg(0, std::ios::end);
    int filesize = fileList.tellg();
    int obj = filesize / sizeof(travel);
    // std::cout << obj;
    fileList.seekg(0, std::ios::beg);
    travel t;
    fileList.read((char *)&t, sizeof(t));
    std::cout << "\n"
              << "S.N\t" << left << setw(45) << "Title of Itinerary" << left << setw(20) << "Starting Point" << left << setw(20) << "Destination" << left << setw(8) << "Days" << left << setw(8) << "Expenses\n";
    while (fileList)
    {
        n++;
        t.show_val(n);
        fileList.read((char *)&t, sizeof(t));
    }
    fileList.close();
}

// this function is used to Search Itinerary
void travel::search_itinerary()
{
    travel t;
    std::string search_item;
    int position;
    int n = 0, l = 11;
search_top:
    system("cls");
    std::cout << "Search Trip\n";
    std::cout << "Enter the keyword: ";
    getline(std::cin >> ws, search_item);
    std::ifstream filesearch;
    filesearch.open("itinerary.txt", std::ios::in);
    while (!filesearch.eof())
    {
        position = filesearch.tellg();
        filesearch.read((char *)this, sizeof(travel));
        if (title_of_itinerary == search_item || starting_point == search_item || destination == search_item)
        {
            n++;
            std::cout << n << "\t";
            filesearch.read((char *)this, sizeof(t));
            std::cout << "Title Of Itinerary: " << title_of_itinerary << "\n";
            std::cout << "Starting Point: " << starting_point << "\n";
            std::cout << "Destination: " << destination << "\n";
            std::cout << "Days: " << days << "\n";
            std::cout << "Expenses: " << expenses << "\n";
        }
    }
}

// this function is used to Edit Itinerary
void travel::edit_itinerary()
{
    travel t;
    int flag = 0;
    fstream editfile;
    string edit_item;
    long position;
    std::cout << "Enter Itinerary Title: ";
    getline(cin >> ws, edit_item);
    editfile.open("itinerary.txt", std::ios::in | std::ios::out | std::ios::binary);
    while (!editfile.eof())
    {
        position = editfile.tellg();
        editfile.read((char *)this, sizeof(travel));
        if (title_of_itinerary == edit_item)
        {
            std::cout << "\n Enter New Details";
            std::cout << "\n -----------------";
            std::cout << "Title of itenary: ";
            cin >> ws;
            cin.getline(title_of_itinerary, sizeof(travel));
            std::cout << "Starting point: ";
            cin >> ws;
            cin.getline(starting_point, sizeof(travel));
            // cin >> starting_point;
            std::cout << "Destination: ";
            cin >> ws;
            cin.getline(destination, sizeof(travel));
            // cin >> destination;
            std::cout << "Days: ";
            std::cin >> days;
            std::cout << "Expenses: ";
            std::cin >> expenses;
            editfile.seekp(position);
            editfile.write((char *)this, sizeof(travel));
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        std::cout << "Entered itinerary is not found";
    }
}

// this function is used to delete Itinerary
void travel::delete_itinerary()
{
    int flag = 0;
    char ch;
    std::string dec_title;
    std::cout << "Enter the TItle of itinerary that is to be deleted: ";
    getline(cin >> ws, dec_title);
    std::ifstream fin("itinerary.txt", ios::in);
    std::ofstream fout("bin.txt", ios::out);
    fin.read((char *)this, sizeof(travel));
    while (!fin.eof())
    {
        if (title_of_itinerary == dec_title)
        {
            std::cout << "\n Title of itinerary " << title_of_itinerary;
            std::cout << "\n starting point: " << starting_point;
            std::cout << "\n Destination: " << destination;
            std::cout << "\n Days: " << days;
            std::cout << "\n Expenses: " << expenses;
            std::cout << "\n\n Do you want to delete this Itinerary(y/n): ";
            std::cin >> ch;
            if (ch == 'n')
            {
                fout.write((char *)this, sizeof(travel));
            }
            flag = 1;
        }
        else
        {
            fout.write((char *)this, sizeof(travel));
        }
        fin.read((char *)this, sizeof(travel));
    }

    fin.close();
    fout.close();

    if (flag == 0)
    {
        cout << "\n Sorry the trip can't be found...!!";
    }
    else
    {
        remove("itinerary.txt");
        rename("bin.txt", "itinerary.txt");
    }
}

// this function is used to show the admin dashboard after login
void travel::admin_dashboard()
{
    system("cls");
admin_top:
    int in;
    system("cls");
    std::cout << "Admin Dashboard:\n\n";
    std::cout << "1.\t Create New Itinerary\n";
    std::cout << "2.\t Edit Itinerary\n";
    std::cout << "3.\t Delete Itinerary\n";
    std::cout << "4.\t Logout\n";
    std::cout << "Enter your option:(1-4): ";
    std::cin >> in;

    switch (in)
    {
    case 1:
        system("cls");
        create_itinerary();
        std::cout << "Itinerary is created!!";
        getch();
        goto admin_top;
        break;
    case 2:
        system("cls");
        edit_itinerary();
        goto admin_top;
        break;
    case 3:
        system("cls");
        delete_itinerary();
        goto admin_top;
        break;
    case 4:
        system("cls");
        break;
    default:
        system("cls");
        std::cout << "Please enter correct input";
        system("cls");
        goto admin_top;
        break;
    }
}

// this function is used for booking a trip
void travel::book_form()
{
    int flag = 0;
book_top:
    std::string search_item;
    std::string book_item_title;
    std::string book_item_start_point;
    std::string book_item_destination;
    int book_item_days;
    int book_item_expenses;
    std::string customer_name;
    int number_of_people;
    long long unsigned int phone_number = 0;
    int day, month, year;

    ifstream trip_det;
    std::cout << "Enter title of itinerary: ";
    getline(std::cin >> ws, search_item);
    trip_det.open("itinerary.txt", std::ios::in);
    trip_det.seekg(0, std::ios::beg);
    while (!trip_det.eof())
    {
        trip_det.read((char *)this, sizeof(travel));
        if (title_of_itinerary == search_item)
        {
            book_item_title = title_of_itinerary;
            book_item_start_point = starting_point;
            book_item_destination = destination;
            book_item_days = days;
            book_item_expenses = expenses;
            flag = 1;
            break;
        }
    }
    trip_det.close();
    if (flag == 0)
    {
        std::cout << "The Itinerary is not found";
    }
    else
    {
        system("cls");
        std::cout << "Title of itinerary: " << book_item_title << "\n";
        std::cout << "Starting point: " << book_item_start_point << "\n";
        std::cout << "Destination: " << book_item_destination << "\n";
        std::cout << "Days: " << book_item_days << "\n";
        std::cout << "Expenses: " << book_item_expenses << "\n";
        std::cout << "Enter your name: ";
        getline(std::cin >> ws, customer_name);
        std::cout << "Enter number of people: ";
        std::cin >> number_of_people;
    date_start:
        std::cout << "Departure Date [Please use space as separator] (yyyy-mm-dd):";
        std::cin >> year >> month >> day;
        if (date_check(year, month, day) != 1)
        { // date check() function is defined in function.h header file, this function checks if the entered date is correct or not
            std::cout << "Please Enter correct date";
            goto date_start;
        }
    phone_er:
        std::cout << "Enter your phone number: ";
        std::cin >> phone_number;
        if (phone_check(phone_number) != 1)
        { // phone_check() function is defined in function.h header file, this function checks if the entered phone number is correct of not
            std::cout << "Phone Number is not correct";
            goto phone_er;
        }

        ofstream bookrec;
        bookrec.open("bookrec.txt", ios::out | ios::app);
        bookrec << "\n=============================================================\n";
        bookrec << "Customer Name: " << customer_name << "\n";
        bookrec << "Number of people: " << number_of_people << "\n";
        bookrec << "Departure Date: " << year << "/" << month << "/" << day << "\n";
        bookrec << "Phone number: " << phone_number << "\n";
        bookrec << "Booked item detail:- \n";
        bookrec << "\tTitle of itinerary: " << book_item_title << "\n";
        bookrec << "\tStarting point: " << book_item_start_point << "\n";
        bookrec << "\tDestination: " << book_item_destination << "\n";
        bookrec << "\tDays: " << book_item_days << "\n";
        bookrec << "\tExpenses: " << book_item_expenses << "\n";
        bookrec << "=============================================================\n";
        bookrec.close();

        std::cout << "Your Trip has been booked. Thank you!!";
        exit(0);
    }
}

int travel::get_integer_from_user_input()
{
    string line;
    int x;
    while (getline(cin, line))
    {
        stringstream ss(line);
        if (ss >> x)
        {
            if (ss.eof())
            {
                break;
            }
        }
        cout << "Invalid Input!"
             << "\n"
             << "Please enter integer:";
    }
    return x;
}

int main()
{
    system("cls");
    gotoxy(40, 5); // gotoxy(x,y) function is defined in cusgraphics.h function, this function is used to locate the cursor at the x and y coordinate
    firstload();   // this is defined in loading.h header file
    gotoxy(45, 8);
    loading(); // this is defined in loading.h header file
top:
    travel t;
    account user; // account class is defined in user.h header file
    int input = 0;
    char ch;
    system("cls");
    std::cout << "\n\n\n\n";
    std::cout << "\t\t\tSelect: \n";
    std::cout << "1. List Itinerary\n";
    std::cout << "2. Search Itinerary\n";
    std::cout << "3. login\n";
    std::cout << "4. Exit Program\n";
    std::cout << "Enter here: ";
    std::cin >> input;
    switch (input)
    {
    case 1:
        system("cls");
        t.list_itinerary();
        std::cout << "Do you want to book: ";
        std::cin >> ch;
        if (ch == 'y' || ch == 'Y')
        {
            t.book_form();
        }
        else
        {
            std::cout << "Thank you for using our services.";
        }
        getch();
        goto top;
        break;
    case 2:
        system("cls");
        t.search_itinerary();
        std::cout << "Do you want to book: ";
        std::cin >> ch;
        if (ch == 'y' || ch == 'Y')
        {
            t.book_form();
        }
        else
        {
            std::cout << "Thank you for using our services.";
        }
        getch();
        goto top;
        break;
    case 3:
        system("cls");
        user.login(); // this function is defined in user.h header file
        getch();
        t.admin_dashboard();
        goto top;
        break;
    case 4:
        system("cls");
        std::cout << "Thank you for using this program";
        exit(0); // this function exits the program
        break;
    default:
        system("cls");
        std::cout << "Please enter correct input";
        loading();
        system("cls");
        goto top;
    }
    return 0;
}
