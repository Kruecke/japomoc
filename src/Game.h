#pragma once

#include <SFML/Graphics.hpp>

class Game {
    public:
        /*! Returns true if the game is about to end. This might be due to a
         *  user input. */
        bool exit() const;

        void dispatch_rendering(sf::RenderWindow&) const;
        void dispatch_event(sf::Event&);
        void dispatch_other() const;

    private:
        bool m_exit; //!< Whether the game is about to quit or not.
};
