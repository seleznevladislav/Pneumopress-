#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

// Инициализирую статическую переменную класса - обязательно
int ParametricModelCreator::colorScheme = 0;

MbModel* ParametricModelCreator::CreatePneymocylinderModel(BuildParams params)
{
	ParametricModelCreator::colorScheme = params.colorScheme;
	MbModel* model = new MbModel();
	auto pneumocylinderAssembly = CreatePneumocylinderAssembly(params);
	model->AddItem(*pneumocylinderAssembly);
	::DeleteItem(pneumocylinderAssembly);
	return model;
}