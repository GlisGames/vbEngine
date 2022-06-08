#include "vbSlider.h"
vbSlider::vbSlider(const Rectangle& boundingArea, const SliderDirection& direct, const Color& valueColor, const Color& remainColor)
	:vbGraphicObject(), m_onChangeValueCallback(nullptr), m_valueColor(valueColor), m_remainColor(remainColor)
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
	m_valueColor(slider.m_valueColor), m_remainColor(slider.m_remainColor)
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

	return (*this);
}

vbSlider::~vbSlider()
{

}

void vbSlider::setup()
{
	vbGraphicObject::setup();
	this->isClickable = TRUE;
}

void vbSlider::update()
{
	vbGraphicObject::update();
	if (isClicked())
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

	DrawRectangleRec(valueRect, m_valueColor);
	DrawRectangleRec(remainRect, m_remainColor);
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
	m_onChangeValueCallback(*this);
}
