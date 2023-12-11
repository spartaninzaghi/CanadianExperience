/**
 * @file Picture.cpp
 * @author Charles B. Owen
 * @author Mate Narh
 */
#include "pch.h"
#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>

#include "Picture.h"
#include "PictureObserver.h"
#include "Actor.h"
#include "StartTimeDlg.h"

/**
 * Constructor
*/
Picture::Picture()
{
}


/**
 * Set the current animation time
 *
 * This forces the animation of all
 * objects to the current animation location.
 * @param time The new time.
 */
void Picture::SetAnimationTime(double time)
{
    mTimeline.SetCurrentTime(time);
    UpdateObservers();

    for (auto actor : mActors)
    {
        actor->GetKeyframe();
    }
}

/**
 * Get the current animation time.
 * @return The current animation time
 */
double Picture::GetAnimationTime()
{
    return mTimeline.GetCurrentTime();
}

/**
 * Add an observer to this picture.
 * @param observer The observer to add
 */
void Picture::AddObserver(PictureObserver* observer)
{
    mObservers.push_back(observer);
}

/**
 * Remove an observer from this picture
 * @param observer The observer to remove
 */
void Picture::RemoveObserver(PictureObserver* observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/**
 * Update all observers to indicate the picture has changed.
 */
void Picture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

/**
 * Draw this picture on a device context
 * @param graphics The device context to draw on
 */
void Picture::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto actor : mActors)
    {
        actor->Draw(graphics);
    }


}

/**
 * Add an actor to this drawable.
 * @param actor Actor to add
 */
void Picture::AddActor(std::shared_ptr<Actor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}


/**
* Save the picture animation to a file
* @param filename File to save to.
*/
void Picture::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"anim");
    xmlDoc.SetRoot(root);

    // Save the timeline animation into the XML
    mTimeline.Save(root);

    for (auto actor : mActors)
        actor->Save(root);

    //
    // It is possible to add attributes to the root node here
    //
    //root->AddAttribute(L"something", mSomething);

    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}



/**
* Load a picture animation from a file
* @param filename file to load from
*/
void Picture::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Animation file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    // Load the animation from the XML
    mTimeline.Load(root);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"leftmachine")
        {
            for (auto actor : mActors)
            {
                if (actor->GetName() == L"LeftMachine")
                    actor->Load(child);
            }
        }
        else if (name == L"rightmachine")
        {
            for (auto actor : mActors)
            {
                if (actor->GetName() == L"RightMachine")
                    actor->Load(child);
            }
        }
    }

    //
    // It is possible to load attributes from the root node here
    //
    // mSomething = root->GetAttribute(L"something", L"default");

    SetAnimationTime(0);
    UpdateObservers();
}

/**
 * Set the parent wxFrame for this picture
 * @param parent The new parent
 */
void Picture::SetParent(wxFrame *parent)
{
    mParent = parent;
}

/**
 * Edit the machine on the left of the window
 */
void Picture::EditLeftMachineNumber()
{
    for (auto actor : mActors)
        if (actor->GetName() == L"LeftMachine")
            actor->DoDialog(mParent);
}

/**
 * Edit the machine on the right of the window
 */
void Picture::EditRightMachineNumber()
{
    for (auto actor : mActors)
        if(actor->GetName() == L"RightMachine")
            actor->DoDialog(mParent);
}

/**
 * Edit the start time of the machine on the left of the screen
 */
void Picture::EditLeftMachineStartTime()
{
    for (auto actor : mActors)
    {
        if(actor->GetName() == L"LeftMachine")
        {
            StartTimeDlg dlg(mParent, actor->GetRoot());
            if(dlg.ShowModal() == wxID_OK)
                UpdateObservers();
        }
    }
}

/**
 * Edit the start time of the machine on the right of the screen
 */
void Picture::EditRightMachineStartTime()
{
    for (auto actor : mActors)
    {
        if(actor->GetName() == L"RightMachine")
        {
            StartTimeDlg dlg(mParent, actor->GetRoot());
            if(dlg.ShowModal() == wxID_OK)
                UpdateObservers();
        }
    }
}