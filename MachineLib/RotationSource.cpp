/**
 * @file RotationSource.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include "RotationSource.h"
#include "Component.h"

/**
 * Constructor
 */
RotationSource::RotationSource()
{

}

/**
 * Assign this rotation source its rotation sink
 * @param sink The new rotation sink
 */
void RotationSource::AddSink(std::shared_ptr<Component> sink)
{
    mSink = sink;
}

/**
 * Get the rotation sink that this rotation source drives
 * @return The rotation sink that this rotation source drives
 */
std::shared_ptr<Component> RotationSource::GetSink() const
{
    return mSink;
}
