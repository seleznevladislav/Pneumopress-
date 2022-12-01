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
   
#pragma endregion

#pragma region Porshen
    SPtr<MbSolid> Yaganov1 = LIS_ME22_3_002_01_001();
    Yaganov1->SetColor(255, 255, 0);
    SPtr<MbSolid> Morozova1 = LIS_ME22_3_002_01_002();
    Morozova1->SetColor(255, 255, 255);
    SPtr<MbSolid> Zarubin1 = LIS_ME22_3_002_01_003();
    Zarubin1->SetColor(255, 255, 0);
    SPtr<MbSolid> Shepovalova1 = LIS_ME22_3_002_01_004(param_length);
    Shepovalova1->SetColor(255, 255, 255);
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
    SPtr<MbSolid> Solov2 = LIS_ME22_3_002_00_001();
    Solov2->SetColor(255, 0, 0);
    SPtr<MbSolid> Vasinkina2 = LIS_ME22_3_002_00_002();
    Vasinkina2->SetColor(0, 255, 255);
    SPtr<MbSolid> Prihodko2 = LIS_ME22_3_002_00_003();
    Prihodko2->SetColor(255, 255, 0);
    SPtr<MbSolid> Seleznev1 = LIS_ME22_3_002_00_004();
    Seleznev1->SetColor(ParametricModelCreator::colorScheme ? RGB(191, 255, 110) : RGB(255, 255, 0));
    SPtr<MbSolid> Veronika1 = LIS_ME22_3_002_00_005();
    Veronika1->SetColor(191, 255, 110);
    SPtr<MbSolid> Fukina31 = LIS_ME22_3_002_00_006();
    Fukina31->SetColor(74, 148, 0);
    SPtr<MbSolid> Fukina32 = LIS_ME22_3_002_00_006();
    Fukina32->SetColor(74, 148, 0);
    SPtr<MbSolid> Fukina33 = LIS_ME22_3_002_00_006();
    Fukina33->SetColor(74, 148, 0);
    SPtr<MbSolid> Solov1 = LIS_ME22_3_002_00_007();
    Solov1->SetColor(244, 184, 105);
    SPtr<MbSolid> Yaganov21 = LIS_ME22_3_002_00_008();
    Yaganov21->SetColor(110, 55, 0);
    SPtr<MbSolid> Yaganov22 = LIS_ME22_3_002_00_008();
    Yaganov22->SetColor(110, 55, 0);
    SPtr<MbSolid> Zarubin21 = LIS_ME22_3_002_00_009();
    Zarubin21->SetColor(255, 255, 255);
    SPtr<MbSolid> Zarubin22 = LIS_ME22_3_002_00_009();
    Zarubin22->SetColor(255, 255, 255);
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
    SPtr<MbSolid> Zarubin3 = LIS_ME22_3_002_00_013();
    Zarubin3->SetColor(244, 120, 0);
    SPtr<MbSolid> Zarubin4 = LIS_ME22_3_002_00_014();
    Zarubin4->SetColor(0, 120, 255);
    SPtr<MbSolid> Fukina2 = LIS_ME22_3_002_00_015();
    Fukina2->SetColor(209, 209, 209);
    SPtr<MbSolid> Vasinkina1 = LIS_ME22_3_002_00_016();
    Vasinkina1->SetColor(89, 44, 0);
    SPtr<MbSolid> VasinkinaXXX = LIS_ME22_3_002_00_XXX();
    VasinkinaXXX->SetColor(89, 44, 0);
    //Оси
    SPtr<MbSolid> Fukina6 = LIS_ME22_3_002_03_001();
    Fukina6->SetColor(220, 220, 220);
    SPtr<MbSolid> Fukina5 = LIS_ME22_3_002_04_001();
    Fukina5->SetColor(220, 220, 220);
#pragma endregion
#pragma region Shatun
    SPtr<MbSolid> Bychkov1 = LIS_ME22_3_002_02_001(param_length);
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
    SPtr<MbSolid> WasherM20 = GWasherM20();
    SPtr<MbSolid> Bolt4m101 = GBolt4m10();
    SPtr<MbSolid> Bolt4m102 = GBolt4m10();
    SPtr<MbSolid> Bolt4m103 = GBolt4m10();
    SPtr<MbSolid> Bolt4m104 = GBolt4m10();
    SPtr<MbSolid> Bolt4m105 = GBolt4m10();
    SPtr<MbSolid> Bolt4m106 = GBolt4m10();
    SPtr<MbSolid> Bolt4m107 = GBolt4m10();
    SPtr<MbSolid> Bolt4m108 = GBolt4m10();

    SPtr<MbSolid> WasherA141 = GWasherA14();
    SPtr<MbSolid> WasherA142 = GWasherA14();
    SPtr<MbSolid> WasherA143 = GWasherA14();

    SPtr<MbSolid> ScrewM141 = GScrewM14();
    SPtr<MbSolid> ScrewM142 = GScrewM14();
    SPtr<MbSolid> ScrewM143 = GScrewM14();

    SPtr<MbSolid> ScrewM101 = GScrewM10();
    SPtr<MbSolid> ScrewM102 = GScrewM10();

    SPtr<MbSolid> ScrewM81 = GScrewM8();
    SPtr<MbSolid> ScrewM82 = GScrewM8();
    SPtr<MbSolid> ScrewM83 = GScrewM8();
    SPtr<MbSolid> ScrewM84 = GScrewM8();
    SPtr<MbSolid> ScrewM85 = GScrewM8();
    SPtr<MbSolid> ScrewM86 = GScrewM8();
    
    SPtr<MbSolid> ScrewAM81 = GScrewAM8();
    SPtr<MbSolid> ScrewAM82 = GScrewAM8();

    SPtr<MbSolid> WassherM81 = GWassherM8();
    SPtr<MbSolid> WassherM82 = GWassherM8();

    SPtr<MbSolid> WasherM16 = GWasherM16();
    
    SPtr<MbSolid> RingA20 = GRingA20();

#pragma endregion
    SPtr<MbSolid> Konfiguration1 = LIS_Konfiguration1();
    SPtr<MbSolid> Konfiguration2 = LIS_Konfiguration2();
    SPtr<MbSolid> Konfiguration3 = LIS_Konfiguration3();

#pragma region Porshen InstanceSPtr
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
#pragma region Sborka InstanceSPtr
    InstanceSPtr Sborka1(new MbInstance(*Solov2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka2(new MbInstance(*Vasinkina2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka3(new MbInstance(*Prihodko2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka4(new MbInstance(*Seleznev1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka5(new MbInstance(*Veronika1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka61(new MbInstance(*Fukina31, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka62(new MbInstance(*Fukina32, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka63(new MbInstance(*Fukina33, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka7(new MbInstance(*Solov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka81(new MbInstance(*Yaganov21, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka82(new MbInstance(*Yaganov22, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka91(new MbInstance(*Zarubin21, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka92(new MbInstance(*Zarubin22, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka101(new MbInstance(*Vasinkina31, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka102(new MbInstance(*Vasinkina32, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka11(new MbInstance(*Kozir1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka121(new MbInstance(*Fukina71, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka122(new MbInstance(*Fukina72, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka13(new MbInstance(*Zarubin3, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka14(new MbInstance(*Zarubin4, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka15(new MbInstance(*Fukina2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka16(new MbInstance(*Vasinkina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr SborkaXXX(new MbInstance(*VasinkinaXXX, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Oc1(new MbInstance(*Fukina6, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Oc2(new MbInstance(*Fukina5, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
#pragma endregion
#pragma region Shatun InstanceSPtr
    InstanceSPtr Shatun1(new MbInstance(*Bychkov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun2(new MbInstance(*Morozova2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun3(new MbInstance(*Fukina4, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun41(new MbInstance(*Prihodko11, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Shatun42(new MbInstance(*Prihodko12, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
#pragma endregion

    MbPlacement3D lcs;
#pragma region Porshen SPtr<MbInstance>
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
#pragma region Sborka SPtr<MbInstance>
    SPtr<MbInstance> Sborka1Comp(new MbInstance(*Sborka1, lcs));
    SPtr<MbInstance> Sborka2Comp(new MbInstance(*Sborka2, lcs));
    SPtr<MbInstance> Sborka3Comp(new MbInstance(*Sborka3, lcs));
    SPtr<MbInstance> Sborka4Comp(new MbInstance(*Sborka4, lcs));
    SPtr<MbInstance> Sborka5Comp(new MbInstance(*Sborka5, lcs));
    SPtr<MbInstance> Sborka61Comp(new MbInstance(*Sborka61, lcs));
    SPtr<MbInstance> Sborka62Comp(new MbInstance(*Sborka62, lcs));
    SPtr<MbInstance> Sborka63Comp(new MbInstance(*Sborka63, lcs));
    SPtr<MbInstance> Sborka7Comp(new MbInstance(*Sborka7, lcs));
    SPtr<MbInstance> Sborka81Comp(new MbInstance(*Sborka81, lcs));
    SPtr<MbInstance> Sborka82Comp(new MbInstance(*Sborka82, lcs));
    SPtr<MbInstance> Sborka91Comp(new MbInstance(*Sborka91, lcs));
    SPtr<MbInstance> Sborka92Comp(new MbInstance(*Sborka92, lcs));
    SPtr<MbInstance> Sborka101Comp(new MbInstance(*Sborka101, lcs));
    SPtr<MbInstance> Sborka102Comp(new MbInstance(*Sborka102, lcs));
    SPtr<MbInstance> Sborka11Comp(new MbInstance(*Sborka11, lcs));
    SPtr<MbInstance> Sborka121Comp(new MbInstance(*Sborka121, lcs));
    SPtr<MbInstance> Sborka122Comp(new MbInstance(*Sborka122, lcs));
    SPtr<MbInstance> Sborka13Comp(new MbInstance(*Sborka13, lcs));
    SPtr<MbInstance> Sborka14Comp(new MbInstance(*Sborka14, lcs));
    SPtr<MbInstance> Sborka15Comp(new MbInstance(*Sborka15, lcs));
    SPtr<MbInstance> Sborka16Comp(new MbInstance(*Sborka16, lcs));
    SPtr<MbInstance> SborkaXXXComp(new MbInstance(*SborkaXXX, lcs));
    SPtr<MbInstance> Oc1Comp(new MbInstance(*Oc1, lcs));
    SPtr<MbInstance> Oc2Comp(new MbInstance(*Oc2, lcs));
#pragma endregion
#pragma region Shatun SPtr<MbInstance>
    SPtr<MbInstance> Shatun1Comp(new MbInstance(*Shatun1, lcs));
    SPtr<MbInstance> Shatun2Comp(new MbInstance(*Shatun2, lcs));
    SPtr<MbInstance> Shatun3Comp(new MbInstance(*Shatun3, lcs));
    SPtr<MbInstance> Shatun41Comp(new MbInstance(*Shatun41, lcs));
    SPtr<MbInstance> Shatun42Comp(new MbInstance(*Shatun42, lcs));
#pragma endregion
#pragma region GOST SPtr<MbInstance>
    SPtr<MbInstance> WasherM20Comp1(new MbInstance(*WasherM20, lcs));

    SPtr<MbInstance> Bolt4m10Comp1(new MbInstance(*Bolt4m101, lcs));
    SPtr<MbInstance> Bolt4m10Comp2(new MbInstance(*Bolt4m102, lcs));
    SPtr<MbInstance> Bolt4m10Comp3(new MbInstance(*Bolt4m103, lcs));
    SPtr<MbInstance> Bolt4m10Comp4(new MbInstance(*Bolt4m104, lcs));
    SPtr<MbInstance> Bolt4m10Comp5(new MbInstance(*Bolt4m105, lcs));
    SPtr<MbInstance> Bolt4m10Comp6(new MbInstance(*Bolt4m106, lcs));
    SPtr<MbInstance> Bolt4m10Comp7(new MbInstance(*Bolt4m107, lcs));
    SPtr<MbInstance> Bolt4m10Comp8(new MbInstance(*Bolt4m108, lcs));

    SPtr<MbInstance> WasherA14Comp1(new MbInstance(*WasherA141, lcs));
    SPtr<MbInstance> WasherA14Comp2(new MbInstance(*WasherA142, lcs));
    SPtr<MbInstance> WasherA14Comp3(new MbInstance(*WasherA143, lcs));

    SPtr<MbInstance> ScrewM14Comp1(new MbInstance(*ScrewM141, lcs));
    SPtr<MbInstance> ScrewM14Comp2(new MbInstance(*ScrewM142, lcs));
    SPtr<MbInstance> ScrewM14Comp3(new MbInstance(*ScrewM143, lcs));

    SPtr<MbInstance> ScrewM10Comp1(new MbInstance(*ScrewM101, lcs));
    SPtr<MbInstance> ScrewM10Comp2(new MbInstance(*ScrewM102, lcs));

    SPtr<MbInstance> ScrewM8Comp1(new MbInstance(*ScrewM81, lcs));
    SPtr<MbInstance> ScrewM8Comp2(new MbInstance(*ScrewM82, lcs));
    SPtr<MbInstance> ScrewM8Comp3(new MbInstance(*ScrewM83, lcs));
    SPtr<MbInstance> ScrewM8Comp4(new MbInstance(*ScrewM84, lcs));
    SPtr<MbInstance> ScrewM8Comp5(new MbInstance(*ScrewM85, lcs));
    SPtr<MbInstance> ScrewM8Comp6(new MbInstance(*ScrewM86, lcs));

    SPtr<MbInstance> ScrewAM8Comp1(new MbInstance(*ScrewAM81, lcs));
    SPtr<MbInstance> ScrewAM8Comp2(new MbInstance(*ScrewAM82, lcs));

    SPtr<MbInstance> WasherM8Comp1(new MbInstance(*WassherM81, lcs));
    SPtr<MbInstance> WasherM8Comp2(new MbInstance(*WassherM82, lcs));

    SPtr<MbInstance> WasherM16Comp1(new MbInstance(*WasherM16, lcs));

    SPtr<MbInstance> RingA20Comp1(new MbInstance(*RingA20, lcs));



#pragma endregion

    SPtr<MbInstance> Konfiguration1Comp(new MbInstance(*Konfiguration1, lcs));
    SPtr<MbInstance> Konfiguration2Comp(new MbInstance(*Konfiguration2, lcs));
    SPtr<MbInstance> Konfiguration3Comp(new MbInstance(*Konfiguration3, lcs));

#pragma region PUSH_BACK MAIN
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
    pair.push_back(Porshen6Comp);
    pair.push_back(Porshen7Comp);
    pair.push_back(Porshen8Comp);
    //Переменные для Сборки
    pair.push_back(Sborka1Comp);
    pair.push_back(Sborka2Comp);
    pair.push_back(Sborka3Comp);
    pair.push_back(Sborka4Comp);
    pair.push_back(Sborka5Comp);
    pair.push_back(Sborka61Comp);
    pair.push_back(Sborka62Comp);
    pair.push_back(Sborka63Comp);
    pair.push_back(Sborka7Comp);
    pair.push_back(Sborka81Comp);
    pair.push_back(Sborka82Comp);
    pair.push_back(Sborka91Comp);
    pair.push_back(Sborka92Comp);
    pair.push_back(Sborka101Comp);
    pair.push_back(Sborka102Comp);
    pair.push_back(Sborka11Comp);
    pair.push_back(Sborka121Comp);
    pair.push_back(Sborka122Comp);
    pair.push_back(Sborka13Comp);
    pair.push_back(Sborka14Comp);
    pair.push_back(Sborka15Comp);
    pair.push_back(ParametricModelCreator::variantsConf ? SborkaXXXComp : Sborka16Comp);
    pair.push_back(Oc1Comp);
    pair.push_back(Oc2Comp);
    //Переменные для Шатуна
    pair.push_back(Shatun1Comp);
    pair.push_back(Shatun2Comp);
    pair.push_back(Shatun3Comp);
    pair.push_back(Shatun41Comp);
    pair.push_back(Shatun42Comp);
#pragma endregion
#pragma region PUSH_BACK GHOSTS
    pair.push_back(WasherM20Comp1);

    pair.push_back(Bolt4m10Comp1);
    pair.push_back(Bolt4m10Comp2);
    pair.push_back(Bolt4m10Comp3);
    pair.push_back(Bolt4m10Comp4);
    pair.push_back(Bolt4m10Comp5);
    pair.push_back(Bolt4m10Comp6);
    pair.push_back(Bolt4m10Comp7);
    pair.push_back(Bolt4m10Comp8);

    pair.push_back(WasherA14Comp1);
    pair.push_back(WasherA14Comp2);
    pair.push_back(WasherA14Comp3);

    pair.push_back(ScrewM14Comp1);
    pair.push_back(ScrewM14Comp2);
    pair.push_back(ScrewM14Comp3);

    pair.push_back(ScrewM10Comp1);
    pair.push_back(ScrewM10Comp2);

    pair.push_back(ScrewM8Comp1);
    pair.push_back(ScrewM8Comp2);
    pair.push_back(ScrewM8Comp3);
    pair.push_back(ScrewM8Comp4);
    pair.push_back(ScrewM8Comp5);
    pair.push_back(ScrewM8Comp6);

    pair.push_back(ScrewAM8Comp1);
    pair.push_back(ScrewAM8Comp2);

    pair.push_back(WasherM8Comp1);
    pair.push_back(WasherM8Comp2);

    pair.push_back(WasherM16Comp1);

    pair.push_back(RingA20Comp1);
#pragma endregion

    pair.push_back(Konfiguration1Comp);
    pair.push_back(Konfiguration2Comp);
    pair.push_back(Konfiguration3Comp);

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
    MtGeomArgument PFR2XXX(VasinkinaXXX->GetFace(33), SborkaXXXComp);
    ParametricModelCreator::variantsConf ?
        assm->AddConstraint(GCM_DISTANCE, PFR1, PFR2XXX, Arg7)
        :
        assm->AddConstraint(GCM_DISTANCE, PFR1, PFR2, Arg7);;
    //Центральное отверстие
    MtGeomArgument PHR1(Seleznev1->GetFace(64), Sborka4Comp);
    MtGeomArgument PHR2(Vasinkina1->GetFace(12), Sborka16Comp);
    MtGeomArgument PHR2XXX(VasinkinaXXX->GetFace(19), SborkaXXXComp);
    ParametricModelCreator::variantsConf ?
        assm->AddConstraint(GCM_CONCENTRIC, PHR1, PHR2XXX)
        :
        assm->AddConstraint(GCM_CONCENTRIC, PHR1, PHR2);
    //Боковое отверстие для выравнивания
    MtGeomArgument PHR3(Seleznev1->GetFace(55), Sborka4Comp);
    MtGeomArgument PHR4(Vasinkina1->GetFace(14), Sborka16Comp);
    MtGeomArgument PHR4XXX(VasinkinaXXX->GetFace(21), SborkaXXXComp);
    
    ParametricModelCreator::variantsConf ?
        assm->AddConstraint(GCM_CONCENTRIC, PHR3, PHR4XXX)
        :
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
    MtGeomArgument HoleL2XXX(VasinkinaXXX->GetFace(0), SborkaXXXComp);
    MtGeomArgument HoleL12(Solov1->GetFace(7), Sborka7Comp);
    ParametricModelCreator::variantsConf ?
        assm->AddConstraint(GCM_ANGLE, HoleL12, HoleL2XXX, 0 * M_PI / 180)
        :
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
#pragma region Sborka - Oc dlinnaya
    //HARDCODE
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
#pragma region Sborka - Oc malaya
    double Val49 = 11.775;
    MtParVariant Arg49(Val49);

    MtGeomArgument QPFM1(Fukina6->GetFace(8), Oc1Comp);
    MtGeomArgument QPFM2(Prihodko2->GetFace(4), Sborka3Comp);
    assm->AddConstraint(GCM_DISTANCE, QPFM1, QPFM2, Arg49);


    MtGeomArgument QPHM1(Fukina6->GetFace(5), Oc1Comp);
    MtGeomArgument QPHM2(Prihodko2->GetFace(11), Sborka3Comp);
    assm->AddConstraint(GCM_CONCENTRIC, QPHM1, QPHM2);

#pragma endregion
#pragma region Sborka - Prokladka
    double Val50 = 0;
    MtParVariant Arg50(Val50);

    MtGeomArgument WPFM1(Zarubin21->GetFace(1), Sborka91Comp);
    MtGeomArgument WPFM2(Solov1->GetFace(7), Sborka7Comp);
    assm->AddConstraint(GCM_DISTANCE, WPFM1, WPFM2, Arg50);


    MtGeomArgument WPHM1(Zarubin21->GetFace(2), Sborka91Comp);
    MtGeomArgument WPHM2(Solov1->GetFace(27), Sborka7Comp);
    assm->AddConstraint(GCM_CONCENTRIC, WPHM1, WPHM2);

    MtGeomArgument WPFM3(Zarubin22->GetFace(0), Sborka92Comp);
    MtGeomArgument WPFM4(Solov1->GetFace(5), Sborka7Comp);
    assm->AddConstraint(GCM_DISTANCE, WPFM3, WPFM4, Arg50);
    //HARDCODE
    MtGeomArgument WPHM3(Zarubin22->GetFace(3), Sborka92Comp);
    MtGeomArgument WPHM4(Zarubin3->GetFace(1), Sborka13Comp);
    assm->AddConstraint(GCM_DISTANCE, WPHM3, WPHM4, -3.0);

    MtGeomArgument WPHM5(Zarubin22->GetFace(4), Sborka92Comp);
    MtGeomArgument WPHM6(Zarubin3->GetFace(4), Sborka13Comp);
    assm->AddConstraint(GCM_DISTANCE, WPHM5, WPHM6, -23.0);
#pragma endregion
#pragma region Sborka - Prokladka napravlyaushei polzuna
    //HARDCODE
    double Val51 = 0;
    MtParVariant Arg51(Val51);

    MtGeomArgument EPFM1(Zarubin3->GetFace(2), Sborka13Comp);
    MtGeomArgument EPFM2(Seleznev1->GetFace(60), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, EPFM1, EPFM2, 75.0);


    MtGeomArgument EPHM1(Zarubin3->GetFace(1), Sborka13Comp);
    MtGeomArgument EPHM2(Seleznev1->GetFace(45), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, EPHM1, EPHM2, 66.0);

    MtGeomArgument EPHM3(Zarubin3->GetFace(3), Sborka13Comp);
    MtGeomArgument EPHM4(Seleznev1->GetFace(74), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, EPHM3, EPHM4, 227.0);

#pragma endregion
#pragma region Sborka - Prokladka polzuna
    //HARDCODE
    double Val52 = -29;
    MtParVariant Arg52(Val52);

    MtGeomArgument RPFM1(Zarubin4->GetFace(5), Sborka14Comp);
    MtGeomArgument RPFM2(Solov1->GetFace(5), Sborka7Comp);
    assm->AddConstraint(GCM_DISTANCE, RPFM1, RPFM2, Arg52);


    MtGeomArgument RPHM1(Zarubin4->GetFace(2), Sborka14Comp);
    MtGeomArgument RPHM2(Solov1->GetFace(1), Sborka7Comp);
    assm->AddConstraint(GCM_DISTANCE, RPHM1, RPHM2, 40.0);

    MtGeomArgument RPHM3(Zarubin4->GetFace(0), Sborka14Comp);
    MtGeomArgument RPHM4(Solov1->GetFace(4), Sborka7Comp);
    assm->AddConstraint(GCM_DISTANCE, RPHM3, RPHM4, -6.0);

#pragma endregion
#pragma region Sborka - End constraints
    MtGeomArgument PHM1(Vasinkina2->GetFace(23), Sborka2Comp);
    MtGeomArgument PHM2(Vasinkina1->GetFace(0), Sborka16Comp);
    MtGeomArgument PHM2XXX(VasinkinaXXX->GetFace(0), SborkaXXXComp);
    //assm->AddConstraint(GCM_DISTANCE, PHM1, PHM2, 143.0); много
    //assm->AddConstraint(GCM_DISTANCE, PHM1, PHM2, 80.0);

    ParametricModelCreator::variantsConf ?
        assm->AddConstraint(GCM_ANGLE, PHM1, PHM2XXX, 180 * M_PI / 180)
        :
        assm->AddConstraint(GCM_ANGLE, PHM1, PHM2, 180 * M_PI / 180);

    MtGeomArgument PHM3(Morozova2->GetFace(0), Shatun2Comp);
    MtGeomArgument PHM4(Zarubin1->GetFace(17), Porshen3Comp);
    //assm->AddConstraint(GCM_DISTANCE, PHM3, PHM4, 30.0);

    MtGeomArgument PHM5(Fukina5->GetFace(0), Oc2Comp);
    MtGeomArgument PHM6(Prihodko2->GetFace(15), Sborka3Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHM5, PHM6, 0);
#pragma endregion
#pragma region Sborka - Angle Constrains
    //Angle for Block
    MtGeomArgument face5(Yaganov1->GetFace(8), Porshen1Comp);
    MtGeomArgument face6(Seleznev1->GetFace(47), Sborka4Comp);
    assm->AddConstraint(GCM_ANGLE, face6, face5, (180 - 10)* M_PI / 180);//Градус 10

    //Angle for Vilka
    MtGeomArgument Opa1(Solov2->GetFace(16), Sborka1Comp);
    MtGeomArgument Opa2(Seleznev1->GetFace(47), Sborka4Comp);
    assm->AddConstraint(GCM_ANGLE, Opa1, Opa2, (180 - 10)* M_PI / 180);//Градус 10

#pragma endregion
#pragma region GOST cinstrains
    //test
    double boltVal = 14;
    double washerVal = 0;
    double screwVal = -20;
    MtParVariant argBolt(boltVal);
    MtParVariant argWasher(washerVal);
    MtParVariant argScrew(screwVal);

    MtGeomArgument PlaneCapfa1(Solov1->GetFace(15), Sborka7Comp);//15
    MtGeomArgument PlaneCapfa2(Solov1->GetFace(22), Sborka7Comp);//22

    MtGeomArgument PlaneBolt1(Bolt4m101->GetFace(10), Bolt4m10Comp1);
    MtGeomArgument PlaneBolt2(Bolt4m102->GetFace(10), Bolt4m10Comp2);
    MtGeomArgument PlaneBolt3(Bolt4m103->GetFace(10), Bolt4m10Comp3);
    MtGeomArgument PlaneBolt4(Bolt4m104->GetFace(10), Bolt4m10Comp4);

    assm->AddConstraint(GCM_DISTANCE, PlaneCapfa1, PlaneBolt1, argBolt);
    assm->AddConstraint(GCM_DISTANCE, PlaneCapfa1, PlaneBolt2, argBolt);
    assm->AddConstraint(GCM_DISTANCE, PlaneCapfa1, PlaneBolt3, argBolt);
    assm->AddConstraint(GCM_DISTANCE, PlaneCapfa1, PlaneBolt4, argBolt);
    //HARDCODE
    MtGeomArgument MKM1(Fukina33->GetFace(12), Sborka63Comp);
    MtGeomArgument MKM2(Seleznev1->GetFace(104), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, MKM1, MKM2, 506.0);

    MtGeomArgument MKM3(Fukina33->GetFace(6), Sborka63Comp);
    MtGeomArgument MKM4(Seleznev1->GetFace(2), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, MKM3, MKM4, 142.0);
    
    MtGeomArgument MKM5(Fukina33->GetFace(0), Sborka63Comp);
    //MtGeomArgument MKM6(Seleznev1->GetFace(3), Sborka4Comp);
    assm->AddConstraint(GCM_DISTANCE, MKM5, PlaneBolt2, 0.0);

    MtGeomArgument PlaneCapfaC1(Fukina33->GetFace(2), Sborka63Comp);//14
    MtGeomArgument PlaneCapfaC2(Fukina33->GetFace(3), Sborka63Comp);
    MtGeomArgument PlaneCapfaC3(Fukina33->GetFace(4), Sborka63Comp);
    MtGeomArgument PlaneCapfaC4(Fukina33->GetFace(5), Sborka63Comp);

    MtGeomArgument PlaneBoltC1(Bolt4m101->GetFace(12), Bolt4m10Comp1);
    MtGeomArgument PlaneBoltC2(Bolt4m102->GetFace(12), Bolt4m10Comp2);
    MtGeomArgument PlaneBoltC3(Bolt4m103->GetFace(12), Bolt4m10Comp3);
    MtGeomArgument PlaneBoltC4(Bolt4m104->GetFace(12), Bolt4m10Comp4);

    assm->AddConstraint(GCM_CONCENTRIC, PlaneCapfaC1, PlaneBoltC1);
    assm->AddConstraint(GCM_CONCENTRIC, PlaneCapfaC2, PlaneBoltC2);
    assm->AddConstraint(GCM_CONCENTRIC, PlaneCapfaC3, PlaneBoltC3);
    assm->AddConstraint(GCM_CONCENTRIC, PlaneCapfaC4, PlaneBoltC4);
#pragma endregion
#pragma region Porshen - Vtulka1
    double Val53 = 0;
    MtParVariant Arg53(Val53);

    MtGeomArgument PFQ1(Zarubin1->GetFace(16), Porshen3Comp);
    MtGeomArgument PFQ2(Aleksanyan1->GetFace(3), Porshen6Comp);
    assm->AddConstraint(GCM_DISTANCE, PFQ1, PFQ2, Arg53);

    MtGeomArgument PHQ1(Zarubin1->GetFace(26), Porshen3Comp);
    MtGeomArgument PHQ2(Aleksanyan1->GetFace(0), Porshen6Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHQ1, PHQ2);
#pragma endregion
#pragma region Porshen - Vtulka2
    double Val54 = 0;
    MtParVariant Arg54(Val54);

    MtGeomArgument PFW1(Yaganov1->GetFace(27), Porshen1Comp);
    MtGeomArgument PFW2(Aleksanyan2->GetFace(17), Porshen7Comp);
    assm->AddConstraint(GCM_DISTANCE, PFW1, PFW2, Arg54);

    MtGeomArgument PHW1(Yaganov1->GetFace(30), Porshen1Comp);
    MtGeomArgument PHW2(Aleksanyan2->GetFace(10), Porshen7Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHW1, PHW2);
#pragma endregion
#pragma region Porshen - Vtulka 3
    double Val6 = 0;
    MtParVariant Arg6(Val6);

    MtGeomArgument PFE1(Yaganov1->GetFace(36), Porshen1Comp);
    MtGeomArgument PFE2(Aleksanyan3->GetFace(1), Porshen8Comp);
    assm->AddConstraint(GCM_DISTANCE, PFE1, PFE2, Arg6);

    MtGeomArgument PHE1(Yaganov1->GetFace(28), Porshen1Comp);
    MtGeomArgument PHE2(Aleksanyan3->GetFace(0), Porshen8Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHE1, PHE2);

#pragma endregion
    MbAxis3D AxX(MbVector3D(1, 0, 0));
    MbAxis3D AxY(MbVector3D(0, 1, 0));
    MbAxis3D AxZ(MbVector3D(0, 0, 1));
#pragma region Moves for ghosts
    Bolt4m105->Rotate(AxX, (- 1)* (180 - 90)* M_PI / 180);
    Bolt4m106->Rotate(AxX, (- 1)* (180 - 90)* M_PI / 180);
    Bolt4m107->Rotate(AxX, (- 1)* (180 - 90)* M_PI / 180);
    Bolt4m108->Rotate(AxX, (- 1)* (180 - 90)* M_PI / 180);
    Bolt4m105->Move(MbVector3D(-15, 141, 58.5));
    Bolt4m106->Move(MbVector3D(-15+36-4, 141, 58.5+30+4));
    Bolt4m107->Move(MbVector3D(-15+36-0.5, 141, 58.5 + 4.5));
    Bolt4m108->Move(MbVector3D(-15-3.5, 141, 58.5+30));

    WasherA14Comp1-> Rotate(AxY, (-1)* (180 - 84)* M_PI / 180);
    WasherA14Comp2-> Rotate(AxY, (-1)* (180 - 84)* M_PI / 180);
    WasherA14Comp3-> Rotate(AxY, (-1)* (180 - 84)* M_PI / 180);
    WasherA14Comp1-> Move(MbVector3D(-143, 72, 285-58));
    WasherA14Comp2-> Move(MbVector3D(-150, 72, 286));
    WasherA14Comp3-> Move(MbVector3D(-157, 72, 286+60));

    ScrewM14Comp1->Rotate(AxY, -(90 - 84)* M_PI / 180);
    ScrewM14Comp2->Rotate(AxY, -(90 - 84)* M_PI / 180);
    ScrewM14Comp3->Rotate(AxY, -(90 - 84)* M_PI / 180);
    ScrewM14Comp1->Move(MbVector3D(-143, 72, 285 - 58));
    ScrewM14Comp2->Move(MbVector3D(-150, 72, 286));
    ScrewM14Comp3->Move(MbVector3D(-157, 72, 286 + 60));

    ScrewM10Comp1->Rotate(AxY, -(180 - 84) * M_PI / 180);
    ScrewM10Comp2->Rotate(AxY, -(180 - 84) * M_PI / 180);
    ScrewM10Comp1->Move(MbVector3D(-140,  72-16, 86+9));
    ScrewM10Comp2->Move(MbVector3D(-140,  72+16, 86+9));

    ScrewM8Comp1->Rotate(AxY, (180-6) * M_PI / 180);
    ScrewM8Comp2->Rotate(AxY, (180-6) * M_PI / 180);
    ScrewM8Comp3->Rotate(AxY, (180-6) * M_PI / 180);
    ScrewM8Comp4->Rotate(AxY, (180-6) * M_PI / 180);
    ScrewM8Comp5->Rotate(AxY, (180-6) * M_PI / 180);
    ScrewM8Comp6->Rotate(AxY, (180-6) * M_PI / 180);

    ScrewM8Comp1->Move(MbVector3D(-31, 72-42, 346));
    ScrewM8Comp2->Move(MbVector3D(-31+4, 72-42, 346-35));
    ScrewM8Comp3->Move(MbVector3D(-31-4, 72-42, 346+35));
    ScrewM8Comp4->Move(MbVector3D(-31-4, 72+43, 346+35));
    ScrewM8Comp5->Move(MbVector3D(-31+4, 72+43, 346-35));
    ScrewM8Comp6->Move(MbVector3D(-31, 72+43, 346));

    ScrewAM8Comp1->Rotate(AxZ, -90 * M_PI / 180);
    ScrewAM8Comp2->Rotate(AxZ, -90 * M_PI / 180);
    ScrewAM8Comp1->Move(MbVector3D(-59, 140, 362.5));
    ScrewAM8Comp2->Move(MbVector3D(-54, 140, 322.5));

    WasherM8Comp1->Rotate(AxY, 90 * M_PI / 180);
    WasherM8Comp1->Rotate(AxZ, 90 * M_PI / 180);
    WasherM8Comp1->Move(MbVector3D(-54, 127, 322.5));
    WasherM8Comp2->Rotate(AxY, 90 * M_PI / 180);
    WasherM8Comp2->Rotate(AxZ, 90 * M_PI / 180);
    WasherM8Comp2->Move(MbVector3D(-59, 127, 362.5));

    WasherM16Comp1->Rotate(AxY, -6 * M_PI / 180);
    WasherM16Comp1->Move(MbVector3D(-103, 72, 182));

    RingA20Comp1->Move(MbVector3D(-36.7, 18.2, 179.5));
#pragma endregion
#pragma region Moves for konfiguration
    Konfiguration1Comp->Rotate(AxY, (180 - 7) * M_PI / 180);
    Konfiguration1Comp->Move(MbVector3D(-60.5, 72.5, 380));
    
#pragma endregion
    assm->EvaluateConstraints();

#pragma region Position of assemble
    assm->Rotate(AxX, (M_PI / 2 ) );
    assm->Rotate(AxY,  - M_PI / 2);
    assm->Rotate(AxX, -(7 * M_PI / 180));
    assm->Move(MbVector3D(72, 600, 0));
#pragma endregion
	return assm;
}