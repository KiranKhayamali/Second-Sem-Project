#ifndef user_h
#define user_h
#endif // user
#include <iostream>
#include <conio.h>
#include <cctype>
#include <fstream>
#include <ctype.h>

class account{
    char uname[10];
    char password[10];
public:
    void create_acc();
    void login();
    void check_acc(std::string username, std::string user_password);
};

void account::create_acc(){
    std::ofstream userfile;
    std::string name;
    userfile.open("user.txt", std::ios::app);
    std::cout<<"Create Account:\n";
    std::cout<<"Enter Username(Small alphabets(a-z), numbers(0-9) and underscores(_) can be used, don't use spaces):";
    std::cin>>uname;
    name = uname;
    std::cout<<"Enter password: ";
    char ch;
    for(int i = 0;i < 100;i++){
        ch = getch();
        if(ch == 13){
            break;
        }
        password[i] = ch;
        ch = '*' ;
        std::cout<<ch;
    }
    std::cout<<"\n";

    std::ifstream usercheckfile;
    account u;
    usercheckfile.open("user.txt", std::ios::in);
    int pos, num=0;
    usercheckfile.seekg(0, std::ios::beg);
    while(!usercheckfile.eof()){
        pos = usercheckfile.tellg();
        usercheckfile.read((char*)this, sizeof(u));
        if(uname == name){
            num++;
        }
    }
    if(num>1){
        std::cout<<"This account is already created";
        exit(0);
    }
    //check_acc(uname, password);
    userfile.write((char*)this,sizeof(account));

    userfile.close();
}

void account::login(){
    system("cls");
    label:
    std::cout<<"Login/Signup";
    std::string check;
    //gotoxy(9,7);
    std::cout<<"Do u want to create a new accout(y/n):";
    std::cin>>check;
    if(check == "n"||check=="N"){
        std::cout<<"Login: \n";
        std::cout<<"Uname: ";
        std::cin>>uname;
        std::cout<<"Password: ";
        char ch;
        for(int i = 0;i < 100;i++){
            ch = getch();
            if(ch == 13){
                break;
            }
            password[i] = ch;
            ch = '*' ;
            std::cout<<ch;
        }
        std::cout<<"\n";
        check_acc(uname,password);
    }else if(check == "y"||check == "Y"){
        create_acc();
    }else{
        std::cout<<"Please enter correct input\n";
        goto label;
    }
}

void account::check_acc(std::string username, std::string user_password){
    int flag =0;
    std::fstream checkfile;
    int position;
    checkfile.open("user.txt", std::ios::in|std::ios::binary);
    if(checkfile){
        checkfile.seekg(0, std::ios::beg);
        while(!checkfile.eof()) {
            position=checkfile.tellg();
            checkfile.read((char*)this,sizeof(account));
            if(uname == username && password==user_password){
                std::cout<<"U have logged in successfully \n";
                std::cout<<"Press Enter to Continue";
                getch();
                flag = 1;
                break;
            }
        }
        if(flag==0){
            std::cout<<"Invalid Uname or password\n";
            std::cout<<"Please try again\n";
            getch();
            login();
        }
    }else{
        std::cout<<"No accounts to be found. Please create a new account\n";
        create_acc();
    }
}

