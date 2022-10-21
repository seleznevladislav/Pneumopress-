#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchShaftPivot(RPArray<MbContour>& _arrContours, double ratio)
{
	SArray<MbCartPoint> arrPnts(4);
	arrPnts.Add(MbCartPoint(12.5 * ratio, 12.5 * ratio));
	arrPnts.Add(MbCartPoint(12.5 * ratio, -12.5 * ratio));
	arrPnts.Add(MbCartPoint(-12.5 * ratio, -12.5 * ratio));
	arrPnts.Add(MbCartPoint(-12.5 * ratio, 12.5 * ratio));

	// Построение единой ломаной внешнего контура по точкам
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
	MbContour* pContourPolyline = nullptr;

	// Задание скругления с использованием функции FilletPolyContour
	::FilletPolyContour(pPolyline, 5 * ratio, false, arrPnts[0], pContourPolyline);

	// Задание индексов точек, в которых будет задаваться скругление с учетом
	// добавления новой точки при скруглении с использованием функции FilletTwoSegments

	ptrdiff_t idxSideRight1 = 0;
	ptrdiff_t idxSideRight2 = 2;
	ptrdiff_t idxSideRight3 = 4;

	// Добавление скруглений
	// 
	pContourPolyline->FilletTwoSegments(idxSideRight1, 5 * ratio);
	pContourPolyline->FilletTwoSegments(idxSideRight2, 5 * ratio);
	pContourPolyline->FilletTwoSegments(idxSideRight3, 5 * ratio);

	_arrContours.push_back(pContourPolyline);
	::DeleteItem(pPolyline);
}

void ParametricModelCreator::CreateShaftPivot(MbAssembly* pAsm, double position, double ratio)
{
	const double diamIn_STD = 8;
	const double sizeOut_STD = 12.5;
	double outRatio = ((sizeOut_STD - diamIn_STD) + (diamIn_STD * ratio)) / sizeOut_STD;

	//Построение параллелепипеда    
	MbPlacement3D pl;

	// Создание образующей для тела выдавливания
	RPArray<MbContour> arrContours;
	CreateSketchShaftPivot(arrContours, outRatio);

	// Отображение образующей (в плоскости XY глобальной СК)
	/*for (int i = 0; i<arrContours.size(); i++)
		show( Style(1, LIGHTRED), arrContours[i], &pl);
	*/
	// ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ
	MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 0, 1));
	// Объект, хранящий параметры образующей
	MbSweptData sweptData(*pPlaneXZ, arrContours);
	// Направляющий вектор для операции выдавливания
	MbVector3D dir(0, 1, 0);

	// Параметры операции выдавливания, задающие свойства тела для построения в прямом и в обратном направлении вдоль (глубина выдавливания и уклон).
	const double HEIGHT_FORWARD = 0, HEIGHT_BACKWARD = 39;
	ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

	// Именователи элементов модели твердого тела и контуров образующей
	MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames(0, 1, false);

	// Вызов функции-утилиты для построения твердого тела выдавливания
	MbSolid* pSolid = nullptr;
	MbResultType res = ::ExtrusionSolid(sweptData, dir, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolid);


	//Построение отверстия
	MbSolid* pBlockHole = NULL;
	{
		MbSNameMaker holeNames(ct_HoleSolid, MbSNameMaker::i_SideNone, 0);
		const double DEG_TO_RAD = M_PI / 180.0;
		MbPlacement3D plHole(MbCartPoint3D(0, 0, 0));
		plHole.Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0))),
			90 * DEG_TO_RAD);
		plHole.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -39, 0)));
		BorerValues params;

		params.type = BorerValues::bt_SimpleCylinder;

		params.diameter = 16* ratio;

		params.depth = 32;

		params.down = true;

		::HoleSolid(pSolid, cm_Copy, plHole, params, holeNames, pBlockHole);


	}

	//Построение вверхней части
	MbPlacement3D pl1;

	SArray<MbCartPoint> arrPnts1(4);
	arrPnts1.Add(MbCartPoint(-12.5 * outRatio, 14.5));
	arrPnts1.Add(MbCartPoint(-12.5 * outRatio, 0));
	arrPnts1.Add(MbCartPoint(12.5 * outRatio, 0));
	arrPnts1.Add(MbCartPoint(12.5 * outRatio, 14.5));

	MbPolyline* pPolyline1 = new MbPolyline(arrPnts1, false);

	MbCartPoint arcCenter(0, 14.5);
	const double RADIUS = 12.5 * outRatio;
	MbArc* pArc = new MbArc(arcCenter, RADIUS, arrPnts1[3], arrPnts1[0], 1);
	MbContour* pContour1 = new MbContour(*pPolyline1, true);
	pContour1->AddSegment(pArc);
	// Вызовы информационных методов контура
	size_t segmentsCount = pContour1->GetSegmentsCount(); // 2
	double tMin = pContour1->GetTMin(); // 0.0
	double tMax = pContour1->GetTMax(); // 10.14159
	// Параметр IsSmoothConnected - допуск для классификации угловых точек    на контуре
	bool isSmooth = pContour1->IsSmoothConnected(0.001); // false
	double length = pContour1->CalculateLength(tMin, tMax); // 302.83
	bool isClosed = pContour1->IsClosedContinuousC0(); // true
	bool isCurvilinear = pContour1->IsAnyCurvilinear(); // true
	// ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ
	MbSweptData sweptData1(pl1, *pContour1);
	MbVector3D dir1(0, 0, 1);
	const double HEIGHT_FORWARD1 = 5, HEIGHT_BACKWARD1 = 5;
	ExtrusionValues extrusionParam(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);

	MbSNameMaker operNames1(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames1(0, 1, false);

	MbSolid* pSolid1 = NULL;
	MbResultType resCode = ::ExtrusionSolid(sweptData1, dir1, NULL, NULL, false,
		extrusionParam, operNames1, cNames1, pSolid1);


	//Построение отверстия в вверхней части
	MbSolid* pHole = NULL;
	{
		MbSNameMaker hole1Names(ct_HoleSolid, MbSNameMaker::i_SideNone, 0);

		MbPlacement3D pl1Hole(MbCartPoint3D(0, 0, 0));
		pl1Hole.Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 1, 0))), 0);
		pl1Hole.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 12.5, 5)));
		BorerValues params1;
		params1.type = BorerValues::bt_SimpleCylinder;

		params1.diameter = (int)(15*outRatio);//делаем для отверстия шаг 1

		params1.depth = 10;

		params1.down = true;

		::HoleSolid(pSolid1, cm_Copy, pl1Hole, params1, hole1Names, pHole);
	}

	//Объединение тел
	MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
	MbBooleanFlags flagsBool;
	flagsBool.InitBoolean(true);
	flagsBool.SetMergingFaces(true);
	flagsBool.SetMergingEdges(true);

	MbSolid* pSolidd = NULL;
	::BooleanResult(*pBlockHole, cm_Copy, *pHole, cm_Copy, bo_Union,
		flagsBool, operBoolNames, pSolidd);

	//Сопряжения    
	MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

	//Указание значений параметров операции скругления ребер
	SmoothValues paramss;
	// Радиусы кривизны на двух скругляемых поверхностях
	paramss.distance1 = 3 * outRatio;
	paramss.distance2 = 3 * outRatio;
	// Тип сопряжения – скругление по двум радиусам
	paramss.form = st_Fillet;
	// Форма профиля сопряжения - окружность
	paramss.conic = 0;
	// Требуется скруглять только ребра, переданные во входном массиве
	paramss.prolong = false;
	// Способ скругления троек ребер
	paramss.smoothCorner = SmoothValues::ec_uniform;
	// Флаг сохранения кромки – режим сохранения поверхности
	paramss.keepCant = ts_negative;
	// Строгое скругление
	paramss.strict = true;

	//Формирование массива с ребрами для скругления.
	// Запрос всех ребер исходного тела
	RPArray<MbCurveEdge> allEdges(4, 1);
	pSolidd->GetEdges(allEdges);
	// В массив ребер для скругления помещается только одно ребро
	RPArray<MbCurveEdge> initCurves(4, 1);
	initCurves.Add(allEdges[16]);
	initCurves.Add(allEdges[20]);

	//Массив граней для обрезки – в данном примере пустой
	RPArray<MbFace> initBounds(0, 1);

	//Вызов функции скругления ребер.
	// В результате выполняется скругление одного ребра – окружности,
	// по которой в исходном теле соединены цилиндр и пластина.
	MbSolid* pResult = NULL;
	MbResultType ress = ::FilletSolid(*pSolidd, cm_Copy, initCurves, initBounds,
		paramss, filletNames, pResult);

	/// //////////////////////////////////////////
	//pResult = pSolidd;///////////////////////////////////////////////////////////////////////////////////////////////

	MbAxis3D axVert(MbVector3D(1, 0, 0));
	// 7) Отображение тела после скругления ребра
	if (ress == rt_Success)
		pResult->Rotate(axVert, M_PI / 2); // вращаем по оси
	pResult->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, position + 113.8)));

	pResult->SetColor(ParametricModelCreator::colorScheme ? RGB(60, 64, 62) : RGB(160,164,160));//GRAY RGB(65,78,81) RGB(40, 45,46)
	pAsm->AddItem(*pResult);
	//viewManager->AddObject(Style(1, LIGHTGRAY), pResult);


// Уменьшение счетчиков ссылок динамически созданных объектов ядра
	::DeleteItem(pSolid);
	::DeleteItem(pSolid1);
	::DeleteItem(pHole);
	::DeleteItem(pBlockHole);
	::DeleteItem(pResult);

}