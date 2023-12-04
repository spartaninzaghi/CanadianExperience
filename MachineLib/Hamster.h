/**
 * @file Hamster.h
 * @author Mate Narh
 *
 * Class for a hamster in a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H


#include <b2_world_callbacks.h>
#include "Component.h"
#include "Polygon.h"
#include "PhysicsPolygon.h"
#include "RotationSource.h"

/**
 * Class for a hamster in a machine
 */
class Hamster : public Component, public b2ContactListener
{
private:

    double mSpeed = 1;              ///< The hamster speed (1 clockwise rotation per second default)
    int mFrameRate = 30;             ///< The frame rate for this hamster
    int mHamsterIndex = 0;          ///< The hamster image index (0 default for sleeping hamster)
    double mRotation = 0.0;         ///< The rotation of this hamster

    RotationSource mSource;         ///< The rotation source for this hamster
    wxPoint2DDouble mWheelPosition; ///< The position of the hamster cage

    bool mRunning = false;          ///< Is this hamster running right now ?
    bool mInitiallyRunning = false; ///< Is this hamster running when system starts ?

    cse335::Polygon mWheel;         ///< The wheel po for this hamster
    cse335::PhysicsPolygon mCage;   ///< The cage for this hamster

    /// Order in which we cycle through this hamster's images
    enum class Mode {Advance, Reverse};
    Mode mCycleMode = Mode::Advance;    ///< The cycle mode for this hamster (default is forward)

    std::vector<std::shared_ptr<cse335::Polygon>> mHamsters; ///< Images of orientations for this hamster

public:

    Hamster(const std::wstring &imagesDir);

    void Reset() override;
    void Update(double elapsed) override;
    void BeginContact(b2Contact *contact);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InstallPhysics(std::shared_ptr<b2World> world) override;

    bool IsRunning() const;
    double GetSpeed() const;
    double GetRotation() const;
    RotationSource *GetSource();
    bool IsInitiallyRunning() const;
    wxPoint2DDouble GetShaftPosition() const;

    void SetSpeed(double speed);
    void SetRunning(bool running);
    void SetRotation(double rotation);
    void SetInitiallyRunning(bool running);
    void SetPosition(double x, double y) override;
    void SetPosition(wxPoint2DDouble position) override;


    /// Copy constructor (disabled)
    Hamster(const Hamster &) = delete;

    /// Assignment operator
    void operator=(const Hamster &) = delete;

    void SwitchHamsterImage();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
