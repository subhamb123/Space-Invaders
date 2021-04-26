#include "header.hpp"
#include "User.hpp"

class Missile : public User
{
public:
    Missile(const Vector2f& pos, const Texture& texture, const Vector2f& scale) : User(pos, texture, scale)
    {
        setPosition(pos);
        setScale(scale);
    }
    ~Missile();
    bool fire(const Vector2f& pos);
};