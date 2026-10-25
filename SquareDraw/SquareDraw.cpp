#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
std::string CycleIteration(int iteration) {
	std::string axiom = "F";
	std::string rule = "F+F-F";
	std::string currentString = axiom;

	for (int i = 0; i < iteration; i++) {
		std::string nextString;
		for (char c : currentString) {
			if (c == 'F') { nextString += rule; }
			else { nextString += c; }
		}
		currentString = nextString;
	}
	return currentString;
}

class Turtle {
private:
	int lengthLines;
	float angle;

	float startX;
	float startY;

	const float pi = 3.14;

	sf::RenderWindow* window;
	sf::VertexArray allLines;

	float initialX, initialY, initialAngle;

public:
	void Init(sf::RenderWindow* windoww, int length_, float angle_, float x, float y) {
		lengthLines = length_;
		angle = angle_;

		startX = x;
		startY = y;

		initialX = x;
		initialY = y;
		initialAngle = angle_;

		window = windoww;
		allLines.setPrimitiveType(sf::Lines);

	}
	float newPositionX() {
		return (startX + lengthLines * cos(angle * pi / 180));
	}
	float newPositionY() {
		return (startY + lengthLines * sin(angle * pi / 180));
	}

	void CycleByString(string lines) {
		for (char simbol : lines) {
			switch (simbol)
			{
			case 'F':
				Forward();
				break;
			case '+':
				angle -= 120;
				break;
			case '-':
				angle += 120;
				break;
			}
		}
	}
	void Forward() {
		float nextX = newPositionX();
		float nextY = newPositionY();

		allLines.append(sf::Vertex({ startX, startY }, sf::Color::White));
		allLines.append(sf::Vertex({ nextX, nextY }, sf::Color::White));

		startX = nextX;
		startY = nextY;
	}

	void Draw() {
		window->draw(allLines);
	}
	void Reset() {
		allLines.clear();
		startX = initialX;
		startY = initialY;
		angle = initialAngle;
	}
};
void DrawFractal() {
	int count = 0;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fractal");

	Turtle turtle;
	turtle.Init(&window, 10, 0, 800, 200);
	std::string str = CycleIteration(count);

	turtle.CycleByString(str);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			// Обработка нажатия пробела
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					count++;

					// Сбрасываем черепаху и строим новый фрактал
					turtle.Reset();
					str = CycleIteration(count);
					turtle.CycleByString(str);
				}
			}
		}
		window.clear();
		turtle.Draw();
		window.display();
	}
}
int main() {
	setlocale(LC_ALL, "RUS");
	DrawFractal();
};
