//
// Created by dusia on 16/01/2025.
//

#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H
#include "Individual.h"
#include "RandomNumberGenerator.h"
#include "ISelectionStrategy.h"

class TournamentSelection : public ISelectionStrategy {
public:
    int chooseParent(const std::vector<Individual*>& population, RandomNumberGenerator& generator) const override {
        const int candidate1 = generator.generateIndividualIndex();
        const int candidate2 = generator.generateIndividualIndex();
        return population[candidate1]->getFitness() < population[candidate2]->getFitness() ? candidate1 : candidate2;
    }
};
#endif //TOURNAMENTSELECTION_H
