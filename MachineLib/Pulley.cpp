/**
 * @file Pulley.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <cmath>
#include "Pulley.h"

/// Type definition for wxPoint2DDouble
using wxP2DD = wxPoint2DDouble;

/// The scale of the pulley belt. This tucks
/// in the belts tightly behind the pulley
/// by trimming its separation by 95%
const double BeltScale = 0.93f;

/// Maximum amount to rock the belt
/// in pixels per second
const double BeltRockAmount = 1;

/// How quickly to rock the belt in radians per second
/// This is divided by the length to get the actual rate
const double BeltRockBaseRate = M_PI * 1000;


/**
 * Constructor
 * @param radius The radius of this pulley
 */
Pulley::Pulley(double radius)
{
    mRadius = radius;
    mPulley.CenteredSquare(mRadius * 2);

    mSink.SetComponent(this);
}


/**
 * Reset this pulley if the current machine frame is 0
 */
void Pulley::Reset()
{
    mSpeed = 0;
    mRotation = 0;
}

/**
 * Update the animation of this pulley
 * @param elapsed
 */
void Pulley::Update(double elapsed)
{
    //
    // If this pulley is a source :
    // update its sink to rotate at its speed
    //
    if (GetSource() && mSource.GetSink())
        mSource.GetSink()->Rotate(mRotation, mSpeed);
}


/**
 * Draw this pulley
 * @param graphics The graphics context object to draw on
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //
    // Draw the belts first so that they appear to slot over the pulleys
    //
    DrawBelts(graphics);

    //
    // Draw the pulley
    //
    mPulley.DrawPolygon(graphics, GetPosition().m_x, GetPosition().m_y, mRotation);
}

/**
 * Rotate this pulley
 * @param rotation The new rotation angle
 * @param speed The new rotation speed
 */
void Pulley::Rotate(double rotation, double speed)
{
    mSpeed =  speed;

    //
    // The pulley ratio is 0 (False) if this pulley is not being
    // driven by another pulley
    //
    // Bigger pulleys should rotate slower than smaller pulleys
    //
    mRotation = mPulleyRatio ? rotation * mPulleyRatio : rotation;
}

/**
 * Cause this pulley to drive the given pulley
 * @param drivenPulley The other pulley to drive
 */
void Pulley::Drive(std::shared_ptr<Pulley> drivenPulley)
{
    mDrivenPulley = drivenPulley;

    //
    // The current pulley is a Source / Driving pulley
    //
    // Set the pulley ratio of the Second / Driven / Sink Pulley
    // using its radius and the radius of its source. This will
    // be used to scale its speed if the sink & source radii differ:
    //
    // Pulley Ratio : drivingPulley->mRadius / drivenPulley->mRadius
    //
    mDrivenPulley->mPulleyRatio = mRadius / mDrivenPulley->mRadius;

    mSource.AddSink(mDrivenPulley);
}

/**
 * Set the image for this pulley
 * @param imagesDir The image directory for this pulley
 */
void Pulley::SetImage(const std::wstring &imagesDir)
{
    mPulley.SetImage(imagesDir);
}

/**
 * Draw belts connecting this pulley to its driven pulley if applicable
 * @param graphics The graphics context object to draw on
 */
void Pulley::DrawBelts(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPen beltPen(*wxBLACK, 2);
    graphics->SetPen(beltPen);

    //
    // A source pulley will have a driven pulley (non-null)
    //
    bool isSource = mDrivenPulley != nullptr;

    if (isSource)
    {
        //
        // Belt Math for pulleys of the same radii or different radii
        //
        auto p1 = GetPosition();
        auto p2 = mDrivenPulley->GetPosition();

        auto r1 = mRadius;                 // Source radius
        auto r2 = mDrivenPulley->mRadius;  // Sink radius

        //
        // Compute beta
        //
        auto beta = ComputeBeta();

        auto offset1  = BeltScale * wxPoint2DDouble( r1 * cos(beta), r1 * sin(beta) );
        auto offset2  = BeltScale * wxPoint2DDouble( r2 * cos(beta), r2 * sin(beta) );

        //
        // Compute the actual positions of Belt #1 and Belt #2
        //
        auto belt1P1 = p1 + offset1;
        auto belt1P2 = p2 + offset2;

        auto belt2P1 = p1 - offset1;
        auto belt2P2 = p2 - offset2;

        //
        // Rock Belts
        //
        RockBelts((wxP2DD &)belt1P1, (wxP2DD &)belt1P2, (wxP2DD &)belt2P1, (wxP2DD &)belt2P2);

        //
        // Draw Belt #1 and Belt #2
        //
        graphics->StrokeLine(belt1P1.m_x, belt1P1.m_y, belt1P2.m_x, belt1P2.m_y);
        graphics->StrokeLine(belt2P1.m_x, belt2P1.m_y, belt2P2.m_x, belt2P2.m_y);
    }
}

/**
 * Get a pointer to the source object
 * @return Pointer to RotationSource object
 */
RotationSource *Pulley::GetSource()
{
    return &mSource;
}

/**
 * Get the rotation sink of this body
 * @return The rotation sink of this body
 */
RotationSink *Pulley::GetSink()
{
    return &mSink;
}

/**
 * Get the driven pulley (if this pulley is a rotation source for another pulley)
 * @return The driven pulley
 */
std::shared_ptr<Pulley> Pulley::GetDrivenPulley() const
{
    return mDrivenPulley;
}

/**
 * Set the angular rotation of this pulley
 * @param rotation The new angular rotation
 */
void Pulley::SetRotation(double rotation)
{
    mRotation = rotation;
}

/**
 * Get the angular rotation of this pulley
 * @return The angular rotation of this pulley
 */
double Pulley::GetRotation() const
{
    return mRotation;
}

/**
 * Compute the beta value for drawing this pulley's belts
 * if the pulley is a source of rotation
 * @return The beta value for drawing this pulley's belts
 */
double Pulley::ComputeBeta()
{
    //
    // Positive rotation means turning counter-clockwise
    //
    // This corresponds to a negative speed
    // (counter-clockwise turns per second)
    //
    bool isPositiveRotation = mSpeed < 0;

    auto p1 = GetPosition();                // P1(x1, y1) : Source center
    auto p2 = mDrivenPulley->GetPosition(); // P2(x2, y2) : Sink center

    auto r1 = mRadius;                      // Source radius
    auto r2 = mDrivenPulley->mRadius;       // Sink radius

    auto sep = (p2 - p1).GetVectorLength(); // The distance between the centers of
                                            // The driving (source) & driven pulley
    //
    // Compute theta and phi
    //

    // tan(θ) = (y2 - y1) / (x2 - x1)
    auto theta = atan2( (p2.m_y - p1.m_y), (p2.m_x - p1.m_x) );

    // sin(ϕ) = (r2 - r1) / |p2 - p1|
    auto sinPhi = (r2 - r1) / sep;
    auto phi = asin( sinPhi );

    const double positiveRotationPhase = M_PI / 2;
    const double negativeRotationPhase = 3 * positiveRotationPhase;

    double beta;

    //
    // Compute beta
    //
    if (isPositiveRotation)
        beta = theta + phi + positiveRotationPhase;

    else
        beta = theta - phi + negativeRotationPhase;

    return beta;
}


/**
 * Rock the belts that slot over a driven and a driving pulley
 * @param belt1P1 The starting point of the 1st belt
 * @param belt1P2 The ending point of the 1st belt
 * @param belt2P1 The starting point of the 2nd belt
 * @param belt2P2 The ending point of the 2nd belt
 */
void Pulley::RockBelts(wxP2DD &belt1P1, wxP2DD &belt1P2, wxP2DD &belt2P1, wxP2DD &belt2P2)
{
    auto beltLength = (belt1P2 - belt1P1).GetVectorLength();
    mBeltRockRate = BeltRockBaseRate / beltLength;

    std::vector<wxPoint2DDouble> rockAmounts;

    if ( mSpeed && (int)(mBeltRockRate * GetMachine()->GetMachineTime()) % int(mBeltRockRate) )
    {
        for(int i = 0; i < 4; i++)
        {
            std::uniform_real_distribution<double> distribution(-BeltRockAmount, BeltRockAmount);
            auto rockAmount = wxPoint2DDouble(distribution(mRandom), distribution(mRandom));
            rockAmounts.push_back(rockAmount);
        }
        belt1P1 += rockAmounts[0];
        belt1P2 += rockAmounts[1];
        belt2P1 += rockAmounts[2];
        belt2P2 += rockAmounts[3];
    }
}





