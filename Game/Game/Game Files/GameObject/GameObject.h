#pragma once

#include <typeinfo>
#include <vector>

class GameObject
{
private:
	static std::vector<GameObject*>m_instances;
	static unsigned int m_numberOfInstances;

	std::string m_name;


protected:
	GameObject(GameObject* pointer, const std::string p_name);

	virtual void Start() {}//Before the main loop
	virtual void Awake() {}//First update

	virtual void FrameStartUpdate() {}
	virtual void Update() {}
	virtual void FrameEndUpdate() {}

	virtual void Render() {}
	virtual void OnGui() {}

	virtual void End(){}

	virtual int GetLastInstance()final { return m_numberOfInstances - 1; }

	static void RemoveFromVector(const unsigned int index);

	int m_index;

public:
	static void CallStart();
	static void CallAwake();

	static void CallFrameStartUpdate();
	static void CallUpdate();
	static void CallFrameEndUpdate();

	static void CallRender();
	static void CallOnGUI();

	static void CallEnd();

	static void Clean();

	static GameObject* Find(const std::string &p_name);//Find object using its name
	
	virtual unsigned int GetIndex()final { return m_index; }

	inline const char* GetRealType()const { return typeid(*this).name; }
	inline const char* GetRealRawType()const { return typeid(*this).raw_name; }

	virtual ~GameObject();
};