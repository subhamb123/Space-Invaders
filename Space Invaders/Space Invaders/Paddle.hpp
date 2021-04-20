#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle : public RectangleShape {
public:
	Paddle(Vector2f& size, Vector2f& pos, const Color &color) : RectangleShape(size) {
		setFillColor(color);
		setPosition(pos);
	}

private:
	
};