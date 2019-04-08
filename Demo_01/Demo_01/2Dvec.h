#pragma once

typedef struct 
{
	float x;
	float y;
} vec;

vec vecsum(vec a, vec b);
vec vecdiff(vec a, vec b);
vec vecmul(vec a, float b);
float norm(vec a);
float scalprod(vec a, vec b);