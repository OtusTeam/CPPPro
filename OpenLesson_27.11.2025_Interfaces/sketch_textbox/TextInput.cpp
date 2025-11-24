#include "TextInput.h"


TextInput::TextInput(int x, int y)
{
    _pos.x = static_cast<float>(x + 2);
    _pos.y = static_cast<float>(y + 2);
    
    if (!_internal_font.loadFromFile("D:\\my_font.ttf")) {
        std::cout << "UNABLE TO LOAD FONT" << std::endl;
    }
    
    _text_input.setFont(_internal_font);
    _text_input.setCharacterSize(30);
    //this->Update();
}

TextInput::TextInput(int x, int y, sf::RenderWindow* w) : TextInput(x,y)
{
    _window = w;
}

void TextInput::Update(sf::Event& event)
{
    _current_event = &event;

    if (this->_selected) {
        UpdateInternalForSelected();
    }
    else {
        UpdateInternal();
    }

}

void TextInput::Draw(sf::Event& event)
{
    _window->draw(_border);
    _window->draw(_background);
    _window->draw(_text_input);
}

int TextInput::Width()
{
    return _width;
}

int TextInput::Height()
{
    return _height;
}

void TextInput::UpdateInternal()
{
    _background.setPosition(_pos);
    _background.setSize(sf::Vector2f(_width, _height));
    _background.setFillColor(sf::Color(230, 230, 230));
    UpdateBorder();
    MouseClick();
    UpdateEnteredText();
    
    _keyboard_lock = false;


}

void TextInput::UpdateInternalForSelected()
{
    _background.setPosition(_pos);
    _background.setSize(sf::Vector2f(_width, _height));
    _background.setFillColor(sf::Color(237, 237, 237, 255));
    UpdateBorder();
    MouseClick();
    HandleKeyBoard();
    UpdateEnteredText();
    

}

void TextInput::MouseClick()
{

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (MouseInRect(_pos, _width, _height,_window)) {
            _selected = true;

        }
        else {
            _selected = false;

        }
    }
}

void TextInput::HandleKeyBoard()
{
    //HandleBackspace();
    HandleTextEntered();
}

void TextInput::HandleBackspace()
{

    if (_current_event->type == sf::Event::KeyPressed) {

        if (_keyboard_lock) return;
        _keyboard_lock = true;

        sf::Keyboard::Key k = _current_event->key.code;

        if (k == sf::Keyboard::Key::BackSpace) {
            if (_text_str.size() > 0) {
                _text_str.erase(--_text_str.end());
                _cursor_pos--;

            }
        }

    }
    else {
        _keyboard_lock = false;
    }
}
void TextInput::HandleTextEntered()
{
    if (_current_event->type == sf::Event::TextEntered) {

        if (_keyboard_lock) return;

        _keyboard_lock = true;

        /*8 is BACKSPACE*/
        if (_current_event->text.unicode == 8) {
            if (_text_str.size() > 0) {
                _text_str.erase(--_text_str.end());
                _cursor_pos--;

            }
        }
        else {

            if (_text_str.size() <= _max_text_length) {
                _cursor_pos++;
                _text_str += _current_event->text.unicode;
            }

        }

    }
    else {
        _keyboard_lock = false;
    }
    

}

void TextInput::UpdateEnteredText()
{
    _text_input.setCharacterSize(40);
    _text_input.setFillColor(sf::Color(0, 0, 0, 255));
    _text_input.setPosition(_pos.x + 1, _pos.y + 1);
    _text_input.setString(_text_str);

}

void TextInput::UpdateBorder()
{
    _border.clear();
    sf::Vertex v(sf::Vector2f(_pos.x - 1, _pos.y - 1));
    v.color = sf::Color(9, 3, 163, 255);
    sf::Vertex v1(sf::Vector2f(_pos.x + _width + 1, _pos.y));
    v1.color = sf::Color(28, 22, 204, 255);
    sf::Vertex v2(sf::Vector2f(v1.position.x, _pos.y + _height + 1));
    v2.color = sf::Color(51, 46, 209, 255);
    sf::Vertex v3(sf::Vector2f(v.position.x, _pos.y + _height));
    v3.color = sf::Color(18, 22, 28, 255);

    _border.append(v);
    _border.append(v1);
    _border.append(v2);
    _border.append(v3);
    _border.append(v);

    if (MouseInRect(_pos, _width, _height,_window)) {
        _border[0].color = sf::Color(3, 127, 252);
        _border[1].color = sf::Color(71, 158, 245);
        _border[2].color = sf::Color(9, 116, 224);
        _border[3].color = sf::Color(205, 83, 230);
    }

    if (this->_selected) {
        _border[0].color = sf::Color(205, 83, 230);
        _border[1].color = sf::Color(223, 113, 245);
        _border[2].color = sf::Color(215, 128, 232);
        _border[3].color = sf::Color(205, 83, 230);

    }

    _border.setPrimitiveType(sf::PrimitiveType::LineStrip);

}

sf::Text TextInput::GetText()
{
    return _text_input;
}

sf::Font& TextInput::GetFont()
{
    return _internal_font;
}

void TextInput::UpdateCursor()
{
}