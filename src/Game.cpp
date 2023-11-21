//
// Created by petroew on 20.11.23.
//

#include "Game.h"

Game::Game()
{

    Base("init"); // Инициализируем базовый класс
    m_game_state = GameState::MainMenu;
    // Пример инициализации уровней
    // level = std::move(mmake_unique<Level_01>(Level_01(...params...)));
}

void Game::Update()
{
    // Тут только апдейтим
    switch (m_game_state)
    {
    case GameState::MainMenu:
        // Например
        // main_menu.Update();
        break;
    case GameState::Play:
        // Например
        // level1->Update();
        break;
    default:
        break;
    }
    UpdateUI();
}

void Game::Action()
{
    // тут только обрабатываем события
    switch (m_game_state)
    {
    case GameState::MainMenu:
        // Например
        //  main_menu.Action();
        break;
    case GameState::Play:
        // Например
        // level->Action();
        break;
    default:
        break;
    }
    ActionUI();
}

void Game::Draw()
{
    // сюда вставляем только отрисовку
    wnd.clear();

    switch (m_game_state)
    {
    case GameState::MainMenu:
        // Например
        // main_menu.Draw();
        break;
    case GameState::Play:
        // Например
        // level->Draw();
        break;
    default:
        break;
    }

    // Оставляем метод DrawUI(); перед wnd.display();
    // т.к. слой интерфейса должен отрисовываться самым последним
    DrawUI();
    wnd.display();
}

void Game::UpdateUI()
{
    wnd.setView(wnd.getDefaultView()); // Устанавливаем камеру по умолчанию

    // Тут обновляем элементы интерфейса используя cur_p_wnd (Позиция курсора в окне)
    // Например
    // UI_Manager.Update();
    wnd.setView(cam); // Возвращаем игровую камеру
}

void Game::ActionUI()
{
    wnd.setView(wnd.getDefaultView()); // Устанавливаем камеру по умолчанию

    // Тут обновляем элементы интерфейса используя cur_p_wnd : Позиция курсора мыши в оконной системе координат
    // Например
    // UI_Manager.Action();
    wnd.setView(cam); // Возвращаем игровую камеру
}

void Game::DrawUI()
{
    wnd.setView(wnd.getDefaultView()); // Устанавливаем камеру по умолчанию
    // Тут обновляем элементы интерфейса используя cur_p_wnd : Позиция курсора мыши в оконной системе координат
    // Например
    // UI_Manager.Draw();
    wnd.setView(cam); // Возвращаем игровую камеру
}

// Метод Play() вообще не трогаем
void Game::Play()
{
    while (wnd.isOpen())
    {
        SystemUpdate();
        Update();
        while (wnd.pollEvent(event))
        {
            CloseEvent();
            Action();
        }
        Draw();
    }
}

Game::~Game()
{
}

int main()
{
    Game game;
    game.Play();
    return 0;
}