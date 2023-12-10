/**
 * @file Curtain.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include "Curtain.h"

/// Image to draw for the curtain rod
const std::wstring CurtainRod = L"/curtain-rod.png";

/// Image to draw for the left curtain
const std::wstring LeftCurtain = L"/curtain1.png";

/// Image to draw for the right curtain
const std::wstring RightCurtain = L"/curtain2.png";

/// Height of our curtains in pixels
const double CurtainHeight = 500;

/// Total width of the curtains in pixels
const double CurtainWidth = 750;

/// Number of seconds to open the curtains
const double CurtainOpenTime = 2.0;

/// Minimum scaling factor for when the curtains are open
const double CurtainMinScale = 0.18f;

/// The size of the curtain rod
const auto RodSize = wxSize(750, 500);

/// Size of the left and right curtain
const auto CurtainSize = wxSize(375, 500);

/// Scale reduction per second
const double ScaleReduction = 0.02f;

/// The rotation of the curtain parts (zero)
const double CurtainRotation = 0.0;


/**
 * Constructor
 * @param imagesDir The images directory
 */
Curtain::Curtain(const std::wstring &imagesDir)
{
    mRod.BottomCenteredRectangle(CurtainWidth, CurtainHeight);
    mRod.SetImage(imagesDir + CurtainRod);

    mLeftCurtain.SetImage(imagesDir + LeftCurtain);
    mLeftCurtain.BottomCenteredRectangle(CurtainWidth/2, CurtainHeight);

    mRightCurtain.SetImage(imagesDir + RightCurtain);
    mRightCurtain.BottomCenteredRectangle(CurtainWidth/2, CurtainHeight);
}

/**
 * Reset this curtain if the current machine frame is 0
 */
void Curtain::Reset()
{

}


/**
 * Update the time of this curtain
 * @param elapsed The time elapsed
 */
void Curtain::Update(double elapsed)
{

}

/**
 * Draw the rod beneath the left and right curtain
 * @param graphics The graphics context object to draw on
 */
void Curtain::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //
    // First : Reset the state of the curtains
    //
    ResetCurtainState();

    //
    // Draw the rod
    //
    mRod.DrawPolygon(graphics, mRodPos.m_x, mRodPos.m_y, CurtainRotation);

    //
    // Draw the left curtain and the right curtain
    //
    DrawCurtains(graphics);
    mPreviousTime = GetMachine()->GetMachineTime();
}

/**
 * Set the position of this curtain
 * @param x The new horizontal location
 * @param y The new vertical location
 */
void Curtain::SetPosition(double x, double y)
{
    mRodPos = wxPoint2DDouble(x, y);
    mLeftPos = wxPoint2DDouble(x - CurtainSize.x / 2, y);
    mRightPos = wxPoint2DDouble(x + CurtainSize.x / 2, y);
}

/**
 * Draw the left and right curtain only
 * @param graphics The graphics context object to draw on
 */
void Curtain::DrawCurtains(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto wid = CurtainWidth / 2;
    auto residue = 1 - mXScale;

    //
    // Drag the left curtain to the left via -ve translation and reduced scale
    //
    graphics->PushState();
    graphics->Translate( -residue * wid, 1 );
    graphics->Scale(mXScale, 1);
    mLeftCurtain.DrawPolygon(graphics, mLeftPos.m_x, mLeftPos.m_y, CurtainRotation);
    graphics->PopState();

    //
    // Drag the right curtain to the right via +ve translation and reduced scale
    //
    graphics->PushState();
    graphics->Translate( residue * wid, 1 );
    graphics->Scale(mXScale, 1);
    mRightCurtain.DrawPolygon(graphics,  mRightPos.m_x, mRightPos.m_y, CurtainRotation);
    graphics->PopState();
}

/**
 * Reset the state of the left and right curtain
 * Determine if they are opening, closing, or stationary
 */
void Curtain::ResetCurtainState()
{
    //
    // Defining and resetting the state of the curtains
    //

    auto currentTime = GetMachine()->GetMachineTime();

    mDirection = (mPreviousTime < currentTime) ? Direction::Forward : Direction::Reverse;

    //
    // The curtains should be stationary at start (t = 0) and when the
    // current time is beyond their opening window (t >= CurtainOpenTime)
    //
    if (currentTime >= CurtainOpenTime || currentTime == 0)
        mState = State::Stationary;

    //
    // If we are not exactly at the start or ARE currently within the
    // opening window of the curtain we need to open / close the curtains
    //
    else
    {
        //
        // If we are moving forward, within this time window, open the curtains
        //
        if (mDirection == Direction::Forward)
            mState = State::Open;

        //
        // If we are reversing, within this time window, close the curtains
        //
        else
            mState = State::Close;
    }

    //
    // 1 Open the curtains by reducing the horizontal scale, dragging them apart
    //
    if ( mState == State::Open )
        mXScale -= ScaleReduction;

    //
    // 2 Close the curtains by increasing the horizontal cale, pulling them together
    //
    else if ( mState == State::Close)
        mXScale += ScaleReduction;

    //
    // 3 If the curtain is stationary, restore or cap its scaling
    //
    else if ( mState == State::Stationary )
    {
        //
        // At start, the stationary curtains should be at 100% of their horizontal scale
        //
        if (currentTime == 0)
            mXScale = 1;

        //
        // At the time bridge (t == CurtainOpenTime) and beyond, the stationary curtains
        // should be limited or capped at their minimum horizontal scale of 20%
        //
        else
            mXScale = CurtainMinScale;
    }
}



