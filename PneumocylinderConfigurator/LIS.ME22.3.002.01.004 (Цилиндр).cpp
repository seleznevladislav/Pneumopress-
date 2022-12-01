#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_004(double length = 265)
{

    //параметры фасок
    double faska1 = 1;
    double faska2 = 1;
    //высот ступеньки
    double height_Cyl_tor = 3;
    //общая высота цилинда
    double diff_length = length - 165;
    double height_Cyl_global = diff_length + 65;
    //наибольший радиус
    double radius_Cyl_b = 87 / 2;
    //внутренний радиус
    double radius_Cyl_v = 40;
    //радиус ступеньки
    double radius_Cyl_s = 83 / 2;

    //---------------------основной цилиндр-----------------------------------------------   
    MbCartPoint3D baseCenter1(0, 0, 0); // Центр первого основания
    MbCartPoint3D baseCenter2(0, height_Cyl_global, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase2(radius_Cyl_b, height_Cyl_global, 0);
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
    //---------------------------------------------------------------------------------------
    MbCartPoint3D baseCenter00(0, 0, 0); // Центр первого основания
    MbCartPoint3D baseCenter01(0, height_Cyl_global, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase00(radius_Cyl_v, height_Cyl_global, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf0 = NULL;
    MbResultType resCylSurf0 = ::ElementarySurface(baseCenter00, baseCenter01, pntOnBase00,
        st_CylinderSurface, pCylSurf0);
    // Построение цилиндрического тела
    MbSolid* pCy02 = nullptr;
    if (resCylSurf0 == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCy00(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid00 = ::ElementarySolid(*pCylSurf0, namesCy00, pCy02);
    }
    //------------булевая операция вычитания--------------------------------------------------  
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    // Флаги булевой операции: построение замкнутого тела с объединением
    // подобных граней и ребер.
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // Результирующее тело
    MbSolid* pSolid2 = NULL;
    MbResultType res0 = ::BooleanResult(*pCy, cm_Copy, *pCy02, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid2);
    //--------------------нижняя ступенька--------------------------------------------------------------------
    MbCartPoint3D baseCenter14(0, 0, 0); // Центр первого основания
    MbCartPoint3D baseCenter24(0, height_Cyl_tor, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase24(radius_Cyl_b, height_Cyl_tor, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf4 = NULL;
    MbResultType resCylSurf4 = ::ElementarySurface(baseCenter14, baseCenter24, pntOnBase24,
        st_CylinderSurface, pCylSurf4);
    // Построение цилиндрического тела
    MbSolid* pCyl4 = nullptr;
    if (resCylSurf4 == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl4(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid4 = ::ElementarySolid(*pCylSurf4, namesCyl4, pCyl4);

    }
    //----------------------------------------------------------------------------------------------
    MbCartPoint3D baseCenter12(0, 0, 0); // Центр первого основания
    MbCartPoint3D baseCenter22(0, height_Cyl_tor, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase22(radius_Cyl_s, height_Cyl_tor, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf2 = NULL;
    MbResultType resCylSurf2 = ::ElementarySurface(baseCenter12, baseCenter22, pntOnBase22,
        st_CylinderSurface, pCylSurf2);
    // Построение цилиндрического тела
    MbSolid* pCy2 = nullptr;
    if (resCylSurf == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl2(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid2 = ::ElementarySolid(*pCylSurf2, namesCyl2, pCy2);
    }
    //------------булевая операция вычитания-------------------------------------------------- 
    MbSolid* pSolid3 = NULL;
    MbResultType res1 = ::BooleanResult(*pCyl4, cm_Copy, *pCy2, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid3);
    //булевая операция объединения (добавлеие нижней ступеньки к цилиндру_---------------------------------------
    MbSolid* pSolid4 = NULL;
    MbResultType res2 = ::BooleanResult(*pSolid2, cm_Copy, *pSolid3, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid4);
    //--------------------верхняя ступенька--------------------------------------------------------------------
    MbCartPoint3D baseCenter15(0, height_Cyl_global - height_Cyl_tor, 0); // Центр первого основания
    MbCartPoint3D baseCenter25(0, height_Cyl_global, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase25(radius_Cyl_b, height_Cyl_global, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf5 = NULL;
    MbResultType resCylSurf5 = ::ElementarySurface(baseCenter15, baseCenter25, pntOnBase25,
        st_CylinderSurface, pCylSurf5);
    // Построение цилиндрического тела
    MbSolid* pCyl5 = nullptr;
    if (resCylSurf5 == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl5(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid5 = ::ElementarySolid(*pCylSurf5, namesCyl5, pCyl5);
    }
    //----------------------------------------------------------------------------------------------
    MbCartPoint3D baseCenter16(0, height_Cyl_global - height_Cyl_tor, 0); // Центр первого основания
    MbCartPoint3D baseCenter26(0, height_Cyl_global, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase26(radius_Cyl_s, height_Cyl_global, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf6 = NULL;
    MbResultType resCylSurf6 = ::ElementarySurface(baseCenter16, baseCenter26, pntOnBase26,
        st_CylinderSurface, pCylSurf6);
    // Построение цилиндрического тела
    MbSolid* pCy6 = nullptr;
    if (resCylSurf == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl6(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid6 = ::ElementarySolid(*pCylSurf6, namesCyl6, pCy6);
    }
    //------------булевая операция вычитания-------------------------------------------------- 
    MbSolid* pSolid5 = NULL;
    MbResultType res7 = ::BooleanResult(*pCyl5, cm_Copy, *pCy6, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid5);
    //булевая операция объединения (добавлеие верхней ступеньки к цилиндру_---------------------------------------
    MbSolid* pSolid6 = NULL;
    MbResultType res8 = ::BooleanResult(*pSolid4, cm_Copy, *pSolid5, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid6);
    //---------------фаска верхняя-------------------------------------------------------------------
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params;
    // Длины катетов фаски
    params.distance1 = faska1;
    params.distance2 = faska2;
    // Тип фаски - построение фаски с заданными катетами
    params.form = st_Chamfer;
    // Режим автоматического скругления ребер, гладко стыкующиеся с ребрами
    // из входного массива
    params.prolong = true;
    // Способ скругления троек ребер
    params.smoothCorner = SmoothValues::ec_uniform;
    // 4) Формирование массива с ребрами для скругления.
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges(4, 1);
    pSolid6->GetEdges(allEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[1]);
    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> initBounds(0, 1);
    // 6) Вызов функции построения фасок
    MbSolid* pResult2 = NULL;
    MbResultType res9 = ::ChamferSolid(*pSolid6, cm_Copy, initCurves,
        params, chamferNames, pResult2);
    //--------------------фаска нижняя-----------------------------------------------------------
    params.distance1 = faska1;
    params.distance2 = faska2;
    // Тип фаски - построение фаски с заданными катетами
    params.form = st_Chamfer;
    // Режим автоматического скругления ребер, гладко стыкующиеся с ребрами
    // из входного массива
    params.prolong = true;
    // Способ скругления троек ребер
    params.smoothCorner = SmoothValues::ec_uniform;
    // 4) Формирование массива с ребрами для скругления.
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges2(4, 1);
    pResult2->GetEdges(allEdges2);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> initCurves2(4, 1);
    initCurves2.Add(allEdges2[8]);
    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> initBounds2(0, 1);
    // 6) Вызов функции построения фасок
    MbSolid* pResult1 = NULL;
    MbResultType res10 = ::ChamferSolid(*pResult2, cm_Copy, initCurves2,
        params, chamferNames, pResult1);


    SolidSPtr MainSolid(pResult1);

    ::DeleteItem(pResult1);
    ::DeleteItem(pResult2);
    ::DeleteItem(pSolid6);
    ::DeleteItem(pSolid5);
    ::DeleteItem(pCy6);
    ::DeleteItem(pCyl5);
    ::DeleteItem(pSolid4);
    ::DeleteItem(pSolid3);
    ::DeleteItem(pCy2);
    ::DeleteItem(pCyl4);
    ::DeleteItem(pSolid2);
    ::DeleteItem(pCy02);
    ::DeleteItem(pCy);

    return MainSolid;
}