/**
 * @file RotationSink.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include "RotationSink.h"
#include "Component.h"

/**
 * Constructor
 */
RotationSink::RotationSink()
{

}

/**
 * Rotate the component that this rotation sink belongs to
 * @param rotation The new rotation
 * @param speed The new speed
 */
void RotationSink::Rotate(double rotation, double speed)
{
    mComponent->Rotate(rotation, speed);
}

/**
 * Set the component that this rotation sink belongs to
 * @param component The new component
 */
void RotationSink::SetComponent(Component *component)
{
    mComponent = component;
}

/**
 * Set the component that this rotation sink belongs to
 * @return The component that this rotation sink belongs to
 */
Component *RotationSink::GetComponent() const
{
    return mComponent;
}

