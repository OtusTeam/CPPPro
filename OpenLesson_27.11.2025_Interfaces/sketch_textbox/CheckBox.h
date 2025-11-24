#pragma once
#include <iostream>
#include "IAction.hpp"

class CheckBox : public IAction
{
public:
	CheckBox(int x, int y, sf::RenderWindow* w);
	void Update(sf::Event& event) override;
	void Draw(sf::Event& event) override;
	bool GetState();
private:

	void DrawCheck();
	void SetCheckState();
	sf::Font _internal_font;
	std::wstring _label_text;
	sf::Text _label;
	
	sf::RectangleShape _border;
	sf::RectangleShape _inner_rect;
	sf::RectangleShape _check;


	sf::RenderWindow* _window = nullptr;
	sf::Event* _current_event = nullptr;

	bool _checked = false;

	
};

