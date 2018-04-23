#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>

std::vector<double> corrNormal(double corr);
double generateGBM(double initial, double drift, double vol, double dt, double phi);
double calcValue(double spot, double swapRate, double rd, double rf, double t,
                    double maturity);
double CVA(double swapRate, double maturity, unsigned int steps,
            double spot, double intensity, double rd, double rf,
            double b, double corr,
            double sigmas, double sigmal);

int main(void) {
    std::ofstream hw8;
    hw8.open("problem3.csv", std::ios::app);
    hw8 << "Correlation, Value" << std::endl;

    /* Initialize value */
    double maturity = 5.0;
    unsigned int step = 100;
    double dt = maturity / step;
    double intensity = 0.005;
    double s = 1.0;
    double rd = 0.01;
    double rf = 0.05;
    double sigmas = 0.20;
    double sigmal = 0.50;
    double b = 0.25;
    double swapRate = 0.9071;


    for (int j = 0; j <= 10; ++j) {
        double corr = j / 10.0;
        double result = 0.0;
        for (int i = 0; i < 5000; ++i) {
            result += CVA(swapRate, maturity, 90 * 5, s, intensity, rd, rf, b, corr,
                                sigmas, sigmal);
        }

        double value = result / 5000;
        hw8 << corr << "," << value << std::endl;
        std::cout << j << "th completed" << std::endl;
    }

    hw8.close();
}

std::vector<double> corrNormal(double corr) {
    std::mt19937_64 gen;
    std::normal_distribution<double> engine(0.0, 1.0);
    std::random_device rd;
    gen.seed(rd());

    std::vector<double> result;

    double w1 = engine(gen);
    double w2 = engine(gen);
    double w3 = corr * w1 + sqrt(1 - corr * corr) * w2;

    result.push_back(w1);
    result.push_back(w3);

    return result;
}

/* Generate GBM */
double generateGBM(double initial, double drift, double vol, double dt, double phi) {
    return initial * exp((drift - 0.5 * vol * vol) * dt + vol * sqrt(dt) * phi);
}

double calcValue(double spot, double swapRate, double rd, double rf, double t,
                    double maturity) {
    double foreign = (spot / rf) * (exp(-rf * t) - exp(-rf * maturity));
    double domestic = (swapRate / rd) * (exp(-rd * t) - exp(-rd * maturity));

    return foreign - domestic;
}

double CVA(double swapRate, double maturity, unsigned int steps,
            double spot, double intensity, double rd, double rf,
            double b, double corr,
            double sigmas, double sigmal) {
    double s = spot;
    double lambda = intensity;
    double dt = maturity / steps;
    double t = 0.0;
    double sumlambda = 0.0;

    double result = 0.0;

    for (int i = 0; i < steps; ++i) {
        std::vector<double> ranNum = corrNormal(corr);
        double w1 = ranNum[0];
        double w2 = ranNum[1];

        /* default intensity */
        double defProb = lambda * exp(-sumlambda);

        /* position value */
        double value;
        double value1 = calcValue(s, swapRate, rd, rf, t, maturity);

        if (value1 >= 0) {
            value = value1;
        }
        else {
            value = 0;
        }

        /* summing all */
        result += exp(-rd * t) * defProb * value * dt;

        /* update variables */
        t += dt;
        s = generateGBM(s, (rd - rf), sigmas, dt, w1);
        lambda = generateGBM(lambda, b, sigmal, dt, w2);
        sumlambda += lambda * dt;
    }

    return result;
}
