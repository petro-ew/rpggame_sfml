//
// Created by petroew on 20.11.23.
//
#pragma once
#include "../Define.h"
class Texture
{
private:
    IMG Load(const string file, bool isSmooth = false)
    {
        IMG texture;
        texture.loadFromFile("resources/images/" + file);
        texture.setSmooth(isSmooth); // Применять сглаживание только для вращающихся объектов
        return texture;
    }
    
public:
    vector<IMG> terrains;
    vector<IMG> units;
    vector<IMG> effects;
    vector<IMG> decorations;
    vector<IMG> grass;
    
    IMG test_image;
    
    Texture() {
        test_image = Load("test.png", false);
    }
    ~Texture(void){}
    
};
