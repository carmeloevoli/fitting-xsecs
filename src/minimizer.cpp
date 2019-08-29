#include "minimizer.h"
#include "Math/IFunction.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"

#include <string>
#include <iostream>
#include <random>

class RNG {
private:
	std::uniform_real_distribution<double> dis;
	std::mt19937 gen;
public:
	RNG(double lower = 0.0, double upper = 1.0) :
			gen(std::random_device()()), dis(lower, upper) {
	}
	double get() {
		double random = dis(gen);
		return random;
	}
};

MinimizerResults Minimizer(const Chi2& chi2, int printlevel) {

	auto nparams = chi2.get_nparams();
	RNG rng;

	const char * algoName = ""; // use default (i.e. migrad)

	ROOT::Math::Minimizer* min = new ROOT::Minuit2::Minuit2Minimizer(algoName);

	int MaxFunctionCalls = 100000;
	min->SetMaxFunctionCalls(MaxFunctionCalls);
	min->SetTolerance(0.01);
	min->SetPrintLevel(printlevel);

	ROOT::Math::Functor f(chi2, nparams);

	min->SetFunction(f);
	for (size_t i = 0; i < nparams; ++i) {
		auto param = chi2.get_param(i);
		double starting = param.min + rng.get() * (param.max - param.min);
		min->SetLimitedVariable(i, param.name, starting, starting * 0.1, param.min, param.max);
	}

	min->Minimize();
	assert(min->NCalls() < MaxFunctionCalls);

	const double *xs = min->X();
	const double *errors = min->Errors();
	double minValue = min->MinValue();

	std::vector<double> values;
	for (size_t i = 0; i < nparams; ++i)
		values.push_back(xs[i]);

	std::vector<double> value_errors;
	for (size_t i = 0; i < nparams; ++i)
		value_errors.push_back(errors[i]);

	MinimizerResults out = { minValue, values, value_errors, nparams };
	return out;
}

//	int printLevel = 0;
//
// Parse command line arguments
//	for (int i = 1; i < argc; i++) {
//		std::string arg = argv[i];
//
//		if (arg == "-v") {
//			printLevel = 1;
//		} else if (arg == "-vv") {
//			printLevel = 2;
//		} else if (arg == "-vvv") {
//			printLevel = 3;
//		} else if (arg == "-n") {
//			std::cout << "using method " << argv[i + 1] << " to minimize" << std::endl;
//			algoName = argv[++i];
//		} else if (arg == "-h") {
//			std::cout << "usage: demoMinimize [ options ] " << std::endl;
//			std::cout << "" << std::endl;
//			std::cout
//					<< "       -n <algorithm> : use given algorithm (possible names: simplex, minimize, scan, fumili)"
//					<< std::endl;
//			std::cout << "     -v    : set minimul verbose mode to show final result"
//					<< std::endl;
//			std::cout
//					<< "       -vv   : set medium verbose mode: show function value and edm at each minimization step"
//					<< std::endl;
//			std::cout
//					<< "       -vvv  : set very verbose mode: show full result at each minimization step"
//					<< std::endl;
//			return 0;
//		}
//	}
