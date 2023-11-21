//
// Created by petroew on 20.11.23.
//
#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include <thread>
#include <functional>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.h>
#include <SFML/Network.h>

constexpr auto PI = 3.141592;
constexpr auto DEG = 57.29582;
constexpr auto RAD = 0.017453;

class Base;
typedef Base B;

using std::cos;
using std::cout;
using std::endl;
using std::to_string;
// using std::cosf;
using std::sin;
// using std::sinf;
// using std::atanf;
using std::atan;
using std::ifstream;
using std::list;
using std::make_shared;
using std::make_unique;
using std::ostream;
using std::shared_ptr;
using std::string;
using std::thread;
using std::unique_ptr;
using std::vector;

// сокращаем названия переменных и классов для удобства
typedef unsigned int uint;
typedef sf::Vector2i v2i;
typedef sf::Vector2f v2f;
typedef sf::Keyboard Key;
typedef sf::RectangleShape Shape;
typedef sf::Texture IMG;
typedef sf::Color Color;

// Перегрузка оператора вывода для v2f
inline ostream& operator<<(ostream& out, const v2f& p)
{
    out << "X: " << p.x << " | Y: " << p.y;
    return out;
}

// Перегрузка оператора вывода для v2i
inline ostream& operator<<(ostream& out, const v2i& p)
{
    out << "X: " << p.x << " | Y: " << p.y;
    return out;
}

// Перегрузка оператора вывода для Shape
inline ostream& operator<<(ostream& out, const Shape& s)
{
    out << "Position: " << s.getPosition() << endl;
    out << "Size: " << s.getSize() << endl;
    const auto& c = s.getFillColor();
    out << "Color: R = " << c.r << " G = " << c.g << " B = " << c.b << endl;
    return out;
}
