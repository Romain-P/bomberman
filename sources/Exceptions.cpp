//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "Exceptions.hpp"

BomberWaveException::BomberWaveException(std::string const &message){
}

const char *BomberWaveException::what() const noexcept {
	return (_message.data());
}

InitialisationException::InitialisationException(std::string const &message) : BomberWaveException(message) {
}


