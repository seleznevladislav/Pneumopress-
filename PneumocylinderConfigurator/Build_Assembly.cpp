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
        GCM_alignment aVal = GCM_CLOSEST,
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
    SPtr<MbSolid> Seleznev1 = LIS_ME22_3_002_00_004();
    Seleznev1->SetColor(191, 255, 110);
    //SPtr<MbSolid> Veronika1 = LIS_ME22_3_002_00_005();
    //Veronika1->SetColor(191, 255, 110);
    SPtr<MbSolid> Vasinkina1 = LIS_ME22_3_002_00_016();
    Vasinkina1->SetColor(89, 44, 0);


    SPtr<MbSolid> Washer = GHOST();
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    MbPlacement3D lcs;
    InstanceSPtr Porshen(new MbInstance(*Yaganov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen1(new MbInstance(*Morozova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen2(new MbInstance(*Washer, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));


    //InstanceSPtr Porshen2(new MbInstance(*Zarubin1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen3(new MbInstance(*Shepovalova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen4(new MbInstance(*Fukina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen5(new MbInstance(*Aleksanyan1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen6(new MbInstance(*Aleksanyan2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen7(new MbInstance(*Aleksanyan3, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //Переменные для сборки
    InstanceSPtr Sborka1(new MbInstance(*Solov2, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka2(new MbInstance(*Vasinkina2, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    InstanceSPtr Sborka4(new MbInstance(*Seleznev1, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    //InstanceSPtr Sborka5(new MbInstance(*Veronika1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Sborka16(new MbInstance(*Vasinkina1, MbPlacement3D(MbCartPoint3D(0.0,0.0, 0.0))));
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    vector<InstanceSPtr> pair;
    pair.push_back(Porshen);
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
    pair.push_back(Sborka4);
   //pair.push_back(Sborka5);
    pair.push_back(Sborka16);


    MbAssembly* assm = new MbAssembly(pair);

    ConstraintSolver cs;


    GCM_geom LCSPorshen = cs.AddGeom(Porshen->GetPlacement());
    GCM_geom LCSPorshen1 = cs.AddGeom(Porshen1->GetPlacement());
    GCM_geom LCSSborka4 = cs.AddGeom(Sborka4->GetPlacement());
    GCM_geom LCSSborka16 = cs.AddGeom(Sborka16->GetPlacement());
    //GCM_geom LCSSborka5 = cs.AddGeom(Sborka5->GetPlacement());
    //Создание основной плоскости
    GCM_geom StartPlacement = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0), MbVector3D(0.0, 0.0, 0.0), MbVector3D(0.0, 0.0, 0.0)));
    GCM_geom StartPlacement1 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(1.0, 0.0, 500.0), MbVector3D(0.0, 1.0, 500.0), MbVector3D(0.0, 0.0, 0.0)));
    GCM_geom StartPlacement2 = cs.AddGeom(MbPlacement3D(MbCartPoint3D(-2.0, 75.0, 160.0)));
    //, MbVector3D(1.0, 75.0, 0.0), MbVector3D(0.0, 75.0, 1.0)

    cs.FixGeom(StartPlacement);
    //GCM_geom box1ContactPointPlacementId = cs.AddGeom(PrepareBoxContactPointPlacement(MbPlacement3D(MbCartPoint3D(-25.0, 5.0, -0.5)), M_PI / 4));
    //MbPlacement3D for1 = MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0));
    //for1.Rotate(MbAxis3D(MbCartPoint3D(0.0,0.0,0.0), MbCartPoint3D(10.0, 0.0, 0.0)), 90*M_PI/180);
    //GCM_geom box1ContactPointPlacementId = cs.AddGeom(for1);

    cs.AddConstraint(GCM_COINCIDENT, StartPlacement1, LCSPorshen);
    cs.AddConstraint(GCM_COINCIDENT, StartPlacement1, LCSPorshen1);
    cs.AddConstraint(GCM_COINCIDENT, StartPlacement, LCSSborka4);
    //cs.AddConstraint(GCM_COINCIDENT, StartPlacement, LCSSborka5);
    cs.AddConstraint(GCM_COINCIDENT, StartPlacement2, LCSSborka16);

    // Решение ограничений
    cs.Evaluate();

    Porshen->SetPlacement(cs.GetNewPlacement3D(LCSPorshen));
    Porshen1->SetPlacement(cs.GetNewPlacement3D(LCSPorshen1));
    //Porshen2->SetPlacement(cs.GetNewPlacement3D(LCSSborka4));
    //Porshen2->SetPlacement(cs.GetNewPlacement3D(LCSSborka5));
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
