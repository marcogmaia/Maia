#pragma once
#include "AnimatedSprite.hpp"

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

enum direction_t { down = 0, left, right, up };

class Player {
private:
    sf::Texture m_texture;
    std::map<direction_t, AnimatedSprite> m_mapAnimatedSprite;

public:
    sf::Sprite sprite;
    sf::Vector2f position;
    Player();
    ~Player();
    void setSprite();
    void setTexture();
    void walk(direction_t direction);
};
