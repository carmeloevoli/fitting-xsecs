#include "model.h"
#include <cmath>

double set_threshold_energy(const Channel& channel) {
//  http://www.nndc.bnl.gov/qcalc/index.jsp
	if (channel == Channel(12, 6, 6, 3)) // C12 -> Li6
		return 24.461686e-3;
	else if (channel == Channel(12, 6, 7, 3)) // C12 -> Li7
		return 28.17563e-3;
	else if (channel == Channel(12, 6, 7, 4)) // C12 -> Be7
		return 24.461686e-3;
	else if (channel == Channel(12, 6, 9, 4)) // C12 -> Be9
		return 31.850e-3;
	else if (channel == Channel(12, 6, 10, 4)) // C12 -> Be10
		return 36.840e-3;
	else if (channel == Channel(12, 6, 10, 5)) // C12 -> B10
		return 21.346e-3;
	else if (channel == Channel(12, 6, 11, 5)) // C12 -> B11 interpolated
		return 20e-3;
	else if (channel == Channel(12, 6, 11, 6)) // C12 -> C11
		return 17.88121e-3;
	else if (channel == Channel(14, 7, 7, 4)) // N14 -> Be7
		return 11.317975e-3;
	else if (channel == Channel(14, 7, 10, 4)) // N14 -> Be10
		return 42.440e-3;
	else if (channel == Channel(14, 7, 11, 5)) // N14 -> B11
		return 25.554e-3;
	else if (channel == Channel(14, 7, 11, 6)) // N14 -> C11
		return 31.321633e-3;
	else if (channel == Channel(14, 7, 10, 5)) // N14 -> B10
		return 14.554e-3;
	else if (channel == Channel(16, 8, 6, 3)) // O16 -> Li6
		return 23.581742e-3;
	else if (channel == Channel(16, 8, 7, 3)) // O16 -> Li7
		return 29.820977e-3;
	else if (channel == Channel(16, 8, 7, 4)) // O16 -> Be7
		return 26.859299e-3;
	else if (channel == Channel(16, 8, 9, 4)) // O16 -> Be9
		return 33.71604e-3;
	else if (channel == Channel(16, 8, 10, 4)) // O16 -> Be10
		return 40.1089e-3;
	else if (channel == Channel(16, 8, 10, 5)) // O16 -> B10
		return 26.859303e-3;
	else if (channel == Channel(16, 8, 11, 5)) // O16 -> B11
			return 26.0335e-3;
	else if (channel == Channel(16, 8, 11, 6)) // O16 -> C11
			return 23.581742e-3;
	else {
		std::cout << "Warning : threshold energy not found!\n";
		return 10e-3;
	}
}

double sigma_1_func(double sigma_1, double xi, double Delta, double T_h, double E_th, double T) {
	double f_1 = 0;
	if (T > E_th) {
		f_1 = sigma_1 * std::pow(1. - E_th / T, xi);
		f_1 *= 1. + Delta / std::pow(1. + (T_h / T), 2.);
	}
	return f_1;
}

double sigma_0_func(double sigma_0, double M, double Gamma, double E_th, double T) {
	double f_0 = 0;
	if (T > E_th) {
		double Gamma_2 = Gamma * Gamma;
		double T_2 = T * T;
		double M_2 = M * M;
		f_0 = sigma_0 * Gamma_2 * std::pow(T - E_th, 2.);
		f_0 /= std::pow(T_2 - M_2, 2.) + Gamma_2 * M_2;
	}
	return f_0;
}
