#pragma once

class RockOnObject : public IGameObject
{
public:
	virtual Vector3 GetPosition() const
	{
		return Vector3::Zero;
	}
	virtual int GetState() const
	{
		return 0;
	}
};