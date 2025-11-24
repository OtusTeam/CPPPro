#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>


std::string font_file = "D:\\my_font.ttf";
sf::Font app_font;
sf::RenderWindow window(sf::VideoMode(1200, 1200), "C++ DEVELOPER PROFESSIONAL");
sf::Color win_background(255, 255, 255, 255);


using namespace boost::multi_index;

enum ShowMode
{
	ALL = 0,
	TRIANGLES = 1,
	RECTS = 2,
	X_GREATER_400 = 3,
	Y_LESS_400 = 4

};

ShowMode app_show_mode = ALL;

template <typename T>
bool MouseInRect(sf::Vector2<T> pos, int width, int height, sf::Window& w)
{
	sf::IntRect ir;
	ir.left = pos.x;
	ir.top = pos.y;
	ir.width = width;
	ir.height = height;

	sf::Vector2i mp = sf::Mouse::getPosition(w);

	return ir.contains(mp);

}

class Control
{
public:
	
	virtual void Draw() = 0;
	virtual void Update() = 0;
	
	virtual ~Control() = default;

	int _x, _y, _type;
};

std::vector<Control*> object_pool;

struct ByXTag {};
struct ByYTag {};

typedef multi_index_container<
	Control*,
	indexed_by<
	
	ordered_non_unique<member<Control, int, &Control::_type> >,
	ordered_non_unique<tag<ByXTag>,member<Control, int, &Control::_x>>,
	ordered_non_unique<tag<ByYTag>,member<Control, int, &Control::_y> >
	>
> observable_set;



observable_set GeometrySet;



class Button : public Control
{
public:
	Button(int x,int y,std::wstring btn_text,std::function<void()> fn)
	{
		
		_clicked = fn;
		_text_color.r = 240;
		_text_color.g = 240;
		_text_color.b = 240;
		_text_color.a = 255;
		
		_base_color.r = 64;
		_base_color.g = 50;
		_base_color.b = 168;
		_base_color.a = 255;

		_mouse_over_color.r = 126;
		_mouse_over_color.g = 113;
		_mouse_over_color.b = 222;
		_mouse_over_color.a = 255;

		_x = x;
		_y = y;

		_bounds.setPosition(sf::Vector2f(_x, _y));
		_bounds.setSize(sf::Vector2f(300, 75));

		_text.setString(btn_text);
		_text.setFont(app_font);
		_text.setCharacterSize(35);
		_text.setPosition(_x + 8, _y + 8);
		
		object_pool.push_back(this);

		

		
	}

	void Draw() override
	{
		
		window.draw(_bounds);
		window.draw(_text);
	}

	void Update() override
	{
		if (MouseInRect(sf::Vector2f(_x, _y), 275, 100, window)) {
			_bounds.setFillColor(_mouse_over_color);
		}
		else {
			_bounds.setFillColor(_base_color);
		}

				
		if (MouseInRect(sf::Vector2f(_x,_y), 300, 100, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				_clicked();
			}
		}
	}

private:
	sf::RectangleShape _bounds;
	sf::Text _text;
	sf::Color _base_color;
	sf::Color _mouse_over_color;
	sf::Color _text_color;
	std::function<void()> _clicked;


};
class Triangle : public Control
{
public:
	Triangle(int x, int y)
	{
		_type = 1;
		_x = x;
		_y = y;

		_data.setFillColor(sf::Color(252, 3, 69, 255));
		_data.setPointCount(3);
		_data.setRadius(100);
		_data.setPosition(sf::Vector2f(_x, _y));

		//object_pool.push_back(this);

		GeometrySet.emplace(this);

	}
	void Draw() override
	{
		window.draw(_data);
	}

	void Update() override {}
private:
	sf::CircleShape _data;
};

class Rectangle : public Control
{
public:
	Rectangle(int x, int y)
	{
		_type = 2;
		_x = x;
		_y = y;

		_data.setFillColor(sf::Color(252, 227, 3, 255));
		_data.setPosition(sf::Vector2f(_x, _y));
		_data.setSize(sf::Vector2f(150, 150));

		//object_pool.push_back(this);

		GeometrySet.emplace(this);
	}

	void Draw() override
	{
		window.draw(_data);
	}

	void Update() override {}

private:
	sf::RectangleShape _data;

};



void ShowAll()
{
	observable_set::iterator begin = GeometrySet.begin();//GetCurrentModeBeginIterator(app_show_mode);
	observable_set::iterator end = GeometrySet.end();


	for (; begin != end; ++begin) {
		(*begin)->Update();
		(*begin)->Draw();
	}
}

void ShowRects()
{
	observable_set::iterator begin = GeometrySet.get<0>().equal_range(2).first;//GetCurrentModeBeginIterator(app_show_mode);
	observable_set::iterator end = GeometrySet.get<0>().equal_range(2).second;


	for (; begin != end; ++begin) {
		(*begin)->Update();
		(*begin)->Draw();
	}
}

void ShowTriangles()
{
	observable_set::iterator begin = GeometrySet.get<0>().equal_range(1).first;//GetCurrentModeBeginIterator(app_show_mode);
	observable_set::iterator end = GeometrySet.get<0>().equal_range(1).second;


	for (; begin != end; ++begin) {
		(*begin)->Update();
		(*begin)->Draw();
	}
}

void ShowXGreater400()
{
	

	auto begin = GeometrySet.get<ByXTag>().lower_bound(400);
	auto end = GeometrySet.get<ByXTag>().upper_bound(INT_MAX);

	for (; begin != end; ++begin) {
		(*begin)->Update();
		(*begin)->Draw();
	}
}

void ShowYLess400()
{
	auto begin = GeometrySet.get<ByYTag>().lower_bound(INT_MIN);
	auto end = GeometrySet.get<ByYTag>().upper_bound(400);

	for (; begin != end; ++begin) {
		(*begin)->Update();
		(*begin)->Draw();
	}
}

void AppDoEvents()
{
	for (auto it = object_pool.begin(); it != object_pool.end(); ++it) {
		(*it)->Update();
		(*it)->Draw();
	}
	
	

	switch (app_show_mode)
	{
	case ALL:
		ShowAll();
		break;
	case RECTS:
		ShowRects();
		break;
	case TRIANGLES:
		ShowTriangles();
		break;
	case X_GREATER_400:
		ShowXGreater400();
		break;
	case Y_LESS_400:
		ShowYLess400();
		break;
	default:
		ShowAll();
		break;

	}
	
	
	
}



void SetAllShowMode()
{
	app_show_mode = ALL;
}

void SetTrianglesShowMode()
{
	app_show_mode = TRIANGLES;
}

void SetRectangleShowMode()
{
	app_show_mode = RECTS;
}

void SetXGreater400ShowMode()
{
	app_show_mode = X_GREATER_400;
}

void SetYLess400ShowMode()
{
	app_show_mode = Y_LESS_400;
}

int main()
{
	if(!app_font.loadFromFile(font_file)) {
		std::cout << "UNABLE TO LOAD FONT" << std::endl;
		
	}

	Button* show_all_btn = new Button(20, 1000, std::wstring(L"Отображать всё"),SetAllShowMode);
	Button* show_triangles = new Button(340, 1000, std::wstring(L"Треугольники"), SetTrianglesShowMode);
	Button* show_rects = new Button(650, 1000, std::wstring(L"Прямоугольники"), SetRectangleShowMode);
	Button* x_greater_400 = new Button(20, 1100, std::wstring(L"X > 400"), SetXGreater400ShowMode);
	Button* y_greater_400 = new Button(340, 1100, std::wstring(L"Y < 400"), SetYLess400ShowMode);

	Triangle* t1 = new Triangle(175, 15);
	t1 = new Triangle(375, 15);
	t1 = new Triangle(575, 15);
	t1 = new Triangle(775, 15);

	Rectangle* r1 = new Rectangle(15, 100);
	r1 = new Rectangle(15, 300);
	r1 = new Rectangle(15, 500);
	r1 = new Rectangle(15, 700);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			window.clear(win_background);   
			AppDoEvents();
			window.display();

		}
	}
}