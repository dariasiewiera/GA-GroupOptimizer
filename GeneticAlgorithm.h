//
// Created by dusia on 04/01/2025.
//

#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H
#include <vector>
#include "Individual.h"
#include "RandomNumberGenerator.h"


class ISelectionStrategy;
class ICrossoverStrategy;

namespace GroupingChallenge {
    class GroupingEvaluator;
}

class RandomNumberGenerator;
class Individual;

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, double mutationProbability, double crossoverProbability,
    int numberOfIterations,int maxNoImproveIterations, GroupingChallenge::GroupingEvaluator &evaluator,ISelectionStrategy *selection,
                   ICrossoverStrategy *crossover);

    ~GeneticAlgorithm();

    Individual *getBestSolution();

    void run();

private:
    int populationSize;
    double mutationProbability;
    double crossoverProbability;
    int numberOfIterations;
    int noImprovementCounter;
    int maxNoImproveIterations;

    Individual *bestSolution;
    std::vector<Individual *> population;

    RandomNumberGenerator *generator;
    const GroupingChallenge::GroupingEvaluator *evaluator;

    ISelectionStrategy *selectionStrategy;
    ICrossoverStrategy *crossoverStrategy;

    void generatePopulation();

    void calculateFitness();

    void crossover();

    std::pair<Individual *, Individual *> getChildren(const Individual &parent1, const Individual &parent2) const;

    void mutate();

    int chooseParent() const;

    void deletePopulation();
};


#endif //CGENETICALGORITHM_H
