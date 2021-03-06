#include "snowball_swap.h"
#include <vector>
#include "u_math.h"
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>

SnowballSwap::SnowballSwap(double notional, double fixedRate,
            SnowballSpread spread, double maturity, double startDate,
            CompFreq freq)
            :mNotional(notional), mFixedRate(fixedRate), mSpread(spread),
                mMaturity(maturity), mStartDate(startDate), mFreq(freq) { }

SnowballSwap::~SnowballSwap() { }

void SnowballSwap::setProcess(OUProcess process) {
    mProcess = process;
}

void SnowballSwap::determineSpread(double r) {
    if (r > mSpread.mUpper)
        mSpread.mAmount += mSpread.mLeverage * (r - mSpread.mUpper);
    else if (r < mSpread.mLower)
        mSpread.mAmount += mSpread.mLeverage * (mSpread.mLower - r);
    else
        mSpread.mAmount = MAX(0, mSpread.mAmount - mSpread.mMinus);
}

std::vector<double> SnowballSwap::mcPrice(unsigned int numPath,
                                                unsigned int numStep) {

    std::ofstream rate;
    rate.open("rate.csv", std::ios::app);
    rate << "NUMPATH,RATE" << std::endl;

    /* get data from process */
    double r0 = mProcess.getCurrentValue();
    double vol = mProcess.getVol();
    double lambda = mProcess.getPriceRisk();
    double kappa = mProcess.getSpeed();

    /* risk-neutralize */
    double lrMean = mProcess.getLmean() - lambda * vol / kappa;

    double dt = mMaturity / (double)numStep;
    double discount;

    /* weighted average long-run mean */
    double expLmean = lrMean * (1 - exp(-kappa * dt));
    double diffusion = sqrt((0.5 * vol * vol / kappa) * (1 - exp(-2 * kappa * dt)));

    /* compounding frequency and calculation and payment date */
    double freq = 1.0 / mFreq;

    /* result vector */
    std::vector<double> result(numPath);
    std::pair<double, double> price;

    /* random number engine */
    std::mt19937_64 gen;
    std::normal_distribution<double> engine(0.0, 1.0);
    std::random_device rd;
    gen.seed(rd());

    /* Simulation */
    for (int i = 0; i < numPath; ++i) {
        double r = r0;  /* initialize r */
        discount = 1.0;   /* initialize discount factor */
        double value = 0;   /* initialize value */

        /* initialize */
        double paymentDate = mStartDate;
        double calcDate = paymentDate - freq;
        double getDate = freq;
        mSpread.mAmount = 0.0;

        for (int j = 0; j < numStep; ++j) {
            /* Generate random number */
            double e = engine(gen);

            /* Update discount factor and spot rate */
            discount *= exp(-r * dt);
            r = r * exp(-kappa * dt) + expLmean + diffusion * e;

            /* at every 3 month */
            if (fabs((j + 1) * dt - getDate) < 1e-03) {
                value += discount * mNotional * mFixedRate * freq;
                getDate += freq;
            }

            /* if payment date */
            if (fabs((j + 1) * dt - paymentDate) < 1e-03) {
                /* pay */
                value -= discount * mNotional * mSpread.mAmount * freq;
                /* update next payment date */
                paymentDate += freq;
            }

            /* if calculation date */
            if (fabs((j + 1) * dt - calcDate) < 1e-03) {
                /* determine spread */
                determineSpread(r);
                /* update next calculation date */
                calcDate += freq;
            }
        }
        result[i] = value;  /* discounted cash flow at i_th path */
        rate << i << "," << r << std::endl;
    }
    rate.close();
    return result;
}
