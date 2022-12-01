#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketchKO(RPArray<MbContour>& _arrContours)
{
    // �������� ������ ��� ��������   

    double height_k = 25; // ������ ��������
    double vne_rad_k = 16; // ������� ������ �������� 
    double vnut_rad_k = 12.5; //���������� ������ 

    SArray<MbCartPoint> arrPnts(5);
    arrPnts.Add(MbCartPoint(vnut_rad_k, height_k));
    arrPnts.Add(MbCartPoint(vne_rad_k, height_k));
    arrPnts.Add(MbCartPoint(vne_rad_k, 5));
    arrPnts.Add(MbCartPoint(14.66, 0));
    arrPnts.Add(MbCartPoint(vnut_rad_k, 0));

    // ���������� ������ ������� �������� ������� �� ������

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContourPolyline);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_003()
{
    // �������� 

    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> arrContours;
    CreateSketchKO(arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    // ����������� ��� �������� ���������� ���� �������� � ��� �������� ����������
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // ��� �������� ��� ���������� ����:
    MbAxis3D axis(pl.GetAxisY());

    // ����� �������-������� ��� ���������� �������� ���� ��������
    MbSolid* pKolp = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pKolp);


    // ���������� ����� 


       // 2) ������-����������� ��� �������� ���������� �����
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    // 3) �������� �������� ���������� �������� ���������� �����
    SmoothValues params;
    //  SmoothValues params;
      // ������� �������� �� ���� ����������� ������������
    params.distance1 = 1;
    // ��� ���������� � ���������� �� ���� ��������
    params.form = st_Fillet;
    // ����� ������� ���������� - ����������
    params.conic = 0;
    // ��������� ��������� ������ �����, ���������� �� ������� �������
    params.prolong = false;
    // ������ ���������� ����� �����
    params.smoothCorner = SmoothValues::ec_uniform;
    // ���� ���������� ������ � ����� ���������� �����������
    params.keepCant = ts_negative;
    // ������� ����������
    params.strict = true;

    // 4) ������������ ������� � ������� ��� ����������.
    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges(4, 1);
    pKolp->GetEdges(allEdges);
    // � ������ ����� ��� ���������� ���������� ������ ���� �����
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[3]);

    // 5) ������ ������ ��� ������� � � ������ ������� ������
    RPArray<MbFace> initBounds(0, 1);

    // 6) ����� ������� ���������� �����.
    // � ���������� ����������� ���������� ������ ����� � ����������,
    // �� ������� � �������� ���� ��������� ������� � ��������.
    MbSolid* pKolp_res = NULL;
    MbResultType res1 = ::FilletSolid(*pKolp, cm_Copy, initCurves, initBounds,
        params, filletNames, pKolp_res);

    SolidSPtr MainSolid(pKolp_res);

    ::DeleteItem(pKolp_res);
    ::DeleteItem(pKolp);

    return MainSolid;
}

