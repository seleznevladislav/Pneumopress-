#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void ParametricModelCreator::CreateSealHousing(MbAssembly* pAsm, double ratio)
{
	// Множитель для преобразования угловых значений из градусов в радианы
	const double DEG_TO_RAD = M_PI / 180.0;

	//Создание двумерные точки на осях X и Y
	MbCartPoint p1(7.25 + 8.75, 7 * ratio);
	MbCartPoint p2(7.75 + 8.75, 7.5 * ratio);
	MbCartPoint p3(7.75 + 8.75, 17.5 * ratio);
	MbCartPoint p4(8.75 + 8.75, 17.5 * ratio);

	MbCartPoint p5(8.75 + 8.75, 23.975 * ratio);
	MbCartPoint p6(7.75 + 8.75, 24.875 * ratio);
	MbCartPoint p7(6.85 + 8.75, 24.875 * ratio);
	MbCartPoint p8(6.85 + 8.75, 20.995 * ratio);
	MbCartPoint p9(3.25 + 8.75, 20.995 * ratio);
	MbCartPoint p10(3.25 + 8.75, 24.875 * ratio);
	MbCartPoint p11(2.25 + 8.75, 24.875 * ratio);
	MbCartPoint p12(2.25 + 8.75, 22.495 * ratio);

	MbCartPoint p13(-2.25 + 8.75, 22.495 * ratio);
	MbCartPoint p14(-2.25 + 8.75, 24.875 * ratio);
	MbCartPoint p15(-3.25 + 8.75, 24.875 * ratio);
	MbCartPoint p16(-3.25 + 8.75, 20.995 * ratio);
	MbCartPoint p17(-6.85 + 8.75, 20.995 * ratio);
	MbCartPoint p18(-6.85 + 8.75, 24.875 * ratio);
	MbCartPoint p19(-7.75 + 8.75, 24.875 * ratio);
	MbCartPoint p20(-8.75 + 8.75, 23.975 * ratio);

	MbCartPoint p21(-8.75 + 8.75, 17.5 * ratio);
	MbCartPoint p22(-7.75 + 8.75, 17.5 * ratio);
	MbCartPoint p23(-7.75 + 8.75, 7.5 * ratio);
	MbCartPoint p24(-7.25 + 8.75, 7 * ratio);

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
	MbLineSegment* Seg18 = new MbLineSegment(p18, p19);
	MbLineSegment* Seg19 = new MbLineSegment(p19, p20);
	MbLineSegment* Seg20 = new MbLineSegment(p20, p21);
	MbLineSegment* Seg21 = new MbLineSegment(p21, p22);
	MbLineSegment* Seg22 = new MbLineSegment(p22, p23);
	MbLineSegment* Seg23 = new MbLineSegment(p23, p24);
	MbLineSegment* Seg24 = new MbLineSegment(p24, p1);

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
	ptrContour->AddSegment(Seg19);
	ptrContour->AddSegment(Seg20);
	ptrContour->AddSegment(Seg21);
	ptrContour->AddSegment(Seg22);
	ptrContour->AddSegment(Seg23);
	ptrContour->AddSegment(Seg24);

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

	MbAxis3D axVert(MbVector3D(0, 1, 0));
	// отображение построенного тела
	if (m_bResult == rt_Success)
		m_pResSolid->Rotate(axVert, M_PI / 2);
	m_pResSolid->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -5)));

	m_pResSolid->SetColor(RGB(8, 8, 6));
	pAsm->AddItem(*m_pResSolid);
	//viewManager->AddObject(Style(1, BLACK), m_pResSolid);

	for (auto item : *ptrContours) {
		::DeleteItem(item);
	}
	::DeleteMatItem(pCurves);
	::DeleteMatItem(ptrContours);
	::DeleteMatItem(place);

	//::DeleteItem(ptrSurface);
	//::DeleteItem(ptrContour);
	//::DeleteItem(Seg1);
	//::DeleteItem(Seg2);
	//::DeleteItem(Seg3);
	
}