/**
 * @file Component.h
 * @author Mate
 *
 * Base class for a component of a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include "PhysicsPolygon.h"
#include "ContactListener.h"
#include "Machine.h"

/**
 * Base class for a component of a machine
 */
class Component
{
private:
    /// The machine that this component belongs to
    Machine* mMachine = nullptr;

protected:
    /// Default constructor
    Component() {}

public:
    /// Destructor
    virtual ~Component() = default;

    /**
     * Reset this component
     */
    virtual void Reset() {}

    /**
     * Rotate this component
     * @param rotation The new rotation
     * @param speed The new speed
     */
    virtual void Rotate(double rotation, double speed) {};

    /**
     * Draw this component
     * @param graphics The graphics context object to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Update the time of this component
     * @param elapsed The time elapsed
     */
    virtual void Update(double elapsed) {}

    /**
     * Get the current time of this component
     * @return The current time of this component
     */
    double GetCurrentTime() const { return 0; }

    /**
     * Install this component into the physics system of its machine
     * @param world The physics world to install this component in
     */
    virtual void InstallPhysics(std::shared_ptr<b2World> world) {};

    /**
     * Set the position of this component given an x and y value
     * @param x The new x coordinate in pixels
     * @param y The new y coordinate in pixels
     */
    virtual void SetPosition(double x, double y) {}

    /**
     * Set the position of this component given a point
     * @param position The point position
     */
    virtual void SetPosition(wxPoint2DDouble position) {}

    /**
     * Get the position of this component
     * @return The (x, y) position of this component in pixels
     */
    virtual wxPoint2DDouble GetPosition() const { return wxPoint2DDouble(0, 0); }

    /**
     * Set the machine this component belongs to
     * @param machine The new machine
     */
    void SetMachine(Machine *machine) { mMachine = machine; }

    /**
     * Get the machine this component belongs to
     * @return The machine this component belongs to
     */
    Machine* GetMachine() const { return mMachine; }


    /// Copy constructor (disabled)
    Component(const Component &) = delete;

    /// Assignment operator
    void operator=(const Component &) = delete;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
