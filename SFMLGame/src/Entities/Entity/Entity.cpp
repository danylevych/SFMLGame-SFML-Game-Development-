#include "Entity.h"

sf::Vector2f Entity::GetVelocity() const
{
    return this->velocity;
}

void Entity::SetVelocity(float x, float y)
{
    this->velocity = sf::Vector2f(x, y);
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Entity::UpdateCurrent(sf::Time delta)
{
    move(velocity * delta.asSeconds());
}
