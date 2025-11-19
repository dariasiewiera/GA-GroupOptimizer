#include "Point.h"

using namespace GroupingChallenge;

void Point::addCoordinate(double dCoordinate)
{
	coordinates.push_back(dCoordinate);
}

double Point::calculateDistance(const Point& cOther) const
{
	if (coordinates.empty() || coordinates.size() != cOther.coordinates.size())
	{
		return WRONG_DISTANCE_VALUE;
	}

	double d_squared_distance = 0;

	for (size_t i = 0; i < coordinates.size(); i++)
	{
		d_squared_distance += (coordinates[i] - cOther.coordinates[i]) * (coordinates[i] - cOther.coordinates[i]);
	}

	return sqrt(d_squared_distance);
}