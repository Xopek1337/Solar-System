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
	void update(double cx,double cy)
	{
		x = orbit * cos(dx) + cx;
		y = orbit * sin(dx) + cy;
		sprite.setPosition(x, y);
		dx += a;
		if (dx > 2 * M_PI - a)
			dx = 0;
	}
};
class SolarSystem
{
public:
	SolarSystem()
	{
	}
	void addplanet(Planet planet)
	{
		v.push_back(planet);
	}
	void addsp(sputnik sp)
	{
		s.push_back(sp);
	}
	void draw(RenderWindow& window, View view, Vector2f center)
	{
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta < 0)
				{
					view.zoom(1.001f);
				}
				else if (event.mouseWheelScroll.delta > 0)
				{
					view.zoom(0.999f);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::A)) { view.move(-0.2, 0); }
			if (Keyboard::isKeyPressed(Keyboard::D)) { view.move(0.2, 0); }
			if (Keyboard::isKeyPressed(Keyboard::S)) { view.move(0, 0.2); }
			if (Keyboard::isKeyPressed(Keyboard::W)) { view.move(0, -0.2); }

			window.setView(view);
			for (int i = 0; i < v.size(); i++)
			{
				v[i].update();
			}
			for (int i = 0; i < s.size(); i++)
			{
				s[i].update(v[1].getx(),v[1].gety());
			}
			window.clear();
			for (int i = 0; i < v.size(); i++)
			{
				window.draw(v[i].sprite);
			}
			for (int i = 0; i < s.size(); i++)
			{
				window.draw(s[i].sprite);
			}
			window.display();
		}
	}
	void changeCFG()
	{
		std::ofstream out("cfg.txt");
		int i = 0;
		if (out.is_open())
		{
			if (!out.eof())
			{
				for (int i = 0; i < v.size(); i++)
				{
					out << v[i].getAngle() << std::endl;
				}
				for (int i = 0; i < s.size(); i++)
				{
					out << s[i].getAngle() << std::endl;
				}
			}
			else
			{
				for (int i = 0; i < v.size()+s.size(); i++)
				{
					out << 0 << std::endl;
				}
			}
		}
	}
	void setCFG()
	{
		std::ifstream in("cfg.txt");
		std::string line;
		int i = 0;
		int d = 0;
		while (std::getline(in, line)) {
			int temp = std::stoi(line);
			if (i < v.size())
			{
				v[i].setAngle(temp);
				i++;
			}
			else
			{
				s[d].setAngle(temp);
				d++;
			}
		}
	}
protected:
	std::vector<Planet> v;
	std::vector<sputnik> s;
};
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