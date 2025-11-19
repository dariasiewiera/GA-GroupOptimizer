//
// Created by dusia on 04/01/2025.
//

#include "GeneticAlgorithm.h"

#include <iostream>
#include <ostream>

#include "Individual.h"
#include "ICrossoverStrategy.h"
#include "ISelectionStrategy.h"

class ISelectionStrategy;
class ICrossoverStrategy;

GeneticAlgorithm::GeneticAlgorithm(int populationSize, double mutationProbability, double crossoverProbability,
                                     int numberOfIterations, int maxNoImproveIterations,
                                     GroupingChallenge::GroupingEvaluator &evaluator, ISelectionStrategy *selection,
                                     ICrossoverStrategy *crossover): populationSize(populationSize),
                                                                     mutationProbability(mutationProbability),
                                                                     crossoverProbability(crossoverProbability),
                                                                     numberOfIterations(numberOfIterations),
                                                                     bestSolution(new Individual()),
                                                                     evaluator(&evaluator), noImprovementCounter(0),
                                                                     maxNoImproveIterations(maxNoImproveIterations),
                                                                     selectionStrategy(selection),
                                                                     crossoverStrategy(crossover) {
    population.reserve(populationSize);
    generator = new RandomNumberGenerator(evaluator.iGetNumberOfPoints(), evaluator.iGetUpperBound(), populationSize);
}

GeneticAlgorithm::~GeneticAlgorithm() {
    deletePopulation();
    delete generator;
    delete bestSolution;
    delete selectionStrategy;
    delete crossoverStrategy;
}


Individual *GeneticAlgorithm::getBestSolution() {
    return bestSolution;
}

void GeneticAlgorithm::run() {
    generatePopulation();
    for (int i = 0; i < numberOfIterations; i++) {
        calculateFitness();
        crossover();
        mutate();

        if (noImprovementCounter >= maxNoImproveIterations) {
            noImprovementCounter = 0;

            if (mutationProbability < 0.5) {
                mutationProbability += 0.05;
            }
            if (crossoverProbability < 0.6) {
                crossoverProbability += 0.05;
            }

            std::cout << "Mutation prob raised to: " << mutationProbability << " Crossing prob raised to: " <<
                    crossoverProbability << std::endl;
        }

    std:
        cout << "Iteration: " << i << ", Best solution: " << getBestSolution()->getFitness() << std::endl;
    }
}


void GeneticAlgorithm::generatePopulation() {
    for (int i = 0; i < populationSize; i++) {
        Individual *individual = new Individual(*evaluator, *generator);
        population.push_back(individual);
    }
}

void GeneticAlgorithm::calculateFitness() {
    bool improved = false;
    for (int i = 0; i < populationSize; i++) {
        population[i]->countFitness(*evaluator);
        if (population[i]->getFitness() < bestSolution->getFitness()) {
            delete bestSolution;
            bestSolution = new Individual(*population[i]);
            improved = true;
        }
    }

    if (improved) {
        noImprovementCounter = 0;
    } else {
        noImprovementCounter++;
    }
}

void GeneticAlgorithm::crossover() {
    vector<Individual *> newPopulation;

    if (populationSize % 2 == 1) {
        Individual *newIndividual = new Individual(*population[selectionStrategy->chooseParent(population,*generator)]);
        newPopulation.emplace_back(newIndividual);
    }

    for (int i = 0; i < populationSize / 2; i++) {
        const int parent1 = selectionStrategy->chooseParent(population,*generator);
        const int parent2 = selectionStrategy->chooseParent(population,*generator);

        pair<Individual *, Individual *> children = crossoverStrategy->getChildren(*population[parent1], *population[parent2],generator,crossoverProbability);

        newPopulation.emplace_back(children.first);
        newPopulation.emplace_back(children.second);
    }

    deletePopulation();
    population = std::move(newPopulation);
}

/*std::pair<CIndividual *, CIndividual *> CGeneticAlgorithm::getChildren(const CIndividual &parent1,
                                                                       const CIndividual &parent2) const {
    if (generator->generateProbability() <= crossoverProbability) {
        return parent1.crossover(parent2, *generator);
    }

    return std::pair{new CIndividual(parent1), new CIndividual(parent2)};
}

int CGeneticAlgorithm::chooseParent() const {
    const int candidate1 = generator->generateIndividualIndex();
    const int candidate2 = generator->generateIndividualIndex();
    return population[candidate1]->getFitness() < population[candidate2]->getFitness() ? candidate1 : candidate2;
}*/


void GeneticAlgorithm::mutate() {
    for (int i = 0; i < populationSize; i++) {
        if (generator->generateProbability() <= mutationProbability) {
            population[i]->mutate(*generator, mutationProbability);
        }
    }
}

void GeneticAlgorithm::deletePopulation() {
    for (int i = 0; i < populationSize; i++) {
        if (population[i] != nullptr) {
            delete population[i];
        }
    }
    population.clear();
}
