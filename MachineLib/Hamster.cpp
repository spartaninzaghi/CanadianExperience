/**
 * @file Hamster.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <b2_contact.h>
#include "Hamster.h"
#include "MachineSystem.h"
#include "RotationSink.h"

/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is how many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};

/**
 * Constructor
 * @param imagesDir The image directory for this Hamster's image files
 */
Hamster::Hamster(const std::wstring & imagesDir)
{
    //
    // Initialize the cage
    //
    mCage.BottomCenteredRectangle(HamsterCageSize);
    mCage.SetImage(imagesDir + HamsterCageImage);

    //
    // Initialize the wheel
    //
    mWheel.CenteredSquare(HamsterWheelSize);
    mWheel.SetImage(imagesDir + HamsterWheelImage);

    //
    // Set this hamster's images
    //
    for (auto hamsterImage : HamsterImages)
    {
        auto hamster = std::make_shared<cse335::Polygon>();
        hamster->CenteredSquare(HamsterSize);
        hamster->SetImage(imagesDir + hamsterImage);
        mHamsters.push_back(hamster);
    }
}

/**
 * Update the animation for this hamster
 * @param elapsed The new time
 */
void Hamster::Update(double elapsed)
{
    if (!mRunning)
        return;

    //
    // Update the hamster index if it is running
    //
    mRotation += -mSpeed * elapsed;
    mRuntime += elapsed;

    //
    // Switch to the appropriate hamster image based on the cycle
    //
    SwitchHamsterImage();

    //
    // Hamster is a rotation source : Rotate its rotation sink
    //
    if (mSource.GetSink() && mRunning) // reverse the speed for clockwise rotation
        mSource.GetSink()->Rotate(mRotation, -mSpeed);
}

/**
 * Draw this hamster
 * @param graphics The graphics context object to draw on
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //
    // Draw the cage first
    //
    mCage.Draw(graphics);

    //
    // Draw the wheel next
    //
    mWheel.DrawPolygon(graphics, mWheelPosition.m_x, mWheelPosition.m_y, mRotation);

    //
    // Draw the hamster
    //
    // At frame 0, draw a sleeping hamster if it is not initially running
    //
    graphics->PushState();
    graphics->Translate(mWheelPosition.m_x, mWheelPosition.m_y);

    if(mSpeed < 0 && mHamsterIndex)
        graphics->Scale(-1, 1);

    mHamsters[mHamsterIndex]->DrawPolygon(graphics, 0, 0, 0);

    graphics->PopState();
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    mRunning = true;
}

/**
 * Install this hamster in the physics world of its machine
 * @param world The physics system of this hamster's machine
 */
void Hamster::InstallPhysics(std::shared_ptr<b2World> world)
{
    mCage.InstallPhysics(world);
    GetMachine()->GetContactListener()->Add(mCage.GetBody(), this);
}

/**
 * Set the position of this hamster and its parts given single x, y values
 * @param x The new x coordinate
 * @param y The new y corrdinate
 */
void Hamster::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);
    mWheelPosition = mPosition + WheelCenter;
    mCage.SetInitialPosition(x, y);
}

/**
 * Set the position of this hamster and its parts given a point
 * @param position The new point position
 */
void Hamster::SetPosition(wxPoint2DDouble position)
{
    mPosition = position;
    mWheelPosition = mPosition + WheelCenter;
    mCage.SetInitialPosition(position.m_x, position.m_y);
}


/**
 * Set the initial running status of this hamster
 * @param running The new initial running status of this hamster
 */
void Hamster::SetInitiallyRunning(bool running)
{
    mInitiallyRunning = running;
    SetRunning(running);

    if (mInitiallyRunning)
        mHamsterIndex = 1;
}

/**
 * Get the position of the shaft of this hamster
 * @return The position of the shaft of this hamster
 */
wxPoint2DDouble Hamster::GetShaftPosition() const
{
    return mPosition + HamsterShaftOffset;
}

/**
 * Get a pointer to the source object
 * @return Pointer to RotationSource object
 */
RotationSource *Hamster::GetSource()
{
    return &mSource;
}

/**
 * Determine if this hamster is running at the start of the system
 * @return True if this hamster is initially running
 */
bool Hamster::IsInitiallyRunning() const
{
    return mInitiallyRunning;
}

/**
 * Set the current running status of this hamster
 * @param running The new current running status of this hamster
 */
void Hamster::SetRunning(bool running)
{
    mRunning = running;
}

/**
 * Is this hamster currently running ?
 * @return True if hamster is currently running, else false
 */
bool Hamster::IsRunning() const
{
    return mRunning;
}

/**
 * Set the speed of this hamster
 * @param speed The new speed
 */
void Hamster::SetSpeed(double speed)
{
    mSpeed = speed;
    mCyclePeriod = 1 / abs(mSpeed) / HamsterSpeed;
}

/**
 * Get the speed of this hamster
 * @return The speed of this hamster
 */
double Hamster::GetSpeed() const
{
    return mSpeed;
}

/**
 * Set the rotation of this hamster
 * @param rotation The new rotation
 */
void Hamster::SetRotation(double rotation)
{
    mRotation = rotation;
}

/**
 * Get the rotation for this hamster
 * @return The rotation for this hamster
 */
double Hamster::GetRotation() const
{
    return mRotation;
}

/**
 * Reset this hamster if the current machine frame is 0
 * and this hamster is not initially running
 */
void Hamster::Reset()
{
    if (!mInitiallyRunning)
    {
        mRotation = 0;
        mRunning = false;
        mHamsterIndex = 0;
        mCycleMode = Mode::Advance;
    }
}

/**
 * Advance to the next hamster image
 */
void Hamster::SwitchHamsterImage()
{
    if (mRunning && mRuntime >= mCyclePeriod / HamsterSpeed)
    {
        //
        // Move forward through the hamster image indices until we arrive at 3
        //
        if(mHamsterIndex == 1)
            mCycleMode = Mode::Advance;

        else if(mHamsterIndex == 3)
            mCycleMode = Mode::Reverse;

        //
        // Set the current hamster image index based on the cycle mode
        //
        if(mCycleMode == Mode::Advance)
            mHamsterIndex++;
        else
            mHamsterIndex--;

        //
        // Reset the hamster runtime for the next cycle
        //
        mRuntime = 0;
    }
}



