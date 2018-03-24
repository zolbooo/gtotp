#include "totp.hpp"

std::string totp::generateSecret(std::string password) {
    auto digest = b32encode(sha1_hmac(password, std::to_string(time(NULL))));

    return std::string(digest.begin(), digest.begin() + 16);
}
std::string totp::generateTOTP(std::string secret, int period, int digits) {
    auto key = b32decode(secret);

    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    long message = ms.count() / 1000 / period;

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
    
    int mod = 1, tmp = digits;
    while (tmp--)
        mod *= 10;
    value %= mod;

    std::string result = std::to_string(value);
    while (result.length() != digits)
        result = '0' + result;

    return result;
}
std::string totp::generateURL(std::string secret, std::string username, std::string issuer, std::string application) {
    return "otpauth://totp/" + (application.empty() ? issuer : application) + ":%2520" + username + "?secret=" + secret + "&issuer=" + issuer;
}

int totp::time_until_new_period(int period) {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    long _time = ms.count() / 1000 % period;

    return 30 - _time;
}