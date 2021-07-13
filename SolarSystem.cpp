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
	double x = 0;
	double y = 0;
	

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
	}
	double getAngle()
	{
		return dx;
	}
	void setAngle(double angle) 
	{
		dx = angle;
	}
protected:
	double dx = 0;
	double a;
	double radius;
	double orbit;
	double centerx;
	double centery;
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
	void draw(RenderWindow &window,View view,Vector2f center)
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

			window.clear();
			for (int i = 0;i<v.size();i++)
			{
				window.draw(v[i].sprite);
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
			}
			else
			{
				for (int i = 0; i < v.size(); i++)
				{
					out << 0 << std::endl;
				}
			}
		}
	}
	void setCFG()
	{
		std::ifstream in("cfg.txt");
		std::vector<int> inputData;
		std::string line;
		int i = 0;
		while (std::getline(in, line)) {
			int temp = std::stoi(line);
			v[i].setAngle(temp);
			i++;
		}
	}
protected:
	std::vector<Planet> v;

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

	eImage.loadFromFile("earth_PNG17.png");
	vImage.loadFromFile("venus.png");
	sImage.loadFromFile("sun.png");
	mImage.loadFromFile("mercury.png");

	Planet earth(eImage, 0.1, 225, center.x, center.y, 0.001);
	Planet sun(sImage, 0.08, 0, center.x, center.y, 0);
	Planet venus(vImage, 0.02, 175, center.x, center.y, 0.0013);
	Planet mercury(vImage, 0.015, 125, center.x, center.y, 0.0015);

	SolarSystem SS;
	SS.addplanet(earth);
	SS.addplanet(sun);
	SS.addplanet(venus);
	SS.addplanet(mercury);

	SS.setCFG();
	
	while (window.isOpen())
	{
		SS.draw(window, view, center);
	}

	SS.changeCFG();

	return 0;
}
