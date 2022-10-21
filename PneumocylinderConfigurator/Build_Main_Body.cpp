#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

double calcCircle(double rad, double otherCord) {
	double r2 = std::pow(rad, 2);
	double p2 = std::pow(otherCord, 2);
	return std::sqrt(r2 - p2);
}

//Функция принимает параметром diamIn - Внутренний диаметр отверстия под вал param
void baseSketch(RPArray<MbContour>* ptrContours, double diamIn = 50) {
	//params std 
	//Стандартный внутренний диаметр
	const double diamIn_STD = 50;
	const double thickness = 3;
	//calculate offsets
	//Разница стандартного и заданного диаметров
	double diamOffset = diamIn - diamIn_STD;
	//Соотношение стандартного и заданного диаметров
	double diamDifRatio = diamIn / diamIn_STD;

	//params std 
	//Стандартная ширина по X, между двумя прямыми боковыми гранями
	const double widthX_STD = 64.5;
	//Стандартная ширина по X выреза в верхней и нижней гранях
	const double widthXIn_STD = 40;
	//Стандартная высота по Y от верхней до нижней грани
	const double heightY_STD = 61;

	//calculate model dimensions 
	//Рассчитанная ширина по X, между двумя прямыми боковыми гранями
	double widthX = widthX_STD + diamOffset;
	//Рассчитанная ширина по X выреза в верхней и нижней гранях
	double widthXIn = widthXIn_STD + ((diamOffset < 0) ? (diamOffset - (1.5 * thickness * (1 / diamDifRatio - 1))) : (diamOffset / (widthX_STD / widthXIn_STD)));
	//Рассчитанная высота по Y от верхней до нижней грани
	double heightY = heightY_STD + diamOffset;

	//Соотношения рассчитанных величин к стандартным
	double widthXDifRatio = widthX / widthX_STD;
	double widthXInDifRatio = widthXIn / widthXIn_STD;
	double heightYDifRatio = heightY / heightY_STD;

	// Параметры модели : diamIn=50, widthX=64.5, widthXIn=40, heightY=61

	////////////

	// Координаты точек нумеруются от самой маленькой до самой большой по своей оси
	// Координаты собраны для упрощения построения эскиза из четырех симметричных частей
	// В след строчке пример как считался коэффициент
	// 40(widthXIn) / 16.489(old val of x1 and p0.x) = 2.425(widthXIn ratio to x1)
	double x1 = widthXIn / 2.425, x2 = widthXIn / 2, x3 = widthX / 2;
	double y1 = heightY / 2.695, y2 = heightY / 2;

	MbCartPoint p0(x1/*16.489*/, y1/*22,63*/);
	//showPoint(p0, BLACK);
	MbCartPoint p1(x2/*20*/, y2 /*30.5*/);
	//showPoint(p1, BLACK);
	MbCartPoint p2(x3/*32.25*/, y2);
	//showPoint(p2, BLACK);
	MbCartPoint p3(x3, -y2);
	//showPoint(p3, BLACK);
	MbCartPoint p4(x2, -y2);
	MbCartPoint p5(x1, -y1);
	MbCartPoint p6(0, -y1);
	MbCartPoint p7(-x1, -y1);
	MbCartPoint p8(-x2, -y2);
	MbCartPoint p9(-x3, -y2);
	MbCartPoint p10(-x3, y2);
	MbCartPoint p11(-x2, y2);
	MbCartPoint p12(-x1, y1);
	MbCartPoint p13(0, y1);

	MbLineSegment* Seg1 = new MbLineSegment(p0, p1);
	MbLineSegment* Seg2 = new MbLineSegment(p1, p2);
	MbLineSegment* Seg3 = new MbLineSegment(p2, p3);
	MbLineSegment* Seg4 = new MbLineSegment(p3, p4);
	MbLineSegment* Seg5 = new MbLineSegment(p4, p5);
	MbLineSegment* Seg6 = new MbLineSegment(p5, p6);
	MbLineSegment* Seg7 = new MbLineSegment(p6, p7);
	MbLineSegment* Seg8 = new MbLineSegment(p7, p8);
	MbLineSegment* Seg9 = new MbLineSegment(p8, p9);
	MbLineSegment* Seg10 = new MbLineSegment(p9, p10);
	MbLineSegment* Seg11 = new MbLineSegment(p10, p11);
	MbLineSegment* Seg12 = new MbLineSegment(p11, p12);
	MbLineSegment* Seg13 = new MbLineSegment(p12, p13);
	MbLineSegment* Seg14 = new MbLineSegment(p13, p0);

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

	MbContour* pFillets = NULL;
	// здесь радиусы скруглений множатся на соотношение изменения ширины
	// численный константный коэффициент 1.76*1.6 подбирался почти методом тыка
	::FilletPolyContour(ptrContour, 9 * widthXDifRatio, false, p3, pFillets);
	::FilletPolyContour(ptrContour, 9 * widthXDifRatio, false, p9, pFillets);
	::FilletPolyContour(ptrContour, 9 * widthXInDifRatio, false, p10, pFillets);
	::FilletPolyContour(ptrContour, 9 * widthXInDifRatio, false, p2, pFillets);

	ptrContours->Add(ptrContour);
}

void baseSideHoleSketch(RPArray<MbContour>* ptrContours, double diamIn = 50, bool xInvert = false, bool yInvert = false) {
	//params std 
	//Стандартный внутренний диаметр
	const double diamIn_STD = 50;

	const double thickness = 3;

	//calculate offsets
	//Разница стандартного и заданного диаметров
	double diamOffset = diamIn - diamIn_STD;
	//Соотношение стандартного и заданного диаметров
	double diamDifRatio = diamIn / diamIn_STD;

	//params std 
	//Стандартная ширина по X, между двумя прямыми боковыми гранями
	const double widthX_STD = 64.5;
	//Стандартная ширина по X выреза в верхней и нижней гранях
	const double widthXIn_STD = 40;
	//Стандартная высота по Y от верхней до нижней грани
	const double heightY_STD = 61;

	//calculate model dimensions 
	//Рассчитанная ширина по X, между двумя прямыми боковыми гранями
	double widthX = widthX_STD + diamOffset;
	//Рассчитанная ширина по X выреза в верхней и нижней гранях
	double widthXIn = widthXIn_STD + ((diamOffset < 0) ? (diamOffset) : (diamOffset / (widthX_STD / widthXIn_STD)));
	//Рассчитанная высота по Y от верхней до нижней грани
	double heightY = heightY_STD + diamOffset;

	//Соотношения рассчитанных величин к стандартным
	double widthXDifRatio = widthX / widthX_STD;
	double widthXInDifRatio = widthXIn / widthXIn_STD;
	double heightYDifRatio = heightY / heightY_STD;
	/////////////////////////////////////////////////////////Sketch3 

// Параметры модели : diamIn=50, widthX=64.5, widthXIn=40, heightY=61

	//double x01 = widthXIn / 2.425, x02 = widthXIn / 2, x03 = widthX / 2;
	//double y01 = heightY / 2.695, y02 = heightY / 2, y03 = y01/*heightY/1.76*/;

	// 40(widthXIn) / 18.37(old val of x1 and p0.x) = 2.177(widthXIn ratio to x1)
	double x1 = widthXIn / 2.177, x2 = widthXIn / 1.88, x3 = widthX / 2.41, x4 = widthX / 2;
	double y1 = heightY / 21.44, y2 = heightY / 4.399, y3 = heightY / 2.877, y4 = heightY / 2.17;

	double outRad = (diamIn / 2) + thickness;

	x4 = ((outRad)+(((diamIn / 2) + (widthX / 2)) / 2)) / 2;
	if (x4 > (outRad))x4 = outRad;
	if (x3 > (outRad - 1))x3 = outRad - 1;

	y1 = calcCircle(outRad, x4);
	y2 = calcCircle(outRad, x3);


	//y3 = (y3 + calcCircle(outRad, x1)) / 2;
	//x1 = (x1 + calcCircle(outRad, y3)) / 2;
	y3 = calcCircle(outRad, x1);

	double x5 = (widthX / 2) - (thickness);

	x2 = widthXIn / 2 + thickness * diamDifRatio / 3;

	y4 = ((heightY / 2 - thickness) + (outRad)) / 2;

	if (xInvert) {
		x1 *= -1; x2 *= -1; x3 *= -1; x4 *= -1; x5 *= -1;
	};
	if (yInvert) {
		y1 *= -1; y2 *= -1; y3 *= -1; y4 *= -1;
	};

	MbCartPoint p14(x1, y3);
	//showPoint(p14, LIGHTRED);
	MbCartPoint p15(x2, y4);
	//showPoint(p15, YELLOW);
	MbCartPoint p16(x5, y4);
	//showPoint(p16, GOLDEN);
	MbCartPoint p17(x5, y2);
	//showPoint(p17, LIGHTGREEN);
	MbCartPoint p18(x4, y1);
	//showPoint(p18, LIGHTBLUE);
	MbCartPoint p19(x3, y2);
	//showPoint(p19, LIGHTMAGENTA);

	MbLineSegment* Seg15 = new MbLineSegment(p14, p15);
	MbLineSegment* Seg16 = new MbLineSegment(p15, p16);
	MbLineSegment* Seg18 = new MbLineSegment(p16, p17);
	MbLineSegment* Seg19 = new MbLineSegment(p17, p18);
	MbArc* Arc20 = new MbArc(p18, p19, p14);

	MbContour* ptrContour2 = new MbContour();

	//Добавление в контур сегментов
	ptrContour2->AddSegment(Seg15);
	ptrContour2->AddSegment(Seg16);
	ptrContour2->AddSegment(Seg18);
	ptrContour2->AddSegment(Seg19);
	ptrContour2->AddSegment(Arc20);

	MbContour* pFillets2 = NULL;
	::FilletPolyContour(ptrContour2, 6.6 * diamDifRatio, false, p16, pFillets2);
	::FilletPolyContour(ptrContour2, 1 * diamDifRatio, false, p18, pFillets2);

	ptrContours->Add(ptrContour2);
}

void sketchCircle(RPArray<MbContour>* ptrContours, double RAD1) {
	MbCartPoint cnt1(0, 0);

	// Построение окружности по центру и радиусу

	MbArc* pc1 = new MbArc(cnt1, RAD1);

	MbContour* ptrContour1 = new MbContour();
	ptrContour1->AddSegment(pc1);

	ptrContours->Add(ptrContour1);
}

void ParametricModelCreator::CreateMainBody(MbAssembly* pAsm = nullptr, double length = 343.95, double  ratio = 1)
{
	const double diamIn_STD = 50;
	double diamIn = diamIn_STD * ratio;


	//Функция эскиза, как и функция детали, принимает параметром diamIn 
	//Внутренний диаметр отверстия под вал
	//Это основной параметр этой детали, от которого все отталкивается
	//Здесь этот параметр можно менять
	//double diamIn = 50; 

	//Длина детали
	//double length = 343.95;

	////////// Основное тело
	//Создание образующей для тела вращения
	RPArray<MbContour>* ptrContours = new RPArray<MbContour>();
	//Вызываем функцию создания эскиза
	baseSketch(ptrContours, diamIn);

	MbPlacement3D* place = new MbPlacement3D();
	MbPlane* ptrSurface = new MbPlane(*place);

	MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
	MbSweptData* pCurves;
	pCurves = new MbSweptData(*ptrSurface, *ptrContours);
	MbVector3D dir(0, 0, 1);

	// Параметры операции выдавливания, задающие свойства тела для построения в прямом и в обратном направлении вдоль (глубина выдавливания и уклон).
	const double HEIGHT_FORWARD = length + 43.95, HEIGHT_BACKWARD = 0;
	const double ANGLE_FORWARD_DEGREE = 0;
	ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

	// Именователи элементов модели твердого тела и контуров образующей
	MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames(0, 1, false);

	// Вызов функции-утилиты для построения твердого тела выдавливания
	MbSolid* pSolid = nullptr;
	MbResultType res = ::ExtrusionSolid(*pCurves, dir, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolid);
	////////// Основное тело выдавлено



	////////// Основное отверстие, выдавливание
	const double RAD1 = diamIn / 2;//(diamDifRatio);
	RPArray<MbContour>* ptrContours1 = new RPArray<MbContour>();
	/////////////////////////////////////////////////////////Sketch2
	sketchCircle(ptrContours1, RAD1);
	/////////////////////////////////////////////////////////Sketch2
	// 
	//Создание образующей для тела вращения
	MbPlacement3D* place1 = new MbPlacement3D();
	MbPlane* ptrSurface1 = new MbPlane(*place1);

	MbPlane* pPlaneXY1 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
	MbSweptData* pCurves1;
	pCurves1 = new MbSweptData(*ptrSurface1, *ptrContours1);
	MbVector3D dir1(0, 0, 1);

	// Именователи элементов модели твердого тела и контуров образующей
	MbSNameMaker operNames1(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames1(0, 1, false);

	// Вызов функции-утилиты для построения твердого тела выдавливания
	MbSolid* pSolid1 = nullptr;
	MbResultType res1 = ::ExtrusionSolid(*pCurves1, dir1, nullptr, nullptr, false, extrusionParams, operNames1, cNames1, pSolid1);
	//выдавливание завершено
	////////// Основное отверстие, выдавливание
	//выдавливание завершено




	////////////out circle
	const double thickness = 3;
	const double RAD3 = RAD1 + thickness;
	////////// Основное отверстие, выдавливание
	RPArray<MbContour>* ptrContours3 = new RPArray<MbContour>();
	/////////////////////////////////////////////////////////Sketch2
	sketchCircle(ptrContours3, RAD3);
	/////////////////////////////////////////////////////////Sketch2
	//Создание образующей для тела вращения
	MbPlacement3D* place3 = new MbPlacement3D();
	MbPlane* ptrSurface3 = new MbPlane(*place3);

	MbPlane* pPlaneXY3 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
	MbSweptData* pCurves3;
	pCurves3 = new MbSweptData(*ptrSurface3, *ptrContours3);
	MbVector3D dir3(0, 0, 1);

	// Именователи элементов модели твердого тела и контуров образующей
	MbSNameMaker operNames3(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames3(0, 1, false);

	// Вызов функции-утилиты для построения твердого тела выдавливания
	MbSolid* pSolid3 = nullptr;
	MbResultType res3 = ::ExtrusionSolid(*pCurves3, dir3, nullptr, nullptr, false, extrusionParams, operNames3, cNames3, pSolid3);
	//выдавливание завершено
	////////// Основное отверстие, выдавливание
	////////////out circle




	//////////  Боковые отверстия, выдавливание
	RPArray<MbContour>* ptrContours2 = new RPArray<MbContour>();
	/////////////////////////////////////////////////////////Sketch3 
	baseSideHoleSketch(ptrContours2, diamIn, false, false);
	baseSideHoleSketch(ptrContours2, diamIn, true, false);
	baseSideHoleSketch(ptrContours2, diamIn, false, true);
	baseSideHoleSketch(ptrContours2, diamIn, true, true);
	////////////////////////////////////////////////////////Sketch3

	//Создание образующей для тела вращения
	MbPlacement3D* place2 = new MbPlacement3D();
	MbPlane* ptrSurface2 = new MbPlane(*place2);
	MbPlane* pPlaneXY2 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
	MbSweptData* pCurves2;
	pCurves2 = new MbSweptData(*ptrSurface2, *ptrContours2);
	MbVector3D dir2(0, 0, 1);

	// Именователи элементов модели твердого тела и контуров образующей
	MbSNameMaker operNames2(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames2(0, 1, false);

	// Вызов функции-утилиты для построения твердого тела выдавливания
	MbSolid* pSolid2 = nullptr;
	MbResultType res2 = ::ExtrusionSolid(*pCurves2, dir2, nullptr, nullptr, false, extrusionParams, operNames2, cNames2, pSolid2);
	//////////  Боковые отверстия, выдавлиены




	/// финальное выдавливание
	MbSolid* pSolid6 = nullptr;

	MbBooleanFlags flagsBool;
	flagsBool.InitBoolean(true);
	flagsBool.SetMergingFaces(true);
	flagsBool.SetMergingEdges(true);
	MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

	MbResultType res6 = ::BooleanResult(*pSolid, cm_Copy, *pSolid2, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid);

	MbResultType res7 = ::BooleanResult(*pSolid, cm_Copy, *pSolid3, cm_Copy, bo_Union, flagsBool, operBoolNames, pSolid6);

	//ВЫДАВЛИВАНИЕ КВАДРАТИКОВ ПО УГЛАМ
	MbResultType res8 = ::BooleanResult(*pSolid6, cm_Copy, *pSolid1, cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolid6);

	pSolid6->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -31.5)));
	pSolid6->SetColor(ParametricModelCreator::colorScheme ? RGB(138, 161, 171) : RGB(20, 30, 30));

	auto addedItem = pAsm->AddItem(*pSolid6);
	addedItem->SetItemName(SimpleName(CASE_ITEMNAME));


	::DeleteMatItem(ptrContours);
	::DeleteMatItem(place);
	::DeleteItem(ptrSurface);
	::DeleteItem(pPlaneXY);
	::DeleteMatItem(pCurves);

	::DeleteMatItem(ptrContours1);
	::DeleteMatItem(place1);
	::DeleteItem(ptrSurface1);
	::DeleteItem(pPlaneXY1);
	::DeleteMatItem(pCurves1);

	::DeleteMatItem(ptrContours2);
	::DeleteMatItem(place2);
	::DeleteItem(ptrSurface2);
	::DeleteItem(pPlaneXY2);
	::DeleteMatItem(pCurves2);

	::DeleteMatItem(ptrContours3);
	::DeleteMatItem(place3);
	::DeleteItem(ptrSurface3);
	::DeleteItem(pPlaneXY3);
	::DeleteMatItem(pCurves3);

	::DeleteItem(pSolid);
	::DeleteItem(pSolid1);
	::DeleteItem(pSolid2);
	::DeleteItem(pSolid3);
	::DeleteItem(pSolid6);

}

