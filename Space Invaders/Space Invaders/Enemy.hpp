#pragma once

#include "header.hpp"
#include "Character.hpp"

class Enemy : public Character 
{
public:
	Enemy(const Vector2f& pos, const Texture& texture, const Vector2f& scale) : Character(pos, texture, scale) {
		alive = true;
	}
	bool isAlive()
	{
		return alive;
	}
	int kill(int level)
	{
		alive = false;
		return level * 5;
	}

private:
	bool alive;
};