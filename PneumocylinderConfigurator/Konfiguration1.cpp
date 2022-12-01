#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_Konfiguration1()
{
    double heightCone = 50;
    double radiusCylinder = 10;
    double heightCylinder = 50;

    MbSolid* pCone = NULL;
    MbSolid* pCyl1 = NULL;


    // ������-����������� ��� ���������� ��������� - ������������ ���
    MbSNameMaker cylNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    // ������ ����� ��� ���������� ������� ��������   
    SArray<MbCartPoint3D> pntsCyl1(3);
    pntsCyl1.Add(MbCartPoint3D(0, 0, 0));
    pntsCyl1.Add(MbCartPoint3D(0, 0, -heightCylinder));
    pntsCyl1.Add(MbCartPoint3D(radiusCylinder, 0, 0));

    // ���������� ������������� ���� - �������� - �� ���� ������
    ElementarySolid(pntsCyl1, et_Cylinder, cylNames, pCyl1);



    MbSNameMaker coneNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    SArray<MbCartPoint3D> pntsCone(3);
    pntsCone.Add(MbCartPoint3D(0, 0, -heightCone - heightCylinder));
    pntsCone.Add(MbCartPoint3D(0, 0, -heightCylinder));
    pntsCone.Add(MbCartPoint3D(radiusCylinder, 0, -heightCylinder));

    // ���������� ������������� ���� - ������ - �� ���� ������
    ElementarySolid(pntsCone, et_Cone, coneNames, pCone);


    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);


    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);


    MbSolid* pSolid = NULL;

    MbResultType res = ::BooleanResult(*pCyl1, cm_Copy, *pCone, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);


    SolidSPtr MainSolid(pSolid);

    // ���������� ��������� ������ ������������ �������� ����
    ::DeleteItem(pSolid);
    ::DeleteItem(pCone);
    ::DeleteItem(pCyl1);

    return MainSolid;
}