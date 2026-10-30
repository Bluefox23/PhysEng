#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>
#include "RigidBody.h"

struct Collision
{
    bool hit = false;

    Vector2 normal;

    float penetration = 0.0f;
};

class CollisionDetector 
{
public:

    static Collision checkCollision(
        const RigidBody& a,
        const RigidBody& b
    )
    {

        Collision collision;

        Vector2 difference =
            b.position - a.position;

        float distance = difference.length();

        float combinedRadius =
            a.radius + b.radius;

        if (distance >= combinedRadius)
        {
            return collision;
        }

        collision.hit = true;

        if (distance > 0.0001f)
        {
            collision.normal = 
                difference / distance;
        }
        else
        {
            collision.normal = Vector2(1, 0);
        }

        collision.penetration = 
            combinedRadius - distance;

        return collision;
    }
};

#endif


class CollisionResolver
{
public:

    static void resolve(
        RigidBody& a,
        RigidBody& b,
        const Collision& collision
    )
    {
        if (!collision.hit)
            return;

        float invMassA =
            a.isStatic ? 0.0f : 1.0f / a.mass;

        float invMassB = 
            b.isStatic ? 0.0f : 1.0f / b.mass;

        float totalInvMass = 
            invMassA + invMassB;

        if (totalInvMass <= 0.0f)
            return;

        const float percent = 0.8f;
        const float slop = 0.01f;

        float correctionMagnitude =
            std::max(
                collision.penetration - slop,
                0.0f
            ) * percent / totalInvMass;
        
        Vector2 correction = 
            collision.normal * correctionMagnitude;

        if (!a.isStatic)
            a.position -= correction * invMassA;

        if (!b.isStatic)
            b.position += correction * invMassB;

        Vector2 relativeVelocity = 
            b.velocity - a.velocity;

        float velocityAlongNormal = 
            Vector2::dot(
                relativeVelocity,
                collision.normal
            );

        if (velocityAlongNormal > 0.0f)
            return;
        
        float restitution = 
            std::min(a.restitution, b.restitution);

        float impulseMagnitude = 
            -(1.0f + restitution)
            * velocityAlongNormal
            / totalInvMass;

        Vector2 impulse = 
            collision.normal * impulseMagnitude;

        if (!a.isStatic)
            a.velocity -= impulse * invMassA;

        if (!b.isStatic)
            b.velocity += impulse * invMassB;

    }
};