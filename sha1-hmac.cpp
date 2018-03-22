#include "sha1-hmac.hpp"

std::vector<uint8_t> sha1_hmac(std::string key, std::string message) {
    unsigned char* hmac_ptr = HMAC(EVP_sha1(), (const unsigned char*)key.c_str(), key.length(), 
        (const unsigned char*)message.c_str(), message.length(), NULL, NULL);

    std::vector<uint8_t> result(hmac_size);
    for (int i = 0; i < hmac_size; i++)
        result[i] = hmac_ptr[i];

    return result;
}

std::vector<uint8_t> sha1_hmac(std::vector<uint8_t> key, std::vector<uint8_t> message) {
    int key_size = key.size();
    int msg_size = message.size();

    uint8_t *key_ptr = new uint8_t[key_size];
    for (int i = 0; i < key_size; i++)
        key_ptr[i] = key[i];
    uint8_t *msg_ptr = new uint8_t[msg_size];
    for (int i = 0; i < msg_size; i++)
        msg_ptr[i] = message[i];

    unsigned char* hmac_ptr = HMAC(EVP_sha1(), key_ptr, key_size, msg_ptr, msg_size, NULL, NULL);

    std::vector<uint8_t> result(hmac_size);
    for (int i = 0; i < hmac_size; i++)
        result[i] = hmac_ptr[i];

    delete[] key_ptr;
    delete[] msg_ptr;

    return result;
}