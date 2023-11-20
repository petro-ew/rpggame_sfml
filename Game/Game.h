//
// Created by petroew on 20.11.23.
//
#pragma once
#include "../Base.h"
enum class GameState : uint {
    MainMenu,
    Play
};
class Game:public B
{
public:
    //Вызывается в main() функции
    //Она находится в самом низу файла Game.cpp
    void Play();
    
    Game();
    ~Game();

private:
    GameState m_game_state;
    // unique_ptr<oLevel> level;
    // MainMenu main_menu;
private:
    //Архитектура содержит простое правило трех UAD  - Update, Action и Draw.
    void Update();
    void Action();
    void Draw();
    
    void UpdateUI();
    void ActionUI();
    void DrawUI();
};
