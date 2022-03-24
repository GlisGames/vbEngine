#ifndef VBCONTACTLISTENER_H
#define VBCONTACTLISTENER_H

#include <vector>
#include "box2d/box2d.h"
#include "vbPhysicsObject.h"

class vbContactListener : public b2ContactListener
{
public:
    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact);

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact);
    vector<vbPhysicsObject*> list;
    void AddToList(vbPhysicsObject* obj);
};
#endif // !VBCONTACTLISTENER_H
