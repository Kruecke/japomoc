#include "Game.h"
#include <SFML/Graphics.hpp>
#include <thread>

static void render_function(const Game *game, sf::RenderWindow *window) {
    // Handle rendering
    while (window->isOpen()) {
        window->clear(sf::Color::Black);

        // Let the game choose which component to render
        game->dispatch_rendering(*window);
        
        window->display();
    }
}

int main() {
    // Create game instance
    Game game;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "JaPomoC");
    window.setVerticalSyncEnabled(true);

    // Do all the rendering in a thread
    window.setActive(false);
    std::thread render_thread(render_function, &game, &window);

    // Handle events
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // "Close requested" event
            if (event.type == sf::Event::Closed)
                window.close();
                // TODO: Change to set game variable!
            
            // Let all other events be handled by the game
            game.dispatch_event(event);
        }

        // Give the game the chance to handle other things like querying the keyboard
        game.dispatch_other();
    }

    // Join render thread
    render_thread.join();

    return EXIT_SUCCESS;
}
