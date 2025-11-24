#ifndef IACTION_HPP
#define IACTION_HPP

#include <SFML/Graphics.hpp>



template <typename T>
bool MouseInRect(sf::Vector2<T> pos, int width, int height, sf::Window* w)
{
    sf::IntRect ir;
    ir.left = pos.x;
    ir.top = pos.y;
    ir.width = width;
    ir.height = height;

    sf::Vector2i mp = sf::Mouse::getPosition(*w);

    return ir.contains(mp);

}



struct IAction {
    virtual void Update(sf::Event& event) = 0;
    virtual void Draw(sf::Event& event) = 0;

    virtual int Width() { return 0; }
    virtual int Height() { return 0; }

    virtual sf::Vector2f GetPosition()
    {
        return _pos;
    }

    virtual void SetPosition(float x, float y)
    {
        _pos.x = x;
        _pos.y = y;
    }
    virtual ~IAction() {};
    sf::Vector2f _pos;


};
#endif