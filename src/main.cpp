#include <iostream>
#include <string>
#include "channel.h"
#include "chi2.h"
#include "data.h"
#include "minimizer.h"

int main(int argc, char *argv[]) {
	if (argc == 4) {
		std::string filename = argv[1];
		bool addResonance = atoi(argv[2]);
		double E_th = atof(argv[3]);

		std::cout << "reading data from " << filename << "\n";
		std::cout << "assuming resonance : " << std::boolalpha << addResonance << "\n";
		std::cout << "threshold energy : " << E_th << " GeV/n" << "\n";

		auto data = std::make_shared<Data>(filename);
		data->add_data_from_file();
		data->stats();
		data->print();

		std::shared_ptr<Model> model;
		if (!addResonance)
			model = std::make_shared<ModelWithoutResonance>(E_th);
		else
			model = std::make_shared<ModelWithResonance>(E_th);

		model->init();

		Chi2 chi2(data, model);

		double min_chi2 = 1e10;
		std::vector<double> params, params_errors;
		for (size_t i = 0; i < 100; ++i) {
			auto result = Minimizer(chi2, 0);
			if (result.minvalue < min_chi2) {
				min_chi2 = result.minvalue;
				params = result.values;
				params_errors = result.errors;
			}
		}

		std::cout << "min chi2 found : " << min_chi2 << "\n";
		int dof = data->get_size() - model->get_nparams();
		std::cout << "reduced chi2 : " << min_chi2 / (double) dof << "\n";
		std::cout << "params : ";
		for (size_t i = 0; i < params.size(); ++i)
			std::cout << params[i] << " +/- " << params_errors[i] << "\t";
		std::cout << "\n";

		model->print(params, params_errors);

	} else {
		std::cout << "Usage: ./ffxsecs data-filename addresonance? E_th[GeV/n]\n";
	}
	return 0;
}
