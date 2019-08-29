#ifndef INCLUDE_MINIMIZER_H_
#define INCLUDE_MINIMIZER_H_

#include "chi2.h"
#include <vector>

struct MinimizerResults {
	double minvalue;
	std::vector<double> values;
	std::vector<double> errors;
	size_t size;
};

MinimizerResults Minimizer(const Chi2& chi2, int printlevel);

#endif /* INCLUDE_MINIMIZER_H_ */
