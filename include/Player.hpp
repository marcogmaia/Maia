#pragma once
// #include "AnimatedSprite.hpp"
#include <Animation.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class Player : public sf::Drawable {
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    Animation m_animation;

    Player();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    sf::Vector2f position;
    Player &operator=(const Player &) = delete;
    ~Player();
    void walk();
    void updateAnimation();
    static Player *getInstance();
};
