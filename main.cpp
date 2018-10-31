#include <iostream>
#include "des.hpp"
#include <string>
string key = "1101001010110101100110110111011110011001111010001101111001110110";
string clear_text = "1111111011011100101110101001100001110110010101000011001000010000";
int main(){
	des *desInstance = new des(key);
	string cipher_text = desInstance->Encrypt(clear_text);
	printf("%s\n", cipher_text);

	delete desInstance;
}