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
