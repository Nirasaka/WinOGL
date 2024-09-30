#include "pch.h"
#include "CAdminControl.h"

CAdminControl::CAdminControl() {
	shape_head = NULL;
	shape_tail = NULL;
	vertex_mouse = new CVertex;
}

CAdminControl::~CAdminControl() {
	shape_head->FreeShape();
	vertex_mouse->FreeVertex();
}

void CAdminControl::Draw() {
	// リストの内容を描画する
	if (shape_head != NULL) {
		CShape* sp;
		for (sp = shape_head; sp != NULL; sp = sp->GetNextShape()) {
			CVertex* vp;
			for (vp = sp->GetVertexHead(); vp->GetNext() != NULL; vp = vp->GetNext()) {
				DrawPoint(vp, sp->IsShapeClosed());
				DrawLine(vp, vp->GetNext(), sp->IsShapeClosed());
			}
			DrawPoint(vp, sp->IsShapeClosed());
		}
		// 予測線を描画
		DrawForecast();
		// マウスポインタ描画
		DrawMousePointer();
	}
}

// 点の描画
void CAdminControl::DrawPoint(CVertex* vertex, bool closed)
{
	// 色の設定
	if (closed) glColor3f(1.0, 1.0, 1.0);
	else		glColor3f(1.0, 0.0, 1.0);
	glPointSize(10.0);							// 点のサイズ
	glBegin(GL_POINTS);							// 点の描画開始
	glVertex2f(vertex->GetX(), vertex->GetY());	// 点描
	glEnd();									// 描画終了
}

// 線の描画
void CAdminControl::DrawLine(CVertex* start, CVertex* end, bool closed)
{
	if (closed) glColor3f(1.0, 1.0, 1.0);
	else		glColor3f(1.0, 0.0, 1.0);
	glLineWidth(2.0);							// 線の太さ
	glBegin(GL_LINE_STRIP);						// 線の描画開始
	glVertex2f(start->GetX(), start->GetY());	// 線描
	glVertex2f(end->GetX(), end->GetY());
	glEnd();
}

// 予測線を描画
void CAdminControl::DrawForecast()
{
	if (shape_head != NULL && !shape_tail->IsShapeClosed()) {
		glEnable(GL_LINE_STIPPLE);	// 破線を開始
		glLineStipple(5, 0x5555);	// 破線のパラメータ
		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(2.0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(shape_tail->GetVertexTail()->GetX(), shape_tail->GetVertexTail()->GetY());
		glVertex2f(vertex_mouse->GetX(), vertex_mouse->GetY());
		glEnd();
		glDisable(GL_LINE_STIPPLE);	// 破線を終了
	}
}

// マウスポインタを描画
void CAdminControl::DrawMousePointer()
{
	int seg = 100;	// 弧の分割数
	float angle_step = (2.0 * 3.14159) / seg; //分割した弧一つの内角
	float radius = 0.03;

	glColor3f(1.0, 1.0, 1.0);
	// 閉じることができない場合はマウスポインタを赤くする
	if (!shape_tail->IsShapeClosed()
		&& IsBetweenVerticesShort(shape_tail->GetVertexHead(), vertex_mouse)
		&& shape_tail->GetVerticesNum() < 3) {
			glColor3f(1.0, 0.0, 0.0);
	}

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= seg; i++) {
		float angle = i * angle_step;
		float x = vertex_mouse->GetX() + cosf(angle) * radius;
		float y = vertex_mouse->GetY() + sinf(angle) * radius;
		glVertex2f(x, y);
	}
	glEnd();
}

// 頂点の追加
void CAdminControl::AddVertex(float x, float y)
{

	// 形状リストが空の時、形状を作成
	if (shape_head == NULL) {
		CShape* new_sp = new CShape;
		shape_head = new_sp;
		shape_tail = new_sp;
	}
	// 末尾の形状が閉じている時、形状を作成
	else if (shape_tail->IsShapeClosed()) {
		CShape* new_sp = new CShape;
		shape_tail->SetNextShape(new_sp);
		new_sp->SetBehindShape(shape_tail);
		shape_tail = new_sp;
	}
	
	// 点リストが空の時、先頭の頂点に設定
	if (shape_tail->GetVertexHead() == NULL) {
		CVertex* new_vp = new CVertex(x, y, NULL, NULL);
		shape_tail->SetVertexHead(new_vp);
		shape_tail->SetVertexTail(new_vp);
	}
	else {
		CVertex* new_vp = new CVertex(x, y, NULL, NULL);
		// 図形を閉じることができる場合は座標を統一する
		CVertex* vp = shape_tail->GetVertexHead();
		if (IsBetweenVerticesShort(vp, new_vp)) { 
			if (shape_tail->GetVerticesNum() < 3) return;
			new_vp->SetX(vp->GetX());
			new_vp->SetY(vp->GetY());
		}

		vp = shape_tail->GetVertexTail();
		vp->SetNext(new_vp);
		new_vp->SetBehind(vp);
		shape_tail->SetVertexTail(new_vp);
	}
}

// 頂点の削除
void CAdminControl::DeleteVertex()
{
	// 形状リストが空でなく、頂点リストが空でないとき
	if (shape_tail != NULL && shape_tail->GetVertexHead() != NULL) {
		// リスト内に頂点が1つしかない時
		if (shape_tail->GetVertexHead() == shape_tail->GetVertexTail()) {
			// リスト内に形状が1つしかないとき
			if (shape_head == shape_tail) {
				shape_head->FreeShape();
				shape_head = NULL;
				shape_tail = NULL;
			}
			else {
				shape_tail = shape_tail->GetBehindShape();
				shape_tail->GetNextShape()->FreeShape();
				shape_tail->SetNextShape(NULL);
			}
		}
		else {
			shape_tail->SetVertexTail(shape_tail->GetVertexTail()->GetBehind());
			shape_tail->GetVertexTail()->GetNext()->FreeVertex();
			shape_tail->GetVertexTail()->SetNext(NULL);
		}
	}
}

// マウスの位置を取得
void CAdminControl::GetMouseVertex(float x, float y)
{
	vertex_mouse->SetX(x);
	vertex_mouse->SetY(y);
}

// 2つの頂点が非常に近いかどうか
bool CAdminControl::IsBetweenVerticesShort(CVertex* vp1, CVertex* vp2)
{
	float d = 0.05;
	return ((vp2->GetX() - vp1->GetX()) * (vp2->GetX() - vp1->GetX()) + (vp2->GetY() - vp1->GetY()) * (vp2->GetY() - vp1->GetY()) <= d*d);
}


///////////////////////////////
//未完成
///////////////////////////////
// 次打つ点(現在のマウスの位置)で閉じることができるかどうか
bool CAdminControl::CanShapeClose()
{
	// 図形が閉じておらず
	// かつ末尾の形状の先頭の点と近く
	// かつ末尾の形状の長点数3以上の時
	return (!shape_tail->IsShapeClosed()
		&& IsBetweenVerticesShort(shape_tail->GetVertexHead(), vertex_mouse)
		&& shape_tail->GetVerticesNum() >= 3);
}
