//
// Created by dusia on 16/01/2025.
//

#ifndef ICROSSOVERSTRATEGY_H
#define ICROSSOVERSTRATEGY_H
#include <utility>
class Individual;
class RandomNumberGenerator;

class ICrossoverStrategy {
public:
    virtual std::pair<Individual *, Individual *> getChildren(const Individual &parent1,
                                                                     const Individual &parent2,
                                                                     RandomNumberGenerator *generator,
                                                                     double crossoverProbability) const = 0;

    virtual ~ICrossoverStrategy() = default;
};
#endif //ICROSSOVERSTRATEGY_H
