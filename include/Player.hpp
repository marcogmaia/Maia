#pragma once
#include "AnimatedSprite.hpp"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

enum direction_t { DOWN = 0, LEFT, RIGHT, UP };

class Player final {
private:
    sf::Texture m_texture;
    std::map<direction_t, Animation> m_mapAnimation;
    Player();

public:
    AnimatedSprite animSprite;
    sf::Vector2f position;
    Player &operator=(const Player &) = delete;
    ~Player();
    void walk();
    static Player *getInstance();
};
