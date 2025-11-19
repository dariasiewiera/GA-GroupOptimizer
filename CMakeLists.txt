cmake_minimum_required(VERSION 3.29)
project(GroupingChallenge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(GroupingChallenge
    GaussianGroupingEvaluatorFactory.cpp
    GaussianGroupingEvaluatorFactory.h
    GroupingChallenge.cpp
    GroupingEvaluator.cpp
    GroupingEvaluator.h
        Point.cpp
    Point.h
        Individual.cpp
        Individual.h
        GeneticAlgorithm.cpp
        GeneticAlgorithm.h
        RandomNumberGenerator.cpp
        RandomNumberGenerator.h
        ISelectionStrategy.h
        ICrossoverStrategy.h
        TournamentSelection.h
        StandardCrossover.h
        AlternativeCrossover.h

)
