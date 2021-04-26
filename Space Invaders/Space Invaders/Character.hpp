#pragma once

#include "header.hpp"

class Character : public Sprite
{
public:
	Character(const Vector2f& pos, const Texture& texture, const Vector2f& scale) : Sprite(texture) {
		setPosition(pos);
		setScale(scale);
	}
	~Character();
};