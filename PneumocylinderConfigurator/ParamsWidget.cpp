#include "ParamsWidget.h"

const bool PARAMETRIZE_DIAM = true;

ParamsWidget::ParamsWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBox_doublesided->addItem("false", QVariant(0));
	ui.comboBox_doublesided->addItem("true", QVariant(1));
	ui.comboBox_edges->addItem("false", QVariant(0));
	ui.comboBox_edges->addItem("true", QVariant(1));
	ui.comboBox_lighttype->addItem("point", QVariant(0));
	ui.comboBox_lighttype->addItem("direction", QVariant(1));
	ui.comboBox_lighttype->addItem("spot", QVariant(2));
	ui.comboBox_section->addItem("false", QVariant(0));
	ui.comboBox_section->addItem("true", QVariant(1));
	ui.comboBox_colorScheme->addItem("Жёлтый", QVariant(0));
	ui.comboBox_colorScheme->addItem("Зелёный", QVariant(1));
	ui.comboBox_config->addItem("1 вариант стола", QVariant(0));
	ui.comboBox_config->addItem("2 вариант стола", QVariant(1));
	ui.comboBox_confB->addItem("1 насадка", QVariant(0));
	ui.comboBox_confB->addItem("2 насадка", QVariant(1));
	ui.comboBox_confB->addItem("3 насадка", QVariant(2));
	

	setupForm_model();
	setupForm_scene();
	
	connect(ui.pushButton_build, &QPushButton::clicked, this, &ParamsWidget::applyAndBuild);
	connect(ui.pushButton_reset, &QPushButton::clicked, this, &ParamsWidget::reset);
	connect(ui.pushButton_sceneset, &QPushButton::clicked, this, &ParamsWidget::sceneset);
}

ParamsWidget::~ParamsWidget()
{
}

BuildMathModel::BuildParams ParamsWidget::getParams_model()
{
	//updateParams_model();
	return modelParams;
}

SceneParams ParamsWidget::getParams_scene()
{
	//updateParams_scene();
	return sceneParams;
}

void ParamsWidget::updateParams_model()
{
	
	modelParams.length = ui.doubleSpinBox_length->value();
	modelParams.colorScheme = ui.comboBox_colorScheme->currentIndex();
	modelParams.variantsConf = ui.comboBox_config->currentIndex();
	modelParams.variantsConfB = ui.comboBox_confB->currentIndex();
}

void ParamsWidget::setupForm_model()
{
	ui.doubleSpinBox_length->setValue(modelParams.length);
	ui.comboBox_colorScheme->setCurrentIndex(modelParams.colorScheme ? 1 : 0);
	ui.comboBox_config->setCurrentIndex(modelParams.variantsConf ? 0 : 1);
	ui.comboBox_confB->setCurrentIndex(modelParams.variantsConfB ? 0 : 1);
}

void ParamsWidget::updateParams_scene()
{
	sceneParams.doubleSided = ui.comboBox_doublesided->currentIndex();
	sceneParams.edges = ui.comboBox_edges->currentIndex();
	sceneParams.lightType = ui.comboBox_lighttype->currentIndex();
	sceneParams.section = ui.comboBox_section->currentIndex();
	sceneParams.frameTransp = ui.horizontalSlider_frameTransp->value();
}

void ParamsWidget::setupForm_scene()
{
	ui.comboBox_doublesided->setCurrentIndex(sceneParams.doubleSided ? 1 : 0);
	ui.comboBox_edges->setCurrentIndex(sceneParams.edges ? 1 : 0);
	ui.comboBox_lighttype->setCurrentIndex(sceneParams.lightType);
	ui.comboBox_section->setCurrentIndex(sceneParams.section ? 1 : 0);
	ui.horizontalSlider_frameTransp->setValue(sceneParams.frameTransp);
}

void ParamsWidget::toggleCaseTranspSlot()
{
	sceneParams.frameTransp = sceneParams.frameTransp > 50 ? 10 : 100;
	ui.horizontalSlider_frameTransp->setValue(sceneParams.frameTransp);
	emit setupSceneSignal();
}

void ParamsWidget::toggleViewSectionSlot()
{
	sceneParams.section = !sceneParams.section;
	ui.comboBox_section->setCurrentIndex(sceneParams.section ? 1 : 0);
	emit setupSceneSignal();
}

void ParamsWidget::applyAndBuild()
{
	updateParams_model();
	emit buildSignal();
}

void ParamsWidget::reset()
{
	modelParams = BuildMathModel::BuildParams();
	setupForm_model();
}

void ParamsWidget::sceneset()
{
	updateParams_scene();
	emit setupSceneSignal();
}
