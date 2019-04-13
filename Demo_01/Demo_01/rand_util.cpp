#include "rand_util.h"

float rand_u(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}
	
float rand_z(float mu, float sigma)
{
	float u = 0, v = 0;
	while (u == 0.0f)
		u = rand_u(0.0f, 1.0f);
	while (v == 0.0f)
		v = rand_u(0.0f, 1.0f);

	return mu + sigma * sqrt(-2.0 * log(u)) * cos(2.0 * PI * v);
}

float rand_log_z(float mu, float sigma)
{
	return mu * exp(rand_z(0.0f, sigma));
}

int rand_b()
{
	return rand() % 2;
}