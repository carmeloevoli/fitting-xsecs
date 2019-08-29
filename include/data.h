#ifndef INCLUDE_DATA_H_
#define INCLUDE_DATA_H_

#include <string>
#include <vector>
#include "channel.h"

class Data {
protected:
	std::vector<double> T;
	std::vector<double> sigma;
	std::vector<double> sigma_err;
	std::vector<std::string> data_ref;
	Channel channel;

public:
	Data() {
	}

	Data(const Channel& ch) :
			channel(ch) {
	}

	virtual ~Data() {
	}

	int get_size() const {
		return T.size();
	}

	double get_T(const int& i) const {
		return T.at(i);
	}

	double get_sigma(const int& i) const {
		return sigma.at(i);
	}

	double get_sigmaerr(const int& i) const {
		return sigma_err.at(i);
	}

	void add_data_from_file(std::string filename);

	double average_relative_error() const;

	void stats() const;

	void print() const;
};

#endif
