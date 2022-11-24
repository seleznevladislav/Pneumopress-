#include "BuildMathModel.h"

using namespace BuildMathModel;

void CreateSketchxa(RPArray<MbContour>& _arrContours)
{

    // ����� ��� ��������� �������������� �� ������ �����

    SArray<MbCartPoint> arrPnts(3);
    arrPnts.Add(MbCartPoint(12, 270));
    arrPnts.Add(MbCartPoint(17, 270));
    arrPnts.Add(MbCartPoint(17, 270 - 3));

    // ���������� ������ ������� �������� ������� �� ������

    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContourPolyline);
}

SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_015()
{

    double height_cyl = 240; // ������ ������� �����
    double rad_cyl = 7; // ������ ������� 
    MbSNameMaker elNames(ct_ElementarySolid, MbSNameMaker::i_SideNone);

    // ���������� ������� 

    MbSolid* pCyl = NULL;
    {
        SArray<MbCartPoint3D> points(3);
        points.Add(MbCartPoint3D(0, 0, 0));
        points.Add(MbCartPoint3D(0, height_cyl, 0));
        points.Add(MbCartPoint3D(rad_cyl, 0, 0));

        ElementarySolid(points, et_Cylinder, elNames, pCyl);

    }

    //���������� ������ 

    double height_ver = 270; //������ ������� 
    double b = 12; // �������� ������� ������� 

    MbSolid* pBlock = NULL;

    {
        SArray<MbCartPoint3D> pntsBlock(4);
        pntsBlock.Add(MbCartPoint3D(b, height_cyl, b));
        pntsBlock.Add(MbCartPoint3D(b, height_cyl, -b));
        pntsBlock.Add(MbCartPoint3D(-b, height_cyl, -b));
        pntsBlock.Add(MbCartPoint3D(-b, height_ver, b));
        ::ElementarySolid(pntsBlock, et_Block, elNames, pBlock);
    }


    //����������� ������� � ������ 


    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
    MbSolid* pBolt = NULL;
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    ::BooleanResult(*pCyl, cm_Copy, *pBlock, cm_Copy, bo_Union,
        flagsBool, operBoolNames, pBolt);



    // �������� ������������ ��� ������ 


    MbPlacement3D pl;

    const double DEG_TO_RAD = M_PI / 180.0;

    RPArray<MbContour> _arrContours;
    CreateSketchxa(_arrContours);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0), MbCartPoint3D(0, 1, 0));
    MbSweptData sweptData(*pPlaneXY, _arrContours);

    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    // ����������� ��� �������� ���������� ���� �������� � ��� �������� ����������
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // ��� �������� ��� ���������� ����:
    MbAxis3D axis(pl.GetAxisY());

    // ����� �������-������� ��� ���������� �������� ���� ��������
    MbSolid* pTriangle = nullptr;
    MbResultType res = ::RevolutionSolid(sweptData, axis, revParms, operNames, cNames, pTriangle);



    // ������� �������� ��������� 



     // ����������� ������ ��� ���������� ���� � ������� ������� �������� 
    MbSNameMaker operBoolNames1(ct_BooleanSolid, MbSNameMaker::i_SideNone);

    // ����� ������� ��������: ���������� ���������� ���� � ������������
    // �������� ������ � �����.
    MbBooleanFlags flagsBool1;
    flagsBool1.InitBoolean(true);
    flagsBool1.SetMergingFaces(true);
    flagsBool1.SetMergingEdges(true);

    // �������������� ����
    MbSolid* pBoltik = NULL;
    // ����� ������� �������� ��� ���������� �����������.
    // ��� ���������� ��������� ���� ������ ���� �������� bo_Union �������
    // �������� bo_Difference, ��� ����������� - �������� bo_Intersect.
    MbResultType res1 = ::BooleanResult(*pBolt, cm_Copy, *pTriangle, cm_Copy, bo_Difference,
        flagsBool1, operBoolNames1, pBoltik);


    SolidSPtr MainSolid(pBoltik);

    ::DeleteItem(pBoltik);
    ::DeleteItem(pCyl);
    ::DeleteItem(pBlock);
    ::DeleteItem(pTriangle);
    ::DeleteItem(pBolt);
    return MainSolid;
}