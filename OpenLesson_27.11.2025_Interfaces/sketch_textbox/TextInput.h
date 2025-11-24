#ifndef TEXTIPUT_HPP
#define TEXTINPUT_HPP

#include "IAction.hpp"
#include <iostream>



class TextInput : public IAction
{
public:
    TextInput(int x, int y);
    TextInput(int x, int y,sf::RenderWindow* w);
    void Update(sf::Event& event) override;
    void Draw(sf::Event& event) override;

    int Width() override;
    int Height() override;

    sf::Text GetText();
    sf::Font& GetFont();


protected:
    void UpdateInternal();
    void UpdateInternalForSelected();
    void MouseClick();
    void HandleKeyBoard();
    void HandleBackspace();
    void HandleTextEntered();
    /*Frame around input field*/
    void UpdateBorder();
    void UpdateCursor();
    void UpdateEnteredText();

    
    sf::Font _internal_font;
    int _width = 500;
    int _height = 100;
    std::wstring _text_str;
    sf::Text _text_input;
    sf::RectangleShape _background;
    sf::VertexArray _border;
    bool _selected = false;
    bool _keyboard_lock = false;
    int _cursor_pos = 0;
    int _max_text_length = 22;

    sf::RenderWindow* _window;
    sf::Event* _current_event;


};

#endif