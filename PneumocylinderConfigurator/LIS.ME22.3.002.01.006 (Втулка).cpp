#include "BuildMathModel.h"

using namespace BuildMathModel;


SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_006()
{
    // ��������� ��� �������������� ������� �������� �� �������� � �������
    const double DEG_TO_RAD = M_PI / 180.0;

    //�������� ��������� ����� �� ���� X � Y
    MbCartPoint p1(0, 7);
    MbCartPoint p2(0, 13);
    MbCartPoint p3(8, 13);
    MbCartPoint p4(8, 7);

    //������������ �������� �������� ��������
    MbLineSegment* Seg1 = new MbLineSegment(p1, p2);
    MbLineSegment* Seg2 = new MbLineSegment(p2, p3);
    MbLineSegment* Seg3 = new MbLineSegment(p3, p4);
    MbLineSegment* Seg4 = new MbLineSegment(p4, p1);

    //������������ �������� �������
    MbContour* ptrContour = new MbContour();
    //���������� � ������ ���������
    ptrContour->AddSegment(Seg1);
    ptrContour->AddSegment(Seg2);
    ptrContour->AddSegment(Seg3);
    ptrContour->AddSegment(Seg4);

    // �������� ��������� - ��� ��������� � ���������� XY ��������� ��
    MbPlacement3D* place = new MbPlacement3D();
    MbPlane* ptrSurface = new MbPlane(*place);

    //�������� ���������� ��� ���� ��������
    RPArray<MbContour>* ptrContours = new RPArray<MbContour>();
    ptrContours->Add(ptrContour);

    //������, � ������� �������� �������� �� ����������
    MbSweptData* pCurves;
    pCurves = new MbSweptData(*ptrSurface, *ptrContours);

    // ������ ���������� ��� ���������� ��� ��������.
    RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);

    //����������� ��� �������� ���������� ���� �������� � ��� �������� ����������
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    //��� �������� ��� ���������� ����
    MbAxis3D axis(place->GetAxisX());

    // ����� �������-������� ��� ���������� �������� ���� ��������
    MbSolid* m_pResSolid = nullptr;
    MbResultType m_bResult = RevolutionSolid(*pCurves, axis, revParms, operNames, cNames, m_pResSolid);

    SolidSPtr MainSolid(m_pResSolid);
    return MainSolid;
}