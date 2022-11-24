#include "BuildMathModel.h"

using namespace BuildMathModel;


void CreateSketchKL(RPArray<MbContour>& _arrContours)
{
    double d = 72; //внутренний диаметр
    double D = 80.4; //внешний диаметр
    double W = 7; // высота кольца
    SArray<MbCartPoint> arrPnts(8);
    arrPnts.Add(MbCartPoint(d / 2, 0));
    arrPnts.Add(MbCartPoint(d / 2, W));
    arrPnts.Add(MbCartPoint(D / 2, W));
    arrPnts.Add(MbCartPoint(D / 2, 0));

    // Построение единой ломаной внешнего контура по точкам
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContourPolyline);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_004()
{

    const double DEG_TO_RAD = M_PI / 180.0;
    double DEG = 360; //угол поворота эскиза

    MbPlacement3D pl;


    RPArray<MbContour> arrContours;
    CreateSketchKL(arrContours);


    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);



    RevolutionValues revParms(DEG * DEG_TO_RAD, 0, 0);


    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);


    MbAxis3D axis(pl.GetAxisY());


    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* pSolid = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms,
        operNames, cNames, pSolid);

    SolidSPtr MainSolid(pSolid);

    return MainSolid;
}