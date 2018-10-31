#ifndef INITIAL_REPLACE_HPP
#define INITIAL_REPLACE_HPP
#include <iostream>
using std::string;
class InitialReplace {
public:
	static InitialReplace* getInstance();
	string IP(string clear_text);
private:
	InitialReplace();
	~InitialReplace();
	static InitialReplace* initialReplace;
};
#endif