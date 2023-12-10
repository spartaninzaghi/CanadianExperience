/**
 * @file Basket.cpp
 * @author Mate Narh
 */

#include "pch.h"
#include "Basket.h"

/// Image to draw for the basket
const std::wstring BasketImage = L"/basket.png";

/// The size of the basket in centimeters
const double BasketSize = 40;

/// The size of the basket base in centimeters
const auto BaseSize = wxSize(20, 1);

/// The size of a side of the basket in centimeters
const auto SideSize = wxSize(5, 20);

/// Delay between when the ball hits the basket
/// and when it is shot out
const double BasketDelay = 1.0;

/// The direction we shoot the ball out of the basket
const wxPoint2DDouble BasketShot = wxPoint2DDouble(1, 7);

/// The impulse with which the ball is shot out of the basket
const b2Vec2 BasketImpulse = 0.0425f * b2Vec2(1, 7);


/**
 * Constructor
 * @param imagesDir The image directory for this basket
 */
Basket::Basket(const std::wstring &imagesDir) : Component()
{
    mBasket.CenteredSquare(BasketSize);
    mBasket.SetImage(imagesDir + BasketImage);

    mBase.BottomCenteredRectangle(BaseSize);
    mBase.SetColor(*wxGREEN);

    mLeftSide.BottomCenteredRectangle(SideSize);
    mLeftSide.SetColor(*wxGREEN);

    mRightSide.BottomCenteredRectangle(SideSize);
    mRightSide.SetColor(*wxGREEN);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Basket::BeginContact(b2Contact *contact)
{
    mOccupied = true;
}

/**
 * Handle before the solution of a contact with the
 * base and sides of the basket
 * @param contact Contact object
 * @param oldManifold Manifold object
 */
void Basket::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{

}

/**
 * Update the time of this basket
 * @param elapsed The new time
 */
void Basket::Update(double elapsed)
{
    if (mOccupied)
    {
        mContactDuration += elapsed;

        if(mContactDuration >= BasketDelay)
        {
            auto ball = mBase.GetBody()->GetContactList()->contact->GetFixtureB()->GetBody();

            ball->ApplyLinearImpulseToCenter(BasketImpulse, true);

            mOccupied = false;
            mContactDuration = 0;
        }
    }
}

/**
 * Draw the this basket's polygon as a texture mapped image.
 * @param graphics
 */
void Basket::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //
    // Draw the image of the basket
    //
    auto rotation = 0; // Rotation is 0 because the basket doesn't turn
    mBasket.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y, rotation);
}

/**
 * Install this basket into the physiscs system world of its machine
 * @param world The physics system world of this basket's machine
 */
void Basket::InstallPhysics(std::shared_ptr<b2World> world)
{
    mBase.InstallPhysics(world);
    mLeftSide.InstallPhysics(world);
    mRightSide.InstallPhysics(world);

    GetMachine()->GetContactListener()->Add(mBase.GetBody(), this);
}

/**
 * Set the position of this basket
 * @param x The new x coordinate
 * @param y The new y coordinate
 */
void Basket::SetPosition(double x, double y)
{
    auto offset1 = 0.4 * BasketSize;
    auto offset2 = 5;

    mPosition = wxPoint2DDouble(x, y);

    mBase.SetInitialPosition(x, y - offset1);
    mLeftSide.SetInitialPosition(x - offset1, y - offset2);
    mRightSide.SetInitialPosition(x + offset1, y - offset2);
}

/**
 * Reset this basket when the current machine frame is 0
 */
void Basket::Reset()
{
    mOccupied = false;
    mContactDuration = 0;
}




