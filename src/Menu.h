/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Florian Klemme
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

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "GameComponent.h"

class Menu : public GameComponent {
    public:
        Menu();

        /* ----- GameComponent interface ------------------------------------ */
        virtual bool rendering_fills_scene() const override;
        virtual void render_scene(sf::RenderWindow&) const override;
        virtual void handle_event(sf::Event&) override;
        virtual void handle_other() override;
        /* ----- End of GameComponent interface ----------------------------- */

        virtual void register_game(Game*) override;
        virtual void pause() override;
        virtual void resume() override;

    private:
        void render_background(sf::RenderWindow&) const;
        void render_menu(sf::RenderWindow&) const;

        std::vector<std::tuple<std::string, std::function<void(void)>>> m_items;
        std::size_t m_cursor_pos; //!< Menu item pointed on by the cursor
        sf::Texture m_background; //!< Background texture
        sf::Music   m_music;      //!< Menu music
};
