/**
 * @file Body.h
 * @author Mate Narh
 *
 * Class for a body in a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H

#include "Component.h"
#include "RotationSink.h"
#include "PhysicsPolygon.h"

/**
 * Class for a body in a machine
 */
class Body : public Component
{
private:

    RotationSink mSink; /// The rotation sink for this body


    cse335::PhysicsPolygon mBody; /// The physics polygon that defines this body

    /// Default number of steps when drawing a circle
    static const int DefaultCircleSteps = 32;

public:

    Body();

    void SetDynamic();
    void SetKinematic();
    RotationSink *GetSink();
    void SetInitialRotation(double r);
    void SetInitialPosition(double x, double y);
    void SetInitialPosition(wxPoint2DDouble position);
    void SetImage(const std::wstring &imagesDir);
    void SetPhysics(double density=1.0, double friction=0.5, double restitution=0.5);
    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void Reset() override;
    void AddPoint(double x, double y);
    void Update(double elapsed) override;
    void Rotate(double rotation, double speed) override;
    void Circle(double radius, int steps=DefaultCircleSteps);
    void BottomCenteredRectangle(double width, double height);
    void Rectangle(double x, double y, double width, double height);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /// Copy constructor (disabled)
    Body(const Body &) = delete;

    /// Assignment operator
    void operator=(const Body &) = delete;


};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
