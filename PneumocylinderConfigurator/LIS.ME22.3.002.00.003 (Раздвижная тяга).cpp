#include "BuildMathModel.h"

using namespace BuildMathModel;


void CreateSketch1er(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> arrPnts(10);
    arrPnts.Add(MbCartPoint(0, 0)); //����� �������� ��������� 16 � ������� ���� R = 18
    arrPnts.Add(MbCartPoint(0, 18));
    arrPnts.Add(MbCartPoint(30, 18));
    arrPnts.Add(MbCartPoint(30, -16));
    arrPnts.Add(MbCartPoint(30, -26));//����� ������ R=10
    arrPnts.Add(MbCartPoint(20, -26));
    arrPnts.Add(MbCartPoint(18, -40));
    arrPnts.Add(MbCartPoint(-18, -40));
    arrPnts.Add(MbCartPoint(0, -40));//����� ��������� D = 20 � ������� ����
    arrPnts.Add(MbCartPoint(-18, 0));


    const double RADIUS1 = 18;
    const double RADIUS2 = 10;
    MbArc* pArc1 = new MbArc(arrPnts[0], RADIUS1, arrPnts[9], arrPnts[1], -1);

    MbLineSegment* pLine1 = new MbLineSegment(arrPnts[1], arrPnts[2]);

    MbLineSegment* pLine2 = new MbLineSegment(arrPnts[2], arrPnts[3]);


    MbArc* pArc2 = new MbArc(arrPnts[4], RADIUS2, arrPnts[3], arrPnts[5], 1);
    MbLineSegment* pLine3 = new MbLineSegment(arrPnts[5], arrPnts[6]);

    MbArc* pArc3 = new MbArc(arrPnts[8], RADIUS1, arrPnts[6], arrPnts[7], -1);
    MbLineSegment* pLine4 = new MbLineSegment(arrPnts[7], arrPnts[9]);


    MbContour* pContour = new MbContour();


    pContour->AddSegment(pArc1);
    pContour->AddSegment(pLine1);
    pContour->AddSegment(pLine2);
    pContour->AddSegment(pArc2);
    pContour->AddSegment(pLine3);
    pContour->AddSegment(pArc3);
    pContour->AddSegment(pLine4);

    _arrContours.push_back(pContour);
}
void CreateSketch2er(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> arrPnts(4);
    arrPnts.Add(MbCartPoint(30, 16));
    arrPnts.Add(MbCartPoint(50, 16));
    arrPnts.Add(MbCartPoint(50, 0));// ����� ���� R=16 �� ���
    arrPnts.Add(MbCartPoint(50, -16));
    arrPnts.Add(MbCartPoint(30, -16));



    const double RADIUS = 16;//������ ���� �� ���



    MbLineSegment* pLine1 = new MbLineSegment(arrPnts[0], arrPnts[1]);
    MbArc* pArc1 = new MbArc(arrPnts[2], RADIUS, arrPnts[1], arrPnts[3], -1);

    MbLineSegment* pLine2 = new MbLineSegment(arrPnts[3], arrPnts[4]);
    MbLineSegment* pLine3 = new MbLineSegment(arrPnts[4], arrPnts[0]);


    MbContour* pContour = new MbContour();



    pContour->AddSegment(pLine1);
    pContour->AddSegment(pArc1);
    pContour->AddSegment(pLine2);
    pContour->AddSegment(pLine3);

    _arrContours.push_back(pContour);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_003()
{
    // ��������� �� (�� ��������� ��������� � ������� ��)
    MbPlacement3D pl;

    // �������� ���������� ��� ���� ������������
    RPArray<MbContour> arrContours;
    CreateSketch1er(arrContours);


    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));
    // ������, �������� ��������� ����������
    MbSweptData sweptData(*pPlaneXY, arrContours);
    // ������������ ������ ��� �������� ������������
    MbVector3D dir1(0, 0, -1);


    const double HEIGHT_FORWARD = 12.0, HEIGHT_BACKWARD = 12.0;//��������� ������������

    ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);



    // ����������� ��������� ������ �������� ���� � �������� ����������
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // ����� �������-������� ��� ���������� �������� ���� ������������
    MbSolid* pSolid = nullptr;
    MbResultType res = ::ExtrusionSolid(sweptData, dir1, nullptr, nullptr, false,
        extrusionParams, operNames, cNames, pSolid);

    RPArray<MbContour> arrContours1;//�������� �������� ������������ ���

    MbSNameMaker holeNames(ct_HoleSolid, MbSNameMaker::i_SideNone, 0);

    MbPlacement3D plHoleD16(MbCartPoint3D(0, 0, 12));

    plHoleD16.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 0)));

    BorerValues paramsD16;//��������� ��������� ��������� 16 

    paramsD16.type = BorerValues::bt_SimpleCylinder;


    paramsD16.diameter = 16; // ������� ���������

    paramsD16.depth = 24; //������� ���������




    MbPlacement3D plHoleD20(MbCartPoint3D(0, 0, 12));

    plHoleD20.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -40, 0)));

    BorerValues paramsD20;//��������� ��������� ��������� 20

    paramsD20.type = BorerValues::bt_SimpleCylinder;


    paramsD20.diameter = 20; // ������� ���������
    paramsD20.depth = 24; //������� ���������




    ::HoleSolid(pSolid, cm_Copy, plHoleD16, paramsD16, holeNames, pSolid);
    ::HoleSolid(pSolid, cm_Copy, plHoleD20, paramsD20, holeNames, pSolid);


    CreateSketch2er(arrContours1);

    MbSweptData sweptData1(*pPlaneXY, arrContours1);
    // ������������ ������ ��� �������� ������������
    MbVector3D dir(0, 0, -1);

    // ��������� �������� ������������, �������� �������� ���� ��� ���������� � ������
    // � � �������� ����������� ����� (������� ������������ � �����).
    const double HEIGHT_FORWARD1 = 9.5, HEIGHT_BACKWARD1 = 9.5;//��������� ������������ ���

    ExtrusionValues extrusionParams1(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);




    MbSNameMaker operNames1(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames1(0, 1, false);


    MbSolid* pSolid1 = nullptr;
    MbResultType res1 = ::ExtrusionSolid(sweptData1, dir, nullptr, nullptr, false,
        extrusionParams1, operNames1, cNames1, pSolid1);

    MbPlacement3D plHoleD162(MbCartPoint3D(0, 0, 0));

    plHoleD162.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(50, 0, 0)));

    BorerValues paramsD162;//��������� ��������� ��������� 16 �� ���

    paramsD162.type = BorerValues::bt_SimpleCylinder;

    paramsD162.diameter = 16;// ������� ���������


    paramsD162.depth = 19;// ������� ���������




    ::HoleSolid(pSolid1, cm_Copy, plHoleD162, paramsD162, holeNames, pSolid1);
    // ����������� ������������ ����

    MbSolid* pSolid3 = nullptr;

    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    MbResultType res6 = ::BooleanResult(*pSolid, cm_Copy, *pSolid1, cm_Copy, bo_Union, flagsBool, operBoolNames, pSolid3);

    SolidSPtr MainSolid(pSolid3);

    ::DeleteItem(pSolid3);
    ::DeleteItem(pSolid);
    ::DeleteItem(pSolid1);

    return MainSolid;
}