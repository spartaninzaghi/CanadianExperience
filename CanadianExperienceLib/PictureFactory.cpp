/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    //
    // 1 Create the background and add it
    //
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    //
    // 2A Create Left Machine and Add It
    //
    auto leftMachineActor = std::make_shared<Actor>(L"LeftMachine");
    leftMachineActor->SetPosition(wxPoint(350,420));
    auto leftMachine = std::make_shared<MachineDrawable>(L"LeftMachine", resourcesDir);
    leftMachine->SetPosition(leftMachineActor->GetPosition());
    leftMachineActor->AddDrawable(leftMachine);
    leftMachineActor->SetRoot(leftMachine);
    picture->AddActor(leftMachineActor);

    //
    // 2B Create Right Machine and Add It
    //
    auto rightMachineActor = std::make_shared<Actor>(L"RightMachine");
    rightMachineActor->SetPosition(wxPoint(1150,420));
    auto rightMachine = std::make_shared<MachineDrawable>(L"RightMachine", resourcesDir);
    rightMachine->SetPosition(rightMachineActor->GetPosition());
    rightMachineActor->AddDrawable(rightMachine);
    rightMachineActor->SetRoot(rightMachine);
    picture->AddActor(rightMachineActor);

    //
    // 3 Create and add Harold
    //
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 600));
    picture->AddActor(harold);

    //
    // 4 Create and add Sparty
    //
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    // This is where Sparty will start out.
    sparty->SetPosition(wxPoint(550, 620));
    picture->AddActor(sparty);


    return picture;
}

