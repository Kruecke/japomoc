#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <cassert>

bool Menu::rendering_fills_scene() const {
    // Menu will cover the whole screen.
    return true;
}

void Menu::render_scene(sf::RenderWindow &window) const {
    assert(m_game != nullptr);
    // TODO
    window.draw(sf::Text("Test!", m_game->font()));
}

void Menu::handle_event(sf::Event &event) {
    // TODO
}

void Menu::handle_other() {
    // TODO
}
