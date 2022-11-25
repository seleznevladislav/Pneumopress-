#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_008()
{
    //���������� �������
    double height_Cyl = 25;// ������ ����������
    double radius_Cyl = 35 / 2;// ������ ����������� ��������
    double height_Cyl_vnesh = 25 - 21;//������ �������
    double radius_Cyl_vnesh = 42 / 2;//���������� ������
    double tolshina = 10;//������� ������������ ��������
    double faska1 = 2;
    double faska2 = 0.5;
    double sopr = 0.5;


    MbCartPoint3D baseCenter1(0, 0, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter2(0, height_Cyl, 0); // ����� ������� ���������

    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase2(radius_Cyl, height_Cyl, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf = NULL;
    MbResultType resCylSurf = ::ElementarySurface(baseCenter1, baseCenter2, pntOnBase2,
        st_CylinderSurface, pCylSurf);
    // ���������� ��������������� ����
    MbSolid* pCy = nullptr;
    if (resCylSurf == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf, namesCyl, pCy);

    }

    //--------------------------������� �������------------------------------------------------------   
    MbCartPoint3D baseCenter_vnesh1(0, 0, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter_vnesh2(0, height_Cyl_vnesh, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_vnesh2(radius_Cyl_vnesh, height_Cyl_vnesh, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_vnesh = NULL;
    MbResultType resCylSurf_vnesh = ::ElementarySurface(baseCenter_vnesh1, baseCenter_vnesh2, pntOnBase_vnesh2,
        st_CylinderSurface, pCylSurf_vnesh);
    // ���������� ��������������� ����
    MbSolid* pCy_vnesh = nullptr;
    if (resCylSurf_vnesh == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_vnesh, namesCyl, pCy_vnesh);

    }
    //-------------������ �������� �����������----------------------------------------------------------------
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    // ����� ������� ��������: ���������� ���������� ���� � ������������
    // �������� ������ � �����.
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // �������������� ����
    MbSolid* vtulka_bez_vireza = NULL;
    MbResultType res0 = ::BooleanResult(*pCy, cm_Copy, *pCy_vnesh, cm_Copy, bo_Union,
        flagsBool, operBoolNames, vtulka_bez_vireza);

    //-------------------------------���������� �������-------------------------------------------------  
    double radius_Cyl_virez = radius_Cyl - tolshina / 2;
    MbCartPoint3D baseCenter_virez1(0, 0, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter_virez2(0, height_Cyl, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_virez2(radius_Cyl_virez, height_Cyl, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_virez = NULL;
    MbResultType resCylSurf_virez = ::ElementarySurface(baseCenter_virez1, baseCenter_virez2, pntOnBase_virez2,
        st_CylinderSurface, pCylSurf_virez);
    // ���������� ��������������� ����
    MbSolid* pCy_virez = nullptr;
    if (resCylSurf_virez == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_virez, namesCyl, pCy_virez);

    }
    MbSolid* vtulka_samosmaz = NULL;
    MbResultType res = ::BooleanResult(*vtulka_bez_vireza, cm_Copy, *pCy_virez, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, vtulka_samosmaz);
    //---------------------------�����1-------------------------------------------------------

    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);


    SmoothValues params;
    // ����� ������� �����
    params.distance1 = faska1;
    params.distance2 = faska1;
    // ��� ����� - ���������� ����� � ��������� ��������
    params.form = st_Chamfer;
    // ����� ��������������� ���������� �����, ������ ����������� � �������
    // �� �������� �������
    params.prolong = true;
    // ������ ���������� ����� �����
    params.smoothCorner = SmoothValues::ec_uniform;


    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges(4, 1);
    vtulka_samosmaz->GetEdges(allEdges);
    // ������ ����� ��� ����������
    RPArray<MbCurveEdge> initCurves(4, 1);

    initCurves.Add(allEdges[0]);

    // ������ ������ ��� ������� ��� ������������� ���������� ������ - ������
    RPArray<MbFace> initBounds(0, 1);

    //����� ������� ���������� �����
    MbSolid* pResult = NULL;
    MbResultType res2 = ::ChamferSolid(*vtulka_samosmaz, cm_Copy, initCurves,
        params, chamferNames, pResult);
    //-----------------------------------------------�����2--------------------------------------
        // ����� ������� �����
    params.distance1 = faska2;
    params.distance2 = faska2;
    // ��� ����� - ���������� ����� � ��������� ��������
    params.form = st_Chamfer;
    // ����� ��������������� ���������� �����, ������ ����������� � �������
    // �� �������� �������
    params.prolong = true;
    // ������ ���������� ����� �����
    params.smoothCorner = SmoothValues::ec_uniform;
    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges1(4, 1);
    pResult->GetEdges(allEdges1);
    // ������ ����� ��� ����������
    RPArray<MbCurveEdge> initCurves1(4, 1);
    initCurves1.Add(allEdges1[2]);
    initCurves1.Add(allEdges1[3]);
    initCurves1.Add(allEdges1[1]);
    // ������ ������ ��� ������� ��� ������������� ���������� ������ - ������
    RPArray<MbFace> initBounds1(0, 1);
    //����� ������� ���������� �����
    MbSolid* pResult1 = NULL;
    MbResultType res3 = ::ChamferSolid(*pResult, cm_Copy, initCurves1,
        params, chamferNames, pResult1);
    //---------------------------------����������-------------------------------
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    params.distance1 = sopr;
    params.distance2 = sopr;
    params.form = st_Fillet;
    params.conic = 0;
    // ��������� ��������� �����, ������ ����������� � ������� �� �������� �������
    params.prolong = true;
    // ������ ���������� ����� �����
    params.smoothCorner = SmoothValues::ec_uniform;
    // ���� ���������� ������ � ����� ���������� �����������
    params.keepCant = ts_neutral;
    // ������� ����������
    params.strict = false;
    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges2(4, 1);
    pResult1->GetEdges(allEdges2);
    // � ������ ����� ��� ���������� ���������� ������ ���� �����
    RPArray<MbCurveEdge> initCurves2(4, 1);
    initCurves2.Add(allEdges2[9]);
    // 5) ������ ������ ��� �������
    RPArray<MbFace> initBounds2(0, 1);
    // 6) ����� ������� ���������� �����.
    MbSolid* detail_008 = NULL;
    MbResultType res4 = ::FilletSolid(*pResult1, cm_Copy, initCurves2, initBounds2,
        params, filletNames, detail_008);

    SolidSPtr MainSolid(detail_008);

    ::DeleteItem(detail_008);
    ::DeleteItem(pResult1);
    ::DeleteItem(pResult);
    ::DeleteItem(vtulka_samosmaz);
    ::DeleteItem(pCy_virez);
    ::DeleteItem(vtulka_bez_vireza);
    ::DeleteItem(pCy_vnesh);
    ::DeleteItem(pCy);

    return MainSolid;
}