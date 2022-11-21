#include "BuildMathModel.h"
using namespace c3d;
using namespace std;
using namespace BuildMathModel;

double a = 200.0;//длина
double b = 165.0;//ширина
double b_pol = 82.5;//половина ширины
double c = 16.0;//высота
double razn = 200 / 8; //=25
double r = 10.0;//радиус центрального отверстия

void CreateSketchYI(RPArray<MbContour>& _arrContours)
{
    const double rad = 6.8 / 2;
    const double ots = 20.0;//отступ
    const double a1 = 80.0;//половина длины прямоуг-ка отверстий
    const double b1 = 60.0;//половина ширины

    MbArc* pCircle1 = new MbArc(MbCartPoint(ots - 100, ots - 80), rad);//создается окружность
    MbArc* pCircle2 = new MbArc(MbCartPoint(ots + a1 - 100, ots - 80), rad);
    MbArc* pCircle3 = new MbArc(MbCartPoint(ots + 2 * a1 - 100, ots - 80), rad);

    MbArc* pCircle4 = new MbArc(MbCartPoint(ots + 2 * a1 - 100, ots + b1 - 80), rad);
    MbArc* pCircle5 = new MbArc(MbCartPoint(ots + 2 * a1 - 100, ots + 2 * b1 - 80), rad);

    MbArc* pCircle6 = new MbArc(MbCartPoint(ots + a1 - 100, ots + 2 * b1 - 80), rad);
    MbArc* pCircle7 = new MbArc(MbCartPoint(ots - 100, ots + 2 * b1 - 80), rad);
    MbArc* pCircle8 = new MbArc(MbCartPoint(ots - 100, ots + b1 - 80), rad);

    _arrContours.push_back(new MbContour(*pCircle1, true));
    _arrContours.push_back(new MbContour(*pCircle2, true));
    _arrContours.push_back(new MbContour(*pCircle3, true));
    _arrContours.push_back(new MbContour(*pCircle4, true));
    _arrContours.push_back(new MbContour(*pCircle5, true));
    _arrContours.push_back(new MbContour(*pCircle6, true));
    _arrContours.push_back(new MbContour(*pCircle7, true));
    _arrContours.push_back(new MbContour(*pCircle8, true));
}

void CreateSketch1YI(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> arrPnts(6);

    arrPnts.Add(MbCartPoint(0 - 100, 0 - 80));
    arrPnts.Add(MbCartPoint(a - 100, 0 - 80));
    arrPnts.Add(MbCartPoint(a - 100, b - razn - 80));
    arrPnts.Add(MbCartPoint(a - razn - 100, b - 80));
    arrPnts.Add(MbCartPoint(razn - 100, b - 80));
    arrPnts.Add(MbCartPoint(0 - 100, b - razn - 80));
    //arrPnts.Add(MbCartPoint(0, 0));

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);
    _arrContours.push_back(pContourPolyline);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_016()
{
    //MbPlacement3D pl;

    MbSolid* pPrism = nullptr;
    {
        RPArray<MbContour> arrContours1;
        CreateSketch1YI(arrContours1);

        MbPlane* pPlaneXZ1 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 0, 1));
        MbSweptData sweptData1(*pPlaneXZ1, arrContours1);
        MbVector3D dirY1(0, 1, 0);
        const double HEIGHT_FORWARD1 = c, HEIGHT_BACKWARD1 = 0;
        ExtrusionValues extrusionParams1(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);

        MbSNameMaker names1(1, MbSNameMaker::i_SideNone, 0);
        PArray<MbSNameMaker> cNames1(0, 1, false);

        MbResultType resholes = ::ExtrusionSolid(sweptData1, dirY1, nullptr, nullptr, false, extrusionParams1, names1, cNames1, pPrism);

    }
    // Создание образующей для тела выдавливания

    //Построение центрального отверстия
    MbSolid* pCyl = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(0, 0, 0));//центр СК
        points.Add(MbCartPoint3D(0, c, 0));//высота цилиндра
        points.Add(MbCartPoint3D(r, c, 0));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCyl);
    }

    //Построение отверстий
    MbSolid* pSolidholes = nullptr;
    {
        RPArray<MbContour> arrContours;
        CreateSketchYI(arrContours);

        MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0),
            MbCartPoint3D(1, 0, 0),
            MbCartPoint3D(0, 0, 1));
        MbVector3D dirY(0, 1, 0);
        MbSweptData sweptData(*pPlaneXZ, arrContours);
        const double HEIGHT_FORWARD = c, HEIGHT_BACKWARD = 0;
        ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        PArray<MbSNameMaker> cNames(0, 1, false);

        MbResultType resholes = ::ExtrusionSolid(sweptData, dirY, nullptr, nullptr, false, extrusionParams, names, cNames, pSolidholes);
    }


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
    //остальные
    MbSolid* pSolid1 = NULL;
    MbResultType res1 = ::BooleanResult(*pSolid, cm_Copy, *pSolidholes, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid1);

    ::DeleteItem(pPrism);
    ::DeleteItem(pCyl);
    ::DeleteItem(pSolidholes);
    ::DeleteItem(pSolid);


    SolidSPtr MainSolid(pSolid1);
    return MainSolid;
}