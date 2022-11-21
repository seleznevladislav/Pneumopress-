#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateBaseSketch(RPArray<MbContour>& _contour, MbPolyline* polyline, MbContour* contour, int baseLength, int baseWidth)
{
    //int baseWidth = 35;
    //int baseLength = 60;

    int baseBodyFrontCutWidth = 2;
    int baseBodyFrontCutLength = 30;

    int additionalRectsWidth = 4;
    int additionalRectsHeight = 15;

    SArray<MbCartPoint> basePoints(12);

    basePoints.Add(MbCartPoint(0, 0));

    // левая нижняя точка переднего выреза
    basePoints.Add(MbCartPoint(0, baseLength / 2 - baseBodyFrontCutLength / 2));
    // правая нижняя точка переднего выреза
    basePoints.Add(MbCartPoint(baseBodyFrontCutWidth, baseLength / 2 - baseBodyFrontCutLength / 2));

    // правая верхняя точка переднего выреза
    basePoints.Add(MbCartPoint(baseBodyFrontCutWidth, baseLength / 2 + baseBodyFrontCutLength / 2));
    // левая верхняя точка переднего выступа
    basePoints.Add(MbCartPoint(0, baseLength / 2 + baseBodyFrontCutLength / 2));


    basePoints.Add(MbCartPoint(0, baseLength)); // левая верхняя точка
    basePoints.Add(MbCartPoint(baseWidth + additionalRectsWidth, baseLength)); // правая верхняя точка

    basePoints.Add(MbCartPoint(baseWidth + additionalRectsWidth, baseLength - additionalRectsHeight)); // правая нижняя точка для доп. прямоугольника

    // вернулись в основной прямоугольник
    basePoints.Add(MbCartPoint(baseWidth, baseLength - additionalRectsHeight));

    // точка ответвления нижнего доп. прямоугольника
    basePoints.Add(MbCartPoint(baseWidth, additionalRectsHeight));
    // точка верхняя правая для нижнего доп. прямоугольника
    basePoints.Add(MbCartPoint(baseWidth + additionalRectsWidth, additionalRectsHeight));
    // точка правая нижняя для нижнего доп. прямоугольника
    basePoints.Add(MbCartPoint(baseWidth + additionalRectsWidth, 0));

    polyline = new MbPolyline(basePoints, true);
    contour = new MbContour(*polyline, true);

    //show(contour);

    _contour.push_back(contour);
}

void CreateBaseBodyAditionSketch(RPArray<MbContour>& _contour, MbPolyline* polyline, MbContour* contour, int length, int width)
{
    int additionalRectsHeight = 15;

    SArray<MbCartPoint> baseAdditionalPoints(4);
    baseAdditionalPoints.Add(MbCartPoint(width, length - additionalRectsHeight));
    baseAdditionalPoints.Add(MbCartPoint(width + 5, length - additionalRectsHeight));
    baseAdditionalPoints.Add(MbCartPoint(width + 5, length / 2 - additionalRectsHeight));
    baseAdditionalPoints.Add(MbCartPoint(width, length / 2 - additionalRectsHeight));

    polyline = new MbPolyline(baseAdditionalPoints, true);
    contour = new MbContour(*polyline, true);

    //show(contour);

    _contour.push_back(contour);
}

void CreateTopBlockSketch(RPArray<MbContour>& _contour, MbPolyline* polyline, MbContour* contour, int width)
{
    SArray<MbCartPoint> topBlockPoints;
    topBlockPoints.Add(MbCartPoint(width / 2 + 5 - 2.5, 0));
    topBlockPoints.Add(MbCartPoint(width / 2 + 5 - 2.5, 35.5));
    topBlockPoints.Add(MbCartPoint(width / 2 + 5 - 2.5 - 35, 35.5));
    topBlockPoints.Add(MbCartPoint(width / 2 + 5 - 2.5 - 35, 0));

    polyline = new MbPolyline(topBlockPoints, true);
    contour = new MbContour(*polyline, true);

    //show(contour);

    _contour.push_back(contour);
}

void CreateSketchEar(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> arrPnts1(4);
    arrPnts1.Add(MbCartPoint(2.5, 157 + 18));
    arrPnts1.Add(MbCartPoint(2.5, 157));
    arrPnts1.Add(MbCartPoint(37.5, 157));
    arrPnts1.Add(MbCartPoint(37.5, 157 + 18));

    MbPolyline* pPolyline1 = new MbPolyline(arrPnts1, false);

    MbCartPoint arcCenter(20, 157 + 18);
    const double RADIUS = 17.5;
    MbArc* pArc = new MbArc(arcCenter, RADIUS, arrPnts1[3], arrPnts1[0], 1);
    MbContour* pContour1 = new MbContour(*pPolyline1, true);
    pContour1->AddSegment(pArc);
    // Вызовы информационных методов контура
    size_t segmentsCount = pContour1->GetSegmentsCount(); // 2
    double tMin = pContour1->GetTMin(); // 0.0
    double tMax = pContour1->GetTMax(); // 10.14159
    // Параметр IsSmoothConnected - допуск для классификации угловых точек    на контуре
    bool isSmooth = pContour1->IsSmoothConnected(0.001); // false
    double length = pContour1->CalculateLength(tMin, tMax); // 302.83
    bool isClosed = pContour1->IsClosedContinuousC0(); // true
    bool isCurvilinear = pContour1->IsAnyCurvilinear();
    _arrContours.push_back(pContour1);

}

void CreateSketchVystypBlock(RPArray<MbContour>& _arrContours)
{
    SArray<MbCartPoint> pnts(4);
    pnts.Add(MbCartPoint(0, 30));
    pnts.Add(MbCartPoint(35.8, 30));
    pnts.Add(MbCartPoint(30, 40));
    pnts.Add(MbCartPoint(0, 40));


    MbLineSegment* pS1 = new MbLineSegment(pnts[0], pnts[1]);
    MbLineSegment* pS2 = new MbLineSegment(pnts[1], pnts[2]);
    MbLineSegment* pS3 = new MbLineSegment(pnts[2], pnts[3]);
    MbLineSegment* pS4 = new MbLineSegment(pnts[3], pnts[0]);

    MbContour* pContour = new MbContour();

    pContour->AddSegment(pS1);
    pContour->AddSegment(pS2);
    pContour->AddSegment(pS3);
    pContour->AddSegment(pS4);


    _arrContours.push_back(pContour);
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_002()
{
    int baseBodyHeight = 157;
    int baseBodySketchLength = 60;
    int baseBodySketchWidth = 35;

    // Именователь граней для построения тела с помощью булевой операции 
   /*
    MbSNameMaker operBoolNames( ct_BooleanSolid, MbSNameMaker::i_SideNone );
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    */
    // названия элементов модели твердого тела и контуров образующей
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Объект-именователь для операции скругления ребер
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    // Базовые векторы
    MbVector3D dirX(1, 0, 0);
    MbVector3D dirY(0, 1, 0);
    MbVector3D dirZ(0, 0, 1);

    // плоскость, в которой строим основание
    MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneXZ__top = new MbPlane(MbCartPoint3D(0, baseBodyHeight, 0), MbCartPoint3D(1, baseBodyHeight, 0), MbCartPoint3D(0, baseBodyHeight, 1));




    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));


    MbPlane* pPlaneXY__top = new MbPlane(
        MbCartPoint3D(baseBodySketchWidth / 2, baseBodyHeight / 2, 0),
        MbCartPoint3D(baseBodySketchWidth, 0, 0),
        MbCartPoint3D(0, baseBodyHeight, 0)
    );

    // show(Style(2, RGB(255, 0, 0)), pPlaneXY__top);

     // Объявление твердых тел
    MbSolid* baseBody = nullptr;
    MbSolid* baseBodyBackAddition = nullptr;
    MbSolid* topBlock = nullptr;


    // первый эскиз - основание ползуна
    RPArray<MbContour> baseContour;
    MbPolyline* rectangle = nullptr;
    MbContour* baseBodyContour = nullptr;
    // рисуем эскиз
    CreateBaseSketch(baseContour, rectangle, baseBodyContour, baseBodySketchLength, baseBodySketchWidth);
    MbSweptData baseBodySweptData(*pPlaneXZ, baseContour);
    MbVector3D baseBodyExtrusionDirection(0, 1, 0);
    ExtrusionValues baseBodyExtrusionParams(baseBodyHeight, 0);
    MbResultType baseBodyExtrusion = ::ExtrusionSolid(baseBodySweptData, baseBodyExtrusionDirection, nullptr, nullptr, false, baseBodyExtrusionParams, operNames, cNames, baseBody);

    // Скругляем грани переднего выреза
    SmoothValues baseBodyFilletParams;
    baseBodyFilletParams.distance1 = 2;
    baseBodyFilletParams.distance2 = 2;
    baseBodyFilletParams.form = st_Fillet; // скругление по двум радиусам
    baseBodyFilletParams.conic = 0; // Форма профиля сопряжения - окружность
    baseBodyFilletParams.prolong = false; // скруглять только ребра, переданные во входном массиве
    baseBodyFilletParams.smoothCorner = SmoothValues::ec_uniform;

    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allBaseBodyEdges(4, 1);
    baseBody->GetEdges(allBaseBodyEdges);
    // В массив ребер для скругления помещается только одно ребро
    RPArray<MbCurveEdge> baseBodyInitCurves(4, 1);
    baseBodyInitCurves.Add(allBaseBodyEdges[26]);
    baseBodyInitCurves.Add(allBaseBodyEdges[29]);
    RPArray<MbFace> baseBodyInitBounds(0, 1);

    MbResultType baseBodyFrontCutFilletRes = ::FilletSolid(*baseBody, cm_Copy, baseBodyInitCurves, baseBodyInitBounds, baseBodyFilletParams, filletNames, baseBody);

    // строим выступ спереди
    RPArray<MbContour> baseAdditionalBackContourArray;
    MbPolyline* additionalRectangle = nullptr;
    MbContour* baseAdditionalBackContour = nullptr;
    // рисуем эскиз
    CreateBaseBodyAditionSketch(baseAdditionalBackContourArray, additionalRectangle, baseAdditionalBackContour, baseBodySketchLength, baseBodySketchWidth);

    MbSweptData rect1SweptData(*pPlaneXZ__top, baseAdditionalBackContourArray);
    MbVector3D baseBodyAdditionalRectExtrusionDirection(0, -1, 0);
    ExtrusionValues baseBodyAdditionalRectExtrusionParams(baseBodyHeight - 120, 0);
    MbResultType baseBodyAdditionalRectExtrusion = ::ExtrusionSolid(rect1SweptData, baseBodyAdditionalRectExtrusionDirection, nullptr, nullptr, false, baseBodyAdditionalRectExtrusionParams, operNames, cNames, baseBodyBackAddition);

    // строим блок сверху
    RPArray<MbContour> topBlockContourArr;
    MbPolyline* topBlockRect = nullptr;
    MbContour* topBlockContour = nullptr;

    CreateTopBlockSketch(topBlockContourArr, topBlockRect, topBlockContour, baseBodySketchWidth);

    //MbSweptData topBlockSweptData(*pPlaneXY__top, topBlockContourArr);
    MbSweptData topBlockSweptData(*pPlaneXZ__top, topBlockContourArr);
    MbVector3D topBlockExtrusionDirection(0, 1, 0);
    ExtrusionValues topBlockExtrusionParams(23, 0);
    MbResultType topBlockExtrusion = ::ExtrusionSolid(topBlockSweptData, topBlockExtrusionDirection, nullptr, nullptr, false, topBlockExtrusionParams, operNames, cNames, topBlock);


    //ушко
    MbPlane* pPlaneYX__middle = new MbPlane(MbCartPoint3D(0, 0, baseBodySketchLength / 2), MbCartPoint3D(1, 0, baseBodySketchLength / 2), MbCartPoint3D(0, 1, baseBodySketchLength / 2));//плоскость для ушка

    RPArray<MbContour> arrContoursEar;
    CreateSketchEar(arrContoursEar);
    // ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ
    MbSweptData sweptData1(*pPlaneYX__middle, arrContoursEar);
    MbVector3D dir1(0, 0, 1);
    const double HEIGHT_FORWARD1 = 11.5, HEIGHT_BACKWARD1 = 11.5;
    ExtrusionValues extrusionParam(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);

    MbSNameMaker operNames1(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames1(0, 1, false);

    MbSolid* pSolid1 = NULL;
    MbResultType resCode = ::ExtrusionSolid(sweptData1, dir1, NULL, NULL, false,
        extrusionParam, operNames1, cNames1, pSolid1);

    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    MbSolid* pCyl = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(20, 157 + 18, 18.5));//центр СК
        points.Add(MbCartPoint3D(20, 157 + 18, 18.5 + 23));//высота цилиндра
        points.Add(MbCartPoint3D(20 + 10, 157 + 18, 18.5 + 23));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCyl);
    }


    MbSolid* pSolid = NULL;
    ::BooleanResult(*pSolid1, cm_Copy, *pCyl, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid1);
    ::BooleanResult(*pSolid1, cm_Copy, *baseBody, cm_Copy, bo_Union,
        flagsBool, operBoolNames, baseBody);
    /*
    MbSolid* pCylCentr = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(20, 0, 30));//центр СК
        points.Add(MbCartPoint3D(20, 30, 30));//высота цилиндра
        points.Add(MbCartPoint3D(20+10, 30, 30));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCylCentr);
    }*/


    MbSolid* pCylSmallDiagL = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(39 - 7, 0, 60 - 8));//центр СК
        points.Add(MbCartPoint3D(39 - 7, 25, 60 - 8));//высота цилиндра
        points.Add(MbCartPoint3D(39 - 7 + 3.4, 25, 60 - 8));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCylSmallDiagL);
    }
    MbSolid* pCylSmallDiagR = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(7, 0, 8));//центр СК
        points.Add(MbCartPoint3D(7, 25, 8));//высота цилиндра
        points.Add(MbCartPoint3D(7 + 3.4, 25, 8));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCylSmallDiagR);
    }

    MbSolid* pCylFront = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(19.5, 9, 30));//центр СК
        points.Add(MbCartPoint3D(19.5, 9 + 5.8, 30));//высота цилиндра
        points.Add(MbCartPoint3D(19.5, 9, 30 + 3.5));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCylFront);
    }

    MbSolid* pCylAside = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(19.5, 9, 60));//центр СК
        points.Add(MbCartPoint3D(19.5, 9, 30));//высота цилиндра
        points.Add(MbCartPoint3D(19.5 + 3.5, 9, 30));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCylAside);
    }

    ::BooleanResult(*baseBody, cm_Copy, *pCylSmallDiagL, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, baseBody);
    ::BooleanResult(*baseBody, cm_Copy, *pCylSmallDiagR, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, baseBody);


    ::BooleanResult(*baseBody, cm_Copy, *pCylFront, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, baseBody);
    ::BooleanResult(*baseBody, cm_Copy, *pCylAside, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, baseBody);

    ///////
    RPArray<MbContour> arrContoursVystypBlock;
    CreateSketchVystypBlock(arrContoursVystypBlock);
    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    MbPlane* pPlaneYZvystypblock = new MbPlane(MbCartPoint3D(20, 0, 0), MbCartPoint3D(20, 1, 0), MbCartPoint3D(20, 0, 1));
    MbSweptData sweptData(*pPlaneYZvystypblock, arrContoursVystypBlock);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    // Ось вращения для построения тела:
    MbAxis3D axis(pl.GetAxisY());
    axis.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(20, 0, 30)));

    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* pKolp = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pKolp);
    ::BooleanResult(*baseBody, cm_Copy, *pKolp, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, baseBody);

    MbSolid* pBlock = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(4);
        points.Add(MbCartPoint3D(40, baseBodyHeight, 45));
        points.Add(MbCartPoint3D(35, baseBodyHeight, 45));
        points.Add(MbCartPoint3D(35, baseBodyHeight, 15));
        points.Add(MbCartPoint3D(40, 120, 15));
        ::ElementarySolid(points, et_Block, names, pBlock);

    }
    ::BooleanResult(*baseBody, cm_Copy, *pBlock, cm_Copy, bo_Union,
        flagsBool, operBoolNames, baseBody);


    // show(baseBodyBackAddition);

    // show(Style(1, RGB(0, 255, 0)), topBlock);

    ::DeleteItem(rectangle);
    ::DeleteItem(baseBodyContour);

    ::DeleteItem(additionalRectangle);
    ::DeleteItem(baseAdditionalBackContour);
    ::DeleteItem(baseBodyBackAddition);
    ::DeleteItem(pBlock);

    ::DeleteItem(topBlockRect);
    ::DeleteItem(topBlockContour);
    ::DeleteItem(topBlock);

    SolidSPtr MainSolid(baseBody);

    return MainSolid;
}