#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_014()
{
    // LIS.ME22.3.002.00.002 ��������� ������� (������)

    MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);

    //  ������� : ������, �����, ������������(������) ��������������
    double blockWidth = 30;
    double blockLength = 120;
    double blockExtrusion = 5;

    SArray<MbCartPoint3D> points(4);
    points.Add(MbCartPoint3D(0, 0, 0)); // ������ ���
    points.Add(MbCartPoint3D(blockLength, 0, 0)); // ����� �� X
    points.Add(MbCartPoint3D(0, blockWidth, 0)); // ������ �� Y
    points.Add(MbCartPoint3D(0, 0, blockExtrusion)); // ������������ �� z

    MbSolid* pBlock = nullptr;
    ::ElementarySolid(points, et_Block, names, pBlock);

    SolidSPtr MainSolid(pBlock);
    ::DeleteItem(pBlock);

    return MainSolid;
}