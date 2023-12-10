/**
 * @file Pulley.h
 * @author Mate Narh
 *
 * Class for a pulley
 *
 * A pulley can be both a source or driver of rotation
 * and a sink or recipient of rotation
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include <random>
#include "Polygon.h"
#include "Component.h"
#include "RotationSource.h"
#include "RotationSink.h"

/**
 * Class for a pulley
 */
class Pulley : public Component
{
private:

    double mSpeed = 0;       ///< The translational speed of this pulley
    double mRadius = 0;      ///< The radius of this pulley
    double mRotation = 0;    ///< The rotation angle for this pulley
    double mPulleyRatio = 0; ///< Radius of Driven Pulley / Radius of Driving Pulley

    RotationSink mSink;      ///< Rotation sink for this pulley (if it is "driven")
    RotationSource mSource;  ///< Rotation source for this pulley (if it is "driving")
    cse335::Polygon mPulley; ///< The polygon for this pulley

    wxPoint2DDouble mPosition = wxPoint2DDouble(0, 0); ///< The location of this pulley (relative to its center)
    std::shared_ptr<Pulley> mDrivenPulley = nullptr;   ///< The sink pulley being driven by this source pulley

    std::mt19937 mRandom;     ///< Random number generator for belt rock amount
    double mBeltRockRate = 1; ///< How quickly to rock pulley belts in cm/s

public:

    Pulley(double radius);

    double ComputeBeta();
    void Reset() override;
    void Update(double elapsed) override;
    void Drive(std::shared_ptr<Pulley> drivenPulley);
    void Rotate(double rotation, double speed) override;
    void DrawBelts(std::shared_ptr<wxGraphicsContext> graphics);
    void RockBelts(wxPoint2DDouble& belt1P1, wxPoint2DDouble& belt1P2,
                   wxPoint2DDouble& belt2P1, wxPoint2DDouble& belt2P2);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetRotation(double rotation);
    void SetImage(const std::wstring &imagesDir);
    void SetPosition(double x, double y) override;
    void SetPosition(wxPoint2DDouble position) override;

    RotationSink *GetSink();
    double GetRotation() const;
    RotationSource *GetSource();
    std::shared_ptr<Pulley> GetDrivenPulley() const;


    /// Default constructor (disabled)
    Pulley() = delete;

    /// Copy constructor (disabled)
    Pulley(const Pulley &) = delete;

    /// Assignment operator
    void operator=(const Pulley &) = delete;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
