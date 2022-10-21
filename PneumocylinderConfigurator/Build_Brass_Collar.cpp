#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchCollar(RPArray<MbContour>& _arrContours,double ratio)
{
	// �������� ������� ����� ��������, � �������� � ���������� ��������� ����������.
	SArray<MbCartPoint> arrPnts(7);
	arrPnts.Add(MbCartPoint(0, 10.05 * ratio));
	arrPnts.Add(MbCartPoint(0, 11 * ratio));
	arrPnts.Add(MbCartPoint(3, 12.25 * ratio));
	arrPnts.Add(MbCartPoint(32, 12.25 * ratio));
	arrPnts.Add(MbCartPoint(32, 9.25 * ratio));
	arrPnts.Add(MbCartPoint(27, 9.25 * ratio));
	arrPnts.Add(MbCartPoint(27, 10.05 * ratio));

	// ���������� ������ ������� �������� ������� �� ������
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
	MbContour* pContourPolyline = new MbContour();

	pContourPolyline->AddSegment(pPolyline);

	_arrContours.push_back(pContourPolyline);

	::DeleteItem(pPolyline);
}

void ParametricModelCreator::CreateBrassCollar(MbAssembly* pAsm, double ratio) {
	// ��������� ��� �������������� ������� �������� �� �������� � �������
	const double DEG_TO_RAD = M_PI / 180.0;

	// ��������� �� (�� ��������� ��������� � ������� ��)
	MbPlacement3D pl;

	// ����� ������� ��� ���������� ���������� (�� ������� 6)
	RPArray<MbContour> arrContours;
	CreateSketchCollar(arrContours, ratio);


	// ���������� ���������� ��� ������ ������� ���������� ���� ��������.
	// sweptData - ������, � ������� �������� �������� �� ����������.
	MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
		MbCartPoint3D(0, 1, 0));
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

	// ��������� ������ ������ ���������� ���� � ����������� ��������� ("�������").
	// revParms.shellClosed = false;
	// ������� ������� ������ ����
	// revParms.thickness1 = 8;

	// ����������� ��� �������� ���������� ���� �������� � ��� �������� ����������
	MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames(0, 1, false);

	// ��� �������� ��� ���������� ����:
	// ��� Y ������� �� ��������� �� -50 ������ ����� ��� X.
	MbAxis3D axis(pl.GetAxisX());


	// ����� �������-������� ��� ���������� �������� ���� ��������
	MbSolid* pSolid = nullptr;
	MbResultType res = ::RevolutionSolid(sweptData, axis, revParms,
		operNames, cNames, pSolid);

	// ����������� ������������ ����
	MbAxis3D axVert(MbVector3D(0, 1, 0));
	pSolid->Rotate(axVert, M_PI / 2);
	pSolid->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 27)));
	if (res == rt_Success) {
		pSolid->SetColor(LIGHTGRAY);
		pAsm->AddItem(*pSolid);
		//viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
	}



	// ���������� ��������� ������ ������������ �������� ����
	::DeleteItem(pSolid);
}