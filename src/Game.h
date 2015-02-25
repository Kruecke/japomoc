#pragma once

#include <SFML/Graphics.hpp>

class Game {
    public:
        void dispatch_rendering(sf::RenderWindow&) const;
        void dispatch_event(sf::Event&) const;
        void dispatch_other() const;
};
