#pragma once

#include "GameComponent.h"

class Menu : public GameComponent {
    public:
        virtual bool rendering_fills_scene() const;
        virtual void render_scene(sf::RenderWindow&) const;
        virtual void handle_event(sf::Event&);
        virtual void handle_other();
};
