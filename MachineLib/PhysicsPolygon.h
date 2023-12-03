/**
 * @file PhysicsPolygon.h
 * @author Charles Owen
 *
 * A Polygon object that can install itself into the
 * physics system.
 *
 * Note: Dimensions for the PhysicsPolygon object are in
 * centimeters.
 *
 * Version history:
 * 1.00 Initial version for FS23 project 2
 * 1.01 Revised to work prior to physics installation
 */

#pragma once

#include "Polygon.h"
#include <b2_math.h>
#include <b2_body.h>

class b2Body;
class b2World;

namespace cse335
{
/**
 * A Polygon object that can install itsel into the
 * physics system.
 *
 * Note: Dimensions for the PhysicsPolygon object are in
 * centimeters.
 *
 * Objects are by default static bodies. The function calls
 * SetDynamic and SetKinematic can be used to set different
 * states.
 */
class PhysicsPolygon : public Polygon
{
private:
    /// The physics system body for this component
    /// Null until installed in the physics system
    b2Body *mBody = nullptr;

    /// Initial rotation of the component in radians
    double mInitialRotation = 0;

    /// The location of the component in the machine
    wxPoint2DDouble mInitialPosition;

    /// What is the body type
    b2BodyType mType = b2_staticBody;

    /// Density in kg/m^2
    double mDensity = 1.0;

    /// Friction coefficient in the range [0, 1]
    double mFriction = 0.5f;

    /// Restitution (elasticity) in the range [0, 1]
    double mRestitution = 0.5;

public:
    PhysicsPolygon();

    /// Copy constructor (disabled)
    PhysicsPolygon(const PhysicsPolygon &) = delete;

    /// Assignment operator
    void operator=(const PhysicsPolygon &) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Set the component position in the machine
     * @param x X position in centimeters
     * @param y Y position in centimeters
     */
    void SetInitialPosition(double x, double y) { mInitialPosition = wxPoint2DDouble(x, y); }

    /**
     * Set the component initial rotation
     * @param r Rotation in turns (0-1 for one rotation)
     */
    void SetInitialRotation(double r) { mInitialRotation = r * M_PI * 2; }

    void SetRotation(double rotation);

    void SetAngularVelocity(double speed);

    virtual double GetRotation();

    wxPoint2DDouble GetPosition();

    void InstallPhysics(std::shared_ptr<b2World> world);

    void SetDynamic();
    void SetKinematic();
    void SetPhysics(double density=1.0, double friction=0.5, double restitution=0.5);

    /**
     * Get the physics body for this component.
     *
     * Only set after InstallPhysics has been called.
     * @return b2Body object
     */
    b2Body* GetBody() {return mBody;}
};

} // cse335

