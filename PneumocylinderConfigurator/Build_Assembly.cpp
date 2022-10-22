#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

MbAssembly* ParametricModelCreator::CreatePneumocylinderAssembly(BuildParams params)
{
	MbAssembly* pAsm = new MbAssembly();



    //GCM_system gSys = GCM_CreateSystem();
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    MbSolid* Yaganov1 = LIS_ME22_3_002_01_001();
    MbSolid* Morozova1 = LIS_ME22_3_002_01_002();
    //
    //MbSolid* Zarubin1 = LIS_ME22_3_002_01_003();
    //MbSolid* Shepovalova1 = LIS_ME22_3_002_01_004();
    //MbSolid* Fukina1 = LIS_ME22_3_002_01_005();
    //MbSolid* Aleksanyan1 = LIS_ME22_3_002_01_006();
    //MbSolid* Aleksanyan2 = LIS_ME22_3_002_01_007();
    //MbSolid* Aleksanyan3 = LIS_ME22_3_002_01_008();

    //// Основная сборка
    //MbSolid* Seleznev1 = LIS_ME22_3_002_00_004();
    //Seleznev1->SetColor(191, 255, 110);
    //MbSolid* Vasinkina1 = LIS_ME22_3_002_00_016();/*!!!!!!!!!!!!!Почему именно с 6 на конце детали начинают не отображать грани и вести себя как то не адекватно?!!!!!!!!!!!!!*/

    //Vasinkina1->SetColor(89, 44, 0);
    //MbSolid* Veronika1 = LIS_ME22_3_002_00_005();
    //Veronika1->SetColor(191, 255, 110);
    //MbSolid* Kozir1 = LIS_ME22_3_002_00_011();
    //Kozir1->SetColor(74, 148, 0);
    //MbSolid* Fukina2 = LIS_ME22_3_002_00_015();
    //Fukina2->SetColor(209, 209, 209);
    //MbSolid* Solov1 = LIS_ME22_3_002_00_007();
    //Solov1->SetColor(244, 184, 105);
    //MbSolid* Fukina3 = LIS_ME22_3_002_00_006();/*!!!!!!!!!!!!!Почему именно с 6 на конце детали начинают не отображать грани и вести себя как то не адекватно?!!!!!!!!!!!!!*/
    //Fukina3->SetColor(74, 148, 0);

    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    MbPlacement3D lcs;
    InstanceSPtr Porshen(new MbInstance(*Yaganov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen1(new MbInstance(*Morozova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    /*InstanceSPtr Porshen2(new MbInstance(*Zarubin1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen3(new MbInstance(*Shepovalova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen4(new MbInstance(*Fukina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen5(new MbInstance(*Aleksanyan1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen6(new MbInstance(*Aleksanyan2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen7(new MbInstance(*Aleksanyan3, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));*/

    //Переменные для сборки
   /* InstanceSPtr Sborka(new MbInstance(*Seleznev1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka1(new MbInstance(*Vasinkina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka2(new MbInstance(*Veronika1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka3(new MbInstance(*Kozir1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka4(new MbInstance(*Fukina2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka5(new MbInstance(*Solov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka6(new MbInstance(*Fukina3, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));*/
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    SPtr<MbInstance> PorshenComp(new MbInstance(*Porshen, lcs));
    SPtr<MbInstance> Porshen1Comp(new MbInstance(*Porshen1, lcs));
    //SPtr<MbInstance> Porshen2Comp(new MbInstance(*Porshen2, lcs));
    //SPtr<MbInstance> Porshen3Comp(new MbInstance(*Porshen3, lcs));
    //SPtr<MbInstance> Porshen41Comp(new MbInstance(*Porshen4, lcs));
    //SPtr<MbInstance> Porshen42Comp(new MbInstance(*Porshen4, lcs));
    //SPtr<MbInstance> Porshen43Comp(new MbInstance(*Porshen4, lcs));
    //SPtr<MbInstance> Porshen44Comp(new MbInstance(*Porshen4, lcs));
    //SPtr<MbInstance> Porshen5Comp(new MbInstance(*Porshen5, lcs));
    //SPtr<MbInstance> Porshen6Comp(new MbInstance(*Porshen6, lcs));
    //SPtr<MbInstance> Porshen7Comp(new MbInstance(*Porshen7, lcs));
    ////Переменные для сборки
    //SPtr<MbInstance> SborkaComp(new MbInstance(*Sborka, lcs));
    //SPtr<MbInstance> Sborka1Comp(new MbInstance(*Sborka1, lcs));
    //SPtr<MbInstance> Sborka2Comp(new MbInstance(*Sborka2, lcs));
    //SPtr<MbInstance> Sborka3Comp(new MbInstance(*Sborka3, lcs));
    //SPtr<MbInstance> Sborka4Comp(new MbInstance(*Sborka4, lcs));
    //SPtr<MbInstance> Sborka5Comp(new MbInstance(*Sborka5, lcs));
    //SPtr<MbInstance> Sborka61Comp(new MbInstance(*Sborka6, lcs));
    //SPtr<MbInstance> Sborka62Comp(new MbInstance(*Sborka6, lcs));
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    vector<SPtr<MbInstance>> pair;
    
    pair.push_back(PorshenComp);
    pair.push_back(Porshen1Comp);
    //pair.push_back(Porshen2Comp);
    //pair.push_back(Porshen3Comp);
    //pair.push_back(Porshen41Comp);
    ////pair.push_back(Porshen42Comp);/*!!!!!!!!!!!!!попробуй меня раскоментировать и ты узнаешь что такое безумие!!!!!!!!!!!!!*/
    //pair.push_back(Porshen43Comp);
    //pair.push_back(Porshen44Comp);
    //pair.push_back(Porshen5Comp);
    //pair.push_back(Porshen6Comp);
    //pair.push_back(Porshen7Comp);
    ////Переменные для сборки
    //pair.push_back(SborkaComp);
    //pair.push_back(Sborka1Comp);
    //pair.push_back(Sborka2Comp);
    //pair.push_back(Sborka3Comp);
    //pair.push_back(Sborka4Comp);
    //pair.push_back(Sborka5Comp);
    //pair.push_back(Sborka61Comp);
    //pair.push_back(Sborka62Comp);
    /*-------------------------------------------------------------------------*/



    SPtr<MbAssembly> assm(new MbAssembly(pair));

    assm->SetJournal("C:\\Users\\Admin\\Desktop\\journal.jrn");
	// крышки пневмоцилиндра
	//CreateBase(pAsm, diamDifRatio); // Зарубин
	//CreateBase(pAsm, diamDifRatio); // Зарубин
	
    pAsm->AddItem(*Yaganov1);
    pAsm->AddItem(*Morozova1);
	return pAsm;
}
