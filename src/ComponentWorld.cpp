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

#include "ComponentWorld.h"

#include <cassert>
#include <iostream>
#include <string>

#include "ComponentMenu.h"

void ComponentWorld::setup() {
    // Load map. TODO!
    sf::Vector2f player_pos(100, 100); // from map

    // Generate a new (most likely smaller) view
    sf::Vector2f view_size(800, 600);
    m_view = sf::View(player_pos, view_size);

    // Load player character
    const std::string char_path = "resources/images/tiny-16-basic/boy.xml";
    if (!m_player.load_from_xml(char_path)) {
        std::cerr << "Could not load player character \"" << char_path << "\"!" << std::endl;
        return; // TODO: Handle errors
    }

    // Place player character. TODO: fix position and scale
    m_player.get_animated_sprite().setPosition(player_pos);
    m_player.get_animated_sprite().setScale(2, 2);

    // Player looks down by default
    m_player.set_direction(AnimatedCharacter::Direction::DOWN);
}

void ComponentWorld::play() {
    // TODO: Implement
}

void ComponentWorld::pause() {
    // TODO: Implement
}

bool ComponentWorld::rendering_fills_scene() const {
    // The world is always screen filling.
    return true;
}

void ComponentWorld::render_scene(sf::RenderWindow &window, const sf::Time &frame_time_delta) {
    window.setView(m_view);

    // TODO: Implement
    AnimatedSprite &player_sprite = m_player.get_animated_sprite();
    player_sprite.update(frame_time_delta);
    window.draw(player_sprite);
}

void ComponentWorld::handle_event(sf::Event &event) {
    assert(m_game_manager != nullptr);

    // TODO: Implement everthing

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            // Open up a menu
            m_game_manager->push_component(std::make_unique<ComponentMenu>());
    }
}

void ComponentWorld::handle_other() {
    // TODO: Implement
}