#pragma once

#include "header.hpp"
#include "Character.hpp"

class User : public Character
{
public:
	User(const Vector2f& pos, const Texture& texture, const Vector2f& scale) : Character(pos, texture, scale) {
		
	}

private:

};