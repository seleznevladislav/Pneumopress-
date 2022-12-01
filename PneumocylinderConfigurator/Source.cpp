/*
#pragma region Porshen-Krishki and cylinder
//�������� ���������� �� ������ �� ��������
double Val1 = 0;
MtParVariant Arg1(Val1);

//������� � 2 ������
MtGeomArgument face1(Shepovalova1->GetFace(4), Porshen3Comp);
MtGeomArgument face2(Yaganov1->GetFace(22), PorshenComp);
MtGeomArgument face3(Shepovalova1->GetFace(2), Porshen3Comp);
MtGeomArgument face4(Zarubin1->GetFace(17), Porshen2Comp);
MtGeomArgument face5(Yaganov1->GetFace(8), PorshenComp);
MtGeomArgument face6(Zarubin1->GetFace(1), Porshen2Comp);
//����������� ���������� ����� ��������� � ��������
assm->AddConstraint(GCM_DISTANCE, face1, face2, Arg1);
assm->AddConstraint(GCM_DISTANCE, face3, face4, Arg1);
assm->AddConstraint(GCM_COINCIDENT, face5, face6);

//��������� ������ � ��������
MtGeomArgument hole2(Shepovalova1->GetFace(3), Porshen3Comp);
MtGeomArgument hole3(Yaganov1->GetFace(28), PorshenComp);
MtGeomArgument hole4(Zarubin1->GetFace(28), Porshen2Comp);
//����������� ��������������� ����� �������� � ���������
assm->AddConstraint(GCM_CONCENTRIC, hole2, hole3);
assm->AddConstraint(GCM_CONCENTRIC, hole2, hole4);/*!!! ����������� ������ (���� 1 ���, ����� �����)
#pragma endregion

#pragma region Porshen-Krishka and sterzhni
//�������� ���������� �� ������ �� ��������
double Val2 = -14;
MtParVariant Arg2(Val2);
//����� �������� �����
MtGeomArgument Planeq1(Fukina1->GetFace(0), Porshen41Comp);
MtGeomArgument Planeq2(Fukina1->GetFace(0), Porshen42Comp);
MtGeomArgument Planeq3(Fukina1->GetFace(0), Porshen43Comp);
MtGeomArgument Planeq4(Fukina1->GetFace(0), Porshen44Comp);
//��������� � ������
MtGeomArgument Holeq1(Zarubin1->GetFace(21), Porshen2Comp);
MtGeomArgument Holeq2(Zarubin1->GetFace(22), Porshen2Comp);
MtGeomArgument Holeq3(Zarubin1->GetFace(23), Porshen2Comp);
MtGeomArgument Holeq4(Zarubin1->GetFace(24), Porshen2Comp);
//������� ����� �����
MtGeomArgument Planeq11(Fukina1->GetFace(1), Porshen41Comp);
MtGeomArgument Planeq22(Fukina1->GetFace(1), Porshen42Comp);
MtGeomArgument Planeq33(Fukina1->GetFace(1), Porshen43Comp);
MtGeomArgument Planeq44(Fukina1->GetFace(1), Porshen44Comp);
//������� ����� ������
MtGeomArgument Planeq111(Yaganov1->GetFace(0), PorshenComp);
//����������� ���������� ����� ������ � ������� 
assm->AddConstraint(GCM_DISTANCE, Planeq11, Planeq111, Arg2);
assm->AddConstraint(GCM_DISTANCE, Planeq22, Planeq111, Arg2);
assm->AddConstraint(GCM_DISTANCE, Planeq33, Planeq111, Arg2);
assm->AddConstraint(GCM_DISTANCE, Planeq44, Planeq111, Arg2);
//��������������� ������
assm->AddConstraint(GCM_CONCENTRIC, Planeq1, Holeq1);
assm->AddConstraint(GCM_CONCENTRIC, Planeq2, Holeq2);
assm->AddConstraint(GCM_CONCENTRIC, Planeq3, Holeq3);
assm->AddConstraint(GCM_CONCENTRIC, Planeq4, Holeq4);
#pragma endregion

#pragma region Porshen-Block and zazhim
double Val3 = 0;
MtParVariant Arg3(Val3);

MtGeomArgument PF1(Morozova1->GetFace(0), Porshen1Comp);
MtGeomArgument PF2(Yaganov1->GetFace(0), PorshenComp);
assm->AddConstraint(GCM_DISTANCE, PF1, PF2, Arg3);

MtGeomArgument PH1(Morozova1->GetFace(5), Porshen1Comp);
MtGeomArgument PH2(Shepovalova1->GetFace(3), Porshen3Comp);
assm->AddConstraint(GCM_CONCENTRIC, PH1, PH2);

MtGeomArgument PH3(Yaganov1->GetFace(13), PorshenComp);
MtGeomArgument PH4(Shepovalova1->GetFace(1), Porshen3Comp);
//assm->AddConstraint(GCM_CONCENTRIC, PH3, PH4);<!!! �� ������ ����������� ���������� ������ � ����� �� 4 ���������� ��� ������������>
#pragma endregion

#pragma region Porshen-Kolpachok and vtilka
double Val4 = 0;
MtParVariant Arg4(Val4);

MtGeomArgument PFQ1(Zarubin1->GetFace(16), Porshen2Comp);
MtGeomArgument PFQ2(Aleksanyan1->GetFace(1), Porshen5Comp);
assm->AddConstraint(GCM_DISTANCE, PFQ1, PFQ2, Arg4);

MtGeomArgument PHQ1(Zarubin1->GetFace(28), Porshen2Comp);
MtGeomArgument PHQ2(Aleksanyan1->GetFace(0), Porshen5Comp);
assm->AddConstraint(GCM_CONCENTRIC, PHQ1, PHQ2);
#pragma endregion

#pragma region Porshen-Block and vtulka1
double Val5 = 0;
MtParVariant Arg5(Val5);

MtGeomArgument PFW1(Yaganov1->GetFace(27), PorshenComp);
MtGeomArgument PFW2(Aleksanyan2->GetFace(17), Porshen6Comp);
assm->AddConstraint(GCM_DISTANCE, PFW1, PFW2, Arg5);

MtGeomArgument PHW1(Yaganov1->GetFace(30), PorshenComp);
MtGeomArgument PHW2(Aleksanyan2->GetFace(10), Porshen6Comp);
assm->AddConstraint(GCM_CONCENTRIC, PHW1, PHW2);
#pragma endregion

#pragma region Porshen-Block and vtulka2
double Val6 = 0;
MtParVariant Arg6(Val6);

MtGeomArgument PFE1(Yaganov1->GetFace(36), PorshenComp);
MtGeomArgument PFE2(Aleksanyan3->GetFace(1), Porshen7Comp);
assm->AddConstraint(GCM_DISTANCE, PFE1, PFE2, Arg6);

MtGeomArgument PHE1(Yaganov1->GetFace(28), PorshenComp);
MtGeomArgument PHE2(Aleksanyan3->GetFace(0), Porshen7Comp);
assm->AddConstraint(GCM_CONCENTRIC, PHE1, PHE2);

#pragma endregion

assm->EvaluateConstraints();
*/