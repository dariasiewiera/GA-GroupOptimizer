//
// Created by dusia on 04/01/2025.
//

#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H
#define FITNESS_NOT_COMPUTED LLONG_MAX
#include <vector>

#include "GeneticAlgorithm.h"
#include "RandomNumberGenerator.h"
#include "GroupingEvaluator.h"


class Individual {
public:
    Individual();
    Individual(const GroupingChallenge::GroupingEvaluator &evaluator, RandomNumberGenerator &generator);
    explicit Individual(vector<int> genotype);
    Individual(const Individual &otherIndividual);


    bool operator==(const Individual &other) const;

    void countFitness(const GroupingChallenge::GroupingEvaluator &evaluator);
    pair<Individual*, Individual*> crossover(const Individual &otherParent, RandomNumberGenerator &generator) const;
    void mutate(RandomNumberGenerator &generator, double mutationProbability);
    double getFitness() const;
    std::vector<int> getGenotype() const;
    int getGene(int i) const;
    void setGene(int i,int gene);

private:
    std::vector<int> genotype;
    double fitness{};
};


#endif //CINDIVIDUAL_H
