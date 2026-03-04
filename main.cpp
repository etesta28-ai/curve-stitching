#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

struct Line {
    sf::Vector2f p1;
    sf::Vector2f p2;
};

int main() {
    const int WIDTH = 600;
    const int HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Curve Stitching from CSV");
    std::vector<Line> lines;
    std::ifstream file("stitches.csv");
    if (!file.is_open()) {
        std::cout << "Failed to open CSV file.\n";
        return 1;
    }

    std::string row;

    std::getline(file, row);

    while (std::getline(file, row)) {
        std::stringstream ss(row);
        std::string value;
        std::vector<float> coords;

        while (std::getline(ss, value, ',')) {
            coords.push_back(std::stof(value));
        }

        if (coords.size() == 4) {
            Line line;
            line.p1 = sf::Vector2f(coords[0], coords[1]);
            line.p2 = sf::Vector2f(coords[2], coords[3]);
            lines.push_back(line);
        }
    }

    file.close();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (const auto& line : lines) {
            sf::Vertex vertices[] = {
                sf::Vertex(line.p1, sf::Color::Black),
                sf::Vertex(line.p2, sf::Color::Black)
            };

            window.draw(vertices, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
