#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

/*
 * Класс который реализует спрайтовую анимацию
 */
class Animation
{
    // Спецификатор доступа public означает что переменные и функции ниже доступны из любого места программы
public:
    void Update(float DeltaSeconds);
    
    /*
     * Функция для возврата значения переменной currentFrameIndex
     * С помощью такого подхода переменная currentFrameIndex не может изменяться извне класса Animation
     * Но мы можем получить её значение извне
     */
    int GetCurrentFrameIndex();

    /*
     * Функция для возврата текущего кадра анимации
     */
    const sf::IntRect& GetCurrentFrame();

public:
    // Текстура в которой находится анимация
    sf::Texture texture;
    
    // Кадры анимации в текстуре
    std::vector<sf::IntRect> frames;

    // Скорость анимации. Чем больше значение тем быстрее анимация
    float speed = 1.f;

    // Спецификатор доступа private означает что переменные и функции ниже доступны только внутри класса Animation
private:
    // Текущий кадр анимации. Переменная находится в private потому изменять её может только класс Animation. Он знает как её нужно изменять в каких числовых пределах она должна находиться
    float currentFrameIndex = 0.f;
};