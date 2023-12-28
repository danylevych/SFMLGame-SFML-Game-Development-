#pragma once

#include "ResourceHolder.h"


#include "../Enums/TextureID.h"
#include <SFML/Graphics/Texture.hpp>

using TextureHolder = ResourceHolder<Textures::TextureID, sf::Texture>;


#include "../Enums/FontID.h"
#include <SFML/Graphics/Font.hpp>

using FontHolder = ResourceHolder<Font::FontID, sf::Font>;


#include "../Enums/ShaderID.h"
#include <SFML/Graphics/Shader.hpp>

using ShaderHolder = ResourceHolder<Graphics::ShaderID, sf::Shader>;


#include "../Enums/MusicID.h"
#include <SFML/Audio/Music.hpp>

using MusicHolder = ResourceHolder<Audio::MusicID, sf::Music>;


#include "../Enums/SoundID.h"
#include <SFML/Audio/SoundBuffer.hpp>

using SoundHolder = ResourceHolder<Audio::SoundID, sf::SoundBuffer>;
