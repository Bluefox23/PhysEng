#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

#include "../Physics/PhysicsWorld.h"

class Renderer
{
private:

    sf::RenderWindow& window;

public:

    Renderer(sf::RenderWindow& target)
        : window(target)
    {
    }

    void drawBody(const RigidBody& body)
    {
        sf::CircleShape circle(body.radius);

        circle.setOrigin(
            sf::Vector2f(
                body.radius,
                body.radius
            )
        );

        circle.setPosition(
            sf::Vector2f(
                body.position.x,
                body.position.y
            )
        );

        circle.setFillColor(
            sf::Color(80,170,255)
        );

        circle.setOutlineThickness(2);

        circle.setOutlineColor(
            sf::Color::White
        );

        window.draw(circle);
    }

    void drawWorld(const PhysicsWorld& world)
    {
        for (const auto& body : world.bodies)
        {
            drawBody(body);
        }
    }

    void drawFloor(float width, float height)
    {
        sf:: RectangleShape floor(
            sf::Vector2f(width, 5)
        );

        floor.setPosition(
            sf::Vector2f(0, height -5)

        );

        floor.setFillColor(
            sf::Color(130, 140, 160)

        );

        window.draw(floor);
    }
};

#endif