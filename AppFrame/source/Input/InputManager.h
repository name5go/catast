/*****************************************************************//**
 * \file   InputManager.h
 * \brief  ���͎擾�N���X
 *
 * \author �y�������Y
 * \date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <utility>
#include <array>
#include <map>
#include <vector>

	//�L�[�̓��͏�ԁ@�����Ă��邩�A�������u�Ԃ��A�������u�Ԃ�
	enum class InputState {
		Hold,
		Pressed,
		Released
	};

	class InputManager {
	public:
		InputManager();
		virtual ~InputManager();
		virtual void Init();

		//���t���[���Ăяo�����͎擾�֐�
		void Input();

		void Debug();

		/**
		 * \brief ���͎擾�p�̊֐�
		 * \param state �擾���������͏�ԁ@�����Ă��邩�A�������u�Ԃ��A�������u�Ԃ�
		 * \return  ���͂������true
		 */
		virtual bool GetMouseLeft(InputState state) { return GetMouseButton(MOUSE_INPUT_LEFT, state); }
		virtual bool GetMouseMiddle(InputState state) { return GetMouseButton(MOUSE_INPUT_MIDDLE, state); }
		virtual bool GetMouseRight(InputState state) { return GetMouseButton(MOUSE_INPUT_RIGHT, state); }
		virtual bool GetKeyUp(InputState state, int controllerNumber=0) { return GetKeyButton(KEY_INPUT_UP, state, controllerNumber); }
		virtual bool GetKeyDown(InputState state, int controllerNumber=0) { return GetKeyButton(KEY_INPUT_DOWN, state, controllerNumber); }
		virtual bool GetKeyLeft(InputState state, int controllerNumber=0) { return GetKeyButton(KEY_INPUT_LEFT, state, controllerNumber); }
		virtual bool GetKeyRight(InputState state, int controllerNumber=0) { return GetKeyButton(KEY_INPUT_RIGHT, state, controllerNumber); }

		virtual bool GetKeyZ(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_1, state, controllerNumber); }
		virtual bool GetKeyX(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_2, state, controllerNumber); }
		virtual bool GetKeyC(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_3, state, controllerNumber); }
		virtual bool GetKeyA(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_4, state, controllerNumber); }
		virtual bool GetKeyS(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_5, state, controllerNumber); }
		virtual bool GetKeyD(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_6, state, controllerNumber); }
		virtual bool GetKeyQ(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_8, state, controllerNumber); }
		virtual bool GetKeyW(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_8, state, controllerNumber); }
		virtual bool GetKeyESC(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_9, state, controllerNumber); }
		virtual bool GetKeySPACE(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_10, state, controllerNumber); }

		virtual bool GetPadDown(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_DOWN, state, controllerNumber); }
		virtual bool GetPadLeft(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_LEFT, state, controllerNumber); }
		virtual bool GetPadRight(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_RIGHT, state, controllerNumber); }
		virtual bool GetPadUp(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_UP, state, controllerNumber); }
		virtual bool GetPadX(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_1, state, controllerNumber); }
		virtual bool GetPadY(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_2, state, controllerNumber); }
		virtual bool GetPadA(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_3, state, controllerNumber); }
		virtual bool GetPadB(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_4, state, controllerNumber); }
		virtual bool GetPadL1(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_5, state, controllerNumber); }
		virtual bool GetPadR1(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_6, state, controllerNumber); }
		virtual bool GetPadL2(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_8, state, controllerNumber); }
		virtual bool GetPadR2(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_8, state, controllerNumber); }
		//L�X�e�B�b�N��������
		virtual bool GetPadL3(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_9, state, controllerNumber); }
		//R�X�e�B�b�N��������
		virtual bool GetPadR3(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_10, state, controllerNumber); }
		virtual bool GetPadBack(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_11, state, controllerNumber); }
		virtual bool GetPadStart(InputState state, int controllerNumber = 0) { return GetKeyButton(PAD_INPUT_12, state, controllerNumber); }

		//�}�E�X�ʒu�擾
		std::pair<int, int> GetMouseXY() { return { _mouseX,_mouseY }; };
		int GetMouseX() { return _mouseX; }
		int GetMouseY() { return _mouseY; }
		//�}�E�X�ʒu�ݒ�
		void SetMouseXY(std::pair<int, int> set) { _mouseX = set.first; _mouseY = set.second; }
		void SetMouseX(int set) { _mouseX = set; }
		void SetMouseY(int set) { _mouseY = set; }

	protected:
		int _mouseX, _mouseY;
		int _mouse, _oldMouse;

		std::vector<int> _keys, _oldKeys;
		std::vector<int> _x;
		std::vector<int> _y;

		static constexpr std::array<int, 16> _controllerList = {
			DX_INPUT_KEY_PAD1,
			DX_INPUT_PAD2,
			DX_INPUT_PAD3,
			DX_INPUT_PAD4,
			DX_INPUT_PAD5,
			DX_INPUT_PAD6,
			DX_INPUT_PAD7,
			DX_INPUT_PAD8,
			DX_INPUT_PAD9,
			DX_INPUT_PAD10,
			DX_INPUT_PAD11,
			DX_INPUT_PAD12,
			DX_INPUT_PAD13,
			DX_INPUT_PAD14,
			DX_INPUT_PAD15,
			DX_INPUT_PAD16
		};

		bool GetMouseButton(int key, InputState state);
		bool GetKeyButton(int key, InputState state, int controllerNumber);
	};