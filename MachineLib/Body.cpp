/**
 * @file Body.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include "Body.h"

/**
 * Constructor
 */
Body::Body() : Component()
{
    mSink.SetComponent(this);
}

/**
 * Draw this body
 * @param graphics The graphics context object to draw on
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mBody.Draw(graphics);
}


/**
 * Set the images directory of this component;
 * @param imagesDir The images directory of this component
 */
void Body::SetImage(const std::wstring &imagesDir)
{
    mBody.SetImage(imagesDir);
}

/**
 * Add a point to this body
 * @param x The x coordinate of the new point
 * @param y The y coordinate of the new point
 */
void Body::AddPoint(double x, double y)
{
    mBody.AddPoint(x, y);
}

/**
 * Set the initial position of this body given x and y coordinates
 * @param x The x coordinate of the initial position
 * @param y The y coordinate of the initial position
 */
void Body::SetInitialPosition(double x, double y)
{
    mBody.SetInitialPosition(x, y);
}

/**
 * Set the initial position of this body given a point position
 * @param position The initial position of this body as a point
 */
void Body::SetInitialPosition(wxPoint2DDouble position)
{
    mBody.SetInitialPosition(position.m_x, position.m_y);
}

/**
 * Enable this body to move by the laws of physics by making
 * it a dynamic body
 */
void Body::SetDynamic()
{
    mBody.SetDynamic();
}

/**
 * Enable this body to remain fixed in space while having a
 * fixed rotational speed
 */
void Body::SetKinematic()
{
    mBody.SetKinematic();
}

/**
 * Make this body a circle centered on (0,0)
 * @param radius Circle radius
 * @param steps Number of steps in circle (0=default)
 */
void Body::Circle(double radius, int steps)
{
    mBody.Circle(radius, steps);
}

/**
 * Create a rectangle.
 *
 * If the height parameter is not supplied and an image
 * has been set, the height will be computed so as to
 * keep the original image aspect ratio correct.
 *
 * @param x Left side X
 * @param y Bottom left Y
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 */
void Body::Rectangle(double x, double y, double width, double height)
{
    mBody.Rectangle(x, y, width, height);
}

/**
 * Create a rectangle where 0,0 is the bottom center of the rectangle.
 *
 * Must set an image first if not providing a width and height.
 *
 * @param width Width of the rectangle in pixels. If not supplied, use the image width.
 * @param height Height of the rectangle in pixels. If not supplied, select a height such
 * that the aspect ratio matches that of the image.
 */
void Body::BottomCenteredRectangle(double width, double height)
{
    mBody.BottomCenteredRectangle(width, height);
}

/**
 * Set the physics characteristics of this component.
 *
 * Must be called before InstallPhysics is called.
 * @param density Density in kg/m^2
 * @param friction Friction coefficient in the range [0, 1]
 * @param restitution Restitution value in the rnnge [0, 1]
 */
void Body::SetPhysics(double density, double friction, double restitution)
{
    mBody.SetPhysics(density, friction, restitution);
}

/**
 * Set the component rotation (current)
 *
 * Rotation is in turns, not radians or degrees
 *
 * @param rotation Rotation in turns
 */
void Body::SetInitialRotation(double rotation)
{
    mBody.SetInitialRotation(rotation);
}

/**
 * Install this body into the physics system of its machine
 * @param world The physics system of this body's machine
 */
void Body::InstallPhysics(std::shared_ptr<b2World> world)
{
    mBody.InstallPhysics(world);
}

/**
 * Update the time of this body
 * @param elapsed The time elapsed
 */
void Body::Update(double elapsed)
{

}

/**
 * Rotate this body using the rotation speed of its rotation source
 * @param rotation The new rotation
 * @param speed The new speed
 */
void Body::Rotate(double rotation, double speed)
{
    mBody.SetAngularVelocity(speed);
}

/**
 * Get the rotation sink of this body
 * @return The rotation sink of this body
 */
RotationSink *Body::GetSink()
{
    return &mSink;
}

/**
 * Reset this body if the current machine frame is 0
 */
void Body::Reset()
{
    mBody.SetAngularVelocity(0);
}




