/**
 * @file Conveyor.h
 * @author Mate Narh
 *
 * Class for a conveyor
 *
 * A conveyor is a rotation sink that is driven by a rotation source.
 * The rotational motion is converted to linear motion, causing bodies
 * on the surface of the conveyor to be propelled in the motion direction.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H

#include <b2_world_callbacks.h>
#include "Component.h"
#include "PhysicsPolygon.h"
#include "RotationSink.h"

/**
 * Class for a conveyor
 */
class Conveyor : public Component, public b2ContactListener
{
private:
    /// The encapsulated physics polygon for this conveyor
    cse335::PhysicsPolygon mConveyor;

    /// Is the surface ramp of the conveyor currently moving ?
    bool mMoving = false;

    /// The rotation sink for this conveyor
    RotationSink mSink;

    /// The speed of this conveyor
    double mSpeed = 0.0;

public:

    Conveyor(const std::wstring &imagesDir);

    wxPoint2DDouble GetPosition();
    wxPoint2DDouble GetShaftPosition();

    void Reset() override;
    void Update(double elapsed) override;
    void SetPosition(double x, double y) override;
    void SetPosition(wxPoint2DDouble position) override;
    void Rotate(double rotation, double speed) override;
    void InstallPhysics(std::shared_ptr<b2World> world) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
