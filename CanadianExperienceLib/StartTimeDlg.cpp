/**
 * @file StartTimeDlg.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>

#include "StartTimeDlg.h"
#include "Drawable.h"

/**
 * Constructor
 * @param parent the parent window to display the dialog box in
 * @param machineDrawable the machine drawable whose start time is edited
 */
StartTimeDlg::StartTimeDlg(wxWindow *parent, std::shared_ptr <Drawable> drawable)
    : mDrawable(drawable)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"StartTimeDlg");

    mStartTime = drawable->GetStartTime();

    Bind(wxEVT_BUTTON, &StartTimeDlg::OnOK, this, wxID_OK);

    auto startTimeCtrl = XRCCTRL(*this, "StartTimeDlgStartTime", wxTextCtrl);
    wxFloatingPointValidator<double> startTimeValidator(3, &mStartTime);
    startTimeValidator.SetRange(0, 1000);
    startTimeCtrl->SetValidator(startTimeValidator);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void StartTimeDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mDrawable->SetStartTime(mStartTime);

        EndModal(wxID_OK);
    }
}
