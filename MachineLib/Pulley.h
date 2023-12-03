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

#include "Polygon.h"
#include "Component.h"
#include "RotationSource.h"
#include "RotationSink.h"

/// Maximum amount to rock the belt
/// No, I'm not going to tell you what
/// the units are.
const double BeltRockAmount = 0.01;

/// How quickly to rock the belt in radians per second
/// This is divided by the length to get the actual rate
const double BeltRockBaseRate = M_PI * 1000;

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

    std::shared_ptr<Pulley> mDrivenPulley = nullptr; ///< The pulley being driven by this pulley


public:

    Pulley(double radius);

    double ComputeBeta();
    void Reset() override;
    void Update(double elapsed) override;
    void Drive(std::shared_ptr<Pulley> drivenPulley);
    void Rotate(double rotation, double speed) override;
    void DrawBelts(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawSameRadiiBelts(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawDifferentRadiiBelts(std::shared_ptr<wxGraphicsContext> graphics);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetRotation(double rotation);
    void SetImage(const std::wstring &imagesDir);

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
