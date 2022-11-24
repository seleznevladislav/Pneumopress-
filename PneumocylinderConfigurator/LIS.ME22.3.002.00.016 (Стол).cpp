#include "BuildMathModel.h"

using namespace BuildMathModel;

double a = 200.0;//длина
double b = 165.0;//ширина
double c = 16.0;//высота
double razn = 200 / 8; //=25
double r = 10.0;//радиус центрального отверстия

void CreateSketch1vf(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(6);

    pnts.Add(MbCartPoint(-102.1, -84.65));
    pnts.Add(MbCartPoint(97.9, -84.65));
    pnts.Add(MbCartPoint(97.9, 73.7));
    pnts.Add(MbCartPoint(76.31, 95.24));//204.31-25.9-102.1, 255.24-75.35-84.65
    pnts.Add(MbCartPoint(-77.07, 95.24));
    pnts.Add(MbCartPoint(-102.1, 70.2));


    MbLineSegment* pS1 = new MbLineSegment(pnts[0], pnts[1]);
    MbLineSegment* pS2 = new MbLineSegment(pnts[1], pnts[2]);
    MbLineSegment* pS3 = new MbLineSegment(pnts[2], pnts[3]);
    MbLineSegment* pS4 = new MbLineSegment(pnts[3], pnts[4]);
    MbLineSegment* pS5 = new MbLineSegment(pnts[4], pnts[5]);
    MbLineSegment* pS6 = new MbLineSegment(pnts[5], pnts[0]);


    MbContour* pContour = new MbContour();

    pContour->AddSegment(pS1);
    pContour->AddSegment(pS2);
    pContour->AddSegment(pS3);
    pContour->AddSegment(pS4);
    pContour->AddSegment(pS5);
    pContour->AddSegment(pS6);

    _arrContours.push_back(pContour);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_016()
{
    MbSolid* pPrism = nullptr;
    {
        RPArray<MbContour> arrContours1;
        CreateSketch1vf(arrContours1);

        MbPlane* pPlaneXZ1 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 0, 1));
        MbSweptData sweptData1(*pPlaneXZ1, arrContours1);
        MbVector3D dirY1(0, 1, 0);
        const double HEIGHT_FORWARD1 = c, HEIGHT_BACKWARD1 = 0;
        ExtrusionValues extrusionParams1(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);

        MbSNameMaker names1(1, MbSNameMaker::i_SideNone, 0);
        PArray<MbSNameMaker> cNames1(0, 1, false);

        MbResultType resholes = ::ExtrusionSolid(sweptData1, dirY1, nullptr, nullptr, false, extrusionParams1, names1, cNames1, pPrism);

    }

    MbPlacement3D VerticalPlane3(MbVector3D(1, 0, 0),
        MbVector3D(0, 1, 0),
        MbCartPoint3D(0, 0, -28  /* 132-75.35-84.65 */));

    MbPlacement3D VerticalPlane4(MbVector3D(1, 0, 0),
        MbVector3D(0, 1, 0),
        MbCartPoint3D(0, 0, 2  /*162-75.35-84.65*/));

    MbPlacement3D VerticalPlane5(MbVector3D(0, 0, 1),
        MbVector3D(0, 1, 0),
        MbCartPoint3D(0, 0, 0 /* 128-25.9-102.1 */));

    MbPlacement3D VerticalPlane6(MbVector3D(0, 0, 1),
        MbVector3D(0, 1, 0),
        MbCartPoint3D(40, 0, 0 /* 168-25.9-102.1 */));



    //Построение центрального отверстия

    MbSolid* pCyl = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(0, 0, 0));//центр СК//128-25.9=102.1 160-75.35=84.65
        points.Add(MbCartPoint3D(0, 16, 0));//высота цилиндра
        points.Add(MbCartPoint3D(0, 16, 10));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCyl);
    }

    MbSolid* pCyl_Solid5 = NULL;
    MbSolid* pCyl_Solid6 = NULL;
    MbSolid* pCyl_Solid7 = NULL;
    MbSolid* pCyl_Solid8 = NULL;
    MbSolid* pCyl_Solid9 = NULL;
    MbSolid* pCyl_Solid10 = NULL;
    MbSolid* pCyl_Solid11 = NULL;
    MbSolid* pCyl_Solid12 = NULL;
    MbSolid* pCyl_Solid13 = NULL;

    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);

    SArray<MbCartPoint3D> cylPnts5;
    cylPnts5.Add(MbCartPoint3D(80, 0, -58));
    cylPnts5.Add(MbCartPoint3D(80, 16, -58));//102-75.35-84.65
    cylPnts5.Add(MbCartPoint3D(80, 16, -54.6));//105.4-75.35-84.65
    // Построение элементарного тела - цилиндра
    ::ElementarySolid(cylPnts5, et_Cylinder,
        namesElSolid, pCyl_Solid5);

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);

    ::MirrorSolid(*pCyl_Solid5, VerticalPlane3, operNames, pCyl_Solid6);
    ::MirrorSolid(*pCyl_Solid5, VerticalPlane4, operNames, pCyl_Solid7);
    ::MirrorSolid(*pCyl_Solid7, VerticalPlane5, operNames, pCyl_Solid8);
    ::MirrorSolid(*pCyl_Solid6, VerticalPlane5, operNames, pCyl_Solid9);
    ::MirrorSolid(*pCyl_Solid5, VerticalPlane5, operNames, pCyl_Solid10);
    ::MirrorSolid(*pCyl_Solid5, VerticalPlane6, operNames, pCyl_Solid11);
    ::MirrorSolid(*pCyl_Solid7, VerticalPlane6, operNames, pCyl_Solid13);


    //Выдавливание отверстий
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    //центральное
    MbSolid* pSolid = NULL;
    MbResultType res = ::BooleanResult(*pPrism, cm_Copy, *pCyl, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);


    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid5, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid6, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid7, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid8, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid9, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid10, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid11, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid13, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);


    SolidSPtr MainSolid(pSolid);

    ::DeleteItem(pSolid);
    ::DeleteItem(pPrism);
    ::DeleteItem(pCyl);
    ::DeleteItem(pCyl_Solid5);
    ::DeleteItem(pCyl_Solid6);
    ::DeleteItem(pCyl_Solid7);
    ::DeleteItem(pCyl_Solid8);
    ::DeleteItem(pCyl_Solid9);
    ::DeleteItem(pCyl_Solid10);
    ::DeleteItem(pCyl_Solid11);
    ::DeleteItem(pCyl_Solid12);
    ::DeleteItem(pCyl_Solid13);

    return MainSolid;
}