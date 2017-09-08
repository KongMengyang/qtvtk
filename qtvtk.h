#ifndef QTVTK_H
#define QTVTK_H

#include <QtWidgets/QMainWindow>
#include "ui_qtvtk.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QColor>
#include <QIcon>
#include <QStringList>
#include <QString>
#include <QTextStream>
#include <math.h>
#include <QVector>
#include <QTableWidgetItem>

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>  
#include <vtkImageActor.h>  

#include "vtkEventQtSlotConnect.h"  
#include "vtkCommand.h" 
#include <vtkSmartPointer.h>

// To setup the ContourWidget and its representation:
#include <vtkContourWidget.h>
#include <vtkProperty.h>
#include <vtkOrientedGlyphContourRepresentation.h>
// To create the geometry:
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkMath.h>
// Usual VTK pipeline elements:
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleUser.h>

class vtkImageViewer2;
class vtkRenderer;
class vtkEventQtSlotConnect;
using namespace std;




class QtVtk : public QMainWindow
{
	Q_OBJECT

public:
	QtVtk(QWidget *parent = 0);
	~QtVtk();


	

private slots:
	//��Ӧ��ͼ���ļ��Ĳۺ���  
	void onOpenSlot();
	//��Ӧ����ƶ�����Ϣ��ʵʱ������ĵ�ǰλ��  
	void updateCoords(vtkObject* obj);
	//��ʼѡ�����Ĳۺ���
	void onMeasureSlot();

private:
	Ui::QtVtkClass ui;

	vtkSmartPointer< vtkImageViewer2 > m_pImageViewer;
	vtkSmartPointer< vtkRenderer > m_pRenderder;
	vtkEventQtSlotConnect* m_Connections;


	


};

#endif // QTVTK_H
