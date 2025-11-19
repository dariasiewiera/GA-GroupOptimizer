//
// Created by dusia on 16/01/2025.
//

#ifndef STANDARDCROSSOVER_H
#define STANDARDCROSSOVER_H
#include <utility>

#include "Individual.h"
#include "ICrossoverStrategy.h"
class Individual;

class StandardCrossover : public ICrossoverStrategy {
public:
    std::pair<Individual*, Individual*> getChildren(const Individual& parent1, const Individual& parent2,
                                                  RandomNumberGenerator* generator,
                                                  const double crossoverProbability) const override {

        if (generator->generateProbability() <= crossoverProbability) {
            return parent1.crossover(parent2, *generator);
        }

        return std::pair{new Individual(parent1), new Individual(parent2)};
    }
};
#endif //STANDARDCROSSOVER_H
