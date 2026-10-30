#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2.h"

class RigidBody
{
public:

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    
    float mass;
    float radius;
    float restitution;

    bool isStatic;

    RigidBody(
        Vector2 startPosition = Vector2(0,0),
        float objectMass = 1.0f,
        float objectRadius = 20.0f
    )

        : position(startPosition),
        velocity(0,0),
        acceleration(0,0),
        mass(objectMass),
        radius(objectRadius),
        restitution(0.8f),
        isStatic(false)
    {
    }

    void applyForce(Vector2 force)
    {
        if (isStatic || mass <= 0)
            return;

            acceleration += force / mass;
    }

    void update(float deltaTime)
    {
        if (isStatic)
            return;

        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        acceleration = Vector2(0, 0);

    }

};

#endif