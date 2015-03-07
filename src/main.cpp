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

#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>

#include "GameManager.h"
#include "ComponentMenu.h"

/*! Main function of the rendering thread. The actual rendering will be done
 *  within the currently displayed game component. */
static void render_function(const GameManager *game_manager, sf::RenderWindow *window) {
    sf::Clock frame_timer;

    // Handle rendering
    while (!game_manager->get_exit()) {
        window->clear(sf::Color::Black);

        // Let the game manager choose which component to render.
        game_manager->dispatch_rendering(*window, frame_timer.restart());
        
        window->display();
    }
}

/*! Main function. Instantiates the game, the drawing window and the rendering
 *  thread. */
int main() {
    // Create game manager instance
    GameManager game_manager;

    // Create the first game component: The main menu
    game_manager.push_component(std::make_shared<ComponentMenu>());
    // Assumption: From now on, the stack will never be empty.

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "JaPomoC");
    window.setVerticalSyncEnabled(true);
    game_manager.set_window(window);

    // Do all the rendering in a thread.
    window.setActive(false);
    std::thread render_thread(render_function, &game_manager, &window);

    // Handle events
    while (!game_manager.get_exit()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Let the game manager handle all events.
            game_manager.dispatch_event(event);
        }

        // Give the game (components) the chance to handle other things like
        // querying the keyboard.
        game_manager.dispatch_other();
    }

    // Join render thread
    render_thread.join();
    
    // Finally, close main window
    window.close();

    return EXIT_SUCCESS;
}