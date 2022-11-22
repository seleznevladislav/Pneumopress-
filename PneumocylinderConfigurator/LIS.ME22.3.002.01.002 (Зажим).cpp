#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_002()
{// Множитель для преобразования углов из градусной в радианную меру.

    //внутренний цилиндр
    double height_Cyl = 15;// высота габаритная
    double radius_Cyl = 70 / 2;// радиус внутреннего цилиндра
    double d_vnesh_otv = 55;//диаметр массива отверстий
    double r_otv = 12 / 2;//радиус большей части отверстия
    double r_otv_mal = 8 / 2;// радиус меньшей части отверстия
    double r_vnut = 40 / 2;//радиус внетреннего отверстия;



    MbCartPoint3D baseCenter1(0, -height_Cyl / 2, 0); // Центр первого основания
    MbCartPoint3D baseCenter2(0, height_Cyl / 2, 0); // Центр второго основания

    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase2(radius_Cyl, height_Cyl / 2, 0);
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
    MbCartPoint3D baseCenter_vnesh1(d_vnesh_otv / 2, -height_Cyl / 2, 0); // Центр первого основания
    MbCartPoint3D baseCenter_vnesh2(d_vnesh_otv / 2, height_Cyl / 2, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_vnesh2(d_vnesh_otv / 2 + r_otv, -height_Cyl / 2, 0);
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
    MbCartPoint3D baseCenter1_vnesh1(d_vnesh_otv / 2, -height_Cyl / 2, 0); // Центр первого основания
    MbCartPoint3D baseCenter1_vnesh2(d_vnesh_otv / 2, 0, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase1_vnesh2(d_vnesh_otv / 2 + r_otv, -height_Cyl / 2, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_vnesh1 = NULL;
    MbResultType resCylSurf_vnesh1 = ::ElementarySurface(baseCenter1_vnesh1, baseCenter1_vnesh2, pntOnBase1_vnesh2,
        st_CylinderSurface, pCylSurf_vnesh1);
    // Построение цилиндрического тела
    MbSolid* pCy_vnesh1 = nullptr;
    if (resCylSurf_vnesh1 == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_vnesh1, namesCyl, pCy_vnesh1);

    }
    MbCartPoint3D baseCenter2_vnesh1(d_vnesh_otv / 2, -height_Cyl / 2, 0); // Центр первого основания
    MbCartPoint3D baseCenter2_vnesh2(d_vnesh_otv / 2, 0, 0); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase2_vnesh2(d_vnesh_otv / 2 + r_otv_mal, -height_Cyl / 2, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_vnesh2 = NULL;
    MbResultType resCylSurf_vnesh2 = ::ElementarySurface(baseCenter2_vnesh1, baseCenter2_vnesh2, pntOnBase2_vnesh2,
        st_CylinderSurface, pCylSurf_vnesh2);
    // Построение цилиндрического тела
    MbSolid* pCy_vnesh2 = nullptr;
    if (resCylSurf_vnesh2 == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_vnesh2, namesCyl, pCy_vnesh2);

    }
    //-------------булева операция вычитания----------------------------------------------------------------

    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    // Флаги булевой операции: построение замкнутого тела с объединением
    // подобных граней и ребер.
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // Результирующее тело
    MbSolid* vtulka_bez_vireza = NULL;
    MbResultType res0 = ::BooleanResult(*pCy_vnesh1, cm_Copy, *pCy_vnesh2, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, vtulka_bez_vireza);
    MbSolid* vtulka_dlya_otv = NULL;
    MbResultType res1 = ::BooleanResult(*pCy_vnesh, cm_Copy, *vtulka_bez_vireza, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, vtulka_dlya_otv);



    //-----------------------------------------------------------------------------------
    // ФОРМИРОВАНИЕ ОБЪЕКТА params С ПАРАМЕТРАМИ ОПЕРАЦИИ КОПИРОВАНИЯ ПО СЕТКЕ
    // Векторы, определяющие полярную СК - направление радиальной оси и
    // направление увеличения полярного угла.
    const double DEG_TO_RAD = M_PI / 180.0;
    MbVector3D mas_vec_Dir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(100, 0, 100));
    MbVector3D mas_vec_Dir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -100, 0));
    // Шаг копирования
    const double mas_step1 = d_vnesh_otv / 2;
    const double mas_step2 = 90 * DEG_TO_RAD;
    // Угловой шаг 30 градусов
    // Задание количества копий
    unsigned int mas_num1 = 1;
    unsigned int mas_num2 = 4;
    // В качестве центра СК сетки передается точка, соответствующая центру сферы.
    DuplicationMeshValues mas_params(true /* полярная СК */, mas_vec_Dir1, mas_step1, mas_num1,
        mas_vec_Dir2, mas_step2, mas_num2, &MbCartPoint3D(0, 0, 0));

    // ПОСТРОЕНИЕ ТЕЛА, СОСТОЯЩЕГО ИЗ КОПИЙ ПО СЕТКЕ
    MbSolid* mas_pDuplSolid = NULL;
    // Именователь операции копирования по сетке
    MbSNameMaker mas_namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    // Вызов операции копирования по сетке
    MbResultType mas_res = ::DuplicationSolid(*vtulka_dlya_otv, mas_params, mas_namesDupl, mas_pDuplSolid);
    //-----------------------------------------------------------------------------------




    MbCartPoint3D baseCenter11(0, -height_Cyl / 2, 0); // Центр первого основания
    MbCartPoint3D baseCenter12(0, height_Cyl / 2, 0); // Центр второго основания

    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase12(r_vnut, height_Cyl / 2, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf3 = NULL;
    MbResultType resCylSurf3 = ::ElementarySurface(baseCenter11, baseCenter12, pntOnBase12,
        st_CylinderSurface, pCylSurf3);
    // Построение цилиндрического тела
    MbSolid* pCy1 = nullptr;
    if (resCylSurf3 == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf3, namesCyl, pCy1);

    }
    MbSolid* osnovanie_s_otv = NULL;
    MbResultType res5 = ::BooleanResult(*pCy, cm_Copy, *mas_pDuplSolid, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, osnovanie_s_otv);
    MbSolid* res = NULL;
    MbResultType res6 = ::BooleanResult(*osnovanie_s_otv, cm_Copy, *pCy1, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, res);


    SolidSPtr MainSolid(res);
    return MainSolid;
}