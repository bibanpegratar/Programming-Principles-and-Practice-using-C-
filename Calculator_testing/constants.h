#pragma once
#include <string>
namespace Constants
{
	//Constant declarations and initializations-------------------------------------
	const char number = '8';    //representation of a number type for a Token
	const char sroot = 'S';
	const char let = 'L';       //represents the "let" term in declaration()
	const char name = 'a';      //name token
	const char power = 'P';
	const char vconst = 'C';

	const std::string decl_key = "let";   //declaration keyword
	const std::string sroot_key = "sqrt";    //keyword for calling sqare_root() function
	const std::string power_key = "pow";     //keyword for calling power() function
	const std::string constant_key = "const";

	const char quit_key = '@';
	const char print_key = ';';
	const char help_key = '$';
	const char show_vars = '&';

	const std::string prompt = ">>";
	const std::string result = "=";      //used to indicate that what follows is a result
	const char recover = '~'; //used as an argument for the keep_window_open() functions in catch statements
   //------------------------------------------------------------------------------
}