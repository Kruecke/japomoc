#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <cassert>
#include <vector>

Menu::Menu() : m_cursor_pos(0) {
    m_items.emplace_back("First!");
    m_items.emplace_back("Second");
    m_items.emplace_back("And a third one");
    m_items.emplace_back("One more!");
}

bool Menu::rendering_fills_scene() const {
    // Menu will cover the whole screen.
    return true;
}

void Menu::render_scene(sf::RenderWindow &window) const {
    // TODO
    render_menu(window);
}

void Menu::handle_event(sf::Event &event) {
    // TODO
}

void Menu::handle_other() {
    // TODO
}

void Menu::render_menu(sf::RenderWindow &window) const {
    assert(m_game != nullptr);

    const sf::Vector2f view_size = window.getView().getSize();

    for (std::size_t i = 0; i < m_items.size(); ++i) {
        sf::Text item(m_items[i], m_game->font());
        // Center text horizontally and set vertical offset
        sf::FloatRect bounds = item.getLocalBounds();
        item.setPosition((view_size.x - bounds.width)  * 0.5f,
                  (0.5f * view_size.y - bounds.height) * 0.5);

        // Move to correct vertical position
        item.move(0.0f, ((float) i / (m_items.size() - 1)) * view_size.y * 0.5f);

        window.draw(item);
    }
}
