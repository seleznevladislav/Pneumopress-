#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;



class ConstraintSolver
{
    GCM_system m_gcSystem;

public:
    ConstraintSolver()
    {
        m_gcSystem = GCM_CreateSystem();
        //GCM_SetJournal(m_gcSystem, "SampleAnimationOfBending.jrn");
    }

    ~ConstraintSolver()
    {
        GCM_RemoveSystem(m_gcSystem);
    }

    GCM_geom AddGeom(const MbPlacement3D placement)
    {
        return GCM_AddGeom(m_gcSystem, GCM_SolidLCS(placement));
    }
    GCM_geom AddPoint(const MbCartPoint3D cPoint)
    {
        return GCM_AddGeom(m_gcSystem, GCM_Point(cPoint));
    }
    GCM_geom AddLine(const MbCartPoint3D cPoint, const MbVector3D axis)
    {
        return GCM_AddGeom(m_gcSystem, GCM_Line(cPoint, axis));
    }
    GCM_geom AddPlane(const MbCartPoint3D cPoint, const MbVector3D axis)
    {
        return GCM_AddGeom(m_gcSystem, GCM_Plane(cPoint, axis));
    }
    GCM_geom SubGeom(GCM_geom lcs, const MbPlacement3D placement)
    {
        return GCM_SubGeom(m_gcSystem, lcs, GCM_SolidLCS(placement));
    }
    GCM_constraint AddDistance(GCM_geom g1, GCM_geom g2, double dVal, GCM_alignment aVal) {

        return GCM_AddDistance(m_gcSystem, g1, g2, dVal, aVal);
    }
    void AddConstraint(GCM_c_type cType,
        GCM_geom g1,
        GCM_geom g2,
        GCM_alignment aVal = GCM_OPPOSITE,
        GCM_tan_choice tVar = GCM_TAN_POINT)
    {
        GCM_AddBinConstraint(m_gcSystem, cType, g1, g2, aVal, tVar);
    }

    void FixGeom(GCM_geom g)
    {
        GCM_FixGeom(m_gcSystem, g);
    }

    GCM_result Evaluate()
    {
        return GCM_Evaluate(m_gcSystem);
    }

    MbPlacement3D GetNewPlacement3D(GCM_geom g)
    {
        return GCM_Placement(m_gcSystem, g);
    }

    void SetPlacement(GCM_geom g, const MbPlacement3D& place)
    {
        GCM_SetPlacement(m_gcSystem, g, place);
    }
};
MbAssembly* ParametricModelCreator::CreatePneumocylinderAssembly(BuildParams params)
{
#pragma region PARAMS
    
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
   
#pragma endregion
#pragma region Porshen
    //Переменные для подсборки Поршень
    SPtr<MbSolid> Yaganov1 = LIS_ME22_3_002_01_001();
    Yaganov1->SetColor(255, 255, 0);
    SPtr<MbSolid> Morozova1 = LIS_ME22_3_002_01_002();
    Morozova1->SetColor(255, 255, 255);
    SPtr<MbSolid> Zarubin1 = LIS_ME22_3_002_01_003();
    Zarubin1->SetColor(255, 255, 0);
    SPtr<MbSolid> Shepovalova1 = LIS_ME22_3_002_01_004();
    Shepovalova1->SetColor(255, 255, 255);
    //Shepovalova1->SetVisual(0, 0, 0, 0, 0.8, 0, 0);
    Shepovalova1->SetItemName(SimpleName(CASE_ITEMNAME));
    SPtr<MbSolid> Fukina11 = LIS_ME22_3_002_01_005(param_length);
    Fukina11->SetColor(0, 236, 236);
    SPtr<MbSolid> Fukina12 = LIS_ME22_3_002_01_005(param_length);
    Fukina12->SetColor(0, 236, 236);
    SPtr<MbSolid> Fukina13 = LIS_ME22_3_002_01_005(param_length);
    Fukina13->SetColor(0, 236, 236);
    SPtr<MbSolid> Fukina14 = LIS_ME22_3_002_01_005(param_length);
    Fukina14->SetColor(0, 236, 236);
    SPtr<MbSolid> Aleksanyan1 = LIS_ME22_3_002_01_006();
    Aleksanyan1->SetColor(255, 173, 91);
    SPtr<MbSolid> Aleksanyan2 = LIS_ME22_3_002_01_007();
    Aleksanyan2->SetColor(140, 70, 0);
    SPtr<MbSolid> Aleksanyan3 = LIS_ME22_3_002_01_008();
    Aleksanyan3->SetColor(255, 58, 58);
#pragma endregion
#pragma region Sborka
    // Основная сборка
    SPtr<MbSolid> Solov2 = LIS_ME22_3_002_00_001();
    Solov2->SetColor(255, 0, 0);
    SPtr<MbSolid> Vasinkina2 = LIS_ME22_3_002_00_002();
    Vasinkina2->SetColor(0, 255, 255);
    SPtr<MbSolid> Prihodko2 = LIS_ME22_3_002_00_003();
    Prihodko2->SetColor(255, 255, 0);
    SPtr<MbSolid> Seleznev1 = LIS_ME22_3_002_00_004();
    Seleznev1->SetColor(ParametricModelCreator::colorScheme ? RGB(191, 255, 110) : RGB(255, 255, 0));
    //Seleznev1->SetPlacement(MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0), MbVector3D(0, 0, 1), MbVector3D(1, 0, 0)));
    //Seleznev1->SetColor(191, 255, 110);
    SPtr<MbSolid> Veronika1 = LIS_ME22_3_002_00_005();
    Veronika1->SetColor(191, 255, 110);
    SPtr<MbSolid> Fukina31 = LIS_ME22_3_002_00_006();
    Fukina31->SetColor(74, 148, 0);
    SPtr<MbSolid> Fukina32 = LIS_ME22_3_002_00_006();
    Fukina32->SetColor(74, 148, 0);
    SPtr<MbSolid> Solov1 = LIS_ME22_3_002_00_007();
    Solov1->SetColor(244, 184, 105);
    SPtr<MbSolid> Yaganov21 = LIS_ME22_3_002_00_008();
    Yaganov21->SetColor(110, 55, 0);
    SPtr<MbSolid> Yaganov22 = LIS_ME22_3_002_00_008();
    Yaganov22->SetColor(110, 55, 0);
    SPtr<MbSolid> Vasinkina31 = LIS_ME22_3_002_00_010();
    Vasinkina31->SetColor(0, 0, 255);
    SPtr<MbSolid> Vasinkina32 = LIS_ME22_3_002_00_010();
    Vasinkina32->SetColor(0, 0, 255);
    SPtr<MbSolid> Kozir1 = LIS_ME22_3_002_00_011();
    Kozir1->SetColor(74, 148, 0);
    SPtr<MbSolid> Fukina71 = LIS_ME22_3_002_00_012();
    Fukina71->SetColor(0, 255, 0);
    SPtr<MbSolid> Fukina72 = LIS_ME22_3_002_00_012();
    Fukina72->SetColor(0, 255, 0);
    SPtr<MbSolid> Fukina2 = LIS_ME22_3_002_00_015();
    Fukina2->SetColor(209, 209, 209);
    SPtr<MbSolid> Vasinkina1 = LIS_ME22_3_002_00_016();
    Vasinkina1->SetColor(89, 44, 0);

    SPtr<MbSolid> Fukina6 = LIS_ME22_3_002_03_001();
    Fukina6->SetColor(220, 220, 220);
    SPtr<MbSolid> Fukina5 = LIS_ME22_3_002_04_001();
    Fukina5->SetColor(220, 220, 220);
#pragma endregion
#pragma region Shatun
    // Шатун
    SPtr<MbSolid> Bychkov1 = LIS_ME22_3_002_02_001();
    Bychkov1->SetColor(224, 224, 224);
    SPtr<MbSolid> Morozova2 = LIS_ME22_3_002_02_002();
    Morozova2->SetColor(230, 230, 230);
    SPtr<MbSolid> Fukina4 = LIS_ME22_3_002_02_003();
    Fukina4->SetColor(240, 240, 240);
    SPtr<MbSolid> Prihodko11 = LIS_ME22_3_002_02_004();
    Prihodko11->SetColor(255, 165, 165);
    SPtr<MbSolid> Prihodko12 = LIS_ME22_3_002_02_004();
    Prihodko12->SetColor(255, 165, 165);
#pragma endregion
#pragma region GOST
    // Шатун
    SPtr<MbSolid> WasherM20 = GWasherM20();

#pragma endregion

    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
#pragma region Porshen InstanceSPtr
    MbPlacement3D lcs;
    InstanceSPtr Porshen1(new MbInstance(*Yaganov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen2(new MbInstance(*Morozova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen3(new MbInstance(*Zarubin1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen4(new MbInstance(*Shepovalova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen51(new MbInstance(*Fukina11, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen52(new MbInstance(*Fukina12, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen53(new MbInstance(*Fukina13, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen54(new MbInstance(*Fukina14, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen6(new MbInstance(*Aleksanyan1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen7(new MbInstance(*Aleksanyan2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen8(new MbInstance(*Aleksanyan3, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
#pragma endregion

    //Переменные для сборки
    InstanceSPtr Sborka1(new MbInstance(*Solov2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka2(new MbInstance(*Vasinkina2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka3(new MbInstance(*Prihodko2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka4(new MbInstance(*Seleznev1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka5(new MbInstance(*Veronika1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka61(new MbInstance(*Fukina31, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka62(new MbInstance(*Fukina32, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka7(new MbInstance(*Solov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka81(new MbInstance(*Yaganov21, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka82(new MbInstance(*Yaganov22, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka101(new MbInstance(*Vasinkina31, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka102(new MbInstance(*Vasinkina32, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka11(new MbInstance(*Kozir1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka121(new MbInstance(*Fukina71, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka122(new MbInstance(*Fukina72, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka15(new MbInstance(*Fukina2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka16(new MbInstance(*Vasinkina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Oc1(new MbInstance(*Fukina6, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Oc2(new MbInstance(*Fukina5, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
#pragma region Shatun InstanceSPtr
    InstanceSPtr Shatun1(new MbInstance(*Bychkov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun2(new MbInstance(*Morozova2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun3(new MbInstance(*Fukina4, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun41(new MbInstance(*Prihodko11, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun42(new MbInstance(*Prihodko12, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
#pragma endregion
    /*-------------------------------------------------------------------------*/
#pragma region Porshen SPtr<MbInstance>
    //Переменные для подсборки Поршень
    SPtr<MbInstance> Porshen1Comp(new MbInstance(*Porshen1, lcs));
    SPtr<MbInstance> Porshen2Comp(new MbInstance(*Porshen2, lcs));
    SPtr<MbInstance> Porshen3Comp(new MbInstance(*Porshen3, lcs));
    SPtr<MbInstance> Porshen4Comp(new MbInstance(*Porshen4, lcs));
    SPtr<MbInstance> Porshen51Comp(new MbInstance(*Porshen51, lcs));
    SPtr<MbInstance> Porshen52Comp(new MbInstance(*Porshen52, lcs));
    SPtr<MbInstance> Porshen53Comp(new MbInstance(*Porshen53, lcs));
    SPtr<MbInstance> Porshen54Comp(new MbInstance(*Porshen54, lcs));
    SPtr<MbInstance> Porshen6Comp(new MbInstance(*Porshen6, lcs));
    SPtr<MbInstance> Porshen7Comp(new MbInstance(*Porshen7, lcs));
    SPtr<MbInstance> Porshen8Comp(new MbInstance(*Porshen8, lcs));
#pragma endregion
    //Переменные для сборки
    SPtr<MbInstance> Sborka1Comp(new MbInstance(*Sborka1, lcs));
    SPtr<MbInstance> Sborka2Comp(new MbInstance(*Sborka2, lcs));
    SPtr<MbInstance> Sborka3Comp(new MbInstance(*Sborka3, lcs));
    SPtr<MbInstance> Sborka4Comp(new MbInstance(*Sborka4, lcs));
    SPtr<MbInstance> Sborka5Comp(new MbInstance(*Sborka5, lcs));
    SPtr<MbInstance> Sborka61Comp(new MbInstance(*Sborka61, lcs));
    SPtr<MbInstance> Sborka62Comp(new MbInstance(*Sborka62, lcs));
    SPtr<MbInstance> Sborka7Comp(new MbInstance(*Sborka7, lcs));
    SPtr<MbInstance> Sborka81Comp(new MbInstance(*Sborka81, lcs));
    SPtr<MbInstance> Sborka82Comp(new MbInstance(*Sborka82, lcs));
    SPtr<MbInstance> Sborka101Comp(new MbInstance(*Sborka101, lcs));
    SPtr<MbInstance> Sborka102Comp(new MbInstance(*Sborka102, lcs));
    SPtr<MbInstance> Sborka11Comp(new MbInstance(*Sborka11, lcs));
    SPtr<MbInstance> Sborka121Comp(new MbInstance(*Sborka121, lcs));
    SPtr<MbInstance> Sborka122Comp(new MbInstance(*Sborka122, lcs));
    SPtr<MbInstance> Sborka15Comp(new MbInstance(*Sborka15, lcs));
    SPtr<MbInstance> Sborka16Comp(new MbInstance(*Sborka16, lcs));
    SPtr<MbInstance> Oc1Comp(new MbInstance(*Oc1, lcs));
    SPtr<MbInstance> Oc2Comp(new MbInstance(*Oc2, lcs));
#pragma region Shatun SPtr<MbInstance>
    SPtr<MbInstance> Shatun1Comp(new MbInstance(*Shatun1, lcs));
    SPtr<MbInstance> Shatun2Comp(new MbInstance(*Shatun2, lcs));
    SPtr<MbInstance> Shatun3Comp(new MbInstance(*Shatun3, lcs));
    SPtr<MbInstance> Shatun41Comp(new MbInstance(*Shatun41, lcs));
    SPtr<MbInstance> Shatun42Comp(new MbInstance(*Shatun42, lcs));
#pragma endregion
#pragma region GOST SPtr<MbInstance>
    SPtr<MbInstance> WasherM20Comp1(new MbInstance(*WasherM20, lcs));
#pragma endregion

    //Переменные для подсборки Поршень
    vector<SPtr<MbInstance>> pair;
    pair.push_back(Porshen1Comp);
    pair.push_back(Porshen2Comp);
    pair.push_back(Porshen3Comp);
    pair.push_back(Porshen4Comp);
    pair.push_back(Porshen51Comp);
    pair.push_back(Porshen52Comp);
    pair.push_back(Porshen53Comp);
    pair.push_back(Porshen54Comp);
    /*
    pair.push_back(Porshen6Comp);
    pair.push_back(Porshen7Comp);
    pair.push_back(Porshen8Comp);
    */
    //Переменные для Сборки
    pair.push_back(Sborka1Comp);
    pair.push_back(Sborka2Comp);
    pair.push_back(Sborka3Comp);
    pair.push_back(Sborka4Comp);
    pair.push_back(Sborka5Comp);
    pair.push_back(Sborka61Comp);
    pair.push_back(Sborka62Comp);
    pair.push_back(Sborka7Comp);
    pair.push_back(Sborka81Comp);
    pair.push_back(Sborka82Comp);
    pair.push_back(Sborka101Comp);
    pair.push_back(Sborka102Comp);
    pair.push_back(Sborka11Comp);
    pair.push_back(Sborka121Comp);
    pair.push_back(Sborka122Comp);
    pair.push_back(Sborka15Comp);
    pair.push_back(Sborka16Comp);
    pair.push_back(Oc1Comp);
    pair.push_back(Oc2Comp);
    //Переменные для Шатуна
    pair.push_back(Shatun1Comp);
    pair.push_back(Shatun2Comp);
    pair.push_back(Shatun3Comp);
    pair.push_back(Shatun41Comp);
    pair.push_back(Shatun42Comp);


    pair.push_back(WasherM20Comp1);

    MbAssembly* assm = new MbAssembly(pair);

#pragma region Sborka - Stoika and Opora
    double Val1 = 0;
    MtParVariant Arg1(Val1);
    double Val11 = 164;
    MtParVariant Arg11(Val11);
    //Реализаця жесткой заделки для опоры и цилиндра
    MtGeomArgument PFT1(Seleznev1->GetFace(13), Sborka4Comp);
    MtGeomArgument PFT2(Veronika1->GetFace(15), Sborka5Comp);
    assm->AddConstraint(GCM_DISTANCE, PFT2, PFT1, Arg11);//<!!!Жесткая заделка опоры>
    //грани между для прижатия опоры к стойке
    MtGeomArgument PFT3(Seleznev1->GetFace(60), Sborka4Comp);
    MtGeomArgument PFT4(Veronika1->GetFace(36), Sborka5Comp);
    assm->AddConstraint(GCM_DISTANCE, PFT4, PFT3, Arg1);
    //Зависимость между внутренними гранями для центрирования
    MtGeomArgument PFT5(Seleznev1->GetFace(82), Sborka4Comp);
    MtGeomArgument PFT6(Veronika1->GetFace(53), Sborka5Comp);
    assm->AddConstraint(GCM_DISTANCE, PFT6, PFT5, Arg1);
#pragma endregion
#pragma region Sborka - Opora and Kronshteins
    double Val12 = 0;
    MtParVariant Arg12(Val12);
    //Плоскости между
    MtGeomArgument PFO1(Veronika1->GetFace(2), Sborka5Comp);
    MtGeomArgument PFO2(Veronika1->GetFace(3), Sborka5Comp);

    MtGeomArgument PFO3(Fukina31->GetFace(1), Sborka61Comp);
    MtGeomArgument PFO4(Fukina32->GetFace(0), Sborka62Comp);

    assm->AddConstraint(GCM_DISTANCE, PFO3, PFO1, Arg12);
    assm->AddConstraint(GCM_DISTANCE, PFO4, PFO2, Arg12);
    //Отверстия 
    MtGeomArgument PHO1(Veronika1->GetFace(4), Sborka5Comp);
    MtGeomArgument PHO2(Fukina32->GetFace(4), Sborka62Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHO2, PHO1);

    MtGeomArgument PHO3(Veronika1->GetFace(8), Sborka5Comp);
    MtGeomArgument PHO4(Fukina32->GetFace(3), Sborka62Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHO4, PHO3);

    MtGeomArgument PHO5(Veronika1->GetFace(9), Sborka5Comp);
    MtGeomArgument PHO6(Fukina31->GetFace(3), Sborka61Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHO6, PHO5);

    MtGeomArgument PHO7(Veronika1->GetFace(5), Sborka5Comp);
    MtGeomArgument PHO8(Fukina31->GetFace(4), Sborka61Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHO8, PHO7);
#pragma endregion
#pragma region Sborka - Kronshteins and Blok

    double Val13 = -3.5;
    MtParVariant Arg13(Val13);
    //Плоскость
    MtGeomArgument PFP1(Yaganov1->GetFace(29), Porshen1Comp);
    MtGeomArgument PFP2(Fukina32->GetFace(1), Sborka62Comp);

    assm->AddConstraint(GCM_DISTANCE, PFP1, PFP2, Arg13);

    //Отверстиe
    MtGeomArgument PHP1(Yaganov1->GetFace(23), Porshen1Comp);
    MtGeomArgument PHP2(Fukina32->GetFace(14), Sborka62Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHP1, PHP2, 1);//<!!! xПеревернули>
    //<!!! свободно вращается сборка>
    
#pragma endregion
#pragma region Sborka - Stol and Stoika
    double Val7 = 0;
    MtParVariant Arg7(Val7);
    //Плоскости между
    MtGeomArgument PFR1(Seleznev1->GetFace(13), Sborka4Comp);
    MtGeomArgument PFR2(Vasinkina1->GetFace(1), Sborka16Comp);
    assm->AddConstraint(GCM_DISTANCE, PFR1, PFR2, Arg7);
    //Центральное отверстие
    MtGeomArgument PHR1(Seleznev1->GetFace(64), Sborka4Comp);
    MtGeomArgument PHR2(Vasinkina1->GetFace(12), Sborka16Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHR1, PHR2);
    //Боковое отверстие для выравнивания
    MtGeomArgument PHR3(Seleznev1->GetFace(55), Sborka4Comp);
    MtGeomArgument PHR4(Vasinkina1->GetFace(14), Sborka16Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHR3, PHR4);
#pragma endregion
#pragma region Porshen - Krishki and Cylinder
//Параметр расстояния от крышек до цилиндра
    double Val4 = 0;
    MtParVariant Arg4(Val4);

    //Цилиндр и 2 крышки
    MtGeomArgument face1(Shepovalova1->GetFace(4), Porshen4Comp);
    MtGeomArgument face2(Yaganov1->GetFace(22), Porshen1Comp);
    assm->AddConstraint(GCM_DISTANCE, face1, face2, Arg4);

    MtGeomArgument hole2(Shepovalova1->GetFace(3), Porshen4Comp);
    MtGeomArgument hole3(Yaganov1->GetFace(28), Porshen1Comp);
    assm->AddConstraint(GCM_CONCENTRIC, hole2, hole3);

    MtGeomArgument face3(Shepovalova1->GetFace(2), Porshen4Comp);
    MtGeomArgument face4(Zarubin1->GetFace(17), Porshen3Comp);

    assm->AddConstraint(GCM_DISTANCE, face4, face3, Arg4);

    MtGeomArgument hole4(Shepovalova1->GetFace(0), Porshen4Comp);
    MtGeomArgument hole5(Zarubin1->GetFace(26), Porshen3Comp);
    //Зависимость консентричности между крышками и цилиндром

    assm->AddConstraint(GCM_CONCENTRIC, hole5, hole4);

#pragma endregion
#pragma region Porshen - Krishka and Shtoki
    //Параметр расстояния от крышек до цилиндра
    double Val2 = -14;
    MtParVariant Arg2(Val2);
    //Грань цилиндра штока
    MtGeomArgument AR1(Fukina11->GetFace(0), Porshen51Comp);
    MtGeomArgument AR2(Fukina12->GetFace(0), Porshen52Comp);
    MtGeomArgument AR3(Fukina13->GetFace(0), Porshen53Comp);
    MtGeomArgument AR4(Fukina14->GetFace(0), Porshen54Comp);
    //отверстия в крышке
    MtGeomArgument BR1(Yaganov1->GetFace(13), Porshen1Comp);
    MtGeomArgument BR2(Yaganov1->GetFace(14), Porshen1Comp);
    MtGeomArgument BR3(Yaganov1->GetFace(15), Porshen1Comp);
    MtGeomArgument BR4(Yaganov1->GetFace(16), Porshen1Comp);
    //Верхняя грань шток
    MtGeomArgument AR11(Fukina11->GetFace(1), Porshen51Comp);
    MtGeomArgument AR22(Fukina12->GetFace(1), Porshen52Comp);
    MtGeomArgument AR33(Fukina13->GetFace(1), Porshen53Comp);
    MtGeomArgument AR44(Fukina14->GetFace(1), Porshen54Comp);
    //Верхняя грань Крышки
    MtGeomArgument BR11(Yaganov1->GetFace(0), Porshen1Comp);
    //Зависимость расстояние между штоком и крышкой 
    assm->AddConstraint(GCM_DISTANCE, AR11, BR11, Arg2);
    assm->AddConstraint(GCM_DISTANCE, AR22, BR11, Arg2);
    assm->AddConstraint(GCM_DISTANCE, AR33, BR11, Arg2);
    assm->AddConstraint(GCM_DISTANCE, AR44, BR11, Arg2);
    //Консентричность штоков
    assm->AddConstraint(GCM_CONCENTRIC, AR1, BR1);
    assm->AddConstraint(GCM_CONCENTRIC, AR2, BR2);
    assm->AddConstraint(GCM_CONCENTRIC, AR3, BR3);
    assm->AddConstraint(GCM_CONCENTRIC, AR4, BR4);
#pragma endregion
#pragma region Porshen - Block and Zazhim
    double Val3 = 0;
    MtParVariant Arg3(Val3);

    MtGeomArgument PF1(Morozova1->GetFace(0), Porshen2Comp);
    MtGeomArgument PF2(Yaganov1->GetFace(0), Porshen1Comp);
    assm->AddConstraint(GCM_DISTANCE, PF1, PF2, Arg3);

    MtGeomArgument PH1(Morozova1->GetFace(3), Porshen2Comp);
    MtGeomArgument PH2(Shepovalova1->GetFace(3), Porshen4Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PH1, PH2);

    MtGeomArgument PH3(Yaganov1->GetFace(13), Porshen1Comp);
    MtGeomArgument PH4(Shepovalova1->GetFace(1), Porshen4Comp);
    //assm->AddConstraint(GCM_CONCENTRIC, PH3, PH4);<!!! Не хатает зависимости совмещения зажима и блока по 4 отверстиям для выравнивания>
#pragma endregion
#pragma region Shatun - Shtok and Porshen
    double Val22 = 0;
    MtParVariant Arg22(Val22);
    //Плоскость
    MtGeomArgument PFL1(Bychkov1->GetFace(16), Shatun1Comp);
    MtGeomArgument PFL2(Morozova2->GetFace(6), Shatun2Comp);

    assm->AddConstraint(GCM_DISTANCE, PFL1, PFL2, Arg22);

    //Отверстие
    MtGeomArgument PHL1(Bychkov1->GetFace(14), Shatun1Comp);
    MtGeomArgument PHL2(Morozova2->GetFace(4), Shatun2Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHL1, PHL2, 1); //<!!! Переворачиваем поршень чтобы стояло правильно>
#pragma endregion
#pragma region Shatun - Porshen and 2 rings
    double Val20 = 0;
    MtParVariant Arg20(Val20);
    //Плоскость
    MtGeomArgument PFJ1(Morozova2->GetFace(13), Shatun2Comp);
    MtGeomArgument PFJ2(Prihodko11->GetFace(0), Shatun41Comp);
    MtGeomArgument PFJ3(Morozova2->GetFace(5), Shatun2Comp);
    MtGeomArgument PFJ4(Prihodko12->GetFace(0), Shatun42Comp);

    assm->AddConstraint(GCM_DISTANCE, PFJ2, PFJ1, Arg20);
    assm->AddConstraint(GCM_DISTANCE, PFJ4, PFJ3, Arg20);
    //Отверстие
    MtGeomArgument PHJ1(Morozova2->GetFace(3), Shatun2Comp);
    MtGeomArgument PHJ2(Prihodko11->GetFace(12), Shatun41Comp);
    MtGeomArgument PHJ3(Prihodko12->GetFace(12), Shatun42Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHJ2, PHJ1);
    assm->AddConstraint(GCM_CONCENTRIC, PHJ3, PHJ1);
#pragma endregion
#pragma region Shatun - Porshen and Cylinder 1 constraint
    double Val23 = 0;
    MtParVariant Arg23(Val23);

    //Отверстие (СОЕДИНЕНИЕ ПОРШНЯ И ЦИЛИНДРА)
    MtGeomArgument PHZ1(Morozova2->GetFace(3), Shatun2Comp);
    MtGeomArgument PHZ2(Shepovalova1->GetFace(3), Porshen4Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHZ1, PHZ2, -1);
#pragma endregion
#pragma region Shatun - Porshen and kolpachok
    double Val15 = 0;
    MtParVariant Arg15(Val15);
    MtGeomArgument PlaneС1(Fukina4->GetFace(4), Shatun3Comp);
    MtGeomArgument PlaneС2(Morozova2->GetFace(6), Shatun2Comp);
    assm->AddConstraint(GCM_DISTANCE, PlaneС1, PlaneС2, Arg15);
    MtGeomArgument HoleС1(Fukina4->GetFace(0), Shatun3Comp);
    MtGeomArgument HoleС2(Morozova2->GetFace(4), Shatun2Comp);
    assm->AddConstraint(GCM_CONCENTRIC, HoleС1, HoleС2);
#pragma endregion
#pragma region Sborka - Napravlyachaya and Opora
    ////Параметр расстояния от блока до втулки2
    double Val9 = 0;
    MtParVariant Arg9(Val9);

    MtGeomArgument PlaneL(Veronika1->GetFace(12), Sborka5Comp);
    MtGeomArgument PlaneL1(Solov1->GetFace(4), Sborka7Comp);

    assm->AddConstraint(GCM_DISTANCE, PlaneL1, PlaneL, Arg9);
    MtGeomArgument HoleL(Veronika1->GetFace(43), Sborka5Comp);
    MtGeomArgument HoleL1(Solov1->GetFace(10), Sborka7Comp);
    assm->AddConstraint(GCM_CONCENTRIC, HoleL1, HoleL, 1);
    
    MtGeomArgument HoleL2(Vasinkina1->GetFace(0), Sborka16Comp);
    MtGeomArgument HoleL12(Solov1->GetFace(7), Sborka7Comp);
    assm->AddConstraint(GCM_ANGLE, HoleL12, HoleL2, 0 * M_PI / 180);
#pragma endregion
#pragma region Sborka - Polzun and Napravlyachaya
    double Val14 = 0;
    MtParVariant Arg14(Val14);
    
    double Val151 = 143;
    MtParVariant Arg151(Val151);
    //Плоскость Нижняя
    MtGeomArgument PFA3(Vasinkina2->GetFace(23), Sborka2Comp);
    MtGeomArgument PFA4(Seleznev1->GetFace(13), Sborka4Comp);
    //assm->AddConstraint(GCM_DISTANCE, PFA3, PFA4, Arg151);//<!!! Жесткая закрепка ползуна>
    
    MtGeomArgument PFA5(Solov1->GetFace(14), Sborka7Comp);//24
    MtGeomArgument PFA6(Vasinkina2->GetFace(18), Sborka2Comp);//12
    assm->AddConstraint(GCM_DISTANCE, PFA6, PFA5, Arg14);//Тут крч совмещение пхд надо будет убрать !!!!! тк мешает сделать концентричность
    
    MtGeomArgument PFA1(Vasinkina2->GetFace(13), Sborka2Comp);//17
    MtGeomArgument PFA2(Solov1->GetFace(21), Sborka7Comp);
    assm->AddConstraint(GCM_DISTANCE, PFA2, PFA1, Arg14);
    assm->AddConstraint(GCM_ANGLE, PFA2, PFA1, 180* M_PI/180);
#pragma endregion
#pragma region Sborka - Polzun and Skolzyachie
    double Val16 = 0.5;
    MtParVariant Arg16(Val16);

    MtGeomArgument PHS1(Vasinkina32->GetFace(23), Sborka102Comp);
    MtGeomArgument PHS2(Vasinkina2->GetFace(22), Sborka2Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHS1, PHS2, 1);//<!!! Разворачиваем скользящий>
 
    MtGeomArgument PHS3(Vasinkina31->GetFace(23), Sborka101Comp);
    MtGeomArgument PHS4(Vasinkina32->GetFace(23), Sborka102Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHS3, PHS4);
#pragma endregion
#pragma region Sborka - Skolzyachie and Tyaga
    double Val17 = 0;
    MtParVariant Arg17(Val17);
    //Плоскость между первым
    MtGeomArgument PFD1(Prihodko2->GetFace(8), Sborka3Comp);
    MtGeomArgument PFD2(Vasinkina32->GetFace(1), Sborka102Comp);
    assm->AddConstraint(GCM_DISTANCE, PFD1, PFD2, Arg17);
    //Отверстие первого
    MtGeomArgument PHD1(Vasinkina32->GetFace(2), Sborka102Comp);
    MtGeomArgument PHD2(Prihodko2->GetFace(16), Sborka3Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHD1, PHD2, 1);//<!!! Разворачиваем Тягу>
    //Плоскость между Вторым
    MtGeomArgument PFD3(Prihodko2->GetFace(6), Sborka3Comp);
    MtGeomArgument PFD4(Vasinkina31->GetFace(22), Sborka101Comp);
    assm->AddConstraint(GCM_DISTANCE, PFD3, PFD4, Arg17);
    //Отверстие Второго
    MtGeomArgument PHD3(Vasinkina31->GetFace(2), Sborka101Comp);//23
    MtGeomArgument PHD4(Prihodko2->GetFace(16), Sborka3Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHD3, PHD4);
#pragma endregion
#pragma region Sborka - Tyaga and Vilka
    double Val18 = 0;
    MtParVariant Arg18(Val18);
    //Плоскость
    MtGeomArgument PFF1(Prihodko2->GetFace(4), Sborka3Comp);
    MtGeomArgument PFF2(Solov2->GetFace(4), Sborka1Comp);
    assm->AddConstraint(GCM_DISTANCE, PFF2, PFF1, Arg18);
    //Отверстие
    MtGeomArgument PHF1(Solov2->GetFace(11), Sborka1Comp);
    MtGeomArgument PHF2(Prihodko2->GetFace(11), Sborka3Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHF2, PHF1);
#pragma endregion
#pragma region Sborka - Vilka and Gaika
    double Val19 = 0;
    MtParVariant Arg19(Val19);
    //Плоскость
    MtGeomArgument PFH1(Solov2->GetFace(27), Sborka1Comp);
    MtGeomArgument PFH2(WasherM20->GetFace(0), WasherM20Comp1);
    assm->AddConstraint(GCM_DISTANCE, PFH1, PFH2, Arg19);
    //Отверстие 
    MtGeomArgument PHH1(Solov2->GetFace(20), Sborka1Comp);
    MtGeomArgument PHH2(WasherM20->GetFace(8), WasherM20Comp1);
    assm->AddConstraint(GCM_CONCENTRIC, PHH1, PHH2);
#pragma endregion
#pragma region Sborka - Vtulka Samosmaz and Kronshteins
    double Val24 = 0;
    MtParVariant Arg24(Val24);

    MtGeomArgument PFX1(Yaganov1->GetFace(29), Porshen1Comp);
    MtGeomArgument PFX2(Yaganov21->GetFace(1), Sborka81Comp);
    MtGeomArgument PFX3(Yaganov1->GetFace(32), Porshen1Comp);
    MtGeomArgument PFX4(Yaganov22->GetFace(1), Sborka82Comp);
    //Жесткий хардкод, никак иначе
    //assm->AddConstraint(GCM_DISTANCE, PFX3, PFX4, Arg24);
    //assm->AddConstraint(GCM_COINCIDENT, PFX2, PFX1, 1);
    assm->AddConstraint(GCM_COINCIDENT, PFX3, PFX4, 1);
    MbAxis3D axxVert(MbVector3D(1, 0, 0));
    Yaganov21->Rotate(axxVert, M_PI / 2);
    assm->AddConstraint(GCM_DISTANCE, PFX2, PFX4, -146.0);
    //assm->AddConstraint(GCM_ANGLE, PFX2, PFX4, (180)* M_PI / 180);//Градус 10
    MtGeomArgument PHX1(Yaganov1->GetFace(23), Porshen1Comp);
    MtGeomArgument PHX2(Yaganov21->GetFace(3), Sborka81Comp);
    MtGeomArgument PHX3(Yaganov21->GetFace(2), Sborka81Comp);
    MtGeomArgument PHX4(Yaganov22->GetFace(3), Sborka82Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHX2, PHX1);
    assm->AddConstraint(GCM_CONCENTRIC, PHX3, PHX4);
#pragma endregion
#pragma region Sborka - Regulir and stoika
    double Val45 = 0;
    MtParVariant Arg45(Val45);
    //Плоскость между
    MtGeomArgument PFY1(Seleznev1->GetFace(42), Sborka4Comp);
    MtGeomArgument PFY2(Kozir1->GetFace(4), Sborka11Comp);
    assm->AddConstraint(GCM_DISTANCE, PFY2, PFY1, Arg9);
    //Первое отверстие
    MtGeomArgument PHY1(Seleznev1->GetFace(66), Sborka4Comp);
    MtGeomArgument PHY2(Kozir1->GetFace(12), Sborka11Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHY1, PHY2, 0);//<!!! Перевернули кронштейн>
    //Второе отверстие
    MtGeomArgument PHY3(Seleznev1->GetFace(65), Sborka4Comp);
    MtGeomArgument PHY4(Kozir1->GetFace(0), Sborka11Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHY3, PHY4, 0);//<!!! Перевернули кронштейн>
#pragma endregion
#pragma region Sborka - Regulir and BoltKrep
    double Val10 = 0;
    MtParVariant Arg10(Val10);
    //Плоскость между
    MtGeomArgument PFU1(Fukina2->GetFace(9), Sborka15Comp);
    MtGeomArgument PFU2(Kozir1->GetFace(1), Sborka11Comp);
    assm->AddConstraint(GCM_DISTANCE, PFU1, PFU2, Arg10);
    //Отверстие 
    MtGeomArgument PHU1(Fukina2->GetFace(10), Sborka15Comp);
    MtGeomArgument PHU2(Kozir1->GetFace(10), Sborka11Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHU1, PHU2, 0);//<!!! Перевернули болт крепежный>
#pragma endregion
#pragma region Sborka - Block and Kolpachek -virovnyali-
    MtGeomArgument PFV1(Yaganov1->GetFace(12), Porshen1Comp);
    MtGeomArgument PFV2(Zarubin1->GetFace(0), Porshen3Comp);
    assm->AddConstraint(GCM_COINCIDENT, PFV1, PFV2);
#pragma endregion
#pragma region Sborka - Vilku and Cylinder -virovnyali-
    //СОЕДИНИЛИ ВИЛКУ ЦЕНТР С ЦИЛИНДРОМ НЕ ОТМЕНЯТЬ
    MtGeomArgument hole232332(Shepovalova1->GetFace(3), Porshen4Comp);
    MtGeomArgument hole2323321(Solov2->GetFace(20), Sborka1Comp);
    assm->AddConstraint(GCM_CONCENTRIC, hole232332, hole2323321);

    double Val21 = 0;
    MtParVariant Arg21(Val21);
    //Плоскость
    MtGeomArgument PFK1(Bychkov1->GetFace(0), Shatun1Comp);
    MtGeomArgument PFK2(WasherM20->GetFace(10), WasherM20Comp1);

    assm->AddConstraint(GCM_DISTANCE, PFK1, PFK2, Arg21);
#pragma endregion
#pragma region Sborka - Shtift16
    double Val46 = 0;
    MtParVariant Arg46(Val46);//5//8
    //0-9
    MtGeomArgument PFN1(Vasinkina31->GetFace(0), Sborka101Comp);
    MtGeomArgument PFN2(Fukina71->GetFace(8), Sborka121Comp);
    assm->AddConstraint(GCM_DISTANCE, PFN1, PFN2, Arg46);

    MtGeomArgument PFN3(Vasinkina31->GetFace(0), Sborka101Comp);
    MtGeomArgument PFN4(Fukina72->GetFace(8), Sborka122Comp);
    assm->AddConstraint(GCM_DISTANCE, PFN3, PFN4, Arg46);

    //MtGeomArgument PHN1(Vasinkina31->GetFace(22), Sborka101Comp);
    MtGeomArgument PHN1(Prihodko2->GetFace(16), Sborka3Comp);
    MtGeomArgument PHN2(Fukina71->GetFace(5), Sborka121Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHN1, PHN2,1);
    
    MtGeomArgument PHN3(Vasinkina2->GetFace(22), Sborka2Comp);
    MtGeomArgument PHN4(Fukina72->GetFace(5), Sborka122Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHN3, PHN4,1);
#pragma endregion
#pragma region Test 
    //7 and 1
    //GCM_system solver = GCM_CreateSystem();


    //GCM_geom lcs1_fixed =
    //    GCM_AddGeom(solver, GCM_SolidLCS(Sborka16Comp->GetPlacement()));
    //GCM_geom plane_lcs1_fixed = GCM_SubGeom(
    //    solver, lcs1_fixed,
    //    GCM_Plane(MbCartPoint3D(0.0, 100.0, 0.0), MbVector3D(0.0, 1.0, 0.0)));

    //GCM_geom lcs2_fixed =
    //    GCM_AddGeom(solver, GCM_SolidLCS(Oc2Comp->GetPlacement()));
    //GCM_geom plane_lcs2_fixed = GCM_SubGeom(
    //    solver, lcs2_fixed,
    //    GCM_Plane(MbCartPoint3D(0.0, 0.0, 0.0), MbVector3D(1.0, 0.0, 0.0)));

    //GCM_constraint distance5 = GCM_AddDistance(
    //    solver, plane_lcs1_fixed, plane_lcs2_fixed, 20., GCM_NO_ALIGNMENT);
#pragma endregion
#pragma region Sborka - Oc dlinnaya
//7 and 1
    double Val47 = -462;
    MtParVariant Arg47(Val47);
    double Val48 = -161;
    MtParVariant Arg48(Val48);

    MtGeomArgument PFM1(Fukina5->GetFace(1), Oc2Comp);
    MtGeomArgument PFM2(Seleznev1->GetFace(72), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, PFM1, PFM2, Arg47);

    MtGeomArgument PFM3(Fukina5->GetFace(7), Oc2Comp);
    MtGeomArgument PFM4(Seleznev1->GetFace(41), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, PFM3, PFM4, Arg48);

    MtGeomArgument PFM5(Fukina5->GetFace(11), Oc2Comp);
    MtGeomArgument PFM6(Seleznev1->GetFace(58), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, PFM5, PFM6, -12.0);

#pragma endregion
   //test
    //23
    MtGeomArgument PHM1(Vasinkina2->GetFace(23), Sborka2Comp);
    MtGeomArgument PHM2(Vasinkina1->GetFace(0), Sborka16Comp);
    //assm->AddConstraint(GCM_DISTANCE, PHM1, PHM2, 143.0); много
    //assm->AddConstraint(GCM_DISTANCE, PHM1, PHM2, 80.0);
    assm->AddConstraint(GCM_ANGLE, PHM1, PHM2, 180 * M_PI / 180);

    MtGeomArgument PHM3(Morozova2->GetFace(0), Shatun2Comp);
    MtGeomArgument PHM4(Zarubin1->GetFace(17), Porshen3Comp);
    //assm->AddConstraint(GCM_DISTANCE, PHM3, PHM4, 30.0);

    MtGeomArgument PHM5(Fukina5->GetFace(0), Oc2Comp);
    MtGeomArgument PHM6(Prihodko2->GetFace(15), Sborka3Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHM5, PHM6, 0);
    /*----------------------------------Соединение оси и цапфы---------------------------------------*/
    /*MtGeomArgument PlaneOporaC5(Veronika1->GetFace(38), Porshen9Comp);
    MtGeomArgument PlaneOpora5(Veronika1->GetFace(3), Porshen9Comp);
    MtGeomArgument PlaneAxeC1(Fukina5->GetFace(5), Porshen10Comp);
    MtGeomArgument PlaneAxe1(Fukina5->GetFace(8), Porshen10Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PlaneOporaC5, PlaneAxeC1);
    assm->AddConstraint(GCM_COINCIDENT, PlaneOpora5, PlaneAxe1);*/

    // Это просто так добавил как у нас была раньше реализована анимация
    //const clock_t duration = CLOCKS_PER_SEC * 4; // 2 seconds
    //const double delta = CLOCKS_PER_SEC / 24;
    //const clock_t startClock = std::clock();
    //while (std::clock() < (startClock + duration))
    //{
    //    const clock_t t = std::clock();
    //    assm->ChangeDimension(angDim, (t - startClock) * 200 / duration);
    //    assm->ChangeDimension(angDim2, (t - startClock) * 200 / duration);
    //    assm->ChangeDimension(angDim3, (t - startClock) * 200 / duration);
    //    assm->ChangeDimension(angDim4, (t - startClock) * 200 / duration);
    //    assm->ChangeDimension(angDim5, (t - startClock) * 200 / duration);

    //    while (std::clock() - t < delta); // delay
    //    /* MbAxis3D axVert(MbVector3D(0, 1, 0));
    //     assm->Rotate(axVert, M_PI / 2);
    //     MbAxis3D axVert2(MbVector3D(1, 0, 0));
    //     assm->Rotate(axVert2, -M_PI / 2);
    //     MbAxis3D axVert3(MbVector3D(0, 0, 1));
    //     assm->Rotate(axVert3, M_PI);*/
    //    viewManager->RefreshModel();
    //    viewManager->ShowModel();
    //}
        // Решение ограничений

    //Angle for Block
    MtGeomArgument face5(Yaganov1->GetFace(8), Porshen1Comp);
    MtGeomArgument face6(Seleznev1->GetFace(47), Sborka4Comp);
    assm->AddConstraint(GCM_ANGLE, face6, face5, (180 - 10)* M_PI / 180);//Градус 10

    //Angle for Vilka
    MtGeomArgument Opa1(Solov2->GetFace(16), Sborka1Comp);
    MtGeomArgument Opa2(Seleznev1->GetFace(47), Sborka4Comp);
    assm->AddConstraint(GCM_ANGLE, Opa1, Opa2, (180 - 10)* M_PI / 180);//Градус 10
    
    ///Фукина для 3
    //MbAxis3D axVert(MbVector3D(0, 1, 0));
    assm->EvaluateConstraints();
    //assm->Rotate(axVert, M_PI / 2);
    //assm->SetPlacement(MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0), MbVector3D(0, 1, 1), MbVector3D(1, 1, 0)));
    //Seleznev1->SetPlacement(MbPlacement3D(MbCartPoint3D(0.0, 0.0, 500.0)));
    //assm->Move(MbVector3D(500, 1000, 300));


	return assm;
}