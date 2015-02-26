#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "GameComponent.h"

class Menu : public GameComponent {
    public:
        Menu();

        /* ----- GameComponent interface ------------------------------------ */
        virtual bool rendering_fills_scene() const;
        virtual void render_scene(sf::RenderWindow&) const;
        virtual void handle_event(sf::Event&);
        virtual void handle_other();
        /* ----- End of GameComponent interface ----------------------------- */

    private:
        void render_menu(sf::RenderWindow&) const;

        std::vector<std::tuple<std::string, std::function<void(void)>>> m_items;
        int m_cursor_pos; //!< Menu item pointed on by the cursor.
};
