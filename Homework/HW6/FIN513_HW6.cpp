#include <iostream>
#include <fstream>
#include <iomanip>
#include "marketvariable.h"
#include "plainvanilla_option.h"

int main(void) {
    std::ofstream result;
    result.open("result.csv", std::ios::app);
    result << "V,OPTION_PRICE,DELTA,VOL" << std::endl;
    PlainVanillaOption option(100, 5.0, Call);
    for (double i = 1; i <= 110; ++i) {
        MarketVariable mktVar(i, 0.06, 0.0, 0.20);
        option.setMarketVariable(mktVar);
        double price = option.bsprice();
        double optdelta = option.delta();
        double vol = optdelta * (i / price) * mktVar.getVol();
        result << i << "," << price << "," << optdelta << "," << \
            vol << std::endl;
    }
    result.close();
    return 0;
}
