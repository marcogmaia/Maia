#include "Player.hpp"

#include <python3.7m/Python.h>

Player::Player() {}
Player::~Player() {}

#define ASSETS_PATH "./assets/Commissions/Paladin.png"
void Player::setTexture() {
    m_texture.loadFromFile(ASSETS_PATH, sf::IntRect(0, 0, 16, 16));
}

// Player::Player() {
//     // m_animations.push_back[];
//     Animation anim;
//     m_texture.loadFromFile(ASSETS_PATH);
//     anim.setSpriteSheet(m_texture);

//     int width, height;
//     width = height = 16;

//     // WASD
//     for(int j = 0; j < 4; ++j) {
//         for(int i = 0; i < 4; ++i) {
//             anim.addFrame(sf::Rect(i * width, j * height, width, height));
//         }
//         m_animations.push_back(anim);
//     }
// }

void Player::setSprite() {
    sprite.setTexture(m_texture);
    sprite.scale(2, 2);
}
