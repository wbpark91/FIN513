#include "ou_process.h"
#include <cmath>

/* Consturctors and Destructor */
OUProcess::OUProcess(double speed, double lmean, double vol, double risk)
    :mSpeed(speed), mLmean(lmean), mVol(vol), mPriceRisk(risk) { }

OUProcess::~OUProcess() { }

/* get functions */
double OUProcess::getSpeed() const { return mSpeed; }
double OUProcess::getLmean() const { return mLmean; }
double OUProcess::getVol() const { return mVol; }
double OUProcess::getPriceRisk() const {return mPriceRisk; }

/* get G0 and G1 */
double OUProcess::getG0(double t) {
    /* risk-neutralized long-run mean */
    double rnMean = mLmean - mPriceRisk * mVol / mSpeed;
    double g1 = getG1(t);
    return (g1 - t) * (rnMean * mSpeed * mSpeed - 0.5 * mVol * mVol) / (mSpeed * mSpeed) \
            - (mVol * mVol * g1 * g1) / (4 * mSpeed);
}

double OUProcess::getG1(double t) {
    return (1 - exp(-mSpeed * t)) / mSpeed;
}
