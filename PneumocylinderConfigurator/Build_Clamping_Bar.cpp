#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchEgorClampingBar(RPArray<MbContour>& _arrContours, double length)
{
	// �������� ������� ����� ��������, � �������� � ���������� ��������� ����������.
	// ������ ������� - 8 ����� ��� ����� ����� ������� ��������� ����������.
	SArray<MbCartPoint> arrPnts(10);
	arrPnts.Add(MbCartPoint(0, 0));
	arrPnts.Add(MbCartPoint(0, 3.5));
	arrPnts.Add(MbCartPoint(0.5, 4));
	arrPnts.Add(MbCartPoint(10, 4));
	arrPnts.Add(MbCartPoint(10, 3.5));
	arrPnts.Add(MbCartPoint(length + 70, 3.5));
	arrPnts.Add(MbCartPoint(length + 70, 4));
	arrPnts.Add(MbCartPoint(length + 79.5, 4));
	arrPnts.Add(MbCartPoint(length + 80, 3.5));
	arrPnts.Add(MbCartPoint(length + 80, 0));

	// ���������� ������ ������� �������� ������� �� ������
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
	MbContour* pContourPolyline = new MbContour();

	pContourPolyline->AddSegment(pPolyline);

	_arrContours.push_back(pContourPolyline);
	::DeleteItem(pPolyline);
}

void ParametricModelCreator::CreateClampingBar(MbAssembly* pAsm, double X, double Y, double length)
{
	// ��������� ��� �������������� ������� �������� �� �������� � �������
	const double DEG_TO_RAD = M_PI / 180.0;

	// ��������� �� (�� ��������� ��������� � ������� ��)
	MbPlacement3D pl;

	// ����� ������� ��� ���������� ���������� (�� ������� 6)
	RPArray<MbContour> arrContours;
	CreateSketchEgorClampingBar(arrContours, length);

	// ���������� ���������� ��� ������ ������� ���������� ���� ��������.
	// sweptData - ������, � ������� �������� �������� �� ����������.
	MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 1),
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
	MbAxis3D axis(pl.GetAxisZ());


	// ����� �������-������� ��� ���������� �������� ���� ��������
	MbSolid* pSolid = nullptr;
	MbResultType res = ::RevolutionSolid(sweptData, axis, revParms,
		operNames, cNames, pSolid);

	// ����������� ������������ ����
	MbAxis3D axVert(MbVector3D(0, 1, 0));
	//pSolid->Rotate(axVert, -M_PI / 2);
	pSolid->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(X, Y, -49.525)));
	if (res == rt_Success) {
		pSolid->SetColor(ParametricModelCreator::colorScheme ? RGB(78, 81, 81) : RGB(65, 45, 10));//BROWN
		pAsm->AddItem(*pSolid);
		//viewManager->AddObject(Style(1, BROWN), pSolid);
	}


	// ���������� ��������� ������ ������������ �������� ����
	::DeleteItem(pSolid);
	//::DeleteItem(pPlaneXY);

}