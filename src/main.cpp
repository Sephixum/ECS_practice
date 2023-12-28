#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

auto main() -> int
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My sfml program");
    sf::RectangleShape rec(sf::Vector2f(10.f, 10.f));
    rec.setFillColor(sf::Color::Green);
    rec.setPosition(sf::Vector2f(400.f, 300.f));

    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();
        window.draw(rec);
        window.display();
    }

    return EXIT_SUCCESS;
}