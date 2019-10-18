#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

const float framerate = 60.f;

float pixel2meter(float pixel);
float meter2pixel(float meter);

b2Vec2 pixel2meter(sf::Vector2f pixels);
sf::Vector2f meter2pixel(b2Vec2 meters);

enum class ContactDataType
{
	PLATFORM_CHARACTER,
	PLATFORM
};

struct ContactData
{
	void* data;
	ContactDataType contactDataType;
};

#endif