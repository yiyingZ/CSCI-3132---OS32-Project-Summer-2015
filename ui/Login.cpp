#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

class Login
{
    string username = "";
    string password = "";
    string ucheck;
    string pcheck;
    string c_line = "OS32> ";
    char ch;
    bool notlog = true;
    bool loggedin = false;
    string message = "Message of the day: If you're reading this, you've been in a coma for almost 20 years now, we're trying a new technique. We don't know where this message will end up in your dream, but we hope we're getting through. Please wake up! We miss you.";
    ifstream userAccounts;

public:

    void login(){

        while(notlog){
            cout << c_line;
            cout << "Enter username: ";
            cin >> username;

            cout << c_line;
            cout << "Enter password: ";
            ch = _getch();
            while(ch != 13){//character 13 is enter
                password.push_back(ch);
                cout << '*';
                ch = _getch();
                while(ch == '\b'){
                    cout << "\b \b";
                    ch = _getch();
                    password.pop_back();
                }
            }

            cout << "\n";

            //

            userAccounts.open("OS32/systems/account/user-accounts.txt");

            while(std::getline(userAccounts, ucheck)){

                std::getline(userAccounts, pcheck);

                if((username.compare(ucheck) == 0) && password.compare(pcheck) == 0){
                    c_line = username + "@OS32> ";
                    cout << c_line;
                    cout << "Login successful! Welcome, " << username << ".\n";
                    notlog = false;
                    cout << message << "\n";
                    loggedin = true;
                    break;
                }
            }

            if(!loggedin){
                cout << "Invalid username or password";
                password = "";
            }

            userAccounts.close();

            cout << "\n";

        }

    }
};
