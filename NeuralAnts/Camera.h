#pragma once
class Camera : public Singleton<Camera>
{
	friend class Singleton < Camera > ;
public:
	Camera();
	~Camera();

private:
	DirectX::SimpleMath::Vector3 m_position;


};

