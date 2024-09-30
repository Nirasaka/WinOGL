
// WinOGLView.cpp : CWinOGLView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView() noexcept
{
	x_Ldown = 0.0;
	y_Ldown = 0.0;
	x_Rdown = 0.0;
	y_Rdown = 0.0;
	x_now = 0.0;
	y_now = 0.0;

}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画

void CWinOGLView::OnDraw(CDC* pDC)
{
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(pDC->m_hDC, m_hRC);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT /* | GL_DEPTH_BUFFER_BIT*/);

	AC.Draw(); // 描画

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, NULL);
}


// CWinOGLView の診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー

// 左クリック時
void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 描画領域の大きさを取得
	CRect rect;
	GetClientRect(rect);

	// 画面が横長の時
	if (rect.Width() > rect.Height()) { 
		x_Ldown = (1.0 * point.x / rect.Width() * 2 - 1.0) * rect.Width() / rect.Height();
		y_Ldown = -1.0 * point.y / rect.Height() * 2 + 1.0;
	}
	// 画面が縦長の時
	else {
		x_Ldown = 1.0 * point.x / rect.Width() * 2 - 1.0;
		y_Ldown = (-1.0 * point.y / rect.Height() * 2 + 1.0) * rect.Height() / rect.Width();
	}
	// 頂点をリストへ追加
	AC.AddVertex(x_Ldown, y_Ldown);

	RedrawWindow();
	CView::OnLButtonDown(nFlags, point);
}


// 右クリック時
void CWinOGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	//// 描画領域の大きさを取得
	//CRect rect;
	//GetClientRect(rect);

	//// 画面が横長の時
	//if (rect.Width() > rect.Height()) {
	//	x_Rdown = (1.0 * point.x / rect.Width() * 2 - 1.0) * rect.Width() / rect.Height();
	//	y_Rdown = -1.0 * point.y / rect.Height() * 2 + 1.0;
	//}
	//// 画面が縦長の時
	//else {
	//	x_Rdown = 1.0 * point.x / rect.Width() * 2 - 1.0;
	//	y_Rdown = (-1.0 * point.y / rect.Height() * 2 + 1.0) * rect.Height() / rect.Width();
	//}

	// 頂点を削除
	AC.DeleteVertex();

	RedrawWindow();
	CView::OnRButtonDown(nFlags, point);
}

// マウスを動かしたとき
void CWinOGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// 描画領域の大きさを取得
	CRect rect;
	GetClientRect(rect);

	// 画面が横長の時
	if (rect.Width() > rect.Height()) {
		x_now = (1.0 * point.x / rect.Width() * 2 - 1.0) * rect.Width() / rect.Height();
		y_now = -1.0 * point.y / rect.Height() * 2 + 1.0;
	}
	// 画面が縦長の時
	else {
		x_now = 1.0 * point.x / rect.Width() * 2 - 1.0;
		y_now = (-1.0 * point.y / rect.Height() * 2 + 1.0) * rect.Height() / rect.Width();
	}

	// 現在のマウスの座標を渡す
	AC.GetMouseVertex(x_now, y_now);

	RedrawWindow();
	CView::OnMouseMove(nFlags, point);
}

// ウィンドウ作成時
int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | 
		PFD_SUPPORT_OPENGL | 
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		24,
		0,0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};
	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC, &pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}

// ウィンドウ破壊時
void CWinOGLView::OnDestroy()
{
	CView::OnDestroy();
	wglDeleteContext(m_hRC);
}


BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

// ウィンドウサイズ変更時
void CWinOGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 課題1
	 // 画面が横長の時
	if(cx > cy) glOrtho( -1.0 * cx / cy, 1.0 * cx / cy, -1.0, 1.0, -100.0, 100.0);
	// 画面が縦長の時
	else  glOrtho(-1.0, 1.0, -1.0 * cy / cx, 1.0 * cy / cx, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}




