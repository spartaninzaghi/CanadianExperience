/**
 * @file MachineSystem.h
 * @author Mate Narh
 *
 * Class for the machine system that controls our machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H

#include "IMachineSystem.h"
#include "Machine.h"

/**
 * Class for the machine system that controls our machines
 */
class MachineSystem : public IMachineSystem
{
private:

    int mFlag = 1;     ///< This machine's flag for DebugDraw visualization
    int mFrame = 0;    ///< The frame that this machine is currently on
    int mNumber = 0;   ///< The machine number of this machine
    int mDuration = 0; ///< The duration of the animation involving this machine

    double mFrameRate = 30;   ///< The frame rate (in number of frames per second)
    double mCurrentTime = 0; ///< The current time for this machine

    std::wstring mResourcesDir;        ///< The resources directory for this machine system
    wxPoint mLocation = wxPoint(0, 0); ///< The location of this machine system
    double mPixelsPerCentimeter = 1.5; ///< How many pixels there are for each CM

    std::shared_ptr<Machine> mMachine = nullptr; ///< The machine that this system controls

public:

    MachineSystem(const std::wstring &resourcesDir);

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetFlag(int flag);
    void SetMachineFrame(int frame) override;
    void SetMachineNumber(int machine) override;
    void SetLocation(wxPoint location) override;
    void SetFrameRate(double rate) override;

    int GetMachineFrame() const;
    double GetFrameRate() const;
    wxPoint GetLocation() override;
    int GetMachineNumber() override;
    double GetMachineTime() override;
    std::wstring GetResourcesDir() const;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
