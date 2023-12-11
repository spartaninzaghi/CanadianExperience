/**
 * @file HamsterAndConveyorFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "HamsterAndConveyorFactory.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Body.h"
#include "Pulley.h"
#include "Machine.h"

/**
 * Create a hamster that is a conveyor.
 * @param hamsterPosition Where to place the hamster
 * @param conveyorPosition Where to place the conveyor
 */
void HamsterAndConveyorFactory::Create(wxPoint2DDouble hamsterPosition, wxPoint2DDouble conveyorPosition)
{
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    mHamster = hamster;
    hamster->SetPosition(hamsterPosition);
    mMachine->AddComponent(hamster);
    auto hamsterShaft = hamster->GetShaftPosition();

    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    mConveyor = conveyor;
    conveyor->SetPosition(conveyorPosition);
    mMachine->AddComponent(conveyor);
    auto conveyorShaft = conveyor->GetShaftPosition();

    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10, mRock);
    pulley1->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft);
    mMachine->AddComponent(pulley1);

    hamster->GetSource()->AddSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(mPulley2Raduis, mRock);
    pulley2->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(conveyorShaft);
    mMachine->AddComponent(pulley2);

    pulley1->Drive(pulley2);

    pulley2->GetSource()->AddSink(conveyor);
}

/**
 * Add a ball onto the conveyor belt for the just created hamster
 * conveyor belt combination.
 * @param placement Placement left (negative) to right (positive)
 * @return Gall object
 */
std::shared_ptr<Body> HamsterAndConveyorFactory::AddBall(double placement)
{
    // Ball
    auto ball = std::make_shared<Body>();
    ball->Circle(12);
    ball->SetImage(mImagesDir + L"/ball1.png");
    ball->SetInitialPosition(mConveyor->GetPosition() + wxPoint2DDouble(placement, 26));
    ball->SetDynamic();
    ball->SetPhysics(2, 0.5, 0.1);
    mMachine->AddComponent(ball);

    return ball;
}
