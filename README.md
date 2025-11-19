# Grouping Challenge

A C++ implementation of a genetic algorithm for solving clustering and grouping optimization problems. The algorithm uses tournament selection and multiple crossover strategies to find optimal groupings of multi-dimensional points.

## Features

- **Genetic Algorithm Core**: Population-based evolutionary optimization
- **Tournament Selection**: Selects parents based on fitness comparison
- **Multiple Crossover Strategies**: 
  - Standard single-point crossover
  - Alternative uniform crossover
- **Adaptive Parameters**: Mutation and crossover probabilities adjust during optimization
- **Gaussian Distribution Generation**: Creates realistic test data with configurable dimensions and groups
- **Distance Matrix Caching**: Pre-computed distances for efficient fitness evaluation

## Project Structure

The project is organized into the following files:

- **`GroupingChallenge.cpp`**: Main entry point and application logic.
- **`GeneticAlgorithm.*`**: Core genetic algorithm implementation.
- **`Individual.*`**: Represents an individual in the population.
- **`Point.*`**: Represents a multi-dimensional data point.
- **`GroupingEvaluator.*`**: Evaluates the fitness of a given grouping.
- **`GaussianGroupingEvaluatorFactory.*`**: Generates test data using a Gaussian distribution.
- **`RandomNumberGenerator.*`**: Utilities for random number generation.
- **`ISelectionStrategy.h`**: Interface for selection strategies.
- **`TournamentSelection.h`**: Implements the tournament selection strategy.
- **`ICrossoverStrategy.h`**: Interface for crossover strategies.
- **`StandardCrossover.h`**: Implements the standard single-point crossover strategy.
- **`AlternativeCrossover.h`**: Implements an alternative uniform crossover strategy.

## Dependencies

- C++20 compatible compiler (e.g., GCC, Clang, MSVC)
- CMake 3.29 or higher

## Building

To build the project, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd GroupingChallenge
   ```

2. **Create a build directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure the project with CMake:**
   ```bash
   cmake ..
   ```

4. **Build the project:**
   ```bash
   cmake --build .
   ```

   This will create an executable named `GroupingChallenge` in the `build` directory.

## Running the Application

To run the application, execute the compiled binary from the `build` directory:

```bash
./GroupingChallenge
```

The output will display the best fitness found by the algorithm.

## Configuration

All configuration parameters are located in `GroupingChallenge.cpp`. You can modify the following:

- **`NUM_GROUPS`**: The number of groups to partition the data into.
- **`NUM_POINTS`**: The total number of data points.
- **`DIMENSIONS`**: The number of dimensions for each data point.
- **`POPULATION_SIZE`**: The number of individuals in the genetic algorithm's population.
- **`MUTATION_PROBABILITY`**: The initial probability of mutation.
- **`CROSSOVER_PROBABILITY`**: The initial probability of crossover.
- **`NUM_ITERATIONS`**: The maximum number of iterations for the algorithm to run.
- **`MAX_NO_IMPROVE_ITERATIONS`**: The number of iterations without improvement before adaptively increasing mutation and crossover rates.

You can also switch between different selection and crossover strategies by changing the instantiated classes:

```cpp
// In GroupingChallenge.cpp
ISelectionStrategy *selection = new TournamentSelection();
ICrossoverStrategy *crossover = new AlternativeCrossover(); // or new StandardCrossover();
```

## Algorithm Details

### Fitness Evaluation
The fitness of an individual (a specific grouping of points) is determined by the sum of intra-group distances. The goal is to minimize this value, meaning that points within the same group are as close to each other as possible.

### Selection
The algorithm uses **Tournament Selection**. In each selection event, two individuals are chosen at random from the population, and the one with the better fitness (lower intra-group distance) is selected to become a parent.

### Crossover
Two crossover strategies are available:

- **Standard Crossover**: A single crossover point is chosen, and the parents' genetic material is swapped to create two offspring.
- **Alternative Crossover**: This is a uniform crossover where, for each gene, there is a 50% chance of it being inherited from either parent.

### Adaptive Parameters
To avoid getting stuck in local optima, the mutation and crossover probabilities are adaptive. If the best fitness in the population does not improve for a specified number of iterations (`MAX_NO_IMPROVE_ITERATIONS`), both probabilities are increased to encourage exploration of the solution space.

## License

This project is provided as-is for educational and research purposes.