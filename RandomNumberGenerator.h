//
// Created by dusia on 14/01/2025.
//

#ifndef CRANDOMNUMBERGENERATOR_H
#define CRANDOMNUMBERGENERATOR_H

#include <random>


class RandomNumberGenerator {
public:

    RandomNumberGenerator(int vectorLength, int groupCount, int populationSize);

    double generateProbability();
    int generateCrossoverPoint();
    int generateGroupNumber();
    int generateIndividualIndex();

private:
    std::mt19937 generator;
    int vectorLength;
    int groupCount;
    int populationSize;

};




#endif //CRANDOMNUMBERGENERATOR_H
