#include "GameComponent.h"

GameComponent::GameComponent() : m_active(false) {}

GameComponent::~GameComponent() {}

void GameComponent::register_game(Game *game) {
    m_game = game;
}

void GameComponent::pause() {
    m_active = false;
}

void GameComponent::resume() {
    m_active = true;
}
