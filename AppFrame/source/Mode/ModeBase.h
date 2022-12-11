#pragma once
#include <memory>
#include <string>

class InputManager;
class ObjectServer;

class ModeServer;

	class		ModeBase
	{
	public:
		ModeBase();
		virtual ~ModeBase();

		virtual bool	Initialize();
		virtual bool	Terminate();
		virtual bool	Update(InputManager& input);
		virtual bool	Render();
		virtual bool	Debug();

		//���̃��[�h���n�܂��Ă���̃J�E���^
		int	GetModeCount() { return _cntMode; }			
		//���̃��[�h���n�܂��Ă���̎���ms
		unsigned long GetModeTime() { return _tmMode; }	
		//�O�t���[������̌o�ߎ���ms
		unsigned long GetStepTime() { return _tmStep; }	
		// ���t���[����1��Process()���ĂԂ�(def:1)
		void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }	
		// 1��̌Ăяo���ɉ���Process()���ĂԂ�(def:1)
		void SetCallOfCount(int count) { _callOfCount = count; }	
		// ���t���[����1��Process()���ĂԂ�(def:1)
		int GetCallPerFrame() { return _callPerFrame; }
		// 1��̌Ăяo���ɉ���Process()���ĂԂ�(def:1)
		int GetCallOfCount() { return _callOfCount; }

		int GetLayer() { return _layer; }
		void SetLayer(int value) { _layer = value; }
		int GetUID() { return _uid; }
		void SetUID(int value) { _uid = value; }
		std::string GetSZName() { return _szName; }
		void SetSZName(std::string string) { _szName = string; }

		// ���Ԍo�߂�������
		void StepTime(unsigned long tmNow);
		// �J�E���g��i�߂�
		void StepCount();

		std::unique_ptr<ObjectServer>& GetObjectServer() { return _objectServer; }

	private:
		// ModeServer�p
		std::string		_szName;
		int				_uid;
		int				_layer;

		// ���[�h�������p
		int		_cntMode;	// �{���[�h�ɓ����Ă���̃J�E���^, 0�X�^�[�g
		unsigned long	_tmMode;	// �{���[�h�ɓ����Ă���̎��ԁBms
		unsigned long	_tmStep;	// �O�t���[������̌o�ߎ��ԁBms
		unsigned long	_tmModeBase;	// ���̃��[�h���n�܂������ԁBms
		unsigned long	_tmPauseBase;	// �|�[�Y���̃x�[�X���ԁBms
		unsigned long	_tmPauseStep;	// �|�[�Y���̐ώZ���ԁBms ���쒆�A���̒l�� _tmMode �ɗp����
		unsigned long	_tmOldFrame;	// �O�t���[���̎��ԁBms

		// CallPerFrame / CallOfCount�p
		int		_callPerFrame, _callPerFrame_cnt;
		int		_callOfCount;

	protected:
		std::unique_ptr<ObjectServer> _objectServer;
	};