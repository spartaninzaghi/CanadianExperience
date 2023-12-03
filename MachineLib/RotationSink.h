/**
 * @file RotationSink.h
 * @author Mate Narh
 *
 * Class for a rotation sink
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H

class Component;

/**
 * Class for a rotation sink
 */
class RotationSink
{
private:
    /// The component that this sink belongs to
    Component *mComponent = nullptr;

public:

    RotationSink();

    void Rotate(double rotation, double speed);
    void SetComponent(Component* component);
    Component *GetComponent() const;
    
    /// Copy constructor (disabled)
    RotationSink(const RotationSink &) = delete;
    
    /// Assignment operator
    void operator=(const RotationSink &) = delete;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
