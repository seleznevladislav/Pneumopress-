#include "BuildMathModel.h"

using namespace BuildMathModel;

//шестиугольная призма
void CreateSketch1YA(RPArray<MbContour>& _arrContours) {
    SArray<MbCartPoint> arrPnts(6); //массив на 6 точек гексагона

    const double lin_dist = 14 - (2.0 / 3.0); //linear distance, от центра точки к грани
    const double diam_size = 25.4; //диаметральный размер, он же между двумя точками

    //расставляем точки шестиугольника по формуле, центр в (0;0)
    MbCartPoint p1(-lin_dist, 0);
    MbCartPoint p2(-lin_dist / 2, diam_size / 2);
    MbCartPoint p3(lin_dist / 2, diam_size / 2);
    MbCartPoint p4(lin_dist, 0);
    MbCartPoint p5(lin_dist / 2, -diam_size / 2);
    MbCartPoint p6(-lin_dist / 2, -diam_size / 2);

    arrPnts.Add(p1);
    arrPnts.Add(p2);
    arrPnts.Add(p3);
    arrPnts.Add(p4);
    arrPnts.Add(p5);
    arrPnts.Add(p6);

    // Построение единой ломаной внешнего контура по точкам
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour();
    //строим отрезки(сегменты)
    MbLineSegment* Seg1 = new MbLineSegment(p1, p2);
    MbLineSegment* Seg2 = new MbLineSegment(p2, p3);
    MbLineSegment* Seg3 = new MbLineSegment(p3, p4);
    MbLineSegment* Seg4 = new MbLineSegment(p4, p5);
    MbLineSegment* Seg5 = new MbLineSegment(p5, p6);
    MbLineSegment* Seg6 = new MbLineSegment(p6, p1);
    //добавляем их в контур
    pContourPolyline->AddSegment(Seg1);
    pContourPolyline->AddSegment(Seg2);
    pContourPolyline->AddSegment(Seg3);
    pContourPolyline->AddSegment(Seg4);
    pContourPolyline->AddSegment(Seg5);
    pContourPolyline->AddSegment(Seg6);

    _arrContours.push_back(pContourPolyline);
}
//прототип вилки
void CreateSketch2YA(RPArray<MbContour>& _arrContours2) {
    SArray<MbCartPoint> arrPnts2(8); //массив на 8 точек основы вилки

    //расставляем точки по чертежу
    MbCartPoint p1(11.11, -42.55 / 2);
    MbCartPoint p2(11.11 + 39.69, -42.55 / 2);
    MbCartPoint p3(11.11 + 39.69, -42.55 / 2 + 11.78);
    MbCartPoint p4(22.22, -42.55 / 2 + 11.78);
    MbCartPoint p5(22.22, 42.55 / 2 - 11.78);
    MbCartPoint p6(11.11 + 39.69, 42.55 / 2 - 11.78);
    MbCartPoint p7(11.11 + 39.69, 42.55 / 2);
    MbCartPoint p8(11.11, 42.55 / 2);

    arrPnts2.Add(p1);
    arrPnts2.Add(p2);
    arrPnts2.Add(p3);
    arrPnts2.Add(p4);
    arrPnts2.Add(p5);
    arrPnts2.Add(p6);
    arrPnts2.Add(p7);
    arrPnts2.Add(p8);

    MbPolyline* pPolyline2 = new MbPolyline(arrPnts2, true);
    MbContour* pContourPolyline2 = new MbContour();

    MbLineSegment* Seg1 = new MbLineSegment(p1, p2);
    MbLineSegment* Seg2 = new MbLineSegment(p2, p3);
    MbLineSegment* Seg3 = new MbLineSegment(p3, p4);
    MbLineSegment* Seg4 = new MbLineSegment(p4, p5);
    MbLineSegment* Seg5 = new MbLineSegment(p5, p6);
    MbLineSegment* Seg6 = new MbLineSegment(p6, p7);
    MbLineSegment* Seg7 = new MbLineSegment(p7, p8);
    MbLineSegment* Seg8 = new MbLineSegment(p8, p1);
    pContourPolyline2->AddSegment(Seg1);
    pContourPolyline2->AddSegment(Seg2);
    pContourPolyline2->AddSegment(Seg3);
    pContourPolyline2->AddSegment(Seg4);
    pContourPolyline2->AddSegment(Seg5);
    pContourPolyline2->AddSegment(Seg6);
    pContourPolyline2->AddSegment(Seg7);
    pContourPolyline2->AddSegment(Seg8);

    _arrContours2.push_back(pContourPolyline2);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_001()
{
    MbPlacement3D pl; //СК

    RPArray<MbContour> arrContours;
    CreateSketch1YA(arrContours);
    RPArray<MbContour> arrContours2;
    CreateSketch2YA(arrContours2);

    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneYZ = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(0, 1, 0),
        MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    MbPlacement3D HorizPlane(MbVector3D(1, 0, 0), /* Ось X  */
        MbVector3D(0, 0, 1), /* Ось Z */
        MbCartPoint3D(0, 0, 0 /* Начало координат СК */));

    MbPlacement3D VerticalPlane(MbVector3D(0, 0, 1), /* Ось Z */
        MbVector3D(0, 1, 0), /* Ось Y */
        MbCartPoint3D(0, 0, 0 /* Начало координат СК */));

    MbPlacement3D ApplicPlane(MbVector3D(0, 1, 0), /* Ось Y */
        MbVector3D(1, 0, 0), /* Ось X */
        MbCartPoint3D(0, 0, 0 /* Начало координат СК */));

    // Направляющий вектор для операции выдавливания
    MbVector3D dirX(1, 0, 0);
    MbVector3D dirY(0, 1, 0);
    MbVector3D dirZ(0, 0, 1);

    MbSweptData sweptData1(*pPlaneYZ, arrContours);
    MbSweptData sweptData2(*pPlaneXY, arrContours2);

    const double HEIGHT_FORWARD = 11.11, HEIGHT_BACKWARD = 0;
    const double HEIGHT_FORWARD2 = 31.75 / 2, HEIGHT_BACKWARD2 = 31.75 / 2;

    ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);
    ExtrusionValues extrusionParams2(HEIGHT_FORWARD2, HEIGHT_BACKWARD2);

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker chamferNames(ct_ChamferSolid, MbSNameMaker::i_SideNone, 0);

    //создаём параметры для скругления заранее
    SmoothValues params;
    params.distance1 = 4.45; //радиус скруглений 4.45
    params.distance2 = 4.45;
    params.form = st_Fillet;
    params.conic = 0; //не конусная форма
    params.prolong = false; //не удлинять
    params.smoothCorner = SmoothValues::ec_uniform;
    params.keepCant = ts_negative;
    params.strict = true; //строгий/острый?
    RPArray<MbCurveEdge> allEdges(4, 1);

    SmoothValues params2;
    params2.distance1 = 0.86;
    params2.distance2 = 0.86;
    params2.form = st_Chamfer;
    params2.conic = 0;
    params2.prolong = false;
    params2.smoothCorner = SmoothValues::ec_uniform;
    params2.keepCant = ts_negative;
    params2.strict = true;
    RPArray<MbCurveEdge> allEdges2(4, 1);

    MbSolid* pSolidHex = nullptr; //гексагон
    MbSolid* pSolidBase = nullptr; //база

    //MbSolid* pSolidBlock = NULL; //уже не используется
    MbSolid* pCyl1_Solid = NULL; //вырез снизу
    MbSolid* pCyl2_Solid = NULL; //"ухо"
    MbSolid* pCyl3_Solid = NULL; //копия уха
    MbSolid* pCyl4_Solid = NULL; // сквозной вырез через два уха


    //создаём сначала шестиугольник
    MbResultType res1 = ::ExtrusionSolid(sweptData1, dirX, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolidHex);
    //затем основу
    MbResultType res21 = ::ExtrusionSolid(sweptData2, dirZ, nullptr, nullptr, false, extrusionParams2, operNames, cNames, pSolidBase);
    //и соединяем их
    MbResultType res22 = ::BooleanResult(*pSolidBase, cm_Copy, *pSolidHex, cm_Copy, bo_Union, flagsBool, operBoolNames, pSolidBase);

    /* //простой блок, надо над ним потрудиться
    SArray<MbCartPoint3D> blockPnts1(4);
    blockPnts1.Add(MbCartPoint3D(-31.75/2, 0, 0));
    blockPnts1.Add(MbCartPoint3D(0, 10, 0));
    blockPnts1.Add(MbCartPoint3D(0, 0, 10));
    blockPnts1.Add(MbCartPoint3D(10, 10, 10));
    */
    //MbResultType res51 = ::ElementarySolid(blockPnts1, et_Block, namesElSolid, pSolidBlock);

    //цилиндр для выреза снизу
    SArray<MbCartPoint3D> cylPnts1(3);
    cylPnts1.Add(MbCartPoint3D(0, 0, 0));
    cylPnts1.Add(MbCartPoint3D(22.22, 0, 0));
    cylPnts1.Add(MbCartPoint3D(0, 0, (17 + (2.0 / 3.0)) / 2));

    MbResultType res31 = ::ElementarySolid(cylPnts1, et_Cylinder, namesElSolid, pCyl1_Solid);
    MbResultType res32 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl1_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);

    //цилиндр для уха
    SArray<MbCartPoint3D> cylPnts2(3);
    cylPnts2.Add(MbCartPoint3D(50.8, 44.45 / 2, 0));
    cylPnts2.Add(MbCartPoint3D(50.8, 9.5, 0));
    cylPnts2.Add(MbCartPoint3D(50.8, 44.45 / 2, 31.76 / 2));

    MbResultType res41 = ::ElementarySolid(cylPnts2, et_Cylinder, namesElSolid, pCyl2_Solid);
    //копируем результат на цилиндр3 относительно плоскости XZ
    MbResultType res42 = ::MirrorSolid(*pCyl2_Solid, HorizPlane, operNames, pCyl3_Solid);
    //добавляем оба цилиндра к телу
    MbResultType res43 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl2_Solid, cm_Copy, bo_Union, flagsBool, operBoolNames, pSolidBase);
    MbResultType res44 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl3_Solid, cm_Copy, bo_Union, flagsBool, operBoolNames, pSolidBase);

    //сквозной вырез через оба уха
    SArray<MbCartPoint3D> cylPnts3(3);
    cylPnts3.Add(MbCartPoint3D(50.8, 44.45 / 2, 0));
    cylPnts3.Add(MbCartPoint3D(50.8, -44.45 / 2, 0));
    cylPnts3.Add(MbCartPoint3D(50.8, 44.45 / 2, 15.88 / 2));

    MbResultType res51 = ::ElementarySolid(cylPnts3, et_Cylinder, namesElSolid, pCyl4_Solid);
    //вырезаем
    MbResultType res52 = ::BooleanResult(*pSolidBase, cm_Copy, *pCyl4_Solid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidBase);

    //получаем все грани тела pSolidBase
    pSolidBase->GetEdges(allEdges);
    RPArray<MbCurveEdge> initCurves(4, 1);
    //нашёл номера рёбер путём перебора, можно проще через поиск GetNumber или что-либо в этом духе
    initCurves.Add(allEdges[50]);
    initCurves.Add(allEdges[55]);
    initCurves.Add(allEdges[57]);
    initCurves.Add(allEdges[58]);
    RPArray<MbFace> initBounds(0, 1);
    //добавляю скругления на рёбра
    MbResultType res6 = ::FilletSolid(*pSolidBase, cm_Copy, initCurves, initBounds, params, filletNames, pSolidBase);

    //проделываем аналогичные операции для построения фаски
    pSolidBase->GetEdges(allEdges2);
    RPArray<MbCurveEdge> initCurves2(4, 1);
    initCurves2.Add(allEdges2[64]); //надо было делать в гексагоне

    MbResultType res7 = ::ChamferSolid(*pSolidBase, cm_Copy, initCurves2, params2, chamferNames, pSolidBase);

    SolidSPtr MainSolid(pSolidBase);

    return MainSolid;
}