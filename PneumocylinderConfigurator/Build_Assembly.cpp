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
    SPtr<MbSolid> Zarubin1 = LIS_ME22_3_002_01_003();
    Zarubin1->SetColor(255, 255, 0);
    SPtr<MbSolid> Shepovalova1 = LIS_ME22_3_002_01_004();
    Shepovalova1->SetColor(0, 0, 0);
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
    /*-------------------------------------------------------------------------*/
    //Переменные для подсборки Поршень
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
    /*-------------------------------------------------------------------------*/
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


    MbAssembly* assm = new MbAssembly(pair);


    double Val1 = 0;
    MtParVariant Arg1(Val1);

    //Цилиндр и 2 крышки
    MtGeomArgument face1(Shepovalova1->GetFace(4), Porshen4Comp);
    MtGeomArgument face2(Yaganov1->GetFace(22), Porshen1Comp);
    MtGeomArgument face3(Shepovalova1->GetFace(2), Porshen4Comp);
    MtGeomArgument face4(Zarubin1->GetFace(17), Porshen3Comp);
    MtGeomArgument face5(Yaganov1->GetFace(8), Porshen1Comp);
    MtGeomArgument face6(Zarubin1->GetFace(1), Porshen3Comp);
    //Зависимость совмещения между цилиндром и крышками
    assm->AddConstraint(GCM_DISTANCE, face1, face2, Arg1);
    assm->AddConstraint(GCM_DISTANCE, face3, face4, Arg1);
    assm->AddConstraint(GCM_COINCIDENT, face5, face6);

    //Отверстия крышек и цилиндра
    MtGeomArgument hole2(Shepovalova1->GetFace(3), Porshen4Comp);
    MtGeomArgument hole3(Yaganov1->GetFace(28), Porshen1Comp);
    MtGeomArgument hole4(Zarubin1->GetFace(28), Porshen3Comp);
    //Зависимость консентричности между крышками и цилиндром
    assm->AddConstraint(GCM_CONCENTRIC, hole2, hole3);
    assm->AddConstraint(GCM_CONCENTRIC, hole2, hole4);/*!!! Перевернули крышку (Была 1 тут, потом убрал)*/
    /*
    //Параметр расстояния от крышек до цилиндра
    double Val2 = -14;
    MtParVariant Arg2(Val2);
    //Грань цилиндра штока
    MtGeomArgument Ar1(Fukina1->GetFace(0), Porshen51Comp);
    MtGeomArgument Ar2(Fukina1->GetFace(0), Porshen52Comp);
    MtGeomArgument Ar3(Fukina1->GetFace(0), Porshen53Comp);
    MtGeomArgument Ar4(Fukina1->GetFace(0), Porshen54Comp);
    //отверстия в крышке
    MtGeomArgument b1(Zarubin1->GetFace(21), Porshen3Comp);
    MtGeomArgument b2(Zarubin1->GetFace(22), Porshen3Comp);
    MtGeomArgument b3(Zarubin1->GetFace(23), Porshen3Comp);
    MtGeomArgument b4(Zarubin1->GetFace(24), Porshen3Comp);
    //Верхняя грань штока
    MtGeomArgument Ar11(Fukina1->GetFace(1), Porshen51Comp);
    MtGeomArgument Ar22(Fukina1->GetFace(1), Porshen52Comp);
    MtGeomArgument Ar33(Fukina1->GetFace(1), Porshen53Comp);
    MtGeomArgument Ar44(Fukina1->GetFace(1), Porshen54Comp);
    //Верхняя грань Крышки
    MtGeomArgument b11(Yaganov1->GetFace(0), Porshen1Comp);
    //Зависимость расстояние между штоком и крышкой 
    assm->AddConstraint(GCM_DISTANCE, Ar11, b11, Arg2);
    assm->AddConstraint(GCM_DISTANCE, Ar22, b11, Arg2);
    assm->AddConstraint(GCM_DISTANCE, Ar33, b11, Arg2);
    assm->AddConstraint(GCM_DISTANCE, Ar44, b11, Arg2);
    //Консентричность штоков
    assm->AddConstraint(GCM_CONCENTRIC, Ar1, b1);
    assm->AddConstraint(GCM_CONCENTRIC, Ar2, b2);
    assm->AddConstraint(GCM_CONCENTRIC, Ar3, b3);
    assm->AddConstraint(GCM_CONCENTRIC, Ar4, b4);
    */
    MtGeomArgument Ar1(Fukina11->GetFace(0), Porshen51Comp);
    MtGeomArgument Ar2(Fukina12->GetFace(0), Porshen52Comp);
    MtGeomArgument Ar3(Fukina13->GetFace(0), Porshen53Comp);
    MtGeomArgument Ar4(Fukina14->GetFace(0), Porshen54Comp);
    //отверстия в крышке
    MtGeomArgument Br1(Yaganov1->GetFace(13), Porshen1Comp);
    MtGeomArgument Br2(Yaganov1->GetFace(14), Porshen1Comp);
    MtGeomArgument Br3(Yaganov1->GetFace(15), Porshen1Comp);
    MtGeomArgument Br4(Yaganov1->GetFace(16), Porshen1Comp);
    //Консентричность штоков
    assm->AddConstraint(GCM_CONCENTRIC, Ar1, Br1);
    assm->AddConstraint(GCM_CONCENTRIC, Ar2, Br2);
    assm->AddConstraint(GCM_CONCENTRIC, Ar3, Br3);
    assm->AddConstraint(GCM_CONCENTRIC, Ar4, Br4);
    
    
    
    
    assm->EvaluateConstraints();
	return assm;
}
