#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateShaftPart(MbSolid*& pSolidShaft, double start, double length, double radius) {
	// ����������� ������ ��� ����������
	MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);

	// ������ ������� ����� ��� ���������� ��������
	SArray<MbCartPoint3D> points(3);

	// ��������� �� �������� ������� �� 50 ������ �� ��� Y ������� ��
	points.Add(MbCartPoint3D(0, 0, start));
	// ����������� ��� Z ��������� �� ��������� � ������������
	// ��� Z ������� ��, ������ �������� ����� 10 ��������
	points.Add(MbCartPoint3D(0, 0, start + length));
	// ����������� ��� X ��������� �� ��������� � ������������ ��� X
	// ������� ��, ������ �������� ����� 10 ��������
	points.Add(MbCartPoint3D(radius, 0, start));
	// ���������� ������������� ���� � �������� - �� ���� ������
	MbSolid* pCyl = NULL;
	::ElementarySolid(points, et_Cylinder, names, pCyl);

	// ���������� ������������ ���� � ����
	if (pCyl) {
		if (pSolidShaft) {
			MbBooleanFlags flagsBool;
			flagsBool.InitBoolean(true);
			flagsBool.SetMergingFaces(true);
			flagsBool.SetMergingEdges(true);
			MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

			MbResultType res = ::BooleanResult(*pCyl, cm_Copy, *pSolidShaft, cm_Copy, bo_Union, flagsBool, operBoolNames, pSolidShaft);

			// ���������� �������� ������ ����������� ���������� ������� ����
			//
			::DeleteItem(pCyl);
		}
		else {
			pSolidShaft = pCyl;
		}
	}
}

void ParametricModelCreator::CreateShaft(MbAssembly* pAsm, double length, double ratio) {
	MbSolid* shaft = nullptr;

	//����
	CreateShaftPart(shaft, 0, length + 66.8, 10 * ratio);
	CreateShaftPart(shaft, length + 66.8, 9, 9.4 * ratio);
	CreateShaftPart(shaft, length + 75.8, 3.5, 6.9 * ratio);
	CreateShaftPart(shaft, length + 79.3, 28, 8 * ratio); // end with pivot
	// zero x , y , z 
	CreateShaftPart(shaft, 0, -5, 9.2 * ratio);
	CreateShaftPart(shaft, -5, -17.5, 7 * ratio);
	CreateShaftPart(shaft, -22.5, -3.2, 6.15 * ratio);
	CreateShaftPart(shaft, -25.7, -16, 7 * ratio); // end with collar
	//Shaft

	shaft->SetColor(RGB(130, 129, 128));
	pAsm->AddItem(*shaft);

	::DeleteItem(shaft);
}
