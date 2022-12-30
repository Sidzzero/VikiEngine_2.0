#ifndef  VD_CLIENT_H
#define VD_CLIENT_H
#include "Client.h"
#include "common.h"
class VD_Client :
    public Client
{
public:
	 void Init() override;

	 void Input() override;
	 void Update() override;
	 void Render() override;

	 Mesh square;
	 Buffer triangleRenderer;
	 unsigned int shaderProgram;

private:

};
#endif
