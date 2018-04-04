#include "snowball_swap.h"
#include <vector>
#include "u_math.h"
#include <cmath>
#include <random>

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
    if (r > spread.mUpper)
        spread.mSpread += spread.mLeverage * (r - spread.mUpper);
    else if (r < spread.mLower)
        spread.mSpread += spread.mLeverage * (spread.mLower - r);
    else
        spread.mSpread = MAX(0, spread.mSpread - spread.mMinus);
}

std::pair<double, double> SnowballSwap::mcPrice(unsigned int numPath,
                                                unsigned int numStep) {
    /* get data from process */
    double r0 = mProcess.mCurrentValue;
    double vol = mProcess.mVol;
    double lambda = mProcess.mPriceRisk;
    double kappa = mProcess.mSpeed;

    /* risk-neutralize */
    double lrMean = mProcess.mLmean - lambda * vol / kappa;

    double dt = mMaturity / (double)numStep;
    double discount;

    /* weighted average long-run mean */
    double expLmean = lrMean * (1 - exp(-kappa * dt));
    double diffusion = sqrt((0.5 * vol * vol / kappa) * (1 - exp(-2 * kappa * dt)));

    /* compounding frequency and calculation and payment date */
    double freq = 1.0 / mFreq;
    double paymentDate = mStartDate;
    double calcDate = paymentDate - freq;

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
        for (int j = 0; j < numStep; ++j) {
            /* Generate random number */
            double e = engine(gen);

            /* Update discount factor and spot rate */
            discount *= exp(-r * dt);
            r = r * exp(-kappa * dt) + expLmean + diffusion * e;

            /* at every 3 month */
            if (std::fmod((j + 1) * dt, freq) < 1e-06) {
                value += discount * mNotional * mFixedRate * freq;
            }

            /* if payment date */
            if (fabs((j + 1) * dt - paymentDate) < 1e-06) {
                /* pay */
                value -= discount * mNotional * spread.mSpread;
                /* update next payment date */
                paymentDate += freq;
            }

            /* if calculation date */
            if (fabs((j + 1) * dt - calcDate) < 1e-06) {
                /* determine spread */
                determineSpread(r);
                /* update next calculation date */
                calcDate += freq;
            }
        }
        result[i] = value;  /* discounted cash flow at i_th path */
    }

    /* calculate average and standard deviation */
    price.first = average(result);
    price.second = stdev(result) / sqrt(numPath);

    return price;
}