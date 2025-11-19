#include "GaussianGroupingEvaluatorFactory.h"

using namespace GroupingChallenge;

Dimension::Dimension(double meanMin, double meanMax, double standardDeviationMin, double standardDeviationMax, mt19937 &cRandomEngine)
	: mean_uniform_distribution(min(meanMin, meanMax), max(meanMin, meanMax)),
	standard_deviation_uniform_distribution(min(standardDeviationMin, standardDeviationMax), max(standardDeviationMin, standardDeviationMax)),
	random_engine(cRandomEngine)
{

}

double Dimension::generateRandomMean()
{
	return mean_uniform_distribution(random_engine);
}

double Dimension::generateRandomStandardDeviation()
{
	double standard_deviation = standard_deviation_uniform_distribution(random_engine);

	if (standard_deviation <= 0)

	{
		standard_deviation = DEFAULT_STANDARD_DEVIATION_VALUE;
	}

	return standard_deviation;
}

GaussianDistribution::GaussianDistribution(double mean, double standardDeviation, mt19937& randomEngine)
	: normal_distribution(mean, standardDeviation), random_engine(randomEngine)
{

}

double GaussianDistribution::generateRandomNumber()
{
	return normal_distribution(random_engine);
}

GaussianGroupingEvaluatorFactory::GaussianGroupingEvaluatorFactory(int numberOfGroups, int numberOfPoints)
	: number_of_groups(max(numberOfGroups, NUMBER_OF_GROUPS_MIN_VALUE)), number_of_points(max(numberOfPoints, NUMBER_OF_GROUPS_MIN_VALUE))
{

}

GaussianGroupingEvaluatorFactory& GaussianGroupingEvaluatorFactory::addDimension(double meanMin, double meanMax, double standardDeviationMin, double standardDeviationMax)
{
	dimensions.push_back(Dimension(meanMin, meanMax, standardDeviationMin, standardDeviationMax, random_engine));

	return *this;
}

GroupingEvaluator* GaussianGroupingEvaluatorFactory::createEvaluator()
{
	random_device seed_generator;

	return createEvaluator(seed_generator());
}

GroupingEvaluator* GaussianGroupingEvaluatorFactory::createEvaluator(unsigned int iSeed)
{
	random_engine.seed(iSeed);

	vector<GaussianDistribution>* gaussian_distributions = create_gaussian_distributions();
	vector<Point>* points = create_points(*gaussian_distributions);

	GroupingEvaluator* evaluator = new GroupingEvaluator(number_of_groups, *points);

	delete gaussian_distributions;
	delete points;

	return evaluator;
}


vector<GaussianDistribution>* GaussianGroupingEvaluatorFactory::create_gaussian_distributions()
{
	vector<GaussianDistribution>* gaussian_distributions = new vector<GaussianDistribution>();

	gaussian_distributions->reserve(dimensions.size());

	for (size_t i = 0; i < dimensions.size(); i++)
	{
		gaussian_distributions->push_back(GaussianDistribution(dimensions[i].generateRandomMean(), dimensions[i].generateRandomStandardDeviation(), random_engine));
	}

	return gaussian_distributions;
}

vector<Point>* GaussianGroupingEvaluatorFactory::create_points(vector<GaussianDistribution>& gaussianDistributions)
{
	vector<Point>* points = new vector<Point>();

	points->reserve(number_of_points);

	for (int i = 0; i < number_of_points; i++)
	{
		Point point;

		for (size_t j = 0; j < gaussianDistributions.size(); j++)
		{
			point.addCoordinate(gaussianDistributions[j].generateRandomNumber());
		}

		points->push_back(point);
	}

	return points;
}