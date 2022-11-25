#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::GHOST() {
	ItemSPtr model;

	path_string  filePath1 = L"..\\GOST\\¡ÓÎÚ 4Ã10-6gx35 √Œ—“ 7798-70.step";
	::ImportFromFile(model, filePath1, nullptr, nullptr);
	MbSolid* Bolt4m10 = static_cast<MbSolid*>((MbItem*)model);

	SPtr<MbSolid> pSolidRes(Bolt4m10);
	return pSolidRes;
}