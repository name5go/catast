/*****************************************************************//**
 * \file   MV1Component.h
 * \brief  MV1�̃g�����X�t�H�[���X�V�A�`��A�A�j���[�V�����t���[���̐i�s�@�\
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/
#pragma once
#include "Object/ComponentBase.h"
#include <functional>
#include <algorithm>
#include <vector>
class AnimationComponent;
class MV1Component :public ComponentBase
{
public:
	MV1Component(int modelHandle);
	~MV1Component();
	bool Init()override;
	void Update()override;
	void Render()override;
	void Debug()override;
	void SetModelHandle(int modelHandle);
	int GetModelHandle() { return _modelHandle; }
	void SetAnimation(int index);
	void SetAnimSpeed(float value) { _animSpeed = value; };
	/**
	 * \brief �A�j���[�V�����̓���̃^�C�~���O�ŌĂяo���֐���ǉ�����
	 * \param animIndex�@�A�j���[�V�����̔ԍ�
	 * \param activateTime�@�A�j���[�V�����̎���
	 * \param function �Ăяo���֐�
	 */
	void AddAnimFunction(int animIndex,float activateTime, std::function<void(void)> function );
private:
	/**
	 * \brief �^�C�~���O���m�F���āA�A�j���[�V�����ɕR�Â��֐����Ăяo��
	 * \param preTime�@�O�t���[���̃A�j���[�V��������
	 * \param nowTime�@���݃t���[���̃A�j���[�V��������
	 */
	void CheckAnimFunction(float preTime,float nowTime);

	int _modelHandle;
	int _attahIndex;
	float _playTime, _totalTime;
	float _animSpeed;
	std::vector<std::vector<std::pair<float, std::function<void(void)>>>> _animFunction;//[�A�j���[�V����Index][����,�Ăяo���֐�]
};