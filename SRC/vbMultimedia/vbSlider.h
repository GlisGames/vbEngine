#ifndef VB_SLIDER_H
#define VB_SLIDER_H

#include "vbContainer.h"
#include "basetypes.h"
#include "raylib.h"
#include <functional>
#include <stdexcept>

enum class SliderDirection
{
	LeftToRight,
	RightToLeft,
	BottomToTop,
	TopToBottom
};

class vbSlider: public vbContainer
{
public:
	vbSlider(const Rectangle& boundingArea, const SliderDirection& direct = SliderDirection::LeftToRight, const Color& valueColor = RED, const Color& remainColor = BLUE);
	vbSlider(const Vector2& boundingArea, const SliderDirection& direct, Texture2D* track, Texture2D* fill, Texture2D* handle);
	vbSlider(const vbSlider& slider);
	vbSlider& operator=(const vbSlider& slider);
	virtual ~vbSlider();

	virtual void setup();
	virtual void update();
	virtual void draw();

	const float& max() const;
	const float& max();

	void setMax(const float& max);

	const float& min() const;
	const float& min();

	void setMin(const float& min);

	const float& value() const;
	const float& value();

	void setValue(const float& value);

	const SliderDirection& direct() const;
	SliderDirection& direct();
	
	void setOnValueChangeCallback(const std::function<void(const vbSlider&)>& callback);

	const vbImage* imgTrack() const;
	const vbImage* imgFill() const;
	const vbImage* imgHandle() const;

	//lock to avoid change the vbImage, if you wanna style one of them, just give it a name

	vbImage& imgTrack();
	vbImage& imgFill();
	vbImage& imgHandle();

protected:
	float m_max;
	float m_min;
	float m_value;
	SliderDirection m_direct;
	std::function<void(const vbSlider&)> m_onChangeValueCallback;
	Color m_valueColor;
	Color m_remainColor;
	
	vbImage* m_imgTrack;
	vbImage* m_imgFill;
	vbImage* m_imgHandle;


};

inline const float& vbSlider::max() const
{
	return m_max;
}

inline const float& vbSlider::max()
{
	return static_cast<const vbSlider&>(*this).max();
}

inline const float& vbSlider::min() const
{
	return m_min;
}

inline const float& vbSlider::min()
{
	return static_cast<const vbSlider&>(*this).min();
}

inline const float& vbSlider::value() const
{
	return m_value;
}

inline const float& vbSlider::value()
{
	return static_cast<const vbSlider&>(*this).value();
}

inline const SliderDirection& vbSlider::direct() const
{
	return m_direct;
}

inline SliderDirection& vbSlider::direct()
{
	return const_cast<SliderDirection&>(static_cast<const vbSlider&>(*this).direct());
}

inline void vbSlider::setOnValueChangeCallback(const std::function<void(const vbSlider&)>& callback)
{
	m_onChangeValueCallback = callback;
}

inline const vbImage* vbSlider::imgTrack() const
{
	return m_imgTrack;
}

inline const vbImage* vbSlider::imgFill() const
{
	return m_imgFill;
}

inline const vbImage* vbSlider::imgHandle() const
{
	return m_imgHandle;
}

inline vbImage& vbSlider::imgTrack()
{
	return *m_imgTrack;
}

inline vbImage& vbSlider::imgFill()
{
	return *m_imgFill;
}

inline vbImage& vbSlider::imgHandle()
{
	return *m_imgHandle;
}


#endif // !VB_SLIDER_H