#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

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

    void update(float deltaTime)
    {
        applyGravity();

        for (auto& body : bodies)
        {
            body.update(deltaTime);

        }
    }
};

#endif