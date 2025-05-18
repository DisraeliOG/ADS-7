// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <random>
#include <vector>
#include "train.h"

using Clock = std::chrono::high_resolution_clock;

enum InitMode { ALL_OFF, ALL_ON, RANDOM };

void run_experiment(InitMode mode, const std::vector<int>& ns) {
    try {
        std::ofstream dataFile("C:/Users/jolly/CLionProjects/ADS7/experiment_data.csv", std::ios::app);
        if (!dataFile) throw std::runtime_error("Can't open file");

        std::mt19937_64 rnd{static_cast<uint64_t>(std::random_device{}())};
        std::uniform_int_distribution<int> bit(0, 1);

        for (int n : ns) {
            std::cout << "\nProcessing n = " << n << std::endl;

            Train train;
            for (int i = 0; i < n; ++i) {
                bool light = (mode == ALL_OFF) ? false :
                            (mode == ALL_ON) ? true : bit(rnd);
                train.addCar(light);
            }
            std::cout << "Train created with " << n << " cars" << std::endl;

            auto t0 = Clock::now();
            size_t length = train.getLength();
            auto t1 = Clock::now();

            dataFile << n << ","
                     << (mode == ALL_OFF ? "ALL_OFF" :
                        mode == ALL_ON ? "ALL_ON" : "RANDOM") << ","
                     << train.getOpCount() << ","
                     << std::chrono::duration<double, std::milli>(t1 - t0).count()
                     << "\n";
            dataFile.flush();

            std::cout << "Data written for n = " << n << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }
}

int main() {
    try {
        std::ofstream("C:/Users/jolly/CLionProjects/ADS7/experiment_data.csv").close();

        std::vector<int> ns;
        for (int n = 1000; n <= 10000; n += 1000) {
            if (n <= 0) throw std::logic_error("Invalid n value");
            ns.push_back(n);
        }

        run_experiment(ALL_OFF, ns);
        run_experiment(ALL_ON, ns);
        run_experiment(RANDOM, ns);

        std::ifstream in("C:/Users/jolly/CLionProjects/ADS7/experiment_data.csv");
        std::cout << "\nFinal file size: " << in.tellg() << " bytes\n";
        in.close();

    } catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
