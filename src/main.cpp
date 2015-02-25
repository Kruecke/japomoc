#include <SFML/Graphics.hpp>
#include <thread>

#include "Game.h"

/*! Main function of the rendering thread. The actual rendering will be done
 *  by the current game component. */
static void render_function(const Game *game, sf::RenderWindow *window) {
    // Handle rendering
    while (!game->exit()) {
        window->clear(sf::Color::Black);

        // Let the game choose which component to render.
        game->dispatch_rendering(*window);
        
        window->display();
    }
}

/*! Main function. Instantiate the game, the drawing window and the rendering
 *  thread. */
int main() {
    // Create game instance
    Game game;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "JaPomoC");
    window.setVerticalSyncEnabled(true);

    // Do all the rendering in a thread.
    window.setActive(false);
    std::thread render_thread(render_function, &game, &window);

    // Handle events
    while (!game.exit()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Let the game handle all events.
            game.dispatch_event(event);
        }

        // Give the game the chance to handle other things like querying the keyboard.
        game.dispatch_other();
    }

    // Join render thread
    render_thread.join();
    
    // Finally, close main window
    window.close();

    return EXIT_SUCCESS;
}
