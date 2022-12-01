#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_Konfiguration3()
{
    double heightC1 = 50;
    double heightC2 = heightC1 / 3;
    double radiusC1 = 10;
    double radiusC2 = radiusC1 * 1.5;
    // �������� ���� - ��������
    MbSolid* pCyl1 = NULL, * pCyl2 = NULL;

    // ������-����������� ��� ���������� ��������� - ������������ ���
    MbSNameMaker cylNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);


    // ������ ����� ��� ���������� ������� ��������   
    SArray<MbCartPoint3D> pntsCyl1(3);
    pntsCyl1.Add(MbCartPoint3D(0, 0, 0));
    pntsCyl1.Add(MbCartPoint3D(0, 0, -heightC1));
    pntsCyl1.Add(MbCartPoint3D(radiusC1, 0, 0));


    // ���������� ������������� ���� - �������� - �� ���� ������
    ElementarySolid(pntsCyl1, et_Cylinder, cylNames, pCyl1);

    // ������ ����� ��� ���������� ������� ��������
    SArray<MbCartPoint3D> pntsCyl2(3);
    pntsCyl2.Add(MbCartPoint3D(0, 0, -heightC1));
    pntsCyl2.Add(MbCartPoint3D(0, 0, -heightC2 - heightC1));
    pntsCyl2.Add(MbCartPoint3D(radiusC2, 0, 0));

    // ���������� ������� ��������
    ElementarySolid(pntsCyl2, et_Cylinder, cylNames, pCyl2);


    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);


    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);


    MbSolid* pSolid = NULL;

    MbResultType res = ::BooleanResult(*pCyl1, cm_Copy, *pCyl2, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);


    SolidSPtr MainSolid(pSolid);

    // ���������� ��������� ������ ������������ �������� ����
    ::DeleteItem(pSolid);
    ::DeleteItem(pCyl1);
    ::DeleteItem(pCyl2);

    return MainSolid;
}