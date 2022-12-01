#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketchKO(RPArray<MbContour>& _arrContours)
{
    // создание эскиза для вращения   

    double height_k = 25; // высота колпачка
    double vne_rad_k = 16; // внешний радиус колпачка 
    double vnut_rad_k = 12.5; //внутренний радиус 

    SArray<MbCartPoint> arrPnts(5);
    arrPnts.Add(MbCartPoint(vnut_rad_k, height_k));
    arrPnts.Add(MbCartPoint(vne_rad_k, height_k));
    arrPnts.Add(MbCartPoint(vne_rad_k, 5));
    arrPnts.Add(MbCartPoint(14.66, 0));
    arrPnts.Add(MbCartPoint(vnut_rad_k, 0));

    // Построение единой ломаной внешнего контура по точкам

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContourPolyline);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_003()
{
    // вращение 

    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> arrContours;
    CreateSketchKO(arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    // Именователи для операции построения тела вращения и для контуров образующей
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Ось вращения для построения тела:
    MbAxis3D axis(pl.GetAxisY());

    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* pKolp = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pKolp);


    // скругление ребра 


       // 2) Объект-именователь для операции скругления ребер
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    // 3) Указание значений параметров операции скругления ребер
    SmoothValues params;
    //  SmoothValues params;
      // Радиусы кривизны на двух скругляемых поверхностях
    params.distance1 = 1;
    // Тип сопряжения – скругление по двум радиусам
    params.form = st_Fillet;
    // Форма профиля сопряжения - окружность
    params.conic = 0;
    // Требуется скруглять только ребра, переданные во входном массиве
    params.prolong = false;
    // Способ скругления троек ребер
    params.smoothCorner = SmoothValues::ec_uniform;
    // Флаг сохранения кромки – режим сохранения поверхности
    params.keepCant = ts_negative;
    // Строгое скругление
    params.strict = true;

    // 4) Формирование массива с ребрами для скругления.
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges(4, 1);
    pKolp->GetEdges(allEdges);
    // В массив ребер для скругления помещается только одно ребро
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[3]);

    // 5) Массив граней для обрезки – в данном примере пустой
    RPArray<MbFace> initBounds(0, 1);

    // 6) Вызов функции скругления ребер.
    // В результате выполняется скругление одного ребра – окружности,
    // по которой в исходном теле соединены цилиндр и пластина.
    MbSolid* pKolp_res = NULL;
    MbResultType res1 = ::FilletSolid(*pKolp, cm_Copy, initCurves, initBounds,
        params, filletNames, pKolp_res);

    SolidSPtr MainSolid(pKolp_res);

    ::DeleteItem(pKolp_res);
    ::DeleteItem(pKolp);

    return MainSolid;
}

