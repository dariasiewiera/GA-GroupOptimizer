//
// Created by dusia on 14/01/2025.
//

#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(const int vectorLength, const int groupCount,
                                             const int populationSize): vectorLength(vectorLength), groupCount(groupCount),
                                                                        populationSize(populationSize) {
    std::random_device seedGenerator;
    generator.seed(seedGenerator());
}


int RandomNumberGenerator::generateGroupNumber() {
    std::uniform_int_distribution<int> distribution(1, groupCount);
    return distribution(generator);
}

int RandomNumberGenerator::generateCrossoverPoint() {
    std::uniform_int_distribution<int> distribution(1, vectorLength - 1);
    return distribution(generator);
}

double RandomNumberGenerator::generateProbability() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

int RandomNumberGenerator::generateIndividualIndex() {
    std::uniform_int_distribution<int> distribution(0, populationSize - 1);
    return distribution(generator);
}
