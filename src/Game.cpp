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

#include "Game.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "GameComponent.h"

Game::Game() : m_exit(false) {
    // Load game font
    const std::string font_path = "resources/dejavu-fonts/DejaVuSans.ttf";
    if(!m_font.loadFromFile(font_path))
        std::cerr << "Could not load font \"" << font_path << "\"!" << std::endl;
}

void Game::push_component(const std::shared_ptr<GameComponent>& component) {
    // Pause the current (foreground) component
    if (!m_comp_stack.empty())
        m_comp_stack.back()->pause();

    // Push component to stack and make it running
    m_comp_stack.emplace_back(component);
    component->register_game(this);
    // TODO: Maybe do a "fade animation" or something here? The call to
    //       'register_game' could actually take some time, depending on what
    //       the implementer has choosed to do there.
    component->resume();
}

void Game::pop_component() {
    // Pause and remove the current component
    m_comp_stack.back()->pause();
    m_comp_stack.pop_back();

    // Run the next component
    assert(m_comp_stack.size() > 0);
    m_comp_stack.back()->resume();
}

std::shared_ptr<GameComponent>
Game::next_component_to(GameComponent *component) const {
    // Search component in stack
    auto it = std::find_if(m_comp_stack.begin(), m_comp_stack.end(),
        [&](const std::shared_ptr<GameComponent> &stack_comp) {
            return stack_comp.get() == component;
        });

    if (it == m_comp_stack.end() || // Component not found
        it == m_comp_stack.begin()) // Component is the last in stack
        return nullptr;
    else
        return *(it - 1);
}

void Game::dispatch_rendering(sf::RenderWindow &window, const sf::Time &frame_time_delta) const {
    assert(!m_comp_stack.empty());

    m_comp_stack.back()->render_scene(window, frame_time_delta);
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

const sf::Font& Game::font() const {
    return m_font;
}

bool Game::exit() const {
    return m_exit;
}

void Game::exit(bool exit) {
    // TODO: Ask the user?
    m_exit = exit;
}