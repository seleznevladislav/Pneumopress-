#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

MbAssembly* ParametricModelCreator::CreatePneumocylinderAssembly(BuildParams params)
{
    GCM_system gSys = GCM_CreateSystem();
    SolidSPtr Yaganov1 = LIS_ME22_3_002_01_001();
    SolidSPtr Morozova1 = LIS_ME22_3_002_01_002();
    //SolidSPtr Veronika1 = LIS_ME22_3_002_00_005();
    Morozova1->SetColor(191, 255, 110);
    Morozova1->Move(MbVector3D::xAxis * 100.0);
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    MbPlacement3D lcs;
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    SPtr<MbInstance> PorshenComp(new MbInstance(*Yaganov1, lcs));
    SPtr<MbInstance> Porshen1Comp(new MbInstance(*Morozova1, lcs.Move(MbVector3D::zAxis * 100.0)));
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    vector<SPtr<MbInstance>> pair;
    
    pair.push_back(PorshenComp);
    pair.push_back(Porshen1Comp);
    /*-------------------------------------------------------------------------*/
    //Сигналы и слоты
    //Умные указатели
    MbAssembly* SborkaMainPtr = new MbAssembly(pair);

    //SborkaMainPtr->SetJournal("C:\\Users\\Admin\\Desktop\\journal.jrn");

    double ash1 = 100;
    MtParVariant rar3(ash1);
    //Грани зажима и блока

    MtGeomArgument face1(Yaganov1->GetFace(0), PorshenComp);
    MtGeomArgument face2(Morozova1->GetFace(0), Porshen1Comp);

    
    //Зависимость совмещения между зажимом и блоком
    //SborkaMainPtr->AddConstraint(GCM_COINCIDENT, face111, face222);
    //
    MtGeomConstraint angDim = SborkaMainPtr->AddConstraint(GCM_DISTANCE, face1, face2, rar3);
    SborkaMainPtr->EvaluateConstraints();


	return SborkaMainPtr;
}
