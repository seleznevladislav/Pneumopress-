#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketchvc(RPArray<MbContour>& _arrContours)
{
    double rad_osn = 8; // ������ ����� ������� ����� ���
    double rad_b = 10.5; // ������ �������� ��������-������ 
    double height = 43; // ����� ������ ��� 
    double height_v = 3; // ������ �������� ������
    double height_prot = 1.5; // ������ �������� ��� ������� 

    // �������� ������ ��� ��������   

    SArray<MbCartPoint> arrPnts(12);
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 1.85));
    arrPnts.Add(MbCartPoint(7.6, 1.85));
    arrPnts.Add(MbCartPoint(7.6, 3));
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


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_012()
{

    // �������� 

    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> arrContours;
    CreateSketchvc(arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    // ����������� ��� �������� ���������� ���� �������� � ��� �������� ����������
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // ��� �������� ��� ���������� ����:
    MbAxis3D axis(pl.GetAxisY());

    // ����� �������-������� ��� ���������� �������� ���� ��������
    MbSolid* pOs1 = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pOs1);



    // ����� 

    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params;
    // ����� ������� �����
    params.distance1 = 0.5;
    params.distance2 = 0.5;
    params.form = st_Chamfer;
    params.prolong = true;
    // ������ ���������� ����� �����
    params.smoothCorner = SmoothValues::ec_uniform;

    // 4) ������������ ������� � ������� ��� ����������.
    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges(4, 1);
    pOs1->GetEdges(allEdges);
    // ������ ����� ��� ����������
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[0]);
    initCurves.Add(allEdges[14]);

    RPArray<MbFace> initBounds(0, 1);

    // 6) ����� ������� ���������� �����
    MbSolid* pOs1_r = NULL;
    MbResultType res1 = ::ChamferSolid(*pOs1, cm_Copy, initCurves,
        params, chamferNames, pOs1_r);

    SolidSPtr MainSolid(pOs1_r);

    ::DeleteItem(pOs1_r);
    ::DeleteItem(pOs1);

    return MainSolid;

}