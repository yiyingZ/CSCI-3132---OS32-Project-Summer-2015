#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#include "UI.h"


using namespace std;

class Login {
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

    /*
     * conio getch replacement found online:
     * http://cboard.cprogramming.com/faq-board/27714-faq-there-getch-conio-equivalent-linux-unix.html
     */
    int mygetch() {
        struct termios oldt,
                newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

public:

    std::string login() {

        while (notlog) {
            cout << c_line;
            cout << "Enter username: ";
            cin >> username;

            cin.ignore(1);
            cin.clear();

            cout << c_line;
            cout << "Enter password: ";
            ch = mygetch();
            while (ch != 10) {//character 13 is enter
                password.push_back(ch);
                cout << '*';
                ch = mygetch();
                while (ch == '\b') {
                    cout << "\b \b";
                    ch = mygetch();
                    password.pop_back();
                }
            }

            cout << "\n";

            //

            userAccounts.open("user-accounts.txt");
            if(!userAccounts.is_open()) {
                UI::println("FATAL ERROR: user-accounts.txt not found.");
            }

            while (std::getline(userAccounts, ucheck)) {

                std::getline(userAccounts, pcheck);

                if ((username.compare(ucheck) == 0) && password.compare(pcheck) == 0) {
                    c_line = username + "@OS32> ";
                    cout << c_line;
                    cout << "Login successful! Welcome, " << username << ".\n";
                    notlog = false;
                    cout << message << "\n";
                    loggedin = true;
                    return username;
                }
            }

            if (!loggedin) {
                cout << "Invalid username or password";
                password = "";
            }

            userAccounts.close();

            cout << "\n";

        }

    }
};
