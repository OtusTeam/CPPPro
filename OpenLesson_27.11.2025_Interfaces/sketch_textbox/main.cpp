#include <SFML/Window.hpp>
#include <vector>
#include "TextSample.h"



sf::RenderWindow window(sf::VideoMode(1000, 1000), "C++ DEVELOPER PROFESSIONAL");
sf::Color background(255, 255, 255, 255);
sf::Event event;
std::vector<IAction*> app_actions;

void Update()
{
	for (int i = 0; i < app_actions.size(); ++i) {
		app_actions[i]->Update(event);
		app_actions[i]->Draw(event);
	}
}

int main()
{
	TextInput* ti = new TextInput(10, 10, &window);
	CheckBox* cb = new CheckBox(10, 200, &window);
	TextSample* ts = new TextSample(cb, ti, &window);

	app_actions.push_back(ti);
	app_actions.push_back(cb);
	app_actions.push_back(ts);

	while (window.isOpen())
	{
		
		while (window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			window.clear(background);
			Update();
			window.display();

		}
	}
}