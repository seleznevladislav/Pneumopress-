#include "BuildMathModel.h"

using namespace BuildMathModel;


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_006()
{
    // Множитель для преобразования угловых значений из градусов в радианы
    const double DEG_TO_RAD = M_PI / 180.0;

    //Создание двумерные точки на осях X и Y
    MbCartPoint p1(0, 7);
    MbCartPoint p2(0, 13);
    MbCartPoint p3(8, 13);
    MbCartPoint p4(8, 7);

    //Динамическое создание объектов отрезков
    MbLineSegment* Seg1 = new MbLineSegment(p1, p2);
    MbLineSegment* Seg2 = new MbLineSegment(p2, p3);
    MbLineSegment* Seg3 = new MbLineSegment(p3, p4);
    MbLineSegment* Seg4 = new MbLineSegment(p4, p1);

    //Динамическое создание контура
    MbContour* ptrContour = new MbContour();
    //Добавление в контур сегментов
    ptrContour->AddSegment(Seg1);
    ptrContour->AddSegment(Seg2);
    ptrContour->AddSegment(Seg3);
    ptrContour->AddSegment(Seg4);

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