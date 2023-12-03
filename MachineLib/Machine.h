/**
 * @file Machine.h
 * @author Mate
 *
 * Base class for a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

#include "PhysicsPolygon.h"
#include "ContactListener.h"

/// Forward references
class Component;
class MachineSystem;

/**
 * Base class for a machine
 */
class Machine
{
private:

    int mFrame = 0;                    ///< The frame that this machine is on
    int mNumber = 0;                   ///< Machine # number for this machine
    double mFrameRate = 30;             ///< The frame rate of this machine
    double mCurrentTime = 0;           ///< The current time of this machine
    wxPoint mLocation = wxPoint(0, 0); ///< The location of this machine
    std::shared_ptr<b2World> mWorld;   ///< The box2D physics system world for this machine

    MachineSystem *mMachineSystem = nullptr; ///< Machine system controlling this machine

    std::shared_ptr<ContactListener> mContactListener;   ///< This machine's installed contact filter
    std::vector<std::shared_ptr<Component>> mComponents; ///< Collection this machine's components


public:

    Machine(int number);

    void Reset();
    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void AddComponent(std::shared_ptr<Component> component);

    void SetNumber(int number);
    void SetFrameRate(double rate);
    void SetMachineFrame(int frame);
    void SetLocation(wxPoint location);
    void SetMachineSystem(MachineSystem *machineSystem);

    int GetNumber() const;
    wxPoint GetLocation() const;
    int GetMachineFrame() const;
    double GetFrameRate() const;
    double GetMachineTime() const;
    MachineSystem *GetMachineSystem() const;
    std::shared_ptr<b2World> GetWorld() const;
    std::shared_ptr<ContactListener> GetContactListener() const;


    /// Default constructor (disabled)
    Machine() = delete;

    /// Copy constructor (disabled)
    Machine(const Machine &) = delete;

    /// Assignment operator
    void operator=(const Machine &) = delete;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
