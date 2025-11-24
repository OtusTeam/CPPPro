#include "TextSample.h"

TextSample::TextSample(CheckBox* cb, TextInput* ti, sf::RenderWindow* w) : m_check_box(cb), m_text_input(ti), m_window(w)
{

}


void TextSample::Update(sf::Event& event)
{
	sf::Text t = m_text_input->GetText();
	m_draw_big = m_check_box->GetState();

	m_text_sample = t;
	m_text_sample.setPosition(sf::Vector2f(15, 450));

	if (m_draw_big) {
		m_text_sample.setCharacterSize(65);
	}
	
}

void TextSample::Draw(sf::Event& event)
{
	m_window->draw(m_text_sample);
}