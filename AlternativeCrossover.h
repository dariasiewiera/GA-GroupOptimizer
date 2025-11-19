//
// Created by dusia on 16/01/2025.
//

#ifndef ALTERNATIVECROSSOVER_H
#define ALTERNATIVECROSSOVER_H

#include <utility>
#include "Individual.h"
#include "ICrossoverStrategy.h"

class AlternativeCrossover : public ICrossoverStrategy {
public:
    std::pair<Individual*, Individual*> getChildren(const Individual& parent1, const Individual& parent2,
                                                      RandomNumberGenerator* generator,
                                                      const double crossoverProbability) const override {

        if (generator->generateProbability() > crossoverProbability) {
            return std::pair{new Individual(parent1), new Individual(parent2)};
        }


        Individual* child1 = new Individual(parent1);
        Individual* child2 = new Individual(parent2);


        int genotypeSize = parent1.getGenotype().size();
        for (int i = 0; i < genotypeSize; i++) {
            if (generator->generateProbability() < 0.5) {

                child1->setGene(i, parent2.getGene(i));
                child2->setGene(i, parent1.getGene(i));
            }
        }

        return std::pair{child1, child2};
    }
};

#endif //ALTERNATIVECROSSOVER_H
