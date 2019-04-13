#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAMETIME 0

#define BG_COLOR color4f{ 0.08f, 0.08f, 0.08f, 1.0f }

#define FUEL_CONSUMPTION_RATE 0.1f
#define FUEL_REFILL_RATE 0.05f
#define FUEL_DENSITY 5.0f

#define PLAYER_MASS 5.0f
#define PLAYER_GMASS 1000.0f
#define PLAYER_POS vec{ 0.0f, 0.0f }
#define PLAYER_VEL vec{ 0.0f, 0.0f }
#define PLAYER_DENSITY 0.7f
#define PLAYER_COLOR color4f{ 0.5f, 0.5f, 0.5f, 1.0f }

#define THRUST_FORCE 1500.0f
#define GRAV_CONSTANT 1000.0f

#define ENTITY_MASS_MIN 50.0f
#define ENTITY_MASS_MAX 100.0f
#define ENTITY_DENSITY_MIN 1.0f
#define ENTITY_DENSITY_MAX 10.0f
#define ENTITY_BASE_COLOR color4f{ 0.5f, 0.5f, 0.1f, 1.0f }
#define ENTITY_COLOR_RANGE color4f{ 0.5f, -0.5f, 0.2f, 1.0f }
#define ENTITY_BASE_COLOR_NEG color4f{ 0.1f, 0.2f, 1.0f, 1.0f }
#define ENTITY_COLOR_RANGE_NEG color4f{ 0.2f, 0.8f, -0.9f, 1.0f }

#define ANNULUS_COLOR color4f{ 0.18f, 0.17f, 0.17f, 1.0f }
#define ANNULUS_THICKNESS 10.0f
#define ANNULUS_INRAD_SCALING 20.0f

#define ENTITIES 20

#define GAME_SPEED 1000000000 / 1

typedef struct
{
	float r;
	float g;
	float b;
	float a;
} color4f;