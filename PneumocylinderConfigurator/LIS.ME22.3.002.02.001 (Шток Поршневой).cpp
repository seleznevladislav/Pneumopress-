#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSquareSketchKD(RPArray<MbContour>& _arrContours, MbPolyline* polyline, MbContour* contour)
{
    double rightSecondBlockWidth = 18.4;
    double filletRadius = 5.0;

    SArray<MbCartPoint> squarePoints(4);
    // верхние левая и правая точки
    squarePoints.Add(MbCartPoint(rightSecondBlockWidth / 2, rightSecondBlockWidth / 2));
    squarePoints.Add(MbCartPoint(-rightSecondBlockWidth / 2, rightSecondBlockWidth / 2));

    // нижние левая и правая точки
    squarePoints.Add(MbCartPoint(-rightSecondBlockWidth / 2, -rightSecondBlockWidth / 2));
    squarePoints.Add(MbCartPoint(rightSecondBlockWidth / 2, -rightSecondBlockWidth / 2));

    polyline = new MbPolyline(squarePoints, true);

    contour = NULL;
    ::FilletPolyContour(polyline, filletRadius, false, squarePoints[1], contour);
    ptrdiff_t idxSideTop = 2;
    ptrdiff_t idxSideRight = 4;
    ptrdiff_t idxSideBottom = 6;
    contour->FilletTwoSegments(idxSideTop, filletRadius);
    contour->FilletTwoSegments(idxSideRight, filletRadius);
    contour->FilletTwoSegments(idxSideBottom, filletRadius);

    //show(contour);

    _arrContours.push_back(contour);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_001()
{
    // параметры левого крайнего цилиндра
    int leftFirstCylinderLength = 14;
    int leftFirstCylinderDiametr = 14;

    // параметры второго слева цилиндра
    int leftSecondCylinderLength = -leftFirstCylinderLength - 22;
    int leftSecondCylinderRezbDiametr = 16;

    // параметры третьего слева цилиндра
    int leftThirdCylinderLength = leftSecondCylinderLength - 16;
    int leftThirdCylinderDiameter = 18;

    // параметры длинного цилиндра
    int longCylinderLength = leftThirdCylinderLength - 200;
    int longCylinderDiameter = 25;

    // параметры второго справа элемента (блок)
    //int rightSecondBlockLength = longCylinderLength - 10;
    int rightSecondBlockLength = 10;

    // параметры крайнего правого цилиндра
    int rightCylinderLength = 22;
    int rightCylinderRezbDiameter = 18;

    MbPlane* pPlaneXY__offset = new MbPlane(MbCartPoint3D(0, 0, longCylinderLength),
        MbCartPoint3D(1, 0, longCylinderLength),
        MbCartPoint3D(0, 1, longCylinderLength));

    // Именователь граней «по умолчанию»
    MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);

    PArray<MbSNameMaker> cNames(0, 1, false);

    //Объект-именователь для операции скругления ребер
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    // контур для правого квадрата
    RPArray<MbContour> squareContour;
    // линия для правого квадрата
    MbPolyline* pSquare = nullptr;
    // скругления для правого квадрата 
    MbContour* pFillets = nullptr;

    // делаем эскиз
    CreateSquareSketchKD(squareContour, pSquare, pFillets);
    MbSweptData sweptData(*pPlaneXY__offset, squareContour);

    // объявление твердых тел
    MbSolid* leftFirstCylinder = nullptr;
    MbSolid* leftSecondCylinder = nullptr;
    MbSolid* leftThirdCylinder = nullptr;
    MbSolid* longCylinder = nullptr;
    MbSolid* square = nullptr;
    MbSolid* firstRightCylinder = nullptr;

    // параметры для фасок
    SmoothValues cylinderChamferParams;
    cylinderChamferParams.distance1 = 0.5;
    cylinderChamferParams.distance2 = 0.5;
    // Тип фаски - построение фаски с заданными катетами
    cylinderChamferParams.form = st_Chamfer;
    // Режим автоматического скругления ребер, гладко стыкующиеся с ребрами
    // из входного массива
    cylinderChamferParams.prolong = true;
    // Способ скругления троек ребер
    cylinderChamferParams.smoothCorner = SmoothValues::ec_uniform;

    // Построение левого цилиндра 14*14
    SArray<MbCartPoint3D> leftCylinderPoints(3);
    leftCylinderPoints.Add(MbCartPoint3D(0, 0, 0));
    leftCylinderPoints.Add(MbCartPoint3D(0, 0, -leftFirstCylinderLength));
    leftCylinderPoints.Add(MbCartPoint3D(0, leftFirstCylinderDiametr / 2, 0));

    ::ElementarySolid(leftCylinderPoints, et_Cylinder, names, leftFirstCylinder);

    // скругление левой грани на 2мм
    SmoothValues leftFilletParams;
    leftFilletParams.distance1 = 2;
    leftFilletParams.distance2 = 2;
    leftFilletParams.form = st_Fillet;
    leftFilletParams.conic = 0;
    leftFilletParams.prolong = false;
    leftFilletParams.smoothCorner = SmoothValues::ec_uniform;
    leftFilletParams.keepCant = ts_negative;
    leftFilletParams.strict = true;

    RPArray<MbCurveEdge> leftCylinderAllEdges(4, 1);
    leftFirstCylinder->GetEdges(leftCylinderAllEdges);

    RPArray<MbCurveEdge> leftCylindetInitCurves(4, 1);
    leftCylindetInitCurves.Add(leftCylinderAllEdges[0]);

    RPArray<MbFace> leftCylinderInitBounds(0, 1);

    MbResultType filletLeft = FilletSolid(
        *leftFirstCylinder,
        cm_Copy,
        leftCylindetInitCurves,
        leftCylinderInitBounds,
        leftFilletParams,
        filletNames,
        leftFirstCylinder
    );

    // Построение второго слева цилиндра под резьбу
    SArray<MbCartPoint3D> leftSecondCylinderPoints(3);
    leftSecondCylinderPoints.Add(MbCartPoint3D(0, 0, -leftFirstCylinderLength));

    leftSecondCylinderPoints.Add(
        MbCartPoint3D(0, 0, leftSecondCylinderLength));

    leftSecondCylinderPoints.Add(
        MbCartPoint3D(0, leftSecondCylinderRezbDiametr / 2, -leftFirstCylinderLength)
    );
    ::ElementarySolid(leftSecondCylinderPoints, et_Cylinder, names, leftSecondCylinder);

    // фаска на втором слева цилиндре
    RPArray<MbCurveEdge> secondLeftCylinderaAllEdges(4, 1);
    leftSecondCylinder->GetEdges(secondLeftCylinderaAllEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> secondLeftCylinderInitCurves(4, 1);
    secondLeftCylinderInitCurves.Add(secondLeftCylinderaAllEdges[0]);
    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> sescondLeftCylinderInitBounds(0, 1);
    // 6) Вызов функции построения фасок
    MbResultType leftSecondCylinderChamfer = ::ChamferSolid(*leftSecondCylinder, cm_Copy, secondLeftCylinderInitCurves,
        cylinderChamferParams, filletNames, leftSecondCylinder);


    // Построение третьего слева цилиндр 16*18
    SArray <MbCartPoint3D> leftThirdCylinderPoints(3);
    leftThirdCylinderPoints.Add(MbCartPoint3D(0, 0, leftSecondCylinderLength));
    leftThirdCylinderPoints.Add(MbCartPoint3D(0, 0, leftThirdCylinderLength));
    leftThirdCylinderPoints.Add(MbCartPoint3D(0, leftThirdCylinderDiameter / 2, leftThirdCylinderLength));

    ::ElementarySolid(leftThirdCylinderPoints, et_Cylinder, names, leftThirdCylinder);

    // фаска на третьем слева цилиндре
    RPArray<MbCurveEdge> thirdLeftCylinderaAllEdges(4, 1);
    leftThirdCylinder->GetEdges(thirdLeftCylinderaAllEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> thirdLeftCylinderInitCurves(4, 1);
    thirdLeftCylinderInitCurves.Add(thirdLeftCylinderaAllEdges[0]);
    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> thirdLeftCylinderInitBounds(0, 1);
    // 6) Вызов функции построения фасок
    MbResultType leftThirdCylinderChamfer = ::ChamferSolid(*leftThirdCylinder, cm_Copy, thirdLeftCylinderInitCurves, cylinderChamferParams, filletNames, leftThirdCylinder);

    // Построение длинного цилиндра
    SArray <MbCartPoint3D> longCylinderPoints(3);
    longCylinderPoints.Add(MbCartPoint3D(0, 0, leftThirdCylinderLength));
    longCylinderPoints.Add(MbCartPoint3D(0, 0, longCylinderLength));
    longCylinderPoints.Add(MbCartPoint3D(0, longCylinderDiameter / 2, longCylinderLength));

    ::ElementarySolid(longCylinderPoints, et_Cylinder, names, longCylinder);

    // фаска на длинном цилиндре
    RPArray<MbCurveEdge> longCylinderaAllEdges(4, 1);
    longCylinder->GetEdges(longCylinderaAllEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> longCylinderInitCurves(4, 1);
    longCylinderInitCurves.Add(longCylinderaAllEdges[0]);
    longCylinderInitCurves.Add(longCylinderaAllEdges[2]);
    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> longCylinderInitBounds(0, 1);
    MbResultType longCylinderChamfer = ::ChamferSolid(*longCylinder, cm_Copy, longCylinderInitCurves, cylinderChamferParams, filletNames, longCylinder);

    // Построение квадрата
    MbVector3D dirZ(0, 0, -1);
    ExtrusionValues squareExtrusionParams(0, -rightSecondBlockLength);
    MbResultType squareResult = ::ExtrusionSolid(sweptData, dirZ, nullptr, nullptr, false, squareExtrusionParams, names, cNames, square);

    // Построение первого правого цилиндра
    SArray<MbCartPoint3D> rightFirstCylinderPoints(3);
    rightFirstCylinderPoints.Add(MbCartPoint3D(0, 0, longCylinderLength - 10));

    rightFirstCylinderPoints.Add(
        MbCartPoint3D(0, 0, longCylinderLength - 10 - rightCylinderLength));

    rightFirstCylinderPoints.Add(
        MbCartPoint3D(0, rightCylinderRezbDiameter / 2, rightCylinderLength)
    );
    ::ElementarySolid(rightFirstCylinderPoints, et_Cylinder, names, firstRightCylinder);

    // фаска на правом цилиндре
    RPArray<MbCurveEdge> rightCylinderAllEdges(4, 1);
    firstRightCylinder->GetEdges(rightCylinderAllEdges);
    // Массив ребер для скругления
    RPArray<MbCurveEdge> rightCylinderInitCurves(4, 1);
    rightCylinderInitCurves.Add(rightCylinderAllEdges[2]);
    // 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
    RPArray<MbFace> rightCylinderInitBounds(0, 1);
    MbResultType rightCylinderChamfer = ::ChamferSolid(*firstRightCylinder, cm_Copy, rightCylinderInitCurves, cylinderChamferParams, filletNames, firstRightCylinder);


    // Именователь граней для построения тела с помощью булевой операции 
    MbSNameMaker operBoolNamesUnion(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    // Флаги булевой операции: построение замкнутого тела с объединением
    // подобных граней и ребер.
    MbBooleanFlags flagsBool_SH;
    flagsBool_SH.InitBoolean(true);
    flagsBool_SH.SetMergingFaces(true);
    flagsBool_SH.SetMergingEdges(true);

    // Результирующее тело
    MbSolid* pSolid_Shtok_res = NULL;
    MbResultType res = ::BooleanResult(*leftFirstCylinder, cm_Copy, *leftSecondCylinder, cm_Copy, bo_Union, flagsBool_SH, operBoolNamesUnion, pSolid_Shtok_res);
    MbResultType res1 = ::BooleanResult(*pSolid_Shtok_res, cm_Copy, *leftThirdCylinder, cm_Copy, bo_Union, flagsBool_SH, operBoolNamesUnion, pSolid_Shtok_res);
    MbResultType res2 = ::BooleanResult(*pSolid_Shtok_res, cm_Copy, *longCylinder, cm_Copy, bo_Union, flagsBool_SH, operBoolNamesUnion, pSolid_Shtok_res);
    MbResultType res3 = ::BooleanResult(*pSolid_Shtok_res, cm_Copy, *square, cm_Copy, bo_Union, flagsBool_SH, operBoolNamesUnion, pSolid_Shtok_res);
    MbResultType res4 = ::BooleanResult(*pSolid_Shtok_res, cm_Copy, *firstRightCylinder, cm_Copy, bo_Union, flagsBool_SH, operBoolNamesUnion, pSolid_Shtok_res);



    SolidSPtr MainSolid(pSolid_Shtok_res);

    ::DeleteItem(pSolid_Shtok_res);
    ::DeleteItem(leftFirstCylinder);
    ::DeleteItem(leftSecondCylinder);
    ::DeleteItem(leftThirdCylinder);
    ::DeleteItem(longCylinder);
    ::DeleteItem(square);
    ::DeleteItem(firstRightCylinder);
    ::DeleteItem(pSquare);
    ::DeleteItem(pFillets);

    return MainSolid;
}