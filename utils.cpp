#include <iostream>
#include "utils.hpp"
using std::string;
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
Utils::Utils(){}
Utils::~Utils(){
	delete utils;
}