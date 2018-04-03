#ifndef _OU_PROCESS_H_
#define _OU_PROCESS_H_

class OUProcess {
public:
    /* Consturctors and Destructor */
    OUProcess(double currentValue, double speed, double lmean,
                double vol, double risk);
    ~OUProcess();

    /* get G0 and G1 */
    double getG0(double t);
    double getG1(double t);

    /* get functions */
    double getCurrentValue() const;
    double getSpeed() const;
    double getLmean() const;
    double getVol() const;
    double getPriceRisk() const;
private:
    double mCurrentValue;   // current value
    double mSpeed;          // mean-reverting speed
    double mLmean;          // long-run mean
    double mVol;            // volatility
    double mPriceRisk;      // market price of risk
};
#endif
