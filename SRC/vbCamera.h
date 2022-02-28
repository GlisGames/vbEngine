#ifndef VBCAMERA_H
#define VBCAMERA_H

#include "raylib.h"
#include <stdexcept>

#define DEFAULT_CAMERA2D Camera2D{ \
	Vector2{0.0f, 0.0f}, /*offset*/ \
	Vector2{0.0f, 0.0f}, /*target*/\
	0.0f, /*rotation*/\
	1.0f /*zoom*/\
}

//The "proto-type" for vbCamera2D
class vbCamera;

//The object inheritance this class can control the camera
class vbCameraFollowable
{
public:
	vbCameraFollowable();
	virtual ~vbCameraFollowable();

	virtual void update(vbCamera* camera) = 0;
protected:
};

class vbCamera
{
public:
	vbCamera(const Camera2D& camera = DEFAULT_CAMERA2D);
	vbCamera(const vbCamera& camera);
	vbCamera& operator=(const vbCamera& camera);
	virtual ~vbCamera();

	const Camera2D& camera() const;
	Camera2D& camera();

	void setup();
	void update();
	void follow(vbCameraFollowable* followingObject);
protected:
	Camera2D m_camera;
	vbCameraFollowable* m_followingObject;
};

#endif