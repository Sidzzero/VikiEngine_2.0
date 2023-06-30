#ifndef  CLIENT_H
#define CLIENT_H

#include "Core.h"
class Client
{
public:
	virtual void Init(GLFWwindow* a_window) = 0;

	virtual void Input(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
protected:
	GLFWwindow *m_window;//TODO: do we need it here

};
#endif // ! CLIENT_H

