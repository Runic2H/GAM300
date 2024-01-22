#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "dotnet/ImportExport.h"
#include "Timestep/Timestep.h"

class DLL_API InputSystem
{
public:
	InputSystem();
	~InputSystem();

	static std::unique_ptr<InputSystem>& GetInstance();

	void update();
	//void addListener(InputListener* listener);
	//void removeListener(InputListener* listener);

	bool isKeyPressed(int key);
	bool isKeyDown(int key);
	bool isKeyReleased(int key);

	struct KeyState
	{
		bool pressed;
		bool down;
		bool up;
	};

public:
	static InputSystem* get();
private:
	// Unique pointer to SceneManager
	static std::unique_ptr<InputSystem> m_instance;

	bool m_Keypressed;
	float m_KeyDelayTimer;
	float m_KeyRepeatTimer;
	//std::unordered_set<InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	KeyState allKeyStates[256];
};