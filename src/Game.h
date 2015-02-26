#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GameComponent.h"

class Game {
    public:
        Game();

        /*! Returns true if the game is about to end. This might be due to a
         *  user input. */
        bool exit() const;

        /*! Push a game component which then will be rendered and handled. */
        void push_component(const std::shared_ptr<GameComponent>&);

        void dispatch_rendering(sf::RenderWindow&) const;
        void dispatch_event(sf::Event&);
        void dispatch_other() const;

    private:
        bool m_exit; //!< Whether the game is about to quit or not.
        std::vector<std::shared_ptr<GameComponent>> m_comp_stack;
};
