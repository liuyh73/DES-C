#include "des.hpp"
#include <iostream>
using std::string;
des::des(string _key):key(_key){
	cipherCode = CipherCode::getInstance();
	utils = Utils::getInstance();
	initialReplace = InitialReplace::getInstance();
	reverseReplace = ReverseReplace::getInstance();
	iteration = Iteration::getInstance();
}
des::~des(){}

string des::getText(string text, string key, bool tag) {
	string keys[17];
	cipherCode->getKeys(key, keys);
	if(!tag) {
		utils->reverse(keys);
	}
	string text_init_replace = initialReplace->IP(text);
	string R_16_L_16 = iteration->F(text_init_replace, keys);
	string final_text = reverseReplace->RP(R_16_L_16);
	return final_text;
}

string des::Encrypt(string clear_text) {
	return getText(clear_text, key, true);
}

string des::Decrypt(string clear_text) {
	return getText(clear_text, key, false);
}
