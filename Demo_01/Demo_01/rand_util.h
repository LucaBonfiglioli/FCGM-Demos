#pragma once
#include <random>
#include <cmath>
#include "commons.h"

float rand_u(float min, float max);
float rand_z(float mu, float sigma);
float rand_log_z(float mu, float sigma);
int rand_b();