/**
 * @file Machine.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include <b2_math.h>
#include <b2_world.h>
#include "Machine.h"
#include "Component.h"
#include "MachineSystem.h"
#include "DebugDraw.h"

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * Constructor
 * @param number The machine number of this machine
 */
Machine::Machine(int number) : mNumber(number)
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
}

/**
 * Add a component to this machine
 * @param component The component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetMachine(this);
}

/**
 * Draw this component
 * @param graphics The graphics context object to draw on
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto component : mComponents)
    {
        component->Draw(graphics);
    }
}

/**
 * Update the animation of this machine by advancing it or backtracking it in time
 * @param elapsed The new time of this machine in seconds
 */
void Machine::Update(double elapsed)
{
    mCurrentTime += elapsed;

    // Call Update on all of our components so they can advance in time
    for (auto component : mComponents)
    {
        component->Update(elapsed);
    }

    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * Resets the physics world of this machine by
 *
 * 1. Creating a new b2World object
 * 2. Creating a new ContactListener object and
 * 3. Installing each component into the physics system
 */
void Machine::Reset()
{
    //
    // 1 Create a new b2World object
    //
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    //
    // 2 Create and install a new contact filter object
    //
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    //
    // 3 Iterate over all components of this machine and install them
    // into the physics system
    //
    for (auto component : mComponents)
    {
        component->Reset();
        component->InstallPhysics(mWorld);
    }
}

/**
 * Set the machine system for this machine
 * @param machineSystem The new machine system
 */
void Machine::SetMachineSystem(MachineSystem *machineSystem)
{
    mMachineSystem = machineSystem;
}

/**
 * Get the machine system that controls this machine
 * @return The machine system that controls this machine
 */
MachineSystem *Machine::GetMachineSystem() const
{
    return mMachineSystem;
}

/**
 * Get the contact listener for this machine's physics world
 * @return The contact listener for this machine's physics world
 */
std::shared_ptr<ContactListener> Machine::GetContactListener() const
{
    return mContactListener;
}


/**
 * Get the current time of this machine
 * @return The current time of this machine
 */
double Machine::GetMachineTime() const
{
    return (double)mFrame/(double)mFrameRate;
}

/**
 * Get the physics system of this machine
 * @return The physics system of this machine
 */
std::shared_ptr<b2World> Machine::GetWorld() const
{
    return mWorld;
}

/**
 * Set the location of this machine
 * @param location The new location
 */
void Machine::SetLocation(wxPoint location)
{
    mLocation = location;
}

/**
 * Get the location of this machine
 * @return The location of this machine
 */
wxPoint Machine::GetLocation() const
{
    return mLocation;
}

/**
 * Set the number of this machine
 * @param number The new number
 */
void Machine::SetNumber(int number)
{
    mNumber = number;
}

/**
 * Get the number of this machine
 * @return The number of this machine
 */
int Machine::GetNumber() const
{
    return mNumber;
}

/**
 * Set the frame that this machine is on
 * @param frame The new frame
 */
void Machine::SetMachineFrame(int frame)
{
    mFrame = frame;
}

/**
 * Get the current frame that this machine is on
 * @return The frame that this machine is currently on
 */
int Machine::GetMachineFrame() const
{
    return mFrame;
}

/**
 * Set the frame rate of this machine
 * @param rate The new frame rate in frames per second
 */
void Machine::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
 * Get the frame rate of this machine
 * @return The frame that this machine is currently on
 */
double Machine::GetFrameRate() const
{
    return mFrameRate;
}







