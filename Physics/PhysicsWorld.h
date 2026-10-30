#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include "Collision.h"
#include "RigidBody.h"
#include <vector>

class PhysicsWorld
{
public:

    std::vector<RigidBody> bodies;

    Vector2 gravity = Vector2(0, 980);

    void addBody(RigidBody body)
    {
        bodies.push_back(body);
    }


    void applyGravity()
    {

        for (auto& body : bodies)
        {
            if (!body.isStatic)
            {
                Vector2 gravityForce = 
                    gravity * body.mass;
                
                body.applyForce(gravityForce);

            }
        }
    }
    void handleBoundaries(RigidBody& body)
    {
        if (body.position.x - body.radius < 0)
        {
            body.position.x = body.radius;

            if (body.velocity.x < 0)
                body.velocity.x *= -body.restitution;
        }

        if (body.position.x + body.radius > 1000)
        {
            body.position.x = 1000 - body.radius;

            if (body.velocity.x > 0)
                body.velocity.x *= -body.restitution;
        }

        if (body.position.y - body.radius < 0)
        {
            body.position.y = body.radius;

            if (body.velocity.y < 0)
                body.velocity.y *= -body.restitution;
        }

                if (body.position.y + body.radius > 700)
        {
            body.position.y = 700 - body.radius;

            if (body.velocity.y > 0)
                body.velocity.y *= -body.restitution;
        }
    }


    void update(float deltaTime)
    {
        applyGravity();

        for (auto& body : bodies)
        {
            body.update(deltaTime);
            handleBoundaries(body);
        }

        for (std::size_t i = 0; i < bodies.size(); i++)
        {
            for (std::size_t j = i + 1;
                j < bodies.size(); j++)
            {
                Collision collision = 
                    CollisionDetector::checkCollision(
                        bodies[i],
                        bodies[j]
                    );
                
                if (collision.hit)
                {
                    CollisionResolver::resolve(
                        bodies[i],
                        bodies[j],
                        collision
                    );
                }
            }
        }
    }
};

#endif