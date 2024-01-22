#include "../Input/InputSystem.h"
#include <Windows.h>

// Unique pointer to instance of Scene
std::unique_ptr<InputSystem> InputSystem::m_instance;

InputSystem::InputSystem() : m_KeyDelayTimer{0.25f}, m_KeyRepeatTimer{0.01f}, m_Keypressed{false}
{
	
}


InputSystem::~InputSystem()
{
}

std::unique_ptr<InputSystem>& InputSystem::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::make_unique<InputSystem>();
	}
	return m_instance;
}

void InputSystem::update()
{
	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			allKeyStates[i].pressed = false;
			allKeyStates[i].down = false;
			allKeyStates[i].up = false;

			// KEY IS DOWN
			if ((m_keys_state[i] & 0x80) && m_keys_state[i] != m_old_keys_state[i])
			{
				//std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				//while (it != m_set_listeners.end())
				//{
				//	(*it)->onKeyPressed(i);
				//	++it;
				//	allKeyStates[i].pressed = true;
				//}
				//(*it)->onKeyPressed(i);
				//++it;
				allKeyStates[i].pressed = true;
				m_KeyDelayTimer = 0.25f;
			}
			else if ((m_keys_state[i] & 0x80) && m_keys_state[i] == m_old_keys_state[i])
			{
				m_KeyDelayTimer -= TDS::TimeStep::GetDeltaTime();
				//std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				if (m_KeyDelayTimer <= 0.0f)
				{
					//while (it != m_set_listeners.end())
					//{
					//	(*it)->onKeyDown(i);
					//	++it;
					//	allKeyStates[i].down = true;
					//}
					//(*it)->onKeyDown(i);
					//++it;
					//allKeyStates[i].down = true;
				}
				allKeyStates[i].down = true;
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					//std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					//while (it != m_set_listeners.end())
					//{
					//	(*it)->onKeyUp(i);
					//	++it;
					//	allKeyStates[i].up = true;
					//}
					//(*it)->onKeyUp(i);
					//++it;
					allKeyStates[i].up = true;
				}
			}

		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

//void InputSystem::addListener(InputListener* listener)
//{
//	m_set_listeners.insert(listener);
//}
//
//void InputSystem::removeListener(InputListener* listener)
//{
//	m_set_listeners.erase(listener);
//}

bool InputSystem::isKeyPressed(int key)
{
	return allKeyStates[key].pressed;
}
bool InputSystem::isKeyDown(int key)
{
	return allKeyStates[key].down;
}
bool InputSystem::isKeyReleased(int key)
{
	return allKeyStates[key].up;
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}