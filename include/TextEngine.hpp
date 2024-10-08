#ifndef TEXTENGINE_HPP
#define TEXTENGINE_HPP

#include "Define.hpp"

#include <iostream>

namespace TextEngine
{
	std::ostream	&red(C_STR_REF text, std::ostream &os);
	std::ostream	&green(C_STR_REF text, std::ostream &os);

	std::ostream	&yellow(C_STR_REF text, std::ostream &os);

	std::ostream	&blue(C_STR_REF text, std::ostream &os);

	std::ostream	&magenta(C_STR_REF text, std::ostream &os);

	std::ostream	&cyan(C_STR_REF text, std::ostream &os);

	std::ostream	&white(C_STR_REF text, std::ostream &os);

	std::ostream	&bold(C_STR_REF text, std::ostream &os);

	std::ostream	&underline(C_STR_REF text, std::ostream &os);

	std::ostream	&reset(C_STR_REF text, std::ostream &os);

	std::ostream	&print(C_STR_REF text, std::ostream &os);
	std::ostream	&printTime(std::ostream &os);
}

#endif
