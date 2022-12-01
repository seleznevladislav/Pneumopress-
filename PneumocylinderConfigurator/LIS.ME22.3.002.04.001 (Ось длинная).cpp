#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketchAxe(RPArray<MbContour>& _arrContours)
{
    // создание эскиза для вращения   
    double rad_osn = 10; // радиус самой длинной части оси
    double rad_b = 13; // радиус большего цилиндра-шляпки 
    double height = 113; // общая высота оси 
    double height_v = 4; // высота цилиндра шляпки
    double height_prot = 1.5; // высота проточки под шляпкой 

    SArray<MbCartPoint> arrPnts(12);
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 0));
    arrPnts.Add(MbCartPoint(rad_osn, 1.65));
    arrPnts.Add(MbCartPoint(rad_osn - 2, 1.65));
    arrPnts.Add(MbCartPoint(rad_osn - 2, 3));
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

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_04_001()
{


    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> arrContours;
    CreateSketchAxe(arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Ось вращения для построения тела:
    MbAxis3D axis(pl.GetAxisY());

    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* pOs = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pOs);

    // фаски   
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    SmoothValues params;
    // Длины катетов фаски
    params.distance1 = 0.5;
    params.distance2 = 0.5;
    params.form = st_Chamfer;
    params.prolong = true;
    params.smoothCorner = SmoothValues::ec_uniform;

    RPArray<MbCurveEdge> allEdges(4, 1);
    pOs->GetEdges(allEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[0]);
    initCurves.Add(allEdges[14]);

    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> initBounds(0, 1);
    // 6) Вызов функции построения фасок
    MbSolid* pOs_r = NULL;
    ::ChamferSolid(*pOs, cm_Copy, initCurves,
        params, chamferNames, pOs_r);



    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    double CENTRA = 55;
    MbSolid* pCylSolid = NULL;
    MbSolid* pCylSolid1 = NULL;
    SArray<MbCartPoint3D> cylPnts(3);
    cylPnts.Add(MbCartPoint3D(0, CENTRA, 8));
    cylPnts.Add(MbCartPoint3D(0, CENTRA, 20));
    cylPnts.Add(MbCartPoint3D(0, CENTRA + 10.0, 0));
    SArray<MbCartPoint3D> cylPnts1(3);
    cylPnts1.Add(MbCartPoint3D(8, CENTRA, 0));
    cylPnts1.Add(MbCartPoint3D(20, CENTRA, 0));
    cylPnts1.Add(MbCartPoint3D(0, CENTRA + 10.0, 0));

    MbResultType resEx1 = ::ElementarySolid(cylPnts, et_Cylinder,
        namesElSolid, pCylSolid);
    MbResultType resEx2 = ::ElementarySolid(cylPnts1, et_Cylinder,
        namesElSolid, pCylSolid1);

    //Переменные для выдавливания
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbResultType resBool4 = ::BooleanResult(*pOs_r, cm_Copy, *pCylSolid, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOs_r);
    MbResultType resBool5 = ::BooleanResult(*pOs_r, cm_Copy, *pCylSolid1, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOs_r);


    SolidSPtr MainSolid(pOs_r);

    // Уменьшение счетчиков ссылок динамических объектов ядра
    ::DeleteItem(pOs);
    ::DeleteItem(pOs_r);
    ::DeleteItem(pCylSolid);
    ::DeleteItem(pCylSolid1);

    return MainSolid;
}