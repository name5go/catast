#pragma once
class ElectronicBoard :public ObjectBase
{
public:
	~ElectronicBoard();
	void Init();
	void Update(InputManager& input);
	void Render();
private:
	VERTEX3DSHADER _vertex[4];
	unsigned short _index[6];
	int _vHandle, _vHandle2;
	int _pHandle, _pHandle2;
};

