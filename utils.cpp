#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "utils.hpp"
using namespace std;

Utils* Utils::utils = nullptr;

Utils* Utils::getInstance(){
	if(utils == nullptr){
		utils = new Utils();
	}
	return utils;
}
string Utils::decimalToBinary(int data) {
	switch (data) {
		case 0:
			return "0000";
		case 1:
			return "0001";
		case 2:
			return "0010";
		case 3:
			return "0011";
		case 4:
			return "0100";
		case 5:
			return "0101";
		case 6:
			return "0110";
		case 7:
			return "0111";
		case 8:
			return "1000";
		case 9:
			return "1001";
		case 10:
			return "1010";
		case 11:
			return "1011";
		case 12:
			return "1100";
		case 13:
			return "1101";
		case 14:
			return "1110";
		case 15:
			return "1111";
	}
	return "";
}

string Utils::hexadecimalToBinary(char data) {
	switch (data) {
	case '0':
		return "0000";
	case '1':
		return "0001";
	case '2':
		return "0010";
	case '3':
		return "0011";
	case '4':
		return "0100";
	case '5':
		return "0101";
	case '6':
		return "0110";
	case '7':
		return "0111";
	case '8':
		return "1000";
	case '9':
		return "1001";
	case 'a':
		return "1010";
	case 'b':
		return "1011";
	case 'c':
		return "1100";
	case 'd':
		return "1101";
	case 'e':
		return "1110";
	case 'f':
		return "1111";
	}
	return "";
}

void Utils::reverse(string keys[]){
	for(int i=0;i<8;i++){
		string temp = keys[i];
		keys[i] = keys[15-i];
		keys[15-i] = temp;
	}
}

string Utils::strToBinary(string data){
	string binary = "";
	for(int i=0;data[i];i++){
		unsigned char k = 0x80;
		for(int i=0;i<8;i++, k>>=1){
			if(data[i]&k){
				binary+="1";
			} else {
				binary+="0";
			}
		}
	}
	return binary;
}

string Utils::strToHex(string data){
	string hexadecimal = "", tmp;
	stringstream ss;
	for(int i=0;i<data.length();i++){
		ss<<hex<<int(data[i])<<std::endl;
		ss>>tmp;
		hexadecimal+=tmp;
	}
	return hexadecimal;
}

string Utils::hexToStr(const string& input)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();
    if (len & 1) throw invalid_argument("odd length");

    string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

// 另外一种方法 strToHex
// std::string string_to_hex(const std::string& input)
// {
//     static const char* const lut = "0123456789abcdef";
//     size_t len = input.length();

//     std::string output;
//     output.reserve(2 * len);
//     for (size_t i = 0; i < len; ++i)
//     {
//         const unsigned char c = input[i];
//         output.push_back(lut[c >> 4]);
//         output.push_back(lut[c & 15]);
//     }
//     return output;
// }

string Utils::hexstrToBinary(string data) {
	string binStr = "";
	for(int i=0;i<data.length();i++){
		binStr+=hexadecimalToBinary(data[i]);
	}
	return binStr;
}

string Utils::binstrToHex(string data){
	string hexStr = "";
	static const char* const lut = "0123456789abcdef";
	for(int i=0;i<data.length()/4;i++){
		hexStr += lut[std::stoi(data.substr(i*4, 4).c_str(), 0, 2)];
	}
	return hexStr;
}

string Utils::formatKey(string _key){
	return hexstrToBinary(strToHex(_key));
}

Utils::Utils(){}
Utils::~Utils(){
	delete utils;
}