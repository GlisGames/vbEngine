#include "vbContactListener.h"
#include "vbPhysicsObject.h"

void vbContactListener::AddToList(vbPhysicsObject* obj)
{
	this->list.push_back(obj);
	obj->phys_enabled = TRUE;
}

void vbContactListener::BeginContact(b2Contact* contact)
{
	for (vbPhysicsObject* &o : this->list)
	{
		if ((o->phys_enabled && contact->GetFixtureA()->GetBody() == o->body) || ((o->phys_enabled && contact->GetFixtureB()->GetBody() == o->body)))
		{
			//CALL the begincontact function
			o->BeginContact(contact);
		}
	}
	/*pGame->ball->BeginContact(contact);
	for (int i = 0; i < pGame->map->vec_Bumpers.size(); i++)
	{
		pGame->map->vec_Bumpers[i]->BeginContact(contact);
	}*/
}

void vbContactListener::EndContact(b2Contact* contact)
{
	for (vbPhysicsObject*& o : this->list)
	{
		if ((o->phys_enabled && contact->GetFixtureA()->GetBody() == o->body) || ((o->phys_enabled && contact->GetFixtureB()->GetBody() == o->body)))
		{
			//CALL the endcontact function
			o->EndContact(contact);
		}
	}
	/*pGame->ball->EndContact(contact);
	for (int i = 0; i < pGame->map->vec_Bumpers.size(); i++)
	{
		pGame->map->vec_Bumpers[i]->EndContact(contact);
	}*/
}

