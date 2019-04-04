#include <iostream>
#include "Entity.h"

int main(int argc, char * argv[]) {
	Entity e(1.0f, 1.0f, vec{ 0.0f, 0.0f }, vec{ 0.0f, 0.0f });
	vec acc = e.getAccelerationAt(vec{ (float)1/2, (float)sqrt(3)/2 });
	std::cout << acc.x << " " << acc.y << '\n';
	float intensity = sqrt(pow(acc.x, 2) + pow(acc.y, 2));
	std::cout << intensity << '\n';
	system("PAUSE");
	return 0;
}