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
	// �_���X�g�̃w�b�h
	CVertex* vertex_head;
	// �_���X�g�̃e�[��
	CVertex* vertex_tail;

	// ���̌`��
	CShape* next_shape;
	// �O�̌`��
	CShape* behind_shape;


public:
	// �擪�̒��_����������
	void SetVertexHead(CVertex*);
	// �擪�̒��_��ǂݍ���
	CVertex* GetVertexHead();
	// �����̒��_����������
	void SetVertexTail(CVertex*);
	// �����̒��_��ǂݍ���
	CVertex* GetVertexTail();

	// ���̌`�����������
	void SetNextShape(CShape*);
	// ���̌`���ǂݍ���
	CShape* GetNextShape();
	// �O�̌`�����������
	void SetBehindShape(CShape*);
	// �O�̌`���ǂݍ���
	CShape* GetBehindShape();

	// ���Ă��邩�ǂ�����Ԃ�
	bool IsShapeClosed();
	// ���_�̐���Ԃ�
	int GetVerticesNum();

	// ���X�g���������
	void FreeShape();
};

