#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "ModeBase.h"

class InputManager;
	class	ModeServer
	{
	public:
		ModeServer();
		virtual	~ModeServer();
		static ModeServer* _lpInstance;
		static ModeServer* GetInstance() { return (ModeServer*)_lpInstance; }

		int Add(std::unique_ptr<ModeBase> mode, int layer, const char* name);		// �o�^�͂��邪�A��x���C�����񂳂Ȃ��Ƃ����Ȃ�
		int Del(ModeBase* mode);		// �폜�\��
		ModeBase* Get(int uid);
		ModeBase* Get(const char* name);
		int GetId(ModeBase* mode);
		int GetId(const char* name);
		const char* GetName(ModeBase* mode);
		const char* GetName(int uid);
		void Clear();
		int	LayerTop() { return INT32_MAX; }

		int UpdateInit();	// �v���Z�X���񂷂��߂̏�����
		int Update(InputManager& input);		// ���C���[�̏�̕����珈��
		int UpdateFinish();		// �v���Z�X���񂵂���̌�n��

		int RenderInit();		// �`����񂷂��߂̏�����
		int Render();		// ���C���[�̉��̕����珈��
		int RenderFinish();		// �`����񂵂���̌�n��

		int DebugInit();		// �f�o�b�O���񂷂��߂̏�����
		int Debug();		// ���C���[�̉��̕����珈��
		int DebugFinish();		// �f�o�b�O���񂵂���̌�n��

		int SkipUpdateUnderLayer();		// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�������Ă΂Ȃ�
		int SkipRenderUnderLayer();			// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�`����Ă΂Ȃ�
		int PauseProcessUnderLayer();		// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A���Ԍo�߂��~�߂�

	private:
		int Release(ModeBase* mode);		// �폜��delete
		bool IsDelRegist(ModeBase* mode);	// �폜�\�񂳂�Ă��邩�H
		bool IsAdd(ModeBase* mode);		// ���X�g�ɂ��邩�H

		std::vector<std::unique_ptr<ModeBase>>	_vMode;			// ���[�h���X�g
		std::vector<std::unique_ptr<ModeBase>>	_vModeAdd;		// �ǉ��\��
		std::vector<ModeBase*>		_vModeDel;		// �폜�\��

		ModeBase* _nowMode;		// ���݌Ăяo�����̃��[�h
		ModeBase* _skipUpdateMode;	// ���̃��[�h��艺��Process���Ă΂Ȃ�
		ModeBase* _skipRenderMode;	// ���̃��[�h��艺��Render���Ă΂Ȃ�
		ModeBase* _pauseUpdateMode;	// ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�

		int	_uid_count;		// uid�J�E���^
	};