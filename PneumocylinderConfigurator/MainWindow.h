#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <model.h>

#include <QMessageBox>

#include "Viewer.h"
#include "ParamsWidget.h"
#include "SceneParams.h"
#include "BuildParams.h"
#include "BuildMathModel.h"
#include "FileController.h"

VSN_USE_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();

private:
	FileController fileController;
	MbModel* currentMathModel = nullptr;
	Ui::MainWindowClass ui;
	Viewer* viewer = Q_NULLPTR;
	ParamsWidget* paramsWidget = Q_NULLPTR;

	void drawMathModel(bool fit = true);

	void setCurrentModel(MbModel* model);
	void unsetCurrentModel();

private slots:
	void makeCylinderMathModelSlot();
	void setupViewerSceneSlot();
	void clearModelSlot();
	void aboutSlot();
	void aboutQtSlot();
	void showParamsSlot();
	void saveFileSlot();
	void openFileSlot();
};
