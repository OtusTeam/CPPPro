#pragma once
#include "CheckBox.h"
#include "TextInput.h"

class TextSample : public IAction
{
public:
	TextSample(CheckBox*, TextInput*,sf::RenderWindow*);
	void Update(sf::Event& event) override;
	void Draw(sf::Event& event) override;
private:



	sf::Text m_text_sample;

	CheckBox* m_check_box;
	TextInput* m_text_input;
	bool m_draw_big = false;
	sf::RenderWindow* m_window = nullptr;
};

