#include "vbSlider.h"
vbSlider::vbSlider(const Rectangle& boundingArea, const SliderDirection& direct, const Color& valueColor, const Color& remainColor)
	:vbGraphicObject(), m_onChangeValueCallback(nullptr), m_valueColor(valueColor), m_remainColor(remainColor),
	m_imgFill(new vbImage()), m_imgHandle(new vbImage()), m_imgTrack(new vbImage())
{
	this->position = {boundingArea.x, boundingArea.y};
	this->width = boundingArea.width;
	this->height = boundingArea.height;
	this->m_direct = direct;
	this->m_max = 1;
	this->m_min = 0;
	this->m_value = 0;
}

vbSlider::vbSlider(const vbSlider& slider)
	:m_direct(slider.m_direct), m_max(slider.m_max), m_min(slider.m_min), m_value(slider.m_value), m_onChangeValueCallback(slider.m_onChangeValueCallback),
	m_valueColor(slider.m_valueColor), m_remainColor(slider.m_remainColor),
	m_imgFill(slider.m_imgFill), m_imgHandle(slider.m_imgHandle), m_imgTrack(slider.m_imgTrack)
{
	this->position = slider.position;
	this->width = slider.width;
	this->height = slider.height;
}

vbSlider& vbSlider::operator=(const vbSlider& slider)
{
	this->position = slider.position;
	this->width = slider.width;
	this->height = slider.height;
	m_direct = slider.m_direct;
	m_max = slider.m_max; 
	m_min = slider.m_min;
	m_value = slider.m_value;
	m_onChangeValueCallback = slider.m_onChangeValueCallback;
	m_valueColor = slider.m_valueColor;
	m_remainColor = slider.m_remainColor;
	m_imgFill = slider.m_imgFill;
	m_imgHandle = slider.m_imgHandle;
	m_imgTrack = slider.m_imgTrack;
	return (*this);
}

vbSlider::~vbSlider()
{

}

void vbSlider::setup()
{
	vbGraphicObject::setup();
	this->m_imgFill->setup();
	this->m_imgHandle->setup();
	this->m_imgTrack->setup();
	this->isClickable = TRUE;
}

void vbSlider::update()
{
	vbGraphicObject::update();
	m_imgFill->position = this->position;
	this->m_imgFill->update();
	this->m_imgHandle->update();
	m_imgTrack->position = this->position;
	this->m_imgTrack->update();
	if (isMouseDown())
	{
		Vector2 mousePos = GetMousePosition();
		Vector2 offset = { mousePos.x - transformed.position.x, mousePos.y - transformed.position.y };
		float distance = m_max - m_min;
		//get real selected value
		switch (m_direct)
		{
		case SliderDirection::LeftToRight:
			setValue(m_min + distance * offset.x / transformed.width);
			break;
		case SliderDirection::RightToLeft:
			setValue(m_min + distance * (1 - offset.x / transformed.width));
			break;
		case SliderDirection::BottomToTop:
			setValue(m_min + distance * (1 - offset.y / transformed.height));
			break;
		case SliderDirection::TopToBottom:
			setValue(m_min + distance * offset.y / transformed.height);
			break;
		}
	}
}

void vbSlider::draw()
{
	vbGraphicObject::draw();
	float normalizeValue = (m_value - m_min) / (m_max - m_min);
	Rectangle valueRect = {};
	Rectangle remainRect = {};

	switch (m_direct)
	{
	case SliderDirection::LeftToRight:
		valueRect.x = transformed.position.x;
		valueRect.y = transformed.position.y;
		valueRect.width = transformed.width * normalizeValue;
		valueRect.height = transformed.height;
		remainRect.x = transformed.position.x + transformed.width - transformed.width * (1 - normalizeValue);
		remainRect.y = transformed.position.y;
		remainRect.width = transformed.width * (1 - normalizeValue);
		remainRect.height = transformed.height;
		break;
	case SliderDirection::RightToLeft:
		valueRect.x = transformed.position.x + transformed.width - transformed.width * normalizeValue;
		valueRect.y = transformed.position.y;
		valueRect.width = transformed.width * normalizeValue;
		valueRect.height = transformed.height;
		remainRect.x = transformed.position.x;
		remainRect.y = transformed.position.y;
		remainRect.width = transformed.width * (1 - normalizeValue);
		remainRect.height = transformed.height;
		break;
	case SliderDirection::BottomToTop:
		valueRect.x = transformed.position.x;
		valueRect.y = transformed.position.y + transformed.height - transformed.height * normalizeValue;
		valueRect.width = transformed.width;
		valueRect.height = transformed.height * normalizeValue;
		remainRect.x = transformed.position.x;
		remainRect.y = transformed.position.y;
		remainRect.width = transformed.width;
		remainRect.height = transformed.height * (1 - normalizeValue);
		break;
	case SliderDirection::TopToBottom:
		valueRect.x = transformed.position.x;
		valueRect.y = transformed.position.y;
		valueRect.width = transformed.width;
		valueRect.height = transformed.height * normalizeValue;
		remainRect.x = transformed.position.x;
		remainRect.y = transformed.position.y + transformed.height - transformed.height * (1 - normalizeValue);
		remainRect.width = transformed.width;
		remainRect.height = transformed.height * (1 - normalizeValue);
		break;
	}

	//this->m_imgFill->draw();
	//this->m_imgHandle->draw();
	//this->m_imgTrack->draw();
	if(m_imgTrack->getTexture() == NULL)
		DrawRectangleRec(valueRect, m_valueColor);
	else
		this->m_imgTrack->draw();

	if(m_imgFill->getTexture() == NULL)
		DrawRectangleRec(remainRect, m_remainColor);
	else
		this->m_imgFill->draw();
}

void vbSlider::setMax(const float& max)
{
	if (max < m_min)
	{
		throw std::invalid_argument("max must be greater than m_min: " + std::to_string(max) + "<" + std::to_string(m_min));
	}
	m_max = max;
}

void vbSlider::setMin(const float& min)
{
	if (min > m_max)
	{
		throw std::invalid_argument("min must be less than m_max: " + std::to_string(min) + ">" + std::to_string(m_max));
	}
	m_min = min;
}

void vbSlider::setValue(const float& value)
{
	if (value < m_min || value > m_max)
	{
		throw std::invalid_argument("value is out of range: _value = " + std::to_string(value) + ", _range = (" + std::to_string(m_min) + ", " + std::to_string(m_max) + ")");
	}
	m_value = value;
	if(m_onChangeValueCallback != nullptr)
		m_onChangeValueCallback(*this);
}
