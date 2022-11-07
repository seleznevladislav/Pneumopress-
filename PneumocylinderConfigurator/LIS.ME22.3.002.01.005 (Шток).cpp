#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_005()
{
    // построение стержня 
    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);
    MbSolid* pShtok = NULL;
    {
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(0, 0, 0));
        points.Add(MbCartPoint3D(0, 265, 0));
        points.Add(MbCartPoint3D(5, 0, 0));

        ElementarySolid(points, et_Cylinder, elNames, pShtok);

    }

    // фаски   
          // 2) Объект-именователь для операции построения фасок
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    // 3) Указание значений параметров операции построения фасок
    SmoothValues params;
    // Длины катетов фаски
    params.distance1 = 1;
    params.distance2 = 1;
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
    pShtok->GetEdges(allEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[2]);
    initCurves.Add(allEdges[0]);
    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> initBounds(0, 1);
    // 6) Вызов функции построения фасок
    MbSolid* pResult = NULL;
    MbResultType res = ::ChamferSolid(*pShtok, cm_Copy, initCurves,
        params, chamferNames, pResult);


    ::DeleteItem(pShtok);


    SolidSPtr MainSolid(pResult);
    return MainSolid;
}