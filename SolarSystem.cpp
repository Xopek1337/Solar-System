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
	Image juImage;
	Image saImage;
	Image uranImage;
	Image neptImage;
	Image moonImage;

	eImage.loadFromFile("earth_PNG17.png");
	vImage.loadFromFile("venus.png");
	sImage.loadFromFile("sun.png");
	mImage.loadFromFile("mercury.png");
	marsImage.loadFromFile("mars.png");
	juImage.loadFromFile("jupiter.png");
	saImage.loadFromFile("saturn.png");
	uranImage.loadFromFile("uran.png");
	neptImage.loadFromFile("neptune.png");
	moonImage.loadFromFile("moon.png");

	Planet sun(sImage, 0.08, 0, center.x, center.y, 0);
	Planet mercury(mImage, 0.015, 100, center.x, center.y, 0.0015);
	Planet venus(vImage, 0.02, 155, center.x, center.y, 0.0013);
	Planet earth(eImage, 0.1, 230, center.x, center.y, 0.001);
	Planet mars(marsImage, 0.03, 300, center.x, center.y, 0.0009);
	Planet jupiter(juImage, 0.08, 420, center.x, center.y, 0.0008);
	Planet saturn(saImage, 0.08, 500, center.x, center.y, 0.0007);
	Planet uran(uranImage, 0.008, 600, center.x, center.y, 0.00065);
	Planet neptun(neptImage, 0.07, 700, center.x, center.y, 0.0006);

	sputnik moon(moonImage, 0.007, 25, center.x, center.y, 0.002);

	SolarSystem SS;

	SS.addplanet(sun);
	SS.addplanet(mercury);
	SS.addplanet(venus);
	SS.addplanet(earth);
	SS.addplanet(mars);
	SS.addplanet(jupiter);
	SS.addplanet(saturn);
	SS.addplanet(uran);
	SS.addplanet(neptun);

	SS.addsp(moon);

	SS.setCFG();

	while (window.isOpen())
	{
		SS.draw(window, view, center);
	}

	SS.changeCFG();

	return 0;
}