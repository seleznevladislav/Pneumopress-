#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_011()
{
    // LIS.ME22.3.002.00.011 ��������� �������������� (������)

    MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker cylNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    //  ������� : ������, �����, ������������(������) ��������������
    // ������ �������� ����
    double blockWidth1 = 60;
    double blockLength1 = 90;
    double blockExtrusion1 = 40;
    //������� ��
    double Xsdvig = -70;
    double Ysdvig = -14;

    SArray<MbCartPoint3D> pointsBlock1(4);
    pointsBlock1.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, 0)); // ������ ���
    pointsBlock1.Add(MbCartPoint3D(blockLength1 + Xsdvig, 0 + Ysdvig, 0)); // ����� �� X
    pointsBlock1.Add(MbCartPoint3D(0 + Xsdvig, blockWidth1 + Ysdvig, 0)); // ������ �� Y
    pointsBlock1.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, blockExtrusion1)); // ������������ �� z

    MbSolid* pBlock1 = nullptr;
    ::ElementarySolid(pointsBlock1, et_Block, names, pBlock1);

    //  ������� : ������, �����, ������������(������) ��������������
    // ������ ���� ��� ������������
    double blockWidth2 = 60;
    double blockLength2 = 50;
    double blockExtrusion2 = 20;

    SArray<MbCartPoint3D> pointsBlock2(4);
    pointsBlock2.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, 0)); // ������ ���
    pointsBlock2.Add(MbCartPoint3D(blockLength2 + Xsdvig, 0 + Ysdvig, 0)); // ����� �� X
    pointsBlock2.Add(MbCartPoint3D(0 + Xsdvig, blockWidth2 + Ysdvig, 0)); // ������ �� Y
    pointsBlock2.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, blockExtrusion2)); // ������������ �� z

    MbSolid* pBlock2 = nullptr;
    ::ElementarySolid(pointsBlock2, et_Block, names, pBlock2);

    // ������������ ������������� �����
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    MbSolid* pSolid = NULL;

    MbResultType res1 = ::BooleanResult(*pBlock1, cm_Copy, *pBlock2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    double cylRadius1 = 8.5; // ������ ��� ������������  ����� ���������� �� ������
    double centerCircleX1 = 22; // ����� �� X
    double centerCircleY1 = 30; // ����� �� X
    SArray<MbCartPoint3D> pointsCyl1(3);
    pointsCyl1.Add(MbCartPoint3D(centerCircleX1 + Xsdvig, centerCircleY1 + Ysdvig, 0)); // ������ ���
    pointsCyl1.Add(MbCartPoint3D(centerCircleX1 + Xsdvig, centerCircleY1 + Ysdvig, blockExtrusion1)); // �� Z
    pointsCyl1.Add(MbCartPoint3D(centerCircleX1 + cylRadius1 + Xsdvig, centerCircleY1 + Ysdvig, 0)); // �� X

    MbSolid* pCyl1 = nullptr;
    ::ElementarySolid(pointsCyl1, et_Cylinder, cylNames, pCyl1);

    // ������������ ���� ���������
    MbResultType res2 = ::BooleanResult(*pSolid, cm_Copy, *pCyl1, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // ������������ ���� ��������� 
    double cylRadius2 = 7; // ������ ��� ������������  ����� ���������� �� ������
    double centerCircleX2 = 70; // ����� �� X
    double centerCircleY2 = 14; // ����� �� X
    SArray<MbCartPoint3D> pointsCyl2(3);
    pointsCyl2.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, 0)); // ������ ���
    pointsCyl2.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, blockExtrusion1)); // �� Z
    pointsCyl2.Add(MbCartPoint3D(centerCircleX2 + cylRadius2 + Xsdvig, centerCircleY2 + Ysdvig, 0)); // �� X

    MbSolid* pCyl2 = nullptr;
    ::ElementarySolid(pointsCyl2, et_Cylinder, cylNames, pCyl2);

    MbResultType res3 = ::BooleanResult(*pSolid, cm_Copy, *pCyl2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // ��������� � ���� �� ����� � �������������� ���������
    double cylRadius3 = 8.5; // ������ ��� ������������ ���������� � �����������
    SArray<MbCartPoint3D> pointsCyl3(3);
    pointsCyl3.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, blockExtrusion1)); // ������ ���
    pointsCyl3.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, blockExtrusion1 - 10)); // �� Z
    pointsCyl3.Add(MbCartPoint3D(centerCircleX2 + cylRadius3 + Xsdvig, centerCircleY2 + Ysdvig, 0)); // �� X

    MbSolid* pCyl3 = nullptr;
    ::ElementarySolid(pointsCyl3, et_Cylinder, cylNames, pCyl3);

    MbResultType res4 = ::BooleanResult(*pSolid, cm_Copy, *pCyl3, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // ������ ������������ ���������
    double centerCircleY3 = 46; // ����� �� X
    SArray<MbCartPoint3D> pointsCyl4(3);
    pointsCyl4.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, 0)); // ������ ���
    pointsCyl4.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, blockExtrusion1)); // �� Z
    pointsCyl4.Add(MbCartPoint3D(centerCircleX2 + cylRadius2 + Xsdvig, centerCircleY3 + Ysdvig, 0)); // �� X

    MbSolid* pCyl4 = nullptr;
    ::ElementarySolid(pointsCyl4, et_Cylinder, cylNames, pCyl4);

    MbResultType res5 = ::BooleanResult(*pSolid, cm_Copy, *pCyl4, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // ��������� � ���� �� ����� � �������������� ���������
    SArray<MbCartPoint3D> pointsCyl5(3);
    pointsCyl5.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, blockExtrusion1)); // ������ ���
    pointsCyl5.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, blockExtrusion1 - 10)); // �� Z
    pointsCyl5.Add(MbCartPoint3D(centerCircleX2 + cylRadius3 + Xsdvig, centerCircleY3 + Ysdvig, 0)); // �� X

    MbSolid* pCyl5 = nullptr;
    ::ElementarySolid(pointsCyl5, et_Cylinder, cylNames, pCyl5);

    MbResultType res6 = ::BooleanResult(*pSolid, cm_Copy, *pCyl5, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);


    ::DeleteItem(pBlock1);


    SolidSPtr MainSolid(pSolid);
    return MainSolid;
}