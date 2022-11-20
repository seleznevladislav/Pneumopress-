#include "BuildMathModel.h"

using namespace c3d;
using namespace std;
using namespace BuildMathModel;

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_001()
{

    double osnovanie_lenghth = 95;// ������� �������� ���������
    double osnovanie_high = 45;//������ �������� ���������
    double sopr = 4;//���������� ���������
    double uho_d = 25;//������� ������� ����
    double uho_length = 145;  //���������� ����� ����
    double glubina = 3;//������� ���������� ������ �� ���������
    double d_vnesh = 86;//������� ������� ���������� ������ �� ���������
    double d_vnut = 80;//���������� ������� ���������� ������
    double d_otv = 12;//������� ������� ��������� �� ���� ������
    double a_kvadrata = 70;//������� ��������, ���������� ����� ����������� d_otv
    double glubina_centr_otv = 20;//������� ������� �����(�������� ���) ������������ ���������
    double d_centr_otv = 40;//������� ������� �����(�������� ���) ������������ ���������
    double glubina_centr_otv2 = 17.5;//������� ������� �����(�������� ���) ������������ ���������
    double d_centr_otv2 = 32;//������� ������������(�������� ���) ������������ ���������
    double glubina_centr_otv3 = 5;//������� �������� �����(�������� ���) ������������ ���������
    double d_centr_otv3 = 42;//������� �������� �����(�������� ���) ������������ ���������
    double glubina_centr_otv4 = 2.5;//������� ���������� �����(�������� ���) ������������ ���������
    double d_centr_otv4 = 33;//������� ���������� �����(�������� ���) ������������ ���������
    //����� ������ ����������� ��������� ������ ���� ������ osnovanie_high. � ���� �� ���������� �������� ����� �������
    double glubina_centr_otv5 = 16;//������ ���� ���������(��� ������), ��������� ���������, ����� ���������� �� ������� ����� ��������� �� ��������� d_centr_otv7,d_centr_otv8
    double a_otv = 32;//���������� �� ������ ��������� �� ���� ���������
    double d_centr_otv5 = 10;// ������������� ������� �������� �� ���������
    double d_centr_otv6 = 5;//������� �������� �� ���������
    double d_centr_otv7 = 7;//������� �������� ���������, �������������� � ���������� d_centr_otv6    
    double glubina_centr_otv7 = 19;//������� ��������� d_centr_otv7
    double d_centr_otv8 = 15.31;//������� �������� ���������, �������������� � ���������� d_centr_otv5 
    double d_centr_otv9 = 10;//������� ������� ��������� (��� �����)
    double d_massiva = 52;//������� ���������� �� ������� ����������� ��������� d_centr_otv9
    double glubina_centr_otv9 = 20;//������� ��������� d_centr_otv9
    double a = osnovanie_lenghth;
    //--------------���������-------------------------------------
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    // �������� ���� �1 - ��������������
    MbSolid* fpOsnovanie = NULL;
    // ������� ����� ��� ���������� ������������� ���� - �����
    SArray<MbCartPoint3D> blockPnts(4);
    blockPnts.Add(MbCartPoint3D(-osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2));
    blockPnts.Add(MbCartPoint3D(-osnovanie_lenghth / 2, 0, -osnovanie_lenghth / 2));
    blockPnts.Add(MbCartPoint3D(-osnovanie_lenghth / 2, osnovanie_high, osnovanie_lenghth / 2));
    blockPnts.Add(MbCartPoint3D(osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2));
    // ���������� ������������� ���� - �����
    MbResultType resBlock = ::ElementarySolid(blockPnts, et_Block,
        namesElSolid, fpOsnovanie);

    //-----------------------------------------------------------------------------------   
    SmoothValues fparams;
    MbSNameMaker filletNames(ct_FilletSolid, MbSNameMaker::i_SideNone, 0);
    fparams.distance1 = sopr;
    fparams.distance2 = sopr;
    fparams.form = st_Fillet;
    fparams.conic = 0;
    // ��������� ��������� �����, ������ ����������� � ������� �� �������� �������
    fparams.prolong = true;
    // ������ ���������� ����� �����
    fparams.smoothCorner = SmoothValues::ec_uniform;
    // ���� ���������� ������ � ����� ���������� �����������
    fparams.keepCant = ts_neutral;
    // ������� ����������
    fparams.strict = false;
    // ������ ���� ����� ��������� ����
    RPArray<MbCurveEdge> allEdges2(4, 1);
    fpOsnovanie->GetEdges(allEdges2);
    // � ������ ����� ��� ���������� ���������� ������ ���� �����
    RPArray<MbCurveEdge> initCurves2(4, 1);
    initCurves2.Add(allEdges2[2]);
    initCurves2.Add(allEdges2[5]);
    initCurves2.Add(allEdges2[7]);
    initCurves2.Add(allEdges2[0]);
    // 5) ������ ������ ��� �������
    RPArray<MbFace> initBounds2(0, 1);
    // 6) ����� ������� ���������� �����.
    MbSolid* pOsnovanie = NULL;
    MbResultType resf = ::FilletSolid(*fpOsnovanie, cm_Copy, initCurves2, initBounds2,
        fparams, filletNames, pOsnovanie);
    osnovanie_lenghth = 0;
    //-----------------------------------------------------------------------------------   
    MbCartPoint3D baseCenter1(osnovanie_lenghth / 2, osnovanie_high / 2, osnovanie_lenghth / 2 - uho_length / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter2(osnovanie_lenghth / 2, osnovanie_high / 2, osnovanie_lenghth / 2 + uho_length / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase2(osnovanie_lenghth / 2 - uho_d / 2, osnovanie_high / 2, osnovanie_lenghth / 2 + uho_length / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pSurUho = NULL;
    MbResultType resUho = ::ElementarySurface(baseCenter1, baseCenter2, pntOnBase2,
        st_CylinderSurface, pSurUho);
    // ���������� ��������������� ����
    MbSolid* pUho = nullptr;
    if (resUho == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pSurUho, namesCyl, pUho);

    }
    //-----------------------------------------------------------------------------------
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    // ����� ������� ��������: ���������� ���������� ���� � ������������
    // �������� ������ � �����.
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // �������������� ����
    MbSolid* pOsn_obsh = NULL;
    MbResultType res_osnovanie = ::BooleanResult(*pOsnovanie, cm_Copy, *pUho, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pOsn_obsh);
    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_kol1(osnovanie_lenghth / 2, osnovanie_high - glubina, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_kol2(osnovanie_lenghth / 2, osnovanie_high, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_kol2(osnovanie_lenghth / 2 + d_vnesh / 2, osnovanie_high, osnovanie_lenghth / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_vnesh = NULL;
    MbResultType resCylSurf = ::ElementarySurface(baseCenter_for_kol1, baseCenter_for_kol2, pntOnBase_for_kol2,
        st_CylinderSurface, pCylSurf_kol_vnesh);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_vnesh = nullptr;
    if (resCylSurf == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_vnesh, namesCyl, pCy_kol_vnesh);

    }

    //-----------------------------------------------------------------------------------

        // ���������� �������������� �����������
    MbCartPoint3D baseCenter_for_kol_vnut1(osnovanie_lenghth / 2, osnovanie_high - glubina, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_kol_vnut2(osnovanie_lenghth / 2, osnovanie_high, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_kol_vnut2(osnovanie_lenghth / 2 + d_vnut / 2, osnovanie_high, osnovanie_lenghth / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_vnut = NULL;
    MbResultType resCylSurf_vnut = ::ElementarySurface(baseCenter_for_kol_vnut1, baseCenter_for_kol_vnut2, pntOnBase_for_kol_vnut2,
        st_CylinderSurface, pCylSurf_kol_vnut);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_vnut = nullptr;
    if (resCylSurf_vnut == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_vnut, namesCyl, pCy_kol_vnut);

    }
    //-----------------------------------------------------------------------------------
         // �������������� ����
    MbSolid* pOsn_kol = NULL;
    MbResultType res_kol = ::BooleanResult(*pCy_kol_vnesh, cm_Copy, *pCy_kol_vnut, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_kol);

    //-----------------------------------------------------------------------------------
         // �������������� ����
    MbSolid* pOsn_obsh_virez = NULL;
    MbResultType res_virez = ::BooleanResult(*pOsn_obsh, cm_Copy, *pOsn_kol, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_virez);

    //----------------------------------------------------------------------------------- 

          //���������
    MbCartPoint3D baseCenter_for_otv1(osnovanie_lenghth / 2 - a_kvadrata / 2, 0, osnovanie_lenghth / 2 - a_kvadrata / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_otv2(osnovanie_lenghth / 2 - a_kvadrata / 2, osnovanie_high, osnovanie_lenghth / 2 - a_kvadrata / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_otv2(osnovanie_lenghth / 2 - a_kvadrata / 2 + d_otv / 2, osnovanie_high, osnovanie_lenghth / 2 - a_kvadrata / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_otv = NULL;
    MbResultType resCylSurf_otv = ::ElementarySurface(baseCenter_for_otv1, baseCenter_for_otv2, pntOnBase_for_otv2,
        st_CylinderSurface, pCylSurf_kol_otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_otv = nullptr;
    if (resCylSurf_otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_otv, namesCyl, pCy_kol_otv);

    }

    //-----------------------------------------------------------------------------------
         // ������������ ������� params � ����������� �������� ����������� �� �����
        // �������, ������������ ��� ����������� �����������
    MbVector3D vecDir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 100));
    MbVector3D vecDir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(100, 0, 0));
    // ��� ����������� �� ���� ����
    const double step1 = a_kvadrata;
    const double step2 = a_kvadrata;
    const unsigned int num1 = 2;
    const unsigned int num2 = 2;
    // � �������� ������ �� ����� ���������� �����, ��������������� ������ ������ ��
    // ��������� ��������� ��������.
    DuplicationMeshValues params(false /* ��������� �� */, vecDir1, step1, num1,
        vecDir2, step2, num2, &MbCartPoint3D(osnovanie_lenghth / 2 - a_kvadrata / 2, osnovanie_high / 2, osnovanie_lenghth / 2 - a_kvadrata / 2));
    // ���������� ����, ���������� �� ����� �� �����
    MbSolid* pDuplSolid = NULL;
    // ����������� �������� ����������� �� �����
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    // ����� �������� ����������� �� �����
    MbResultType res = ::DuplicationSolid(*pCy_kol_otv, params, namesDupl, pDuplSolid);

    // ����������� ��������������� ���������� ����


//-----------------------------------------------------------------------------------
     // �������������� ����
    MbSolid* pOsn_obsh_otv = NULL;
    MbResultType res_otv = ::BooleanResult(*pOsn_obsh_virez, cm_Copy, *pDuplSolid, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_otv);

    //-----------------------------------------------------------------------------------

          // ���������� �������������� �����������
    MbCartPoint3D baseCenter_for_centr_otv1(osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_otv2(osnovanie_lenghth / 2, glubina_centr_otv, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_otv2(osnovanie_lenghth / 2 + d_centr_otv / 2, glubina_centr_otv, osnovanie_lenghth / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_otv = NULL;
    MbResultType resCylSurf_centr_otv = ::ElementarySurface(baseCenter_for_centr_otv1, baseCenter_for_centr_otv2, pntOnBase_for_centr_otv2,
        st_CylinderSurface, pCylSurf_kol_centr_otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_otv = nullptr;
    if (resCylSurf_centr_otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_otv, namesCyl, pCy_kol_centr_otv);

    }

    //-----------------------------------------------------------------------------------
         // �������������� ����
    MbSolid* pOsn_obsh_centr_otv = NULL;
    MbResultType res_centr_otv = ::BooleanResult(*pOsn_obsh_otv, cm_Copy, *pCy_kol_centr_otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv);

    //-----------------------------------------------------------------------------------
    MbCartPoint3D baseCenter_for_centr_2otv1(osnovanie_lenghth / 2, glubina_centr_otv, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_2otv2(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_2otv2(osnovanie_lenghth / 2 + d_centr_otv2 / 2, glubina_centr_otv + glubina_centr_otv2, osnovanie_lenghth / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_2otv = NULL;
    MbResultType resCylSurf_centr_2otv = ::ElementarySurface(baseCenter_for_centr_2otv1, baseCenter_for_centr_2otv2, pntOnBase_for_centr_2otv2,
        st_CylinderSurface, pCylSurf_kol_centr_2otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_2otv = nullptr;
    if (resCylSurf_centr_2otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_2otv, namesCyl, pCy_kol_centr_2otv);

    }

    //-----------------------------------------------------------------------------------
         // �������������� ����
    MbSolid* pOsn_obsh_centr_otv2 = NULL;
    MbResultType res_centr_otv2 = ::BooleanResult(*pOsn_obsh_centr_otv, cm_Copy, *pCy_kol_centr_2otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv2);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_3otv1(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_3otv2(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_3otv2(osnovanie_lenghth / 2 + d_centr_otv3 / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3, osnovanie_lenghth / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_3otv = NULL;
    MbResultType resCylSurf_centr_3otv = ::ElementarySurface(baseCenter_for_centr_3otv1, baseCenter_for_centr_3otv2, pntOnBase_for_centr_3otv2,
        st_CylinderSurface, pCylSurf_kol_centr_3otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_3otv = nullptr;
    if (resCylSurf_centr_3otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_3otv, namesCyl, pCy_kol_centr_3otv);

    }
    //-----------------------------------------------------------------------------------    
    MbSolid* pOsn_obsh_centr_otv3 = NULL;
    MbResultType res_centr_otv3 = ::BooleanResult(*pOsn_obsh_centr_otv2, cm_Copy, *pCy_kol_centr_3otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv3);

    //-----------------------------------------------------------------------------------   

    MbCartPoint3D baseCenter_for_centr_4otv1(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_4otv2(osnovanie_lenghth / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3 + glubina_centr_otv4, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_4otv2(osnovanie_lenghth / 2 + d_centr_otv4 / 2, glubina_centr_otv + glubina_centr_otv2 + glubina_centr_otv3 + glubina_centr_otv4, osnovanie_lenghth / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_4otv = NULL;
    MbResultType resCylSurf_centr_4otv = ::ElementarySurface(baseCenter_for_centr_4otv1, baseCenter_for_centr_4otv2, pntOnBase_for_centr_4otv2,
        st_CylinderSurface, pCylSurf_kol_centr_4otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_4otv = nullptr;
    if (resCylSurf_centr_4otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_4otv, namesCyl, pCy_kol_centr_4otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv4 = NULL;
    MbResultType res_centr_otv4 = ::BooleanResult(*pOsn_obsh_centr_otv3, cm_Copy, *pCy_kol_centr_4otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv4);

    //-----------------------------------------------------------------------------------  

    MbCartPoint3D baseCenter_for_centr_5otv1(osnovanie_lenghth / 2 - a_otv, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_5otv2(osnovanie_lenghth / 2 - a_otv, osnovanie_high, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_5otv2(osnovanie_lenghth / 2 - a_otv, osnovanie_high, osnovanie_lenghth / 2 + d_centr_otv5 / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_5otv = NULL;
    MbResultType resCylSurf_centr_5otv = ::ElementarySurface(baseCenter_for_centr_5otv1, baseCenter_for_centr_5otv2, pntOnBase_for_centr_5otv2,
        st_CylinderSurface, pCylSurf_kol_centr_5otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_5otv = nullptr;
    if (resCylSurf_centr_5otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_5otv, namesCyl, pCy_kol_centr_5otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv5 = NULL;
    MbResultType res_centr_otv5 = ::BooleanResult(*pOsn_obsh_centr_otv4, cm_Copy, *pCy_kol_centr_5otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv5);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_6otv1(osnovanie_lenghth / 2 + a_otv, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_6otv2(osnovanie_lenghth / 2 + a_otv, osnovanie_high, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_6otv2(osnovanie_lenghth / 2 + a_otv, osnovanie_high, osnovanie_lenghth / 2 + d_centr_otv6 / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_6otv = NULL;
    MbResultType resCylSurf_centr_6otv = ::ElementarySurface(baseCenter_for_centr_6otv1, baseCenter_for_centr_6otv2, pntOnBase_for_centr_6otv2,
        st_CylinderSurface, pCylSurf_kol_centr_6otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_6otv = nullptr;
    if (resCylSurf_centr_6otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_6otv, namesCyl, pCy_kol_centr_6otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv6 = NULL;
    MbResultType res_centr_otv6 = ::BooleanResult(*pOsn_obsh_centr_otv5, cm_Copy, *pCy_kol_centr_6otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv6);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_7otv1(a / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 4); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_7otv2(a / 2 - glubina_centr_otv7, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_7otv2(a / 2 - glubina_centr_otv7, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2 + d_centr_otv7 / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_7otv = NULL;
    MbResultType resCylSurf_centr_7otv = ::ElementarySurface(baseCenter_for_centr_7otv1, baseCenter_for_centr_7otv2, pntOnBase_for_centr_7otv2,
        st_CylinderSurface, pCylSurf_kol_centr_7otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_7otv = nullptr;
    if (resCylSurf_centr_7otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_7otv, namesCyl, pCy_kol_centr_7otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv7 = NULL;
    MbResultType res_centr_otv7 = ::BooleanResult(*pOsn_obsh_centr_otv6, cm_Copy, *pCy_kol_centr_7otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv7);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_8otv1(-a / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_8otv2(osnovanie_lenghth / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_8otv2(osnovanie_lenghth / 2, osnovanie_high - glubina_centr_otv5, osnovanie_lenghth / 2 + d_centr_otv8 / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_8otv = NULL;
    MbResultType resCylSurf_centr_8otv = ::ElementarySurface(baseCenter_for_centr_8otv1, baseCenter_for_centr_8otv2, pntOnBase_for_centr_8otv2,
        st_CylinderSurface, pCylSurf_kol_centr_8otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_8otv = nullptr;
    if (resCylSurf_centr_8otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_8otv, namesCyl, pCy_kol_centr_8otv);

    }
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv8 = NULL;
    MbResultType res_centr_otv8 = ::BooleanResult(*pOsn_obsh_centr_otv7, cm_Copy, *pCy_kol_centr_8otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv8);

    //-----------------------------------------------------------------------------------

    MbCartPoint3D baseCenter_for_centr_9otv1(osnovanie_lenghth / 2, 0, osnovanie_lenghth / 2); // ����� ������� ���������
    MbCartPoint3D baseCenter_for_centr_9otv2(osnovanie_lenghth / 2, glubina_centr_otv9, osnovanie_lenghth / 2); // ����� ������� ���������
    // ����� �� ������ ��������� ��� �������� ������� ��������
    MbCartPoint3D pntOnBase_for_centr_9otv2(osnovanie_lenghth / 2 + d_centr_otv9 / 2, glubina_centr_otv9, osnovanie_lenghth / 2);
    // ����� ������� ���� ��� �������� ������������ �����������
    MbSurface* pCylSurf_kol_centr_9otv = NULL;
    MbResultType resCylSurf_centr_9otv = ::ElementarySurface(baseCenter_for_centr_9otv1, baseCenter_for_centr_9otv2, pntOnBase_for_centr_9otv2,
        st_CylinderSurface, pCylSurf_kol_centr_9otv);
    // ���������� ��������������� ����
    MbSolid* pCy_kol_centr_9otv = nullptr;
    if (resCylSurf_centr_9otv == rt_Success)
    {
        // ��������������� ������ ��� ���������� ��������� ��������� �������� ����
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // ����� ������� ���� ��� ���������� ���� �� ������ ������������ �����������
        MbResultType resSolid = ::ElementarySolid(*pCylSurf_kol_centr_9otv, namesCyl, pCy_kol_centr_9otv);

    }
    //-----------------------------------------------------------------------------------
        // ������������ ������� params � ����������� �������� ����������� �� �����
        // �������, ������������ �������� �� - ����������� ���������� ��� �
        // ����������� ���������� ��������� ����.
    const double DEG_TO_RAD = M_PI / 180.0;
    MbVector3D mas_vec_Dir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(100, 0, 100));
    MbVector3D mas_vec_Dir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -100, 0));
    // ��� �����������
    const double mas_step1 = d_massiva / 2;
    const double mas_step2 = 90 * DEG_TO_RAD;
    // ������� ��� 30 ��������
    // ������� ���������� �����
    unsigned int mas_num1 = 1;
    unsigned int mas_num2 = 4;
    // � �������� ������ �� ����� ���������� �����, ��������������� ������ �����.
    DuplicationMeshValues mas_params(true /* �������� �� */, mas_vec_Dir1, mas_step1, mas_num1,
        mas_vec_Dir2, mas_step2, mas_num2, &MbCartPoint3D(osnovanie_lenghth / 2, glubina_centr_otv9 / 2, osnovanie_lenghth / 2));

    // ���������� ����, ���������� �� ����� �� �����
    MbSolid* mas_pDuplSolid = NULL;
    // ����������� �������� ����������� �� �����
    MbSNameMaker mas_namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    // ����� �������� ����������� �� �����
    MbResultType mas_res = ::DuplicationSolid(*pCy_kol_centr_9otv, mas_params, mas_namesDupl, mas_pDuplSolid);
    //-----------------------------------------------------------------------------------
    MbSolid* pOsn_obsh_centr_otv9 = NULL;
    MbResultType res_centr_otv9 = ::BooleanResult(*mas_pDuplSolid, cm_Copy, *pCy_kol_centr_9otv, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pOsn_obsh_centr_otv9);

    //-----------------------------------------------------------------------------------
    MbSolid* detail002 = NULL;
    MbResultType res_centr_mas = ::BooleanResult(*pOsn_obsh_centr_otv8, cm_Copy, *pOsn_obsh_centr_otv9, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, detail002);

    //-----------------------------------------------------------------------------------
    osnovanie_lenghth = a;


    SolidSPtr MainSolid(detail002);
    return MainSolid;
}