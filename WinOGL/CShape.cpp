#include "pch.h"
#include "CShape.h"

CShape::CShape()
{
	vertex_head = NULL;
	vertex_tail = NULL;
	next_shape = NULL;
	behind_shape = NULL;
}

CShape::CShape(CVertex* new_vh, CVertex* new_vt, CShape* new_ns, CShape* new_bs)
{
	vertex_head = new_vh;
	vertex_tail = new_vt;
	next_shape = new_ns;
	behind_shape = new_bs;
}

CShape::~CShape()
{
	vertex_head->FreeVertex();
}

// 先頭の頂点を書きこむ
void CShape::SetVertexHead(CVertex* new_vh)
{
	vertex_head = new_vh;
}

// 先頭の頂点を読み込む
CVertex* CShape::GetVertexHead()
{
	return vertex_head;
}

// 末尾の頂点を書きこむ
void CShape::SetVertexTail(CVertex* new_vt)
{
	vertex_tail = new_vt;
}

// 末尾の頂点を読み込む
CVertex* CShape::GetVertexTail()
{
	return vertex_tail;
}

// 次の形状を書きこむ
void CShape::SetNextShape(CShape* new_sp)
{
	next_shape = new_sp;
}

// 次の形状を読み込む
CShape* CShape::GetNextShape()
{
	return next_shape;
}

// 前の形状を書きこむ
void CShape::SetBehindShape(CShape* new_sp)
{
	behind_shape = new_sp;
}

// 前の形状を読み込む
CShape* CShape::GetBehindShape()
{
	return behind_shape;
}

// 閉じているかどうか
bool CShape::IsShapeClosed()
{
	// 点が4つ以上の場合(図形を構成する点と閉じた時に追加した点)
	bool a = this->GetVerticesNum() >= 3 + 1;
	// x座標とy座標が同じ
	bool b = vertex_head->GetX() == vertex_tail->GetX() && vertex_head->GetY() == vertex_tail->GetY();
	return a && b;
}

// 形状の頂点の数を返す
int CShape::GetVerticesNum()
{
	int cnt = 0;
	for (CVertex* vp = vertex_head; vp != NULL; vp = vp->GetNext()) cnt++;
	return cnt;
}

// リストを解放する
void CShape::FreeShape()
{
	CShape* nowS = this;
	while (nowS != NULL) {
		CShape* del_cell = nowS;
		nowS = nowS->GetNextShape();
		delete del_cell;
	}
}
