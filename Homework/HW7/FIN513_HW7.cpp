#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "u_math.h"
#include "ou_process.h"
#include "snowball_swap.h"

int main(void) {
    std::ofstream problem5;
    problem5.open("problem5.csv", std::ios::app);
    problem5 << "NUMPATH,VALUE" << std::endl;

    OUProcess process(0.03576228, 0.10, 0.04614356, 0.0065, 0.0);
    SnowballSpread spread = {0.0, 0.02, 0.06, 2.0, 0.0050};
    SnowballSwap swap(89.0, 0.03, spread, 15.0, 2.0, Quarter);
    swap.setProcess(process);

    std::vector<double> result = swap.mcPrice(10000, 365 * 22);
    std::cout << "Average: " << mean(result) << std::endl;
    std::cout << "St.dev: " << stdev(result) / sqrt(result.size()) << std::endl;

    for (int i = 0; i < result.size(); ++i) {
        problem5 << i+1 << "," << result[i] << std::endl;
    }

    problem5.close();
    return 0;
}
