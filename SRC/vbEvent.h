#ifndef VBEVENT_H
#define VBEVENT_H
#include <functional>
#include <chrono>

template<typename Sender>
class vbEvent;

template<class Sender>
class vbEventListener
{
private:
public:
	typedef std::function<void(Sender)> t_callback;
	t_callback callback = NULL;
	vbEvent<Sender>* owner = NULL;
	vbEventListener(t_callback f = NULL) { setCallback(f); }

	~vbEventListener()
	{
		owner->unsubscribe(this);
	}

	void setCallback(t_callback f)
	{
		this->callback = f;
	}

	BOOL enabled = TRUE;
};


template<typename Sender>
class vbEvent 
{
private:
	list<vbEventListener<Sender>*> listeners;
public:
	BOOL enabled = TRUE;

	vbEventListener<Sender>* subscribe(std::function<void(Sender)> f)
	{
		auto ret = new vbEventListener<vbButton*>(f);
		ret->owner = this;
		listeners.push_back(ret);
		return ret;
	}

	vbEventListener<Sender>* subscribe(vbEventListener<Sender>* listener)
	{
		listener->owner = this;
		listeners.push_back(listener);
		return listener;
	}

	BOOL unsubscribe(vbEventListener<Sender>* del)
	{
		auto found = std::find(listeners.begin(), listeners.end(), del);
		if (found != listeners.end())
		{
			listeners.remove(del);
			return TRUE;
		}
		return FALSE;
	}

	void trigger(Sender param)
	{
		if (!enabled)
			return;

		for (vbEventListener<Sender>* l : listeners)
		{
			if(l->enabled && l->callback != NULL) 
				l->callback(param);
		}
	};

};

#endif // !VBTIMER_H
