#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_001()
{

    double osnovanie_lenghth = 95;// сторона квадрата основания
    double osnovanie_high = 45;//высота квадрата основания
    double sopr = 4;//сопряжение основания
    double uho_d = 25;//диаметр боковых ушек
    double uho_length = 145;  //габаритная длина ушек
    double glubina = 3;//глубина кольцевого выреза на основании
    double d_vnesh = 86;//внешний диаметр кольцевого выреза на основании
    double d_vnut = 80;//внутренний диаметр кольцевого выреза
    double d_otv = 12;//диаметр четырех отверстий на виде сверху
    double a_kvadrata = 70;//сторона квадрата, расстояние между отверстиями d_otv
    double glubina_centr_otv = 20;//глубина первого снизу(основной вид) центрального отверстия
    double d_centr_otv = 40;//диаметр первого снизу(основной вид) центрального отверстия
    double glubina_centr_otv2 = 17.5;//глубина второго снизу(основной вид) центрального отверстия
    double d_centr_otv2 = 32;//диаметр второгоснизу(основной вид) центрального отверстия
    double glubina_centr_otv3 = 5;//глубина третьего снизу(основной вид) центрального отверстия
    double d_centr_otv3 = 42;//диаметр третьего снизу(основной вид) центрального отверстия
    double glubina_centr_otv4 = 2.5;//глубина четвертого снизу(основной вид) центрального отверстия
    double d_centr_otv4 = 33;//диаметр четвертого снизу(основной вид) центрального отверстия
    //сумма глубин центральных отверстий должен быть равным osnovanie_high. В коде не проводится проверка этого условия
    double glubina_centr_otv5 = 16;//губина двух отверстий(вид сверху), различных диаметров, также расстояние от верхней части основания до отверстий d_centr_otv7,d_centr_otv8
    double a_otv = 32;//расстояние от центра основания до этих отверстий
    double d_centr_otv5 = 10;// следовательно диаметр большего из отверстий
    double d_centr_otv6 = 5;//диаметр меньшего из отверстий
    double d_centr_otv7 = 7;//диаметр бокового отверстия, пересекающийся с отверстием d_centr_otv6    
    double glubina_centr_otv7 = 19;//глубина отверстия d_centr_otv7
    double d_centr_otv8 = 15.31;//диаметр бокового отверстия, пересекающийся с отверстием d_centr_otv5 
    double d_centr_otv9 = 10;//диаметр четырех отверстий (вид снизу)
    double d_massiva = 52;//диаметр окружности на котором расположены отверстия d_centr_otv9
    double glubina_centr_otv9 = 20;//глубина отверстий d_centr_otv9
    double a = osnovanie_lenghth;
    //--------------основание-------------------------------------
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    // ИСХОДНОЕ ТЕЛО №1 - ПАРАЛЛЕЛЕПИПЕД
    MbSolid* fpOsnovanie = NULL;
    // Опорные точки для построения элементарного тела - блока
    SArray<MbCartPoint3D> blockPnts(4);
    blockPnts.Add(MbCartPoint3D(-osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2));
    blockPnts.Add(MbCartPoint3D(-osnovanie_lenghth / 2, 0, -osnovanie_lenghth / 2));
    blockPnts.Add(MbCartPoint3D(-osnovanie_lenghth / 2, osnovanie_high, osnovanie_lenghth / 2));
    blockPnts.Add(MbCartPoint3D(osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2));
    // Построение элементарного тела - блока
    MbResultType resBlock = ::ElementarySolid(blockPnts, et_Block,
        namesElSolid, fpOsnovanie);

    //-----------------------------------------------------------------------------------   
    SmoothValues fparams;
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    fparams.distance1 = sopr;
    fparams.distance2 = sopr;
    fparams.form = st_Fillet;
    fparams.conic = 0;
    // Требуется скруглять ребра, гладко стыкующиеся с ребрами из входного массива
    fparams.prolong = true;
    // Способ скругления троек ребер
    fparams.smoothCorner = SmoothValues::ec_uniform;
    // Флаг сохранения кромки – режим сохранения поверхности
    fparams.keepCant = ts_neutral;
    // Строгое скругление
    fparams.strict = false;
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges2(4, 1);
    fpOsnovanie->GetEdges(allEdges2);
    // В массив ребер для скругления помещается только одно ребро
    RPArray<MbCurveEdge> initCurves2(4, 1);
    initCurves2.Add(allEdges2[2]);
    initCurves2.Add(allEdges2[5]);
    initCurves2.Add(allEdges2[7]);
    initCurves2.Add(allEdges2[0]);
    // 5) Массив граней для обрезки
    RPArray<MbFace> initBounds2(0, 1);
    // 6) Вызов функции скругления ребер.
    MbSolid* pOsnovanie = NULL;
    MbResultType resf = ::FilletSolid(*fpOsnovanie, cm_Copy, initCurves2, initBounds2,
        fparams, filletNames, pOsnovanie);
    osnovanie_lenghth = 0;
    //-----------------------------------------------------------------------------------   
    MbCartPoint3D baseCenter1(osnovanie_lenghth / 2, osnovanie_high / 2, osnovanie_lenghth / 2 - uho_length / 2); // Центр первого основания
    MbCartPoint3D baseCenter2(osnovanie_lenghth / 2, osnovanie_high / 2, osnovanie_lenghth / 2 + uho_length / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase2(osnovanie_lenghth / 2 - uho_d / 2, osnovanie_high / 2, osnovanie_lenghth / 2 + uho_length / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pSurUho = NULL;
    MbResultType resUho = ::ElementarySurface(baseCenter1, baseCenter2, pntOnBase2,
        st_CylinderSurface, pSurUho);
    // Построение цилиндрического тела
    MbSolid* pUho = nullptr;
    if (resUho == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pSurUho, namesCyl, pUho);

    }
    //-----------------------------------------------------------------------------------
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    // Флаги булевой операции: построение замкнутого тела с объединением
    // подобных граней и ребер.
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // Результирующее тело
    MbSolid* pOsn_obsh = NULL;
    MbResultType res_osnovanie = ::BooleanResult(*pOsnovanie, cm_Copy, *pUho, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pOsn_obsh);
    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_kol1(osnovanie_lenghth / 2, osnovanie_high - glubina, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_kol2(osnovanie_lenghth / 2, osnovanie_high, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_kol2(osnovanie_lenghth / 2 + d_vnesh / 2, osnovanie_high, osnovanie_lenghth / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_vnesh = NULL;
    MbResultType resCylSurf = ::ElementarySurface(baseCenter_for_kol1, baseCenter_for_kol2, pntOnBase_for_kol2,
        st_CylinderSurface, pCylSurf_kol_vnesh);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_vnesh = nullptr;
    if (resCylSurf == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_vnesh, namesCyl, pCy_kol_vnesh);

    }

    //-----------------------------------------------------------------------------------

        // Построение цилиндрической поверхности
    MbCartPoint3D baseCenter_for_kol_vnut1(osnovanie_lenghth / 2, osnovanie_high - glubina, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_kol_vnut2(osnovanie_lenghth / 2, osnovanie_high, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_kol_vnut2(osnovanie_lenghth / 2 + d_vnut / 2, osnovanie_high, osnovanie_lenghth / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_vnut = NULL;
    MbResultType resCylSurf_vnut = ::ElementarySurface(baseCenter_for_kol_vnut1, baseCenter_for_kol_vnut2, pntOnBase_for_kol_vnut2,
        st_CylinderSurface, pCylSurf_kol_vnut);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_vnut = nullptr;
    if (resCylSurf_vnut == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_vnut, namesCyl, pCy_kol_vnut);

    }
    //-----------------------------------------------------------------------------------
         // Результирующее тело
    MbSolid* pOsn_kol = NULL;
    MbResultType res_kol = ::BooleanResult(*pCy_kol_vnesh, cm_Copy, *pCy_kol_vnut, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_kol);

    //-----------------------------------------------------------------------------------
         // Результирующее тело
    MbSolid* pOsn_obsh_virez = NULL;
    MbResultType res_virez = ::BooleanResult(*pOsn_obsh, cm_Copy, *pOsn_kol, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_virez);

    //----------------------------------------------------------------------------------- 

          //отверстия
    MbCartPoint3D baseCenter_for_otv1(osnovanie_lenghth / 2 - a_kvadrata / 2, 0, osnovanie_lenghth / 2 - a_kvadrata / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_otv2(osnovanie_lenghth / 2 - a_kvadrata / 2, osnovanie_high, osnovanie_lenghth / 2 - a_kvadrata / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_otv2(osnovanie_lenghth / 2 - a_kvadrata / 2 + d_otv / 2, osnovanie_high, osnovanie_lenghth / 2 - a_kvadrata / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_otv = NULL;
    MbResultType resCylSurf_otv = ::ElementarySurface(baseCenter_for_otv1, baseCenter_for_otv2, pntOnBase_for_otv2,
        st_CylinderSurface, pCylSurf_kol_otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_otv = nullptr;
    if (resCylSurf_otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_otv, namesCyl, pCy_kol_otv);

    }

    //-----------------------------------------------------------------------------------
         // ФОРМИРОВАНИЕ ОБЪЕКТА params С ПАРАМЕТРАМИ ОПЕРАЦИИ КОПИРОВАНИЯ ПО СЕТКЕ
        // Векторы, определяющие два направления копирования
    MbVector3D vecDir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 100));
    MbVector3D vecDir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(100, 0, 0));
    // Шаг копирования по двум осям
    const double step1 = a_kvadrata;
    const double step2 = a_kvadrata;
    const unsigned int num1 = 2;
    const unsigned int num2 = 2;
    // В качестве центра СК сетки передается точка, соответствующая центру одного из
    // оснований исходного цилиндра.
    DuplicationMeshValues params(false /* декартова СК */, vecDir1, step1, num1,
        vecDir2, step2, num2, &MbCartPoint3D(osnovanie_lenghth / 2 - a_kvadrata / 2, osnovanie_high / 2, osnovanie_lenghth / 2 - a_kvadrata / 2));
    // ПОСТРОЕНИЕ ТЕЛА, СОСТОЯЩЕГО ИЗ КОПИЙ ПО СЕТКЕ
    MbSolid* pDuplSolid = NULL;
    // Именователь операции копирования по сетке
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    // Вызов операции копирования по сетке
    MbResultType res = ::DuplicationSolid(*pCy_kol_otv, params, namesDupl, pDuplSolid);

    // Отображение результирующего составного тела


//-----------------------------------------------------------------------------------
     // Результирующее тело
    MbSolid* pOsn_obsh_otv = NULL;
    MbResultType res_otv = ::BooleanResult(*pOsn_obsh_virez, cm_Copy, *pDuplSolid, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_otv);

    //-----------------------------------------------------------------------------------

          // Построение цилиндрической поверхности
    MbCartPoint3D baseCenter_for_centr_otv1(osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_otv2(osnovanie_lenghth / 2, glubina_centr_otv, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_otv2(osnovanie_lenghth / 2 + d_centr_otv / 2, glubina_centr_otv, osnovanie_lenghth / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_otv = NULL;
    MbResultType resCylSurf_centr_otv = ::ElementarySurface(baseCenter_for_centr_otv1, baseCenter_for_centr_otv2, pntOnBase_for_centr_otv2,
        st_CylinderSurface, pCylSurf_kol_centr_otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_otv = nullptr;
    if (resCylSurf_centr_otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_otv, namesCyl, pCy_kol_centr_otv);

    }

    //-----------------------------------------------------------------------------------
         // Результирующее тело
    MbSolid* pOsn_obsh_centr_otv = NULL;
    MbResultType res_centr_otv = ::BooleanResult(*pOsn_obsh_otv, cm_Copy, *pCy_kol_centr_otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv);

    //-----------------------------------------------------------------------------------
    MbCartPoint3D baseCenter_for_centr_2otv1(osnovanie_lenghth / 2, glubina_centr_otv, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_2otv2(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_2otv2(osnovanie_lenghth / 2 + d_centr_otv2 / 2, glubina_centr_otv + glubina_centr_otv2, osnovanie_lenghth / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_2otv = NULL;
    MbResultType resCylSurf_centr_2otv = ::ElementarySurface(baseCenter_for_centr_2otv1, baseCenter_for_centr_2otv2, pntOnBase_for_centr_2otv2,
        st_CylinderSurface, pCylSurf_kol_centr_2otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_2otv = nullptr;
    if (resCylSurf_centr_2otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_2otv, namesCyl, pCy_kol_centr_2otv);

    }

    //-----------------------------------------------------------------------------------
         // Результирующее тело
    MbSolid* pOsn_obsh_centr_otv2 = NULL;
    MbResultType res_centr_otv2 = ::BooleanResult(*pOsn_obsh_centr_otv, cm_Copy, *pCy_kol_centr_2otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv2);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_3otv1(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_3otv2(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_3otv2(osnovanie_lenghth / 2 + d_centr_otv3 / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3, osnovanie_lenghth / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_3otv = NULL;
    MbResultType resCylSurf_centr_3otv = ::ElementarySurface(baseCenter_for_centr_3otv1, baseCenter_for_centr_3otv2, pntOnBase_for_centr_3otv2,
        st_CylinderSurface, pCylSurf_kol_centr_3otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_3otv = nullptr;
    if (resCylSurf_centr_3otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_3otv, namesCyl, pCy_kol_centr_3otv);

    }
    //-----------------------------------------------------------------------------------    
    MbSolid* pOsn_obsh_centr_otv3 = NULL;
    MbResultType res_centr_otv3 = ::BooleanResult(*pOsn_obsh_centr_otv2, cm_Copy, *pCy_kol_centr_3otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv3);

    //-----------------------------------------------------------------------------------   

    MbCartPoint3D baseCenter_for_centr_4otv1(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_4otv2(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3 + glubina_centr_otv4, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_4otv2(osnovanie_lenghth / 2 + d_centr_otv4 / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3 + glubina_centr_otv4, osnovanie_lenghth / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_4otv = NULL;
    MbResultType resCylSurf_centr_4otv = ::ElementarySurface(baseCenter_for_centr_4otv1, baseCenter_for_centr_4otv2, pntOnBase_for_centr_4otv2,
        st_CylinderSurface, pCylSurf_kol_centr_4otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_4otv = nullptr;
    if (resCylSurf_centr_4otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_4otv, namesCyl, pCy_kol_centr_4otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv4 = NULL;
    MbResultType res_centr_otv4 = ::BooleanResult(*pOsn_obsh_centr_otv3, cm_Copy, *pCy_kol_centr_4otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv4);

    //-----------------------------------------------------------------------------------  

    MbCartPoint3D baseCenter_for_centr_5otv1(osnovanie_lenghth / 2 - a_otv, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_5otv2(osnovanie_lenghth / 2 - a_otv, osnovanie_high, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_5otv2(osnovanie_lenghth / 2 - a_otv, osnovanie_high, osnovanie_lenghth / 2 + d_centr_otv5 / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_5otv = NULL;
    MbResultType resCylSurf_centr_5otv = ::ElementarySurface(baseCenter_for_centr_5otv1, baseCenter_for_centr_5otv2, pntOnBase_for_centr_5otv2,
        st_CylinderSurface, pCylSurf_kol_centr_5otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_5otv = nullptr;
    if (resCylSurf_centr_5otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_5otv, namesCyl, pCy_kol_centr_5otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv5 = NULL;
    MbResultType res_centr_otv5 = ::BooleanResult(*pOsn_obsh_centr_otv4, cm_Copy, *pCy_kol_centr_5otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv5);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_6otv1(osnovanie_lenghth / 2 + a_otv, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_6otv2(osnovanie_lenghth / 2 + a_otv, osnovanie_high, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_6otv2(osnovanie_lenghth / 2 + a_otv, osnovanie_high, osnovanie_lenghth / 2 + d_centr_otv6 / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_6otv = NULL;
    MbResultType resCylSurf_centr_6otv = ::ElementarySurface(baseCenter_for_centr_6otv1, baseCenter_for_centr_6otv2, pntOnBase_for_centr_6otv2,
        st_CylinderSurface, pCylSurf_kol_centr_6otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_6otv = nullptr;
    if (resCylSurf_centr_6otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_6otv, namesCyl, pCy_kol_centr_6otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv6 = NULL;
    MbResultType res_centr_otv6 = ::BooleanResult(*pOsn_obsh_centr_otv5, cm_Copy, *pCy_kol_centr_6otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv6);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_7otv1(a / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 4); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_7otv2(a / 2 - glubina_centr_otv7, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_7otv2(a / 2 - glubina_centr_otv7, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2 + d_centr_otv7 / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_7otv = NULL;
    MbResultType resCylSurf_centr_7otv = ::ElementarySurface(baseCenter_for_centr_7otv1, baseCenter_for_centr_7otv2, pntOnBase_for_centr_7otv2,
        st_CylinderSurface, pCylSurf_kol_centr_7otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_7otv = nullptr;
    if (resCylSurf_centr_7otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_7otv, namesCyl, pCy_kol_centr_7otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv7 = NULL;
    MbResultType res_centr_otv7 = ::BooleanResult(*pOsn_obsh_centr_otv6, cm_Copy, *pCy_kol_centr_7otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv7);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_8otv1(-a / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_8otv2(osnovanie_lenghth / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_8otv2(osnovanie_lenghth / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2 + d_centr_otv8 / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_8otv = NULL;
    MbResultType resCylSurf_centr_8otv = ::ElementarySurface(baseCenter_for_centr_8otv1, baseCenter_for_centr_8otv2, pntOnBase_for_centr_8otv2,
        st_CylinderSurface, pCylSurf_kol_centr_8otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_8otv = nullptr;
    if (resCylSurf_centr_8otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_8otv, namesCyl, pCy_kol_centr_8otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv8 = NULL;
    MbResultType res_centr_otv8 = ::BooleanResult(*pOsn_obsh_centr_otv7, cm_Copy, *pCy_kol_centr_8otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv8);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_9otv1(osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2); // Центр первого основания
    MbCartPoint3D baseCenter_for_centr_9otv2(osnovanie_lenghth / 2, glubina_centr_otv9, osnovanie_lenghth / 2); // Центр второго основания
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase_for_centr_9otv2(osnovanie_lenghth / 2 + d_centr_otv9 / 2, glubina_centr_otv9, osnovanie_lenghth / 2);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf_kol_centr_9otv = NULL;
    MbResultType resCylSurf_centr_9otv = ::ElementarySurface(baseCenter_for_centr_9otv1, baseCenter_for_centr_9otv2, pntOnBase_for_centr_9otv2,
        st_CylinderSurface, pCylSurf_kol_centr_9otv);
    // Построение цилиндрического тела
    MbSolid* pCy_kol_centr_9otv = nullptr;
    if (resCylSurf_centr_9otv == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_9otv, namesCyl, pCy_kol_centr_9otv);

    }
    //-----------------------------------------------------------------------------------
        // ФОРМИРОВАНИЕ ОБЪЕКТА params С ПАРАМЕТРАМИ ОПЕРАЦИИ КОПИРОВАНИЯ ПО СЕТКЕ
        // Векторы, определяющие полярную СК - направление радиальной оси и
        // направление увеличения полярного угла.
    const double DEG_TO_RAD = M_PI / 180.0;
    MbVector3D mas_vec_Dir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(100, 0, 100));
    MbVector3D mas_vec_Dir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -100, 0));
    // Шаг копирования
    const double mas_step1 = d_massiva / 2;
    const double mas_step2 = 90 * DEG_TO_RAD;
    // Угловой шаг 30 градусов
    // Задание количества копий
    unsigned int mas_num1 = 1;
    unsigned int mas_num2 = 4;
    // В качестве центра СК сетки передается точка, соответствующая центру сферы.
    DuplicationMeshValues mas_params(true /* полярная СК */, mas_vec_Dir1, mas_step1, mas_num1,
        mas_vec_Dir2, mas_step2, mas_num2, &MbCartPoint3D(osnovanie_lenghth / 2, glubina_centr_otv9 / 2, osnovanie_lenghth / 2));

    // ПОСТРОЕНИЕ ТЕЛА, СОСТОЯЩЕГО ИЗ КОПИЙ ПО СЕТКЕ
    MbSolid* mas_pDuplSolid = NULL;
    // Именователь операции копирования по сетке
    MbSNameMaker mas_namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    // Вызов операции копирования по сетке
    MbResultType mas_res = ::DuplicationSolid(*pCy_kol_centr_9otv, mas_params, mas_namesDupl, mas_pDuplSolid);
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv9 = NULL;
    MbResultType res_centr_otv9 = ::BooleanResult(*mas_pDuplSolid, cm_Copy, *pCy_kol_centr_9otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv9);

    //-----------------------------------------------------------------------------------
    MbSolid* detail002 = NULL;
    MbResultType res_centr_mas = ::BooleanResult(*pOsn_obsh_centr_otv8, cm_Copy, *pOsn_obsh_centr_otv9, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, detail002);

    //-----------------------------------------------------------------------------------
    osnovanie_lenghth = a;


    SolidSPtr MainSolid(detail002);
    return MainSolid;
}