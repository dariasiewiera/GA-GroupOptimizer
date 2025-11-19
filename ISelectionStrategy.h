

#ifndef ISELECTIONSTRATEGY_H
#define ISELECTIONSTRATEGY_H
#include <vector>
class RandomNumberGenerator;
class Individual;

class ISelectionStrategy {
public:
    virtual int chooseParent(const std::vector<Individual*>& population, RandomNumberGenerator& generator) const = 0;
    virtual ~ISelectionStrategy() = default;
};

#endif //ISELECTIONSTRATEGY_H
