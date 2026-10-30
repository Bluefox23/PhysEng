#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    std::cout << "Physics Engine Starting!" << std::endl;

    sf::RenderWindow window(
        sf::VideoMode(1000,700),
        "My Physics Engine"
    );

    window.setFramerateLimit(60);

    while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color(20,22,30));

        window.display();

    }
    return 0;

}