#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::GWasherM20() {
	ItemSPtr model10;

	path_string  filePath10 = L"..\\GOST\\√‡ÈÍ‡ Ã20-6H √Œ—“ 5916-70.step";
	::ImportFromFile(model10, filePath10, nullptr, nullptr);
	MbSolid* WasherM20 = static_cast<MbSolid*>((MbItem*)model10);

	SPtr<MbSolid> pSolidRes(WasherM20);
	return pSolidRes;
}