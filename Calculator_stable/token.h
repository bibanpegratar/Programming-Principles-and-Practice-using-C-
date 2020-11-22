#pragma once
#include "std_lib_facilities.h"
//Token implementation----------------------------------------------------------
class Token {
public:
	char type;
	double value;
	string name;   // used for a Token of type name

	Token(char ch) :type{ ch }, value{ 0 } {};
	Token(char ch, double val) :type{ ch }, value{ val } {};
	Token(char ch, string n) :type{ ch }, name{ n } {};
};
//-------------------------------------------------------------------------------

//Token_stream implementation----------------------------------------------------
class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);

private:
	bool isFull = false;
	Token buffer;
};