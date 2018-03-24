# gtotp
Simple to use library for generating TOTP

### Usage
Just:
```c++
#include "totp.hpp"
```

And use functions:
```c++
std::string totp::generateSecret(std::string password);
```
Generating secret using init string or password and encodes it in base32
```c++
std::string totp::generateTOTP(std::string secret, int period = 30, int digits = 6);
```
Generate TOTP using existing secret, also you can define update period and number of digits
```c++
std::string totp::generateURL(std::string secret, std::string username, std::string issuer, std::string application = "");
```
Generate URL using data to make QR code and simplify scan on mobile devices

```c++
int totp::time_until_new_period(int period);
```
Get time in seconds until new period
### Compiling
Go to the gtotp folder and:
```shell
make
```

Copy libtotp.a to your folder and compile it with your project
Also do not forget to install OpenSSL headers by installing libssl-dev package:
```shell
sudo apt-get install libssl-dev
```
And link your project with -lcrypto flag:
```shell
g++ test.cpp libtotp.a -o test -lcrypto
```