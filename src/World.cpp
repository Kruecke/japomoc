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

#include "World.h"

#include <cassert>
#include <iostream>
#include <string>

#include "Menu.h"
#include "tinyxml2.h"

World::World() {
    // Load player character
    const std::string char_path = "resources/images/tiny-16-basic/boy.xml";
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(char_path.c_str()) != tinyxml2::XML_NO_ERROR)
        std::cerr << "Could not load " << char_path << "!" << std::endl;

    tinyxml2::XMLElement *root = doc.FirstChildElement("character");
    assert(root != nullptr);
    tinyxml2::XMLElement *sheet = root->FirstChildElement("spritesheet");
    assert(sheet != nullptr);
    std::cout << "Sheet path: " << sheet->GetText() << "\n";

    for (auto animation_it = root->FirstChildElement("animation");
        animation_it != nullptr;
        animation_it = animation_it->NextSiblingElement("animation"))
    {
        std::string id = animation_it->Attribute("id"); // TODO: check nullptr
        std::cout << "Animation: " << id << "\n";

        for (auto frame_it = animation_it->FirstChildElement("frame");
            frame_it != nullptr;
            frame_it = frame_it->NextSiblingElement("frame"))
        {
            sf::IntRect frame;
            if (frame_it->QueryIntAttribute("x", &frame.left) != tinyxml2::XML_NO_ERROR)
                std::cerr << "Could not read attribute!" << std::endl;
            if (frame_it->QueryIntAttribute("y", &frame.top) != tinyxml2::XML_NO_ERROR)
                std::cerr << "Could not read attribute!" << std::endl;
            if (frame_it->QueryIntAttribute("width", &frame.width) != tinyxml2::XML_NO_ERROR)
                std::cerr << "Could not read attribute!" << std::endl;
            if (frame_it->QueryIntAttribute("height", &frame.height) != tinyxml2::XML_NO_ERROR)
                std::cerr << "Could not read attribute!" << std::endl;

            std::cout << "Frame: "
                      << frame.left << " " << frame.top << " "
                      << frame.width << " " << frame.height << "\n";
        }
    }
}

bool World::rendering_fills_scene() const {
    // The world is always screen filling.
    return true;
}

void World::render_scene(sf::RenderWindow &window) const {
    // TODO: Implement
}

void World::handle_event(sf::Event &event) {
    assert(m_game != nullptr);

    // TODO: Implement everthing

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            // Open up a menu
            m_game->push_component(std::make_shared<Menu>());
    }
}

void World::handle_other() {
    // TODO: Implement
}