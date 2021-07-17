#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace sf;

class Planet
{
public:
	Texture texture;
	Sprite sprite;
	Planet()
	{
	}

	Planet(Image& image, double radius, double orbit, double centerx, double centery, double a)
	{
		sprite.setOrigin(sf::Vector2f(image.getSize().x / 2, image.getSize().y / 2));

		this->a = a;
		this->centerx = centerx;
		this->centery = centery;
		this->radius = radius;
		this->orbit = orbit;

		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setScale(radius, radius);
	}

	void update()
	{
		x = orbit * cos(dx) + centerx;
		y = orbit * sin(dx) + centery;
		sprite.setPosition(x, y);
		dx += a;
		if (dx > 2 * M_PI - a)
			dx = 0;
	}
	double getAngle()
	{
		return dx;
	}
	void setAngle(double angle)
	{
		dx = angle;
	}
	double getx()
	{
		return x;
	}
	double gety()
	{
		return y;
	}
protected:
	double x = 0;
	double y = 0;
	double dx = 0;
	double a;
	double radius;
	double orbit;
	double centerx;
	double centery;
};
class sputnik :public Planet
{
public:
	sputnik(Image& image, double radius, double orbit, double centerx, double centery, double a)
	{
		sprite.setOrigin(sf::Vector2f(image.getSize().x / 2, image.getSize().y / 2));

		this->a = a;
		this->centerx = centerx;
		this->centery = centery;
		this->radius = radius;
		this->orbit = orbit;

		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setScale(radius, radius);
	}
	void update(double cx, double cy)
	{
		x = orbit * cos(dx) + cx;
		y = orbit * sin(dx) + cy;
		sprite.setPosition(x, y);
		dx += a;
		if (dx > 2 * M_PI - a)
			dx = 0;
	}
};