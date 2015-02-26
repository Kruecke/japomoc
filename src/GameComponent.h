#pragma once

#include <SFML/Graphics.hpp>

class GameComponent {
    public:
        GameComponent();
        virtual ~GameComponent();
        virtual bool rendering_fills_scene() const = 0;
        virtual void render_scene(sf::RenderWindow&) const = 0;
        virtual void handle_event(sf::Event&) = 0;
        virtual void handle_other() = 0;

        /*! Pause will be called by the game when the component goes to the background. */
        virtual void pause();
        /*! Resume will be called by the game when the component goes to the foreground. */
        virtual void resume();

    protected:
        bool m_active; //!< Tells whether this component is running or not. Every component starts inactive and is being activated by the game on demand.
};
