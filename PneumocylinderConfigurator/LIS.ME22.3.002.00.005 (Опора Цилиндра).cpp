#include "BuildMathModel.h"

#include <action_solid.h> 
#include "cur_polyline.h" 
#include "surf_plane.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateBlock(SArray<MbCartPoint3D>& _CardPoint, float x, float y, float z, float x1, float y1, float z1)
{
    _CardPoint.RemoveInd(0, 4);
    _CardPoint.Add(MbCartPoint3D(x, y, z));
    _CardPoint.Add(MbCartPoint3D(x + x1, y, z));
    _CardPoint.Add(MbCartPoint3D(x, y + y1, z));
    _CardPoint.Add(MbCartPoint3D(x, y, z + z1));
}

void CreateCylinder(SArray<MbCartPoint3D>& _CardPoint, float x, float y, float z, float y1, float x1, float x2, float y2, float z1)
{
    _CardPoint.RemoveInd(0, 3);
    _CardPoint.Add(MbCartPoint3D(x, y, z));
    _CardPoint.Add(MbCartPoint3D(x + x2, y + y1, z + z1));
    _CardPoint.Add(MbCartPoint3D(x + x1, y + y2, z));
}


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_005()
{
    //ГЛАВНЫЕ РАЗМЕРЫ
    float mn_l = 350.0;
    float mn_w = 154.0;
    float mn_btw = 50.0; //расстояние МЕЖДУ двумя отзеркаленными элементами

    //ПРЯМОУГОЛЬНИКИ
      // 1 прямоугольник
    float rtg1_l = 106.0;
    float rtg1_w = 70.0;
    float rtg1_d = 190.0;
    float rtg1_th1 = 16.0;
    float rtg1_th2 = 20.0;
    float rtg1_th3 = 20.0;

    // 2 прямоугольник
    float rtg2_w = 40.0;
    float rtg2_l = 130.0;

    // 3 прямоугольник
    float rtg3_l = 165.0;
    float rtg3_w = 25.0; //ширина паза на большом прямоугольнике - нет на чертеже
    float rtg3_th = 4.0;
    float rtg3_ind = 12.5;

    //ЦИЛИНДРЫ
      //1 цилиндр 
    float cln1_ix = 215.0;
    float cln1_iy = 90.0;
    float cln1_d = (rtg1_l - mn_btw - rtg1_th1 * 2) / 2; //глубина выдавливания = 12
    float cln1_D = 40.0; // диаметр цилиндра
    float cln1_fl = 3.0; //радиус скругления - нет на чертеже

    //2 цилиндр 
    float cln2_D = 20.0;
    float cln2_fl = 5.0; //радиус скругления - нет на чертеже

    //3, 4, 5 цилиндр 
    float cln3_D = 12.0;
    float cln3_dist = 35.0; //отступ от большого прямоугольника по x
    //нет на чертеже
    float cln3_btw = (rtg1_d - cln3_dist * 2) / 2; //60 расстояние между - нет на чертеже

    //6 цилиндр
    float cln6_D = 14.5;
    float cln6_dist = 25;//отступ от большого прямоугольника по y
    //нет на чертеже
//7 цилиндр + 1 массив
    float cln7_D = 8.0;
    float cln7_d = 8.0; //глубина отверстия
    float cln7_indx = 15.0; //
    float cln7_distx = 35.0; //расстояние между отверстиями по x
    float cln7_distz = 86.0; //расстояние между отверстиями по z 
    int cln7_kx = 3; //количество отверстий по x
    int cln7_kz = 2; //количество отверстий по z

    //8 цилиндр + 2 массив
    float cln8_D = 11.5; //диаметр отверстия - нет на чертеже
    float cln8_indx = 10.0;
    float cln8_disty = 36.0; //расстояние между отверстиями по y
    float cln8_distx = 30.0; //расстояние между отверстиями по x
    int cln8_ky = 2; //количество отверстий по y
    int cln8_kx = 2; //количество отверстий по x

    //ТЕЛО НЕПОНЯТНОЙ ФОРМЫ
      //основные размеры
    float er_th = 16.0;
    float er_ch = 5.0; //фаска - нет на чертеже
    //по y размеры
    float er_w1 = 40.0;
    float er_w2 = 40.0;
    //по x размеры
    float er_l1 = 140.0;
    float er_l3 = mn_w - rtg1_w - er_w1 - rtg3_th; //тоже 40
    float er_l4 = 210.0;
    float er_l5 = 100.0;

    SArray<MbCartPoint3D> CardPointB(4);
    SArray<MbCartPoint3D> CardPointC(3);

    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    //Создаем 3 блока
    CreateBlock(CardPointB, rtg2_l, (-rtg1_w + rtg1_th1 * 2) * 2, -(rtg1_w + rtg1_th2 - rtg1_th1) / 2,
        rtg2_w, 5 * (rtg1_w - rtg1_th1 * 2) / 2, rtg1_w + (rtg1_th2 - rtg1_th1));
    MbSolid* pBlock1 = NULL;
    ::ElementarySolid(CardPointB, et_Block, elNames, pBlock1);

    CreateBlock(CardPointB, -rtg1_d + rtg1_th3, -(rtg1_w - rtg1_th1 * 2) / 2, -(rtg1_w + rtg3_th) / 2,
        rtg1_d * 2 - rtg1_th3 * 2, rtg1_w - rtg1_th1 * 2, rtg1_w + rtg3_th);
    MbSolid* pBlock2 = NULL;
    ::ElementarySolid(CardPointB, et_Block, elNames, pBlock2);

    CreateBlock(CardPointB, 0, -rtg1_w / 2, -rtg1_l / 2, rtg1_d, rtg1_w, rtg1_l);
    MbSolid* pBlock3 = NULL;
    ::ElementarySolid(CardPointB, et_Block, elNames, pBlock3);

    //Вырезаем из pBlock3 pBlock1 и pBlock2
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbBooleanFlags flagsBool;
    MbResultType res1;

    res1 = ::BooleanResult(*pBlock3, cm_Copy, *pBlock1, cm_Copy, bo_Difference, flagsBool, operBoolNames, pBlock3);
    res1 = ::BooleanResult(*pBlock3, cm_Copy, *pBlock2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pBlock3);

    ::DeleteItem(pBlock1);
    ::DeleteItem(pBlock2);

    //pBlock4
    CreateBlock(CardPointB, rtg1_d - rtg3_l - rtg3_ind, rtg1_w / 2, -rtg3_w / 2, rtg3_l, rtg3_th, rtg3_w);
    MbSolid* pBlock4 = NULL;
    ::ElementarySolid(CardPointB, et_Block, elNames, pBlock4);

    //Скругление pBlock4
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params1;

    params1.distance1 = rtg3_w / 2; //радиус скругления == 1/2 ширины паза
    params1.distance2 = rtg3_w / 2; //радиус скругления == 1/2 ширины паза
    params1.form = st_Fillet;
    params1.smoothCorner = SmoothValues::ec_uniform;
    RPArray<MbFace> initBounds(0, 1);
    RPArray<MbCurveEdge> initCurves(4, 4);
    initCurves.Add(pBlock4->GetEdge(2)); //8 ребро - радиус
    initCurves.Add(pBlock4->GetEdge(5));
    initCurves.Add(pBlock4->GetEdge(7));
    initCurves.Add(pBlock4->GetEdge(0));

    MbResultType res2 = ::FilletSolid(*pBlock4, cm_Copy, initCurves, initBounds, params1, filletNames, pBlock4);

    //pCylinder1
    CreateCylinder(CardPointC, cln1_ix, -cln1_iy + rtg1_w / 2, -(rtg1_l / 2) + rtg1_th1, 0, -cln1_D / 2, 0, 0, cln1_d);
    MbSolid* pCylinder1 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder1);

    //pCylinder2
    CreateCylinder(CardPointC, cln1_ix, -cln1_iy + rtg1_w / 2, -rtg1_l / 2, 0, -cln2_D / 2, 0, 0, rtg1_l / 2);
    MbSolid* pCylinder2 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder2);

    //тело непонятной формы
    MbPlacement3D pl;
    pl.Move(MbVector3D(0, 0, -rtg1_l / 2));

    SArray<MbCartPoint> arrPnts(7);
    arrPnts.Add(MbCartPoint(er_l1, -rtg1_w / 2)); //p0
    arrPnts.Add(MbCartPoint(er_l1, -rtg1_w / 2 - er_w1)); //p1
    arrPnts.Add(MbCartPoint(er_l1 + er_l3, -rtg1_w / 2 - er_w1 - er_l3)); //p2
    arrPnts.Add(MbCartPoint(er_l1 + er_l4, -rtg1_w / 2 - er_w1 - er_l3)); //p3
    arrPnts.Add(MbCartPoint(er_l1 + er_l4, -rtg1_w / 2)); //p4
    arrPnts.Add(MbCartPoint(rtg1_d + er_l5, -rtg1_w / 2)); //p5
    arrPnts.Add(MbCartPoint(rtg1_d, -er_w2 + rtg1_w / 2)); //p6

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContour = new MbContour(*pPolyline, true);
    MbSweptData sweptData(pl, *pContour);
    MbVector3D dir(0, 0, 1);

    ExtrusionValues extrusionParams(er_th, 0.0);
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    MbSolid* pSolid1 = nullptr;
    MbResultType res3 = ::ExtrusionSolid(sweptData, dir, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolid1);

    //Объединяем pSolid1, pCylinder1
    MbSolid* pSolid2 = NULL;
    MbSNameMaker operUnionNames(ct_UnionSolid, MbSNameMaker::i_SideNone, 0);
    bool checkIntersection = true; bool isArray = false;
    RPArray<MbSolid> solids;
    solids.Add(pSolid1);
    solids.Add(pCylinder1);
    MbResultType resUnion = ::UnionSolid(solids, cm_Same, checkIntersection, operUnionNames, isArray, pSolid2);

    //Вырезаем из pSolid2 pCylinder2
    MbResultType res4 = ::BooleanResult(*pSolid2, cm_Copy, *pCylinder2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid2);

    ::DeleteItem(pSolid1);
    ::DeleteItem(pCylinder1);
    ::DeleteItem(pCylinder2);

    //Скругление тела pSolid2
    params1.distance1 = cln1_fl;
    params1.distance2 = cln2_fl;

    initCurves.RemoveInd(0);
    initCurves.RemoveInd(1);
    initCurves.RemoveInd(2);
    initCurves.RemoveInd(3);
    initCurves.Add(pSolid2->GetEdge(25)); //25 ребро - радиус 3
    initCurves.Add(pSolid2->GetEdge(8)); //8 ребро - радиус 5

    MbResultType res5 = ::FilletSolid(*pSolid2, cm_Copy, initCurves, initBounds, params1, filletNames, pSolid2);

    //Фаска pSolid2
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params2;
    params2.distance1 = er_ch;
    params2.distance2 = er_ch;
    params2.form = st_Chamfer;
    params2.smoothCorner = SmoothValues::ec_uniform;

    initCurves.RemoveInd(0);
    initCurves.RemoveInd(1);
    initCurves.Add(pSolid2->GetEdge(19)); // 19 ребро - фаска 5
    MbResultType res6 = ::ChamferSolid(*pSolid2, cm_Copy, initCurves, params2, chamferNames, pSolid2);

    //Зеркально отражаем pSolid2
    MbPlacement3D plSym;
    MbSolid* pSolidCopy = NULL;
    MbSNameMaker symNames(ct_SymmetrySolid);
    MbResultType resSolidCopy = ::MirrorSolid(*pSolid2, plSym, symNames, pSolidCopy);

    //Объединяем pSolid2, pSolidCopy, pBlock3, pBlock4
    MbSolid* pUnionSolid = NULL;
    solids.RemoveInd(0);
    solids.RemoveInd(1);
    solids.Add(pSolid2);
    solids.Add(pSolidCopy);
    solids.Add(pBlock3);
    solids.Add(pBlock4);
    resUnion = ::UnionSolid(solids, cm_Same, checkIntersection, operUnionNames, isArray, pUnionSolid);

    ::DeleteItem(pSolid2);
    ::DeleteItem(pSolidCopy);
    ::DeleteItem(pBlock3);
    ::DeleteItem(pBlock4);

    ///Создаем 4 отверстия
    CreateCylinder(CardPointC, cln3_dist, rtg1_w / 2 + rtg3_th, 0,
        -rtg1_th2, -cln3_D / 2, 0, 0, 0); //pCylinder3
    MbSolid* pCylinder3 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder3);

    CreateCylinder(CardPointC, cln3_dist + cln3_btw, rtg1_w / 2 + rtg3_th, 0,
        -rtg1_th2, -cln3_D / 2, 0, 0, 0); //pCylinder4
    MbSolid* pCylinder4 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder4);

    CreateCylinder(CardPointC, cln3_dist + cln3_btw * 2, rtg1_w / 2 + rtg3_th, 0,
        -rtg1_th2, -cln3_D / 2, 0, 0, 0); //pCylinder5
    MbSolid* pCylinder5 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder5);

    CreateCylinder(CardPointC, rtg1_d, rtg1_w / 2 - cln6_dist, 0, 0, 0, -rtg1_d, cln6_D / 2, 0); //pCylinder6
    MbSolid* pCylinder6 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder6);

    //Вырезаем 4 отверстия из основного тела
    MbResultType res7;
    res7 = ::BooleanResult(*pUnionSolid, cm_Copy, *pCylinder3, cm_Copy,
        bo_Difference, flagsBool, operBoolNames, pUnionSolid);
    res7 = ::BooleanResult(*pUnionSolid, cm_Copy, *pCylinder4, cm_Copy,
        bo_Difference, flagsBool, operBoolNames, pUnionSolid);
    res7 = ::BooleanResult(*pUnionSolid, cm_Copy, *pCylinder5, cm_Copy,
        bo_Difference, flagsBool, operBoolNames, pUnionSolid);
    res7 = ::BooleanResult(*pUnionSolid, cm_Copy, *pCylinder6, cm_Copy,
        bo_Difference, flagsBool, operBoolNames, pUnionSolid);

    ::DeleteItem(pCylinder3);
    ::DeleteItem(pCylinder4);
    ::DeleteItem(pCylinder5);
    ::DeleteItem(pCylinder6);

    //5 отверстие и тело его копий
    CreateCylinder(CardPointC, cln7_indx, -rtg1_w / 2, rtg1_l / 2 - (rtg1_l - cln7_distz) / 2,
        cln7_d, -cln7_D / 2, 0, 0, 0); //pCylinder7
    MbSolid* pCylinder7 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder7);

    MbVector3D vecDir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0));
    MbVector3D vecDir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -1));
    MbCartPoint3D l(15, -35, (39 + 4));
    // Шаг копирования по двум осям
    const double step1 = cln7_distx; const double step2 = cln7_distz;
    // Количество копий по двум направлениям
    const unsigned int num1 = cln7_kx; const unsigned int num2 = cln7_kz;
    DuplicationMeshValues params(false, vecDir1, step1, num1, vecDir2, step2, num2, &l);

    MbSolid* pDuplSolid = NULL;
    MbSolid* pUnionSolid2 = NULL;
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    MbResultType res8 = ::DuplicationSolid(*pCylinder7, params, namesDupl, pDuplSolid);
    res8 = ::BooleanResult(*pUnionSolid, cm_Copy, *pDuplSolid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pUnionSolid2);

    ::DeleteItem(pUnionSolid);
    ::DeleteItem(pCylinder7);
    ::DeleteItem(pDuplSolid);

    //6 отверстие и тело его копий
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    CreateCylinder(CardPointC, 337, -98, 0, 0, -(11.5 / 2), 0, 0, 53 * 4); //SolidsC[7]
    MbSolid* pCylinder8 = NULL;

    MbSolid* pDuplSolid2 = NULL;
    MbSolid* pUnionSolid3 = NULL;
    ::ElementarySolid(CardPointC, et_Cylinder, elNames, pCylinder8);

    MbVector3D vecDir12(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 1, 0));
    MbVector3D vecDir22(MbCartPoint3D(0, 0, 0), MbCartPoint3D(-1, 0, 0));
    MbCartPoint3D l2(337, -98, -53);

    const double step12 = cln8_disty; const double step22 = cln8_distx;
    const unsigned int num12 = cln8_ky; const unsigned int num22 = cln8_kx;
    DuplicationMeshValues params22(false, vecDir12, step12, num12, vecDir22, step22, num22, &l2);

    res8 = ::DuplicationSolid(*pCylinder8, params22, namesDupl, pDuplSolid2);
    MbResultType res9 = ::BooleanResult(*pUnionSolid2, cm_Copy, *pDuplSolid2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pUnionSolid3);


    SolidSPtr MainSolid(pUnionSolid3);

    return MainSolid;
}