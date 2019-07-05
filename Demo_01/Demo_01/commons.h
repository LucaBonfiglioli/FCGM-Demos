#pragma once

#define PI 3.14159265f

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FRAMETIME 0

#define BG_COLOR color4f{ 0.08f, 0.08f, 0.08f, 1.0f }

#define FUEL_CONSUMPTION_RATE 1.0f
#define FUEL_REFILL_RATE 1.0f
#define FUEL_DENSITY 50.0f
#define PLAYER_FUEL_MASS_RATIO 2.0f

#define PLAYER_MASS 50.0f
#define PLAYER_GMASS 1000.0f
#define PLAYER_POS vec{ 0.0f, 0.0f }
#define PLAYER_VEL vec{ 0.0f, 0.0f }
#define PLAYER_DENSITY 1.0f
#define PLAYER_COLOR color4f{ 0.5f, 0.5f, 0.5f, 1.0f }

#define THRUST_FORCE 15000.0f
#define THRUST_ACCELERATION 1000.0f
#define GRAV_CONSTANT 1000.0f

#define ENTITY_MASS_MIN 50.0f
#define ENTITY_MASS_MAX 100.0f
#define ENTITY_DENSITY_MIN 0.5f
#define ENTITY_DENSITY_MAX 2.0f
#define ENTITY_BASE_COLOR color4f{ 0.5f, 0.3f, 0.1f, 1.0f }
#define ENTITY_COLOR_RANGE color4f{ 0.5f, -0.3f, -0.1f, 1.0f }
#define ENTITY_BASE_COLOR_NEG color4f{ 0.2f, 0.2f, 1.0f, 1.0f }
#define ENTITY_COLOR_RANGE_NEG color4f{ 0.1f, -0.1f, -0.6f, 1.0f }
#define ENTITY_BORDER_SCALING 0.9f
#define ENTITY_BORDER_COLOR_COEFF 2.0f

#define RING_COLOR_DARK color4f{ 0.21f, 0.21f, 0.21f, 0.5f }
#define RING_COLOR_LIGHT color4f{ 0.42f, 0.42f, 0.42f, 0.5f }
#define RING_THICKNESS 5.0f
#define RING_INRAD_SCALING 20.0f

#define PARTICLE_SPAWN_CHANCE 1000.0f
#define PARTICLE_FADING_SPEEED 1.0f
#define PARTICLE_SPEED_RANGE 2.0f
#define PARTICLE_ANGLE_SIGMA 1.5f
#define PARTICLE_SCALING 0.02f
#define PARTICLE_COLOR_COEFF 3.0f

#define ENTITIES 20
#define ENTITY_SPAWN_CHANCE 1.0f
#define ENTITY_SPAWN_WARNING_TIME 5.0f

#define GAME_SPEED 1000000000 / 2

typedef struct
{
	float r;
	float g;
	float b;
	float a;
} color4f;