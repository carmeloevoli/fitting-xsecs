#ifndef INCLUDE_MODEL_H_
#define INCLUDE_MODEL_H_

#include "channel.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

double set_threshold_energy(const Channel& channel);
double sigma_1_func(double sigma_1, double xi, double Delta, double T_h, double E_th, double T);
double sigma_0_func(double sigma_0, double M, double Gamma, double E_th, double T);

struct Param {
	std::string name;
	double min;
	double max;
};

class Model {
protected:
	Channel channel;
	std::vector<Param> params;
	double T_h = 2.; // GeV/n
	double E_th = 0;

public:
	Model() {
	}

	Model(const Channel& ch) :
			channel(ch) {
	}

	virtual ~Model() {
	}

	size_t get_nparams() const {
		return params.size();
	}

	Param get_param(size_t i) const {
		auto param = params.at(i);
		return param;
	}

	void print(const std::vector<double>& p, const std::vector<double>& err) const {
		assert(p.size() == params.size());
		std::string filename = "model_";
		filename += channel.string_it();
		filename += ".txt";
		std::ofstream outfile(filename.c_str());
		outfile << "#";
		for (size_t i = 0; i < p.size(); ++i)
			outfile << p.at(i) << " " << err.at(i) << " ";
		outfile << "\n";
		for (double T = 0.01; T < 2e3; T *= 1.01)
			outfile << std::scientific << T << "\t" << get(p, T) << "\n";
		outfile.close();
	}

	virtual void init() = 0;
	virtual double get(const std::vector<double>& p, double T) const = 0;
};

class ModelWithoutResonance: public Model {
public:
	ModelWithoutResonance() {
	}

	ModelWithoutResonance(const Channel& ch) :
			Model(ch) {
	}

	void init() override {
		params.push_back(Param( { "sigma_1", 0, 100 }));
		params.push_back(Param( { "xi", 0, 10 }));
		params.push_back(Param( { "Delta", -2, 2 }));
		E_th = set_threshold_energy(channel);
	}

	double get(const std::vector<double>& p, double T) const override {
		assert(p.size() == params.size());
		return sigma_1_func(p[0], p[1], p[2], T_h, E_th, T);
	}
};

class ModelWithResonance: public Model {
public:
	ModelWithResonance() {
	}

	ModelWithResonance(const Channel& ch) :
			Model(ch) {
	}

	void init() override {
		params.push_back(Param( { "sigma_1", 0, 100 }));
		params.push_back(Param( { "xi", 0, 10 }));
		params.push_back(Param( { "Delta", -2, 2 }));
		params.push_back(Param( { "sigma_0", 0, 100 }));
		params.push_back(Param( { "M", 0, 1 }));
		params.push_back(Param( { "Gamma", 0, 1}));
		E_th = set_threshold_energy(channel);
	}

	double get(const std::vector<double>& p, double T) const override {
		assert(p.size() == params.size());
		double value = sigma_1_func(p[0], p[1], p[2], T_h, E_th, T);
		value += sigma_0_func(p[3], p[4], p[5], E_th, T);
		return value;
	}
};

#endif /* INCLUDE_SIGMA_FUNC_H_ */
