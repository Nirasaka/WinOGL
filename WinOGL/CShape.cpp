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

// �擪�̒��_����������
void CShape::SetVertexHead(CVertex* new_vh)
{
	vertex_head = new_vh;
}

// �擪�̒��_��ǂݍ���
CVertex* CShape::GetVertexHead()
{
	return vertex_head;
}

// �����̒��_����������
void CShape::SetVertexTail(CVertex* new_vt)
{
	vertex_tail = new_vt;
}

// �����̒��_��ǂݍ���
CVertex* CShape::GetVertexTail()
{
	return vertex_tail;
}

// ���̌`�����������
void CShape::SetNextShape(CShape* new_sp)
{
	next_shape = new_sp;
}

// ���̌`���ǂݍ���
CShape* CShape::GetNextShape()
{
	return next_shape;
}

// �O�̌`�����������
void CShape::SetBehindShape(CShape* new_sp)
{
	behind_shape = new_sp;
}

// �O�̌`���ǂݍ���
CShape* CShape::GetBehindShape()
{
	return behind_shape;
}

// ���Ă��邩�ǂ���
bool CShape::IsShapeClosed()
{
	// �_��4�ȏ�̏ꍇ(�}�`���\������_�ƕ������ɒǉ������_)
	bool a = this->GetVerticesNum() >= 3 + 1;
	// x���W��y���W������
	bool b = vertex_head->GetX() == vertex_tail->GetX() && vertex_head->GetY() == vertex_tail->GetY();
	return a && b;
}

// �`��̒��_�̐���Ԃ�
int CShape::GetVerticesNum()
{
	int cnt = 0;
	for (CVertex* vp = vertex_head; vp != NULL; vp = vp->GetNext()) cnt++;
	return cnt;
}

// ���X�g���������
void CShape::FreeShape()
{
	CShape* nowS = this;
	while (nowS != NULL) {
		CShape* del_cell = nowS;
		nowS = nowS->GetNextShape();
		delete del_cell;
	}
}
