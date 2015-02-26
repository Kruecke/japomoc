#include "Game.h"

#include <cassert>

Game::Game() : m_exit(false) {}

bool Game::exit() const {
    return m_exit;
}

void Game::push_component(const std::shared_ptr<GameComponent>& component) {
    // Pause the current component
    if (!m_comp_stack.empty())
        m_comp_stack.back()->pause();

    // Push component to stack and make it active
    m_comp_stack.emplace_back(component);
    component->resume();
}

void Game::dispatch_rendering(sf::RenderWindow &window) const {
    assert(!m_comp_stack.empty());

    m_comp_stack.back()->render_scene(window);
}

void Game::dispatch_event(sf::Event &event) {
    assert(!m_comp_stack.empty());

    // Catch "close requested" events
    if (event.type == sf::Event::Closed)
        m_exit = true;

    // Let all other events be handled by the current game component.
    m_comp_stack.back()->handle_event(event);
}

void Game::dispatch_other() const {
    assert(!m_comp_stack.empty());

    m_comp_stack.back()->handle_other();
}
