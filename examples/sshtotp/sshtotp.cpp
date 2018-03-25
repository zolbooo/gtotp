#include "totp.min.hpp"

#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int main() {
    string twoFactor, secret;
    const char* ssh_addr = getenv("SSH_CONNECTION");

    if (ssh_addr == NULL) //If it's not SSH
        return 0;
    else {
        ifstream secret_file(".ssh/id_totp");
        secret_file >> secret;
        secret_file.close();

        if (secret.length() != 16) {
            cout << "Setting up TOTP..." << endl;
            string password = getpass("Enter password: ");

            ofstream id_totp(".ssh/id_totp");
            secret = totp::generateSecret(password);
            id_totp << secret << endl;
            id_totp.close();


            cout << "Open the following link to generate QR code:" << endl;
            cout << "https://api.qrserver.com/v1/create-qr-code/?size=500x500&data=" 
                << totp::generateURL(secret, getenv("USER"), "sshTOTP", "sshTOTP") << endl;
            cout << "It's recommended to use Google Authenticator application" << endl;
        }

prompt:
        cout << "Enter two-factor key: ";
        cin >> twoFactor;

        if (twoFactor != totp::generateTOTP(secret)) {
            cout << "Try again" << endl;
            goto prompt;
        }
    }

    setenv("SSH_TOTP_VERIFIED", "1", 0);
    system("bash");
    return 0;
}
