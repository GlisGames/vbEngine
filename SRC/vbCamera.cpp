#include "vbCamera.h"

vbCamera::vbCamera(const Camera2D& camera)
	:m_camera(camera), m_followingObject(NULL)
{
}

vbCamera::vbCamera(const vbCamera& camera)
	: m_camera(camera.m_camera), m_followingObject(camera.m_followingObject)
{
}

vbCamera& vbCamera::operator=(const vbCamera& camera)
{
	m_camera = camera.m_camera;
	m_followingObject = camera.m_followingObject;

	return (*this);
}

vbCamera::~vbCamera()
{
}

const Camera2D& vbCamera::camera() const
{
	return m_camera;
}

Camera2D& vbCamera::camera()
{
	return const_cast<Camera2D&>(static_cast<const vbCamera&>(*this).camera());
}

void vbCamera::setup()
{
}

void vbCamera::update()
{
	if (m_followingObject != NULL)
	{
		m_followingObject->update(this);
	}
}

void vbCamera::follow(vbCameraFollowable* followingObject)
{
	if (followingObject == NULL)
	{
		throw std::invalid_argument("Null-pointer followingObject");
	}
	this->m_followingObject = followingObject;
}

vbCameraFollowable::vbCameraFollowable()
{
}

vbCameraFollowable::~vbCameraFollowable()
{
}