#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchCollar(RPArray<MbContour>& _arrContours,double ratio)
{
	// Создание массива точек квадрата, к которому в дальнейшем добавятся скругления.
	SArray<MbCartPoint> arrPnts(7);
	arrPnts.Add(MbCartPoint(0, 10.05 * ratio));
	arrPnts.Add(MbCartPoint(0, 11 * ratio));
	arrPnts.Add(MbCartPoint(3, 12.25 * ratio));
	arrPnts.Add(MbCartPoint(32, 12.25 * ratio));
	arrPnts.Add(MbCartPoint(32, 9.25 * ratio));
	arrPnts.Add(MbCartPoint(27, 9.25 * ratio));
	arrPnts.Add(MbCartPoint(27, 10.05 * ratio));

	// Построение единой ломаной внешнего контура по точкам
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
	MbContour* pContourPolyline = new MbContour();

	pContourPolyline->AddSegment(pPolyline);

	_arrContours.push_back(pContourPolyline);

	::DeleteItem(pPolyline);
}

void ParametricModelCreator::CreateBrassCollar(MbAssembly* pAsm, double ratio) {
	// Множитель для преобразования угловых значений из градусов в радианы
	const double DEG_TO_RAD = M_PI / 180.0;

	// Локальная СК (по умолчанию совпадает с мировой СК)
	MbPlacement3D pl;

	// Вызов функции для построения образующей (из примера 6)
	RPArray<MbContour> arrContours;
	CreateSketchCollar(arrContours, ratio);


	// Подготовка параметров для вызова функции построения тела вращения.
	// sweptData - объект, в котором хранятся сведения об образующей.
	MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
		MbCartPoint3D(0, 1, 0));
	MbSweptData sweptData(*pPlaneXY, arrContours);

	// Объект параметров для операции построения тела вращения.
	// Первые два параметра конструктора задают углы вращения в прямом и обратном
	// направлении (по нормали к образующей или противоположно этой нормали).
	// В данном примере вращение осуществляется на 120 градусов в прямом направлении.
	// Третий параметр задает форму топологии твердого тела.
	// При s = 0 строится тело с топологией сферы, при s = 1 - с топологией тора.
	// Если образующая - незамкнутая кривая, и ось вращения лежит в плоскости кривой,
	// то при s = 0 при построении образующая будет автоматически продлена до оси
	// вращения. В данном примере различий между значениями s нет, т.к. образующая
	// имеет вид замкнутого контура.
	RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

	// Следующая строка задает построение тела с незамкнутой оболочкой ("пустого").
	// revParms.shellClosed = false;
	// Задание толщины стенки тела
	// revParms.thickness1 = 8;

	// Именователи для операции построения тела вращения и для контуров образующей
	MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames(0, 1, false);

	// Ось вращения для построения тела:
	// ось Y мировой СК смещается на -50 единиц вдоль оси X.
	MbAxis3D axis(pl.GetAxisX());


	// Вызов функции-утилиты для построения твердого тела вращения
	MbSolid* pSolid = nullptr;
	MbResultType res = ::RevolutionSolid(sweptData, axis, revParms,
		operNames, cNames, pSolid);

	// Отображение построенного тела
	MbAxis3D axVert(MbVector3D(0, 1, 0));
	pSolid->Rotate(axVert, M_PI / 2);
	pSolid->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 27)));
	if (res == rt_Success) {
		pSolid->SetColor(LIGHTGRAY);
		pAsm->AddItem(*pSolid);
		//viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
	}



	// Уменьшение счетчиков ссылок динамических объектов ядра
	::DeleteItem(pSolid);
}