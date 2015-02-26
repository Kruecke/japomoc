#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

class GameComponent {
    public:
        GameComponent();
        virtual ~GameComponent();

        /* ----- GameComponent interface. Overload these functions. --------- */

        /*! Returns true if this component fill the whole view. If it returns
         *  false, the underlying component will be drawn as well. */
        virtual bool rendering_fills_scene() const = 0;

        /*! Will be called by the game to render the view. Implement your
         *  drawing here. */
        virtual void render_scene(sf::RenderWindow&) const = 0;

        /*! Will be called by the game to handle event. Implement your event
         *  handling here. */
        virtual void handle_event(sf::Event&) = 0;

        /*! Will be called by the game to handle other things. You can use this
         *  function to implement other handling like querying the keyboard. */
        virtual void handle_other() = 0;

        /* ----- End of GameComponent interface. ---------------------------- */

        /*! This function will be called by the game when the component is
         *  pushed to the game component stack. */
        virtual void register_game(Game*);
        /*! Pause will be called by the game when the component goes to the
         *  background. */
        virtual void pause();
        /*! Resume will be called by the game when the component goes to the
         *  foreground. */
        virtual void resume();

    protected:
        Game *m_game;  //!< Reference to the game instance.
        bool m_active; /*!< Tells whether this component is running or not.
                        *   Every component starts inactive and is being
                        *   activated by the game on demand. */
};
