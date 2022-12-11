/*****************************************************************//**
 * \file   Collision.h
 * \brief  
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include "../AppFrameMath.h"

	class AABB{
	public:
		Vector2 min;//<コリジョン矩形の左上座標
		Vector2 max;//<コリジョン矩形の右下座標

	};
	/**
	* \brief 2つのAABBの交差判定
	*
	* \param r1 AABB1個目
	* \param r2 AABB2個目
	* \return 交差していたらTrue
	*/
	bool Intersect(const AABB& r1, const AABB& r2);

	/**
* \brief 2つのAABBの交差判定
*
* \param r1 AABB1個目
* \param r2 AABB2個目
* \return 1個目の中に2個目が完全に収まっていればTrue
*/
	bool Within(const AABB& r1, const AABB& r2);

	/**
* \brief 1つのAABBと1つの点の交差判定
*
* \param r1 AABB
* \param r2 座標
* \return 1個目の中に2個目が収まっていればTrue
*/
	bool Within(const AABB& r1, const Vector2& r2);

