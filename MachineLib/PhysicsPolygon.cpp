/**
 * @file PhysicsPolygon.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PhysicsPolygon.h"
#include "Consts.h"
#include <b2_polygon_shape.h>
#include <b2_circle_shape.h>
#include <b2_fixture.h>
#include <b2_world.h>

/**
 * Constructor
 */
cse335::PhysicsPolygon::PhysicsPolygon() : Polygon()
{
}

/**
 * Draw the component
 * @param graphics Graphics device to render to
 */
void cse335::PhysicsPolygon::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto position = GetPosition();
    auto rotation = GetRotation();

    DrawPolygon(graphics, position.m_x, position.m_y, rotation);
}

/**
 * Install this component into the physics system world.
 * @param world Physics system world
 */
void cse335::PhysicsPolygon::InstallPhysics(std::shared_ptr<b2World> world)
{
    // Create the physics system body we will need for any
    // item in the physics space
    b2BodyDef bodyDefinition;
    bodyDefinition.type = mType;
    mBody = world->CreateBody(&bodyDefinition);

    b2FixtureDef fixtureDef;

    // These must be in the same scope as fixtureDef:
    b2CircleShape circle;
    b2PolygonShape poly;

    if(IsCircle())
    {
        circle.m_radius = Radius() / Consts::MtoCM - 0.005;
        fixtureDef.shape = &circle;
    }
    else
    {
        // Determine the maximum values in each dimension
        auto boundingBox = Polygon::BoundingBox();

        // Box2D adds a 0.5cm "skin" around objects. This shrinks the
        // representation in that system to reflect that extra skin in the size
        auto size = wxPoint2DDouble(boundingBox.m_width/2, boundingBox.m_height/2);
        auto center = boundingBox.GetCentre();
        auto scale = (size - wxPoint2DDouble(0.95, 0.95)) / size;

        std::vector<b2Vec2> vertices;
        for(auto v : *this)
        {
            auto scaled = ((v - center) * scale) + center;

            vertices.push_back(b2Vec2(scaled.m_x / Consts::MtoCM, scaled.m_y / Consts::MtoCM));
        }

        poly.Set(&vertices[0], vertices.size());
        fixtureDef.shape = &poly;
    }

    fixtureDef.density = mDensity;
    fixtureDef.friction = mFriction;
    fixtureDef.restitution = mRestitution;

    mBody->CreateFixture(&fixtureDef);

    mBody->SetTransform(b2Vec2(mInitialPosition.m_x / Consts::MtoCM,
                               mInitialPosition.m_y / Consts::MtoCM), mInitialRotation);

}

/**
 * Get the component position in the machine.
 * @return Position in pixels
 */
wxPoint2DDouble cse335::PhysicsPolygon::GetPosition()
{
    if(mBody != nullptr)
    {
        // Once installed in the physics system, we us
        // the current position from that system, converting
        // meters to centimeters.
        auto position = mBody->GetPosition();

        return wxPoint2DDouble(position.x * Consts::MtoCM, position.y * Consts::MtoCM);
    }
    else
    {
        return mInitialPosition;
    }
}


/**
 * Set the component rotation (current)
 *
 * Rotation is in turns, not radians or degrees
 *
 * @param rotation Rotation in turns
 */
void cse335::PhysicsPolygon::SetRotation(double rotation)
{
    if(mBody != nullptr)
    {
        mBody->SetTransform(mBody->GetPosition(), rotation * M_PI * 2);
        mBody->SetGravityScale(0);
    }
    else
    {
        SetInitialRotation(rotation);
    }
}


/**
 * Get the component rotation
 * @return Rotation in turns (0-1)
 */
double cse335::PhysicsPolygon::GetRotation()
{
    if(mBody != nullptr)
    {
        auto rotation = mBody->GetAngle();
        return rotation / (M_PI * 2);
    }
    else
    {
        auto rotation = mInitialRotation;
        return rotation / (M_PI * 2);
    }

}


/**
 * Make this component a dynamic component
 *
 * Dynamic components move based on the physics
 */
void cse335::PhysicsPolygon::SetDynamic() {
    mType = b2_dynamicBody;
}

/**
 * Make this component a dynamic component
 *
 * Dynamic components move based on the physics and
 * defined velocities.
 */
void cse335::PhysicsPolygon::SetKinematic() {
    mType = b2_kinematicBody;
}

/**
 * Set the physics characteristics of this component.
 *
 * Must be called before InstallPhysics is called.
 * @param density Density in kg/m^2
 * @param friction Friction coefficient in the range [0, 1]
 * @param restitution Restitution value in the rnnge [0, 1]
 */
void cse335::PhysicsPolygon::SetPhysics(double density, double friction, double restitution)
{
    mDensity = density;
    mFriction = friction;
    mRestitution = restitution;
}

/**
 * Set the angular velocity (rotation speed)
 * @param speed Speed in turns per second
 */
void cse335::PhysicsPolygon::SetAngularVelocity(double speed)
{
    if(mBody != nullptr)
    {
        mBody->SetAngularVelocity(speed * M_PI * 2);
    }
}





