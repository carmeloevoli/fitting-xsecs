#ifndef INCLUDE_CHANNEL_H_
#define INCLUDE_CHANNEL_H_

#include <iostream>
#include <sstream>

class Channel {
protected:
	size_t proj_A = 0;
	size_t proj_Z = 0;
	size_t frag_A = 0;
	size_t frag_Z = 0;

public:
	Channel();
	Channel(size_t proj_A, size_t proj_Z, size_t frag_A, size_t frag_Z);
	virtual ~Channel();
	void read_from_input(char *argv[]);
	void print() const;

	bool operator==(const Channel& rhs) const {
		bool value = true;
		if (proj_A != rhs.proj_A || proj_Z != rhs.proj_Z)
			value = false;
		if (frag_A != rhs.frag_A || frag_Z != rhs.frag_Z)
			value = false;
		return value;
	}

	std::string string_it() const {
		std::stringstream sstream;
		sstream << proj_A << "_" << proj_Z << "_" << frag_A << "_" << frag_Z;
		std::string out = sstream.str();
		return out;
	}
};

#endif /* INCLUDE_CHANNEL_H_ */
