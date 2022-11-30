#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_009()
{
    // LIS.ME22.3.002.00.009 ���������(�������������) (������)

    MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker cylNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    //  ������� : ������, �����, ������������(������) ��������������
    double blockWidth = 17;
    double blockLength = 17;
    double blockExtrusion = 1.2;  // � ���� ������ 2 �������� �������

    SArray<MbCartPoint3D> pointsBlock(4);
    pointsBlock.Add(MbCartPoint3D(0, 0, 0)); // ������ ���
    pointsBlock.Add(MbCartPoint3D(blockLength, 0, 0)); // ����� �� X
    pointsBlock.Add(MbCartPoint3D(0, blockWidth, 0)); // ������ �� Y
    pointsBlock.Add(MbCartPoint3D(0, 0, blockExtrusion)); // ������������ �� z

    MbSolid* pBlock = nullptr;
    ::ElementarySolid(pointsBlock, et_Block, names, pBlock);


    double cylRadius = 6; // ������ ��� ������������ ����������

    SArray<MbCartPoint3D> pointsCyl(3);
    pointsCyl.Add(MbCartPoint3D(blockWidth / 2, blockWidth / 2, 0)); // ������ ���
    pointsCyl.Add(MbCartPoint3D(blockWidth / 2, blockWidth / 2, blockExtrusion)); // �� Z
    pointsCyl.Add(MbCartPoint3D(cylRadius, cylRadius, 0)); // �� X

    MbSolid* pCyl = nullptr;
    ::ElementarySolid(pointsCyl, et_Cylinder, cylNames, pCyl);

    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    MbSolid* pSolid = NULL;

    MbResultType res = ::BooleanResult(*pBlock, cm_Copy, *pCyl, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);
    // ����������� ������������ ����


    SolidSPtr MainSolid(pSolid);

    ::DeleteItem(pSolid);
    ::DeleteItem(pBlock);
    ::DeleteItem(pCyl);

    return MainSolid;
}