#include "Game.h"

bool Game::exit() const {
    return m_exit;
}

void Game::dispatch_rendering(sf::RenderWindow &window) const {
    // TODO
}

void Game::dispatch_event(sf::Event &event) {
    // Catch "close requested" events
    if (event.type == sf::Event::Closed)
        m_exit = true;

    // Let all other events be handled by the current game component
    //game.dispatch_event(event);
}

void Game::dispatch_other() const {
    // TODO
}
