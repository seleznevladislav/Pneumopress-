#include "BuildMathModel.h"

using namespace BuildMathModel;


// ��������������� ������� ��� ���������� ���������� � ���� �������� �� ������������.
void CreateSketchKI(RPArray<MbContour>& _arrContours)
{
    // �������� ������� ����� ��������, � �������� � ���������� ��������� ����������.
    // ������ ������� - 8 ����� ��� ����� ����� ������
    SArray<MbCartPoint> arrPnts(12);

    arrPnts.Add(MbCartPoint(-40, 11));
    arrPnts.Add(MbCartPoint(-36, 11));
    arrPnts.Add(MbCartPoint(-36, 4));
    arrPnts.Add(MbCartPoint(-40, 4));
    arrPnts.Add(MbCartPoint(-40, 0));
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(0, 38));
    arrPnts.Add(MbCartPoint(-40, 38));
    arrPnts.Add(MbCartPoint(-40, 34));
    arrPnts.Add(MbCartPoint(-36, 34));
    arrPnts.Add(MbCartPoint(-36, 27));
    arrPnts.Add(MbCartPoint(-40, 27));
    // ���������� ������ ������� �������� ������� �� ������
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = nullptr;

    ::FilletPolyContour(pPolyline, 0, false, arrPnts[12], pContourPolyline);

    _arrContours.push_back(pContourPolyline);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_002()
{
    // ��������� ��� �������������� ������� �������� �� �������� � �������
    const double DEG_TO_RAD = M_PI / 180.0;
    const double SqureSize = 80; //��� ���������
    // ��������� �� (�� ��������� ��������� � ������� ��)
    MbPlacement3D pl;

    //���������� ��� ������������
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    // ����� ������� ��� ���������� ���������� (�� ������� 6)
    RPArray<MbContour> arrContours;
    CreateSketchKI(arrContours);



    // ���������� ���������� ��� ������ ������� ���������� ���� ��������.
    // sweptData - ������, � ������� �������� �������� �� ����������.
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);
    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);



    // ����������� ��� �������� ���������� ���� �������� � ��� �������� ����������
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);

    // ��� �������� ��� ���������� ����:
    // ��� Y ������� �� ��������� �� -40 ������ ����� ��� X.
    MbAxis3D axis(pl.GetAxisY());
    //axis.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(40, 0, 0)));

    // ����� �������-������� ��� ���������� �������� ���� ��������
    MbSolid* pSolid = nullptr;
    MbSolid* pCyl1_Solid = NULL; // ��������� ���������
    MbSolid* pCyl2_Solid = NULL; // ������� ���������
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms,
        operNames, cNames, pSolid);



    // �������� ���� �1 - ������� �����������
    // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts1(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts1.Add(MbCartPoint3D(0, 22, 0));
    cylPnts1.Add(MbCartPoint3D(0, 38, 0));
    cylPnts1.Add(MbCartPoint3D(0, 22, 9));

    MbResultType resCyl1 = ::ElementarySolid(cylPnts1, et_Cylinder, namesElSolid, pCyl1_Solid);
    MbResultType res1 = ::BooleanResult(*pSolid, cm_Copy, *pCyl1_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // �������� ���� �2 - ������� �����������
      // ������� ����� ��� ������������� ���� - ��������
    SArray<MbCartPoint3D> cylPnts2(3); //������ �� 3 ����� ��� ��������/�����
    cylPnts2.Add(MbCartPoint3D(0, 0, 0));
    cylPnts2.Add(MbCartPoint3D(0, 22, 0));
    cylPnts2.Add(MbCartPoint3D(0, 0, 7.25));

    MbResultType resCyl2 = ::ElementarySolid(cylPnts2, et_Cylinder, namesElSolid, pCyl2_Solid);
    MbResultType res2 = ::BooleanResult(*pSolid, cm_Copy, *pCyl2_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);


    SolidSPtr MainSolid(pSolid);

    ::DeleteItem(pSolid);
    ::DeleteItem(pCyl1_Solid);
    ::DeleteItem(pCyl2_Solid);

    return MainSolid;
}