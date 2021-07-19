#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "Planet.h"

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

			if (Keyboard::isKeyPressed(Keyboard::X)) 
			{ 
				sf::Vector2i localPosition = Mouse::getPosition();
				double cx =  localPosition.x - center.x;
				double cy =  localPosition.y - center.y;
				
				double rad = sqrt(cx*cx+cy*cy);
				Image mImage;
				mImage.loadFromFile("venus.png");
				for (int i = 1; i < v.size(); i++)
				{
					if (v[i].geto()-v[i].getr() > rad && v[i-1].geto()+v[i-1].getr() < rad)
					{
						if (abs(v[i - 1].getx() - localPosition.x) < 75 && abs(v[i - 1].gety() - localPosition.y) < 75)
						{
							double cex = localPosition.x - v[i - 1].getx();
							double cey = localPosition.y - v[i - 1].gety();
							double rads = sqrt(cey * cey + cex * cex);
							sputnik gg(mImage, 0.005, rads, center.x, center.y, 0.0030);
							gg.setAngle(atan2(cey, cex));
							if (i == 2)
								mer.push_back(gg);
							if (i == 3)
								vs.push_back(gg);
							if (i == 4)
								es.push_back(gg);
							if (i == 5)
								mar.push_back(gg);
							if (i == 6)
								ju.push_back(gg);
							if (i == 7)
								sat.push_back(gg);
							if (i == 8)
								uran.push_back(gg);
							if (i == 9)
								nept.push_back(gg);
						}
						else if (abs(v[i].getx() - localPosition.x) < 75 && abs(v[i].gety() - localPosition.y) < 75)
						{
							double cex = localPosition.x - v[i].getx();
							double cey = localPosition.y - v[i].gety();
							double rads = sqrt(cey * cey + cex * cex);
							sputnik gg(mImage, 0.005, rads, center.x, center.y, 0.0030);
							gg.setAngle(atan2(cey, cex));
							if (i == 1)
								mer.push_back(gg);
							if (i == 2)
								vs.push_back(gg);
							if (i == 3)
								es.push_back(gg);
							if (i == 4)
								mar.push_back(gg);
							if (i == 5)
								ju.push_back(gg);
							if (i == 6)
								sat.push_back(gg);
							if (i == 7)
								uran.push_back(gg);
							if (i == 8)
								nept.push_back(gg);
						}
						else
						{
							Planet gg(mImage, 0.005, rad, center.x, center.y, 0.0015);
							gg.setAngle(atan2(cy, cx));
							sv.push_back(gg);
						}
					}
				}
			}

			window.setView(view);
			for (int i = 0; i < v.size(); i++)
			{
				v[i].update();
			}
			for (int i = 0; i < sv.size(); i++)
			{
				sv[i].update();
			}
			for (int i = 0; i < s.size(); i++)
			{
				s[i].update(v[3].getx(), v[3].gety());
			}

			for (int i = 0; i < es.size(); i++)
			{
				es[i].update(v[3].getx(), v[3].gety());
			}
			for (int i = 0; i < vs.size(); i++)
			{
				vs[i].update(v[2].getx(), v[2].gety());
			}
			for (int i = 0; i < mar.size(); i++)
			{
				mar[i].update(v[4].getx(), v[4].gety());
			}
			for (int i = 0; i < mer.size(); i++)
			{
				mer[i].update(v[1].getx(), v[1].gety());
			}
			for (int i = 0; i < ju.size(); i++)
			{
				ju[i].update(v[5].getx(), v[5].gety());
			}
			for (int i = 0; i < sat.size(); i++)
			{
				sat[i].update(v[6].getx(), v[6].gety());
			}
			for (int i = 0; i < uran.size(); i++)
			{
				uran[i].update(v[7].getx(), v[7].gety());
			}
			for (int i = 0; i < nept.size(); i++)
			{
				nept[i].update(v[8].getx(), v[8].gety());
			}
			window.clear();
			for (int i = 0; i < v.size(); i++)
			{
				window.draw(v[i].sprite);
			}
			for (int i = 0; i < sv.size(); i++)
			{
				window.draw(sv[i].sprite);
			}
			for (int i = 0; i < s.size(); i++)
			{
				window.draw(s[i].sprite);
			}
			for (int i = 0; i < es.size(); i++)
			{
				window.draw(es[i].sprite);
			}
			for (int i = 0; i < vs.size(); i++)
			{
				window.draw(vs[i].sprite);
			}
			for (int i = 0; i < mar.size(); i++)
			{
				window.draw(mar[i].sprite);
			}
			for (int i = 0; i < mer.size(); i++)
			{
				window.draw(mer[i].sprite);
			}
			for (int i = 0; i < ju.size(); i++)
			{
				window.draw(ju[i].sprite);
			}
			for (int i = 0; i < sat.size(); i++)
			{
				window.draw(sat[i].sprite);
			}
			for (int i = 0; i < uran.size(); i++)
			{
				window.draw(uran[i].sprite);
			}
			for (int i = 0; i < nept.size(); i++)
			{
				window.draw(nept[i].sprite);
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
	std::vector<Planet> sv;
	std::vector<sputnik> s;
	std::vector<sputnik> es;
	std::vector<sputnik> vs;
	std::vector<sputnik> mer;
	std::vector<sputnik> mar;
	std::vector<sputnik> ju;
	std::vector<sputnik> sat;
	std::vector<sputnik> uran;
	std::vector<sputnik> nept;
};