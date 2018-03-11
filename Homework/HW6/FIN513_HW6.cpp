#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "marketvariable.h"
#include "plainvanilla_option.h"

int main(void) {
    std::ofstream problem2;
    problem2.open("problem2.csv", std::ios::app);
    problem2 << "V,OPTION_PRICE,DELTA,VOL,CEVVOL" << std::endl;

    double w = 1;
    PlainVanillaOption option(100.0, 5.0, Call);

    /* Problem 2 */
    for (double i = 11; i <= 110; ++i) {
        MarketVariable mktVar(i, 0.06, 0.0, 0.20);
        option.setMarketVariable(mktVar);
        double price = option.bsprice();
        double optdelta = option.delta();
        double vol = optdelta * (i / price) * mktVar.getVol();
        problem2 << i << "," << price << "," << optdelta << "," << \
            vol << "," << w * w / sqrt(price) << std::endl;
    }
    problem2.close();

    /* Problem 3 */
    std::ofstream problem3;
    problem3.open("problem3.csv", std::ios::app);
    problem3 << "VOL,SIGMA_S(100),SIGMA_S(50),MULT(100),MULT(50)" << std::endl;

    PlainVanillaOption option2(100.0, 5.0, Call);     /* Debt FV = 100 */
    PlainVanillaOption option3(50.0, 5.0, Call);      /* Debt FV = 50 */

    for (double i = 1; i <= 80; ++i) {
        double vol = i / 100.0;
        MarketVariable mktVar2(100.0, 0.06, 0.0, vol);
        option2.setMarketVariable(mktVar2);
        option3.setMarketVariable(mktVar2);

        double price2 = option2.bsprice();
        double delta2 = option2.delta();
        double price3 = option3.bsprice();
        double delta3 = option3.delta();

        problem3 << vol << "," << delta2 * (100.0 / price2) * vol << "," << \
            delta3 * (100.0 / price3) * vol << "," << \
            delta2 * (100.0 / price2) << "," << delta3 * (100.0 / price3) << std::endl;
    }
    problem3.close();
    return 0;
}
