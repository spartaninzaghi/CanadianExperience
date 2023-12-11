/**
 * @file HamsterAndConveyorFactory.h
 * @author Charles Owen
 *
 * Factory that creates a Hamster to drive and a
 * conveyor belt connected by two pulleys.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H

class Machine;
class Hamster;
class Conveyor;
class Body;

/**
 * Factory that creates a Hamster to drive and a
 * conveyor belt connected by two pulleys.
 *
 * Since the example machine has three of these combinations we
 * use this factory that creates a hamster, conveyor, and the
 * pulley combinations to drive the conveyor.
 *
 * Example usage:
 *
 * \code
    HamsterAndConveyorFactory hamsterAndConveyorFactory(machine, mImagesDir);

    hamsterAndConveyorFactory.Create(wxPoint2DDouble(240, 0), wxPoint2DDouble(100, 90));
    hamsterAndConveyorFactory.AddBall(40);
    auto hamster1 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor1 = hamsterAndConveyorFactory.GetConveyor();
    hamster1->SetInitialSpeed(-1);
 * \endcode
 */
class HamsterAndConveyorFactory
{
private:
    /// The machine we are adding these components to
    std::shared_ptr<Machine> mMachine;

    /// The directory for the images
    std::wstring mImagesDir;

    /// The hamster wheel
    std::shared_ptr<Hamster> mHamster;

    /// The conveyor
    std::shared_ptr<Conveyor> mConveyor;

    /// The radius of the second pulley
    double mPulley2Raduis = 10;

    /// Should this pulley set-up have flapping belts
    bool mRock = false;

public:

    /**
     * Constructor
     * @param machine The Machine to add the components to
     * @param imagesDir Directory containing the images
     * @param pulley2Radius Radius of second pulley
     * @param rock Flap pulley belts if true
     */
    HamsterAndConveyorFactory(std::shared_ptr<Machine> machine, std::wstring imagesDir,
                              double pulley2Radius=10, bool rock=false) :
        mMachine(machine), mImagesDir(imagesDir), mPulley2Raduis(pulley2Radius), mRock(rock) {}

    /// Default constructor (disabled)
    HamsterAndConveyorFactory() = delete;

    /// Copy constructor (disabled)
    HamsterAndConveyorFactory(const HamsterAndConveyorFactory &) = delete;

    /// Assignment operator
    void operator=(const HamsterAndConveyorFactory &) = delete;

    void Create(wxPoint2DDouble hamsterPosition, wxPoint2DDouble conveyorPosition);

    std::shared_ptr<Body> AddBall(double placement);

    /**
     * Get the constructed Hamster object
     * @return Hamster object
     */
    std::shared_ptr<Hamster> GetHamster() {return mHamster;}

    /**
     * Get the constructed Conveyor object
     * @return Conveyor object
     */
    std::shared_ptr<Conveyor> GetConveyor() {return mConveyor;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
