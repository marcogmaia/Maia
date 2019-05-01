#include "Player.hpp"

#include "Thor/Vectors.hpp"

#include <fmt/format.h>
#include <iostream>

#define ASSETS_PATH                                                            \
    "/home/marco/dev/cpp/games/maia/assets/Commissions/Paladin32x.png"
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_animation, states);
}

Player::Player()
    : m_animation(m_sprite) {
    m_texture.loadFromFile(ASSETS_PATH);
    m_sprite.setTexture(m_texture);

    m_animation.addFrames(0, 3, 0);
    m_animation.addToAnimator(DOWN, 1.f);
    m_animation.addFrames(0, 3, 1);
    m_animation.addToAnimator(LEFT, 1.f);
    m_animation.addFrames(0, 3, 2);
    m_animation.addToAnimator(RIGHT, 1.f);
    m_animation.addFrames(0, 3, 3);
    m_animation.addToAnimator(UP, 1.f);
    m_animation.playAnimation(DOWN);
    m_animation.animate();
}

Player::~Player() {}

void Player::walk() {
    float velocity    = 2.f;
    static bool moved = false;
    // direction_t direction = UP;
    static enum_animId_t direction     = DOWN;
    static enum_animId_t old_direction = direction;
    sf::Vector2f movement(0.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        movement.y -= velocity;
        moved = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        movement.y += velocity;
        moved = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        movement.x -= velocity;
        moved = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        movement.x += velocity;
        moved = true;
    }

    if(movement.x > 0)
        direction = RIGHT;
    else if(movement.x < 0)
        direction = LEFT;
    else if(movement.y > 0)
        direction = DOWN;
    else if(movement.y < 0)
        direction = UP;
    else
        moved = false;

    if(moved) {
    }

    auto checkChangedDirection = [&]() -> bool {
        bool restart = false;
        if(direction != old_direction) {
            old_direction = direction;
            restart       = true;
        }
        return restart;
    };

    if(moved) {
        m_animation.playAnimation(direction, checkChangedDirection());
        movement = thor::unitVector(movement);
        m_sprite.move(movement);
        moved = false;
    }
    else if(m_animation.isPlaying()) {
        m_animation.stop();
        /**
         * adicionar uma idle animation pra cada direção
         * std::map<enum_animId, enum_animId> idle;
         * idle[UP] = IDLE_UP;
         * ... etc
         * m_animation.playAnimation(idle[direction]);
         * */
    }
}

void Player::updateAnimation() {
    m_animation.animate();
}

Player *Player::getInstance() {
    static Player p;
    return &p;
}