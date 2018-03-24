#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include "sha1-hmac.hpp"
#include "b32.hpp"

namespace totp {
    std::string generateSecret(std::string password);
    std::string generateTOTP(std::string secret, int period = 30, int digits = 6);

    std::string generateURL(std::string secret, std::string username, std::string issuer, std::string application = "");

    int time_until_new_period(int period);
};