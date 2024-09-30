
// WinOGLView.h : CWinOGLView クラスのインターフェイス
//

#pragma once
#include <gl/GL.h>
#include "CAdminControl.h"


class CWinOGLView : public CView
{
protected: // シリアル化からのみ作成します。
	CWinOGLView() noexcept;
	DECLARE_DYNCREATE(CWinOGLView)

// 属性
public:
	CWinOGLDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CWinOGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 左クリック時
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 右クリック時
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// マウスを動かしたとき
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private:
	HGLRC m_hRC;

	// 左クリックしたx座標を格納
	float x_Ldown;
	// 左クリックしたy座標を格納
	float y_Ldown;
	// 右クリックしたx座標を格納
	float x_Rdown;
	// 右クリックしたy座標を格納
	float y_Rdown;
	// 現在のマウスのx座標を格納
	float x_now;
	// 現在のマウスのy座標を格納
	float y_now;

	// CAdminControlクラス
	CAdminControl AC;


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // WinOGLView.cpp のデバッグ バージョン
inline CWinOGLDoc* CWinOGLView::GetDocument() const
   { return reinterpret_cast<CWinOGLDoc*>(m_pDocument); }
#endif

