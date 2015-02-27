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
#include <memory>
#include <vector>

class GameComponent;

class Game {
    public:
        Game();

        /*! Pushes a game component which then will be rendered and used to
         *  handle events. */
        void push_component(const std::shared_ptr<GameComponent>&);

        /*! Pops the current game component and returns running the next one. */
        void pop_component();

        /*! Return the game component on stack right below the given one. A
         *  nullptr will be returned if there is no match. (Which means that
         *  either the given component is the base of the stack or the given
         *  component is not on the stack at all.) */
        std::shared_ptr<GameComponent> next_component_to(GameComponent*) const;

        /*! Called by the render thread to pass control of what will be drawn to
         *  the game. The time that has passed since the last frame draw is
         *  passed as a second parameter. */
        void dispatch_rendering(sf::RenderWindow&, const sf::Time &frame_time_delta) const;
        /*! Called by the main thread to handle events. */
        void dispatch_event(sf::Event&);
        /*! Called by the main thread to give the game a chance to handle other
         *  things like querying the keyboard. */
        void dispatch_other() const;

        /*! Get the common game font. */
        const sf::Font& font() const;

        /*! Returns true if the game is about to end. This might be due to a
        *  user input. */
        bool exit() const;

        /*! Request game exit by passing 'true' or cancel a request by passing
         *  'false'. */
        void exit(bool);

    private:
        std::vector<std::shared_ptr<GameComponent>> m_comp_stack;
        sf::Font m_font; //!< Common game font
        bool     m_exit; //!< Whether the game is about to quit or not
};
