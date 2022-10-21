#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void CreateSketchEgorClampingBar(RPArray<MbContour>& _arrContours, double length)
{
	// Создание массива точек квадрата, к которому в дальнейшем добавятся скругления.
	// Размер массива - 8 точек для учета точек четырех сегментов скруглений.
	SArray<MbCartPoint> arrPnts(10);
	arrPnts.Add(MbCartPoint(0, 0));
	arrPnts.Add(MbCartPoint(0, 3.5));
	arrPnts.Add(MbCartPoint(0.5, 4));
	arrPnts.Add(MbCartPoint(10, 4));
	arrPnts.Add(MbCartPoint(10, 3.5));
	arrPnts.Add(MbCartPoint(length + 70, 3.5));
	arrPnts.Add(MbCartPoint(length + 70, 4));
	arrPnts.Add(MbCartPoint(length + 79.5, 4));
	arrPnts.Add(MbCartPoint(length + 80, 3.5));
	arrPnts.Add(MbCartPoint(length + 80, 0));

	// Построение единой ломаной внешнего контура по точкам
	MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
	MbContour* pContourPolyline = new MbContour();

	pContourPolyline->AddSegment(pPolyline);

	_arrContours.push_back(pContourPolyline);
	::DeleteItem(pPolyline);
}

void ParametricModelCreator::CreateClampingBar(MbAssembly* pAsm, double X, double Y, double length)
{
	// Множитель для преобразования угловых значений из градусов в радианы
	const double DEG_TO_RAD = M_PI / 180.0;

	// Локальная СК (по умолчанию совпадает с мировой СК)
	MbPlacement3D pl;

	// Вызов функции для построения образующей (из примера 6)
	RPArray<MbContour> arrContours;
	CreateSketchEgorClampingBar(arrContours, length);

	// Подготовка параметров для вызова функции построения тела вращения.
	// sweptData - объект, в котором хранятся сведения об образующей.
	MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 1),
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
	MbAxis3D axis(pl.GetAxisZ());


	// Вызов функции-утилиты для построения твердого тела вращения
	MbSolid* pSolid = nullptr;
	MbResultType res = ::RevolutionSolid(sweptData, axis, revParms,
		operNames, cNames, pSolid);

	// Отображение построенного тела
	MbAxis3D axVert(MbVector3D(0, 1, 0));
	//pSolid->Rotate(axVert, -M_PI / 2);
	pSolid->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(X, Y, -49.525)));
	if (res == rt_Success) {
		pSolid->SetColor(ParametricModelCreator::colorScheme ? RGB(78, 81, 81) : RGB(65, 45, 10));//BROWN
		pAsm->AddItem(*pSolid);
		//viewManager->AddObject(Style(1, BROWN), pSolid);
	}


	// Уменьшение счетчиков ссылок динамических объектов ядра
	::DeleteItem(pSolid);
	//::DeleteItem(pPlaneXY);

}