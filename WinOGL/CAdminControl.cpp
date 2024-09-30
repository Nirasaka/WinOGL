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
	// ���X�g�̓��e��`�悷��
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
		// �\������`��
		DrawForecast();
		// �}�E�X�|�C���^�`��
		DrawMousePointer();
	}
}

// �_�̕`��
void CAdminControl::DrawPoint(CVertex* vertex, bool closed)
{
	// �F�̐ݒ�
	if (closed) glColor3f(1.0, 1.0, 1.0);
	else		glColor3f(1.0, 0.0, 1.0);
	glPointSize(10.0);							// �_�̃T�C�Y
	glBegin(GL_POINTS);							// �_�̕`��J�n
	glVertex2f(vertex->GetX(), vertex->GetY());	// �_�`
	glEnd();									// �`��I��
}

// ���̕`��
void CAdminControl::DrawLine(CVertex* start, CVertex* end, bool closed)
{
	if (closed) glColor3f(1.0, 1.0, 1.0);
	else		glColor3f(1.0, 0.0, 1.0);
	glLineWidth(2.0);							// ���̑���
	glBegin(GL_LINE_STRIP);						// ���̕`��J�n
	glVertex2f(start->GetX(), start->GetY());	// ���`
	glVertex2f(end->GetX(), end->GetY());
	glEnd();
}

// �\������`��
void CAdminControl::DrawForecast()
{
	if (shape_head != NULL && !shape_tail->IsShapeClosed()) {
		glEnable(GL_LINE_STIPPLE);	// �j�����J�n
		glLineStipple(5, 0x5555);	// �j���̃p�����[�^
		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(2.0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(shape_tail->GetVertexTail()->GetX(), shape_tail->GetVertexTail()->GetY());
		glVertex2f(vertex_mouse->GetX(), vertex_mouse->GetY());
		glEnd();
		glDisable(GL_LINE_STIPPLE);	// �j�����I��
	}
}

// �}�E�X�|�C���^��`��
void CAdminControl::DrawMousePointer()
{
	int seg = 100;	// �ʂ̕�����
	float angle_step = (2.0 * 3.14159) / seg; //���������ʈ�̓��p
	float radius = 0.03;

	glColor3f(1.0, 1.0, 1.0);
	// ���邱�Ƃ��ł��Ȃ��ꍇ�̓}�E�X�|�C���^��Ԃ�����
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

// ���_�̒ǉ�
void CAdminControl::AddVertex(float x, float y)
{

	// �`�󃊃X�g����̎��A�`����쐬
	if (shape_head == NULL) {
		CShape* new_sp = new CShape;
		shape_head = new_sp;
		shape_tail = new_sp;
	}
	// �����̌`�󂪕��Ă��鎞�A�`����쐬
	else if (shape_tail->IsShapeClosed()) {
		CShape* new_sp = new CShape;
		shape_tail->SetNextShape(new_sp);
		new_sp->SetBehindShape(shape_tail);
		shape_tail = new_sp;
	}
	
	// �_���X�g����̎��A�擪�̒��_�ɐݒ�
	if (shape_tail->GetVertexHead() == NULL) {
		CVertex* new_vp = new CVertex(x, y, NULL, NULL);
		shape_tail->SetVertexHead(new_vp);
		shape_tail->SetVertexTail(new_vp);
	}
	else {
		CVertex* new_vp = new CVertex(x, y, NULL, NULL);
		// �}�`����邱�Ƃ��ł���ꍇ�͍��W�𓝈ꂷ��
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

// ���_�̍폜
void CAdminControl::DeleteVertex()
{
	// �`�󃊃X�g����łȂ��A���_���X�g����łȂ��Ƃ�
	if (shape_tail != NULL && shape_tail->GetVertexHead() != NULL) {
		// ���X�g���ɒ��_��1�����Ȃ���
		if (shape_tail->GetVertexHead() == shape_tail->GetVertexTail()) {
			// ���X�g���Ɍ`��1�����Ȃ��Ƃ�
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

// �}�E�X�̈ʒu���擾
void CAdminControl::GetMouseVertex(float x, float y)
{
	vertex_mouse->SetX(x);
	vertex_mouse->SetY(y);
}

// 2�̒��_�����ɋ߂����ǂ���
bool CAdminControl::IsBetweenVerticesShort(CVertex* vp1, CVertex* vp2)
{
	float d = 0.05;
	return ((vp2->GetX() - vp1->GetX()) * (vp2->GetX() - vp1->GetX()) + (vp2->GetY() - vp1->GetY()) * (vp2->GetY() - vp1->GetY()) <= d*d);
}


///////////////////////////////
//������
///////////////////////////////
// ���ł_(���݂̃}�E�X�̈ʒu)�ŕ��邱�Ƃ��ł��邩�ǂ���
bool CAdminControl::CanShapeClose()
{
	// �}�`�����Ă��炸
	// �������̌`��̐擪�̓_�Ƌ߂�
	// �������̌`��̒��_��3�ȏ�̎�
	return (!shape_tail->IsShapeClosed()
		&& IsBetweenVerticesShort(shape_tail->GetVertexHead(), vertex_mouse)
		&& shape_tail->GetVerticesNum() >= 3);
}
