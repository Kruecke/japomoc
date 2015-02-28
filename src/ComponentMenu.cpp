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

#include "ComponentMenu.h"

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <string>

#include "ComponentWorld.h"

ComponentMenu::ComponentMenu() : m_cursor_position(0) {}

void ComponentMenu::setup() {
    assert(m_game_manager != nullptr);

    // Load background image
    const std::string bg_path = "resources/images/menu_background.png";
    if (!m_background.loadFromFile(bg_path))
        std::cerr << "Could not load texture \"" + bg_path << "\"!" << std::endl;

    // Load music
    const std::string music_path = "resources/audio/menu.ogg";
    if (!m_music.openFromFile(music_path))
        std::cerr << "Could not load music \"" + music_path << "\"!" << std::endl;
    m_music.setLoop(true);

    // Check game component below and add menu entries
    auto next = m_game_manager->next_component_to(this);
    if (next == nullptr) {
        // This is the base menu. Add a button to start the game.
        m_items.emplace_back("Start game", [this]() {
            assert(m_game_manager != nullptr);
            m_game_manager->push_component(std::make_shared<ComponentWorld>());
        });
    }
    else if (typeid(*next) == typeid(ComponentWorld)) {
        // This is a "pause" menu. Add a button to get back to the game.
        m_items.emplace_back("Back to game", [this]() {
            assert(m_game_manager != nullptr);
            m_game_manager->pop_component();
        });
    }
    // TODO: Add further situations

    // There is always a button to quit the game.
    m_items.emplace_back("Quit game", [this]() {
        assert(m_game_manager != nullptr);
        m_game_manager->set_exit(true);
    });
}

void ComponentMenu::play() {
    // Start music
    m_music.play();
}

void ComponentMenu::pause() {
    // Stop music
    m_music.stop();
}

bool ComponentMenu::rendering_fills_scene() const {
    // Menu will cover the whole screen.
    return true;
}

void ComponentMenu::render_scene(sf::RenderWindow &window, const sf::Time &frame_time_delta) {
    // TODO: Make everything beautiful!
    render_background(window);
    render_menu(window);
}

void ComponentMenu::handle_event(sf::Event &event) {
    assert(m_game_manager != nullptr);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            m_cursor_position = (m_cursor_position - 1 + m_items.size()) % m_items.size();
        if (event.key.code == sf::Keyboard::Down)
            m_cursor_position = (m_cursor_position + 1) % m_items.size();

        if (event.key.code == sf::Keyboard::Return)
            // Execute item function
            std::get<1>(m_items[m_cursor_position])();

        if (event.key.code == sf::Keyboard::Escape) {
            // If this is not a base menu, make 'escape' go back last component.
            if (m_game_manager->next_component_to(this) != nullptr)
                m_game_manager->pop_component();
        }
    }
}

void ComponentMenu::handle_other() {
    // Nothing to do here
}

void ComponentMenu::render_background(sf::RenderWindow &window) const {
    const sf::Vector2f view_size = window.getView().getSize();
    const sf::Vector2u tex_size  = m_background.getSize();

    sf::Sprite background(m_background);
    background.setScale(view_size.x / tex_size.x, view_size.y / tex_size.y);
    window.draw(background);
}

void ComponentMenu::render_menu(sf::RenderWindow &window) const {
    assert(m_game_manager != nullptr);

    const sf::Vector2f view_size = window.getView().getSize();

    for (std::size_t i = 0; i < m_items.size(); ++i) {
        // TODO: Improve that arrow!
        std::string text = std::get<0>(m_items[i]);
        if (i == m_cursor_position)
            text = "--> " + text;

        // Generate text for item
        sf::Text item(text, m_game_manager->get_font());
        item.setColor(sf::Color::Black);

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