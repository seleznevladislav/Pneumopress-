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
    //Переменные для подсборки Поршень
    SPtr<MbSolid> Yaganov1 = LIS_ME22_3_002_01_001();
    Yaganov1->SetColor(255, 255, 0);
    SPtr<MbSolid> Morozova1 = LIS_ME22_3_002_01_002();
    Morozova1->SetColor(255, 255, 255);

    /*SPtr<MbSolid> Zarubin1 = LIS_ME22_3_002_01_003();
    Zarubin1->SetColor(255, 255, 0);
    SPtr<MbSolid> Shepovalova1 = LIS_ME22_3_002_01_004();
    Shepovalova1->SetColor(0, 0, 0);
    Shepovalova1->SetVisual(0, 0, 0, 0, 0.8, 0, 0);
    SPtr<MbSolid> Fukina1 = LIS_ME22_3_002_01_005();
    Fukina1->SetColor(0, 236, 236);
    SPtr<MbSolid> Aleksanyan1 = LIS_ME22_3_002_01_006();
    Aleksanyan1->SetColor(255, 173, 91);
    SPtr<MbSolid> Aleksanyan2 = LIS_ME22_3_002_01_007();
    Aleksanyan2->SetColor(140, 70, 0);
    */
    SPtr<MbSolid> Aleksanyan3 = LIS_ME22_3_002_01_008();
    Aleksanyan3->SetColor(255, 255, 255);

    // Основная сборка
    SPtr<MbSolid> Solov2 = LIS_ME22_3_002_00_001();
    Solov2->SetColor(255, 0, 0);
    SPtr<MbSolid> Vasinkina2 = LIS_ME22_3_002_00_002();
    Vasinkina2->SetColor(0, 255, 255);
    SPtr<MbSolid> Prihodko2 = LIS_ME22_3_002_00_003();
    Prihodko2->SetColor(255, 255, 0);
    SPtr<MbSolid> Seleznev1 = LIS_ME22_3_002_00_004();
    Seleznev1->SetColor(191, 255, 110);
    //SPtr<MbSolid> Veronika1 = LIS_ME22_3_002_00_005();
    //Veronika1->SetColor(191, 255, 110);
    SPtr<MbSolid> Fukina3 = LIS_ME22_3_002_00_006();
    Fukina3->SetColor(74, 148, 0);
    SPtr<MbSolid> Solov1 = LIS_ME22_3_002_00_007();
    Solov1->SetColor(244, 184, 105);
    SPtr<MbSolid> Yaganov2 = LIS_ME22_3_002_00_008();
    Yaganov2->SetColor(110, 55, 0);
    SPtr<MbSolid> Vasinkina3 = LIS_ME22_3_002_00_010();
    Vasinkina3->SetColor(0, 0, 255);
    SPtr<MbSolid> Kozir1 = LIS_ME22_3_002_00_011();
    Kozir1->SetColor(74, 148, 0);
    /*SPtr<MbSolid> Fukina7 = LIS_ME22_3_002_00_012();
    Fukina7->SetColor(0, 255, 0);*/
    SPtr<MbSolid> Fukina2 = LIS_ME22_3_002_00_015();
    Fukina2->SetColor(209, 209, 209);
    SPtr<MbSolid> Vasinkina1 = LIS_ME22_3_002_00_016();
    Vasinkina1->SetColor(89, 44, 0);


    SPtr<MbSolid> Washer = GHOST();
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    MbPlacement3D lcs;
    InstanceSPtr Porshen1(new MbInstance(*Yaganov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen2(new MbInstance(*Morozova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));


    //InstanceSPtr Porshen2(new MbInstance(*Zarubin1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen3(new MbInstance(*Shepovalova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen4(new MbInstance(*Fukina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen5(new MbInstance(*Aleksanyan1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen6(new MbInstance(*Aleksanyan2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen7(new MbInstance(*Aleksanyan3, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //Переменные для сборки
    InstanceSPtr Sborka1(new MbInstance(*Solov2, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka2(new MbInstance(*Vasinkina2, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka3(new MbInstance(*Prihodko2, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka4(new MbInstance(*Seleznev1, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    //InstanceSPtr Sborka5(new MbInstance(*Veronika1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka6(new MbInstance(*Fukina3, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka7(new MbInstance(*Solov1, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka8(new MbInstance(*Yaganov2, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka101(new MbInstance(*Vasinkina3, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka102(new MbInstance(*Vasinkina3, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka11(new MbInstance(*Kozir1, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    //InstanceSPtr Sborka12(new MbInstance(*Fukina7, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka15(new MbInstance(*Fukina2, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka16(new MbInstance(*Vasinkina1, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    //Переменные для GOST
    InstanceSPtr Gost1(new MbInstance(*Washer, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    vector<InstanceSPtr> pair;
    pair.push_back(Porshen1);
    pair.push_back(Porshen2);
    
    /*
    pair.push_back(Porshen2Comp);
    pair.push_back(Porshen3Comp);
    pair.push_back(Porshen41Comp);
    pair.push_back(Porshen42Comp);
    pair.push_back(Porshen43Comp);
    pair.push_back(Porshen44Comp);
    pair.push_back(Porshen5Comp);
    pair.push_back(Porshen6Comp);;
    */
    pair.push_back(Porshen7);
    //Переменные для сборки
    pair.push_back(Sborka1);
    pair.push_back(Sborka2);
    pair.push_back(Sborka3);
    pair.push_back(Sborka4);
    //pair.push_back(Sborka5);//Разобраться почему ошибка templ
    pair.push_back(Sborka6);
    pair.push_back(Sborka7);
    pair.push_back(Sborka8);
    pair.push_back(Sborka101);
    pair.push_back(Sborka102);
    pair.push_back(Sborka11);
    //pair.push_back(Sborka12);//Разобраться почему ошибка templ
    pair.push_back(Sborka15);
    pair.push_back(Sborka16);
    //Переменные для GOST
    pair.push_back(Gost1);


    MbAssembly* assm = new MbAssembly(pair);

    ConstraintSolver cs;

    //placements of porshen

    GCM_geom LCSPorshen1 = cs.AddGeom(Porshen1->GetPlacement());
    GCM_geom PlacementPorshen1 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementPorshen1, LCSPorshen1);

    GCM_geom LCSPorshen2 = cs.AddGeom(Porshen2->GetPlacement());
    GCM_geom PlacementPorshen2 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementPorshen2, LCSPorshen2);

    //placements of sborka

    GCM_geom LCSSborka1 = cs.AddGeom(Sborka1->GetPlacement());
    GCM_geom PlacementSborka1 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka1, LCSSborka1);

    GCM_geom LCSSborka2 = cs.AddGeom(Sborka2->GetPlacement());//23.5
    GCM_geom PlacementSborka2 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(-30.0, 234.6, 185.4), MbVector3D(1.0, 0.0, 0.0), MbVector3D(0.0, 0.0, -1.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka2, LCSSborka2);

    GCM_geom LCSSborka3 = cs.AddGeom(Sborka3->GetPlacement());
    GCM_geom PlacementSborka3 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka3, LCSSborka3);

    //Создание основной плоскости
    GCM_geom LCSSborka4 = cs.AddGeom(Sborka4->GetPlacement());
    GCM_geom StartPlacement = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0)));
    cs.FixGeom(StartPlacement);
    cs.AddConstraint(GCM_COINCIDENT, StartPlacement, LCSSborka4);

    /*GCM_geom LCSSborka5 = cs.AddGeom(Sborka5->GetPlacement());
    GCM_geom PlacementSborka5 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, 400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka5, LCSSborka5);*/

    GCM_geom LCSSborka6 = cs.AddGeom(Sborka6->GetPlacement());
    GCM_geom PlacementSborka6 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka6, LCSSborka6);

    GCM_geom LCSSborka7 = cs.AddGeom(Sborka7->GetPlacement());
    GCM_geom PlacementSborka7 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(-55.0, 255.0, 145.4), MbVector3D(1.0, 0.0, 0.0), MbVector3D(0.0, 1.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka7, LCSSborka7);

    GCM_geom LCSSborka8 = cs.AddGeom(Sborka8->GetPlacement());
    GCM_geom PlacementSborka8 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka8, LCSSborka8);

    GCM_geom LCSSborka101 = cs.AddGeom(Sborka101->GetPlacement());//40.5//+20
    GCM_geom PlacementSborka101 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(11.5, 446.16, 183.4), MbVector3D(0.0, -0.5, 1.0), MbVector3D(0.0, -1.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka101, LCSSborka101);

    GCM_geom LCSSborka102 = cs.AddGeom(Sborka102->GetPlacement());//40.5//+20
    GCM_geom PlacementSborka102 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(10.0, 0.0, 0.0), MbVector3D(0.0, 0.0, 0.0), MbVector3D(0.0, 0.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka102, LCSSborka102);

    GCM_geom LCSSborka11 = cs.AddGeom(Sborka11->GetPlacement());
    GCM_geom PlacementSborka11 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka11, LCSSborka11);

    GCM_geom LCSSborka15 = cs.AddGeom(Sborka15->GetPlacement());
    GCM_geom PlacementSborka15 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, -400.0, 0.0)));
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka15, LCSSborka15);

    GCM_geom LCSSborka16 = cs.AddGeom(Sborka16->GetPlacement());
    GCM_geom PlacementSborka16 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(-2.0, 75.0, 160.0), MbVector3D(0, 0, 1), MbVector3D(1, 0, 0))); // Захардкодили стол
    cs.AddConstraint(GCM_COINCIDENT, PlacementSborka16, LCSSborka16);

    // Решение ограничений
    cs.Evaluate();

    Porshen1->SetPlacement(cs.GetNewPlacement3D(LCSPorshen1));
    Porshen2->SetPlacement(cs.GetNewPlacement3D(LCSPorshen2));


    Sborka1->SetPlacement(cs.GetNewPlacement3D(LCSSborka1));
    Sborka2->SetPlacement(cs.GetNewPlacement3D(LCSSborka2));
    Sborka3->SetPlacement(cs.GetNewPlacement3D(LCSSborka3));
    Sborka4->SetPlacement(cs.GetNewPlacement3D(LCSSborka4));
    //Sborka5->SetPlacement(cs.GetNewPlacement3D(LCSSborka5));
    Sborka6->SetPlacement(cs.GetNewPlacement3D(LCSSborka6));
    Sborka7->SetPlacement(cs.GetNewPlacement3D(LCSSborka7));
    Sborka8->SetPlacement(cs.GetNewPlacement3D(LCSSborka8));
    Sborka101->SetPlacement(cs.GetNewPlacement3D(LCSSborka101));
    Sborka102->SetPlacement(cs.GetNewPlacement3D(LCSSborka102));
    Sborka11->SetPlacement(cs.GetNewPlacement3D(LCSSborka11));
    Sborka15->SetPlacement(cs.GetNewPlacement3D(LCSSborka15));
    Sborka16->SetPlacement(cs.GetNewPlacement3D(LCSSborka16));

    //TEST
    //GCM_geom side1 = cs.AddGeom(PorshenComp->GetPlacement());
    //GCM_geom box1Id = cs.SubGeom(side1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0)));

    //GCM_geom side2 = cs.AddGeom(PorshenComp->GetPlacement());
    //GCM_geom box2Id = cs.SubGeom(side2, GCM_Plane(MbCartPoint3D(0.0, 0.0, 0.0), -MbVector3D::xAxis));

    //cs.AddDistance(box1Id, box2Id, 100, GCM_OPPOSITE);
    // 
    // Решение ограничений
    //cs.Evaluate();

    ////// Задаем объектам насчитанные в решателе placement
    //PorshenComp->SetPlacement(cs.GetNewPlacement3D(side1));
    //Porshen1Comp->SetPlacement(cs.GetNewPlacement3D(side2));
    //END TEST

	return assm;
}
