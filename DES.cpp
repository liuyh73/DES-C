#include "DES.hpp"

des::des(string _key):key(_key){
	cipherCode = CipherCode.getInstance();
	utils = Utils.getInstance();
	initialReplace = InitialReplace.getInstance();
	reverseReplace = ReverseReplace.getInstance();
	iteration = Iteration.getInstance();
}
des::~des(){}

string des::Encrypt(string clear_text) {
	return getText(clear_text, key, true);
}

string des::Decrypt(string clear_text) {
	return getText(clear_text, key, false);
}

string getText(string text, string key, bool tag) {
	string keys[17];
	cipherCode.getKeys(key, keys);
	if !tag {
		utils.reverse(keys);
	}
	string text_init_replace = initialReplace.initial_replace(text);
	string R_16_L_16 = iteration.iter(text_init_replace, keys);
	string final_text = reverseReplace.reverse_replace(R_16_L_16);
	return final_text;
}