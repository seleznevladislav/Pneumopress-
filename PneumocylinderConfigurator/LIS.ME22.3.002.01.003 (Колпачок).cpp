#include "BuildMathModel.h"

using namespace BuildMathModel;

const double DEG_TO_RAD = M_PI / 180.0;
//���������� ��� ��������� ���� 
double square = 95;
double squareFillet = 2;
double squareDepth = 32;
//���������� ��� ���������
double cylSize = 70;
double cylRadius = 6;
//���������� ������
double ringInner = 80;
double ringOuter = 86;
double ringDepth = 3;
// ���������� ��� ���������� ��������  
double cylSmallRad = 1.5;
double cylSmallCenter = 25;
// ���������� ��� ������������ ��������
double CenRotParamInner = 16;
double CenRotParamOutter = 26;
double CenRotParamDepthSmall = 2;
double CenRotParamDepthMedium = 10;
double CenRotParamDepthFar = 20;
double CenRotParamPoint = 24;
// ���������� ��� ��������������� ��������
//�����
double HorRotRightInner = 3;
double HorRotRightOutter = 7;
double HorRotRightSmall = 20;
double HorRotRightMedium = 22;
// ����    
double HorRotLeftInner = 8;
double HorRotLeftOuter = 15;
double HorRotLeftSmall = 25;
double HorRotLeftMedium = 28;
//����� ��� ��������� ��������
void CreateSketch(RPArray<MbContour>& _arrContours)
{
    // �������� ������� ����� ��������, � �������� � ���������� ��������� ����������.
    // ������ ������� - 8 ����� ��� ����� ����� ������� ��������� ����������.
    SArray<MbCartPoint> arrPnts(4);
    arrPnts.Add(MbCartPoint(square / 2, square / 2));
    arrPnts.Add(MbCartPoint(square / 2, -square / 2));
    arrPnts.Add(MbCartPoint(-square / 2, -square / 2));
    arrPnts.Add(MbCartPoint(-square / 2, square / 2));
    // ���������� ������ ������� �������� ������� �� ������
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = nullptr;
    ::FilletPolyContour(pPolyline, squareFillet, false, arrPnts[4], pContourPolyline);
    // ������� �������� �����, � ������� ����� ���������� ���������� � ������
    // ���������� ����� ����� ��� ���������� � �������������� ������� FilletTwoSegments
    ptrdiff_t idxSideRight1 = 0;
    ptrdiff_t idxSideRight2 = 2;
    ptrdiff_t idxSideRight3 = 4;
    // ���������� ����������
    pContourPolyline->FilletTwoSegments(idxSideRight1, squareFillet);
    pContourPolyline->FilletTwoSegments(idxSideRight2, squareFillet);
    pContourPolyline->FilletTwoSegments(idxSideRight3, squareFillet);
    _arrContours.push_back(pContourPolyline);
}
//����� ��� ������
void CreateSketch2(RPArray<MbContour>& _arrContours2)
{
    SArray<MbCartPoint> arrPnts(4);
    arrPnts.Add(MbCartPoint(ringInner / 2, squareDepth - ringDepth));
    arrPnts.Add(MbCartPoint(ringOuter / 2, squareDepth - ringDepth));
    arrPnts.Add(MbCartPoint(ringOuter / 2, squareDepth));
    arrPnts.Add(MbCartPoint(ringInner / 2, squareDepth));
    // ���������� ������ ������� �������� ������� �� ������
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);
    _arrContours2.push_back(pContourPolyline);
}
//����� ��� ��������� ������������ ��������
void CreateSketch3(RPArray<MbContour>& _arrContours3)
{
    SArray<MbCartPoint> arrPnts(8);
    arrPnts.Add(MbCartPoint(0, squareDepth));
    arrPnts.Add(MbCartPoint(CenRotParamInner / 2, squareDepth));
    arrPnts.Add(MbCartPoint(CenRotParamInner / 2, squareDepth - CenRotParamDepthSmall));
    arrPnts.Add(MbCartPoint(CenRotParamOutter / 2, squareDepth - CenRotParamDepthSmall));
    arrPnts.Add(MbCartPoint(CenRotParamOutter / 2, squareDepth - CenRotParamDepthMedium));
    arrPnts.Add(MbCartPoint(CenRotParamInner / 2, squareDepth - CenRotParamDepthMedium));
    arrPnts.Add(MbCartPoint(CenRotParamInner / 2, squareDepth - CenRotParamDepthFar));
    arrPnts.Add(MbCartPoint(0, squareDepth - CenRotParamPoint));
    // ���������� ������ ������� �������� ������� �� ������
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);
    _arrContours3.push_back(pContourPolyline);
}
//����� ��� ��������������� ��������
void CreateSketch4(RPArray<MbContour>& _arrContours4)
{
    SArray<MbCartPoint> arrPnts(8);
    arrPnts.Add(MbCartPoint(square / 2, squareDepth / 2 + HorRotRightOutter / 2));
    arrPnts.Add(MbCartPoint(square / 2 - HorRotRightSmall, squareDepth / 2 + HorRotRightOutter / 2));
    arrPnts.Add(MbCartPoint(square / 2 - HorRotRightMedium, squareDepth / 2 + HorRotRightInner / 2));
    arrPnts.Add(MbCartPoint(0, squareDepth / 2 + HorRotRightInner / 2));
    arrPnts.Add(MbCartPoint(0, squareDepth / 2 + HorRotLeftInner / 2));
    arrPnts.Add(MbCartPoint(-square / 2 + HorRotLeftMedium, squareDepth / 2 + HorRotLeftInner / 2));
    arrPnts.Add(MbCartPoint(-square / 2 + HorRotLeftSmall, squareDepth / 2 + HorRotLeftOuter / 2));
    arrPnts.Add(MbCartPoint(-square / 2, squareDepth / 2 + HorRotLeftOuter / 2));
    arrPnts.Add(MbCartPoint(-square / 2, squareDepth / 2));
    arrPnts.Add(MbCartPoint(square / 2, squareDepth / 2));
    // ���������� ������ ������� �������� ������� �� ������
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);
    _arrContours4.push_back(pContourPolyline);
}
SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_003()
{
    // ��������� �� (�� ��������� ��������� � ������� ��)
    MbPlacement3D pl;
    // �������� ���������� ��� ���� ������������
    RPArray<MbContour> arrContours;
    CreateSketch(arrContours);
    RPArray<MbContour> arrContours2;
    CreateSketch2(arrContours2);
    RPArray<MbContour> arrContours3;
    CreateSketch3(arrContours3);
    RPArray<MbContour> arrContours4;
    CreateSketch4(arrContours4);
    //���������� ��� ������������
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);
    // ����������� ��������� ������
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone);
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker namesElSolid(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker namesDupl(ct_DuplicationSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);
    // ����������� ���������
    MbPlane* pPlaneXZ = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneYZ = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(0, 1, 0),
        MbCartPoint3D(0, 0, 1));
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));
    // ������������ �������
    MbVector3D dirX(1, 0, 0);
    MbVector3D dirY(0, 1, 0);
    MbVector3D dirZ(0, 0, 1);
    //���
    MbAxis3D axiX(pl.GetAxisX());
    axiX.Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, squareDepth / 2)));
    MbAxis3D axiY(pl.GetAxisY());
    MbAxis3D axiZ(pl.GetAxisZ());
    // �������, ������������ ��� ����������� ����������� ������� ���������
    MbVector3D vecDir1(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -100, 0));
    MbVector3D vecDir2(MbCartPoint3D(0, 0, 0), MbCartPoint3D(-100, 0, 0));
    // �������, �������� ��������� ����������
    MbSweptData sweptData(*pPlaneXY, arrContours);
    MbSweptData sweptData2(*pPlaneXZ, arrContours2);
    MbSweptData sweptData3(*pPlaneXZ, arrContours3);
    MbSweptData sweptData4(*pPlaneXZ, arrContours4);
    // ��������� �������� ������������ ��� ��������� ��������
    const double high = squareDepth, low = 0;
    ExtrusionValues extrusionParams(high, low);
    // ���������� ��� ������� ���
    MbSolid* pSolid = nullptr;
    MbSolid* pCylSolid = NULL;
    MbSolid* pCylSolid1 = NULL;
    MbSolid* pDuplSolid = NULL;
    MbSolid* pRing = NULL;
    MbSolid* pRotCentr = NULL;
    MbSolid* pRotHoriz = NULL;
    //������ ����� ��� pCylSolid
    SArray<MbCartPoint3D> cylPnts(3);
    cylPnts.Add(MbCartPoint3D(cylSize / 2, cylSize / 2, 0));
    cylPnts.Add(MbCartPoint3D(cylSize / 2, cylSize / 2, (cylSize / 2) + squareDepth));
    cylPnts.Add(MbCartPoint3D(cylSize / 2, cylSize / 2 + cylRadius, 0));
    //������ ����� ��� pCylSolid1
    SArray<MbCartPoint3D> cylPnts1(3);
    cylPnts1.Add(MbCartPoint3D(cylSmallCenter, 0, squareDepth / 2));
    cylPnts1.Add(MbCartPoint3D(cylSmallCenter, 0, squareDepth));
    cylPnts1.Add(MbCartPoint3D(cylSmallCenter + cylSmallRad, 0, squareDepth / 2));
    // � �������� ������ �� ����� ���������� �����, ��������������� ������ ������ ��
    // ��������� ��������� ��������.
    DuplicationMeshValues params(false, vecDir1, cylSize, 2,
        vecDir2, cylSize, 2, &cylPnts[0]);
    //�������� ��� �������� 
    RevolutionValues revParam360(360 * DEG_TO_RAD, 0, 0);
    //revParms.shellClosed = true;
    //revParms.thickness1  = 8;
    // �������� ������������
    MbResultType resEx = ::ExtrusionSolid(sweptData, dirZ, nullptr, nullptr, false, extrusionParams, operNames, cNames, pSolid);
    //������������ ��������
    MbResultType resEx1 = ::ElementarySolid(cylPnts, et_Cylinder,
        namesElSolid, pCylSolid);
    MbResultType resEx2 = ::ElementarySolid(cylPnts1, et_Cylinder,
        namesElSolid, pCylSolid1);
    //�������� ������������
    MbResultType resDup = ::DuplicationSolid(*pCylSolid, params, namesDupl, pDuplSolid);
    //�������� ��������
    MbResultType resRot = ::RevolutionSolid(sweptData2, axiZ, revParam360,
        operNames, cNames, pRing);
    MbResultType resRot1 = ::RevolutionSolid(sweptData3, axiZ, revParam360,
        operNames, cNames, pRotCentr);
    MbResultType resRot2 = ::RevolutionSolid(sweptData4, axiX, revParam360,
        operNames, cNames, pRotHoriz);
    // ������� ��������
    MbResultType resBool = ::BooleanResult(*pSolid, cm_Copy, *pDuplSolid, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);
    MbResultType resBool1 = ::BooleanResult(*pSolid, cm_Copy, *pRing, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);
    MbResultType resBool2 = ::BooleanResult(*pSolid, cm_Copy, *pCylSolid1, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);
    MbResultType resBool3 = ::BooleanResult(*pSolid, cm_Copy, *pRotCentr, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);
    MbResultType resBool4 = ::BooleanResult(*pSolid, cm_Copy, *pRotHoriz, cm_Copy, bo_Difference,
        flagsBool, operBoolNames, pSolid);

    SolidSPtr MainSolid(pSolid);


    ::DeleteItem(pSolid);
    ::DeleteItem(pCylSolid);
    ::DeleteItem(pCylSolid1);
    ::DeleteItem(pDuplSolid);
    ::DeleteItem(pRing);
    ::DeleteItem(pRotCentr);
    ::DeleteItem(pRotHoriz);


    return MainSolid;

}