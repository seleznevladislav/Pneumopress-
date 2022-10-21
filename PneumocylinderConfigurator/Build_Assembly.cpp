#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

MbAssembly* ParametricModelCreator::CreatePneumocylinderAssembly(BuildParams params)
{
	MbAssembly* pAsm = new MbAssembly();

	double param_length = params.length;

	double diamMain = params.diam;
	const double diamMain_STD = 50;
	//calculate offsets
	//Разница стандартного и заданного диаметров
	double diamMainOffset = diamMain - diamMain_STD;
	//Соотношение стандартного и заданного диаметров
	double diamDifRatio = diamMain / diamMain_STD;

	double radMainOffset = diamMainOffset / 2;
	
	// �������� ������
	double len_dif = param_length - 132.95;

	//pAsm->AddItem(*pSolid);

	double DD = 23.6 + radMainOffset;//ClampingBar and bolts offset from 0 coord

	//Шток
	CreateShaft(pAsm, len_dif, diamDifRatio);

	// Вращающая насадка на шток
	CreateShaftPivot(pAsm, len_dif, diamDifRatio); // Васинкина

	// крышки пневмоцилиндра
	CreateBase(pAsm, diamDifRatio); // Зарубин
	CreateTopGuide(pAsm, len_dif, diamDifRatio); // Фукина

	// корпус
	CreateMainBody(pAsm, len_dif, diamDifRatio); // Балобанов

	// поршень и кольца на нем
	CreateSealHousing(pAsm, diamDifRatio); // Гарник
	CreateORing(pAsm, -19, diamDifRatio); // 
	CreateORing(pAsm, -8.5, diamDifRatio); // 

	// Упоры поршня на штоке
	CreateSocketHeadCollar(pAsm, diamDifRatio); // Приходько
	CreateBrassCollar(pAsm, diamDifRatio); // Козырь

	// штыри
	CreateClampingBar(pAsm, DD, DD, len_dif); // Приходько 
	CreateClampingBar(pAsm, DD, -DD, len_dif); // 
	CreateClampingBar(pAsm, -DD, -DD, len_dif); // 
	CreateClampingBar(pAsm, -DD, DD, len_dif); // 

	CreateBolt(pAsm, DD, DD, -32.6); // Фукина
	CreateBolt(pAsm, DD, -DD, -32.6); //
	CreateBolt(pAsm, -DD, -DD, -32.6); //
	CreateBolt(pAsm, -DD, DD, -32.6); //
	CreateBolt(pAsm, -DD, DD, len_dif + 16.05, 1); //
	CreateBolt(pAsm, DD, DD, len_dif + 16.05, 1); //
	CreateBolt(pAsm, DD, -DD, len_dif + 16.05, 1); //
	CreateBolt(pAsm, -DD, -DD, len_dif + 16.05, 1); //

	return pAsm;
}
