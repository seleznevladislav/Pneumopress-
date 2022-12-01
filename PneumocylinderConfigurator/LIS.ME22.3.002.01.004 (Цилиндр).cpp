#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_004(double length = 265)
{

    //��������� �����
    double faska1 = 1;
    double faska2 = 1;
    //����� ���������
    double height_Cyl_tor = 3;
    //����� ������ �������
    double diff_length = length - 165;
    double height_Cyl_global = diff_length + 65;
    //���������� ������
    double radius_Cyl_b = 87 / 2;
    //���������� ������
    double radius_Cyl_v = 40;
    //������ ���������
    double radius_Cyl_s = 83 / 2;

    //---------------------�������� �������-----------------------------------------------   
    MbCartPoint3D baseCenter1(0, 0, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter2(0, height_Cyl_global, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase2(radius_Cyl_b, height_Cyl_global, 0);
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
    //---------------------------------------------------------------------------------------
    MbCartPoint3D baseCenter00(0, 0, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter01(0, height_Cyl_global, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase00(radius_Cyl_v, height_Cyl_global, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf0 = NULL;
    MbResultType resCylSurf0 = ::ElementarySurface(baseCenter00, baseCenter01, pntOnBase00,
        st_CylinderSurface, pCylSurf0);
    // ���������� ��������������� ����
    MbSolid* pCy02 = nullptr;
    if (resCylSurf0 == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCy00(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid00 = ::ElementarySolid(*pCylSurf0, namesCy00, pCy02);
    }
    //------------������� �������� ���������--------------------------------------------------  
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    // ����� ������� ��������: ���������� ���������� ���� � ������������
    // �������� ������ � �����.
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // �������������� ����
    MbSolid* pSolid2 = NULL;
    MbResultType res0 = ::BooleanResult(*pCy, cm_Copy, *pCy02, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid2);
    //--------------------������ ���������--------------------------------------------------------------------
    MbCartPoint3D baseCenter14(0, 0, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter24(0, height_Cyl_tor, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase24(radius_Cyl_b, height_Cyl_tor, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf4 = NULL;
    MbResultType resCylSurf4 = ::ElementarySurface(baseCenter14, baseCenter24, pntOnBase24,
        st_CylinderSurface, pCylSurf4);
    // ���������� ��������������� ����
    MbSolid* pCyl4 = nullptr;
    if (resCylSurf4 == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl4(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid4 = ::ElementarySolid(*pCylSurf4, namesCyl4, pCyl4);

    }
    //----------------------------------------------------------------------------------------------
    MbCartPoint3D baseCenter12(0, 0, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter22(0, height_Cyl_tor, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase22(radius_Cyl_s, height_Cyl_tor, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf2 = NULL;
    MbResultType resCylSurf2 = ::ElementarySurface(baseCenter12, baseCenter22, pntOnBase22,
        st_CylinderSurface, pCylSurf2);
    // ���������� ��������������� ����
    MbSolid* pCy2 = nullptr;
    if (resCylSurf == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl2(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid2 = ::ElementarySolid(*pCylSurf2, namesCyl2, pCy2);
    }
    //------------������� �������� ���������-------------------------------------------------- 
    MbSolid* pSolid3 = NULL;
    MbResultType res1 = ::BooleanResult(*pCyl4, cm_Copy, *pCy2, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid3);
    //������� �������� ����������� (��������� ������ ��������� � ��������_---------------------------------------
    MbSolid* pSolid4 = NULL;
    MbResultType res2 = ::BooleanResult(*pSolid2, cm_Copy, *pSolid3, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid4);
    //--------------------������� ���������--------------------------------------------------------------------
    MbCartPoint3D baseCenter15(0, height_Cyl_global - height_Cyl_tor, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter25(0, height_Cyl_global, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase25(radius_Cyl_b, height_Cyl_global, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf5 = NULL;
    MbResultType resCylSurf5 = ::ElementarySurface(baseCenter15, baseCenter25, pntOnBase25,
        st_CylinderSurface, pCylSurf5);
    // ���������� ��������������� ����
    MbSolid* pCyl5 = nullptr;
    if (resCylSurf5 == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl5(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid5 = ::ElementarySolid(*pCylSurf5, namesCyl5, pCyl5);
    }
    //----------------------------------------------------------------------------------------------
    MbCartPoint3D baseCenter16(0, height_Cyl_global - height_Cyl_tor, 0); // ����� ������� ���������
    MbCartPoint3D baseCenter26(0, height_Cyl_global, 0); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase26(radius_Cyl_s, height_Cyl_global, 0);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf6 = NULL;
    MbResultType resCylSurf6 = ::ElementarySurface(baseCenter16, baseCenter26, pntOnBase26,
        st_CylinderSurface, pCylSurf6);
    // ���������� ��������������� ����
    MbSolid* pCy6 = nullptr;
    if (resCylSurf == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl6(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid6 = ::ElementarySolid(*pCylSurf6, namesCyl6, pCy6);
    }
    //------------������� �������� ���������-------------------------------------------------- 
    MbSolid* pSolid5 = NULL;
    MbResultType res7 = ::BooleanResult(*pCyl5, cm_Copy, *pCy6, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid5);
    //������� �������� ����������� (��������� ������� ��������� � ��������_---------------------------------------
    MbSolid* pSolid6 = NULL;
    MbResultType res8 = ::BooleanResult(*pSolid4, cm_Copy, *pSolid5, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid6);
    //---------------����� �������-------------------------------------------------------------------
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params;
    // ����� ������� �����
    params.distance1 = faska1;
    params.distance2 = faska2;
    // ��� ����� - ���������� ����� � ��������� ��������
    params.form = st_Chamfer;
    // ����� ��������������� ���������� �����, ������ ����������� � �������
    // �� �������� �������
    params.prolong = true;
    // ������ ���������� ����� �����
    params.smoothCorner = SmoothValues::ec_uniform;
    // 4) ������������ ������� � ������� ��� ����������.
    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges(4, 1);
    pSolid6->GetEdges(allEdges);
    // ������ ����� ��� ����������
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[1]);
    // 5) ������ ������ ��� ������� ��� ������������� ���������� ������ - ������
    RPArray<MbFace> initBounds(0, 1);
    // 6) ����� ������� ���������� �����
    MbSolid* pResult2 = NULL;
    MbResultType res9 = ::ChamferSolid(*pSolid6, cm_Copy, initCurves,
        params, chamferNames, pResult2);
    //--------------------����� ������-----------------------------------------------------------
    params.distance1 = faska1;
    params.distance2 = faska2;
    // ��� ����� - ���������� ����� � ��������� ��������
    params.form = st_Chamfer;
    // ����� ��������������� ���������� �����, ������ ����������� � �������
    // �� �������� �������
    params.prolong = true;
    // ������ ���������� ����� �����
    params.smoothCorner = SmoothValues::ec_uniform;
    // 4) ������������ ������� � ������� ��� ����������.
    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges2(4, 1);
    pResult2->GetEdges(allEdges2);
    // ������ ����� ��� ����������
    RPArray<MbCurveEdge> initCurves2(4, 1);
    initCurves2.Add(allEdges2[8]);
    // 5) ������ ������ ��� ������� ��� ������������� ���������� ������ - ������
    RPArray<MbFace> initBounds2(0, 1);
    // 6) ����� ������� ���������� �����
    MbSolid* pResult1 = NULL;
    MbResultType res10 = ::ChamferSolid(*pResult2, cm_Copy, initCurves2,
        params, chamferNames, pResult1);


    SolidSPtr MainSolid(pResult1);

    ::DeleteItem(pResult1);
    ::DeleteItem(pResult2);
    ::DeleteItem(pSolid6);
    ::DeleteItem(pSolid5);
    ::DeleteItem(pCy6);
    ::DeleteItem(pCyl5);
    ::DeleteItem(pSolid4);
    ::DeleteItem(pSolid3);
    ::DeleteItem(pCy2);
    ::DeleteItem(pCyl4);
    ::DeleteItem(pSolid2);
    ::DeleteItem(pCy02);
    ::DeleteItem(pCy);

    return MainSolid;
}