#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_007()
{
    // Множитель для преобразования угловых значений из градусов в радианы
    const double DEG_TO_RAD = M_PI / 180.0;

    //Создание двумерные точки на осях X и Y
    MbCartPoint p1(0, 14);
    MbCartPoint p2(0, 20);
    MbCartPoint p3(8, 20);
    MbCartPoint p4(8, 17);
    MbCartPoint p5(12, 17);
    MbCartPoint p6(12, 20);
    MbCartPoint p7(20, 20);
    MbCartPoint p8(20, 18);
    MbCartPoint p9(40, 18);
    MbCartPoint p10(40, 14);
    MbCartPoint p11(38, 14);
    MbCartPoint p12(38, 15.1);
    MbCartPoint p13(34.5, 15.1);
    MbCartPoint p14(34.5, 14);
    MbCartPoint p15(6, 14);
    MbCartPoint p16(6, 15.6);
    MbCartPoint p17(2, 15.6);
    MbCartPoint p18(2, 14);

    //Динамическое создание объектов отрезков
    MbLineSegment* Seg1 = new MbLineSegment(p1, p2);
    MbLineSegment* Seg2 = new MbLineSegment(p2, p3);
    MbLineSegment* Seg3 = new MbLineSegment(p3, p4);
    MbLineSegment* Seg4 = new MbLineSegment(p4, p5);
    MbLineSegment* Seg5 = new MbLineSegment(p5, p6);
    MbLineSegment* Seg6 = new MbLineSegment(p6, p7);
    MbLineSegment* Seg7 = new MbLineSegment(p7, p8);
    MbLineSegment* Seg8 = new MbLineSegment(p8, p9);
    MbLineSegment* Seg9 = new MbLineSegment(p9, p10);
    MbLineSegment* Seg10 = new MbLineSegment(p10, p11);
    MbLineSegment* Seg11 = new MbLineSegment(p11, p12);
    MbLineSegment* Seg12 = new MbLineSegment(p12, p13);
    MbLineSegment* Seg13 = new MbLineSegment(p13, p14);
    MbLineSegment* Seg14 = new MbLineSegment(p14, p15);
    MbLineSegment* Seg15 = new MbLineSegment(p15, p16);
    MbLineSegment* Seg16 = new MbLineSegment(p16, p17);
    MbLineSegment* Seg17 = new MbLineSegment(p17, p18);
    MbLineSegment* Seg18 = new MbLineSegment(p18, p1);

    //Динамическое создание контура
    MbContour* ptrContour = new MbContour();
    //Добавление в контур сегментов
    ptrContour->AddSegment(Seg1);
    ptrContour->AddSegment(Seg2);
    ptrContour->AddSegment(Seg3);
    ptrContour->AddSegment(Seg4);
    ptrContour->AddSegment(Seg5);
    ptrContour->AddSegment(Seg6);
    ptrContour->AddSegment(Seg7);
    ptrContour->AddSegment(Seg8);
    ptrContour->AddSegment(Seg9);
    ptrContour->AddSegment(Seg10);
    ptrContour->AddSegment(Seg11);
    ptrContour->AddSegment(Seg12);
    ptrContour->AddSegment(Seg13);
    ptrContour->AddSegment(Seg14);
    ptrContour->AddSegment(Seg15);
    ptrContour->AddSegment(Seg16);
    ptrContour->AddSegment(Seg17);
    ptrContour->AddSegment(Seg18);

    // Создание плоскости - она совпадает с плоскостью XY локальной СК
    MbPlacement3D* place = new MbPlacement3D();
    MbPlane* ptrSurface = new MbPlane(*place);

    //Создание образующей для тела вращения
    RPArray<MbContour>* ptrContours = new RPArray<MbContour>();
    ptrContours->Add(ptrContour);

    //объект, в котором хранятся сведения об образующей
    MbSweptData* pCurves;
    pCurves = new MbSweptData(*ptrSurface, *ptrContours);

    // Объект параметров для построения тел вращения.
    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    //Именователи для операции построения тела вращения и для контуров образующей
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    //Ось вращения для построения тела
    MbAxis3D axis(place->GetAxisX());

    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* m_pResSolid = nullptr;
    MbResultType m_bResult = RevolutionSolid(*pCurves, axis, revParms, operNames, cNames, m_pResSolid);



    SolidSPtr MainSolid(m_pResSolid);
    return MainSolid;
}