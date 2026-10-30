
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "../Physics/PhysicsWorld.h"
#include "../Rendering/Renderer.h"

int main()
{
    const unsigned int WIDTH = 1000;
    const unsigned int HEIGHT = 700;

    sf::RenderWindow window(
        sf::VideoMode(WIDTH, HEIGHT),
        "Interactive Physics Engine"
    );

    window.setFramerateLimit(144);

    PhysicsWorld world;
    Renderer renderer(window);


    for (int i = 0; i < 8; i++)
    {
        RigidBody ball(
            Vector2(150 + i * 80, 100),
            2.0f,
            20.0f
        );

        ball.restitution = 0.8f;

        world.addBody(ball);
    }


    bool paused = false;
    bool gravityEnabled = true;
    bool dragging = false;

    int selectedBody = -1;


    sf::Clock clock;

    const float FIXED_DT = 1.0f / 120.0f;

    float accumulator = 0.0f;

    while (window.isOpen())
    {
        float frameTime = clock.restart().asSeconds();

        frameTime = std::min(frameTime, 0.05f);

        sf::Event event;


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                    paused = !paused;

                if (event.key.code == sf::Keyboard::G)
                    gravityEnabled = !gravityEnabled;

                if (event.key.code == sf::Keyboard::R)
                {
                    world.bodies.clear();

                    selectedBody = -1;
                    dragging = false;
                }
            }


            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePixel(
                    event.mouseButton.x,
                    event.mouseButton.y
                );

                sf::Vector2f mousePosition =
                    window.mapPixelToCoords(mousePixel);

                Vector2 point(
                    mousePosition.x,
                    mousePosition.y
                );

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    selectedBody = world.findBodyAt(point);

                    if (selectedBody == -1)
                    {
                        RigidBody ball(
                            point,
                            2.0f,
                            20.0f
                        );

                        world.addBody(ball);

                        selectedBody =
                            static_cast<int>(
                                world.bodies.size() - 1
                            );
                    }

                    dragging = true;
                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    world.applyImpulse(point);
                }
            }


            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    dragging = false;
                    selectedBody = -1;
                }
            }
        }

        if (dragging &&
            selectedBody >= 0 &&
            selectedBody < static_cast<int>(world.bodies.size()))
        {
            sf::Vector2i mousePixel =
                sf::Mouse::getPosition(window);

            sf::Vector2f mousePosition =
                window.mapPixelToCoords(mousePixel);

            RigidBody& body =
                world.bodies[selectedBody];

            if (!body.isStatic)
            {
                body.position = Vector2(
                    mousePosition.x,
                    mousePosition.y
                );

                body.velocity = Vector2(0, 0);
            }
        }


        if (!paused)
        {
            accumulator += frameTime;

            while (accumulator >= FIXED_DT)
            {
                world.gravity = gravityEnabled
                    ? Vector2(0, 980)
                    : Vector2(0, 0);

                world.update(FIXED_DT);

                accumulator -= FIXED_DT;
            }
        }

        window.clear(sf::Color(20, 22, 30));

        renderer.drawFloor(
            static_cast<float>(WIDTH),
            static_cast<float>(HEIGHT)
        );

        renderer.drawWorld(world);

        window.display();
    }

    return 0;
}
