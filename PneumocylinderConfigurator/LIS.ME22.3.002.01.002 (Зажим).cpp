#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

MbSolid* ParametricModelCreator::LIS_ME22_3_002_01_002()
{// ��������� ��� �������������� ����� �� ��������� � ��������� ����.
    const double DEG_TO_RAD = M_PI / 180.0;
    const double SqureSize = 65; //��� ���������


    // ��������� �� (�� ��������� ��������� � ������� ��)
    MbPlacement3D pl;

    //���������� ��� ������������
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    //������ ���������, �� ������� ����� ���������� ������
    MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneYZ = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(0, 1, 0),
        MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    //�������� ��������� ��� ��������������, �� ���� �� ����������
    MbPlacement3D HorizPlane(MbVector3D(1, 0, 0), /* ��� X ��������� �� */
        MbVector3D(0, 0, 1), /* ��� Z ��������� �� */
        MbCartPoint3D(0, 32.6, 0 /* ������ ��������� ��������� �� */));
    MbPlacement3D VerticalPlane(MbVector3D(0, 0, 1), /* ��� Z ��������� �� */
        MbVector3D(0, 1, 0), /* ��� Y ��������� �� */
        MbCartPoint3D(32.6, 0, 0 /* ������ ��������� ��������� �� */));

    // ������������ ������ ��� �������� ������������
    MbVector3D dirX(1, 0, 0);
    MbVector3D dirY(0, 1, 0);
    MbVector3D dirZ(0, 0, 1);

    // ������, �������� ��������� ����������(�������), ��� ���� �������, �� ����� ��������� �������� ������ 



    // ��������� �������� ������������, �������� �������� ���� ��� ���������� � ������ �/��� � ��������������� �����������




    // ����������� ��������� ������ �������� ���� � �������� ����������, ������ ���������� �� � ��������� ������������ � �� ������� �����
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    // ����������� �������� ���������� ������������� ����



    MbSolid* pCyl1_Solid = NULL; // ���������
    MbSolid* pCyl2_Solid = NULL; // ��������� ����������

    MbSolid* pCyl3_Solid = NULL; // ��������� ������� �����
    MbSolid* pCyl4_Solid = NULL; // ��������� ������� �����

    MbSolid* pCyl5_Solid = NULL; // ��������� ������� �����
    MbSolid* pCyl6_Solid = NULL; // ��������� ������� �����

    MbSolid* pCyl7_Solid = NULL; // ��������� ������� ������
    MbSolid* pCyl8_Solid = NULL; // ��������� ������� ������

    MbSolid* pCyl9_Solid = NULL; // ��������� ������� ������
    MbSolid* pCyl10_Solid = NULL; // ��������� ������� ������

    //����� ��� �������� �������� ����� � ����
    // �������� ���� �1 - ������� �����������
    // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts1(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts1.Add(MbCartPoint3D(SqureSize / 2, SqureSize / 2, 0));
    //����� ������ �����, SqureSize = 81, �� ������ -5 ������
    cylPnts1.Add(MbCartPoint3D(SqureSize / 2, SqureSize / 2, 12));
    //������� �����, ������ ����� (10-(-5))=15
    cylPnts1.Add(MbCartPoint3D(SqureSize / 2, SqureSize / 2 + (65 / 2), 0));
    //������ �� ������, ������ �������� ����������, ������ - ��� ����� �� ������� �����(81/2 + ������� �����/2), �� ��� �� ������ -5(3-� ����������), ��� � ������ �����

    // ���������� ������������� ���� - ��������
    MbResultType resCyl1 = ::ElementarySolid(cylPnts1, et_Cylinder,
        namesElSolid, pCyl1_Solid);

    // ���� �2 - ������� �����������
    // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts2(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts2.Add(MbCartPoint3D(SqureSize / 2, SqureSize / 2, 0));
    cylPnts2.Add(MbCartPoint3D(SqureSize / 2, SqureSize / 2, 12));
    cylPnts2.Add(MbCartPoint3D(SqureSize / 2, SqureSize / 2 + (37 / 2), 0));

    MbResultType resCyl2 = ::ElementarySolid(cylPnts2, et_Cylinder,
        namesElSolid, pCyl2_Solid);

    // �������� �� ��������� �������� ������� �������, ��������� 37
    MbResultType res1 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl2_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);


    // ���� �3 - ������� �����������
        // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts3(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts3.Add(MbCartPoint3D(6.5, 32.5, 6));
    cylPnts3.Add(MbCartPoint3D(6.5, 32.5, 12));
    cylPnts3.Add(MbCartPoint3D(6.5, 32.5 + (11 / 2), 6));

    MbResultType resCyl3 = ::ElementarySolid(cylPnts3, et_Cylinder,
        namesElSolid, pCyl3_Solid);
    MbResultType res2 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl3_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);

    // ���� �4 - ������� �����������
       // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts4(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts4.Add(MbCartPoint3D(6.5, 32.5, 0));
    cylPnts4.Add(MbCartPoint3D(6.5, 32.5, 6));
    cylPnts4.Add(MbCartPoint3D(6.5, 32.5 + (6.6 / 2), 0));

    MbResultType resCyl4 = ::ElementarySolid(cylPnts4, et_Cylinder,
        namesElSolid, pCyl4_Solid);
    MbResultType res3 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl4_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);

    // ���� �5 - ������� �����������
        // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts5(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts5.Add(MbCartPoint3D(32.5, 6.5, 6));
    cylPnts5.Add(MbCartPoint3D(32.5, 6.5, 12));
    cylPnts5.Add(MbCartPoint3D(32.5, 6.5 + (11 / 2), 6));

    MbResultType resCyl5 = ::ElementarySolid(cylPnts5, et_Cylinder,
        namesElSolid, pCyl5_Solid);
    MbResultType res5 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl5_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);

    // ���� �6 - ������� �����������
       // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts6(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts6.Add(MbCartPoint3D(32.5, 6.5, 0));
    cylPnts6.Add(MbCartPoint3D(32.5, 6.5, 6));
    cylPnts6.Add(MbCartPoint3D(32.5, 6.5 + (6.6 / 2), 0));

    MbResultType resCyl6 = ::ElementarySolid(cylPnts6, et_Cylinder,
        namesElSolid, pCyl6_Solid);
    MbResultType res6 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl6_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);

    // ���� �7 - ������� �����������
       // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts7(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts7.Add(MbCartPoint3D(58.5, 32.5, 6));
    cylPnts7.Add(MbCartPoint3D(58.5, 32.5, 12));
    cylPnts7.Add(MbCartPoint3D(58.8, 32.5 + (11 / 2), 6));

    MbResultType resCyl7 = ::ElementarySolid(cylPnts7, et_Cylinder,
        namesElSolid, pCyl7_Solid);
    MbResultType res7 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl7_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);

    // ���� �8 - ������� �����������
       // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts8(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts8.Add(MbCartPoint3D(58.5, 32.5, 0));
    cylPnts8.Add(MbCartPoint3D(58.5, 32.5, 6));
    cylPnts8.Add(MbCartPoint3D(58.5, 32.5 + (6.6 / 2), 0));

    MbResultType resCyl8 = ::ElementarySolid(cylPnts8, et_Cylinder,
        namesElSolid, pCyl8_Solid);
    MbResultType res8 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl8_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);


    // ���� �9 - ������� �����������
    // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts9(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts9.Add(MbCartPoint3D(32.5, 58.5, 6));
    cylPnts9.Add(MbCartPoint3D(32.5, 58.5, 12));
    cylPnts9.Add(MbCartPoint3D(32.5, 58.5 + (11 / 2), 6));

    MbResultType resCyl9 = ::ElementarySolid(cylPnts9, et_Cylinder,
        namesElSolid, pCyl9_Solid);
    MbResultType res9 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl9_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);

    // ���� �10 - ������� �����������
       // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts10(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts10.Add(MbCartPoint3D(32.5, 58.5, 0));
    cylPnts10.Add(MbCartPoint3D(32.5, 58.5, 6));
    cylPnts10.Add(MbCartPoint3D(32.5, 58.5 + (6.6 / 2), 0));

    MbResultType resCyl10 = ::ElementarySolid(cylPnts10, et_Cylinder,
        namesElSolid, pCyl10_Solid);
    MbResultType res10 = ::BooleanResult(*pCyl1_Solid, cm_Copy, *pCyl10_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pCyl1_Solid);

    return pCyl1_Solid;
}