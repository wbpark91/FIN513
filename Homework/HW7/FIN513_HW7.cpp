#include <iostream>
#include <vector>
#include <cmath>
#include "u_math.h"
#include "ou_process.h"
#include "snowball_swap.h"

int main(void) {
    OUProcess process(0.03576228, 0.10, 0.04614356, 0.0065, 0.0);
    SnowballSpread spread(0.0, 0.02, 0.06, 2.0, 0.0050);
    SnowballSwap swap(89.0, 0.03, spread, 15.0, 2.0, Quarter);
    swap.setProcess(process);

    std::vector<double> result = swap.mcPrice(10000, 365 * 22);
    std::cout << "Average: " << average(result) << std::endl;
    std::cout << "St.dev: " << stdev(result) / sqrt(result.size()) << std::endl;

    return 0;
}
