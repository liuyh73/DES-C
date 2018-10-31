#ifndef REVERSE_REPLACE_HPP
#define REVERSE_REPLACE_HPP
#include <iostream>
using std::string;
class ReverseReplace
{
public:
	static ReverseReplace *getInstance();
	string RP(string R_16_L_16);
private:
	static ReverseReplace *reverseReplace;
	ReverseReplace();
	~ReverseReplace();
};

#endif