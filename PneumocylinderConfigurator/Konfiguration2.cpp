#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_Konfiguration2()
{
    double heightCylinder = 50;
    double radiusCylinder = 10;
    double heightCube = radiusCylinder * 2;


    MbSolid* pCube = NULL;

    MbSolid* pCyl1 = NULL;

    // Объект-именователь для построения цилиндров - элементарных тел
    MbSNameMaker cylNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    // Массив точек для построения первого цилиндра   
    SArray<MbCartPoint3D> pntsCyl1(3);
    pntsCyl1.Add(MbCartPoint3D(0, 0, 0));
    pntsCyl1.Add(MbCartPoint3D(0, 0, -heightCylinder));
    pntsCyl1.Add(MbCartPoint3D(radiusCylinder, 0, 0));

    // Построение элементарного тела - цилиндра - по трем точкам
    ElementarySolid(pntsCyl1, et_Cylinder, cylNames, pCyl1);



    // Массив характерных точек для куба
    SArray<MbCartPoint3D> arrPnts(4);
    arrPnts.Add(MbCartPoint3D(-heightCube / 2, -heightCube / 2, -heightCylinder - heightCube));
    arrPnts.Add(MbCartPoint3D(heightCube / 2, -heightCube / 2, -heightCylinder - heightCube));
    arrPnts.Add(MbCartPoint3D(heightCube / 2, heightCube / 2, -heightCylinder - heightCube));
    arrPnts.Add(MbCartPoint3D(-heightCube / 2, heightCube / 2, -heightCylinder - heightCube));



    MbSNameMaker namesCube(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);

    MbResultType resCube = ::ElementarySolid(arrPnts, et_Block, namesCube, pCube);

    /////////////
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);


    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);


    MbSolid* pSolid = NULL;

    MbResultType res = ::BooleanResult(*pCyl1, cm_Copy, *pCube, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);

    SolidSPtr MainSolid(pSolid);

    // Уменьшение счетчиков ссылок динамических объектов ядра
    ::DeleteItem(pSolid);
    ::DeleteItem(pCyl1);
    ::DeleteItem(pCube);

    return MainSolid;
}