#ifndef  CLIENT_H
#define CLIENT_H
class Client
{
public:
	virtual void Init() = 0;

	virtual void Input(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

};
#endif // ! CLIENT_H

