#include <openssl/hmac.h>
#include <cstring>

#include <string>
#include <vector>

const int hmac_size = 20;
 
std::vector<uint8_t> sha1_hmac(std::string key, std::string message);
std::vector<uint8_t> sha1_hmac(std::vector<uint8_t> key, std::vector<uint8_t> message);