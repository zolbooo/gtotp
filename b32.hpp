#include <string>
#include <vector>

const std::string b32chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567=";

std::vector<uint8_t> b32decode(std::string data);
std::string b32encode(std::vector<uint8_t> data);