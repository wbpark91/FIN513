/* FIN513 - Financial Engineering 1 */
/* HW5 - Problem 4(a) */
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "u_math.h"

int main(void) {
    std::vector<double> vol = {0.20, 0.30, 0.40, 0.50};

    /* Parameter setting */
    double spot = 100;
    double maturity = 1.0;
    double mu = 0.07;
    double r = 0.0;
    double b = 0.1;

    double steps = 500;
    double numPath = 50000;

    double dt = maturity / steps;

    /* Random Number Generator */
    std::mt19937_64 gen;
    std::normal_distribution<double> engine(0.0, 1.0);
    std::random_device rd;
    gen.seed(rd());

    std::cout << "Simulation: " << "Number of path - " << numPath << " " << "Number of steps - " << steps << std::endl;
    for (int k = 0; k < vol.size(); ++k) {
        std::cout << "========" << "Vol: " << vol[k] << "========" << std::endl;
        std::vector<double> payoffStream;
        double diffusion = vol[k] * sqrt(dt);
        double expReturn = exp((mu - 0.5 * vol[k] * vol[k]) * dt);

        for (int i = 0; i < numPath; ++i) {
            std::vector<double> deltaStream;
            std::vector<double> spotStream;
            std::vector<double> cashStream;

            deltaStream.push_back(0.0);
            spotStream.push_back(spot);
            cashStream.push_back(-deltaStream[0] * spot);
            /* For each path */
            for (int j = 1; j <= steps; ++j) {
                double e = engine(gen);
                double s = spotStream[j-1] * expReturn * exp(diffusion * e);
                spotStream.push_back(s);

                if (j != steps) {
                    deltaStream.push_back(b * (s - spot));
                    cashStream.push_back(cashStream[j-1] * exp(r * dt) + (deltaStream[j-1] - deltaStream[j]) * s);
                }
                else {
                    payoffStream.push_back(deltaStream[j-1] * s + cashStream[j-1] * exp(r * dt));
                }
            }
        }
        std::cout << "Mean: " << mean(payoffStream) << std::endl;
        std::cout << "Standard Deviation: " << stdev(payoffStream) / sqrt(numPath) << std::endl;
    }


    return 0;
}
