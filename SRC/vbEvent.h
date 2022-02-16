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
	vbEvent<Sender>* owner = NULL;
public:
	typedef std::function<void(Sender)> t_callback;

	/// <summary>
	/// function that will be called when the event is triggered
	/// </summary>
	t_callback callback = NULL;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="f">Event callback function</param>
	vbEventListener(t_callback f = NULL) { setCallback(f); }

	~vbEventListener()
	{
		owner->unsubscribe(this);
	}

	/// <summary>
	/// Set the event callback
	/// </summary>
	/// <param name="f">Event callback function</param>
	void setCallback(t_callback f)
	{
		this->callback = f;
	}

	BOOL enabled = TRUE;
};

/// <summary>
/// Example of use
/// 	auto listener = yourEvent.subscribe(
///			[=](yourParams p){
///		 		p->aBoolVariable = FALSE;
///		});
/// Remember to deallocate the listener and to unsubscribe the even if the callback goes out of scope.
/// </summary>
/// <typeparam name="Sender"></typeparam>
template<typename Sender>
class vbEvent 
{
private:
	list<vbEventListener<Sender>*> listeners;
public:
	BOOL enabled = TRUE;

	/// <summary>
	/// Given a function allocates a new listener.
	/// WARNING. The event won't handle the memory, leak will occur should you forget to free the returned pointer
	/// </summary>
	/// <param name="f">Event callback function</param>
	/// <returns>Pointer to the newely allocated listener</returns>
	vbEventListener<Sender>* subscribe(std::function<void(Sender)> f)
	{
		auto ret = new vbEventListener<vbButton*>(f);
		ret->owner = this;
		listeners.push_back(ret);
		return ret;
	}

	/// <summary>
	/// Insert a subscriber to the event sub list. The event will call the callback function whenever the event triggers
	/// WARNING. The event won't check the sanity of any lister's callback, SEG FAULT will occur should you deallocate the function pointer without unsubcribing or destroying the listener
	/// </summary>
	/// <param name="listener">Pointer to a listener to be subscribed</param>
	/// <returns>The same pointer passed as parameter, in case you're allocating a new listener inside the brackets</returns>
	vbEventListener<Sender>* subscribe(vbEventListener<Sender>* listener)
	{
		listener->owner = this;
		listeners.push_back(listener);
		return listener;
	}

	/// <summary>
	/// Remove a listener from the subscribers list
	/// </summary>
	/// <param name="del">The listener to be removed</param>
	/// <returns>TRUE if the listener was on the list and has been removed</returns>
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

	/// <summary>
	/// Will call all the subscribers callbacks
	/// </summary>
	/// <param name="param">Parameter to pass to the subs</param>
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
