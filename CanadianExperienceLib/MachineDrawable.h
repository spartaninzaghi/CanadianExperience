/**
 * @file MachineDrawable.h
 * @author Mate Narh
 *
 * Class for drawing a machine in the Canadian Experience
 *
 * This class is an adapter class which uses the Encapsulation
 * Adapter Pattern to wrap a machine system in a drawable
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include "Drawable.h"
#include <machine-api.h>

/**
 * Class for drawing a machine in the Canadian Experience
 */
class MachineDrawable : public Drawable
{
private:
    /// The start time for the machine
    double mStartTime = 0;

    /// The system for this drawable's machine
    std::shared_ptr<IMachineSystem> mMachineSystem;

public:

    MachineDrawable(const std::wstring &name, const std::wstring &resourcesDir);

    void Run();
    bool HitTest(wxPoint pos) override;
    void XmlSave(wxXmlNode *node) override;
    void XmlLoad(wxXmlNode *node) override;
    void DoDialog(wxWindow *parent) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetPosition(wxPoint pos) override;
    void SetStartTime(double time) override;

    double GetStartTime() const override;
    wxPoint GetPosition() const override;

    /// Default constructor (disabled)
    MachineDrawable() = delete;

    /// Copy constructor (disabled)
    MachineDrawable(const MachineDrawable &) = delete;

    /// Assignment operator
    void operator=(const MachineDrawable &) = delete;

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
