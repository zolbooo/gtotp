#include "b32.hpp"

inline int b32toi(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    else
        return 26 + (c - '2');
}
std::vector<uint8_t> b32decode(std::string data) {
    std::vector<uint8_t> result;

    int pad_count = 0;
    while (data[data.length() - 1 - pad_count] == '=')
        ++pad_count;

    int i, index1, index2, index3, index4, index5, index6, index7, index8, len = data.length() - pad_count;
    for (i = 0; i + 7 < len; i += 8) {
        index1 = b32toi(data[i]);
        index2 = b32toi(data[i + 1]);

        result.push_back(index1 << 3 | (index2 & 0b00011100) >> 2);

        index3 = b32toi(data[i + 2]);
        index4 = b32toi(data[i + 3]);
        result.push_back((index2 & 0b00000011) << 6 | (index3 & 0b00011111) << 1 | (index4 & 0b00010000) >> 4);
        
        index5 = b32toi(data[i + 4]);
        result.push_back((index4 & 0b00001111) << 4 | (index5 & 0b00011110) >> 1);

        index6 = b32toi(data[i + 5]);
        index7 = b32toi(data[i + 6]);
        result.push_back((index5 & 0b00000001) << 7 | (index6 & 0b00011111) << 2 | (index7 & 0b00011000) >> 3);

        index8 = b32toi(data[i + 7]);
        result.push_back((index7 & 0b00000111) << 5 | (index8 & 0b00011111));
    }

    switch (pad_count) {
    case 6:
        index1 = b32toi(data[i]);
        index2 = b32toi(data[i + 1]);

        result.push_back(index1 << 3 | (index2 & 0b00011100) >> 2);
        break;
    case 4:
        index1 = b32toi(data[i]);
        index2 = b32toi(data[i + 1]);

        result.push_back(index1 << 3 | (index2 & 0b00011100) >> 2);

        index3 = b32toi(data[i + 2]);
        index4 = b32toi(data[i + 3]);
        result.push_back((index2 & 0b00000011) << 6 | (index3 & 0b00011111) << 1 | (index4 & 0b00010000) >> 4);
        break;
    case 3:
        index1 = b32toi(data[i]);
        index2 = b32toi(data[i + 1]);

        result.push_back(index1 << 3 | (index2 & 0b00011100) >> 2);

        index3 = b32toi(data[i + 2]);
        index4 = b32toi(data[i + 3]);
        result.push_back((index2 & 0b00000011) << 6 | (index3 & 0b00011111) << 1 | (index4 & 0b00010000) >> 4);

        index5 = b32toi(data[i + 4]);
        result.push_back((index4 & 0b00001111) << 4 | (index5 & 0b00011110) >> 1);
        break;
    case 1:
        index1 = b32toi(data[i]);
        index2 = b32toi(data[i + 1]);

        result.push_back(index1 << 3 | (index2 & 0b00011100) >> 2);

        index3 = b32toi(data[i + 2]);
        index4 = b32toi(data[i + 3]);
        result.push_back((index2 & 0b00000011) << 6 | (index3 & 0b00011111) << 1 | (index4 & 0b00010000) >> 4);

        index5 = b32toi(data[i + 4]);
        result.push_back((index4 & 0b00001111) << 4 | (index5 & 0b00011110) >> 1);

        index6 = b32toi(data[i + 5]);
        index7 = b32toi(data[i + 6]);

        result.push_back((index5 & 0b00000001) << 7 | (index6 & 0b00011111) << 2 | (index7 & 0b00010000) >> 4);
        break;
    }

    return result;
}
std::string b32encode(std::vector<uint8_t> data) {
    std::string result;

    int pad_size = 0;
    switch (data.size() % 5) {
    case 1:
        pad_size = 6;
        break;
    case 2:
        pad_size = 4;
        break;
    case 3:
        pad_size = 3;
        break;
    case 4:
        pad_size = 1;
        break;
    }
    for (int i = 0; i < pad_size; i++)
        data.push_back(0);
    
    int i, index2, index3, index4, index5, index6, index7;
    for (i = 0; i + 4 < data.size(); i += 5) {
        result += b32chars[(data[i] & 0b11111000) >> 3];
        
        index2 = (data[i] & 0b00000111) << 2 | (data[i + 1] & 0b11000000) >> 6;
        result += b32chars[index2];

        index3 = (data[i + 1] & 0b00111110) >> 1;
        result += b32chars[index3];

        index4 = (data[i + 1] & 0b00000001) << 4 | (data[i + 2] & 0b11110000) >> 4;
        result += b32chars[index4];

        index5 = (data[i + 2] & 0b00001111) << 1 | (data[i + 3] & 0b10000000) >> 7;
        result += b32chars[index5];

        index6 = (data[i + 3] & 0b01111100) >> 2;
        result += b32chars[index6];

        index7 = (data[i + 3] & 0b00000011) << 3 | (data[i + 4] & 0b11100000) >> 5;
        result += b32chars[index7];

        result += b32chars[data[i + 4] & 0b00011111];
    }

    switch (pad_size) {
    case 6:
        result[result.size() - 1] = '=';
        result[result.size() - 2] = '=';
        result[result.size() - 3] = '=';
        result[result.size() - 4] = '=';
        result[result.size() - 5] = '=';
        result[result.size() - 6] = '=';
        break;
    case 4:
        result[result.size() - 1] = '=';
        result[result.size() - 2] = '=';
        result[result.size() - 3] = '=';
        result[result.size() - 4] = '=';
        break;
    case 3:
        result[result.size() - 1] = '=';
        result[result.size() - 2] = '=';
        result[result.size() - 3] = '=';
        break;
    case 1:
        result[result.size() - 1] = '=';
        break;
    }

    return result;
}