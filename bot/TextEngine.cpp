#include <iostream>
#include <string>
#include "TextEngine.hpp"
#include "Utils.hpp"

std::ostream &TextEngine::red(C_STR_REF text, std::ostream &os)
{
	os << "\033[31m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::green(C_STR_REF text, std::ostream &os)
{
	os << "\033[32m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::yellow(C_STR_REF text, std::ostream &os)
{
	os << "\033[33m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::blue(C_STR_REF text, std::ostream &os)
{
	os << "\033[34m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::magenta(C_STR_REF text, std::ostream &os)
{
	os << "\033[35m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::cyan(C_STR_REF text, std::ostream &os)
{
	os << "\033[36m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::white(C_STR_REF text, std::ostream &os)
{
	os << "\033[37m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::bold(C_STR_REF text, std::ostream &os)
{
	os << "\033[1m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::underline(C_STR_REF text, std::ostream &os)
{
	os << "\033[4m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::reset(C_STR_REF text, std::ostream &os)
{
	os << "\033[0m" << text << "\033[0m";
	return os;
}
std::ostream &TextEngine::print(C_STR_REF text, std::ostream &os)
{
	os << text;
	return os;
}

std::ostream	&TextEngine::printTime(std::ostream &os){
	TextEngine::yellow("[ " + Utils::getTime() + " ] ", os);
	return os;
}