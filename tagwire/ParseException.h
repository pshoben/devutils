#ifndef ParseException_H
#define ParseException_H

#include <exception>

class ParseException : public std::exception
{
public:
	ParseException(string text):text(text){}
	string text;
};

#endif
