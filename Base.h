//
// Created by petroew on 20.11.23.
//
#pragma once

#include "Resources/Texture.h"
#include "Resources/Audio.h"
#include "Resources/Font.h"
// #include "Define.h"

class Base
{
public:
    static sf::RenderWindow wnd; // Окно
    static Texture texture;      // Набор текстур
    static Font font;            // Набор шрифтов
    static Audio audio;     // Набор звуков и музыки (audio.sound.my_sound | audio.music.my_music)
    static sf::Event event; // События SFML
    static sf::View cam;    // Камера вида
    static int scr_w;       // Ширина рабочего стола
    static int scr_h;       // Высота рабочего стола
    static v2f cam_p;       // Позиция камеры
    static v2f cur_p;       // Позиция курсора в глобальной системе координат
    static v2f cur_p_wnd; // Позиция курсора в оконной системе координат (для обработки UI)
    static float time; // Прошедшее время каждого тика

    // Определение Методов базового класса

    // Обновление полей базового класса
    // Вызывать только в начале метода Update() в классе Game и нигде больше
    static void SystemUpdate()
    {
        // Обновление времени прошедшего тика
        time = float(clock.getElapsedTime().asMicroseconds()) / 1000.f, clock.restart();
        // Обновление позиции курсора в глобальной системе координат
        cur_p = wnd.mapPixelToCoords(sf::Mouse::getPosition(wnd));
        // Обновление позиции курсора в оконной системе координат
        cur_p_wnd = v2f(sf::Mouse::getPosition(wnd));
        // Обновление позиции центра камеры вида
        cam_p = cam.getCenter();
    }

    // Обработчик события закрытия окна
    static void CloseEvent()
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == Key::Escape))
            wnd.close();
    }

    // Возвращает область видимости камеры
    static const sf::FloatRect GetCamVisible()
    {
        return sf::FloatRect(cam.getCenter().x - (cam.getSize().x / 2), // X Левой части обзора
                             cam.getCenter().y - (cam.getSize().y / 2), // Y Верхней части обзора
                             cam.getSize().x,                           // X Размер камеры
                             cam.getSize().y);                          // Y Размер камеры
    }

    // Возвращает позицию относительно pos на расстояние dist в направление angle
    static const v2f GetNormallizedPosition(const v2f& pos, float dist, float angle)
    {
        const float& A = angle * RAD;
        return pos + v2f(cos(A), sin(A)) * dist;
    }

    // Возвращает позицию относительно центра фигуры shape на расстоянии dist в направлении angle
    static const v2f GetNormallizedPosition(Shape& shape, float dist, float angle)
    {
        const float& A = angle * RAD;
        return shape.getPosition() + v2f(cos(A), sin(A)) * dist;
    }

    // Возвращает нахождение pos в фигуре shape
    static const bool IsContains(Shape& shape, const v2f& pos)
    {
        return shape.getGlobalBounds().contains(pos);
    }

    // Возвращает результат соприкосновения двух окружностей
    // Принимает обычные sf::RectangleShape, используется для фигур
    // с круглыми текстурами и прозрачностью вокруг
    // Но ничто не мешает перезагрузить метод для sf::CircleShape
    static const bool GetCollisionCircle(Shape& c1, Shape& c2)
    {
        const float r1 = c1.getSize().x / 2.f;
        const float r2 = c2.getSize().x / 2.f;
        const v2f& p1 = c1.getPosition();
        const v2f& p2 = c2.getPosition();
        return GetDistance(p1, p2) > float(r1 + r2) ? false : true;
    }

    // Возвращает результат соприкосновения двух прямоугольников
    // Принимает обычные sf::RectangleShape
    static const bool GetCollisionRect(Shape& s1, Shape& s2)
    {
        return s1.getGlobalBounds().intersects(sf::FloatRect(s2.getPosition().x - (s2.getSize().x / 2.f),
                                                             s2.getPosition().y - (s2.getSize().y / 2.f),
                                                             s2.getSize().x, s2.getSize().y));
    }

    // Обработчик для столкновений для статического и динамического объектов
    // Динамический объект выталкивается из статического
    // Например объект юнита будет выталкиваться из объекта стена
    static void CollisionUpdate(Shape& static_s1, Shape& dynamic_s2)
    {
        if (GetCollisionCircle(static_s1, dynamic_s2))
        {
            dynamic_s2.setPosition(GetNormallizedPosition(static_s1.getPosition(),
                                                          dynamic_s2.getSize().x + static_s1.getSize().x / 1.99f,
                                                          GetAngle(static_s1, dynamic_s2)));
        }
    }

    // Возвращает расстояние между двумя точками v2f
    static const float GetDistance(const v2f& p1, const v2f& p2)
    {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }

    // Возвращает расстояние мужду двумя объектами Shape
    static const float GetDistance(Shape& s1, Shape& s2)
    {
        const v2f& p1 = s1.getPosition();
        const v2f& p2 = s2.getPosition();
        return GetDistance(p1, p2);
    }

    // Возвращает расстояние между Shape и v2f
    static const float GetDistance(Shape& s1, const v2f& pos)
    {
        const v2f& p1 = s1.getPosition();
        return GetDistance(p1, pos);
    }

    // Вспомогательный метод конструкторн для объектов Shape
    // Пример использования - Shape shape = CreateShape(v2f(0,0), v2f(10,10), texture.my_loaded_image);
    //  три параметра - позиция, размер, текстура
    static const Shape CreateShape(v2f pos, v2f siz, IMG& png)
    {
        Shape shp;
        shp.setOrigin(siz / 2.f);
        shp.setSize(siz);
        shp.setPosition(pos);
        shp.setTexture(&png);
        return shp;
    }

    // Вспомогательный метод коструктор для объектов Shape
    // Пример использования - Shape shape - CreateShape(v2f(0,0), v2f(10,10));
    static const Shape CreateShape(v2f pos, v2f siz)
    {
        Shape shp;
        shp.setOrigin(siz / 2.f);
        shp.setSize(siz);
        shp.setPosition(pos);
        return shp;
    }

    // Вспомогательный метод-конструктор для объектов Shape
    // Пример использования Shape shape = CreateShape(v2f(0,0), v2f(10,10), Color::Yellow);
    static const Shape CrateShape(v2f pos, v2f siz, Color color)
    {
        Shape shp;
        shp.setSize(siz);
        shp.setOrigin(siz / 2.f);
        shp.setFillColor(color);
        shp.setPosition(pos);
        return shp;
    }

    // Вспомогательный метод-конструктор для объектов Shape
    // Пример использования Shape shape = CreateShape(v2f(0,0), v2f(10,10), -3, Color::Red, Color::Yellow);
    static const Shape CrateShape(v2f pos, v2f siz, float out_siz, Color color = Color::White,
                                  Color out_color = Color::White)
    {
        Shape shp;
        shp.setSize(siz);
        shp.setOrigin(siz / 2.f);
        shp.setFillColor(color);
        shp.setPosition(pos);
        shp.setOutlineThickness(out_siz);
        shp.setOutlineColor(out_color);
        return shp;
    }

    // Вспомогательный метод-конструктор для объектов sf::Text
    // Пример использования sf::Text text = CreateText(v2f(0,0), 16, "какой-то текст", font.my_loaded_font,
    // Color::Magenta);
    static const sf::Text CreateText(v2f pos, uint siz, sf::String str, sf::Font& font, Color col)
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(siz);
        text.setFillColor(col);
        text.setString(str);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
        text.setPosition(pos.x, pos.y - siz / 3);
        return text;
    }

    // Возвращает направление в градусах относительно точки p1 к точке p2
    static const float GetAngle(const v2f& p1, const v2f& p2)
    {
        return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
    }

    // Возвращает направление в градусах относительно фигруры shp к точке p
    static const float GetAngle(Shape& shp, const v2f& p)
    {
        return atan2f(p.y - shp.getPosition().y, p.x - shp.getPosition().x) * DEG;
    }

    // Возвращает направление в градусах относительно фигруры shp1 к фигуре shp2
    static const float GetAngle(Shape& shp1, Shape& shp2)
    {
        const v2f& p1 = shp1.getPosition();
        const v2f& p2 = shp2.getPosition();
        return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
    }

    // Перемещает позицию текста в его центр
    // Использовать после присвоения my_text.setString("какой-то текст");
    static void CenteringText(sf::Text& text)
    {
        text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 1.5f);
    }

    // Возвращает результат нажатия на кнопку клавиатуры
    // Пример использования if(IsKeyPressed(Key::F1)) {Condition..}
    static bool IsKeyPressed(const sf::Keyboard::Key& code)
    {
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == code)
                return true;
        return false;
    }

    // Возвращает результат отжатия на кнопку клавиатуры
    // Пример использования if(IsKeyReleased(Key::F1)) {Condition..}
    static bool IsKeyReleased(const sf::Keyboard::Key& code)
    {
        if (event.type == sf::Event::KeyReleased)
            if (event.key.code == code)
                return true;
        return false;
    }

    // Возвращает результат нажатия на кнопки мыши
    // Пример использования if(IsMousePressed(sf::Mouse::Left)) {Condition..}
    static bool IsMousePressed(const sf::Mouse::Button& code)
    {
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.key.code == code)
                return true;
        return false;
    }

    // Возвращает результат отжатия нажатой кнопки мыши
    // Пример использования if(IsMouseReleased(sf::Mouse::Left)) {Condition..}
    static bool IsMouseReleased(const sf::Mouse::Button& code)
    {
        if (event.type == sf::Event::MouseButtonReleased)
            if (event.key.code == code)
                return true;
        return false;
    }

    // Возвращает результат прокрутки колеса мыши
    static bool IsMouseWheelUp(const sf::Mouse::Wheel code)
    {
        if (event.mouseWheel.x == code)
            return true;
        return false;
    }

    // Конструктор инициализатор
    // Вызывается только один раз на старте программы
    Base(string init)
    {
        if (init == "init")
        {
            // Инициализируем поля базового класса
            scr_w = sf::VideoMode::getDesktopMode().width;
            scr_h = sf::VideoMode::getDesktopMode().height;
            font = Font();
            texture = Texture();
            audio = Audio();
            wnd.create(sf::VideoMode(scr_w, scr_h), "RPG game", sf::Style::Close, sf::ContextSettings(0, 0, 8));
            cam.reset(sf::FloatRect(0, 0, scr_w, scr_h));
            cam.setCenter(0, 0);
            cam_p = cam.getCenter();
            cur_p = v2f(0, 0);
            cur_p_wnd = v2f(0, 0);
            wnd.setView(cam);
            wnd.setMouseCursorVisible(true);
            wnd.setFramerateLimit(30);
            srand(::time(0));
        }
    }

    Base(void)
    {
    }

private:
    static sf::Clock clock;
};

// выносим статические поля в глобальную область видимости
sf::RenderWindow B::wnd; // Окно
Texture B::texture;      // Набор текстур
Font B::font;            // Набор шрифтов
Audio B::audio;          // Набор звуков и музыки (audio.sound.my_sound | audio.music.my_music)
sf::Event B::event;      // События SFML
sf::View B::cam;         // Камера вида
int B::scr_w;            // Ширина рабочего стола
int B::scr_h;            // Высота рабочего стола
v2f B::cam_p;            // Позиция камеры
v2f B::cur_p;            // Позиция курсора в глобальной системе координат
v2f B::cur_p_wnd; // Позиция курсора в оконной системе координат (для обработки UI)
float B::time; // Прошедшее время каждого тика
sf::Clock B::clock;
