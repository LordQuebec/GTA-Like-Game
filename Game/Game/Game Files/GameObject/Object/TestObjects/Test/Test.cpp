#include "Test.h"
#include "../../../../Manager/InputManager/InputManager.h"
#include "../../../../Manager/Time Manager/TimeManager.h"

TestO::TestO()
	:GameObject(this, "TEST")
{}


void TestO::Start()
{
	std::vector<glm::vec3>pos = { glm::vec3(-1, -1, 0), glm::vec3(1, -1, 0), glm::vec3(0, 1, 0) };
	std::vector<glm::vec4>color = { glm::vec4(1, 0, 0, 1), glm::vec4(0, 1, 0, 1), glm::vec4(0, 0, 1, 1) };

	m_testObjectVBO.SendData(GL_STATIC_DRAW, pos, color);
}

void TestO::Render()
{
	if (Input->GetInput("walk"))
	{
		m_testObjectVBO.Translate(glm::vec3( 1 * Time->DeltaTime(), 0, 0));
	}
	m_testObjectVBO.Render();//Log("OK");
}