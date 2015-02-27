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

#include "AnimatedCharacter.h"

#include <iostream>
#include <string>

#include "tinyxml2.h"

AnimatedCharacter::AnimatedCharacter() : m_animations(4) {
    // Don't move upon creation
    m_animated_sprite.stop();
}

bool AnimatedCharacter::load_from_xml(const std::string &path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str()) != tinyxml2::XML_NO_ERROR) {
        std::cerr << "Could not load XML file \"" << path << "\"!" << std::endl;
        return false;
    }

    tinyxml2::XMLElement *root = doc.FirstChildElement("character");
    if (root == nullptr) {
        std::cerr << "Could not find element \"character\"!" << std::endl;
        return false;
    }

    tinyxml2::XMLElement *sheet = root->FirstChildElement("spritesheet");
    if (sheet == nullptr) {
        std::cerr << "Could not find element \"spritesheet\"!" << std::endl;
        return false;
    }

    // Load sprite sheet
    const std::string sheet_path = sheet->GetText();
    if (!m_sprite_sheet.loadFromFile(sheet_path)) {
        std::cerr << "Could not load texture \"" << sheet_path << "\"!" << std::endl;
        return false;
    }

    for (auto animation_it = root->FirstChildElement("animation");
        animation_it != nullptr;
        animation_it = animation_it->NextSiblingElement("animation"))
    {
        const char *attr_id = animation_it->Attribute("id");
        if (attr_id == nullptr) {
            std::cerr << "Animation tag without \"id\"!" << std::endl;
            return false;
        }

        Animation *animation = nullptr;
        const std::string id = attr_id;
        if (id.compare("up") == 0)
            animation = &m_animations.at(Direction::UP);
        else if (id.compare("down") == 0)
            animation = &m_animations.at(Direction::DOWN);
        else if (id.compare("left") == 0)
            animation = &m_animations.at(Direction::LEFT);
        else if (id.compare("right") == 0)
            animation = &m_animations.at(Direction::RIGHT);
        else {
            std::cerr << "Unknown animation id \"" << id << "\"!" << std::endl;
            return false;
        }

        // Add sprite sheet to animation
        animation->setSpriteSheet(m_sprite_sheet);

        for (auto frame_it = animation_it->FirstChildElement("frame");
            frame_it != nullptr;
            frame_it = frame_it->NextSiblingElement("frame"))
        {
            sf::IntRect frame;
            if (frame_it->QueryIntAttribute("x", &frame.left) != tinyxml2::XML_NO_ERROR) {
                std::cerr << "Could not read attribute \"x\"!" << std::endl;
                return false;
            }
            if (frame_it->QueryIntAttribute("y", &frame.top) != tinyxml2::XML_NO_ERROR) {
                std::cerr << "Could not read attribute \"y\"!" << std::endl;
                return false;
            }
            if (frame_it->QueryIntAttribute("width", &frame.width) != tinyxml2::XML_NO_ERROR) {
                std::cerr << "Could not read attribute \"width\"!" << std::endl;
                return false;
            }
            if (frame_it->QueryIntAttribute("height", &frame.height) != tinyxml2::XML_NO_ERROR) {
                std::cerr << "Could not read attribute \"height\"!" << std::endl;
                return false;
            }

            // Add frame to animation
            animation->addFrame(frame);
        }
    }

    // TODO: Check if the xml file provided all the information needed.

    return true;
}

AnimatedSprite& AnimatedCharacter::get_animated_sprite() {
    return m_animated_sprite;
}

void AnimatedCharacter::set_direction(Direction direction) {
    m_animated_sprite.setAnimation(m_animations.at(direction));
}