#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketch444(RPArray<MbContour>& _arrContours)
{
    // Построение образующей в виде двух концентрических окружностей
    const double RAD = 8; // Радиус внешней окружности



    MbArc* pCircleExt = new MbArc(MbCartPoint(15, -35), RAD);


    _arrContours.push_back(new MbContour(*pCircleExt, true));

}


SPtr<MbSolid> ParametricModelCreator::LIS_Konfiguration4()
{
    const double position = 15;
    // Локальная СК (по умолчанию совпадает с мировой СК)
    MbPlacement3D pl;

    // Массив контрольных точек для построения NURBS-сплайна
    vector<MbCartPoint3D> vecPnts =
    {
    {position,0, 0},
    {0,position, -7},
    {-position,0, -14},
    {0,-position, -21},
    {position,0, -28},
    {0,position, -35},
    {-position,0, -42},
    {0,-position, -49},
    {position,0, -56},
    {0,position, -63},
    {-position,0, -70}
    };
    SArray<MbCartPoint3D> arrPnts(vecPnts);
    // Построение направляющей кривой в виде незамкнутого NURBS-сплайна
    // 4-го порядка по контрольным точкам
    MbNurbs3D* pSpline = MbNurbs3D::Create(4, arrPnts, false);

    // Описание образующей кривой в виде плоского контура на плоскости XY мировой СК
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 0, 1));

    // Построение образующей кривой с помощью вспомогательной функции CreateSketch
    RPArray<MbContour> arrContours;
    CreateSketch444(arrContours);
    MbSweptData sweptData(*pPlaneXY, arrContours);

    // Объект с параметрами операции построения тела заметания
    EvolutionValues params;


    // Служебные объекты-именователи для вызова геометрической операции
    MbSNameMaker operNames(ct_CurveEvolutionSolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker cNames(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> contourNames(1, 0, false);
    contourNames.Add(&cNames);
    MbSNameMaker splineNames(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);

    // Вызов операции построения тела заметания
    MbSolid* pSolid1 = nullptr;
    MbResultType res = ::EvolutionSolid(sweptData, *pSpline, params, operNames,
        contourNames, splineNames, pSolid1);


    double heightC1 = 100;

    double radiusC1 = 10;

    // Исходные тела - цилиндры
    MbSolid* pCyl1 = NULL;

    // Объект-именователь для построения цилиндров - элементарных тел
    MbSNameMaker cylNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);


    // Массив точек для построения первого цилиндра   
    SArray<MbCartPoint3D> pntsCyl1(3);
    pntsCyl1.Add(MbCartPoint3D(0, 0, 0));
    pntsCyl1.Add(MbCartPoint3D(0, 0, -heightC1));
    pntsCyl1.Add(MbCartPoint3D(radiusC1, 0, 0));


    // Построение элементарного тела - цилиндра - по трем точкам
    ElementarySolid(pntsCyl1, et_Cylinder, cylNames, pCyl1);



    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    MbSolid* pSolid = NULL;

    MbResultType res1 = ::BooleanResult(*pCyl1, cm_Copy, *pSolid1, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);


    SolidSPtr MainSolid(pSolid);

    // Уменьшение счетчиков ссылок динамических объектов ядра
    ::DeleteItem(pSolid);
    ::DeleteItem(pPlaneXY);
    ::DeleteItem(pSpline);
    ::DeleteItem(pSolid1);

    return MainSolid;
}