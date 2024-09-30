#include "pch.h"
#pragma once

class CVertex
{
public:
	CVertex();
	CVertex(float new_x, float new_y, CVertex* new_next, CVertex* new_behind);
	~CVertex();

private:
	// ���W
	float x, y;
	// ���̒��_
	CVertex* next_vertex;
	// �O�̒��_
	CVertex* behind_vertex;

public:
	// ���_��X���W����������
	void SetX(float);
	// ���_��Y���W����������
	void SetY(float);
	// ���_��X���W��ǂݍ���
	float GetX();
	// ���_��Y���W��ǂݍ���
	float GetY();

	// ���̒��_���X�g���w���|�C���^����������
	void SetNext(CVertex*);
	// ���̒��_���X�g���w���|�C���^��ǂݍ���
	CVertex* GetNext();
	// �O�̒��_���X�g���w���|�C���^����������
	void SetBehind(CVertex*);
	// �O�̒��_���X�g���w���|�C���^��ǂݍ���
	CVertex* GetBehind();

	// ���X�g���������
	void FreeVertex();
};

