#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketchvc(RPArray<MbContour>& _arrContours)
{
    double rad_osn = 8; // радиус самой длинной части оси
    double rad_b = 10.5; // радиус большего цилиндра-шляпки 
    double height = 43; // общая высота оси 
    double height_v = 3; // высота цилиндра шляпки
    double height_prot = 1.5; // высота проточки под шляпкой 

    // создание эскиза для вращения   

    SArray<MbCartPoint> arrPnts(12);
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 1.85));
    arrPnts.Add(MbCartPoint(7.6, 1.85));
    arrPnts.Add(MbCartPoint(7.6, 3));
    arrPnts.Add(MbCartPoint(rad_osn, 3));
    arrPnts.Add(MbCartPoint(rad_osn, height - height_prot - height_v));
    arrPnts.Add(MbCartPoint(rad_osn - 0.1, height - height_prot - height_v));
    arrPnts.Add(MbCartPoint(rad_osn - 0.1, height - height_v));
    arrPnts.Add(MbCartPoint(rad_b, height - height_v));
    arrPnts.Add(MbCartPoint(rad_b, height));
    arrPnts.Add(MbCartPoint(0, height));

    // Построение единой ломаной внешнего контура по точкам

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContourPolyline);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_012()
{

    // вращение 

    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> arrContours;
    CreateSketchvc(arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    // Именователи для операции построения тела вращения и для контуров образующей
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Ось вращения для построения тела:
    MbAxis3D axis(pl.GetAxisY());

    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* pOs1 = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pOs1);



    // фаски 

    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params;
    // Длины катетов фаски
    params.distance1 = 0.5;
    params.distance2 = 0.5;
    params.form = st_Chamfer;
    params.prolong = true;
    // Способ скругления троек ребер
    params.smoothCorner = SmoothValues::ec_uniform;

    // 4) Формирование массива с ребрами для скругления.
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges(4, 1);
    pOs1->GetEdges(allEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[0]);
    initCurves.Add(allEdges[14]);

    RPArray<MbFace> initBounds(0, 1);

    // 6) Вызов функции построения фасок
    MbSolid* pOs1_r = NULL;
    MbResultType res1 = ::ChamferSolid(*pOs1, cm_Copy, initCurves,
        params, chamferNames, pOs1_r);

    SolidSPtr MainSolid(pOs1_r);

    ::DeleteItem(pOs1_r);
    ::DeleteItem(pOs1);

    return MainSolid;

}