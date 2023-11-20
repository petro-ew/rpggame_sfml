//
// Created by petroew on 20.11.23.
//
#pragma once
#include "../Define.h"

struct Font{
    sf::Font common;
    Font() {
        common.loadFromFile("Resources/Fonts/common.ttf");
    }
    ~Font(){}
};
