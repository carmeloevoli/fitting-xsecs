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
	std::string filename;

public:
	Data() {
	}

	Data(const std::string& _filename) :
			filename(_filename) {
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

	void add_data_from_file();

	double average_relative_error() const;

	void stats() const;

	void print() const;
};

#endif
