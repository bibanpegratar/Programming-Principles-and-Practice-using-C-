#pragma once
// forward declarations
//class Token_stream;
//class Symbol_table;
#include "token.h"

//Declarations and Initializations-----------------------------------------------
void calculate(Token_stream& ts, Symbol_table& st);
double statement(Token_stream& ts, Symbol_table& st);
double declaration(Token_stream& ts, Symbol_table& st);
double square_root(Token_stream& ts, Symbol_table& sts);
double powerf(Token_stream& ts, Symbol_table& st);
double expression(Token_stream& ts, Symbol_table& st);
double term(Token_stream& ts, Symbol_table& st);
double factorial(Token_stream& ts, Symbol_table& st);
double primary(Token_stream& ts, Symbol_table& st);
double variable(Token_stream& ts, Symbol_table& st);
void intro_message();
void cleanup(Token_stream&);
//-------------------------------------------------------------------------------

