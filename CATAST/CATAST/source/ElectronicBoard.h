#pragma once
class ElectronicBoard :public ObjectBase
{
public:
	ElectronicBoard();
	~ElectronicBoard();
	void Init();
	void Update(InputManager& input);
	void Render();
	void Debug()override;
	void SetFlag(bool flag) { _flag = flag; }
private:
	VERTEX3DSHADER _vertex[4];
	unsigned short _index[6];
	int _vHandle;
	int _pHandle;
	int _testHandle;

	bool _flag;
	int _screenHandle;
	int _baseTex;
	int _moveTex;
	std::vector<int> _fx;
	int _fxIndex,_fxX,_fxY;

	float _brightness;
	int _gridNumber;

};

