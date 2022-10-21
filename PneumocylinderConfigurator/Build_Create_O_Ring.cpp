#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void ParametricModelCreator::CreateORing(MbAssembly* pAsm, double Z, double ratio) {

	MbPlacement3D pl;

	// ����� ����������� � ��� � ��������� ��
	MbCartPoint cnt(0, 22.575*ratio);
	// ���������� ���������� �� ������ � �������
	const double RAD1 = 1.325;
	MbArc* circle1 = new MbArc(cnt, RAD1);
	MbContour* pContour = new MbContour();
	pContour->AddSegment(circle1);
	// ��������� ��� �������������� ������� �������� �� �������� � �������
	const double DEG_TO_RAD = M_PI / 180.0;

	RPArray<MbContour> arrContours;
	arrContours.push_back(pContour);
	// ���������� ���������� ��� ������ ������� ���������� ���� ��������.

	MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
	MbSweptData sweptData(*pPlaneXY, arrContours);

	// ������ ���������� ��� �������� ���������� ���� ��������.
	// ������ ��� ��������� ������������ ������ ���� �������� � ������ � ��������
	// ����������� (�� ������� � ���������� ��� �������������� ���� �������).
	// � ������ ������� �������� �������������� �� 120 �������� � ������ �����������.
	// ������ �������� ������ ����� ��������� �������� ����.
	// ��� s = 0 �������� ���� � ���������� �����, ��� s = 1 - � ���������� ����.
	// ���� ���������� - ����������� ������, � ��� �������� ����� � ��������� ������,
	// �� ��� s = 0 ��� ���������� ���������� ����� ������������� �������� �� ���
	// ��������. � ������ ������� �������� ����� ���������� s ���, �.�. ����������
	// ����� ��� ���������� �������.
	RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);



	// ����������� ��� �������� ���������� ���� �������� � ��� �������� ����������
	MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames(0, 1, false);

	// ��� �������� ��� ���������� ����:
	// ��� Y ������� �� ��������� �� -50 ������ ����� ��� X.
	MbAxis3D axis(pl.GetAxisX());

	// ����� �������-������� ��� ���������� �������� ���� ��������
	MbSolid* pSolid = nullptr;
	MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pSolid);

	// ����������� ������������ ����
	MbAxis3D axVert(MbVector3D(0, 1, 0));
	pSolid->Rotate(axVert, -M_PI / 2);
	pSolid->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, Z)));

	pSolid->SetColor(BLACK);
	pAsm->AddItem(*pSolid);
	//viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);


	::DeleteItem(circle1);
	::DeleteItem(pSolid);
}