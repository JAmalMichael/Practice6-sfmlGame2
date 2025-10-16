#ifndef CSHAPE_H
#define CSHAPE_H

#include "Component.h"
#include <SFML/Graphics.hpp>


class CShape : public Component 
{
public:
	sf::CircleShape circle;
	CShape( float radius, int points, const sf::Color & fill, const sf::Color outline, float thickness)
	{
		circle.setRadius(radius);
		circle.setPointCount(points);
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};



#endif