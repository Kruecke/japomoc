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

#include "GameManager.h"

/*! // TODO: write description!
*/
class GameComponent {
public:
    GameComponent();
    virtual ~GameComponent();

    /* ----- GameComponent interface. Overload these functions. ------------- */

    /*! Setup will be called once by the game when the component is about to go
     *  to the foreground for the first time. Do all your loading and
     *  preparations here (and not in the constructor).
     *
     *  The parameter 'next_to_this' gives you a reference to the component next
     *  to this one. // TODO: This needs some clear description. Might be long.
     *  This might even be a nullptr, if this is going to be the base component.
     *
     *  A loading screen might cover the screen while this function is being
     *  processed; see description of get_loading_screen(). */
    virtual void setup(const GameComponent* next_to_this) = 0;

    /*! Play will be called by the game when the component goes to the
    *  foreground. The component is (again) at the top of the stack. */
    virtual void play() = 0;

    /*! Pause will be called by the game when the component goes to the
     *  background. The component is (yet) at the top of the stack. */
    virtual void pause() = 0;

    /*! Returns true if this component fills the whole view. If it returns
     *  false, the underlying component will be drawn as well. */
    virtual bool rendering_fills_scene() const = 0;

    /*! Returns a nullptr if this component doesn't use any loading screen or
     *  some instance of GameComponent that implements a loading screen.
     *
     *  If this GameComponent implements a loading screen (which means a
     *  instance of this is returned by this function of some other
     *  GameComponent implementation), this function is not going to be called
     *  in the first place. (No endless recursion will happen.) */
    virtual std::shared_ptr<GameComponent> get_loading_screen() const = 0;

    /*! Will be called by the game to render the scene. Implement your drawing
     *  here. The time that has passed since the last frame draw is passed as
     *  the second parameter. This can be useful to progress animations.
     *
     *  Important note: This function is called in a seperate rendering thread
     *  and so might be run in parallel to the event handling functions! Keep
     *  that in mind when your accessing resources that might be changed in any
     *  other function of this interface. Only setup(...) is guaranteed to be
     *  called (and finished) before this function is invoked the first time. */
    virtual void render_scene(sf::RenderWindow&, const sf::Time &frame_time_delta) = 0;

    /*! Will be called by the game to handle event. Implement your event
     *  handling here. */
    virtual void handle_event(sf::Event&) = 0;

    /*! Will be called by the game to handle other things. You can use this
     *  function to implement other handling like querying the keyboard. */
    virtual void handle_other() = 0;

    /* ----- End of GameComponent interface. -------------------------------- */

    /* There should be no need to override the following functions. */

    /*! Keep a reference back to the GameManager instance. This function will be
     *  called by the game before the component is pushed to the game component
     *  stack. */
    virtual void register_game_manager(GameManager*);

protected:
    GameManager *m_game_manager; //!< Reference to the game manager instance.
};