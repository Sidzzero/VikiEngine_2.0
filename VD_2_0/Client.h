#ifndef  CLIENT_H
#define CLIENT_H
class Client
{
public:
	virtual void Init() = 0;

	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};
#endif // ! CLIENT_H

