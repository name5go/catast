/*****************************************************************//**
 * \file   MV1Component.h
 * \brief  MV1のトランスフォーム更新、描画、アニメーションフレームの進行機能
 *
 * \author 土居将太郎
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
	 * \brief アニメーションの特定のタイミングで呼び出す関数を追加する
	 * \param animIndex　アニメーションの番号
	 * \param activateTime　アニメーションの時間
	 * \param function 呼び出す関数
	 */
	void AddAnimFunction(int animIndex,float activateTime, std::function<void(void)> function );
private:
	/**
	 * \brief タイミングを確認して、アニメーションに紐づく関数を呼び出す
	 * \param preTime　前フレームのアニメーション時間
	 * \param nowTime　現在フレームのアニメーション時間
	 */
	void CheckAnimFunction(float preTime,float nowTime);

	int _modelHandle;
	int _attahIndex;
	float _playTime, _totalTime;
	float _animSpeed;
	std::vector<std::vector<std::pair<float, std::function<void(void)>>>> _animFunction;//[アニメーションIndex][時間,呼び出し関数]
};