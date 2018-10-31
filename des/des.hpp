#ifndef DES_HPP
#define DES_HPP
#include <iostream>
#include "../cipher_code/cipher_code.hpp"
#include "../initial_replace/initial_replace.hpp"
#include "../reverse_replace/reverse_replace.hpp"
#include "../iteration/iteration.hpp"
#include "../utils/utils.hpp"
using std::string;
class des {
public:
	des(string _key);
	~des();
	string Encrypt(string clear_text);
	string Decrypt(string ciper_text);
	string getText(string text, string key, bool tag);
private:
	string key;
	CipherCode *cipherCode;
	Utils *utils;
	InitialReplace *initialReplace;
	ReverseReplace *reverseReplace;
	Iteration *iteration;
};
#endif