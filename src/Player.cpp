#include "Player.hpp"

#include "Thor/Vectors.hpp"

#include <fmt/format.h>
#include <iostream>

#define ASSETS_PATH                                                            \
    "/home/marco/dev/cpp/games/maia/assets/Commissions/Paladin32x.png"
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32

Player::Player() {
    animSprite = AnimatedSprite();
    m_mapAnimation[DOWN] = Animation();
    m_mapAnimation[LEFT] = Animation();
    m_mapAnimation[RIGHT] = Animation();
    m_mapAnimation[UP] = Animation();

    m_texture.loadFromFile(ASSETS_PATH);
    /**
     * AnimatedSprite only takes care of the animation
     * of the Animation class
     *
     * We need a animation for each of the player animation
     * */
    for(auto &&i : m_mapAnimation) {
        i.second.setSpriteSheet(m_texture);
    }
    auto setFrames = [](Animation &anim, sf::Vector2i initialPos) {
        sf::IntRect rect;
        for(int i = 0; i < 4; ++i) {
            rect.left = initialPos.x + i * SPRITE_WIDTH;
            rect.top = initialPos.y;
            rect.width = SPRITE_WIDTH;
            rect.height = SPRITE_HEIGHT;
            anim.addFrame(rect);
        }
    };
    setFrames(m_mapAnimation[DOWN], sf::Vector2i(0, 0));
    setFrames(m_mapAnimation[LEFT], sf::Vector2i(0, SPRITE_HEIGHT * 1));
    setFrames(m_mapAnimation[RIGHT], sf::Vector2i(0, SPRITE_HEIGHT * 2));
    setFrames(m_mapAnimation[UP], sf::Vector2i(0, SPRITE_HEIGHT * 3));
    /**
     * once with all the animations set up
     * we can can use AnimatedSprite
     * this class only takes care of the animations
     */
    animSprite.setOrigin(SPRITE_WIDTH / 2, SPRITE_HEIGHT / 2);
    animSprite.play(m_mapAnimation[DOWN]);
}

Player::~Player() {}

void Player::walk() {
    float velocity = 1.f;
    static bool moved = false;
    direction_t direction = UP;
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
        animSprite.play(m_mapAnimation[direction]);
        movement = thor::unitVector(movement);
        // Vector2Math::normalize(movement);
        animSprite.move(movement);
        moved = false;
    }
    else if(animSprite.isPlaying()) {
        animSprite.stop();
    }
}

Player *Player::getInstance() {
    static Player p;
    return &p;
}