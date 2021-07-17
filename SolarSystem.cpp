#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "Planet.h"
#include "System.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 1200), "Solar System");
	//RenderWindow window(sf::VideoMode(), "app.exe", sf::Style::Fullscreen);
	sf::View view = window.getDefaultView();
	sf::Vector2f center = view.getCenter();

	Image eImage;
	Image vImage;
	Image sImage;
	Image mImage;
	Image marsImage;
	Image moonImage;

	eImage.loadFromFile("earth_PNG17.png");
	vImage.loadFromFile("venus.png");
	sImage.loadFromFile("sun.png");
	mImage.loadFromFile("mercury.png");
	marsImage.loadFromFile("mars.png");
	moonImage.loadFromFile("moon.png");

	Planet sun(sImage, 0.08, 0, center.x, center.y, 0);
	Planet mars(marsImage, 0.03, 300, center.x, center.y, 0.0009);
	Planet earth(eImage, 0.1, 230, center.x, center.y, 0.001);
	Planet venus(vImage, 0.02, 155, center.x, center.y, 0.0013);
	Planet mercury(mImage, 0.015, 100, center.x, center.y, 0.0015);
	sputnik moon(moonImage, 0.007, 25, center.x, center.y, 0.002);

	SolarSystem SS;

	SS.addplanet(sun);
	SS.addplanet(earth);
	SS.addplanet(venus);
	SS.addplanet(mercury);
	SS.addplanet(mars);

	SS.addsp(moon);

	SS.setCFG();

	while (window.isOpen())
	{
		SS.draw(window, view, center);
	}

	SS.changeCFG();

	return 0;
}