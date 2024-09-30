#include "pch.h"
#pragma once

class CVertex
{
public:
	CVertex();
	CVertex(float new_x, float new_y, CVertex* new_next, CVertex* new_behind);
	~CVertex();

private:
	// 座標
	float x, y;
	// 次の頂点
	CVertex* next_vertex;
	// 前の頂点
	CVertex* behind_vertex;

public:
	// 頂点のX座標を書き込む
	void SetX(float);
	// 頂点のY座標を書き込む
	void SetY(float);
	// 頂点のX座標を読み込む
	float GetX();
	// 頂点のY座標を読み込む
	float GetY();

	// 次の頂点リストを指すポインタを書き込む
	void SetNext(CVertex*);
	// 次の頂点リストを指すポインタを読み込む
	CVertex* GetNext();
	// 前の頂点リストを指すポインタを書き込む
	void SetBehind(CVertex*);
	// 前の頂点リストを指すポインタを読み込む
	CVertex* GetBehind();

	// リストを解放する
	void FreeVertex();
};

