/**
 * @file Goal.h
 * @author Mate Narh
 *
 * Class for a basketball goal in a machine
 *
 * A basketball goal comprises a goal image, a post or backboard and
 * a goal object "within" the basket that can detect contact for a
 * made basket. The scoreboard is just a rectangle with no physics.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H

#include <b2_contact.h>
#include <b2_world_callbacks.h>
#include "Component.h"
#include "PhysicsPolygon.h"


/**
 * Class for a basketball goal in a machine
 */
class Goal : public Component, public b2ContactListener
{
private:
    /// The current score for this basketball goal
    int mScore = 0;

    /// Where the goal image displays
    wxPoint2DDouble mGoalImagePos = wxPoint2DDouble(0, 0);

    /// The polygon object for the goal image
    cse335::Polygon mGoalImage;

    /// Physics polygon for the backboard/post
    cse335::PhysicsPolygon mPost;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mGoal;

public:

    Goal(const std::wstring &imagesDir);

    void Reset() override;
    void Update(double elapsed) override;
    void BeginContact(b2Contact *contact);
    void SetPosition(double x, double y) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void InstallPhysics(std::shared_ptr<b2World> world) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);

    /// Default constructor (disabled)
    Goal() = delete;
    
    /// Copy constructor (disabled)
    Goal(const Goal &) = delete;
    
    /// Assignment operator
    void operator=(const Goal &) = delete;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
