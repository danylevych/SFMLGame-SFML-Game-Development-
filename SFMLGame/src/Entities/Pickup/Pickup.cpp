#include "Pickup.h"
#include "../../Utilities/DataTables/DataTables.h"


namespace
{
    std::vector<PickupData> DATA_TABLE = InitializePickupData();
}


Pickup::Pickup(Pickup::Type type, const TextureHolder& textures)
    : Entity(1)
    , type(type)
    , sprite(textures.Get(DATA_TABLE[type].texture))
{  
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Pickup::GetCategory() const
{
    return Category::Pickup;
}

sf::FloatRect Pickup::GetBoundingRect() const
{
    return GetWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Pickup::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Pickup::Apply(Aircraft& player) const
{
    DATA_TABLE[type].action(player);
}
