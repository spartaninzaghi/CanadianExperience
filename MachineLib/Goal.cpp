/**
 * @file Goal.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <sstream>
#include "Goal.h"
#include "Machine.h"

/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);

/// Rotation angle for this goal. The goal never turns so
/// this value is zero, 0
const double GoalRotation = 0.0;

/// Scoreboard rectangle scale. This scales the rectangle
/// by x by 98.4% and the rectangle y by 93%
const wxPoint2DDouble rScale = wxPoint2DDouble(0.984f, 0.930f);


/**
 * Constructor
 * @param imagesDir The images directory for this goal
 */
Goal::Goal(const std::wstring &imagesDir) : Component()
{
    mGoalImage.BottomCenteredRectangle(GoalSize);
    mGoalImage.SetImage(imagesDir + GoalImage);

    mPost.BottomCenteredRectangle(PostSize);
    mPost.SetColor(*wxBLUE);

    mGoal.BottomCenteredRectangle(TargetSize);
    mGoal.SetColor(*wxGREEN);
}


/**
 * Handle a contact beginning
 *
 * Increase the score by 2 points when a basket is made
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{
    mScore += 2;
}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contact object
 * @param oldManifold Manifold object
 */
void Goal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);
}

/**
 * Draw the this goal's polygon as a texture mapped image.
 * @param graphics Graphics object to draw on
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //
    // Draw the image of the basketball goal
    //
    mGoalImage.DrawPolygon(graphics,mGoalImagePos.m_x, mGoalImagePos.m_y, GoalRotation);

    //
    // Draw the score text with an inverted scale
    //
    std::wstringstream score;
    if (mScore < 10)
        score << L"0";

    score << mScore;

    auto rect = ScoreboardRectangle;

    auto textX = ScoreboardTextLocation.m_x;
    auto textY = ScoreboardTextLocation.m_y;

    auto scoreX = mGoalImagePos.m_x + textX;
    auto scoreY = mGoalImagePos.m_y + textY;

    wxPen scorePen(*wxBLACK, ScoreboarderLineWidth);
    graphics->SetPen(scorePen);
    graphics->SetBrush(ScoreboardBackgroundColor);
    graphics->DrawRectangle(rScale.m_x * scoreX,
                            rScale.m_y * scoreY,
                            rect.m_width, rect.m_height);

    wxFont font(wxSize(0, ScoreboardFontSize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);

    graphics->SetFont(font, *wxWHITE);

    graphics->PushState();
    graphics->Translate(scoreX,scoreY);
    graphics->Scale(1, -1);
    graphics->DrawText(score.str(), 0, 0);
    graphics->PopState();
}

/**
 * Install this goal into the physics system of its machine
 * @param world The physics system world of this goal's machine
 */
void Goal::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPost.InstallPhysics(world);
    mGoal.InstallPhysics(world);

    GetMachine()->GetContactListener()->Add(mGoal.GetBody(), this);
}

/**
 * Set the position of this goal
 * @param x The new x coordinate
 * @param y The new y coordinate
 */
void Goal::SetPosition(double x, double y)
{
    mGoalImagePos = wxPoint2DDouble(x, y);
    mPost.SetInitialPosition(x + PostPosition.m_x, y + PostPosition.m_y);
    mGoal.SetInitialPosition(x + GoalPosition.m_x, y + GoalPosition.m_y);
}


/**
 * Update the time of this goal
 * @param elapsed The new time
 */
void Goal::Update(double elapsed)
{
}

/**
 * Reset this goal if the current machine frame is 0
 */
void Goal::Reset()
{
    mScore = 0;
}




