#include "data.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>

void Data::add_data_from_file() {
	std::ifstream infile(filename, std::ios::in);
	assert(infile.is_open());
	infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	double data[3];
	size_t counter = 0;
	while (infile >> data[0] >> data[1] >> data[2]) {
		T.push_back(data[0]);
		sigma.push_back(data[1]);
		if (data[2] / data[1] > 0.1)
			sigma_err.push_back(data[2]);
		else
			sigma_err.push_back(0.1 * data[1]);
		counter++;
	}
	infile.close();
}

double Data::average_relative_error() const {
	double value = 0;
	for (size_t i = 0; i < T.size(); ++i)
		value += sigma_err.at(i) / sigma.at(i);
	return value / (double) T.size();
}

void Data::stats() const {
	std::cout << "number of data points : " << T.size() << "\n";
	if (T.size() > 0) {
		std::cout << "min energy : " << *std::min_element(T.begin(), T.end()) << " GeV/n\n";
		std::cout << "max energy : " << *std::max_element(T.begin(), T.end()) << " GeV/n\n";
		std::cout << "max sigma : " << *std::max_element(sigma.begin(), sigma.end()) << " mb\n";
		std::cout << "average relative error : " << average_relative_error() * 100. << "%\n";
	}
}

void Data::print() const {
	std::string filename = "data";
	filename += ".txt";
	std::ofstream outfile(filename.c_str());
	outfile << "#\n";
	for (size_t i = 0; i < T.size(); ++i) {
		outfile << T[i] << " " << sigma[i] << " " << sigma_err[i] << "\n";
	}
	outfile.close();
}
