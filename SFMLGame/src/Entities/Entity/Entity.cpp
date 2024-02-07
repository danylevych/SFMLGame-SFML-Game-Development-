#include "Entity.h"

Entity::Entity(int32_t hitpoints)
    : hitpoints(hitpoints)
{   }

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

void Entity::Accelerate(sf::Vector2f velocity)
{
    this->velocity += velocity;
}

void Entity::Accelerate(float xVelocity, float yVelocity)
{
    Accelerate(sf::Vector2f(xVelocity, yVelocity));
}

int32_t Entity::GetHitpoints() const
{
    return hitpoints;
}

void Entity::Repair(int32_t points)
{
    hitpoints += points;
}

void Entity::Damage(int32_t points)
{
    hitpoints -= points;
}

bool Entity::IsDestroyed() const
{
    return hitpoints <= 0;
}

void Entity::Destroy()
{
    hitpoints = 0;
}

void Entity::UpdateCurrent(sf::Time delta, CommandQueue& commands)
{
    move(velocity * delta.asSeconds());
}
