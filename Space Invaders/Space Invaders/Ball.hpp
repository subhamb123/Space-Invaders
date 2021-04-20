#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball : public CircleShape {
public:
	Ball(const float &radius, const Vector2f &pos, const Color &color) : CircleShape(radius) {
		setFillColor(color);
		setPosition(pos);
	}

private:

};