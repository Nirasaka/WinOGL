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
	// �`�󃊃X�g�̃w�b�h
	CShape* shape_head;
	// �`�󃊃X�g�̃e�[��
	CShape* shape_tail;
	// �_�̕`��
	void DrawPoint(CVertex* vertex, bool closed);
	// ���̕`��
	void DrawLine(CVertex* start, CVertex* end ,bool closed);
	// �\������`��
	void DrawForecast();
	// �}�E�X�|�C���^��`��
	void DrawMousePointer();
	
	// ���݂̃}�E�X�̈ʒu���i�[
	CVertex* vertex_mouse;

public:
	// �`��
	void Draw();
	// ���_�̒ǉ�
	void AddVertex(float, float);
	// ���_�̍폜
	void DeleteVertex();
	// �}�E�X�̈ʒu���擾
	void GetMouseVertex(float, float);
	// 2�̒��_�����ɋ߂����ǂ���
	bool IsBetweenVerticesShort(CVertex*, CVertex*);
	// ���ł_�ŕ��邱�Ƃ��ł��邩�ǂ���
	bool CanShapeClose();
};

/*
�Z�����������K
1,2,3

�Z�I���W�i���e�B
�E�`�󂪕��Ă���Ƃ��ɐF��ς���悤�ɕύX�B(�\���e�X�g�p)
�EIsShapeClosed�F�`�󂪕��Ă��邩�ǂ�����Ԃ�CShape�N���X�֐�
�EIsBetweenVerticesShort �FCVertex*�^�̒��_2�̋��������ɋ߂����ǂ�����Ԃ�CAdminControl�N���X�֐�
�@						 �@�`�����邩�ǂ����̔���Ɏg�p���Ă���A���㒸�_�̑I���Ɋ��p�\��B
�EGetVerticesNum�F�`�󂪎����_�̐���Ԃ�CShape�N���X�֐�
�EGetMouseVertex�F�}�E�X�̈ʒu���擾����CAdminControl�N���X�֐�
�EDrawForecast�F�\������`��
�EDrawMousePointer�F�}�E�X�|�C���^��`��
�EIsBetweenVerticesShort�F2�̒��_�����ɋ߂����ǂ�����Ԃ�CAdminControl�N���X�֐�

*/
