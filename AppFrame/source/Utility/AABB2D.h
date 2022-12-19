/*****************************************************************//**
 * \file   Collision.h
 * \brief  
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include "../AppFrameMath.h"

	class AABB{
	public:
		Vector2 min;//<�R���W������`�̍�����W
		Vector2 max;//<�R���W������`�̉E�����W

	};
	/**
	* \brief 2��AABB�̌�������
	*
	* \param r1 AABB1��
	* \param r2 AABB2��
	* \return �������Ă�����True
	*/
	bool Intersect(const AABB& r1, const AABB& r2);

	/**
* \brief 2��AABB�̌�������
*
* \param r1 AABB1��
* \param r2 AABB2��
* \return 1�ڂ̒���2�ڂ����S�Ɏ��܂��Ă����True
*/
	bool Within(const AABB& r1, const AABB& r2);

	/**
* \brief 1��AABB��1�̓_�̌�������
*
* \param r1 AABB
* \param r2 ���W
* \return 1�ڂ̒���2�ڂ����܂��Ă����True
*/
	bool Within(const AABB& r1, const Vector2& r2);

