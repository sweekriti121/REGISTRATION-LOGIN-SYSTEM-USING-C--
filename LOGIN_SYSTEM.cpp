#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool isLoggedIn()
{
    string username, password, us, pw;
    // login
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream in("Login&register.txt");
    // searching and matching login id
    while (in)
    {
        in >> us;
        // cout << us;
        if (us == username)
        {
            in >> pw;
            // cout << pw;
            if (pw == password)
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            continue;
        }
        us = "";
        pw = "";
    }
}
bool isRegistered(string r)
{
    string r1;
    ifstream in2("Login&register.txt");
    // searching and matching username registered or not
    while (in2)
    {
        in2 >> r1;
        // cout << us;
        if (r1 == r)
        {
            return true;
        }
        else
        {
            continue;
        }
        r1 = "";
    }
    return false;
}
int main()
{
    int option, uc_count = 0, lc_count = 0, num_count = 0, naplha_count = 0;
    cout << "Enter 1: Register" << endl
         << "Enter 2: Login" << endl
         << "Enter 3: Delete account" << endl
         << "Enter 4: Close"<<endl;
    cout << "Enter option: ";
    cin >> option;
    int attempt = 2; // locking after 3 attempts
    if (option == 1)
    {
        // register
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        bool registered = isRegistered(username);
        if (registered)
        {
            cout << "Already registered..No need to register again!" << endl;
            main();
        }
        else
        {

            int length = password.size();
            for (int i = 0; i < password.size(); i++)
            {
                char c = password.at(i);
                if (isupper(c))
                    uc_count++;
                else if (islower(c))
                    lc_count++;
                else if (isdigit(c))
                    num_count++;
                else
                    naplha_count++;
            }
            if (length < 8)
            {
                cout << "Password must be at least 8 characters in length" << endl;
                if (uc_count < 1)
                    cout << "Password Must contain at least one English uppercase character (A through Z)" << endl;
                if (lc_count < 1)
                    cout << "Password Must contain at least one English lowercase character (a through z)" << endl;
                if (num_count < 1)
                    cout << "Password Must contain at least one Base 10 digit (0 through 9)" << endl;
                if (naplha_count < 1)
                    cout << "Password Must contain one non-alphanuneric character (e.g., @, !, $, #, %)" << endl;
            }
            else
            {
                cout << "Successfully Registered!" << endl;
                ofstream out;
                // open file in append mode without starting with nextline
                out.open("Login&register.txt", ios::out | ios::app);
                out << username << " " << password << endl;
                out.close();
            }

            main();
        }
    }
    else if (option == 2)
    {
        bool status = isLoggedIn();
        if (!status)
        {

            if (attempt != 0)
            {
                int x;
                cout << "Invalid Login Credentials!" << endl;
                cout << "Do you want to retry? 1 for YES and 0 for NO." << endl;
                cin >> x;
                if (x)
                {
                    cout << attempt << " attempt(s) left!" << endl;
                    attempt--;
                    main();
                }
            }
            else
            {
                cout << "All your attempts are exhausted!";
                return 0;
            }
        }
        else
        {
            cout << "Successfully Logged In!" << endl;
            return 1;
        }
    }
    // deleting
    else if (option == 3)
    {
        string username;
        string password;
        string us, pw;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        bool user = isRegistered(username);
        bool pass = isRegistered(password);
        if (user && pass)
        {
            string deleteline = username + " " + password;
            string line;
            ifstream fin;
            fin.open("Login&register.txt");
            ofstream temp;
            temp.open("temp.txt");
            while (getline(fin, line))
            {
                // write all lines to temp other than the line marked for erasing
                if (line != deleteline)
                    temp << line << endl;
            }

            cout << "Account deleted!" << endl;
            temp.close();
            fin.close();
            remove("Login&register.txt");
            rename("temp.txt", "Login&register.txt");
        }
        else
        {
            cout << "Account doesn't exist!" << endl;
        }
        main();
    }
}
