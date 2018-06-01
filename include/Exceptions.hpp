//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#ifndef EXCEPTIONS_HPP_
# define EXCEPTIONS_HPP_

#include <string>
#include <exception>

class BomberWaveException : public std::exception
{
public:
	BomberWaveException(std::string const &message);
	const char *what() const noexcept;
private:
	std::string _message;
};

class InitialisationException : public BomberWaveException
{
public:
	InitialisationException(std::string const &message);
};

#endif /* !EXCEPTIONS_HPP_ */
