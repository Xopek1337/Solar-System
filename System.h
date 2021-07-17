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
				s[i].update(v[1].getx(), v[1].gety());
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
				for (int i = 0; i < v.size() + s.size(); i++)
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