#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchEgor(RPArray<MbContour>& _arrContours, double ratio)
{
	// �������� ������� ����� ��������, � �������� � ���������� ��������� ����������.
	SArray<MbCartPoint> arrPnts(8);
	arrPnts.Add(MbCartPoint(0, 0 ));
	arrPnts.Add(MbCartPoint(0, 10 * ratio));
	arrPnts.Add(MbCartPoint(27, 10 * ratio));
	arrPnts.Add(MbCartPoint(28, 9.25 * ratio));
	arrPnts.Add(MbCartPoint(32, 9.25 * ratio));
	arrPnts.Add(MbCartPoint(32, 7 * ratio));
	arrPnts.Add(MbCartPoint(9.5, 7 * ratio));
	arrPnts.Add(MbCartPoint(8.5, 0 ));

	// ���������� ������ ������� �������� ������� �� ������
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);

	MbContour* pContourPolyline = new MbContour();

	pContourPolyline->AddSegment(pPolyline);

	_arrContours.push_back(pContourPolyline);
	::DeleteItem(pPolyline);
}
void CreateSketchEgor2(RPArray<MbContour>& _arrContours, double R = 5.125)
{
	// �������� ������� ����� ��������, � �������� � ���������� ��������� ����������.
	// ������ ������� - 8 ����� ��� ����� ����� ������� ��������� ����������.
	SArray<MbCartPoint> arrPnts(12);
	const double DEG_TO_RAD1 = M_PI / 180.0;
	
	arrPnts.Add(MbCartPoint(R * cos(0 * DEG_TO_RAD1), R * sin(0 * DEG_TO_RAD1)));
	arrPnts.Add(MbCartPoint(R * cos(60 * DEG_TO_RAD1), R * sin(60 * DEG_TO_RAD1)));

	arrPnts.Add(MbCartPoint(R * cos(120 * DEG_TO_RAD1), R * sin(120 * DEG_TO_RAD1)));
	arrPnts.Add(MbCartPoint(R * cos(180 * DEG_TO_RAD1), R * sin(180 * DEG_TO_RAD1)));
	arrPnts.Add(MbCartPoint(R * cos(240 * DEG_TO_RAD1), R * sin(240 * DEG_TO_RAD1)));
	arrPnts.Add(MbCartPoint(R * cos(300 * DEG_TO_RAD1), R * sin(300 * DEG_TO_RAD1)));

	// ���������� ������ ������� �������� ������� �� ������
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);

	MbContour* pContourPolyline = new MbContour();
	pContourPolyline->AddSegment(pPolyline);

	_arrContours.push_back(pContourPolyline);
	::DeleteItem(pPolyline);
}

void ParametricModelCreator::CreateSocketHeadCollar(MbAssembly* pAsm, double ratio)
{
	// ��������� ��� �������������� ������� �������� �� �������� � �������
	const double DEG_TO_RAD = M_PI / 180.0;

	// ��������� �� (�� ��������� ��������� � ������� ��)
	MbPlacement3D pl;

	// ����� ������� ��� ���������� ���������� (�� ������� 6)
	RPArray<MbContour> arrContours;
	CreateSketchEgor(arrContours, ratio);

	// ����������� ���������� (� ��������� XY ���������� ��)


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
	

	//switch 

	MbPlacement3D pl1;
	RPArray<MbContour> arrContours1;
	
	double R = 5.125;
	if(ratio < 0.8)R *= 0.5;
	CreateSketchEgor2(arrContours1,R);

	//������ ������ �� ����� � ������
	//for (int i = 0; i < arrContours1.size(); i++)
		//viewManager->AddObject(Style(1, RGB(0, 0, 255)), arrContours1[i], &pl1);

	MbPlane* pPlaneYZ = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 1), MbCartPoint3D(0, 1, 0));
	// ������, �������� ��������� ����������
	MbSweptData sweptData1(*pPlaneYZ, arrContours1);
	// ������������ ������ ��� �������� ������������
	MbVector3D dir(1, 0, 0);

	const double HEIGHT_FORWARD = 10, HEIGHT_BACKWARD = 0;
	const double ANGLE_FORWARD_DEGREE = 0;
	ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);
	// �������� ������ ��� ������������ � ������ �����������
	extrusionParams.side1.rake = ANGLE_FORWARD_DEGREE * M_PI / 180;

	MbSNameMaker operNames1(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames1(0, 1, false);

	MbSolid* pSolid1 = nullptr;
	MbResultType res1 = ::ExtrusionSolid(sweptData1, dir, nullptr, nullptr, false, extrusionParams, operNames1, cNames1, pSolid1);

	// ����������� ������������ ����
   // ���������� ��������� ������ ����������� ��������� �������� ����



	// ����������� ������ ��� ���������� ���� � ������� ������� �������� 
	MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

	// ����� ������� ��������: ���������� ���������� ���� � ������������
	// �������� ������ � �����.
	MbBooleanFlags flagsBool;
	flagsBool.InitBoolean(true);
	flagsBool.SetMergingFaces(true);
	flagsBool.SetMergingEdges(true);

	// �������������� ����
	MbSolid* pSolid2 = nullptr;
	// ����� ������� �������� ��� ���������� �����������.
	// ��� ���������� ��������� ���� ������ ���� �������� bo_Union �������
	// �������� bo_Difference, ��� ����������� - �������� bo_Intersect.
	MbResultType res2 = ::BooleanResult(*pSolid, cm_Copy, *pSolid1, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid2);

	MbAxis3D axVert(MbVector3D(0, 1, 0));
	MbAxis3D axVertX(MbVector3D(1, 0, 0));
	// ����������� ��������������� ����
	if (res2 == rt_Success) {
		pSolid2->Rotate(axVert, M_PI / 2);
		pSolid2->Rotate(axVertX, M_PI);
		pSolid2->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -54)));

		pSolid2->SetColor(ParametricModelCreator::colorScheme ? LIGHTGRAY : BLACK);
		pAsm->AddItem(*pSolid2);
		//viewManager->AddObject(Style(1, LIGHTGRAY), pSolid2);
	}
	// ���������� ��������� ������ ������������ �������� ����
	::DeleteItem(pSolid1);

	::DeleteItem(pSolid);
	::DeleteItem(pSolid2);
}