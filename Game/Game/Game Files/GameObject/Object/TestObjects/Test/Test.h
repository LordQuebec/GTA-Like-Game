#pragma once


#include "../../../GameObject.h"
#include "../../../../VBO/VBO.h"

class TestO : public GameObject
{
public:
	TestO();
	~TestO() {}

protected:
	void Start();
	void Render();


private:
	VBO m_testObjectVBO;
};