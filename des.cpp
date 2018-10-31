#include "des.hpp"
#include <iostream>
#include <cstdio>
using std::string;
using std::cerr;
using std::endl;
des::des(string _key){
	cipherCode = CipherCode::getInstance();
	utils = Utils::getInstance();
	initialReplace = InitialReplace::getInstance();
	reverseReplace = ReverseReplace::getInstance();
	iteration = Iteration::getInstance();
	if(_key.length() != 8) {
		cerr << "密钥长度应该为8" <<endl;
		exit(0);
	}
	key = utils->formatKey(_key);
}
des::~des(){}

string des::getText(string text, string key, bool tag) {
	string keys[17];
	cipherCode->getKeys(key, keys);
	if(!tag) {
		utils->reverse(keys);
	}
	string text_init_replace, R_16_L_16, final_text = "";
	for(int i=0;i<text.length()/16;i++){
		text_init_replace = initialReplace->IP(utils->hexstrToBinary(text.substr(i*16, 16)));
		R_16_L_16 = iteration->F(text_init_replace, keys);
		final_text +=  utils->binstrToHex(reverseReplace->RP(R_16_L_16));
	}
	return final_text;
}

string des::Encrypt(string clear_text) {
	int extra = 8 - clear_text.length() % 8;
	for(int i=0;i<extra;i++){
		clear_text+=char(extra+'0');
	}
	string clear_text_hex = utils->strToHex(clear_text);
	return getText(clear_text_hex, key, true);
}

string des::Decrypt(string cipher_text) {
	string cipher_text_hex = getText(cipher_text, key, false);
	string clear_text = utils->hexToStr(cipher_text_hex);
	return clear_text.substr(0, clear_text.length()-(clear_text[clear_text.length()-1] - '0'));
}
