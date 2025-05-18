// Copyright 2022 NNTU-CS
#include "train.h"
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

namespace {

constexpr char kDataFilePath[] = 
    "C:/Users/jolly/CLionProjects/ADS7/experiment_data.csv";

enum class InitMode { kAllOff, kAllOn, kRandom };

std::string InitModeToString(InitMode mode) {
  switch (mode) {
    case InitMode::kAllOff:
      return "ALL_OFF";
    case InitMode::kAllOn:
      return "ALL_ON";
    case InitMode::kRandom:
      return "RANDOM";
    default:
      return "UNKNOWN";
  }
}

void RunExperiment(InitMode mode, const std::vector<int>& test_sizes) {
  try {
    std::ofstream data_file(kDataFilePath, std::ios::app);
    if (!data_file) throw std::runtime_error("Can't open file");

    std::mt19937_64 rng{static_cast<uint64_t>(std::random_device{}())};
    std::uniform_int_distribution<int> bit_dist(0, 1);

    for (const int car_count : test_sizes) {
      std::cout << "\nProcessing n = " << car_count << std::endl;

      Train train;
      for (int i = 0; i < car_count; ++i) {
        bool light = false;
        if (mode == InitMode::kAllOff) {
          light = false;
        } else if (mode == InitMode::kAllOn) {
          light = true;
        } else {
          light = bit_dist(rng);
        }
        train.addCar(light);
      }
      std::cout << "Train created with " << car_count << " cars" << std::endl;

      const auto start_time = std::chrono::high_resolution_clock::now();
      const size_t length = train.getLength();
      const auto end_time = std::chrono::high_resolution_clock::now();

      const double elapsed_ms = 
          std::chrono::duration<double, std::milli>(end_time - start_time).count();

      data_file << car_count << ","
                << InitModeToString(mode) << ","
                << train.getOpCount() << ","
                << elapsed_ms << "\n";
      data_file.flush();

      std::cout << "Data written for n = " << car_count << std::endl;
    }
  } catch (const std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
  }
}

}

int main() {
  try {
    std::ofstream(kDataFilePath).close();

    std::vector<int> test_sizes;
    for (int n = 1000; n <= 10000; n += 1000) {
      if (n <= 0) throw std::logic_error("Invalid n value");
      test_sizes.push_back(n);
    }

    RunExperiment(InitMode::kAllOff, test_sizes);
    RunExperiment(InitMode::kAllOn, test_sizes);
    RunExperiment(InitMode::kRandom, test_sizes);

    std::ifstream in(kDataFilePath);
    in.seekg(0, std::ios::end);
    std::cout << "\nFinal file size: " << in.tellg() << " bytes\n";
    in.close();

  } catch (const std::exception& e) {
    std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
