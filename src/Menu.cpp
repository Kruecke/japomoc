/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Florian Klemme <mail@florianklemme.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <string>

#include "World.h"

Menu::Menu() : m_cursor_pos(0) {
    // Add basic menu entries
    m_items.emplace_back("Quit game", [this]() {
        assert(m_game != nullptr);
        m_game->exit(true);
    });

    // Load background image
    const std::string bg_path = "resources/images/menu_background.png";
    if (!m_background.loadFromFile(bg_path))
        std::cerr << "Could not load " + bg_path << "!" << std::endl;

    // Load music
    const std::string music_path = "resources/audio/menu.ogg";
    if (!m_music.openFromFile(music_path))
        std::cerr << "Could not load " + music_path << "!" << std::endl;
    m_music.setLoop(true);
}

bool Menu::rendering_fills_scene() const {
    // Menu will cover the whole screen.
    return true;
}

void Menu::render_scene(sf::RenderWindow &window) const {
    // TODO: Make everything beautiful!
    render_background(window);
    render_menu(window);
}

void Menu::handle_event(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            m_cursor_pos = (m_cursor_pos - 1 + m_items.size()) % m_items.size();
        if (event.key.code == sf::Keyboard::Down)
            m_cursor_pos = (m_cursor_pos + 1) % m_items.size();
        if (event.key.code == sf::Keyboard::Return)
            // Execute item function
            std::get<1>(m_items[m_cursor_pos])();
    }
}

void Menu::handle_other() {
    // Nothing to do here
}

void Menu::register_game(Game *game) {
    // Call base class implementation. See GameComponent header commentary.
    GameComponent::register_game(game);

    // Check game component below and add menu entries
    auto next = game->next_component_to(this);
    if (next == nullptr) {
        // This is the base menu. Add a button to start the game.
        m_items.emplace(m_items.begin(), "Start game", [this]() {
            assert(m_game != nullptr);
            m_game->push_component(std::make_shared<World>());
        });
    } else if (typeid(*next) == typeid(World)) {
        // This is a "pause" menu. Add a button to get back to the game.
        m_items.emplace(m_items.begin(), "Back to game", [this]() {
            assert(m_game != nullptr);
            m_game->pop_component();
        });
    }
    // TODO: Add further situations
}

void Menu::pause() {
    // Call base class implementation. See GameComponent header commentary.
    GameComponent::pause();

    // Stop music
    m_music.stop();
}

void Menu::resume() {
    // Call base class implementation. See GameComponent header commentary.
    GameComponent::resume();

    // Start music
    m_music.play();
}

void Menu::render_background(sf::RenderWindow &window) const {
    const sf::Vector2f view_size = window.getView().getSize();
    const sf::Vector2u tex_size  = m_background.getSize();

    sf::Sprite background(m_background);
    background.setScale(view_size.x / tex_size.x, view_size.y / tex_size.y);
    window.draw(background);
}

void Menu::render_menu(sf::RenderWindow &window) const {
    assert(m_game != nullptr);

    const sf::Vector2f view_size = window.getView().getSize();

    for (std::size_t i = 0; i < m_items.size(); ++i) {
        // TODO: Improve that arrow!
        std::string text = std::get<0>(m_items[i]);
        if (i == m_cursor_pos)
            text = "--> " + text;

        // Generate text for item
        sf::Text item(text, m_game->font());
        item.setColor(sf::Color::Black);

        // Center text horizontally and set vertical offset
        sf::FloatRect bounds = item.getLocalBounds();
        item.setPosition((view_size.x - bounds.width)  * 0.5f,
                  (0.5f * view_size.y - bounds.height) * 0.5f);

        // Move to correct vertical position
        if (m_items.size() == 1)
            item.move(0.0f, view_size.y * 0.25f); // Move to middle
        else
            item.move(0.0f,
                ((float) i / (m_items.size() - 1)) * view_size.y * 0.5f);

        window.draw(item);
    }
}
