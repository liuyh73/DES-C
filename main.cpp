#include <iostream>
#include "des.hpp"
#include <string>
using std::cin;
using std::cout;
using std::endl;
string key; 
string clear_text;
int main(){
	cout<<"输入密钥：";
	cin >> key;
	cout<<"输入明文：";
	cin >> clear_text;
	des* desInstance = new des(key);
	string cipher_text = desInstance->Encrypt(clear_text);
	cout<<"加密后的密文："<<cipher_text<<endl;
	string plain_text = desInstance->Decrypt(cipher_text);
	cout<<"解密后的明文："<<plain_text<<endl;
	cout<<"clear_text == plain_text: "<<(clear_text == plain_text ? "true" : "false")<<endl;
	delete desInstance;
}