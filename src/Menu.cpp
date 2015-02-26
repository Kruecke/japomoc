#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <cassert>

Menu::Menu() : m_cursor_pos(0) {
    //m_items.emplace_back("Do noting!", []() {});

    m_items.emplace_back("Quit game", [this]() {
        assert(m_game != nullptr);
        m_game->exit(true);
    });
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
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            m_cursor_pos = (m_cursor_pos - 1 + m_items.size()) % m_items.size();
        if (event.key.code == sf::Keyboard::Down)
            m_cursor_pos = (m_cursor_pos + 1) % m_items.size();
        if (event.key.code == sf::Keyboard::Return) {
            std::get<1>(m_items[m_cursor_pos])();
        }
    }
}

void Menu::handle_other() {
    // TODO
}

void Menu::render_menu(sf::RenderWindow &window) const {
    assert(m_game != nullptr);

    const sf::Vector2f view_size = window.getView().getSize();

    for (std::size_t i = 0; i < m_items.size(); ++i) {
        // TODO: Improve that arrow!
        std::string text = std::get<0>(m_items[i]);
        if (i == m_cursor_pos)
            text = "--> " + text;

        sf::Text item(text, m_game->font());

        // Center text horizontally and set vertical offset
        sf::FloatRect bounds = item.getLocalBounds();
        item.setPosition((view_size.x - bounds.width)  * 0.5f,
                  (0.5f * view_size.y - bounds.height) * 0.5f);

        // Move to correct vertical position
        if (m_items.size() == 1)
            item.move(0.0f, view_size.y * 0.25f); // Move to middle
        else
            item.move(0.0f, ((float) i / (m_items.size() - 1)) * view_size.y * 0.5f);

        window.draw(item);
    }
}
