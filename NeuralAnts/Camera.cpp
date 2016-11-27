#include "pch.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

SimpleMath::Matrix Camera::GetProjection()
{
	return(SimpleMath::Matrix::CreatePerspectiveFieldOfView(m_field_of_view, m_aspect_ratio, 0.1f, 1000.0f));
}

SimpleMath::Matrix Camera::GetView()
{
	auto out = SimpleMath::Matrix::Identity;
	if(m_mode == MODE_LOOK_AT)
	{
		out = SimpleMath::Matrix::CreateLookAt(m_position, m_look_target, SimpleMath::Vector3::UnitY);
	}
	else if(m_mode == MODE_FREE)
	{

	}

	return(out);
}

void Camera::LookAt(SimpleMath::Vector3 target)
{
	m_look_target = target;
	m_mode = MODE_LOOK_AT;
}

void Camera::SetAspect(float aspect)
{
	m_aspect_ratio = aspect;
}

void Camera::SetFOV(float fov)
{
	m_field_of_view = fov;
}

void Camera::SetPosition(SimpleMath::Vector3 position)
{
	m_position = position;
}