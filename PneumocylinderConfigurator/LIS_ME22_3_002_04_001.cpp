#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchAxe(RPArray<MbContour>& _arrContours)
{
    // �������� ������ ��� ��������   
    double rad_osn = 10; // ������ ����� ������� ����� ���
    double rad_b = 13; // ������ �������� ��������-������ 
    double height = 113; // ����� ������ ��� 
    double height_v = 4; // ������ �������� ������
    double height_prot = 1.5; // ������ �������� ��� ������� 

    SArray<MbCartPoint> arrPnts(12);
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 1.65));
    arrPnts.Add(MbCartPoint(rad_osn - 2, 1.65));
    arrPnts.Add(MbCartPoint(rad_osn - 2, 3));
    arrPnts.Add(MbCartPoint(rad_osn, 3));
    arrPnts.Add(MbCartPoint(rad_osn, height - height_prot - height_v));
    arrPnts.Add(MbCartPoint(rad_osn - 0.1, height - height_prot - height_v));
    arrPnts.Add(MbCartPoint(rad_osn - 0.1, height - height_v));
    arrPnts.Add(MbCartPoint(rad_b, height - height_v));
    arrPnts.Add(MbCartPoint(rad_b, height));
    arrPnts.Add(MbCartPoint(0, height));

    // ���������� ������ ������� �������� ������� �� ������

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContourPolyline);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_04_001()
{


    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> arrContours;
    CreateSketchAxe(arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // ��� �������� ��� ���������� ����:
    MbAxis3D axis(pl.GetAxisY());

    // ����� �������-������� ��� ���������� �������� ���� ��������
    MbSolid* pOs = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pOs);

    // �����   
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    SmoothValues params;
    // ����� ������� �����
    params.distance1 = 0.5;
    params.distance2 = 0.5;
    params.form = st_Chamfer;
    params.prolong = true;
    params.smoothCorner = SmoothValues::ec_uniform;

    RPArray<MbCurveEdge> allEdges(4, 1);
    pOs->GetEdges(allEdges);
    // ������ ����� ��� ����������
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[0]);
    initCurves.Add(allEdges[14]);

    // 5) ������ ������ ��� ������� ��� ������������� ���������� ������ - ������
    RPArray<MbFace> initBounds(0, 1);
    // 6) ����� ������� ���������� �����
    MbSolid* pOs_r = NULL;
    ::ChamferSolid(*pOs, cm_Copy, initCurves,
        params, chamferNames, pOs_r);


    SolidSPtr MainSolid(pOs_r);

    // ���������� ��������� ������ ������������ �������� ����
    ::DeleteItem(pOs);
    ::DeleteItem(pOs_r);

    return MainSolid;
}