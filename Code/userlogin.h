#include<string>
#include<fstream>
#include<iostream>
#include <iomanip>
using namespace std;
class Login {
private:
    string Username;
    string Password;
    string Role;
public:
    Login() {
        Username = "";
        Password = "";
        Role = " ";

    }
    Login(string U, string P, string R) {
        Username = U;
        Password = P;
        Role = R;

    }
    void setUsername(string U) {
        Username = U;
    }
    string getUsername() {
        return Username;
    }
    void setPassword(string P) {
        Password = P;
    }
    string getPassword() {
        return Password;
    }

    void signUp() {
        fstream Log;
        Log.open("Files\\logindata.txt", ios::app);
        cout << "Enter username(Max 6 characters): ";
        cin >> Username;
        cout << "Enter Password(Max 6 characters): ";
        cin >> Password;

        if (Log.is_open()) {

            Log << left << setw(10) << Username;
            Log << left << setw(10) << Password << endl;


        }
        Log.close();
        cout << endl;
        cout << "You are successfully Signed up!" << endl;

    }

    bool  signIn(string un, string pw)
    {
        ifstream Log;
        Log.open("Files\\logindata.txt", ios::in);
        while (!Log.eof())
        {
            Log >> Username >> Password;

            if (un == Username && pw == Password)
            {

                cout << "Welcome User!" << endl;
                return 1;
            }




        }

        Log.close();
        cout << "Invalid Username or Password!" << endl;
        return 0;
    }

    int menu() {
        int op;
        string username, password;

        do {
            cout << endl;
            cout << "----------------LOGIN MENU----------------" << endl;
            cout << endl;
            cout << "     Press 1 to Sign up." << endl;
            cout << "     Press 2 to Sign in." << endl;
            cout << "     Press 0 to exit." << endl;
            cout << endl;
            cout << "-------------------------------------------" << endl;
            cout << "Your choice :";
            cin >> op;
            switch (op) {
            case 1:
                signUp();
                system("pause");

                break;
            case 2:
                cout << "Enter Username :" << endl;
                cin >> username;
                cout << "Enter Password :" << endl;
                cin >> password;
                signIn(username, password);
                system("pause");

                break;


            }
        } while (op != 0);
        return 0;
    }


};
