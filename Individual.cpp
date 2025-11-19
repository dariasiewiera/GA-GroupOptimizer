//
// Created by dusia on 04/01/2025.
//

#include "Individual.h"

#include <utility>

Individual::Individual(const GroupingChallenge::GroupingEvaluator &evaluator,
                          RandomNumberGenerator &generator): fitness(FITNESS_NOT_COMPUTED) {
    genotype.reserve(evaluator.iGetNumberOfPoints());
    for (unsigned int i = 0; i < evaluator.iGetNumberOfPoints(); i++) {
        int gene = generator.generateGroupNumber();
        genotype.push_back(gene);
    }
}

Individual::Individual() {
    fitness = FITNESS_NOT_COMPUTED;
}

Individual::Individual(vector<int> genotype): genotype(std::move(genotype)), fitness(FITNESS_NOT_COMPUTED) {
}

Individual::Individual(const Individual &otherIndividual) {
    genotype = otherIndividual.genotype;
    fitness = otherIndividual.fitness;
}


bool Individual::operator==(const Individual &other) const {
    return genotype == other.genotype;
}

std::vector<int> Individual::getGenotype() const {
    return genotype;
}

int Individual::getGene(int i) const{
    return genotype[i];
}

void Individual::setGene(int i, int gene) {
    genotype[i] = gene;
}


void Individual::countFitness(const GroupingChallenge::GroupingEvaluator &evaluator) {
    fitness = evaluator.dEvaluate(genotype);
}

double Individual::getFitness() const {
    return fitness;
}

void Individual::mutate(RandomNumberGenerator &generator, double mutationProbability) {
    for (unsigned int i = 0; i < genotype.size(); i++) {
        if (generator.generateProbability() <= mutationProbability) {
            genotype[i] = generator.generateGroupNumber();
        }
    }
}

std::pair<Individual*, Individual*>
Individual::crossover(const Individual &otherParent,RandomNumberGenerator &generator) const{
    if (*this == otherParent) {
        return make_pair(new Individual(*this), new Individual(otherParent));
    }

    vector<int> child1;
    vector<int> child2;

    child1.reserve(genotype.size());
    child2.reserve(genotype.size());

    int crossoverPoint = generator.generateCrossoverPoint();

    for (int i = 0; i < crossoverPoint; i++) {
        child1.push_back(genotype[i]);
        child2.push_back(otherParent.genotype[i]);
    }

    for (int i = crossoverPoint; i < genotype.size(); i++) {
        child1.push_back(otherParent.genotype[i]);
        child2.push_back(genotype[i]);
    }

    return make_pair(new Individual(std::move(child1)), new Individual(std::move(child2)));
}
