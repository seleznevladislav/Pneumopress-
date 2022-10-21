#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

void ParametricModelCreator::CreateORing(MbAssembly* pAsm, double Z, double ratio) {

	MbPlacement3D pl;

	// Центр окружностей и дуг в локальной СК
	MbCartPoint cnt(0, 22.575*ratio);
	// Построение окружности по центру и радиусу
	const double RAD1 = 1.325;
	MbArc* circle1 = new MbArc(cnt, RAD1);
	MbContour* pContour = new MbContour();
	pContour->AddSegment(circle1);
	// Множитель для преобразования угловых значений из градусов в радианы
	const double DEG_TO_RAD = M_PI / 180.0;

	RPArray<MbContour> arrContours;
	arrContours.push_back(pContour);
	// Подготовка параметров для вызова функции построения тела вращения.

	MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
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



	// Именователи для операции построения тела вращения и для контуров образующей
	MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
	PArray<MbSNameMaker> cNames(0, 1, false);

	// Ось вращения для построения тела:
	// ось Y мировой СК смещается на -50 единиц вдоль оси X.
	MbAxis3D axis(pl.GetAxisX());

	// Вызов функции-утилиты для построения твердого тела вращения
	MbSolid* pSolid = nullptr;
	MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pSolid);

	// Отображение построенного тела
	MbAxis3D axVert(MbVector3D(0, 1, 0));
	pSolid->Rotate(axVert, -M_PI / 2);
	pSolid->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, Z)));

	pSolid->SetColor(BLACK);
	pAsm->AddItem(*pSolid);
	//viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);


	::DeleteItem(circle1);
	::DeleteItem(pSolid);
}