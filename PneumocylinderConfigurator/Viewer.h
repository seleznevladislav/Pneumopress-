#pragma once

#include <qt_openglwidget.h>
#include <vsn_vision.h>
#include <vsn_segmentfeatures.h>
#include <model.h>
#include "SceneParams.h"
#include <QTimer>
#include <QTime>


class Viewer : public QtVision::QtOpenGLSceneWidget
{
	Q_OBJECT

public:
	Viewer(QWidget* parent = Q_NULLPTR);
	~Viewer();

	/*NodeKeyVector addMathGeoms(MbItem* item, VSN::SceneSegment* sceneSegment = nullptr);*/
	NodeKeyVector addMathGeoms(MbModel* model, VSN::SceneSegment* sceneSegment = nullptr);
	NodeKeyVector addMathGeoms(MbItem* item, VSN::SceneSegment* sceneSegment = nullptr, MbMatrix3D matrix = MbMatrix3D());
	void clearScene();
	void setSceneParams(SceneParams params);
	void animation();

public slots:
	void fitSceneSlot();
	void nextOrientationSlot();
	void changeSectionPlaneSlot();
	void animationSlot();
	void animationSwitchSlot();
private:
	QTimer* timer;
	int sectionId = 0;
	SectionPlaneId m_sectionPlaneIdArr[2]{ 0,0 };
	SceneParams sceneParams;
	VSN::Orientation orientation = VSN::Orientation::IsoXYZ;
	VSN::SceneSegment* rootSceneSegment = nullptr;
	void prepareSceneBackground();
	void prepareSectionPlane();
	void updSectionState();
	void updHideElements();
	void checkHideElement(VSN::SceneSegment* seg);
};
