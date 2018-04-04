#ifndef _SNOWBALL_SWAP_H_
#define _SNOWBALL_SWAP_H_
#include "ou_process.h"
#include <utility>

enum CompFreq { Annual = 1, SemiAnnual = 2, Quarter = 4 }

/* Spread handler */
struct SnowballSpread {
    double mSpread;     /* amount of spread */
    double mLower;      /* lower bound of the range */
    double mUpper;      /* upper bound of the range */
    double mLeverage;
};

class SnowballSwap {
public:
    /* Constructors and destructor */
    SnowballSwap(double notional, double fixedRate, SnowballSpread spread,
                double maturity, double startDate, CompFreq freq);
    ~SnowballSwap();

    void setProcess(OUProcess process);

    /* Monte-Carlo simulation: return mean and standard deviation */
    std::pair<double, double> mcPrice(unsigned int numPath, unsigned int numStep);
private:
    double mNotional;       /* notional amount */
    double mFixedRate;      /* fixed rate */
    SnowballSpread mSpread; /* spread */
    double mMaturity;       /* maturity */
    double mStartDate;      /* date start to pay spread */
    CompFreq mFreq;         /* compounding frequency */

    OUProcess mProcess;      /* interest rate process */
};
#endif
