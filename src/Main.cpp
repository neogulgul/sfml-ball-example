#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

const unsigned int viewWidth    = 400;
const unsigned int viewHeight   = 225;
const unsigned int windowWidth  = viewWidth  * 2;
const unsigned int windowHeight = viewHeight * 2;

const unsigned int targetFPS = 60;

// keyboard key pressed
bool pressing(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key)) { return true; }
	return false;
}

// mouse button pressed
bool pressing(sf::Mouse::Button button)
{
	if (sf::Mouse::isButtonPressed(button)) { return true; }
	return false;
}

sf::Color getRandomColor(std::mt19937 &rng)
{
	static std::vector<sf::Color> colorsToChooseFrom = {
		sf::Color(255,   0,   0, 63),
		sf::Color(255, 255,   0, 63),
		sf::Color(255,   0, 255, 63),
		sf::Color(  0, 255,   0, 63),
		sf::Color(  0, 255, 255, 63),
		sf::Color(  0,   0, 255, 63)
	};

	static std::uniform_int_distribution<> color_dist(0, colorsToChooseFrom.size() - 1);

	return colorsToChooseFrom.at(color_dist(rng));
}

struct Ball
{
	sf::RenderWindow *window;
	sf::CircleShape shape;
	float radius = 5.0;

	Ball(sf::RenderWindow *_window, sf::Vector2f position, sf::Color color)
	{
		window = _window;
		shape.setPosition({position.x - radius, position.y - radius});
		shape.setFillColor(color);
		shape.setRadius(radius);
	}

	void draw()
	{
		window->draw(shape);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "", sf::Style::Default);
	sf::View view(sf::Vector2f(viewWidth / 2, viewHeight / 2), sf::Vector2f(viewWidth, viewHeight));
	sf::Event event;

	window.setFramerateLimit(targetFPS);

	sf::Vector2f mousePosition;

	sf::Keyboard::Key reset     = sf::Keyboard::R;
	sf::Mouse::Button leftClick = sf::Mouse::Left;

	std::mt19937 rng;

	std::vector<Ball> balls;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		if (pressing(reset))
		{
			balls.clear();
		}

		if (pressing(leftClick))
		{
			balls.push_back(
				Ball(&window, mousePosition, getRandomColor(rng))
			);
		}

		window.setView(view);

		for (Ball ball : balls)
		{
			ball.draw();
		}

		window.display();
	}

	return 0;
}
