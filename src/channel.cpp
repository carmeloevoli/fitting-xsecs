#include "channel.h"
#include <cassert>
#include <iostream>

Channel::Channel() {
}

Channel::~Channel() {
}

Channel::Channel(size_t proj_A, size_t proj_Z, size_t frag_A, size_t frag_Z) {
	assert(proj_A == 0 || proj_A >= proj_Z);
	assert(frag_A == 0 || frag_A >= frag_Z);
	this->proj_A = proj_A;
	this->proj_Z = proj_Z;
	this->frag_A = frag_A;
	this->frag_Z = frag_Z;
}

void Channel::read_from_input(char *argv[]) {
	proj_A = atoi(argv[1]);
	proj_Z = atoi(argv[2]);
	frag_A = atoi(argv[3]);
	frag_Z = atoi(argv[4]);
}

void Channel::print() const {
	std::cout << "channel read : ";
	std::cout << "(" << proj_A << "," << proj_Z << ") -> (" << frag_A << "," << frag_Z << ")\n";
}
