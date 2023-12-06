/**
 * @file MachineSystem.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <b2_world.h>
#include "MachineSystem.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"
#include "DebugDraw.h"

/**
 * Constructor
 * @param resourcesDir The resources directory for this machine system
 */
MachineSystem::MachineSystem(const std::wstring &resourcesDir)
{
    mResourcesDir = resourcesDir;

    //
    // SetMachineNumber() is more than a setter : it instantiates an
    // actual machine bearing the given machine number
    //
    SetMachineNumber(1);
}

/**
 * Draw the machine at the currently specified location
 * @param graphics Graphics object to render to
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);

    if(mFlag & 1)
    {
        // Draw your machine normally
        // Draw the machine assuming an origin of 0,0
        if (mMachine)
            mMachine->Draw(graphics);
    }

    if(mFlag & 2)
    {
        //
        // Used DebugDraw to visualize machine outlines (good stuff!)
        //
        DebugDraw debugDraw(graphics);
        debugDraw.SetLineWidth(1);
        debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
        mMachine->GetWorld()->SetDebugDraw(&debugDraw);
        mMachine->GetWorld()->DebugDraw();
    }

    graphics->PopState();

}

/**
 * Set the current machine animation frame
 * @param frame Frame number
 */
void MachineSystem::SetMachineFrame(int frame) {

    if(frame < mFrame)
    {
        mFrame = 0;
        mMachine->SetMachineFrame(mFrame);
        mMachine->Reset();
    }

    for( ; mFrame < frame;  mFrame++)
    {
        mMachine->SetMachineFrame(mFrame);
        mMachine->Update(1.0 / mFrameRate);
    }
    mMachine->SetMachineFrame(mFrame);
}

/**
 * Create a machine with the given number
 * @param machine An integer number. Each number makes a different machine
 */
void MachineSystem::SetMachineNumber(int machine)
{
    mNumber = machine;

    // Default to Machine #1
    if (mNumber != 2)
    {
        Machine1Factory machine1Factory(mResourcesDir);
        mMachine = machine1Factory.Create();
        mMachine->SetMachineSystem(this);
        mMachine->Reset(); // otherwise nothing will work because the Physics world isn't reset
    }
    // Select Machine #2 if the machine number is 2
    else
    {
        Machine2Factory machine2Factory(mResourcesDir);
        mMachine = machine2Factory.Create();
        mMachine->SetMachineSystem(this);
        mMachine->Reset();
    }
}

/**
 * Set the position for the root of the machine
 * @param location The x,y location to place the machine
 */
void MachineSystem::SetLocation(wxPoint location)
{
    mLocation = location;
    mMachine->SetLocation(location);
}

/**
 * Get the location of the machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mMachine->GetLocation();
}

/**
 * Get the current machine animation frame
 * @return The current machine animation frame
 */
int MachineSystem::GetMachineFrame() const
{
    return mMachine->GetMachineFrame();
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
    mMachine->SetFrameRate(rate);
}

/**
 * Get the expected frame rate in frames per second
 * @return The expected frame rate in frames per second
 */
double MachineSystem::GetFrameRate() const
{
    return mMachine->GetFrameRate();
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
    return mMachine->GetNumber();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return mMachine->GetMachineTime();
}

/**
 * Get the resources directory for this machine system
 * @return The resources directory for this machine system
 */
std::wstring MachineSystem::GetResourcesDir() const
{
    return mResourcesDir;
}

/**
 * Set the flag from the control panel
 * @param flag Flag to set
 */
void MachineSystem::SetFlag(int flag)
{
    mFlag = flag;
}










