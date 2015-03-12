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

#include "TileMap.h"

#include <algorithm>
#include <iostream>
#include <tuple>

#include "tinyxml2.h"

static std::tuple<std::string, std::vector<sf::IntRect>>
get_tilesheet_from_xml(const std::string &path) {
    std::tuple<std::string, std::vector<sf::IntRect>> result;

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str()) != tinyxml2::XML_NO_ERROR) {
        std::cerr << "Could not load XML file \"" << path << "\"!" << std::endl;
        // TODO: Handle errors
    }

    tinyxml2::XMLElement *root = doc.FirstChildElement("tilesheet");
    if (root == nullptr) {
        std::cerr << "Could not find element \"tilesheet\"!" << std::endl;
        // TODO: Handle errors
    }

    // Sprite sheet
    tinyxml2::XMLElement *spritesheet = root->FirstChildElement("spritesheet");
    if (spritesheet == nullptr) {
        std::cerr << "Could not find element \"spritesheet\"!" << std::endl;
        // TODO: Handle errors
    }
    std::get<0>(result) = spritesheet->GetText();

    // Tile dimension
    tinyxml2::XMLElement *tiledimension = root->FirstChildElement("tiledimension");
    if (tiledimension == nullptr) {
        std::cerr << "Could not find element \"tiledimension\"!" << std::endl;
        // TODO: Handle errors
    }
    const char *attr_width = tiledimension->Attribute("width");
    if (attr_width == nullptr) {
        std::cerr << "Tiledimension tag without \"width\"!" << std::endl;
        // TODO: Handle errors
    }
    const char *attr_height = tiledimension->Attribute("height");
    if (attr_height == nullptr) {
        std::cerr << "Tiledimension tag without \"height\"!" << std::endl;
        // TODO: Handle errors
    }

    // Grid dimension
    tinyxml2::XMLElement *griddimension = root->FirstChildElement("griddimension");
    if (griddimension == nullptr) {
        std::cerr << "Could not find element \"griddimension\"!" << std::endl;
        // TODO: Handle errors
    }
    const char *attr_rows = griddimension->Attribute("rows");
    if (attr_rows == nullptr) {
        std::cerr << "Griddimension tag without \"rows\"!" << std::endl;
        // TODO: Handle errors
    }
    const char *attr_cols = griddimension->Attribute("cols");
    if (attr_cols == nullptr) {
        std::cerr << "Griddimension tag without \"cols\"!" << std::endl;
        // TODO: Handle errors
    }

    // TODO: check conversions?
    const int width = std::stoi(attr_width), height = std::stoi(attr_height);
    const int rows = std::stoi(attr_rows), cols = std::stoi(attr_cols);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            std::get<1>(result).emplace_back(col * width, row * height, width, height);
        }
    }

    return result;
}

bool TileMap::load_from_xml(const std::string &path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str()) != tinyxml2::XML_NO_ERROR) {
        std::cerr << "Could not load XML file \"" << path << "\"!" << std::endl;
        return false;
    }

    tinyxml2::XMLElement *root = doc.FirstChildElement("level");
    if (root == nullptr) {
        std::cerr << "Could not find element \"level\"!" << std::endl;
        return false;
    }

    // Load all tile sheets
    std::map<std::string, std::vector<sf::IntRect>> tilesheets;
    for (auto tilesheet_it = root->FirstChildElement("tilesheet");
        tilesheet_it != nullptr;
        tilesheet_it = tilesheet_it->NextSiblingElement("tilesheet"))
    {
        const char *attr_id = tilesheet_it->Attribute("id");
        if (attr_id == nullptr) {
            std::cerr << "Tilesheet tag without \"id\"!" << std::endl;
            return false;
        }

        const std::string sheet_path = tilesheet_it->GetText();
        auto tilesheet = get_tilesheet_from_xml(sheet_path);

        if (!m_textures[attr_id].loadFromFile(std::get<0>(tilesheet))) {
            std::cerr << "Could not load texture \"" << std::get<0>(tilesheet)
                      << "\"!" << std::endl;
            return false;
        }

        tilesheets.emplace(attr_id, std::move(std::get<1>(tilesheet)));
    }

    tinyxml2::XMLElement *tilemap = root->FirstChildElement("tilemap");
    if (tilemap == nullptr) {
        std::cerr << "Could not find element \"tilemap\"!" << std::endl;
        return false;
    }

    for (auto tile_it = tilemap->FirstChildElement("tile");
        tile_it != nullptr;
        tile_it = tile_it->NextSiblingElement("tile"))
    {
        // Read next tile
        Tile tile;

        const char *attr_sheet_id = tile_it->Attribute("sheet_id");
        if (attr_sheet_id == nullptr) {
            std::cerr << "Tile tag without \"sheet_id\"!" << std::endl;
            return false;
        }
        tile.m_sheet_id = attr_sheet_id;

        const char *attr_sheet_num = tile_it->Attribute("sheet_num");
        if (attr_sheet_num == nullptr) {
            std::cerr << "Tile tag without \"sheet_num\"!" << std::endl;
            return false;
        }
        auto &tex = tilesheets.at(attr_sheet_id).at(std::stoi(attr_sheet_num)); // TODO: check conversion?
        // TODO: This also might throw on illegal "sheet ids".

        const char *attr_map_x = tile_it->Attribute("map_x");
        if (attr_map_x == nullptr) {
            std::cerr << "Tile tag without \"map_x\"!" << std::endl;
            return false;
        }
        const char *attr_map_y = tile_it->Attribute("map_y");
        if (attr_map_y == nullptr) {
            std::cerr << "Tile tag without \"map_y\"!" << std::endl;
            return false;
        }

        // Set vertices
        const int x = std::stoi(attr_map_x), y = std::stoi(attr_map_y); // TODO: check conversion?
        tile.m_tile_vertices.append(sf::Vertex(
            sf::Vector2f((float) x * TILE_WIDTH, (float) y * TILE_HEIGHT),
            sf::Vector2f((float) tex.left, (float) tex.top)));
        tile.m_tile_vertices.append(sf::Vertex(
            sf::Vector2f((float) (x + 1) * TILE_WIDTH, (float) y * TILE_HEIGHT),
            sf::Vector2f((float) tex.left + tex.width, (float) tex.top)));
        tile.m_tile_vertices.append(sf::Vertex(
            sf::Vector2f((float) (x + 1) * TILE_WIDTH, (float) (y + 1) * TILE_HEIGHT),
            sf::Vector2f((float) tex.left + tex.width, (float) tex.top + tex.height)));
        tile.m_tile_vertices.append(sf::Vertex(
            sf::Vector2f((float) x * TILE_WIDTH, (float) (y + 1) * TILE_HEIGHT),
            sf::Vector2f((float) tex.left, (float) tex.top + tex.height)));
        tile.m_tile_vertices.setPrimitiveType(sf::Quads); // Vertice order matters!

        const char *attr_map_lvl = tile_it->Attribute("map_lvl");
        if (attr_map_lvl == nullptr) {
            std::cerr << "Tile tag without \"map_lvl\"!" << std::endl;
            return false;
        }
        tile.m_tile_level = std::stoi(attr_map_lvl); // TODO: check conversion?

        // Add tile
        m_tiles.emplace_back(std::move(tile));
    }

    // Prepare draw order. Sort first by tile level, then by texture (id).
    std::sort(m_tiles.begin(), m_tiles.end(),
        [](const Tile &a, const Tile &b) { return a.m_sheet_id < b.m_sheet_id; });
    std::stable_sort(m_tiles.begin(), m_tiles.end(),
        [](const Tile &a, const Tile &b) { return a.m_tile_level < b.m_tile_level; });

    return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // TODO: This can surely be optimized! Do it! Really! (Keep texture!)
    for (const auto& tile : m_tiles) {
        states.texture = &m_textures.at(tile.m_sheet_id);
        target.draw(tile.m_tile_vertices, states);
    }
}