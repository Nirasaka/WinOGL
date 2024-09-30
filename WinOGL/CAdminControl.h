#include "pch.h"
#pragma once
#include <gl/GL.h>
#include "CVertex.h"
#include "CShape.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();

private:
	// 形状リストのヘッド
	CShape* shape_head;
	// 形状リストのテール
	CShape* shape_tail;
	// 点の描画
	void DrawPoint(CVertex* vertex, bool closed);
	// 線の描画
	void DrawLine(CVertex* start, CVertex* end ,bool closed);
	// 予測線を描画
	void DrawForecast();
	// マウスポインタを描画
	void DrawMousePointer();
	
	// 現在のマウスの位置を格納
	CVertex* vertex_mouse;

public:
	// 描画
	void Draw();
	// 頂点の追加
	void AddVertex(float, float);
	// 頂点の削除
	void DeleteVertex();
	// マウスの位置を取得
	void GetMouseVertex(float, float);
	// 2つの頂点が非常に近いかどうか
	bool IsBetweenVerticesShort(CVertex*, CVertex*);
	// 次打つ点で閉じることができるかどうか
	bool CanShapeClose();
};

/*
〇完了した演習
1,2,3

〇オリジナリティ
・形状が閉じているときに色を変えるように変更。(表示テスト用)
・IsShapeClosed：形状が閉じているかどうかを返すCShapeクラス関数
・IsBetweenVerticesShort ：CVertex*型の頂点2つの距離が非常に近いかどうかを返すCAdminControlクラス関数
　						 　形状を閉じるかどうかの判定に使用しており、今後頂点の選択に活用予定。
・GetVerticesNum：形状が持つ頂点の数を返すCShapeクラス関数
・GetMouseVertex：マウスの位置を取得するCAdminControlクラス関数
・DrawForecast：予測線を描画
・DrawMousePointer：マウスポインタを描写
・IsBetweenVerticesShort：2つの頂点が非常に近いかどうかを返すCAdminControlクラス関数

*/
