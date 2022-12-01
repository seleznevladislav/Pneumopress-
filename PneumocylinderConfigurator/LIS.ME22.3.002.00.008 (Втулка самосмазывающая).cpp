#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_008()
{
    //внутренний цилиндр
    double height_Cyl = 25;// высота габаритная
    double radius_Cyl = 35 / 2;// радиус внутреннего цилиндра
    double height_Cyl_vnesh = 25 - 21;//высота бортика
    double radius_Cyl_vnesh = 42 / 2;//габаритный радиус
    double tolshina = 10;//толцина внеутреннего цилиндра
    double faska1 = 2;
    double faska2 = 0.5;
    double sopr = 0.5;


    MbCartPoint3D baseCenter1(0, 0, 0); // Центр первого основания
    MbCartPoint3D baseCenter2(0, height_Cyl, 0); // Центр второго основания

    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase2(radius_Cyl, height_Cyl, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf = NULL;
    MbResultType resCylSurf = ::ElementarySurface(baseCenter1, baseCenter2, pntOnBase2,
        st_CylinderSurface, pCylSurf);
    // Построение цилиндрического тела
    MbSolid* pCy = nullptr;
    if (resCylSurf == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf, namesCyl, pCy);

    }

    //--------------------------внешний цилиндр------------------------------------------------------   
    MbCartPoint3D baseCenter_vnesh1(0, 0, 0); // Центр первого основания
    MbCartPoint3D baseCenter_vnesh2(0, height_Cyl_vnesh, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_vnesh2(radius_Cyl_vnesh, height_Cyl_vnesh, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_vnesh = NULL;
    MbResultType resCylSurf_vnesh = ::ElementarySurface(baseCenter_vnesh1, baseCenter_vnesh2, pntOnBase_vnesh2,
        st_CylinderSurface, pCylSurf_vnesh);
    // Построение цилиндрического тела
    MbSolid* pCy_vnesh = nullptr;
    if (resCylSurf_vnesh == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_vnesh, namesCyl, pCy_vnesh);

    }
    //-------------булева операция объединения----------------------------------------------------------------
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    // Флаги булевой операции: построение замкнутого тела с объединением
    // подобных граней и ребер.
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // Результирующее тело
    MbSolid* vtulka_bez_vireza = NULL;
    MbResultType res0 = ::BooleanResult(*pCy, cm_Copy, *pCy_vnesh, cm_Copy, bo_Union,
        flagsBool, operBoolNames, vtulka_bez_vireza);

    //-------------------------------внутренний цилиндр-------------------------------------------------  
    double radius_Cyl_virez = radius_Cyl - tolshina / 2;
    MbCartPoint3D baseCenter_virez1(0, 0, 0); // Центр первого основания
    MbCartPoint3D baseCenter_virez2(0, height_Cyl, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_virez2(radius_Cyl_virez, height_Cyl, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_virez = NULL;
    MbResultType resCylSurf_virez = ::ElementarySurface(baseCenter_virez1, baseCenter_virez2, pntOnBase_virez2,
        st_CylinderSurface, pCylSurf_virez);
    // Построение цилиндрического тела
    MbSolid* pCy_virez = nullptr;
    if (resCylSurf_virez == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_virez, namesCyl, pCy_virez);

    }
    MbSolid* vtulka_samosmaz = NULL;
    MbResultType res = ::BooleanResult(*vtulka_bez_vireza, cm_Copy, *pCy_virez, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, vtulka_samosmaz);
    //---------------------------фаска1-------------------------------------------------------

    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);


    SmoothValues params;
    // Длины катетов фаски
    params.distance1 = faska1;
    params.distance2 = faska1;
    // Тип фаски - построение фаски с заданными катетами
    params.form = st_Chamfer;
    // Режим автоматического скругления ребер, гладко стыкующиеся с ребрами
    // из входного массива
    params.prolong = true;
    // Способ скругления троек ребер
    params.smoothCorner = SmoothValues::ec_uniform;


    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges(4, 1);
    vtulka_samosmaz->GetEdges(allEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> initCurves(4, 1);

    initCurves.Add(allEdges[0]);

    // Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> initBounds(0, 1);

    //Вызов функции построения фасок
    MbSolid* pResult = NULL;
    MbResultType res2 = ::ChamferSolid(*vtulka_samosmaz, cm_Copy, initCurves,
        params, chamferNames, pResult);
    //-----------------------------------------------фаска2--------------------------------------
        // Длины катетов фаски
    params.distance1 = faska2;
    params.distance2 = faska2;
    // Тип фаски - построение фаски с заданными катетами
    params.form = st_Chamfer;
    // Режим автоматического скругления ребер, гладко стыкующиеся с ребрами
    // из входного массива
    params.prolong = true;
    // Способ скругления троек ребер
    params.smoothCorner = SmoothValues::ec_uniform;
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges1(4, 1);
    pResult->GetEdges(allEdges1);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> initCurves1(4, 1);
    initCurves1.Add(allEdges1[2]);
    initCurves1.Add(allEdges1[3]);
    initCurves1.Add(allEdges1[1]);
    // Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> initBounds1(0, 1);
    //Вызов функции построения фасок
    MbSolid* pResult1 = NULL;
    MbResultType res3 = ::ChamferSolid(*pResult, cm_Copy, initCurves1,
        params, chamferNames, pResult1);
    //---------------------------------сопряжение-------------------------------
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    params.distance1 = sopr;
    params.distance2 = sopr;
    params.form = st_Fillet;
    params.conic = 0;
    // Требуется скруглять ребра, гладко стыкующиеся с ребрами из входного массива
    params.prolong = true;
    // Способ скругления троек ребер
    params.smoothCorner = SmoothValues::ec_uniform;
    // Флаг сохранения кромки – режим сохранения поверхности
    params.keepCant = ts_neutral;
    // Строгое скругление
    params.strict = false;
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges2(4, 1);
    pResult1->GetEdges(allEdges2);
    // В массив ребер для скругления помещается только одно ребро
    RPArray<MbCurveEdge> initCurves2(4, 1);
    initCurves2.Add(allEdges2[9]);
    // 5) Массив граней для обрезки
    RPArray<MbFace> initBounds2(0, 1);
    // 6) Вызов функции скругления ребер.
    MbSolid* detail_008 = NULL;
    MbResultType res4 = ::FilletSolid(*pResult1, cm_Copy, initCurves2, initBounds2,
        params, filletNames, detail_008);

    SolidSPtr MainSolid(detail_008);

    ::DeleteItem(detail_008);
    ::DeleteItem(pResult1);
    ::DeleteItem(pResult);
    ::DeleteItem(vtulka_samosmaz);
    ::DeleteItem(pCy_virez);
    ::DeleteItem(vtulka_bez_vireza);
    ::DeleteItem(pCy_vnesh);
    ::DeleteItem(pCy);

    return MainSolid;
}