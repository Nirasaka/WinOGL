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

// ���_��X���W����������
void CVertex::SetX(float new_x)
{
	x = new_x;
}

// ���_��Y���W����������
void CVertex::SetY(float new_y)
{
	y = new_y;
}

// ���_��X���W��ǂݍ���
float CVertex::GetX()
{
	return x;
}

// ���_��Y���W��ǂݍ���
float CVertex::GetY()
{
	return y;
}

// ���̒��_���X�g���w���|�C���^����������
void CVertex::SetNext(CVertex* new_next)
{
	next_vertex = new_next;
}

// ���̒��_���X�g���w���|�C���^��ǂݍ���
CVertex* CVertex::GetNext()
{
	return next_vertex;
}

// �O�̒��_���X�g���w���|�C���^����������
void CVertex::SetBehind(CVertex* new_behind)
{
	behind_vertex = new_behind;
}

// �O�̒��_���X�g���w���|�C���^��ǂݍ���
CVertex* CVertex::GetBehind()
{
	return behind_vertex;
}

// ���X�g���������
void CVertex::FreeVertex()
{
	CVertex* nowV = this;
	while (nowV != NULL) {
		CVertex* del_cell = nowV;
		nowV = nowV->GetNext();
		delete del_cell;
	}
}