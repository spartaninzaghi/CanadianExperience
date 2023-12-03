/**
 * @file ContactListener.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include <b2_contact.h>

#include "ContactListener.h"

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void ContactListener::BeginContact(b2Contact *contact)
{
    b2ContactListener* listener = nullptr;
    if(ShouldDispatch(contact, 1, listener))
    {
        listener->BeginContact(contact);
    }

    if(ShouldDispatch(contact, 2, listener))
    {
        listener->BeginContact(contact);
    }
}

/**
 * This function is called before the contact occurs
 * @param contact Contact object
 * @param oldManifold A manifold object
 */
void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    b2ContactListener* listener = nullptr;
    if(ShouldDispatch(contact, 1, listener))
    {
        listener->PreSolve(contact, oldManifold);
    }

    if(ShouldDispatch(contact, 2, listener))
    {
        listener->PreSolve(contact, oldManifold);
    }
}

/**
 * Should a contact be dispatched to an installed listener for some body?
 *
 * We have installed listeners in mDispatch for bodies. This tests to see
 * if either of the two bodies involved  in the collision are in the
 * mDispatch map. If so, the listener reference value is set and a
 * true value is returned.
 *
 * @param contact Contact to test
 * @param body Which body for the contact (1 or 2?)
 * @param listener Where to put the listener to call the function on
 * @return true if we should dispatch this contact
 */
 bool ContactListener::ShouldDispatch(b2Contact *contact, int body, b2ContactListener* &listener)
{
    b2Body* bodyD = body == 1 ? contact->GetFixtureA()->GetBody() :
                               contact->GetFixtureB()->GetBody();

    auto dispatchA = mDispatch.find(bodyD);
    if(dispatchA != mDispatch.end())
    {
       listener = dispatchA->second;
       return true;
    }

    return false;
}


