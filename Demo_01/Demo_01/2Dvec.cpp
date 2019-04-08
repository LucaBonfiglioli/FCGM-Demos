#include "2Dvec.h"
#include <cmath>

vec vecsum(vec a, vec b)
{
	return vec{ a.x + b.x, a.y + b.y };
}

vec vecdiff(vec a, vec b)
{
	return vec{ a.x - b.x, a.y - b.y };
}

vec vecmul(vec a, float b)
{
	return vec{ a.x * b, a.y * b };
}

float norm(vec a)
{
	return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

float scalprod(vec a, vec b)
{
	return a.x * b.x + a.y * b.y;
}