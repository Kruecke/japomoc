#include "GameComponent.h"

GameComponent::GameComponent() : m_active(false) {}

GameComponent::~GameComponent() {}

void GameComponent::pause() {
    m_active = false;
}

void GameComponent::resume() {
    m_active = true;
}
