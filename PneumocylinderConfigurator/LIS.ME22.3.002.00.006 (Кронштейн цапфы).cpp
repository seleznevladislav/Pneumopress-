#include "BuildMathModel.h"

using namespace BuildMathModel;


double a = 70; // ширина
double b = 135; // длина 
double c = 16; // высота 
double X_sdvig = 110;
double Z_sdvig = 25;

void CreateSketchtr(RPArray<MbContour>& _arrContours) // эскизы для отверстий 
{
    double rad_m = 5.75; // радиус маленьких отверстий 
    double ots1_x = 50; // координаты для плоскости XZ
    double ots2_x = 20;
    double ots1_z = 17;
    double ots2_z = 53;

    MbArc* pCircle1 = new MbArc(MbCartPoint(ots1_x - X_sdvig, ots1_z - Z_sdvig), rad_m);  //создается окружность для маленьких отверстий 
    MbArc* pCircle2 = new MbArc(MbCartPoint(ots2_x - X_sdvig, ots1_z - Z_sdvig), rad_m);
    MbArc* pCircle3 = new MbArc(MbCartPoint(ots2_x - X_sdvig, ots2_z - Z_sdvig), rad_m);
    MbArc* pCircle4 = new MbArc(MbCartPoint(ots1_x - X_sdvig, ots2_z - Z_sdvig), rad_m);

    _arrContours.push_back(new MbContour(*pCircle1, true));
    _arrContours.push_back(new MbContour(*pCircle2, true));
    _arrContours.push_back(new MbContour(*pCircle3, true));
    _arrContours.push_back(new MbContour(*pCircle4, true));

}

void CreateSketch1tr(RPArray<MbContour>& _arrContours1)
{
    double u = 5; // координата маленьких углов
    // построение основного тела 

    MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
    SArray<MbCartPoint> points1(9);
    points1.Add(MbCartPoint(u - X_sdvig, 0 - Z_sdvig));
    points1.Add(MbCartPoint(125 - X_sdvig, 0 - Z_sdvig));
    points1.Add(MbCartPoint(b - X_sdvig, u * 2 - Z_sdvig));
    points1.Add(MbCartPoint(b - X_sdvig, a / 2 + 5 - Z_sdvig));
    points1.Add(MbCartPoint(b - 30 - X_sdvig, a - Z_sdvig));
    points1.Add(MbCartPoint(u - X_sdvig, a - Z_sdvig));
    points1.Add(MbCartPoint(0 - X_sdvig, a - u - Z_sdvig));
    points1.Add(MbCartPoint(0 - X_sdvig, u - Z_sdvig));
    points1.Add(MbCartPoint(u - X_sdvig, 0 - Z_sdvig));

    MbPolyline* pPolyline = new MbPolyline(points1, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours1.push_back(pContourPolyline);
}



SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_006()
{


    double c1 = 25; // точка центра большого отверстия по z
    double rad_b = 17.5; // радиус большого отверстия 
    double u_b = 30; //координата больших углов

    MbPlacement3D pl;

    RPArray<MbContour> _arrContours1;
    CreateSketch1tr(_arrContours1);

    MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 0, 1));
    MbSweptData sweptData(*pPlaneXZ, _arrContours1);
    MbVector3D dir(0, 1, 0);

    const double HEIGHT_FORWARD = 16.0, HEIGHT_BACKWARD = 0.0;
    ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Вызов функции-утилиты для построения твердого тела выдавливания
    MbSolid* pSolidEX = nullptr;
    MbResultType res = ::ExtrusionSolid(sweptData, dir, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolidEX);


    MbSolid* pCyl = nullptr;
    {
        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(b - c1 - X_sdvig, 0, c1 - Z_sdvig));//центр СК
        points.Add(MbCartPoint3D(b - c1 - X_sdvig, c, c1 - Z_sdvig));//высота цилиндра
        points.Add(MbCartPoint3D(b - c1 + rad_b - X_sdvig, c, c1 - Z_sdvig));//радиус цилиндра
        ::ElementarySolid(points, et_Cylinder, names, pCyl);
    }

    //Построение маленьких отверстий

    MbSolid* pSolidholes = nullptr;
    {
        RPArray<MbContour> arrContours;
        CreateSketchtr(arrContours);

        MbVector3D dirY(0, 1, 0);
        MbSweptData sweptData(*pPlaneXZ, arrContours);
        const double HEIGHT_FORWARD1 = 16, HEIGHT_BACKWARD1 = 0;
        ExtrusionValues extrusionParams(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);

        MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
        PArray<MbSNameMaker> cNames(0, 1, false);

        MbResultType resholes = ::ExtrusionSolid(sweptData, dirY, nullptr, nullptr, false, extrusionParams, names, cNames, pSolidholes);
    }

    //Выдавливание отверстий

    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    //центральное
    MbSolid* pSolid = NULL;
    MbResultType res3 = ::BooleanResult(*pSolidEX, cm_Copy, *pCyl, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);
    //остальные
    MbSolid* pSolid1 = NULL;
    MbResultType res1 = ::BooleanResult(*pSolid, cm_Copy, *pSolidholes, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid1);


    // фаски 

    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params;
    //Длины катетов фаски
    params.distance1 = 1;
    params.distance2 = 1;
    params.form = st_Chamfer;
    params.prolong = true;
    params.smoothCorner = SmoothValues::ec_uniform;

    // Запрос всех ребер исходного тела
    RPArray<MbCurveEdge> allEdges(4, 1);
    pSolid1->GetEdges(allEdges);

    RPArray<MbCurveEdge> initCurves(4, 1);
    for (int i = 0; i < 30; i++)
        initCurves.Add(allEdges[i]);

    RPArray<MbFace> initBounds(0, 1);

    // 6) Вызов функции построения фасок
    MbSolid* pResult_kron = NULL;
    MbResultType res2 = ::ChamferSolid(*pSolid1, cm_Copy, initCurves,
        params, chamferNames, pResult_kron);


    // Уменьшение счетчиков ссылок динамически созданных объектов ядра

    SolidSPtr MainSolid(pResult_kron);

    ::DeleteItem(pResult_kron);
    ::DeleteItem(pSolidEX);
    ::DeleteItem(pCyl);
    ::DeleteItem(pSolid1);
    ::DeleteItem(pSolid);
    ::DeleteItem(pSolidholes);

    return MainSolid;
}
