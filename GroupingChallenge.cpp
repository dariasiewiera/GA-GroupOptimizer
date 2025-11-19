#include <iostream>

#include "AlternativeCrossover.h"
#include "GeneticAlgorithm.h"
#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "StandardCrossover.h"
#include "TournamentSelection.h"

class UniformCrossover;
class GeneticAlgorithm;
using namespace GroupingChallenge;

int main() {
    GaussianGroupingEvaluatorFactory evaluator_factory(5, 100);

    evaluator_factory
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0)
            .addDimension(-100, 100, 1.0, 1.0);

    GroupingEvaluator *evaluator = evaluator_factory.createEvaluator(0);


    ISelectionStrategy *selection = new TournamentSelection();
    ICrossoverStrategy *crossover = new StandardCrossover();
    ICrossoverStrategy *crossover2 = new AlternativeCrossover();
    GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm(600, 0.15, 0.5, 1000,50, *evaluator, selection, crossover2);


    geneticAlgorithm->run();
    std::cout << "Final best solution: " << geneticAlgorithm->getBestSolution()->getFitness();

    delete geneticAlgorithm;
    delete evaluator;


    return 0;
}
