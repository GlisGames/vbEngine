#include "vbEngine.h"
#include "vbSlider.h"

vbSlider::vbSlider(const Rectangle& boundingArea, const SliderDirection& direct, const Color& valueColor, const Color& remainColor)
	:vbContainer(), m_onChangeValueCallback(nullptr), m_valueColor(valueColor), m_remainColor(remainColor),
	m_imgFill(new vbImage()), m_imgHandle(new vbImage()), m_imgTrack(new vbImage())
{
	this->position = {boundingArea.x, boundingArea.y};
	this->width = boundingArea.width;
	this->height = boundingArea.height;
	this->m_direct = direct;
	this->m_max = 1;
	this->m_min = 0;
	this->m_value = 0;
	this->addObject(m_imgFill);
	this->addObject(m_imgHandle);
	this->addObject(m_imgTrack);

	m_imgHandle->regPointRule = transformRegRule::REG_CENTER;
}

vbSlider::vbSlider(const Vector2& boundingArea, const SliderDirection& direct, Texture2D* track, Texture2D* fill, Texture2D* handle)
	:vbContainer(), m_onChangeValueCallback(nullptr), m_valueColor(WHITE), m_remainColor(WHITE),
	m_imgFill(new vbImage(fill)), m_imgHandle(new vbImage(handle)), m_imgTrack(new vbImage(track))
{
	this->position = { boundingArea.x, boundingArea.y };
	this->width = track->width;
	this->height = track->height;
	this->m_direct = direct;
	this->m_max = 1;
	this->m_min = 0;
	this->m_value = 0;
	this->addObject(m_imgFill);
	this->addObject(m_imgHandle);
	this->addObject(m_imgTrack);

	m_imgHandle->regPointRule = transformRegRule::REG_CENTER;
}

vbSlider::vbSlider(const vbSlider& slider)
	:m_direct(slider.m_direct), m_max(slider.m_max), m_min(slider.m_min), m_value(slider.m_value), m_onChangeValueCallback(slider.m_onChangeValueCallback),
	m_valueColor(slider.m_valueColor), m_remainColor(slider.m_remainColor),
	m_imgFill(slider.m_imgFill), m_imgHandle(slider.m_imgHandle), m_imgTrack(slider.m_imgTrack)
{
	this->position = slider.position;
	this->width = slider.width;
	this->height = slider.height;
	this->gObjects.insert(this->gObjects.end(), slider.gObjects.begin(), slider.gObjects.end());
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
	this->gObjects.insert(this->gObjects.end(), slider.gObjects.begin(), slider.gObjects.end());

	return (*this);
}

vbSlider::~vbSlider()
{

}

void vbSlider::setup()
{
	vbGraphicObject::setup();
	this->isClickable = TRUE;
	//memcpy(&transformed, dynamic_cast<vbProperties*>(this), sizeof(vbProperties));
}

void vbSlider::update()
{
	vbContainer::update();
	
	m_imgFill->position = this->position;
	m_imgTrack->position = this->position;
	
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

	float normalizeValue = (m_value - m_min) / (m_max - m_min);
	switch (m_direct)
	{
	case SliderDirection::LeftToRight:
		m_imgHandle->position.x = transformed.position.x + transformed.width * (normalizeValue)-m_imgHandle->transformed.width * 0.5f;
		m_imgHandle->position.y = transformed.position.y;
		break;
	case SliderDirection::RightToLeft:
		m_imgHandle->position.x = transformed.position.x + transformed.width * (1 - normalizeValue) - m_imgHandle->transformed.width * 0.5f;
		m_imgHandle->position.y = transformed.position.y;
		break;
	case SliderDirection::BottomToTop:
		m_imgHandle->position.y = transformed.position.y + transformed.height * (1 - normalizeValue) - m_imgHandle->transformed.height * 0.5f;
		m_imgHandle->position.x = transformed.position.x;
		break;
	case SliderDirection::TopToBottom:
		m_imgHandle->position.y = transformed.position.y + transformed.height * (normalizeValue)-m_imgHandle->transformed.height * 0.5f;
		m_imgHandle->position.x = transformed.position.x;
		break;
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
	{
		BeginScissorMode(valueRect.x, valueRect.y, valueRect.width, valueRect.height);
		this->m_imgFill->draw();
		EndScissorMode();
	}

	if (m_imgHandle->getTexture() != NULL)
	{
		this->m_imgHandle->draw();
	}
		
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

