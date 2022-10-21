#pragma once

#include <QWidget>
#include "ui_ParamsWidget.h"
#include "BuildParams.h"
#include "SceneParams.h"

class ParamsWidget : public QWidget
{
	Q_OBJECT

public:
	ParamsWidget(QWidget* parent = Q_NULLPTR);
	~ParamsWidget();

	BuildMathModel::BuildParams getParams_model();
	SceneParams getParams_scene();

private:
	Ui::ParamsWidget ui;
	BuildMathModel::BuildParams modelParams;
	SceneParams sceneParams;
	void updateParams_model();
	void setupForm_model();
	void updateParams_scene();
	void setupForm_scene();

public slots:
	void toggleViewSectionSlot();
	void toggleCaseTranspSlot();

private slots:
	void applyAndBuild();
	void reset();
	void sceneset();

signals:
	void buildSignal();
	void setupSceneSignal();
};
