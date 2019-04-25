#pragma once
#include "AnimatedSprite.hpp"

#include <SFML/Graphics.hpp>
#include <map>

enum direction_t { DOWN = 0, LEFT, RIGHT, UP };

class Player {
private:
    sf::Texture m_texture;
    std::map<direction_t, Animation> m_mapAnimation;
    direction_t m_facingDirection;

public:
    // sf::Sprite sprite;
    AnimatedSprite animSprite;
    sf::Vector2f position;
    Player();
    ~Player();
    void walk();
};
