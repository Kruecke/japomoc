#include "Menu.h"

#include <SFML/Graphics.hpp>

bool Menu::rendering_fills_scene() const {
    // Menu will cover the whole screen.
    return true;
}

void Menu::render_scene(sf::RenderWindow &window) const {
    // TODO
    sf::Font dejavu;
    if (dejavu.loadFromFile("resources/dejavu-fonts/DejaVuSans.ttf"))
        window.draw(sf::Text("Test!", dejavu));
}

void Menu::handle_event(sf::Event &event) {
    // TODO
}

void Menu::handle_other() {
    // TODO
}
