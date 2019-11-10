#include <iostream>
#include<cmath>
#include <random>


double Tmin = 0.00001;
double Tmax = 90000;
double A = 7;
double B = 10;

using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;

enum mode {
	unimodal,
	multimodal
};

double generateRaw() {
	static mt19937 engine(random_device{}());
	auto generator = uniform_real_distribution<double>(0.0, 1.0);
	return generator(engine);
}


double generateRandom() {
	return A + (B - A) * generateRaw();
}

double getValueFor(double x, mode m) {
	if (m == multimodal) return sin(5*x)*getValueFor(x, unimodal);
	return cos(x) + log10(x);
}



int main() {
	for (mode a : {unimodal, multimodal}) {
		
		double x1 = generateRandom();
		double f1 = getValueFor(x1, a);
		double Ti = Tmax;
		while (Ti > Tmin) {
			double x2 = generateRandom();
			double f2 = getValueFor(x2, a);
			double df = f2 - f1;
			if(df>0 && generateRaw()>exp(-df/Ti)) {
				//комментарий, чтобы эта часть кода не выглядела незавершённой
			} else {
				x1 = x2;
				f1 = f2;
			}
			Ti *= 0.95;
		}
		std::cout << x1 << std::endl << f1 << std::endl;
	}
}