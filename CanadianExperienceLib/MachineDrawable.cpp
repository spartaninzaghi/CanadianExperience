/**
 * @file MachineDrawable.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <machine-api.h>

#include "MachineDrawable.h"
#include "Actor.h"
#include "Picture.h"

/**
 * Constructor
 * @param name The machine name
 * @param resourcesDir The resources directory for the machine
 */
MachineDrawable::MachineDrawable(const std::wstring &name, const std::wstring &resourcesDir) : Drawable(name)
{
    MachineSystemFactory factory(resourcesDir);
    mMachineSystem = factory.CreateMachineSystem();
}


/**
 * Draw the machine system encapsulated in this drawable
 * @param graphics The graphics context object to draw on
 */
void MachineDrawable::Draw(std::shared_ptr <wxGraphicsContext> graphics)
{
    if (mRunning)
        Run();

    double scale = 0.70f;

    graphics->PushState();
    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    graphics->Scale(scale, scale);
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);
    mMachineSystem->SetLocation(wxPoint(0, 0));
    mMachineSystem->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Test to see if we have been clicked on by the mouse
 * @param pos Position to test
 * @return true if clicked on
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
    return false;
}

/**
 * Set the start time for the machine system encapsulated in this drawable
 * @param time The new start time
 */
void MachineDrawable::SetStartTime(double time)
{
    mStartTime = time;
}

/**
 * Get the start time for the machine system encapsulated in this drawable
 * @return The start time for the machine system encapsulated in this drawable
 */
double MachineDrawable::GetStartTime() const
{
    return mStartTime;
}

/**
 * Display the machine selection dialog box
 * @param parent Parent window for the dialog box
 */
void MachineDrawable::DoDialog(wxWindow* parent)
{
    MachineDialog machineDialog(parent, mMachineSystem);
    if (machineDialog.ShowModal() == wxID_OK)
    {
        GetActor()->GetPicture()->UpdateObservers();
    }
}

/**
 * Set the position of the machine system encapsulated in this drawable
 * @param pos The new position
 */
void MachineDrawable::SetPosition(wxPoint pos)
{
    mMachineSystem->SetLocation(pos);
}

/**
 * Get the position of the machine system encapsulated in this drawable
 * @return The position of the machine system encapsulated in this drawable
 */
wxPoint MachineDrawable::GetPosition() const
{
    return mMachineSystem->GetLocation();
}

/**
 * Make the machine encapsulated in this drawable run at start
 */
void MachineDrawable::Wake()
{
    mRunning = true;
}

/**
 * Make the machine encapsulated in this drawable inactive
 */
void MachineDrawable::Sleep()
{
    mRunning = false;
}

/**
 * Make the machine encapsulated in this drawable run in sync with
 * the Canadian Experience
 */
void MachineDrawable::Run()
{
    auto frame = GetActor()->GetPicture()->GetTimeline()->GetCurrentFrame();
    auto frameRate = GetActor()->GetPicture()->GetTimeline()->GetFrameRate();

    mMachineSystem->SetFrameRate(frameRate);
    mMachineSystem->SetMachineFrame(frame);

}
