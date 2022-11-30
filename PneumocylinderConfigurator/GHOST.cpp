#include "BuildMathModel.h"

using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::GBolt4m10() {
	ItemSPtr model;

	path_string  filePath1 = L"..\\GOST\\���� 4�10-6gx35 ���� 7798-70.step";
	::ImportFromFile(model, filePath1, nullptr, nullptr);
	MbSolid* Bolt4m10 = static_cast<MbSolid*>((MbItem*)model);

	SPtr<MbSolid> pSolidRes(Bolt4m10);
	return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GWasherM20() {
	ItemSPtr model10;

	path_string  filePath10 = L"..\\GOST\\����� �20-6H ���� 5916-70.step";
	::ImportFromFile(model10, filePath10, nullptr, nullptr);
	MbSolid* WasherM20 = static_cast<MbSolid*>((MbItem*)model10);

	SPtr<MbSolid> pSolidRes(WasherM20);
	return pSolidRes;
}