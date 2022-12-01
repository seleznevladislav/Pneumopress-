#include "BuildMathModel.h"

#include <action_solid.h> 
#include "cur_polyline.h" 
#include "surf_plane.h"


using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateBlock(SArray<MbSolid*>& _SolidsB, float x, float y, float z, float x1, float y1, float z1)
{
    SArray<MbCartPoint3D> _alCardPoint(4);
    _alCardPoint.Add(MbCartPoint3D(x, y, z));
    _alCardPoint.Add(MbCartPoint3D(x + x1, y, z));
    _alCardPoint.Add(MbCartPoint3D(x, y + y1, z));
    _alCardPoint.Add(MbCartPoint3D(x, y, z + z1));

    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);
    MbSolid* pBlock = NULL;
    ::ElementarySolid(_alCardPoint, et_Block, elNames, pBlock);
    _SolidsB.push_back(pBlock);
}

void CreateCylinder(SArray<MbSolid*>& _SolidsC, float x, float y, float z, float y1, float x1, float x2, float y2, float z1)
{
    SArray<MbCartPoint3D> _alCardPoint(3);
    _alCardPoint.Add(MbCartPoint3D(x, y, z));
    _alCardPoint.Add(MbCartPoint3D(x + x2, y + y1, z + z1));
    _alCardPoint.Add(MbCartPoint3D(x + x1, y + y2, z));

    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);
    MbSolid* pCylinder = NULL;
    ::ElementarySolid(_alCardPoint, et_Cylinder, elNames, pCylinder);
    _SolidsC.push_back(pCylinder);
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

    SArray<MbSolid*> SolidsB;
    SArray<MbSolid*> SolidsC;

    //Создаем 3 блока
    CreateBlock(SolidsB, rtg2_l, (-rtg1_w + rtg1_th1 * 2) * 2, -(rtg1_w + rtg1_th2 - rtg1_th1) / 2,
        rtg2_w, 5 * (rtg1_w - rtg1_th1 * 2) / 2, rtg1_w + (rtg1_th2 - rtg1_th1));//SolidsB[0]

    CreateBlock(SolidsB, -rtg1_d + rtg1_th3, -(rtg1_w - rtg1_th1 * 2) / 2, -(rtg1_w + rtg3_th) / 2,
        rtg1_d * 2 - rtg1_th3 * 2, rtg1_w - rtg1_th1 * 2, rtg1_w + rtg3_th); //SolidsB[1]

    CreateBlock(SolidsB, 0, -rtg1_w / 2, -rtg1_l / 2, rtg1_d, rtg1_w, rtg1_l);//SolidsB[2]

    //Вырезаем из SolidsB[2] SolidsB[0] и SolidsB[1]
    MbSolid* pSolid = NULL;
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbBooleanFlags flagsBool;

    for (int i = 0; i < 2; i++)
    {
        ::BooleanResult(*SolidsB[2], cm_Copy, *SolidsB[i], cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);
        SolidsB.RemoveInd(2);
        SolidsB.AddAt(pSolid, 2);
    }

    //SolidsB[3]
    CreateBlock(SolidsB, rtg1_d - rtg3_l - rtg3_ind, rtg1_w / 2, -rtg3_w / 2, rtg3_l, rtg3_th, rtg3_w);

    //Скругление SolidsB[3]
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params1;

    params1.distance1 = rtg3_w / 2; //радиус скругления == 1/2 ширины паза
    params1.distance2 = rtg3_w / 2; //радиус скругления == 1/2 ширины паза
    params1.form = st_Fillet;
    params1.smoothCorner = SmoothValues::ec_uniform;
    RPArray<MbFace> initBounds(0, 1);
    RPArray<MbCurveEdge> initCurves(4, 4);
    initCurves.Add(SolidsB[3]->GetEdge(2)); //8 ребро - радиус
    initCurves.Add(SolidsB[3]->GetEdge(5));
    initCurves.Add(SolidsB[3]->GetEdge(7));
    initCurves.Add(SolidsB[3]->GetEdge(0));

    ::FilletSolid(*SolidsB[3], cm_Copy, initCurves, initBounds, params1, filletNames, SolidsB[3]);


    //SolidsC[0]
    CreateCylinder(SolidsC, cln1_ix, -cln1_iy + rtg1_w / 2, -(rtg1_l / 2) + rtg1_th1, 0, -cln1_D / 2, 0, 0, cln1_d);
    //SolidsC[1]
    CreateCylinder(SolidsC, cln1_ix, -cln1_iy + rtg1_w / 2, -rtg1_l / 2, 0, -cln2_D / 2, 0, 0, rtg1_l / 2);

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

    MbSolid* pSolid2 = nullptr;
    ::ExtrusionSolid(sweptData, dir, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolid2);

    //Объединяем pSolid2, SolidsC[0]
    MbSolid* pUnionSolid = NULL;
    MbSNameMaker operUnionNames(ct_UnionSolid, MbSNameMaker::i_SideNone, 0);
    bool checkIntersection = true; bool isArray = false;
    RPArray<MbSolid> solids;
    solids.Add(pSolid2);
    solids.Add(SolidsC[0]);
    ::UnionSolid(solids, cm_Same, checkIntersection, operUnionNames, isArray, pUnionSolid);

    //Вырезаем из pUnionSolid SolidsC[1]
    MbSolid* pSolid3 = NULL;
    ::BooleanResult(*pUnionSolid, cm_Copy, *SolidsC[1], cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid3);

    //Скругление тела pSolid3
    params1.distance1 = cln1_fl;
    params1.distance2 = cln2_fl;

    RPArray<MbCurveEdge> allEdges(3, 1);
    RPArray<MbFace> initBounds2(0, 1);
    RPArray<MbCurveEdge> initCurves2(3, 1);

    initCurves2.Add(pSolid3->GetEdge(25)); //25 ребро - радиус 3
    initCurves2.Add(pSolid3->GetEdge(8)); //8 ребро - радиус 5

    ::FilletSolid(*pSolid3, cm_Copy, initCurves2, initBounds2, params1, filletNames, pSolid3);

    //Фаска pSolid3 
    MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    SmoothValues params2;
    params2.distance1 = er_ch;
    params2.distance2 = er_ch;
    params2.form = st_Chamfer;
    params2.smoothCorner = SmoothValues::ec_uniform;

    initCurves.RemoveInd(0);
    initCurves.RemoveInd(1);
    initCurves.Add(pSolid3->GetEdge(19)); // 19 ребро - фаска 5
    ::ChamferSolid(*pSolid3, cm_Copy, initCurves, params2, chamferNames, pSolid3);

    //Зеркально отражаем pSolid3
    MbPlacement3D plSym;
    MbSolid* pSolidCopy = NULL;
    MbSNameMaker symNames(ct_SymmetrySolid);
    ::MirrorSolid(*pSolid3, plSym, symNames, pSolidCopy);


    //Объединяем pSolid3, pSolidCopy, pSolid, SolidsB[3]
    RPArray<MbSolid> solids2;
    solids2.Add(pSolid3);
    solids2.Add(pSolidCopy);
    solids2.Add(pSolid);
    solids2.Add(SolidsB[3]);
    ::UnionSolid(solids2, cm_Same, checkIntersection, operUnionNames, isArray, pUnionSolid);

    ///Создаем 4 отверстия
    CreateCylinder(SolidsC, cln3_dist, rtg1_w / 2 + rtg3_th, 0,
        -rtg1_th2, -cln3_D / 2, 0, 0, 0); //SolidsC[2]
    CreateCylinder(SolidsC, cln3_dist + cln3_btw, rtg1_w / 2 + rtg3_th, 0,
        -rtg1_th2, -cln3_D / 2, 0, 0, 0); //SolidsC[3]
    CreateCylinder(SolidsC, cln3_dist + cln3_btw * 2, rtg1_w / 2 + rtg3_th, 0,
        -rtg1_th2, -cln3_D / 2, 0, 0, 0); //SolidsC[4]

    CreateCylinder(SolidsC, rtg1_d, rtg1_w / 2 - cln6_dist, 0, 0, 0, -rtg1_d, cln6_D / 2, 0); //SolidsC[5]

    //Вырезаем 4 отверстия из основного тела
    for (int i = 2; i < 6; i++)
    {
        ::BooleanResult(*pUnionSolid, cm_Copy, *SolidsC[i], cm_Copy,
            bo_Difference, flagsBool, operBoolNames, pUnionSolid);
    }


    //5 отверстие и тело его копий
    CreateCylinder(SolidsC, cln7_indx, -rtg1_w / 2, rtg1_l / 2 - (rtg1_l - cln7_distz) / 2,
        cln7_d, -cln7_D / 2, 0, 0, 0); //SolidsC[6]

    MbVector3D vecDir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0));
    MbVector3D vecDir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -1));

    MbCartPoint3D l(15, -35, (39 + 4));

    // Шаг копирования по двум осям

    const double step1 = cln7_distx; const double step2 = cln7_distz;

    // Количество копий по двум направлениям

    const unsigned int num1 = cln7_kx; const unsigned int num2 = cln7_kz;
    DuplicationMeshValues params(false, vecDir1, step1, num1, vecDir2, step2, num2, &l);

    MbSolid* pDuplSolid = NULL;
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);

    ::DuplicationSolid(*SolidsC[6], params, namesDupl, pDuplSolid);
    ::BooleanResult(*pUnionSolid, cm_Copy, *pDuplSolid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pUnionSolid);

    //6 отверстие и тело его копий
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    CreateCylinder(SolidsC, 337, -98, 0, 0, -(11.5 / 2), 0, 0, 53 * 4); //SolidsC[7]

    MbVector3D vecDir12(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 1, 0));
    MbVector3D vecDir22(MbCartPoint3D(0, 0, 0), MbCartPoint3D(-1, 0, 0));
    MbCartPoint3D l2(337, -98, -53);

    const double step12 = cln8_disty; const double step22 = cln8_distx;
    const unsigned int num12 = cln8_ky; const unsigned int num22 = cln8_kx;

    DuplicationMeshValues params22(false, vecDir12, step12, num12, vecDir22, step22, num22, &l2);

    ::DuplicationSolid(*SolidsC[7], params22, namesDupl, pDuplSolid);
    ::BooleanResult(*pUnionSolid, cm_Copy, *pDuplSolid, cm_Copy, bo_Difference, flagsBool, operBoolNames, pUnionSolid);

    SolidSPtr MainSolid(pUnionSolid);

    ::DeleteItem(pUnionSolid);
    ::DeleteItem(SolidsC[0]);
    ::DeleteItem(SolidsC[1]);
    ::DeleteItem(SolidsC[2]);
    ::DeleteItem(SolidsC[3]);
    ::DeleteItem(SolidsC[4]);
    ::DeleteItem(SolidsC[5]);
    ::DeleteItem(SolidsC[6]);
    ::DeleteItem(SolidsC[7]);
    ::DeleteItem(pDuplSolid);
    ::DeleteItem(pSolid2);
    ::DeleteItem(SolidsB[1]);
    ::DeleteItem(SolidsB[2]);
    ::DeleteItem(SolidsB[0]);
    ::DeleteItem(pSolid3);
    ::DeleteItem(pSolidCopy);

    return MainSolid;

}