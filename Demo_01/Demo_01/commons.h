#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAMETIME 0

#define BG_COLOR color4f{ 0.0f, 0.0f, 0.0f, 1.0f }
#define ENTITY_BASE_COLOR color4f{ 0.8f, 0.2f, 0.1f, 1.0f }
#define ENTITY_COLOR_RANGE color4f{ 0.2f, 0.2f, 0.2f, 1.0f }

#define FUEL_CONSUMPTION_RATE 0.1f
#define FUEL_REFILL_RATE 0.05f
#define FUEL_DENSITY 1.0f

#define PLAYER_COLOR color4f{ 1.0f, 1.0f, 1.0f, 1.0f }
#define PLAYER_MASS 0.3f

typedef struct
{
	float r;
	float g;
	float b;
	float a;
} color4f;