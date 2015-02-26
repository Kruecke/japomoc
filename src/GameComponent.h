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

        /* The following functions can be overriden as well, if you need a hook
         * to the moment when your component becomes registered, paused or
         * resumed. If you do override them, make sure to call their base
         * implementation as well to not break other functionality. */

        /*! This function will be called by the game right after the component
         *  has been pushed to the game component stack. */
        virtual void register_game(Game*);
        /*! Pause will be called by the game when the component goes to the
         *  background. The component is (still) at the top of the stack. */
        virtual void pause();
        /*! Resume will be called by the game when the component goes to the
         *  foreground. The component is (again) at the top of the stack. */
        virtual void resume();

    protected:
        Game *m_game;  //!< Reference to the game instance.
        bool m_active; /*!< Tells whether this component is running or not.
                        *   Every component starts inactive and is being
                        *   activated by the game on demand. */
};
