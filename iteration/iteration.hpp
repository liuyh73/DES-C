#ifndef ITERATION_HPP
#define ITERATION_HPP
#include <iostream>
#include <string>
#include "../utils/utils.hpp"
using std::string;

class Iteration
{
public:
	static Iteration *getInstance();
	string F(string clear_text_init_replace, string keys[]);
	string extendReplacement(string R_K);
	string xorWithKeys_K(string R_extended, string keys_K);
	string sBoxTransfer(string R_extended_xor);
	string pBoxTransfer(string R_extended_xor_S_trans);
	string xorWithL_K(string R_extended_xor_S_P_trans, string L_K);
	int getRow(char num1, char num2);
	int getColumn(string column);
private:
	static Iteration *iter;
	Utils *utils;
	Iteration();
	~Iteration();
};
#endif