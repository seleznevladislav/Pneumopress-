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
SPtr<MbSolid> ParametricModelCreator::GWasherA14() {
    ItemSPtr model2;

    path_string  filePath2 = L"..\\GOST\\����� A.14.37 ���� 11371-78.step";
    ::ImportFromFile(model2, filePath2, nullptr, nullptr);
    MbSolid* WasherA14 = static_cast<MbSolid*>((MbItem*)model2);

    SPtr<MbSolid> pSolidRes(WasherA14);
    return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GScrewM14() {
    ItemSPtr model3;

    path_string  filePath3 = L"..\\GOST\\���� �14-6gx25 ���� 11738-84.step";
    ::ImportFromFile(model3, filePath3, nullptr, nullptr);
    MbSolid* ScrewM14 = static_cast<MbSolid*>((MbItem*)model3);

    SPtr<MbSolid> pSolidRes(ScrewM14);
    return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GScrewM10() {
    ItemSPtr model4;

    path_string  filePath4 = L"..\\GOST\\���� �10-6gx45 ���� 11738-84.step";
    ::ImportFromFile(model4, filePath4, nullptr, nullptr);
    MbSolid* ScrewM10 = static_cast<MbSolid*>((MbItem*)model4);

    SPtr<MbSolid> pSolidRes(ScrewM10);
    return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GScrewM8() {
    ItemSPtr model5;

    path_string  filePath5 = L"..\\GOST\\���� �10-6gx45 ���� 11738-84.step";
    ::ImportFromFile(model5, filePath5, nullptr, nullptr);
    MbSolid* ScrewM8 = static_cast<MbSolid*>((MbItem*)model5);

    SPtr<MbSolid> pSolidRes(ScrewM8);
    return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GScrewAM8() {
    ItemSPtr model6;

    path_string  filePath6 = L"..\\GOST\\���� �.�8-6gx35 ���� 11074-93.step";
    ::ImportFromFile(model6, filePath6, nullptr, nullptr);
    MbSolid* ScrewAM8 = static_cast<MbSolid*>((MbItem*)model6);

    SPtr<MbSolid> pSolidRes(ScrewAM8);
    return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GWassherM8() {
    ItemSPtr model7;

    path_string  filePath7 = L"..\\GOST\\����� �8-6H ���� 5915-70.step";
    ::ImportFromFile(model7, filePath7, nullptr, nullptr);
    MbSolid* WassherM8 = static_cast<MbSolid*>((MbItem*)model7);

    SPtr<MbSolid> pSolidRes(WassherM8);
    return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GWasherM16() {
    ItemSPtr model8;

    path_string  filePath8 = L"..\\GOST\\����� �16-6H ���� 5915-70.step";
    ::ImportFromFile(model8, filePath8, nullptr, nullptr);
    MbSolid* WasherM16 = static_cast<MbSolid*>((MbItem*)model8);

    SPtr<MbSolid> pSolidRes(WasherM16);
    return pSolidRes;
}
SPtr<MbSolid> ParametricModelCreator::GRingA20() {
    ItemSPtr model9;

    path_string  filePath9 = L"C:/Users/Admin/Desktop/������������/������ A20.50 ��� ���� 13942-86.step";
    ::ImportFromFile(model9, filePath9, nullptr, nullptr);
    MbSolid* RingA20 = static_cast<MbSolid*>((MbItem*)model9);

    SPtr<MbSolid> pSolidRes(RingA20);
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