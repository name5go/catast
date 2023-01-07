/*****************************************************************//**
 * \file   MessageWindow.h
 * \brief  ���b�Z�[�W���\�������E�B���h�E
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
class MessageWindow : public ObjectBase
{
public:
	MessageWindow();
	~MessageWindow();
	void Init()override;
	void Update(InputManager& input)override;
	void Render()override;
	void Debug()override;
	bool SetMassage(std::string name,std::string message);
private:

	//�\���p�ɃZ�b�g������e
	int _cg;//�`�悷��L�����摜
	std::string _nameText;//�`�悷�閼�O
	std::string _message;//�`�悷��S��
	std::array<int, 10> _insetImageList;//�����ɑ}���ł���摜

	//�������p���
	int _messageWidth;//�S���̕�px
	int _lineMax;//�S�����̍s��

	//���b�Z�[�W�`�撆�Ɏg�p����ϐ�
	int _drawingByte;//���o�C�g�ڂ̕�����`�悵�Ă��邩
	int _drawingPositionX;//�`�悵�Ă��镶����X���Wpx
	int _drawingLine;//�`�悵�Ă��镶���̍s��
	float _time;//�Ō���̕�����`�悵�n�߂Ă���o�߂�������(sec)
	int _color;//�����F
	float _wait;//�����`����n�߂�܂ł̑ҋ@����(sec)
	int _drawingImage;//�����ɑ}�������摜

	bool _messageFinished;//�S���\�������t���O

	int _fontSize;
	int _font;//�t�H���g�n���h��

	int _screen;//�t���[���o�b�t�@


};

