#include "GroupingEvaluator.h"

using namespace GroupingChallenge;

GroupingEvaluator::GroupingEvaluator(int iNumberOfGroups, const vector<Point>& vPoints)
	: i_number_of_groups(iNumberOfGroups), v_points(vPoints)
{
	distance_matrix.resize(v_points.size(), vector<double>(v_points.size(), -1));
	for (int i = 0; i < v_points.size(); i++)
	{
		for (int j = i + 1; j < v_points.size(); j++)
		{
			double distance = v_points[i].calculateDistance(v_points[j]);
			distance_matrix[i][j] = distance;
			distance_matrix[j][i] = distance;
		}
	}
}

double GroupingEvaluator::dEvaluate(const int* piSolution) const
{


	if (!piSolution || v_points.empty())
	{
		return d_WRONG_VALUE;
	}

	for (size_t i = 0; i < v_points.size(); ++i)
	{
		if (piSolution[i] < iGetLowerBound() || piSolution[i] > iGetUpperBound())
		{
			return d_WRONG_VALUE;
		}
	}

	double d_distance_sum = 0;

	for (size_t i = 0; i + 1 < v_points.size(); ++i)
	{
		for (size_t j = i + 1; j < v_points.size(); ++j)
		{
			if (piSolution[i] == piSolution[j])
			{
				d_distance_sum += 2.0 * distance_matrix[i][j];
			}
		}
	}


	return d_distance_sum;
}

double GroupingEvaluator::dEvaluate(const vector<int>* pvSolution) const
{
	if (!pvSolution)
	{
		return d_WRONG_VALUE;
	}

	return dEvaluate(*pvSolution);
}

double GroupingEvaluator::dEvaluate(const vector<int>& vSolution) const
{
	if (vSolution.size() != v_points.size())
	{
		return d_WRONG_VALUE;
	}

	return dEvaluate(vSolution.data());
}