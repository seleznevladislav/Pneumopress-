#pragma once

#include <model.h>
#include <conv_model_exchange.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

class FileController
{
	QWidget* parentWidget = Q_NULLPTR;
public:
	FileController(QWidget* parent = Q_NULLPTR);
	~FileController();
	void setParentWidget(QWidget* parent);
	void saveModel(MbModel* ptrModel);
	MbModel* openModel();
private:
	c3d::path_string getFilePath(bool save = true);
	void exportCurrentModel(c3d::path_string path, MbModel* ptrModel);
	MbModel* importCurrentModel(c3d::path_string path);
};
