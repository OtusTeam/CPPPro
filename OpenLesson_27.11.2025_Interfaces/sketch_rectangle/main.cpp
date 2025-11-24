#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


sf::RenderWindow w(sf::VideoMode(1000, 1000), "C++ DEVELOPER PROFESSIONAL");
sf::Event event;

std::string font_file = "D:\\my_font.ttf";
sf::Font f;
sf::Text x_coord;
sf::Text y_coord;
sf::RectangleShape r;



bool MouseInRect(sf::RectangleShape& rs)
{
	sf::IntRect ir;
	ir.left = rs.getPosition().x;
	ir.top = rs.getPosition().y;
	ir.width = rs.getSize().x;
	ir.height = rs.getSize().y;
	
	sf::Vector2i mp = sf::Mouse::getPosition(w);

	return ir.contains(mp);

}

int InitApp()
{
	if (!f.loadFromFile(font_file)) {
		std::cout << "UNABLE TO OPEN FONT!" << std::endl;
		return -1;
	}

	x_coord.setFont(f);
	x_coord.setFillColor(sf::Color(0, 0, 0, 255));
	x_coord.setCharacterSize(30);
	x_coord.setPosition(sf::Vector2f(1, 1));

	y_coord.setFont(f);
	y_coord.setFillColor(sf::Color(0, 0, 0, 255));
	y_coord.setCharacterSize(30);
	y_coord.setPosition(sf::Vector2f(1, 30));

	r.setPosition(500, 500);
	r.setSize(sf::Vector2f(300,300));
	r.setFillColor(sf::Color(161, 252, 3, 255));

}

void ReactToMouse()
{
	

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
		     	int mx = sf::Mouse::getPosition(w).x;
				int my = sf::Mouse::getPosition(w).y;

				r.setPosition(sf::Vector2f(mx, my));

		
		}
						
	}
		

}

void AppDoEvents()
{
	ReactToMouse();
	x_coord.setString("X_COORD:" + std::to_string(r.getPosition().x));
	y_coord.setString("Y_COORD:" + std::to_string(r.getPosition().y));

	w.draw(x_coord);
	w.draw(y_coord);
	w.draw(r);
}

int main()
{
	if (InitApp() == -1) return -1;

	
	sf::Color background(255, 255, 255, 255);
	
	while (w.isOpen())
	{
		
		while (w.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
				w.close();

			w.clear(background);
			AppDoEvents();
			w.display();

		}
	}
}