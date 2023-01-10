/*****************************************************************//**
 * \file   EditorTextBox.h
 * \brief  ���l����͂���{�b�N�X
 *
 * \author �y�������Y
 * \date   January 2023
 *********************************************************************/
#pragma once
class EditorTextBox : public ObjectBase
{
public:
	EditorTextBox(ObjectListWindow& list);
	~EditorTextBox();
	void Init()override;
	void Update(InputManager& input)override;
	void Render()override;
	void Debug()override;

	void SetSizeX(int value) { _sizeX = value; }
	void SetSizeY(int value) { _sizeY = value; }
	int GetSizeX() { return _sizeX; }
	int GetSizeY() { return _sizeY; }
private:
	ObjectListWindow& _list;
	int _sizeX;
	int _sizeY;
};

