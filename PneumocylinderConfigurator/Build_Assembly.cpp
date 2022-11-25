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
    SPtr<MbSolid> Fukina11 = LIS_ME22_3_002_01_005();
    Fukina11->SetColor(0, 236, 236);
    SPtr<MbSolid> Fukina12 = LIS_ME22_3_002_01_005();
    Fukina12->SetColor(0, 236, 236);
    SPtr<MbSolid> Fukina13 = LIS_ME22_3_002_01_005();
    Fukina13->SetColor(0, 236, 236);
    SPtr<MbSolid> Fukina14 = LIS_ME22_3_002_01_005();
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
    SPtr<MbSolid> Vasinkina2 = LIS_ME22_3_002_00_002();
    Vasinkina2->SetColor(0, 255, 255);
    SPtr<MbSolid> Seleznev1 = LIS_ME22_3_002_00_004();
    Seleznev1->SetColor(191, 255, 110);
    SPtr<MbSolid> Veronika1 = LIS_ME22_3_002_00_005();
    Veronika1->SetColor(191, 255, 110);
    SPtr<MbSolid> Fukina31 = LIS_ME22_3_002_00_006();
    Fukina31->SetColor(74, 148, 0);
    SPtr<MbSolid> Fukina32 = LIS_ME22_3_002_00_006();
    Fukina32->SetColor(74, 148, 0);
    SPtr<MbSolid> Solov1 = LIS_ME22_3_002_00_007();
    Solov1->SetColor(244, 184, 105);
    SPtr<MbSolid> Vasinkina31 = LIS_ME22_3_002_00_010();
    Vasinkina31->SetColor(0, 0, 255);
    SPtr<MbSolid> Vasinkina32 = LIS_ME22_3_002_00_010();
    Vasinkina32->SetColor(0, 0, 255);
    SPtr<MbSolid> Vasinkina1 = LIS_ME22_3_002_00_016();
    Vasinkina1->SetColor(89, 44, 0);
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

    InstanceSPtr Porshen10(new MbInstance(*Fukina5, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //Переменные для сборки
    InstanceSPtr Sborka2(new MbInstance(*Vasinkina2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka4(new MbInstance(*Seleznev1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka5(new MbInstance(*Veronika1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka61(new MbInstance(*Fukina31, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka62(new MbInstance(*Fukina32, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka7(new MbInstance(*Solov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka101(new MbInstance(*Vasinkina31, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka102(new MbInstance(*Vasinkina32, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka16(new MbInstance(*Vasinkina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
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
    SPtr<MbInstance> Porshen10Comp(new MbInstance(*Porshen10, lcs));
#pragma endregion
    //Переменные для сборки
    SPtr<MbInstance> Sborka2Comp(new MbInstance(*Sborka2, lcs));
    SPtr<MbInstance> Sborka4Comp(new MbInstance(*Sborka4, lcs));
    SPtr<MbInstance> Sborka5Comp(new MbInstance(*Sborka5, lcs));
    SPtr<MbInstance> Sborka61Comp(new MbInstance(*Sborka61, lcs));
    SPtr<MbInstance> Sborka62Comp(new MbInstance(*Sborka62, lcs));
    SPtr<MbInstance> Sborka7Comp(new MbInstance(*Sborka7, lcs));
    SPtr<MbInstance> Sborka101Comp(new MbInstance(*Sborka101, lcs));
    SPtr<MbInstance> Sborka102Comp(new MbInstance(*Sborka102, lcs));
    SPtr<MbInstance> Sborka16Comp(new MbInstance(*Sborka16, lcs));
#pragma region Shatun SPtr<MbInstance>
    SPtr<MbInstance> Shatun1Comp(new MbInstance(*Shatun1, lcs));
    SPtr<MbInstance> Shatun2Comp(new MbInstance(*Shatun2, lcs));
    SPtr<MbInstance> Shatun3Comp(new MbInstance(*Shatun3, lcs));
    SPtr<MbInstance> Shatun41Comp(new MbInstance(*Shatun41, lcs));
    SPtr<MbInstance> Shatun42Comp(new MbInstance(*Shatun42, lcs));
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
    pair.push_back(Porshen10Comp);
    */
    //Переменные для Сборки
    pair.push_back(Sborka2Comp);
    pair.push_back(Sborka4Comp);
    pair.push_back(Sborka5Comp);
    pair.push_back(Sborka61Comp);
    pair.push_back(Sborka62Comp);
    pair.push_back(Sborka7Comp);
    pair.push_back(Sborka101Comp);
    pair.push_back(Sborka102Comp);
    pair.push_back(Sborka16Comp);
    //Переменные для Шатуна
    pair.push_back(Shatun1Comp);
    pair.push_back(Shatun2Comp);
    pair.push_back(Shatun3Comp);
    pair.push_back(Shatun41Comp);
    pair.push_back(Shatun42Comp);

    MbAssembly* assm = new MbAssembly(pair);
    ConstraintSolver cs;
    //Фиксация первого элемента сборки
    GCM_geom LCSSborka4 = cs.AddGeom(Sborka4Comp->GetPlacement());
    GCM_geom PlacementSborka4 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0), MbVector3D(0.0,0.0,1.0), MbVector3D(1.0, 0.0, 0.0)));
    cs.FixGeom(PlacementSborka4);
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka4, LCSSborka4);

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
    assm->AddConstraint(GCM_CONCENTRIC, HoleС1, HoleС2, -1);
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
    assm->AddConstraint(GCM_DISTANCE, PFA3, PFA4, Arg151);//<!!! Жесткая закрепка ползуна>
    //Плоскость боковая
    MtGeomArgument PFA5(Solov1->GetFace(14), Sborka7Comp);//24
    MtGeomArgument PFA6(Vasinkina2->GetFace(18), Sborka2Comp);//12
    assm->AddConstraint(GCM_DISTANCE, PFA6, PFA5, Arg14);//Тут крч совмещение пхд надо будет убрать !!!!! тк мешает сделать концентричность
    //Плоскость между
    MtGeomArgument PFA1(Vasinkina2->GetFace(13), Sborka2Comp);//17
    MtGeomArgument PFA2(Solov1->GetFace(21), Sborka7Comp);
    assm->AddConstraint(GCM_DISTANCE, PFA2, PFA1, Arg14);
    assm->AddConstraint(GCM_ANGLE, PFA2, PFA1, 180* M_PI/180);
#pragma endregion
#pragma region Sborka - Polzun and Skolzyachie
    double Val16 = 0.5;
    MtParVariant Arg16(Val16);
    //Плоскость между первым
    MtGeomArgument PFS1(Vasinkina32->GetFace(22), Sborka102Comp);
    MtGeomArgument PFS2(Vasinkina2->GetFace(2), Sborka2Comp);
    assm->AddConstraint(GCM_DISTANCE, PFS1, PFS2, Arg16);
    //Отверстие первого
    MtGeomArgument PHS1(Vasinkina32->GetFace(23), Sborka102Comp);
    MtGeomArgument PHS2(Vasinkina2->GetFace(22), Sborka2Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHS1, PHS2, 0);//<!!! Разворачиваем скользящий>
    //Плоскость между вторым
    MtGeomArgument PFS3(Vasinkina31->GetFace(1), Sborka101Comp);
    MtGeomArgument PFS4(Vasinkina2->GetFace(3), Sborka2Comp);
    assm->AddConstraint(GCM_DISTANCE, PFS3, PFS4, Arg16);//<!!! Вроде не надо, но добавим, это одни из скользяжих выравнивается с тягой(Но зачем, он же выровнян уже с ползуном)>
    //Отверстие второго    
    MtGeomArgument PHS3(Vasinkina31->GetFace(2), Sborka101Comp);
    MtGeomArgument PHS4(Vasinkina2->GetFace(22), Sborka2Comp);
    assm->AddConstraint(GCM_CONCENTRIC, PHS3, PHS4);
#pragma endregion
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


    MtGeomArgument face5(Yaganov1->GetFace(8), Porshen1Comp);
    MtGeomArgument face6(Seleznev1->GetFace(47), Sborka4Comp);
    assm->AddConstraint(GCM_ANGLE, face6, face5, (180 - 10)* M_PI / 180);//Градус 10

    cs.Evaluate();

    Sborka4Comp->SetPlacement(cs.GetNewPlacement3D(LCSSborka4));
    
    assm->EvaluateConstraints();

	return assm;
}
