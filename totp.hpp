#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include "sha1-hmac.hpp"
#include "b32.hpp"

namespace totp {
    std::string generateSecret(std::string password);
    std::string generate(std::string secret);
};