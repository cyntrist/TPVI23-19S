#pragma once

class GameObject
{

public:
	GameObject() = default;
	GameObject();
	~GameObject();
	virtual void render() = 0;
};