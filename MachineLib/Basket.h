/**
 * @file Basket.h
 * @author Mate Narh
 *
 * Class for a basket.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BASKET_H
#define CANADIANEXPERIENCE_MACHINELIB_BASKET_H

#include <b2_contact.h>
#include <b2_world_callbacks.h>
#include "Component.h"
#include "Polygon.h"
#include "PhysicsPolygon.h"

/**
 * Class for a basket
 */
class Basket : public Component, public b2ContactListener
{
private:

    cse335::Polygon mBasket;           ///< The polygon for the basket
    cse335::PhysicsPolygon mBase;      ///< The base of the basket
    cse335::PhysicsPolygon mLeftSide;  ///< The Left side of the basket
    cse335::PhysicsPolygon mRightSide; ///< The right side of the basket

    double mContactDuration = 0;       ///< How long a ball has been in this basket
    bool mOccupied = false;            ///< Is a ball currently in this basket

public:

    Basket(const std::wstring &imagesDir);

    void Reset() override;
    void BeginContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void InstallPhysics(std::shared_ptr<b2World> world) override;
    void SetPosition(double x, double y) override;
    void Update(double elapsed) override;

    /// Default constructor (disabled)
    Basket() = delete;

    /// Copy constructor (disabled)
    Basket(const Basket &) = delete;

    /// Assignment operator
    void operator=(const Basket &) = delete;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BASKET_H
