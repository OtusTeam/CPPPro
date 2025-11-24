#include "CheckBox.h"

CheckBox::CheckBox(int x, int y, sf::RenderWindow* w)
{
    _pos.x = static_cast<float>(x + 2);
    _pos.y = static_cast<float>(y + 2);

    if (!_internal_font.loadFromFile("D:\\my_font.ttf")) {
        std::cout << "UNABLE TO LOAD FONT" << std::endl;
    }

    _label.setFont(_internal_font);
    _label.setCharacterSize(30);
    _label.setFillColor(sf::Color(0, 0, 0, 255));
    _label.setString(std::wstring(L"Отображать крупнее"));
    
    _border.setPosition(sf::Vector2f(_pos.x, _pos.y));
    _border.setSize(sf::Vector2f(50, 50));
    _border.setFillColor(sf::Color(52, 79, 235, 255));

    _inner_rect.setPosition(sf::Vector2f(_border.getPosition().x + 2, _border.getPosition().y + 2));
    _inner_rect.setSize(sf::Vector2f(_border.getSize().x - 4, _border.getSize().y - 4));
    _inner_rect.setFillColor(sf::Color(245, 245, 245, 255));


    _label.setPosition( sf::Vector2f( (_border.getPosition().x + _border.getSize().x + 5),
                        _border.getPosition().y + 2)
                       );

    
    _window = w;



}
void CheckBox::Update(sf::Event& event)
{
    _current_event = &event;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (MouseInRect(_pos, _border.getSize().x, _border.getSize().y, _window)) {
            SetCheckState();
        }
       
    }


    

}

void CheckBox::SetCheckState()
{
    if (_checked) {
        _checked = false;
    }
    else {
        _checked = true;
    }
}

void CheckBox::Draw(sf::Event& event)
{
    _current_event = &event;

    _window->draw(_border);
    _window->draw(_inner_rect);
    _window->draw(_label);

    if (_checked) {
        DrawCheck();
    }

}



void CheckBox::DrawCheck()
{
    sf::Color color = _border.getFillColor();

    
    

    {
        sf::Vector2f size(2, _inner_rect.getSize().y + 19);
        sf::Vector2f pos(_inner_rect.getPosition().x, _inner_rect.getPosition().y + 1);
        sf::RectangleShape rs;
        rs.setFillColor(color);
        rs.setSize(size);
        rs.setPosition(pos);
        rs.setRotation(-45);
        _window->draw(rs);
    }

    {
        sf::Vector2f size(2, _inner_rect.getSize().y + 19);
        sf::Vector2f pos(_inner_rect.getPosition().x, _inner_rect.getPosition().y + _inner_rect.getSize().y);
        sf::RectangleShape rs;
        rs.setFillColor(color);
        rs.setSize(size);
        rs.setPosition(pos);
        rs.setRotation(-134);
        _window->draw(rs);
    }

    
    
    

}

bool CheckBox::GetState()
{
    return _checked;
}