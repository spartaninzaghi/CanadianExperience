/**
 * @file RotationSource.h
 * @author Mate Narh
 *
 * Class for a rotation source
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

class Component;

/**
 * Class for a rotation source
 */
class RotationSource
{
private:
    /// The rotation sink that this rotation source rotates or drives
    std::shared_ptr<Component> mSink = nullptr;

public:

    RotationSource();

    void AddSink(std::shared_ptr<Component> sink);
    std::shared_ptr<Component> GetSink() const;

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator
    void operator=(const RotationSource &) = delete;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
