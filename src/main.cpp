#include <iostream>
#include "channel.h"
#include "chi2.h"
#include "data.h"
#include "minimizer.h"

int main(int argc, char *argv[]) {
	if (argc == 6) {
		Channel channel;
		channel.read_from_input(argv);
		channel.print();

		bool addResonance = atoi(argv[5]);

		auto data = std::make_shared<Data>(channel);
		data->add_data_from_file("data/xsecs_db_GALPROP.txt");
		data->add_data_from_file("data/xsecs_db_EXFOR.txt");
		data->add_data_from_file("data/xsecs_db_EXFOR_nat.txt");
		data->stats();
		data->print();

		std::shared_ptr<Model> model;
		if (!addResonance)
			model = std::make_shared<ModelWithoutResonance>(channel);
		else
			model = std::make_shared<ModelWithResonance>(channel);

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
		std::cout << "Usage: ./ffxsecs proj_A proj_Z frag_A frag_Z addresonance?\n";
	}
	return 0;
}
