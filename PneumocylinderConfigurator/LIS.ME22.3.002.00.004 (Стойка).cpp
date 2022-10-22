#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;



void CreateSourceSolid(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(8);
    pnts.Add(MbCartPoint(50.93, 0));
    pnts.Add(MbCartPoint(204.31, 0));
    pnts.Add(MbCartPoint(255.24, 50.93));
    pnts.Add(MbCartPoint(255.24, 204.31));
    pnts.Add(MbCartPoint(204.31, 255.24));
    pnts.Add(MbCartPoint(50.93, 255.24));
    pnts.Add(MbCartPoint(0, 204.31));
    pnts.Add(MbCartPoint(0, 50.93));


    MbLineSegment* pS1 = new MbLineSegment(pnts[0], pnts[1]);
    MbLineSegment* pS2 = new MbLineSegment(pnts[1], pnts[2]);
    MbLineSegment* pS3 = new MbLineSegment(pnts[2], pnts[3]);
    MbLineSegment* pS4 = new MbLineSegment(pnts[3], pnts[4]);
    MbLineSegment* pS5 = new MbLineSegment(pnts[4], pnts[5]);
    MbLineSegment* pS6 = new MbLineSegment(pnts[5], pnts[6]);
    MbLineSegment* pS7 = new MbLineSegment(pnts[6], pnts[7]);
    MbLineSegment* pS8 = new MbLineSegment(pnts[7], pnts[0]);

    MbContour* pContour = new MbContour();

    pContour->AddSegment(pS1);
    pContour->AddSegment(pS2);
    pContour->AddSegment(pS3);
    pContour->AddSegment(pS4);
    pContour->AddSegment(pS5);
    pContour->AddSegment(pS6);
    pContour->AddSegment(pS7);
    pContour->AddSegment(pS8);

    _arrContours.push_back(pContour);

    //::DeleteItem(pContour);
}
void CreateSourceSolidSecondPart(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(8);
    pnts.Add(MbCartPoint(50.93, 0));
    pnts.Add(MbCartPoint(204.31, 0));
    pnts.Add(MbCartPoint(225.9, 21.59)); // !!!
    pnts.Add(MbCartPoint(225.9, 233.70)); // !!!
    pnts.Add(MbCartPoint(204.31, 255.24));
    pnts.Add(MbCartPoint(50.93, 255.24));
    pnts.Add(MbCartPoint(25.9, 230.20));
    pnts.Add(MbCartPoint(25.9, 25));


    MbLineSegment* pS1 = new MbLineSegment(pnts[0], pnts[1]);
    MbLineSegment* pS2 = new MbLineSegment(pnts[1], pnts[2]);
    MbLineSegment* pS3 = new MbLineSegment(pnts[2], pnts[3]);
    MbLineSegment* pS4 = new MbLineSegment(pnts[3], pnts[4]);
    MbLineSegment* pS5 = new MbLineSegment(pnts[4], pnts[5]);
    MbLineSegment* pS6 = new MbLineSegment(pnts[5], pnts[6]);
    MbLineSegment* pS7 = new MbLineSegment(pnts[6], pnts[7]);
    MbLineSegment* pS8 = new MbLineSegment(pnts[7], pnts[0]);

    MbContour* pContour = new MbContour();

    pContour->AddSegment(pS1);
    pContour->AddSegment(pS2);
    pContour->AddSegment(pS3);
    pContour->AddSegment(pS4);
    pContour->AddSegment(pS5);
    pContour->AddSegment(pS6);
    pContour->AddSegment(pS7);
    pContour->AddSegment(pS8);

    //show(Style(1, LIGHTGRAY), pContour);

    _arrContours.push_back(pContour);

}
void CreateSourceSolidThirdPart(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(8);
    pnts.Add(MbCartPoint(62.5, 75));
    pnts.Add(MbCartPoint(187.5, 75));
    pnts.Add(MbCartPoint(187.5, 8)); // !!!
    pnts.Add(MbCartPoint(179.5, 8)); // !!!
    pnts.Add(MbCartPoint(179.5, 12));
    pnts.Add(MbCartPoint(70.5, 12));
    pnts.Add(MbCartPoint(70.5, 8));
    pnts.Add(MbCartPoint(62.5, 8));

    MbPolyline* pPolyline = new MbPolyline(pnts, true);
    MbContour* pContour = nullptr;
    ::FilletPolyContour(pPolyline, 4, false, pnts[1], pContour);

    ptrdiff_t idxSideRight1 = 2;
    ptrdiff_t idxSideRight2 = 4;
    ptrdiff_t idxSideRight3 = 6;
    ptrdiff_t idxSideRight4 = 7;
    ptrdiff_t idxSideRight5 = 8;

    pContour->FilletTwoSegments(idxSideRight1, 4);
    pContour->FilletTwoSegments(idxSideRight2, 4);
    pContour->FilletTwoSegments(idxSideRight3, 4);
    pContour->FilletTwoSegments(idxSideRight4, 4);
    pContour->FilletTwoSegments(idxSideRight5, 4);

    //show(Style(1, LIGHTGRAY), pContour);

    _arrContours.push_back(pContour);

}

void CreatePartForCutout(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(8);
    pnts.Add(MbCartPoint(56.9, 15));
    pnts.Add(MbCartPoint(199.9, 15));
    pnts.Add(MbCartPoint(215.9, 33));
    pnts.Add(MbCartPoint(215.9, 220));
    pnts.Add(MbCartPoint(199.9, 239));
    pnts.Add(MbCartPoint(56.9, 239));
    pnts.Add(MbCartPoint(40.9, 220));
    pnts.Add(MbCartPoint(40.9, 33));

    MbPolyline* pPolyline = new MbPolyline(pnts, true);
    MbContour* pContour = nullptr;
    ::FilletPolyContour(pPolyline, 0, false, pnts[2], pContour);



    _arrContours.push_back(pContour);

}
void CreatePartForCutoutSecondPart(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(4);
    pnts.Add(MbCartPoint(70.5, 91));
    pnts.Add(MbCartPoint(70.5, 483));
    pnts.Add(MbCartPoint(179.5, 483));
    pnts.Add(MbCartPoint(179.5, 91));

    MbPolyline* pPolyline = new MbPolyline(pnts, true);
    MbContour* pContour = nullptr;
    ::FilletPolyContour(pPolyline, 0, false, pnts[3], pContour);

    _arrContours.push_back(pContour);
}
void CreateOvalForCutout(RPArray<MbContour>& _arrContours, double x1, double x2, double y1, double y2, double radius)
{
    SArray<MbCartPoint> pnts(4);
    pnts.Add(MbCartPoint(x1, y1));
    pnts.Add(MbCartPoint(x1, y2));
    pnts.Add(MbCartPoint(x2, y2));
    pnts.Add(MbCartPoint(x2, y1));

    MbPolyline* pPolyline = new MbPolyline(pnts, true);
    MbContour* pContour = nullptr;
    ::FilletPolyContour(pPolyline, radius, false, pnts[2], pContour);

    ptrdiff_t idxSideRight = 0;
    ptrdiff_t idxSideRight1 = 3;
    ptrdiff_t idxSideRight3 = 5;

    pContour->FilletTwoSegments(idxSideRight, radius);
    pContour->FilletTwoSegments(idxSideRight1, radius);
    pContour->FilletTwoSegments(idxSideRight3, radius);

    _arrContours.push_back(pContour);
}
void CreateEdgesBack(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(4);
    pnts.Add(MbCartPoint(181, 20));
    pnts.Add(MbCartPoint(148, 55));
    pnts.Add(MbCartPoint(148, 65));
    pnts.Add(MbCartPoint(181, 65));

    MbPolyline* pPolyline = new MbPolyline(pnts, true);
    MbContour* pContour = nullptr;
    ::FilletPolyContour(pPolyline, 8, false, pnts[3], pContour);

    _arrContours.push_back(pContour);

}

MbSolid* ParametricModelCreator::LIS_ME22_3_002_00_004()
{

    RPArray<MbContour> arrContours;
    CreateSourceSolid(arrContours);
    RPArray<MbContour> arrContours2;
    CreateSourceSolidSecondPart(arrContours2);
    RPArray<MbContour> arrContours3;
    CreateSourceSolidThirdPart(arrContours3);
    RPArray<MbContour> arrContours4;
    CreatePartForCutout(arrContours4);
    RPArray<MbContour> arrContours5;
    CreatePartForCutoutSecondPart(arrContours5);
    RPArray<MbContour> arrContours6;
    CreateOvalForCutout(arrContours6, 120, 135, 205, 465, 7.5);
    RPArray<MbContour> arrContours7;
    CreateOvalForCutout(arrContours7, 115, 140, 200, 470, 12.5);
    RPArray<MbContour> arrContours8;
    CreateEdgesBack(arrContours8);

    MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    MbPlacement3D HorizPlane(MbVector3D(1, 0, 0), /* Ось X локальной СК */
        MbVector3D(0, 0, 1), /* Ось Z локальной СК */
        MbCartPoint3D(0, 234, 0 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane(MbVector3D(1, 0, 0), /* Ось X локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(0, 0, 127 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane2(MbVector3D(0, 0, 1), /* Ось Z локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(126, 0, 0 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane3(MbVector3D(1, 0, 0), /* Ось X локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(0, 0, 132 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane4(MbVector3D(1, 0, 0), /* Ось X локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(0, 0, 162 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane5(MbVector3D(0, 0, 1), /* Ось Z локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(128, 0, 0 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane6(MbVector3D(0, 0, 1), /* Ось Z локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(168, 0, 0 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane7(MbVector3D(0, 0, 1), /* Ось Z локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(128, 0, 0 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane8(MbVector3D(0, 0, 1), /* Ось Z локальной СК */
        MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbCartPoint3D(127, 0, 0 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane9(MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbVector3D(1, 0, 0), /* Ось X локальной СК */
        MbCartPoint3D(0, 0, 40 /* Начало координат локальной СК */));

    MbPlacement3D VerticalPlane10(MbVector3D(0, 1, 0), /* Ось Y локальной СК */
        MbVector3D(1, 0, 0), /* Ось X локальной СК */
        MbCartPoint3D(0, 0, 125 /* Начало координат локальной СК */));

    MbSweptData* pBase;
    pBase = new MbSweptData(*pPlaneXZ, arrContours);

    MbSweptData* pBase2;
    pBase2 = new MbSweptData(*pPlaneXZ, arrContours2);

    MbSweptData* pBase3;
    pBase3 = new MbSweptData(*pPlaneXZ, arrContours3);

    MbSweptData* pBase4;
    pBase4 = new MbSweptData(*pPlaneXZ, arrContours4);

    MbSweptData* pBase5;
    pBase5 = new MbSweptData(*pPlaneXY, arrContours5);

    MbSweptData* pBase6;
    pBase6 = new MbSweptData(*pPlaneXY, arrContours6);

    MbSweptData* pBase7;
    pBase7 = new MbSweptData(*pPlaneXY, arrContours7);

    MbSweptData* pBase8;
    pBase8 = new MbSweptData(*pPlaneXZ, arrContours8);

    const double HEIGHT_FORWARD = 75, HEIGHT_BACKWARD = 0;
    const double HEIGHT_FORWARD2 = 495, HEIGHT_BACKWARD2 = 0 - HEIGHT_FORWARD;
    const double HEIGHT_FORWARD3 = 60, HEIGHT_BACKWARD3 = 0;
    const double HEIGHT_FORWARD4 = 65, HEIGHT_BACKWARD4 = 0;

    ExtrusionValues extrusionParams(12, 0);
    ExtrusionValues extrusionParams2(HEIGHT_FORWARD, HEIGHT_BACKWARD);
    ExtrusionValues extrusionParams3(HEIGHT_FORWARD2, HEIGHT_BACKWARD2);
    ExtrusionValues extrusionParams4(HEIGHT_FORWARD3, HEIGHT_BACKWARD3);
    ExtrusionValues extrusionParams5(HEIGHT_FORWARD4, HEIGHT_BACKWARD4);
    ExtrusionValues extrusionParams6(80, 0);
    ExtrusionValues extrusionParams7(80, -72);
    ExtrusionValues extrusionParams8(300, -288);

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbVector3D dirY(0, 1, 0);
    MbVector3D dirZ(0, 0, 1);

    MbSolid* pSolid = NULL;
    MbSolid* pSolid2 = NULL;
    MbSolid* pSolid3 = NULL;
    MbSolid* pSolid4 = NULL;
    MbSolid* pSolid5 = NULL;
    MbSolid* pSolid6 = NULL;
    MbSolid* pSolid7 = NULL;

    // Ребра жесткости задние
    MbSolid* pSolid8 = NULL;
    MbSolid* pSolid9 = NULL;
    MbSolid* pSolid10 = NULL;
    MbSolid* pSolid11 = NULL;

    // ОТВЕРСТИЯ 
    MbSolid* pCyl_Solid = NULL;
    MbSolid* pCyl_Solid2 = NULL;
    MbSolid* pCyl_Solid3 = NULL;
    MbSolid* pCyl_Solid4 = NULL;
    // В центре
    MbSolid* pCyl_Solid5 = NULL;
    MbSolid* pCyl_Solid6 = NULL;
    MbSolid* pCyl_Solid7 = NULL;
    MbSolid* pCyl_Solid8 = NULL;
    MbSolid* pCyl_Solid9 = NULL;
    MbSolid* pCyl_Solid10 = NULL;
    MbSolid* pCyl_Solid11 = NULL;
    MbSolid* pCyl_Solid12 = NULL;
    MbSolid* pCyl_Solid13 = NULL;
    // Сверху
    MbSolid* pCyl_Solid14 = NULL;
    MbSolid* pCyl_Solid15 = NULL;
    // Сзади
    MbSolid* pCyl_Solid16 = NULL;
    MbSolid* pCyl_Solid17 = NULL;
    MbSolid* pCyl_Solid18 = NULL;
    MbSolid* pCyl_Solid19 = NULL;

    // Ребра жесткости
    MbSolid* pBlock_Solid = NULL;
    MbSolid* pBlock_Solid2 = NULL;

    MbResultType res = ::ExtrusionSolid(*pBase, dirY, NULL, NULL, false, extrusionParams, operNames, cNames, pSolid);
    MbResultType res2 = ::ExtrusionSolid(*pBase2, dirY, NULL, NULL, false, extrusionParams2, operNames, cNames, pSolid2);
    MbResultType res3 = ::ExtrusionSolid(*pBase3, dirY, NULL, NULL, false, extrusionParams3, operNames, cNames, pSolid3);
    ::ExtrusionSolid(*pBase4, dirY, NULL, NULL, false, extrusionParams4, operNames, cNames, pSolid4);
    ::ExtrusionSolid(*pBase5, dirZ, NULL, NULL, false, extrusionParams5, operNames, cNames, pSolid5);
    ::ExtrusionSolid(*pBase6, dirZ, NULL, NULL, false, extrusionParams6, operNames, cNames, pSolid6);
    ::ExtrusionSolid(*pBase7, dirZ, NULL, NULL, false, extrusionParams7, operNames, cNames, pSolid7);
    ::ExtrusionSolid(*pBase8, dirY, NULL, NULL, false, extrusionParams8, operNames, cNames, pSolid8);

    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    // Указание значений параметров операции скругления ребер
    SmoothValues params;
    // Радиусы кривизны на двух скругляемых поверхностях
    params.distance1 = 8;
    params.distance2 = 8;
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
    // Формирование массива с ребрами для скругления.
    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges(10, 1);
    pSolid5->GetEdges(allEdges);
    // В массив ребер для скругления помещается только одно ребро
    RPArray<MbCurveEdge> initCurves(4, 1);
    initCurves.Add(allEdges[6]);
    initCurves.Add(allEdges[11]);
    // Массив граней для обрезки – в данном примере пустой
    RPArray<MbFace> initBounds(0, 1);
    // Вызов функции скругления ребер.
    ::FilletSolid(*pSolid5, cm_Copy, initCurves, initBounds,
        params, filletNames, pSolid5);

    // ОТВЕРСТИЕ ПО БОКАМ
    // Опорные точки для элементарного тела - цилиндра
    SArray<MbCartPoint3D> cylPnts4;
    cylPnts4.Add(MbCartPoint3D(12, 0, 70));
    cylPnts4.Add(MbCartPoint3D(12, 100, 70));
    cylPnts4.Add(MbCartPoint3D(12, 100, 75.5));
    // Построение элементарного тела - цилиндра
    MbResultType resCyl5 = ::ElementarySolid(cylPnts4, et_Cylinder,
        namesElSolid, pCyl_Solid);

    // Маленькие отверстия в центре
    SArray<MbCartPoint3D> cylPnts5;
    cylPnts5.Add(MbCartPoint3D(208, 0, 102));
    cylPnts5.Add(MbCartPoint3D(208, 100, 102));
    cylPnts5.Add(MbCartPoint3D(208, 100, 105.4));
    // Построение элементарного тела - цилиндра
    ::ElementarySolid(cylPnts5, et_Cylinder,
        namesElSolid, pCyl_Solid5);

    // Большое отверстие в центре
    SArray<MbCartPoint3D> cylPnts12;
    cylPnts12.Add(MbCartPoint3D(128, 0, 160));
    cylPnts12.Add(MbCartPoint3D(128, 100, 160));
    cylPnts12.Add(MbCartPoint3D(128, 100, 170));
    // Построение элементарного тела - цилиндра
    ::ElementarySolid(cylPnts12, et_Cylinder,
        namesElSolid, pCyl_Solid12);

    // отверстие в сверху
    SArray<MbCartPoint3D> cylPnts13;
    cylPnts13.Add(MbCartPoint3D(144, 400, 52));
    cylPnts13.Add(MbCartPoint3D(144, 500, 52));
    cylPnts13.Add(MbCartPoint3D(144, 500, 57));
    // Построение элементарного тела - цилиндра
    ::ElementarySolid(cylPnts13, et_Cylinder,
        namesElSolid, pCyl_Solid14);

    SArray<MbCartPoint3D> cylPnts14;
    cylPnts14.Add(MbCartPoint3D(162, 75, 55));
    cylPnts14.Add(MbCartPoint3D(162, 110, 55));
    cylPnts14.Add(MbCartPoint3D(162, 110, 60.5));
    // Построение элементарного тела - цилиндра
    ::ElementarySolid(cylPnts14, et_Cylinder,
        namesElSolid, pCyl_Solid16);

    // Ребро жесткости внизу
    SArray<MbCartPoint3D> blockPnts;
    blockPnts.Add(MbCartPoint3D(40, 60, 180));
    blockPnts.Add(MbCartPoint3D(216, 60, 180));
    blockPnts.Add(MbCartPoint3D(200, 19, 180));
    blockPnts.Add(MbCartPoint3D(200, 48, 190));
    // Построение элементарного тела - цилиндра
    ::ElementarySolid(blockPnts, et_Block,
        namesElSolid, pBlock_Solid);


    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    ::MirrorSolid(*pCyl_Solid, VerticalPlane, operNames, pCyl_Solid2);
    ::MirrorSolid(*pCyl_Solid, VerticalPlane2, operNames, pCyl_Solid3);
    ::MirrorSolid(*pCyl_Solid2, VerticalPlane2, operNames, pCyl_Solid4);

    ::MirrorSolid(*pCyl_Solid5, VerticalPlane3, operNames, pCyl_Solid6);
    ::MirrorSolid(*pCyl_Solid5, VerticalPlane4, operNames, pCyl_Solid7);
    ::MirrorSolid(*pCyl_Solid7, VerticalPlane5, operNames, pCyl_Solid8);
    ::MirrorSolid(*pCyl_Solid6, VerticalPlane5, operNames, pCyl_Solid9);
    ::MirrorSolid(*pCyl_Solid5, VerticalPlane5, operNames, pCyl_Solid10);
    ::MirrorSolid(*pCyl_Solid5, VerticalPlane6, operNames, pCyl_Solid11);
    ::MirrorSolid(*pCyl_Solid7, VerticalPlane6, operNames, pCyl_Solid13);

    // Ребро жесткости
    ::MirrorSolid(*pBlock_Solid, VerticalPlane10, operNames, pBlock_Solid2);

    ::MirrorSolid(*pCyl_Solid14, VerticalPlane7, operNames, pCyl_Solid15);

    ::MirrorSolid(*pCyl_Solid16, VerticalPlane8, operNames, pCyl_Solid17);
    ::MirrorSolid(*pCyl_Solid16, VerticalPlane9, operNames, pCyl_Solid18);
    ::MirrorSolid(*pCyl_Solid17, VerticalPlane9, operNames, pCyl_Solid19);

    // Ребра жесткости сзади
    ::MirrorSolid(*pSolid8, VerticalPlane7, operNames, pSolid9);
    ::MirrorSolid(*pSolid9, HorizPlane, operNames, pSolid10);
    ::MirrorSolid(*pSolid8, HorizPlane, operNames, pSolid11);

    //Объединение двух тел

    ::BooleanResult(*pSolid, cm_Copy, *pSolid2, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);  // Объеденение
    ::BooleanResult(*pSolid, cm_Copy, *pSolid4, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid); // Вырезание нижней части
    ::BooleanResult(*pSolid, cm_Copy, *pSolid3, cm_Copy, bo_Union, // Объеденение
        flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pSolid5, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid); // Вырезание задней части
    ::BooleanResult(*pSolid, cm_Copy, *pSolid6, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid); // Вырезание малого овала
    ::BooleanResult(*pSolid, cm_Copy, *pSolid7, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid); // Вырезание большого овала
    ::BooleanResult(*pSolid, cm_Copy, *pBlock_Solid, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);  // Объеденение ребра жесткости
    ::BooleanResult(*pSolid, cm_Copy, *pBlock_Solid2, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);
    // Объеденение ребер жесткости сзади
    ::BooleanResult(*pSolid, cm_Copy, *pSolid8, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pSolid9, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pSolid10, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pSolid11, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);

    // Отверстия
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid3, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid4, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // Отверстия в центре
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid5, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid6, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid7, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid8, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid9, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid10, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid11, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid12, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid13, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid14, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid15, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid16, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid17, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid18, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
    ::BooleanResult(*pSolid, cm_Copy, *pCyl_Solid19, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    return pSolid;

    //Уменьшение счетчиков ссылок динамически созданных объектов ядра

    ::DeleteItem(pSolid);
    ::DeleteItem(pSolid2);
    ::DeleteItem(pSolid3);
    ::DeleteItem(pSolid4);
    ::DeleteItem(pSolid5);
    ::DeleteItem(pSolid6);
    ::DeleteItem(pSolid7);



}