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
        GCM_SetJournal(m_gcSystem, "SampleAnimationOfBending.jrn");
    }

    ~ConstraintSolver()
    {
        GCM_RemoveSystem(m_gcSystem);
    }

    GCM_geom AddGeom(const MbPlacement3D placement)
    {
        return GCM_AddGeom(m_gcSystem, GCM_SolidLCS(placement));
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
    SPtr<MbSolid> Aleksanyan3 = LIS_ME22_3_002_01_008();
    Aleksanyan3->SetColor(255, 58, 58);*/
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    MbPlacement3D lcs;
    InstanceSPtr Porshen(new MbInstance(*Yaganov1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    InstanceSPtr Porshen1(new MbInstance(*Morozova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen2(new MbInstance(*Zarubin1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen3(new MbInstance(*Shepovalova1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen4(new MbInstance(*Fukina1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen5(new MbInstance(*Aleksanyan1, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen6(new MbInstance(*Aleksanyan2, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
    //InstanceSPtr Porshen7(new MbInstance(*Aleksanyan3, MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0))));
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
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
    vector<SPtr<MbInstance>> pair;
    pair.push_back(PorshenComp);
    pair.push_back(Porshen1Comp);
    /*
    pair.push_back(Porshen2Comp);
    pair.push_back(Porshen3Comp);
    pair.push_back(Porshen41Comp);
    pair.push_back(Porshen42Comp);
    pair.push_back(Porshen43Comp);
    pair.push_back(Porshen44Comp);
    pair.push_back(Porshen5Comp);
    pair.push_back(Porshen6Comp);;
    pair.push_back(Porshen7Comp);*/

    MbAssembly* assm = new MbAssembly(pair);

    ConstraintSolver cs;


    GCM_geom sideIdPorshenComp = cs.AddGeom(PorshenComp->GetPlacement());
    GCM_geom StartPlacement = cs.AddGeom(MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0)));

    GCM_geom box1Id = cs.AddGeom(Porshen1Comp->GetPlacement());

    //GCM_geom box1ContactPointPlacementId = cs.AddGeom(PrepareBoxContactPointPlacement(MbPlacement3D(MbCartPoint3D(-25.0, 5.0, -0.5)), M_PI / 4));
    MbPlacement3D for1 = MbPlacement3D(MbCartPoint3D(0.0, 0.0, 0.0));
    //for1.Rotate(MbAxis3D(MbCartPoint3D(0.0,0.0,0.0), MbCartPoint3D(10.0, 0.0, 0.0)), 90*M_PI/180);
    GCM_geom box1ContactPointPlacementId = cs.AddGeom(for1);


    cs.FixGeom(StartPlacement);
    cs.FixGeom(box1ContactPointPlacementId);

    cs.AddConstraint(GCM_COINCIDENT, StartPlacement, sideIdPorshenComp);
    cs.AddConstraint(GCM_COINCIDENT, box1ContactPointPlacementId, box1Id);

    // Решение ограничений
    cs.Evaluate();

    PorshenComp->SetPlacement(cs.GetNewPlacement3D(sideIdPorshenComp));
    Porshen1Comp->SetPlacement(cs.GetNewPlacement3D(box1Id));

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
