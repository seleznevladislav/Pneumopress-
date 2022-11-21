#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_011()
{
    // LIS.ME22.3.002.00.011 Кронштейн регулировочный (Козырь)

    MbSNameMaker names(1, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker cylNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    //  Размеры : ширина, длина, выдавливание(высота) прямоугольника
    // Первый основной блок
    double blockWidth1 = 60;
    double blockLength1 = 90;
    double blockExtrusion1 = 40;
    //двигаем ск
    double Xsdvig = -70;
    double Ysdvig = -14;

    SArray<MbCartPoint3D> pointsBlock1(4);
    pointsBlock1.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, 0)); // начало ЛСК
    pointsBlock1.Add(MbCartPoint3D(blockLength1 + Xsdvig, 0 + Ysdvig, 0)); // длина по X
    pointsBlock1.Add(MbCartPoint3D(0 + Xsdvig, blockWidth1 + Ysdvig, 0)); // ширина по Y
    pointsBlock1.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, blockExtrusion1)); // выдавливание по z

    MbSolid* pBlock1 = nullptr;
    ::ElementarySolid(pointsBlock1, et_Block, names, pBlock1);

    //  Размеры : ширина, длина, выдавливание(высота) прямоугольника
    // Второй блок для выдавливания
    double blockWidth2 = 60;
    double blockLength2 = 50;
    double blockExtrusion2 = 20;

    SArray<MbCartPoint3D> pointsBlock2(4);
    pointsBlock2.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, 0)); // начало ЛСК
    pointsBlock2.Add(MbCartPoint3D(blockLength2 + Xsdvig, 0 + Ysdvig, 0)); // длина по X
    pointsBlock2.Add(MbCartPoint3D(0 + Xsdvig, blockWidth2 + Ysdvig, 0)); // ширина по Y
    pointsBlock2.Add(MbCartPoint3D(0 + Xsdvig, 0 + Ysdvig, blockExtrusion2)); // выдавливание по z

    MbSolid* pBlock2 = nullptr;
    ::ElementarySolid(pointsBlock2, et_Block, names, pBlock2);

    // выдавливание прямоугольной части
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    MbSolid* pSolid = NULL;

    MbResultType res1 = ::BooleanResult(*pBlock1, cm_Copy, *pBlock2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    double cylRadius1 = 8.5; // радиус для выдавливания  одной окружности по центру
    double centerCircleX1 = 22; // центр по X
    double centerCircleY1 = 30; // центр по X
    SArray<MbCartPoint3D> pointsCyl1(3);
    pointsCyl1.Add(MbCartPoint3D(centerCircleX1 + Xsdvig, centerCircleY1 + Ysdvig, 0)); // начало ЛСК
    pointsCyl1.Add(MbCartPoint3D(centerCircleX1 + Xsdvig, centerCircleY1 + Ysdvig, blockExtrusion1)); // по Z
    pointsCyl1.Add(MbCartPoint3D(centerCircleX1 + cylRadius1 + Xsdvig, centerCircleY1 + Ysdvig, 0)); // по X

    MbSolid* pCyl1 = nullptr;
    ::ElementarySolid(pointsCyl1, et_Cylinder, cylNames, pCyl1);

    // выдавливание двух отверстий
    MbResultType res2 = ::BooleanResult(*pSolid, cm_Copy, *pCyl1, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // выдавливание двух отверстий 
    double cylRadius2 = 7; // радиус для выдавливания  одной окружности по центру
    double centerCircleX2 = 70; // центр по X
    double centerCircleY2 = 14; // центр по X
    SArray<MbCartPoint3D> pointsCyl2(3);
    pointsCyl2.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, 0)); // начало ЛСК
    pointsCyl2.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, blockExtrusion1)); // по Z
    pointsCyl2.Add(MbCartPoint3D(centerCircleX2 + cylRadius2 + Xsdvig, centerCircleY2 + Ysdvig, 0)); // по X

    MbSolid* pCyl2 = nullptr;
    ::ElementarySolid(pointsCyl2, et_Cylinder, cylNames, pCyl2);

    MbResultType res3 = ::BooleanResult(*pSolid, cm_Copy, *pCyl2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // отверстие в этой же точке с цилиндрической зенковкой
    double cylRadius3 = 8.5; // радиус для выдавливания окружности с зенкованием
    SArray<MbCartPoint3D> pointsCyl3(3);
    pointsCyl3.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, blockExtrusion1)); // начало ЛСК
    pointsCyl3.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY2 + Ysdvig, blockExtrusion1 - 10)); // по Z
    pointsCyl3.Add(MbCartPoint3D(centerCircleX2 + cylRadius3 + Xsdvig, centerCircleY2 + Ysdvig, 0)); // по X

    MbSolid* pCyl3 = nullptr;
    ::ElementarySolid(pointsCyl3, et_Cylinder, cylNames, pCyl3);

    MbResultType res4 = ::BooleanResult(*pSolid, cm_Copy, *pCyl3, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // второе симметричное отверстие
    double centerCircleY3 = 46; // центр по X
    SArray<MbCartPoint3D> pointsCyl4(3);
    pointsCyl4.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, 0)); // начало ЛСК
    pointsCyl4.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, blockExtrusion1)); // по Z
    pointsCyl4.Add(MbCartPoint3D(centerCircleX2 + cylRadius2 + Xsdvig, centerCircleY3 + Ysdvig, 0)); // по X

    MbSolid* pCyl4 = nullptr;
    ::ElementarySolid(pointsCyl4, et_Cylinder, cylNames, pCyl4);

    MbResultType res5 = ::BooleanResult(*pSolid, cm_Copy, *pCyl4, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

    // отверстие в этой же точке с цилиндрической зенковкой
    SArray<MbCartPoint3D> pointsCyl5(3);
    pointsCyl5.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, blockExtrusion1)); // начало ЛСК
    pointsCyl5.Add(MbCartPoint3D(centerCircleX2 + Xsdvig, centerCircleY3 + Ysdvig, blockExtrusion1 - 10)); // по Z
    pointsCyl5.Add(MbCartPoint3D(centerCircleX2 + cylRadius3 + Xsdvig, centerCircleY3 + Ysdvig, 0)); // по X

    MbSolid* pCyl5 = nullptr;
    ::ElementarySolid(pointsCyl5, et_Cylinder, cylNames, pCyl5);

    MbResultType res6 = ::BooleanResult(*pSolid, cm_Copy, *pCyl5, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);


    ::DeleteItem(pBlock1);


    SolidSPtr MainSolid(pSolid);
    return MainSolid;
}