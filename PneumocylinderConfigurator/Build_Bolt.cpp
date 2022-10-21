#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

//Функции по созданию деталей ребят
void ParametricModelCreator::CreateBolt(MbAssembly* pAsm, double X, double Y, double Z , int ANGLE )
{
	MbSolid* pCyl = NULL;

	MbSNameMaker namesCyl(1, MbSNameMaker::i_SideNone, 0);

	SArray<MbCartPoint3D> points(3);
	points.Add(MbCartPoint3D(0, 0, 0));
	points.Add(MbCartPoint3D(0, 19.6, 0));
	points.Add(MbCartPoint3D(5.75, 0, 0));

	ElementarySolid(points, et_Cylinder, namesCyl, pCyl);



	//второй цилиндр

	MbSolid* pCyl1 = NULL;
	MbSNameMaker namesCyl1(1, MbSNameMaker::i_SideNone, 0);

	SArray<MbCartPoint3D> points1(3);
	points1.Add(MbCartPoint3D(0, 19.6, 0));
	points1.Add(MbCartPoint3D(0, 27.5, 0));
	points1.Add(MbCartPoint3D(8.1, 19.6, 0));

	ElementarySolid(points1, et_Cylinder, namesCyl1, pCyl1);




	// 2) Построение отверстия в исходном теле
	MbSolid* pBlockHole = NULL;
	{
		// Объект-именователь для операции построения отверстия
		MbSNameMaker holeNames(ct_HoleSolid, MbSNameMaker::i_SideNone, 0);


		// Локальная СК, задающая положение вспомогательного тела - образа отверстия.
		const double DEG_TO_RAD = M_PI / 180.0;
		MbPlacement3D plHole(MbCartPoint3D(0, 0, 0));
		plHole.Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0))),
			90 * DEG_TO_RAD);

		BorerValues params;

		params.type = BorerValues::bt_SimpleCylinder;

		params.diameter = 8;

		params.depth = 28;

		params.down = true;

		::HoleSolid(pCyl, cm_Copy, plHole, params, holeNames, pBlockHole);


	}

	MbSolid* pBlockHole1 = NULL;
	{
		// Объект-именователь для операции построения отверстия
		MbSNameMaker holeNames(ct_HoleSolid, MbSNameMaker::i_SideNone, 0);


		// Локальная СК, задающая положение вспомогательного тела - образа отверстия.
		const double DEG_TO_RAD = M_PI / 180.0;
		MbPlacement3D plHole1(MbCartPoint3D(0, 0, 0));
		plHole1.Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0))),
			90 * DEG_TO_RAD);
		plHole1.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 19.6, 0)));
		BorerValues params;

		params.type = BorerValues::bt_SimpleCylinder;

		params.diameter = 8;

		params.depth = 7.9;

		params.down = true;

		::HoleSolid(pCyl1, cm_Copy, plHole1, params, holeNames, pBlockHole1);
	}

	// show(Style(1, LIGHTGRAY), pBlockHole); 
	// show(Style(1, LIGHTGRAY), pBlockHole1); 


	MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 27.6, 0), MbVector3D(1, 0, 0),
		MbVector3D(0, 0, 1));


	// Трехмерная кривая "контур на плоскости", которая будет использоваться в качестве
	// образующей для операции выдавливания
	MbSolid* pSh = NULL;

	MbSNameMaker elNames(1, MbSNameMaker::i_SideNone, 0);
	SArray<MbCartPoint3D> pnts(7);
	pnts.Add(MbCartPoint3D(0, 23.6, 4.763));
	pnts.Add(MbCartPoint3D(4.125, 23.6, 2.382));
	pnts.Add(MbCartPoint3D(4.125, 23.6, -2.382));
	pnts.Add(MbCartPoint3D(0, 23.6, -4.763));
	pnts.Add(MbCartPoint3D(-4.125, 23.6, -2.382));
	pnts.Add(MbCartPoint3D(-4.125, 23.6, 2.382));
	pnts.Add(MbCartPoint3D(-4.125, 27.6, 2.382));

	ElementarySolid(pnts, et_Prism, elNames, pSh);

	MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);

	// Флаги булевой операции: построение замкнутого тела с объединением
	// подобных граней и ребер.
	MbBooleanFlags flagsBool;
	flagsBool.InitBoolean(false);
	flagsBool.SetMergingFaces(true);
	flagsBool.SetMergingEdges(true);

	// Результирующее тело
	MbSolid* pSolid = NULL;
	// Вызов булевой операции для выполнения объединения.
	// Для выполнения вычитания надо вместо типа операции bo_Union указать
	// значение bo_Difference, для пересечения - значение bo_Intersect.
	MbResultType res = ::BooleanResult(*pBlockHole1, cm_Copy, *pBlockHole, cm_Copy, bo_Union, flagsBool, operBoolNames, pSolid);

	MbSNameMaker operBoolNames1(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);


	// Результирующее тело
	MbSolid* pSolidSh = NULL;
	// Вызов булевой операции для выполнения объединения.
	// Для выполнения вычитания надо вместо типа операции bo_Union указать
	// значение bo_Difference, для пересечения - значение bo_Intersect.
	MbResultType res1 = ::BooleanSolid(*pSolid, cm_Copy, *pSh, cm_Copy, bo_Difference, operBoolNames1, pSolidSh);

	MbSNameMaker chamferNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

	// 3) Указание значений параметров операции построения фасок
	SmoothValues params;
	// Длины катетов фаски
	params.distance1 = 0.5;
	params.distance2 = 0.5;
	// Тип фаски - построение фаски с заданными катетами
	params.form = st_Chamfer;
	// Режим автоматического скругления ребер, гладко стыкующиеся с ребрами
	// из входного массива
	params.prolong = false;
	// Способ скругления троек ребер
	params.smoothCorner = SmoothValues::ec_uniform;

	// 4) Формирование массива с ребрами для скругления.
	// Запрос всех ребер исходного тела
	RPArray<MbCurveEdge> allEdges;
	pSolidSh->GetEdges(allEdges);
	// Массив ребер для скругления
	RPArray<MbCurveEdge> initCurves;

	initCurves.Add(allEdges[22]);

	// 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
	RPArray<MbFace> initBounds(0, 1);

	// 6) Вызов функции построения фасок
	MbSolid* pResult = NULL;
	MbResultType res5 = ::ChamferSolid(*pSolidSh, cm_Copy, initCurves,
		params, chamferNames, pResult);
	//   if (res5 == rt_Success)
	   //    show(Style(1, LIGHTGRAY), pResult); 



	MbSNameMaker chamferNames1(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);

	// 3) Указание значений параметров операции построения фасок
	SmoothValues params1;
	// Длины катетов фаски
	params1.distance1 = 2;
	params1.distance2 = 2;
	// Тип фаски - построение фаски с заданными катетами
	params1.form = st_Chamfer;
	// Режим автоматического скругления ребер, гладко стыкующиеся с ребрами
	// из входного массива
	params1.prolong = false;
	// Способ скругления троек ребер
	params1.smoothCorner = SmoothValues::ec_uniform;

	// 4) Формирование массива с ребрами для скругления.
	// Запрос всех ребер исходного тела
	RPArray<MbCurveEdge> allEdges1;
	pResult->GetEdges(allEdges1);
	// Массив ребер для скругления
	RPArray<MbCurveEdge> initCurves1;

	initCurves1.Add(allEdges1[24]);

	// 5) Массив граней для обрезки при неоднозначном выполнении метода - пустой
	RPArray<MbFace> initBounds1(0, 1);

	// 6) Вызов функции построения фасок
	MbSolid* pResult1 = NULL;
	MbResultType res6 = ::ChamferSolid(*pResult, cm_Copy, initCurves1,
		params1, chamferNames1, pResult1);
	MbAxis3D axVert(MbVector3D(1, 0, 0));
	pResult1->Rotate(axVert, M_PI / 2 * ANGLE);
	pResult1->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(X, Y, Z)));

	if (res6 == rt_Success)
		//pResult1->Rotate(axVert, M_PI / 2 );

		pResult1->SetColor(LIGHTGRAY);
	pAsm->AddItem(*pResult1);
	//viewManager->AddObject(Style(1, LIGHTGRAY), pResult1);


	::DeleteItem(pCyl);
	::DeleteItem(pCyl1);
	::DeleteItem(pBlockHole);
	::DeleteItem(pBlockHole1);
	::DeleteItem(pSh);
	::DeleteItem(pSolid);
	::DeleteItem(pSolidSh);
	::DeleteItem(pResult1);
	::DeleteItem(pResult);
	::DeleteItem(pPlaneXZ);

}