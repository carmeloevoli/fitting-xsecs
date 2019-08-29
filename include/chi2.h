#ifndef INCLUDE_CHI2_H_
#define INCLUDE_CHI2_H_

#include "data.h"
#include "model.h"
#include <cmath>

class Chi2 {
protected:
	std::shared_ptr<Data> data;
	std::shared_ptr<Model> model;

public:
	Chi2() {
	}

	Chi2(const std::shared_ptr<Data> data_, const std::shared_ptr<Model> model_) :
			model(model_), data(data_) {
	}

	virtual ~Chi2() {
	}

	size_t get_nparams() const {
		return model->get_nparams();
	}

	Param get_param(size_t i) const {
		auto param = model->get_param(i);
		return param;
	}

	double operator()(const double * x) const {
		std::vector<double> p;
		for (size_t i = 0; i < model->get_nparams(); ++i)
			p.push_back(x[i]);
		double chi2 = 0;
		for (size_t i = 0; i < data->get_size(); ++i) {
			double dchi2 = (data->get_sigma(i) - model->get(p, data->get_T(i)))
					/ data->get_sigmaerr(i);
			chi2 += dchi2 * dchi2;
		}
		return chi2;
	}
};

#endif /* INCLUDE_CHI2_H_ */
