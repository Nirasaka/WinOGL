#include "pch.h"
#pragma once
#include "CVertex.h"

class CShape
{
public:
	CShape::CShape();
	CShape::CShape(CVertex* new_vh, CVertex* new_vt, CShape* new_ns, CShape* new_bs);
	CShape::~CShape();

private:
	// 点リストのヘッド
	CVertex* vertex_head;
	// 点リストのテール
	CVertex* vertex_tail;

	// 次の形状
	CShape* next_shape;
	// 前の形状
	CShape* behind_shape;


public:
	// 先頭の頂点を書きこむ
	void SetVertexHead(CVertex*);
	// 先頭の頂点を読み込む
	CVertex* GetVertexHead();
	// 末尾の頂点を書きこむ
	void SetVertexTail(CVertex*);
	// 末尾の頂点を読み込む
	CVertex* GetVertexTail();

	// 次の形状を書きこむ
	void SetNextShape(CShape*);
	// 次の形状を読み込む
	CShape* GetNextShape();
	// 前の形状を書きこむ
	void SetBehindShape(CShape*);
	// 前の形状を読み込む
	CShape* GetBehindShape();

	// 閉じているかどうかを返す
	bool IsShapeClosed();
	// 頂点の数を返す
	int GetVerticesNum();

	// リストを解放する
	void FreeShape();
};

