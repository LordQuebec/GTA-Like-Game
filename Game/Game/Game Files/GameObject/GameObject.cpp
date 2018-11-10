#include "GameObject.h"

using namespace std;


vector<GameObject*> GameObject::m_instances = {};
unsigned int GameObject::m_numberOfInstances = 0;


GameObject::GameObject(GameObject* p_pointer, const string p_name)
	:m_name(p_name)
{
	m_instances.push_back(p_pointer);
	p_pointer->m_index = m_numberOfInstances;
	++m_numberOfInstances;
}



#pragma region Calls

void GameObject::CallStart()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->Start();
}

void GameObject::CallAwake()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->Awake();
}

void GameObject::CallFrameStartUpdate()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->FrameStartUpdate();
}

void GameObject::CallUpdate()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->Update();
}

void GameObject::CallFrameEndUpdate()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->FrameEndUpdate();
}

void GameObject::CallRender()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->Render();
}

void GameObject::CallOnGUI()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->OnGui();
}

void GameObject::CallEnd()
{
	for (auto gameObject : GameObject::m_instances)
		gameObject->End();
}

#pragma endregion


void GameObject::Clean()
{
	for (int i = 0; i < m_numberOfInstances; ++i)
		delete m_instances[i];

	m_instances.clear();
}


GameObject* GameObject::Find(const string &p_name)
{
	for (auto gameObject : GameObject::m_instances)
	{
		if (gameObject->m_name == p_name)
			return gameObject;
	}
	return nullptr;
}

void GameObject::RemoveFromVector(const unsigned int p_index)
{
	for (int i = p_index; i < m_numberOfInstances; ++i)
		--m_instances[i]->m_index;

	--m_numberOfInstances;

	m_instances.erase(m_instances.begin() + p_index);
}


GameObject::~GameObject()
{
	RemoveFromVector(this->m_index);
}