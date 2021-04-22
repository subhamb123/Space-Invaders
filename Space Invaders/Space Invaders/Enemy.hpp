#pragma once

#include "header.hpp"
#include "Character.hpp"

class Enemy : public Character 
{
public:
	Enemy(const Vector2f& pos, const Texture& texture, const Vector2f& scale) : Character(pos, texture, scale) {

	}

private:

};