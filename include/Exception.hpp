#pragma once

#include <stdexcept>
#include <string>
#include "Define.hpp"
#include <vector>
using namespace std;

class Exception : public std::exception
{
	public:
		Exception(C_STR_REF message) : message(message) {}
		virtual const char* what() const throw()
		{
			return message.c_str();
		}
		virtual ~Exception() throw() {}
	private:
		std::string message;
};
