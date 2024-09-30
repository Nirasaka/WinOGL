#include "pch.h"
#include "CVertex.h"

CVertex::CVertex() {
	x = 0.0;
	y = 0.0;
	next_vertex = NULL;
	behind_vertex = NULL;
}

CVertex::CVertex(float new_x, float new_y, CVertex* new_next, CVertex* new_behind) {
	x = new_x;
	y = new_y;
	next_vertex = new_next;
	behind_vertex = new_behind;
}

CVertex::~CVertex() {
}

// 頂点のX座標を書きこむ
void CVertex::SetX(float new_x)
{
	x = new_x;
}

// 頂点のY座標を書きこむ
void CVertex::SetY(float new_y)
{
	y = new_y;
}

// 頂点のX座標を読み込む
float CVertex::GetX()
{
	return x;
}

// 頂点のY座標を読み込む
float CVertex::GetY()
{
	return y;
}

// 次の頂点リストを指すポインタを書き込む
void CVertex::SetNext(CVertex* new_next)
{
	next_vertex = new_next;
}

// 次の頂点リストを指すポインタを読み込む
CVertex* CVertex::GetNext()
{
	return next_vertex;
}

// 前の頂点リストを指すポインタを書き込む
void CVertex::SetBehind(CVertex* new_behind)
{
	behind_vertex = new_behind;
}

// 前の頂点リストを指すポインタを読み込む
CVertex* CVertex::GetBehind()
{
	return behind_vertex;
}

// リストを解放する
void CVertex::FreeVertex()
{
	CVertex* nowV = this;
	while (nowV != NULL) {
		CVertex* del_cell = nowV;
		nowV = nowV->GetNext();
		delete del_cell;
	}
}