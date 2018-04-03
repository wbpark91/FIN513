#include "ou_process.h"

/* Consturctors and Destructor */
OUProcess::OUProcess(double speed, double lmean, double vol, double risk)
    :mSpeed(speed), mLmean(lmean), mVol(vol), mPriceRisk(risk) { }

OUProcess::~OUProcess() { }

/* get functions */
double OUProcess::getSpeed() const { return mSpeed; }
double OUProcess::getLmean() const { return mLmean; }
double OUProcess::getVol() const { return mVol; }
double OUProcess::getPriceRisk() const {return mPriceRisk; }
