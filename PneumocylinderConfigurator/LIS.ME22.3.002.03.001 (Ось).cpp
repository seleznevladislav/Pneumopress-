#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketch5432(RPArray<MbContour>& _arrContours)
{
    double rad_osn = 8; // радиус самой длинной части оси
    double rad_b = 10.5; // радиус большего цилиндра-шляпки 
    double height = 51; // общая высота оси 
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


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_03_001()
{

    // вращение 

    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> arrContours;
    CreateSketch5432(arrContours);

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


    // построение фасок 

        // 2) Объект-именователь для операции построения фасок
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    // 3) Указание значений параметров операции построения фасок
    SmoothValues params;
    // Длины катетов фаски
    params.distance1 = 0.5;
    params.distance2 = 0.5;
    params.form = st_Chamfer;
    params.prolong = true;
    params.smoothCorner = SmoothValues::ec_uniform;

    RPArray<MbCurveEdge> allEdges(4, 1);
    pOs1->GetEdges(allEdges);

    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[0]);
    initCurves.Add(allEdges[14]);

    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> initBounds(0, 1);

    // 6) Вызов функции построения фасок
    MbSolid* pOs1_r = NULL;
    MbResultType res1 = ::ChamferSolid(*pOs1, cm_Copy, initCurves,
        params, chamferNames, pOs1_r);

    SolidSPtr MainSolid(pOs1_r);

    // Уменьшение счетчиков ссылок динамических объектов ядра
    ::DeleteItem(pOs1);
    ::DeleteItem(pOs1_r);

    return MainSolid;
}