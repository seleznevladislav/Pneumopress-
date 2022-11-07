#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_005()
{
    // ���������� ������� 
    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);
    MbSolid* pShtok = NULL;
    {
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(0, 0, 0));
        points.Add(MbCartPoint3D(0, 265, 0));
        points.Add(MbCartPoint3D(5, 0, 0));

        ElementarySolid(points, et_Cylinder, elNames, pShtok);

    }

    // �����   
          // 2) ������-����������� ��� �������� ���������� �����
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    // 3) �������� �������� ���������� �������� ���������� �����
    SmoothValues params;
    // ����� ������� �����
    params.distance1 = 1;
    params.distance2 = 1;
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
    pShtok->GetEdges(allEdges);
    // ������ ����� ��� ����������
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[2]);
    initCurves.Add(allEdges[0]);
    // 5) ������ ������ ��� ������� ��� ������������� ���������� ������ - ������
    RPArray<MbFace> initBounds(0, 1);
    // 6) ����� ������� ���������� �����
    MbSolid* pResult = NULL;
    MbResultType res = ::ChamferSolid(*pShtok, cm_Copy, initCurves,
        params, chamferNames, pResult);


    ::DeleteItem(pShtok);


    SolidSPtr MainSolid(pResult);
    return MainSolid;
}