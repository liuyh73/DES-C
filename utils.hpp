#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
using std::string;

class Utils{
public:
	static Utils *getInstance();
	string decimalToBinary(int data);
	string hexadecimalToBinary(char data);
	string strToBinary(string data);
	string strToHex(string data);
	string hexToStr(const string& input);
	string hexstrToBinary(string data);
	string binstrToHex(string data);
	string formatKey(string _key);
	void reverse(string keys[]);

private:
	static Utils *utils;
	Utils();
	~Utils();
};
#endif