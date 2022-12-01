#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_Konfiguration1()
{
    double heightCone = 50;
    double radiusCylinder = 10;
    double heightCylinder = 50;

    MbSolid* pCone = NULL;
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



    MbSNameMaker coneNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    SArray<MbCartPoint3D> pntsCone(3);
    pntsCone.Add(MbCartPoint3D(0, 0, -heightCone - heightCylinder));
    pntsCone.Add(MbCartPoint3D(0, 0, -heightCylinder));
    pntsCone.Add(MbCartPoint3D(radiusCylinder, 0, -heightCylinder));

    // Построение элементарного тела - конуса - по трем точкам
    ElementarySolid(pntsCone, et_Cone, coneNames, pCone);


    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);


    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);


    MbSolid* pSolid = NULL;

    MbResultType res = ::BooleanResult(*pCyl1, cm_Copy, *pCone, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pSolid);


    SolidSPtr MainSolid(pSolid);

    // Уменьшение счетчиков ссылок динамических объектов ядра
    ::DeleteItem(pSolid);
    ::DeleteItem(pCone);
    ::DeleteItem(pCyl1);

    return MainSolid;
}