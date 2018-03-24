#include "totp.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

using namespace std;

int main() {
    char action;
    string login, in_login, password, phash, twoFactorKey, secret;
    ofstream passwd_reg("passwd", ios::app);
    ifstream passwd_log;

start:
    cout << "Enter action(h for help): ";
    cin >> action;

    switch (action) {
    case 'r':
        cout << "Enter login: ";
        cin >> login;

        password = getpass("Enter password: ");
        secret = totp::generateSecret(password);

        cout << totp::generateURL(secret, login, "totpapi", "Test%20application") << endl;

        passwd_reg << login << ' ' << secret << endl;
        break;
    case 'g':
        secret = getpass("Enter secret: ");
        cout << "Your code is: " << totp::generateTOTP(secret) << endl;
        break;
    case 'l':
        passwd_log.open("passwd");

        cout << "Enter login: ";
        cin >> in_login;

        while (!passwd_log.eof() && login != in_login)
            passwd_log >> login >> phash >> secret;

        cout << "Enter Guard code: ";
        cin >> twoFactorKey;

        if (twoFactorKey != totp::generateTOTP(secret)) {
            cout << "Login failed" << endl;
            goto start;
        }
        cout << "Success" << endl;

        passwd_log.close();
        break;
    case 'h':
        cout << "r - Register and get secret" << endl;
        cout << "g - Generate new Guard code" << endl;
        cout << "l - Login into account" << endl;
        break;
    };
    goto start;

    return 0;
}