#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
using std::string;

class Utils{
public:
	static Utils *getInstance();
	string decimalToBinary(int data);
	string hexadecimalToBinary(char data);

	void reverse(string keys[]);
private:
	static Utils *utils;
	Utils();
	~Utils();
};
#endif