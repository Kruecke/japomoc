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

#include "GameManager.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "GameComponent.h"

GameManager::GameManager() : m_exit(false), m_window(nullptr) {
    // Load game font
    const std::string font_path = "resources/dejavu-fonts/DejaVuSans.ttf";
    if(!m_font.loadFromFile(font_path))
        std::cerr << "Could not load font \"" << font_path << "\"!" << std::endl;
}

void GameManager::push_component(const std::shared_ptr<GameComponent>& component) {
    // Basic stack change concept:
    //     1) Pause old foreground component
    //     2) Update stack
    //     3) Make the new foreground component play
    // This means that a component might be drawn after the call to pause or
    // before the call to play! So it is essential that every component is ready
    // to be drawn after its setup implementation has been called.

    std::shared_ptr<GameComponent> below_component; // next on the stack
    {
        std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // TODO: shared lock
        below_component = !m_comp_stack.empty() ? m_comp_stack.back() : nullptr;
    }

    // Do we have a loading screen for switching to component?
    auto loading_screen = component->get_loading_screen();
    if (loading_screen != nullptr) {
        // Set up loading screen. (This is better be done fast.)
        loading_screen->register_game_manager(this);
        loading_screen->setup(component.get());

        // Pause the current foreground component.
        if (below_component != nullptr)
            below_component->pause();

        // Push loading screen to the stack and make it play.
        {
            std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // lock for change
            m_comp_stack.emplace_back(loading_screen);
        }
        loading_screen->play();
    }

    // Prepare component. The loading screen is displayed while this is running.
    component->register_game_manager(this);
    component->setup(below_component.get());

    // Done setting up. Replace loading screen with actual component to draw.
    {
        // Pause foreground component.
        if (loading_screen != nullptr)
            loading_screen->pause();
        else if (below_component != nullptr)
            below_component->pause();

        // Push component to the stack and make it play.
        {
            std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // lock for change
            if (loading_screen != nullptr)
                m_comp_stack.pop_back();
            m_comp_stack.emplace_back(component);
        }
        component->play();
    }
}

void GameManager::pop_component() {
    std::shared_ptr<GameComponent> current, next;

    // Get the current and the next component to play.
    {
        std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // TODO: shared lock
        assert(m_comp_stack.size() >= 2); // We'll never pop the last element!
        auto last = m_comp_stack.rbegin();
        current = *last;
        next = *++last;
    }

    // Pause the current foreground component.
    current->pause();

    // Lock stack and pop back.
    {
        std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // lock for change
        m_comp_stack.pop_back();
    }

    // Play the next component.
    next->play();
}

std::shared_ptr<GameComponent> GameManager::next_component_to(GameComponent *component) const {
    std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // TODO: shared lock

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

void GameManager::dispatch_rendering(sf::RenderWindow &window, const sf::Time &frame_time_delta) const {
    // Take part in ownership of components to draw.
    std::vector<std::shared_ptr<GameComponent>> components;

    // Take part in the ownership of all components to render.
    {
        std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // TODO: shared lock
        // Assumptions: The stack is never empty and (at least) the bottom
        //              component is always screen filling!
        assert(!m_comp_stack.empty());
        assert(m_comp_stack.begin()->get()->rendering_fills_scene());

        // Find topmost component that is screen filling.
        auto it = m_comp_stack.end() - 1;
        while (!it->get()->rendering_fills_scene())
            --it;

        // Take part in ownership to prevent concurrent deleting.
        std::copy(it, m_comp_stack.end(), std::back_inserter(components));
    }

    // Render all components from the topmost screen filling to the top.
    for (auto &comp : components)
        comp->render_scene(window, frame_time_delta);
}

void GameManager::dispatch_event(sf::Event &event) {
    // Catch "close requested" events
    if (event.type == sf::Event::Closed)
        set_exit(true);

    // Take part in component ownership.
    std::shared_ptr<GameComponent> component;
    {
        std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // TODO: shared lock
        assert(!m_comp_stack.empty());
        component = m_comp_stack.back();
    }

    // Let all other events be handled by the current game component.
    component->handle_event(event);
}

void GameManager::dispatch_other() const {
    // Take part in component ownership.
    std::shared_ptr<GameComponent> component;
    {
        std::lock_guard<std::mutex> lock(m_comp_stack_mutex); // TODO: shared lock
        assert(!m_comp_stack.empty());
        component = m_comp_stack.back();
    }

    // Let the component handle other things.
    component->handle_other();
}

const sf::Font& GameManager::get_font() const {
    return m_font;
}

bool GameManager::get_exit() const {
    return m_exit;
}

void GameManager::set_exit(bool exit) {
    // TODO: Ask the user?
    m_exit = exit;
}

const sf::RenderWindow& GameManager::get_window() const {
    assert(m_window != nullptr);
    return *m_window;
}

void GameManager::set_window(const sf::RenderWindow &window) {
    m_window = &window;
}