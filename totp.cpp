#include "totp.hpp"

std::string totp::generateSecret(std::string password) {
    auto digest = b32encode(sha1_hmac(password, std::to_string(time(NULL))));

    return std::string(digest.begin(), digest.begin() + 16);
}
std::string totp::generate(std::string secret) {
    auto key = b32decode(secret);
    auto message = time(NULL) / 30;

    std::vector<uint8_t> msg(sizeof(message));
    for (int i = sizeof(message) - 1; i >= 0; --i) {
        msg[i] = message & 0xFF;
        message >>= 8;
    }

    auto digest = sha1_hmac(key, msg);
    int offset = digest[digest.size() - 1] & 0xF;

    int value = (digest[offset] & 0x7F) << 24;
    value |= (digest[offset + 1] & 0xFF) << 16;
    value |= (digest[offset + 2] & 0xFF) << 8;
    value |= (digest[offset + 3] & 0xFF);
    
    const int mod = 1000000;
    value %= mod;

    std::string result = std::to_string(value);
    if (result.length() != 6)
        result = '0' + result;

    return result;
}