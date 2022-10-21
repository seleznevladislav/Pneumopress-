#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchShaftPivot(RPArray<MbContour>& _arrContours, double ratio)
{
	SArray<MbCartPoint> arrPnts(4);
	arrPnts.Add(MbCartPoint(12.5 * ratio, 12.5 * ratio));
	arrPnts.Add(MbCartPoint(12.5 * ratio, -12.5 * ratio));
	arrPnts.Add(MbCartPoint(-12.5 * ratio, -12.5 * ratio));
	arrPnts.Add(MbCartPoint(-12.5 * ratio, 12.5 * ratio));

	// ���������� ������ ������� �������� ������� �� ������
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
	MbContour* pContourPolyline = nullptr;

	// ������� ���������� � �������������� ������� FilletPolyContour
	::FilletPolyContour(pPolyline, 5 * ratio, false, arrPnts[0], pContourPolyline);

	// ������� �������� �����, � ������� ����� ���������� ���������� � ������
	// ���������� ����� ����� ��� ���������� � �������������� ������� FilletTwoSegments

	ptrdiff_t idxSideRight1 = 0;
	ptrdiff_t idxSideRight2 = 2;
	ptrdiff_t idxSideRight3 = 4;

	// ���������� ����������
	// 
	pContourPolyline->FilletTwoSegments(idxSideRight1, 5 * ratio);
	pContourPolyline->FilletTwoSegments(idxSideRight2, 5 * ratio);
	pContourPolyline->FilletTwoSegments(idxSideRight3, 5 * ratio);

	_arrContours.push_back(pContourPolyline);
	::DeleteItem(pPolyline);
}

void ParametricModelCreator::CreateShaftPivot(MbAssembly* pAsm, double position, double ratio)
{
	const double diamIn_STD = 8;
	const double sizeOut_STD = 12.5;
	double outRatio = ((sizeOut_STD - diamIn_STD) + (diamIn_STD * ratio)) / sizeOut_STD;

	//���������� ���������������    
	MbPlacement3D pl;

	// �������� ���������� ��� ���� ������������
	RPArray<MbContour> arrContours;
	CreateSketchShaftPivot(arrContours, outRatio);

	// ����������� ���������� (� ��������� XY ���������� ��)
	/*for (int i = 0; i<arrContours.size(); i++)
		show( Style(1, LIGHTRED), arrContours[i], &pl);
	*/
	// ���������� ���� ������������
	MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 0, 1));
	// ������, �������� ��������� ����������
	MbSweptData sweptData(*pPlaneXZ, arrContours);
	// ������������ ������ ��� �������� ������������
	MbVector3D dir(0, 1, 0);

	// ��������� �������� ������������, �������� �������� ���� ��� ���������� � ������ � � �������� ����������� ����� (������� ������������ � �����).
	const double HEIGHT_FORWARD = 0, HEIGHT_BACKWARD = 39;
	ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

	// ����������� ��������� ������ �������� ���� � �������� ����������
	MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames(0, 1, false);

	// ����� �������-������� ��� ���������� �������� ���� ������������
	MbSolid* pSolid = nullptr;
	MbResultType res = ::ExtrusionSolid(sweptData, dir, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolid);


	//���������� ���������
	MbSolid* pBlockHole = NULL;
	{
		MbSNameMaker holeNames(ct_HoleSolid, MbSNameMaker::i_SideNone, 0);
		const double DEG_TO_RAD = M_PI / 180.0;
		MbPlacement3D plHole(MbCartPoint3D(0, 0, 0));
		plHole.Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0))),
			90 * DEG_TO_RAD);
		plHole.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -39, 0)));
		BorerValues params;

		params.type = BorerValues::bt_SimpleCylinder;

		params.diameter = 16* ratio;

		params.depth = 32;

		params.down = true;

		::HoleSolid(pSolid, cm_Copy, plHole, params, holeNames, pBlockHole);


	}

	//���������� �������� �����
	MbPlacement3D pl1;

	SArray<MbCartPoint> arrPnts1(4);
	arrPnts1.Add(MbCartPoint(-12.5 * outRatio, 14.5));
	arrPnts1.Add(MbCartPoint(-12.5 * outRatio, 0));
	arrPnts1.Add(MbCartPoint(12.5 * outRatio, 0));
	arrPnts1.Add(MbCartPoint(12.5 * outRatio, 14.5));

	MbPolyline* pPolyline1 = new MbPolyline(arrPnts1, false);

	MbCartPoint arcCenter(0, 14.5);
	const double RADIUS = 12.5 * outRatio;
	MbArc* pArc = new MbArc(arcCenter, RADIUS, arrPnts1[3], arrPnts1[0], 1);
	MbContour* pContour1 = new MbContour(*pPolyline1, true);
	pContour1->AddSegment(pArc);
	// ������ �������������� ������� �������
	size_t segmentsCount = pContour1->GetSegmentsCount(); // 2
	double tMin = pContour1->GetTMin(); // 0.0
	double tMax = pContour1->GetTMax(); // 10.14159
	// �������� IsSmoothConnected - ������ ��� ������������� ������� �����    �� �������
	bool isSmooth = pContour1->IsSmoothConnected(0.001); // false
	double length = pContour1->CalculateLength(tMin, tMax); // 302.83
	bool isClosed = pContour1->IsClosedContinuousC0(); // true
	bool isCurvilinear = pContour1->IsAnyCurvilinear(); // true
	// ���������� ���� ������������
	MbSweptData sweptData1(pl1, *pContour1);
	MbVector3D dir1(0, 0, 1);
	const double HEIGHT_FORWARD1 = 5, HEIGHT_BACKWARD1 = 5;
	ExtrusionValues extrusionParam(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);

	MbSNameMaker operNames1(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames1(0, 1, false);

	MbSolid* pSolid1 = NULL;
	MbResultType resCode = ::ExtrusionSolid(sweptData1, dir1, NULL, NULL, false,
		extrusionParam, operNames1, cNames1, pSolid1);


	//���������� ��������� � �������� �����
	MbSolid* pHole = NULL;
	{
		MbSNameMaker hole1Names(ct_HoleSolid, MbSNameMaker::i_SideNone, 0);

		MbPlacement3D pl1Hole(MbCartPoint3D(0, 0, 0));
		pl1Hole.Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 1, 0))), 0);
		pl1Hole.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 12.5, 5)));
		BorerValues params1;
		params1.type = BorerValues::bt_SimpleCylinder;

		params1.diameter = (int)(15*outRatio);//������ ��� ��������� ��� 1

		params1.depth = 10;

		params1.down = true;

		::HoleSolid(pSolid1, cm_Copy, pl1Hole, params1, hole1Names, pHole);
	}

	//����������� ���
	MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
	MbBooleanFlags flagsBool;
	flagsBool.InitBoolean(true);
	flagsBool.SetMergingFaces(true);
	flagsBool.SetMergingEdges(true);

	MbSolid* pSolidd = NULL;
	::BooleanResult(*pBlockHole, cm_Copy, *pHole, cm_Copy, bo_Union,
		flagsBool, operBoolNames, pSolidd);

	//����������    
	MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

	//�������� �������� ���������� �������� ���������� �����
	SmoothValues paramss;
	// ������� �������� �� ���� ����������� ������������
	paramss.distance1 = 3 * outRatio;
	paramss.distance2 = 3 * outRatio;
	// ��� ���������� � ���������� �� ���� ��������
	paramss.form = st_Fillet;
	// ����� ������� ���������� - ����������
	paramss.conic = 0;
	// ��������� ��������� ������ �����, ���������� �� ������� �������
	paramss.prolong = false;
	// ������ ���������� ����� �����
	paramss.smoothCorner = SmoothValues::ec_uniform;
	// ���� ���������� ������ � ����� ���������� �����������
	paramss.keepCant = ts_negative;
	// ������� ����������
	paramss.strict = true;

	//������������ ������� � ������� ��� ����������.
	// ������ ���� ����� ��������� ����
	RPArray<MbCurveEdge> allEdges(4, 1);
	pSolidd->GetEdges(allEdges);
	// � ������ ����� ��� ���������� ���������� ������ ���� �����
	RPArray<MbCurveEdge> initCurves(4, 1);
	initCurves.Add(allEdges[16]);
	initCurves.Add(allEdges[20]);

	//������ ������ ��� ������� � � ������ ������� ������
	RPArray<MbFace> initBounds(0, 1);

	//����� ������� ���������� �����.
	// � ���������� ����������� ���������� ������ ����� � ����������,
	// �� ������� � �������� ���� ��������� ������� � ��������.
	MbSolid* pResult = NULL;
	MbResultType ress = ::FilletSolid(*pSolidd, cm_Copy, initCurves, initBounds,
		paramss, filletNames, pResult);

	/// //////////////////////////////////////////
	//pResult = pSolidd;///////////////////////////////////////////////////////////////////////////////////////////////

	MbAxis3D axVert(MbVector3D(1, 0, 0));
	// 7) ����������� ���� ����� ���������� �����
	if (ress == rt_Success)
		pResult->Rotate(axVert, M_PI / 2); // ������� �� ���
	pResult->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, position + 113.8)));

	pResult->SetColor(ParametricModelCreator::colorScheme ? RGB(60, 64, 62) : RGB(160,164,160));//GRAY RGB(65,78,81) RGB(40, 45,46)
	pAsm->AddItem(*pResult);
	//viewManager->AddObject(Style(1, LIGHTGRAY), pResult);


// ���������� ��������� ������ ����������� ��������� �������� ����
	::DeleteItem(pSolid);
	::DeleteItem(pSolid1);
	::DeleteItem(pHole);
	::DeleteItem(pBlockHole);
	::DeleteItem(pResult);

}