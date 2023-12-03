/**
 * @file Curtain.h
 * @author Mate
 *
 * Class for a curtain that opens to reveal the innards of a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H
#define CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H

#include "Component.h"
#include "Polygon.h"

/**
 * Class for a curtain
 */
class Curtain : public Component
{
private:

    cse335::Polygon mRod;          ///< Polygon for the curtain rod
    cse335::Polygon mLeftCurtain;  ///< Polygon for the left curtain
    cse335::Polygon mRightCurtain; ///< Polygon for the right curtain

    wxPoint2DDouble mRodPos = wxPoint2DDouble(0, 0);   ///< Location of the curtain rod
    wxPoint2DDouble mLeftPos = wxPoint2DDouble(0, 0);  ///< Location of the left curtain
    wxPoint2DDouble mRightPos = wxPoint2DDouble(0, 0); ///< Location of the right curtain

    double mXScale = 1;       ///< Horizontal scaling for the left & right curtain
    double mPreviousTime = 0; ///< The previous time in the machine

    /// The possible states of the curtains
    enum class State {Stationary, Open, Close};

    /// The current state of the curtains
    State mState = State::Stationary;

    /// The possible directions, in time, of the system slider
    enum class Direction {Forward, Reverse};

    /// The current direction, in time, of the system slider
    Direction mDirection = Direction::Forward;

public:

    Curtain(const std::wstring &imagesDir);

    void Reset() override;
    void ResetCurtainState();
    void Update(double elapsed) override;
    void SetPosition(double x, double y) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawCurtains(std::shared_ptr<wxGraphicsContext> graphics);

    /// Copy constructor (disabled)
    Curtain(const Curtain &) = delete;

    /// Assignment operator
    void operator=(const Curtain &) = delete;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H
