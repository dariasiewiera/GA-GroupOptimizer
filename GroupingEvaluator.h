#ifndef GROUPING_EVALUATOR_H
#define GROUPING_EVALUATOR_H

#include "Point.h"

#include <vector>

using namespace std;

namespace GroupingChallenge
{
	class GroupingEvaluator
	{
	public:
		GroupingEvaluator(int iNumberOfGroups, const vector<Point>& vPoints);

		double dEvaluate(const int* piSolution) const;
		double dEvaluate(const vector<int>* pvSolution) const;
		double dEvaluate(const vector<int>& vSolution) const;

		int iGetNumberOfPoints() const { return (int)v_points.size(); };

		int iGetLowerBound() const { return 1; };
		int iGetUpperBound() const { return i_number_of_groups; }

	private:
		const double d_WRONG_VALUE = -1;

		int i_number_of_groups;
		vector<Point> v_points;
		vector<vector<double>> distance_matrix;
	};
}

#endif