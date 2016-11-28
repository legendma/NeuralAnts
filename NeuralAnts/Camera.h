#pragma once

using namespace DirectX;
class Camera : public Singleton<Camera>
{
	friend class Singleton < Camera > ;
public:
	Camera();
	~Camera();

	SimpleMath::Matrix GetProjection();
	SimpleMath::Matrix GetView();
	void SetAspect(float aspect);
	void SetFOV(float fov);
	void SetPosition(SimpleMath::Vector3 position);
	void LookAt(SimpleMath::Vector3 target);

private:
	typedef enum
	{
		MODE_FREE,
		MODE_LOOK_AT
	} CameraMode;

	SimpleMath::Vector3    m_position;
	SimpleMath::Vector3    m_look_target;

	CameraMode             m_mode;
	float                  m_aspect_ratio;
	float                  m_field_of_view;
};

