/**
 * @file ContactListener.h
 * @author Charles Owen
 *
 * A contact filter allows for testing for things
 * that should happen based on different contacts.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONTACTLISTENER_H
#define CANADIANEXPERIENCE_MACHINELIB_CONTACTLISTENER_H

#include <map>
#include <b2_world_callbacks.h>

/**
 * A contact filter allows for testing for things
 * that should happen based on different contacts.
 */
class ContactListener : public b2ContactListener
{
private:
    /**
     * Keep track of bodies we want to dispatch
     * the contact listener to.
     */
    std::map<b2Body*, b2ContactListener*> mDispatch;

    bool ShouldDispatch(b2Contact *contact, int body, b2ContactListener* &listener);

public:
    /**
     * Add a dispatched listener for some body.
     * @param body Body to listen for
     * @param listener Listener to call
     */
    void Add(b2Body* body, b2ContactListener* listener) {mDispatch[body] = listener;}

    void BeginContact(b2Contact* contact) override;

    /**
     * Handle the end of a contact situation
     * @param contact Contact object
     */
    void EndContact(b2Contact* contact) override
    { /* handle end event */ }

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    /**
     * Called after the solve has been computed, but before the contact is reported
     * @param contact Contact object
     * @param impulse Impulse related to the contact
     */
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
    { /* handle post-solve event */ }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONTACTLISTENER_H
