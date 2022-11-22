#include "BuildMathModel.h"

using namespace BuildMathModel;


//������ ��������� �� � ������� �� �������� � �������
#define M_PI 3.1415926
const double DTR = M_PI / 180.0;
const double dy1 = 35; //������� �������� �� Y �� ��������� ZX

//�������� ����� ��� ������������ 
void CreateSketch1t(RPArray<MbContour>& _arrContours) {
    //������ 8 ����� ��� �������
    SArray<MbCartPoint> arrPnts(10); //2 ����� �������� � ������ �����
    MbCartPoint p1(-55, 0 - dy1);
    MbCartPoint p2(-55, 55 - dy1);
    MbCartPoint p3(-55 + 23.5, 55 - dy1);
    MbCartPoint p4(-55 + 23.5, 15 - dy1);
    MbCartPoint p5(30, 15 - dy1);
    MbCartPoint p6(30, 55 - dy1);
    MbCartPoint p7(55, 55 - dy1);
    MbCartPoint p8(55, 0 - dy1);

    arrPnts.Add(p1);
    arrPnts.Add(p2);
    arrPnts.Add(p3);
    arrPnts.Add(p4);
    arrPnts.Add(p5);
    arrPnts.Add(p6);
    arrPnts.Add(p7);
    arrPnts.Add(p8);

    // ���������� ������ ������� �������� ������� �� ������
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);

    MbContour* pContourPolyline = new MbContour();

    //������ �������(��������) �� ������, ��������� �� � ��������� � ������
    MbLineSegment* Seg1 = new MbLineSegment(p1, p2);
    MbLineSegment* Seg2 = new MbLineSegment(p2, p3);
    MbLineSegment* Seg3 = new MbLineSegment(p3, p4);
    MbLineSegment* Seg4 = new MbLineSegment(p4, p5);
    MbLineSegment* Seg5 = new MbLineSegment(p5, p6);
    MbLineSegment* Seg6 = new MbLineSegment(p6, p7);
    MbLineSegment* Seg7 = new MbLineSegment(p7, p8);
    MbLineSegment* Seg8 = new MbLineSegment(p8, p1);
    pContourPolyline->AddSegment(Seg1);
    pContourPolyline->AddSegment(Seg2);
    pContourPolyline->AddSegment(Seg3);
    pContourPolyline->AddSegment(Seg4);
    pContourPolyline->AddSegment(Seg5);
    pContourPolyline->AddSegment(Seg6);
    pContourPolyline->AddSegment(Seg7);
    pContourPolyline->AddSegment(Seg8);

    //���������� ������� ��� �����
    ptrdiff_t idxSideRight1 = 6;
    ptrdiff_t idxSideRight2 = 7;
    //������ �����
    pContourPolyline->ChamferTwoSegments(idxSideRight2, 4, 45 * DTR, true, true);
    pContourPolyline->ChamferTwoSegments(idxSideRight1, 4, 45 * DTR, true, true);

    _arrContours.push_back(pContourPolyline);
}

//������������� ��� ������������ �����(������� ����� 6)
void CreateSketch2t(RPArray<MbContour>& _arrContours2) {
    SArray<MbCartPoint> arrPnts2(4);
    arrPnts2.Add(MbCartPoint(-35.5, 15));
    arrPnts2.Add(MbCartPoint(-27.5, 15));
    arrPnts2.Add(MbCartPoint(-27.5, -15));
    arrPnts2.Add(MbCartPoint(-35.5, -15));

    //����� ������� ������� ���������� � 0, ��� ����� ��������
    MbPolyline* pPolyline2 = new MbPolyline(arrPnts2, true);
    MbContour* pContourPolyline2 = new MbContour;
    ::FilletPolyContour(pPolyline2, 0, false, arrPnts2[4], pContourPolyline2);
    ptrdiff_t idxSideRight1 = 0;
    ptrdiff_t idxSideRight2 = 2;
    ptrdiff_t idxSideRight3 = 4;

    // ���������� ����������
    pContourPolyline2->FilletTwoSegments(idxSideRight1, 0);
    pContourPolyline2->FilletTwoSegments(idxSideRight2, 0);
    pContourPolyline2->FilletTwoSegments(idxSideRight3, 0);
    _arrContours2.push_back(pContourPolyline2);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_007()
{
    // ��������� �� (�� ��������� ��������� � ������� ��)
    MbPlacement3D pl;

    // �������� ���������� ��� ���� ������������
    RPArray<MbContour> arrContours;
    CreateSketch1t(arrContours);
    RPArray<MbContour> arrContours2;
    CreateSketch2t(arrContours2);

    //���������� ��� ������������
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

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

    //�������� ��������� ��� ��������������
    MbPlacement3D HorizPlane(MbVector3D(1, 0, 0), /* ��� X  */
        MbVector3D(0, 0, 1), /* ��� Z */
        MbCartPoint3D(0, 0, 0 /* ������ ��������� �� */));

    MbPlacement3D VerticalPlane(MbVector3D(0, 0, 1), /* ��� Z */
        MbVector3D(0, 1, 0), /* ��� Y */
        MbCartPoint3D(0, 0, 0 /* ������ ��������� �� */));

    MbPlacement3D ApplicPlane(MbVector3D(0, 1, 0), /* ��� Y */
        MbVector3D(1, 0, 0), /* ��� X */
        MbCartPoint3D(0, 0, 0 /* ������ ��������� �� */));

    //��� ������� ���������, ������ � ����� �� ������������ ��������������
    MbPlacement3D HoleRightPlane(MbVector3D(0, 1, 0), /* ��� Y */
        MbVector3D(1, 0, 0), /* ��� X */
        MbCartPoint3D(0, 0, 35 / 2 /* ������ ��������� �� */));

    MbPlacement3D HoleLeftPlane(MbVector3D(0, 1, 0), /* ��� Y */
        MbVector3D(1, 0, 0), /* ��� X �� */
        MbCartPoint3D(0, 0, -35 / 2 /* ������ ��������� �� */));

    // ������������ ������ ��� �������� ������������
    MbVector3D dirX(1, 0, 0);
    MbVector3D dirY(0, 1, 0);
    MbVector3D dirZ(0, 0, 1);

    //���������� �������� �� ����������, ������ ��� ��, ��� � � ������������ ������
    MbSweptData sweptData1(*pPlaneXY, arrContours);
    MbSweptData sweptData2(*pPlaneXY, arrContours2);

    const double HEIGHT_FORWARD = 50, HEIGHT_BACKWARD = 50; //����������� �� 100
    const double HEIGHT_FORWARD2 = 50, HEIGHT_BACKWARD2 = 50;
    //const double HEIGHT_FORWARD3 = 0, HEIGHT_BACKWARD3 = 1.5;
    //const double HEIGHT_FORWARD4 = 0, HEIGHT_BACKWARD4 = 2;

    ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);
    ExtrusionValues extrusionParams2(HEIGHT_FORWARD2, HEIGHT_BACKWARD2);
    //ExtrusionValues extrusionParams3(HEIGHT_FORWARD3, HEIGHT_BACKWARD3);
    //ExtrusionValues extrusionParams4(HEIGHT_FORWARD4, HEIGHT_BACKWARD4);


    // ����������� ��������� ������ �������� ���� � �������� ����������, ������ ���������� �� � ��������� ������������ � �� ������� �����
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    // ����������� �������� ���������� ������������� ����


    // �������� ���������� ��� ������� ���
    MbSolid* pSolidBase = nullptr; //�������������� �����
    MbSolid* pSolidRect = nullptr; //����� � ����� ��������������

    MbSolid* pCyl1_Solid = NULL; //��������� � ����� ����� ������� � �����
    MbSolid* pCyl2_Solid = NULL;

    MbSolid* pCyl3_Solid = NULL; //� ����� ������� �������
    MbSolid* pCyl4_Solid = NULL;

    MbSolid* pCyl5_Solid = NULL; //����� ����� �� �����
    MbSolid* pCyl6_Solid = NULL;
    MbSolid* pCyl7_Solid = NULL;
    MbSolid* pCyl8_Solid = NULL;
    MbSolid* pCyl9_Solid = NULL;
    MbSolid* pCyl10_Solid = NULL;

    MbSolid* pCyl11_Solid = NULL; //����� ������� ��������� �� ���� �� 8 ������ �����
    MbSolid* pCyl12_Solid = NULL;
    MbSolid* pCyl13_Solid = NULL;
    MbSolid* pCyl14_Solid = NULL;
    MbSolid* pCyl15_Solid = NULL;
    MbSolid* pCyl16_Solid = NULL;

    //�������� ���� ��� ������
    MbResultType res1 = ::ExtrusionSolid(sweptData1, dirZ, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolidBase);

    //����������� ��������������� �� sketch2
    MbResultType res21 = ::ExtrusionSolid(sweptData2, dirZ, nullptr, nullptr, false, extrusionParams2, operNames, cNames, pSolidRect);
    MbResultType res22 = ::BooleanResult(*pSolidBase, cm_Copy, *pSolidRect, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);

    // ���������� ������������� ���� - ��������(��������� ������� � ����� ��������� 6, �������� 10)
    SArray<MbCartPoint3D> cylPnts(3);
    cylPnts.Add(MbCartPoint3D(-41.5, -0.5, 50));
    cylPnts.Add(MbCartPoint3D(-41.5, -0.5, 40));
    cylPnts.Add(MbCartPoint3D(-41.5, -0.5 + 3, 50));

    //����������� �������1 � � ����������� ��������� �� �������2
    MbResultType res31 = ::ElementarySolid(cylPnts, et_Cylinder, namesElSolid, pCyl1_Solid);
    MbResultType res32 = ::MirrorSolid(*pCyl1_Solid, ApplicPlane, operNames, pCyl2_Solid);
    //�������� � �� ������� � �������� ����
    MbResultType res33 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl1_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res34 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl2_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);

    //�������� � ����� ����� ��������� 7
    SArray<MbCartPoint3D> cylPnts2(3);
    cylPnts2.Add(MbCartPoint3D(-55, 0, 20));
    cylPnts2.Add(MbCartPoint3D(-55 + 23.5, 0, 20));
    cylPnts2.Add(MbCartPoint3D(-55, 0 + 3.5, 20));

    MbResultType res41 = ::ElementarySolid(cylPnts2, et_Cylinder, namesElSolid, pCyl3_Solid);
    MbResultType res42 = ::MirrorSolid(*pCyl3_Solid, ApplicPlane, operNames, pCyl4_Solid);

    MbResultType res43 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl3_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res44 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl4_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);

    //��������, ������ ����� �����, ��������� 9
    SArray<MbCartPoint3D> cylPnts3(3);
    cylPnts3.Add(MbCartPoint3D(-43, -35, 0));
    cylPnts3.Add(MbCartPoint3D(-43, -35 + 55, 0));
    cylPnts3.Add(MbCartPoint3D(-43 + 4.5, -35, 0));

    MbResultType res51 = ::ElementarySolid(cylPnts3, et_Cylinder, namesElSolid, pCyl5_Solid);
    MbResultType res52 = ::MirrorSolid(*pCyl5_Solid, HoleRightPlane, operNames, pCyl6_Solid);
    MbResultType res53 = ::MirrorSolid(*pCyl5_Solid, HoleLeftPlane, operNames, pCyl7_Solid);
    MbResultType res54 = ::MirrorSolid(*pCyl5_Solid, VerticalPlane, operNames, pCyl8_Solid);
    MbResultType res55 = ::MirrorSolid(*pCyl6_Solid, VerticalPlane, operNames, pCyl9_Solid);
    MbResultType res56 = ::MirrorSolid(*pCyl7_Solid, VerticalPlane, operNames, pCyl10_Solid);

    MbResultType res57 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl5_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res58 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl6_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res59 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl7_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res5A = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl8_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res5B = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl9_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res5C = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl10_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);

    //�������� ������� ����� �����(15 � ��������, �� ������ 8)
    SArray<MbCartPoint3D> cylPnts4(3);
    cylPnts4.Add(MbCartPoint3D(-43, -35, 0));
    cylPnts4.Add(MbCartPoint3D(-43, -35 + 8, 0));
    cylPnts4.Add(MbCartPoint3D(-43 + 7.5, -35, 0));

    MbResultType res61 = ::ElementarySolid(cylPnts4, et_Cylinder, namesElSolid, pCyl11_Solid);
    MbResultType res62 = ::MirrorSolid(*pCyl11_Solid, HoleRightPlane, operNames, pCyl12_Solid);
    MbResultType res63 = ::MirrorSolid(*pCyl11_Solid, HoleLeftPlane, operNames, pCyl13_Solid);
    MbResultType res64 = ::MirrorSolid(*pCyl11_Solid, VerticalPlane, operNames, pCyl14_Solid);
    MbResultType res65 = ::MirrorSolid(*pCyl12_Solid, VerticalPlane, operNames, pCyl15_Solid);
    MbResultType res66 = ::MirrorSolid(*pCyl13_Solid, VerticalPlane, operNames, pCyl16_Solid);

    MbResultType res67 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl11_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res68 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl12_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res69 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl13_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res6A = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl14_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res6B = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl15_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    MbResultType res6C = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl16_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);
    pSolidBase->Move(MbVector3D(MbCartPoint3D(0.0, 0.0, 0.0), MbCartPoint3D(55.0, 35.0, 50)));
    pSolidBase->Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0.0, 0.0, 0.0), MbCartPoint3D(0.0, 0.0, 1))), 180 * DTR);
    pSolidBase->Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0.0, 0.0, 0.0), MbCartPoint3D(0.0, 1.0, 0))), 90 * DTR);
    pSolidBase->Move(MbVector3D(MbCartPoint3D(0.0, 0.0, 0.0), MbCartPoint3D(0.0, 55.0, 0)));
     //��������� ����
    //show(Style(1, WHITE), pSolidRect);    
    //show(Style(1, LIGHTBLUE), pCyl6_Solid);
    //show(Style(1, LIGHTRED), pCyl1_Solid);
    //show(Style(1, LIGHTGRAY), pCyl4_Solid);
    //show(Style(1, LIGHTGRAY), pCyl9_Solid);
    //show(Style(1, LIGHTGRAY), pCyl10_Solid);
    SolidSPtr MainSolid(pSolidBase);
    return MainSolid;
}