/**
 * @file Conveyor.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <b2_contact.h>
#include "Conveyor.h"

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * Constructor
 * @param imagesDir The image directory for this conveyor's image file
 */
Conveyor::Conveyor(const std::wstring &imagesDir) : Component()
{
    mConveyor.BottomCenteredRectangle(ConveyorSize);
    mConveyor.SetImage(imagesDir + ConveyorImageName);

    mSink.SetComponent(this);
}

/**
 * Update the animation of this conveyor and its associations
 * If there are objects on the surface of the conveyor, cause
 * them to move linearly at the speed of the conveyor
 * @param elapsed The new time
 */
void Conveyor::Update(double elapsed)
{
    //
    // Translate every body on the conveyor
    //
    auto contact = mConveyor.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(-mSpeed, 0));
        }
        contact = contact->next;
    }
}

/**
 * Draw this conveyor
 * @param graphics The graphics context object to draw on
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mConveyor.Draw(graphics);
}

/**
 * Install this conveyor in the physics system world of its machine
 * @param world The physics system world of this conveyor's machine
 */
void Conveyor::InstallPhysics(std::shared_ptr<b2World> world)
{
    mConveyor.InstallPhysics(world);
    GetMachine()->GetContactListener()->Add(mConveyor.GetBody(), this);
}

/**
 * Set the position of this component given an x and y value
 * @param x The new x coordinate in pixels
 * @param y The new y coordinate in pixels
 */
void Conveyor::SetPosition(double x, double y)
{
    mConveyor.SetInitialPosition(x, y);
}


/**
 * Set the position of this hamster and its parts given a point
 * @param position The initial position of this conveyor
 */
void Conveyor::SetPosition(wxPoint2DDouble position)
{
    mConveyor.SetInitialPosition(position.m_x, position.m_y);
}

/**
 * Get the position of this conveyor
 * @return The position of this conveyor
 */
wxPoint2DDouble Conveyor::GetPosition()
{
    return mConveyor.GetPosition();
}


/**
 * Rotate this conveyor by translating the bodies on its surface
 * @param rotation The new rotation
 * @param speed The new speed
 */
void Conveyor::Rotate(double rotation, double speed)
{
    mSpeed = speed;
}


/**
 * Get the shaft position of this conveyor
 * @return The shaft position of this conveyor
 */
wxPoint2DDouble Conveyor::GetShaftPosition()
{
    return GetPosition() + ConveyorShaftOffset;
}

/**
 * Handle conditions called right before the contact with this conveyor occurs
 * @param contact Contact object
 * @param oldManifold A manifold object
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(mSpeed);
}

/**
 * Reset this conveyor if the current machine frame is 0
 */
void Conveyor::Reset()
{
    mSpeed = 0;
}

