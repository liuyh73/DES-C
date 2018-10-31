#include <iostream>
#include "cipher_code.cpp"
#include "utils.cpp"
#include "initial_replace.cpp"
#include "reverse_replace.cpp"
#include "iteration.cpp"
using std::string;
class des {
public:
	des(string _key);
	~des();
	string Encrypt(string clear_text, key);
	string Decrypt(string ciper_text, key);
private:
	string key;
	CipherCode *cipherCode;
	Utils *utils;
	InitialReplace *initialReplace;
	ReverseReplace *reverseReplace;
	Iteration *iteration;
};