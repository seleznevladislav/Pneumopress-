#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketchxa(RPArray<MbContour>& _arrContours)
{

    // эскиз для вырезания треугольничков на голове болта

    SArray<MbCartPoint> arrPnts(3);
    arrPnts.Add(MbCartPoint(12, 270));
    arrPnts.Add(MbCartPoint(17, 270));
    arrPnts.Add(MbCartPoint(17, 270 - 3));

    // Построение единой ломаной внешнего контура по точкам

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContourPolyline);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_015()
{

    double height_cyl = 240; // высота стержня болта
    double rad_cyl = 7; // радиус стержня 
    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    // построение стержня 

    MbSolid* pCyl = NULL;
    {
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(0, 0, 0));
        points.Add(MbCartPoint3D(0, height_cyl, 0));
        points.Add(MbCartPoint3D(rad_cyl, 0, 0));

        ElementarySolid(points, et_Cylinder, elNames, pCyl);

    }

    //построение головы 

    double height_ver = 270; //высота головки 
    double b = 12; // половина стороны головки 

    MbSolid* pBlock = NULL;

    {
        SArray<MbCartPoint3D> pntsBlock(4);
        pntsBlock.Add(MbCartPoint3D(b, height_cyl, b));
        pntsBlock.Add(MbCartPoint3D(b, height_cyl, -b));
        pntsBlock.Add(MbCartPoint3D(-b, height_cyl, -b));
        pntsBlock.Add(MbCartPoint3D(-b, height_ver, b));
        ::ElementarySolid(pntsBlock, et_Block, elNames, pBlock);
    }


    //объединение стержня и головы 


    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
    MbSolid* pBolt = NULL;
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    ::BooleanResult(*pCyl, cm_Copy, *pBlock, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pBolt);



    // вращение треугольника для выреза 


    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> _arrContours;
    CreateSketchxa(_arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, _arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    // Именователи для операции построения тела вращения и для контуров образующей
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Ось вращения для построения тела:
    MbAxis3D axis(pl.GetAxisY());

    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* pTriangle = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pTriangle);



    // булевая операция вычитания 



     // Именователь граней для построения тела с помощью булевой операции 
    MbSNameMaker operBoolNames1(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    // Флаги булевой операции: построение замкнутого тела с объединением
    // подобных граней и ребер.
    MbBooleanFlags flagsBool1;
    flagsBool1.InitBoolean(true);
    flagsBool1.SetMergingFaces(true);
    flagsBool1.SetMergingEdges(true);

    // Результирующее тело
    MbSolid* pBoltik = NULL;
    // Вызов булевой операции для выполнения объединения.
    // Для выполнения вычитания надо вместо типа операции bo_Union указать
    // значение bo_Difference, для пересечения - значение bo_Intersect.
    MbResultType res1 = ::BooleanResult(*pBolt, cm_Copy, *pTriangle, cm_Copy, bo_Difference,
        flagsBool1, operBoolNames1, pBoltik);


    SolidSPtr MainSolid(pBoltik);

    ::DeleteItem(pBoltik);
    ::DeleteItem(pCyl);
    ::DeleteItem(pBlock);
    ::DeleteItem(pTriangle);
    ::DeleteItem(pBolt);
    return MainSolid;
}