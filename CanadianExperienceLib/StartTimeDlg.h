/**
 * @file StartTimeDlg.h
 * @author Mate Narh
 *
 * Start Time Dialog Box
 */

#ifndef CANADIANEXPERIENCE_CANADIANXP_CANADIANEXPERIENCELIB_STARTTIMEDLG_H
#define CANADIANEXPERIENCE_CANADIANXP_CANADIANEXPERIENCELIB_STARTTIMEDLG_H

class Drawable;

/**
 * Start Time Dialog Box
 */
class StartTimeDlg final : public wxDialog
{
private:
    void OnOK(wxCommandEvent& event);

    /// The pointer to the drawable whose start time to edit
    std::shared_ptr<Drawable> mDrawable;

    /// The entered start time for the relevant drawable
    double mStartTime = 0;

public:

    StartTimeDlg(wxWindow *parent, std::shared_ptr<Drawable> drawable);

};
#endif //CANADIANEXPERIENCE_CANADIANXP_CANADIANEXPERIENCELIB_STARTTIMEDLG_H
