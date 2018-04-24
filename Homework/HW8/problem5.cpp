#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>

void printVector(std::vector<double> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ", ";
    }
    std::cout << std::endl;
}

std::vector<double> generateIR(double kappa, double lrMean, double sigma,
                                double initial, double maturity,
                                unsigned int steps);

std::vector<double> generateE(double kappa, double sigma, double initial,
                                double maturity, unsigned int steps);

double npv(double initialR, double b);
double mcNPV(double initialR, double b, unsigned int numPath);

int main(void) {
    std::ofstream output;
    output.open("problem5.csv", std::ios::app);
    output << "Interest" << "," << "NPV_a" << "," << "NPV_b" << std::endl;
    for (int i = 1; i <= 16; ++i) {
        double ir = i / 100.0;
        double result1 = mcNPV(ir, -30, 10000);
        double result2 = mcNPV(ir, 0, 10000);
        output << ir << "," << result1 << "," << result2 << std::endl;
    }
    output.close();
    return 0;
}

double mcNPV(double initialR, double b, unsigned int numPath) {
    double result = 0.0;
    for (int i = 0; i < numPath; ++i) {
        result += npv(initialR, b);
    }
    return result / numPath;
}

double npv(double initialR, double b) {
    std::vector<double> ir = generateIR(0.12, 0.05, 0.2425, initialR, 30.0, 360);
    std::vector<double> e = generateE(0.18, 0.83, 0.0, 30.0, 360);

    /* discount factor */
    std::vector<double> discountFactor;
    double df = 1;
    for (int i = 0; i < ir.size() - 1; ++i) {
        df *= 1.0 / (1 + ir[i] * 1 / 12.0);
        discountFactor.push_back(df);
    }

    /* pi and z vector */
    std::vector<double> piVec;
    std::vector<double> zVec;
    double c = 0.06;
    for (int i = 1; i < ir.size(); ++i) {
        double longRun = -6 - (12.0 / i) + 0.02 * (120.0 - i);
        double pi = longRun + b * (ir[i] - c) + e[i];
        double z = exp(pi) / (1 + exp(pi));
        piVec.push_back(pi);
        zVec.push_back(z);
    }

    /* MBS */
    double principal = 100;
    double cpnRate = 0.06;
    int freq = 12;
    double maturity = 30.0;

    double coupon = principal * cpnRate / freq;
    double schedulePmt = principal * (cpnRate / freq) \
        / (1 - pow(1 + cpnRate / freq, -maturity * freq));


    double fraction = 1.0;
    double npv = 0;
    for (int i = 0; i < zVec.size(); ++i) {
        npv += discountFactor[i] * (schedulePmt * fraction + zVec[i] * principal * fraction);
        fraction = fraction * (1 - zVec[i]);
    }

    return npv;
}

std::vector<double> generateIR(double kappa, double lrMean, double sigma,
                                double initial, double maturity,
                                unsigned int steps) {
    /* Initialize parameters */
    double dt = maturity / steps;
    double spot = initial;

    double drift = kappa * (lrMean - spot);
    double diffusion = sigma * spot;

    std::vector<double> result;
    result.push_back(spot);

    /* Random Number Generator */
    std::mt19937_64 gen;
    std::normal_distribution<double> engine(0.0, 1.0);
    std::random_device rd;
    gen.seed(rd());

    /* generate path */
    for (int i = 0; i < steps; ++i) {
        double e = engine(gen);
        spot += drift * dt + diffusion * e * sqrt(dt);
        result.push_back(spot);

        /* update drift and diffusion */
        drift = kappa * (lrMean - spot);
        diffusion = sigma * spot;
    }

    return result;
}

std::vector<double> generateE(double kappa, double sigma, double initial,
                                double maturity, unsigned int steps) {
    /* Initialize parameters */
    double dt = maturity / steps;
    double spot = initial;

    double drift = -kappa * spot;
    double diffusion = sigma;

    std::vector<double> result;
    result.push_back(spot);

    /* Random Number Generator */
    std::mt19937_64 gen;
    std::normal_distribution<double> engine(0.0, 1.0);
    std::random_device rd;
    gen.seed(rd());

    for (int i = 0; i < steps; ++i) {
        double e = engine(gen);
        spot += drift * dt + diffusion * e * sqrt(dt);
        result.push_back(spot);

        /* update drift */
        drift = -kappa * spot;
    }

    return result;
}
