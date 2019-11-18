#include <iostream>
#include<cmath>
#include <random>
#include <iomanip>


double Tmin = 0.01;
double Tmax = 10000;
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
		int N = 0;
		double x1 = INFINITY;
			//generateRandom();
		double f1 = INFINITY;
			//getValueFor(x1, a);
		double Ti = Tmax;
		std::cout << std::fixed << std::setprecision(4) << "| N| \t   Ti\t| \tx\t| \tf \t\tP\n";
		while (Ti > Tmin) {
			N++;
			double x2 = generateRandom();
			double f2 = getValueFor(x2, a);
			double df = f2 - f1;
			std::cout << std::fixed << std::setprecision(4) << "| " << N << "| \t " << Ti << "| \t";
			std::cout<< x2 << "| \t" << f2;
			double P = exp(-df / Ti);
			std::cout << "| \t" << (P>1?1:P) << "| \t ";
			if(df>0 && generateRaw()>P) {
				std::cout << "N \n";
				//комментарий, чтобы эта часть кода не выглядела незавершённой
			} else {
				x1 = x2;
				f1 = f2;
				std::cout << "Y \n";
			}
			Ti *= 0.95;
		}
		std::cout << "\n";
		std::cout << "Result: x=" << x1 << ", f(x)=" << f1 << std::endl << std::endl;
		//std::cout << x1 << std::endl << f1 << std::endl;
	}
}
