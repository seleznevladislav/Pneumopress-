#include "BuildMathModel.h"

using namespace BuildMathModel;

double h = 6.0; //толщина
double ln = 110; //длина

double pP = 26.5; //передняя полка
double zP = 29; //задняя полка
double pS = 45; //средняя передняя полка
double zS = 40; //средняя задняя полка

double rad1u = 0.74;
double rad2u = 6.74;

void CreateSketchvf(RPArray<MbContour>& _arrContours) {
    SArray<MbCartPoint> arrPnts(12);
    arrPnts.Add(MbCartPoint(0 - ln / 2, 0));
    arrPnts.Add(MbCartPoint(0 - ln / 2, h));
    arrPnts.Add(MbCartPoint(pP - ln / 2, h));
    arrPnts.Add(MbCartPoint(pP + h - ln / 2, 2 * h));
    arrPnts.Add(MbCartPoint(pP + h + pS - ln / 2, 2 * h));
    arrPnts.Add(MbCartPoint(ln - pP - ln / 2, h));

    arrPnts.Add(MbCartPoint(ln - ln / 2, h));
    arrPnts.Add(MbCartPoint(ln - ln / 2, 0));
    arrPnts.Add(MbCartPoint(ln - zP - ln / 2, 0));
    arrPnts.Add(MbCartPoint(ln - zP - h - ln / 2, h));
    arrPnts.Add(MbCartPoint(zP + h - ln / 2, h));
    arrPnts.Add(MbCartPoint(zP - ln / 2, 0));

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = nullptr;
    ::FilletPolyContour(pPolyline, rad1u, false, arrPnts[2], pContourPolyline);

    ptrdiff_t idxSideRight3 = 3;
    //ptrdiff_t idxSideRight2 = 4;
    ptrdiff_t idxSideRight5 = 5;
    ptrdiff_t idxSideRight7 = 7;

    ptrdiff_t idxSideRight12 = 12;
    ptrdiff_t idxSideRight13 = 13;
    ptrdiff_t idxSideRight14 = 14;

    // Добавление скруглений
    pContourPolyline->FilletTwoSegments(idxSideRight3, rad2u);
    //pContourPolyline->FilletTwoSegments(idxSideRight2, 6.74);
    pContourPolyline->FilletTwoSegments(idxSideRight5, rad2u);
    pContourPolyline->FilletTwoSegments(idxSideRight7, rad1u);

    pContourPolyline->FilletTwoSegments(idxSideRight12, rad1u);
    pContourPolyline->FilletTwoSegments(idxSideRight13, rad1u);
    pContourPolyline->FilletTwoSegments(idxSideRight14, rad1u);

    _arrContours.push_back(pContourPolyline);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_010()
{
    //////выдавливание шатуна
    double c = 30;
    MbSolid* pSolidbase = nullptr;

    RPArray<MbContour> arrContours;
    CreateSketchvf(arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, -c / 2),
        MbCartPoint3D(1, 0, -c / 2),
        MbCartPoint3D(0, 1, -c / 2));
    MbVector3D dirZ(0, 0, 1);
    MbSweptData sweptData(*pPlaneXY, arrContours);
    const double HEIGHT_FORWARD = c, HEIGHT_BACKWARD = 0;
    ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

    MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    MbResultType resbase = ::ExtrusionSolid(sweptData, dirZ, nullptr, nullptr, false, extrusionParams, names, cNames, pSolidbase);

    //////Добавление внутренних сопряжений V
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    SmoothValues paramsV;
    paramsV.distance1 = rad2u;
    paramsV.distance2 = rad2u;
    paramsV.form = st_Fillet;
    paramsV.conic = 0;
    paramsV.prolong = false;
    paramsV.smoothCorner = SmoothValues::ec_uniform;
    paramsV.keepCant = ts_negative;
    paramsV.strict = true;

    RPArray<MbCurveEdge> allEdgesV(4, 1);
    pSolidbase->GetEdges(allEdgesV);
    RPArray<MbCurveEdge> initCurvesV(4, 1);
    initCurvesV.Add(allEdgesV[1]);
    initCurvesV.Add(allEdgesV[17]);
    RPArray<MbFace> initBounds1(0, 1);
    MbSolid* pResultV = NULL;
    MbResultType resV = ::FilletSolid(*pSolidbase, cm_Copy, initCurvesV, initBounds1,
        paramsV, filletNames, pResultV);


    //////добавление боковых сопряжений(ушки)
    SmoothValues paramsB;
    paramsB.distance1 = c / 2;//=15
    paramsB.distance2 = c / 2;
    paramsB.form = st_Fillet;
    paramsB.conic = 0;
    paramsB.prolong = false;
    paramsB.smoothCorner = SmoothValues::ec_uniform;
    paramsB.keepCant = ts_negative;
    paramsB.strict = true;

    RPArray<MbCurveEdge> allEdgesB(4, 1);
    pResultV->GetEdges(allEdgesB);
    RPArray<MbCurveEdge> initCurvesB(4, 1);
    initCurvesB.Add(allEdgesB[24]);
    initCurvesB.Add(allEdgesB[26]);
    initCurvesB.Add(allEdgesB[54]);
    initCurvesB.Add(allEdgesB[55]);

    RPArray<MbFace> initBoundsB(0, 1);
    MbSolid* pResultB = NULL;
    MbResultType resB = ::FilletSolid(*pResultV, cm_Copy, initCurvesB, initBoundsB,
        paramsB, filletNames, pResultB);

    //////Построение отверстия в ушке 
    double RAD = 8; //радиус отверстия в ушке
    SArray<MbCartPoint3D> points(3);
    points.Add(MbCartPoint3D(6.5 + RAD - ln / 2, 0, 0));
    points.Add(MbCartPoint3D(6.5 + RAD - ln / 2, h, 0));
    points.Add(MbCartPoint3D(6.5 + RAD - ln / 2, h, RAD));
    MbSolid* pCyl = nullptr;
    ::ElementarySolid(points, et_Cylinder, names, pCyl);

    //////Создание плоскости для создания второго отверстия в ушке
    MbPlacement3D VerticalPlane(MbVector3D(0, 0, 1), /* Ось Z локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(55 - 55, 0, 0 /* Начало координат локальной СК */));

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    MbSolid* pCyl1 = NULL;
    MbResultType res5 = ::MirrorSolid(*pCyl, VerticalPlane, operNames, pCyl1);

    //////Выдавливание получившихся отверстий

    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    MbSolid* pSolid1 = NULL;
    MbSolid* pSolid2 = NULL;
    MbResultType res1 = ::BooleanResult(*pResultB, cm_Copy, *pCyl, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid1);
    MbResultType res2 = ::BooleanResult(*pSolid1, cm_Copy, *pCyl1, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid2);


    ::DeleteItem(pSolidbase);
    ::DeleteItem(pResultB);
    ::DeleteItem(pResultV);
    ::DeleteItem(pSolid1);

    SolidSPtr MainSolid(pSolid2);
    return MainSolid;
}