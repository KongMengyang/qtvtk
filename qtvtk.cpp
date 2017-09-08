#include "qtvtk.h"

QtVtk::QtVtk(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_pImageViewer = vtkSmartPointer< vtkImageViewer2 >::New();
	m_pRenderder = vtkSmartPointer< vtkRenderer >::New();//渲染场景
	
	connect(ui.openPushButton, SIGNAL(clicked()),this, SLOT(onOpenSlot()));
	connect(ui.measurePushbutton, SIGNAL(clicked()), this, SLOT(onMeasureSlot()));
	m_Connections = vtkEventQtSlotConnect::New();
	m_Connections->Connect(ui.qvtkWidget->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseMoveEvent,
		this,
		SLOT(updateCoords(vtkObject*)));


}

QtVtk::~QtVtk()
{

}

void QtVtk::updateCoords(vtkObject* obj)
{
	// 获取交互器  
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);

	// 获取鼠标的当前位置  
	int event_pos[2];
	iren->GetEventPosition(event_pos);

	QString str;
	str.sprintf("x=%d : y=%d", event_pos[0], event_pos[1]);
	ui.statusBar->showMessage(str);
}

void QtVtk::onOpenSlot()
{
	QString filename;
	filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图像"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty() == true) return;

	// 支持带中文路径的读取  
	QByteArray ba = filename.toLocal8Bit();
	const char *fileName_str = ba.data();

	
		
	// 设置qvtkWidget的渲染器
	
	ui.qvtkWidget->GetRenderWindow()->AddRenderer(m_pRenderder);
	// 用vtkJPEGReader读取JPG图像
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName(fileName_str);
	reader->Update();
	// 将reader的输出作为m_pImageViewer的输入，并设置m_pImageViewer与渲染器m_pRenderer的关联
	m_pImageViewer->SetInputData(reader->GetOutput());
	m_pImageViewer->UpdateDisplayExtent();
	m_pImageViewer->SetRenderWindow(ui.qvtkWidget->GetRenderWindow());//设置为同一个渲染窗口
	m_pImageViewer->SetRenderer(m_pRenderder);//设置渲染场景
	m_pImageViewer->SetupInteractor(ui.qvtkWidget->GetRenderWindow()->GetInteractor());//交互方式
	m_pImageViewer->SetSliceOrientationToXY(); //默认就是这个方向的
	m_pImageViewer->GetImageActor()->InterpolateOff();
	m_pRenderder->ResetCamera();
	m_pRenderder->DrawOn();
	ui.qvtkWidget->GetRenderWindow()->Render();//自动绘制出图像
}

void QtVtk::onMeasureSlot()
{
	// Create the contour widget
	vtkSmartPointer<vtkContourWidget> contourWidget =
		vtkSmartPointer<vtkContourWidget>::New();

	// Override the default representation for the contour widget to customize its look
	vtkSmartPointer<vtkOrientedGlyphContourRepresentation> contourRepresentation =
		vtkSmartPointer<vtkOrientedGlyphContourRepresentation>::New();
	contourRepresentation->GetLinesProperty()->SetColor(1, 0, 0); // Set color to red
	contourWidget->SetRepresentation(contourRepresentation);

	// Generate a set of points arranged in a circle
	int numPts = 10;
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	for (int i = 0; i < numPts; i++)
	{
		// Create numPts points evenly spread around a circumference of radius 0.1
		const double angle = 2.0*vtkMath::Pi()*i / numPts;
		points->InsertPoint(static_cast<vtkIdType>(i),100+100*cos(angle), 100+100*sin(angle), 0.0);
	}

	// Create a cell array to connect the points into meaningful geometry
	vtkIdType* vertexIndices = new vtkIdType[numPts + 1];
	for (int i = 0; i < numPts; i++) { vertexIndices[i] = static_cast<vtkIdType>(i); }
	// Set the last vertex to 0; this means the last line segment will join the 19th point (vertices[19])
	// with the first one (vertices[0]), thus closing the circle.
	vertexIndices[numPts] = 0;
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	lines->InsertNextCell(numPts + 1, vertexIndices);

	// Create polydata to hold the geometry just created, and populate it
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetLines(lines);

	// Create the renderer to visualize the scene
	//vtkSmartPointer<vtkRenderer> renderer = renderer = ui.qvtkWidget->GetRenderWindow()->GetRenderers();
	//renderer->SetBackground(0.1, 0.2, 0.4); // Set a dark blue background (default is black)

	// Create the GUI window to hold the rendered scene
	vtkSmartPointer<vtkRenderWindow> renderWindow = ui.qvtkWidget->GetRenderWindow();
	//renderWindow->AddRenderer(renderer);

	// Create the events manager for the renderer window
	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	// Use the "trackball camera" interactor style, rather than the default "joystick camera"
	//vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	vtkSmartPointer<vtkInteractorStyleUser> style = vtkSmartPointer<vtkInteractorStyleUser>::New();
	interactor->SetInteractorStyle(style);

	// Set up the contour widget within the visualization pipeline just assembled
	contourWidget->SetInteractor(interactor);
	contourWidget->On(); // Turn on the interactor observer
	contourWidget->Initialize(polydata);
	//m_pRenderder->ResetCamera(); // Reposition camera to fit the scene elements

							 // Start the interaction
	interactor->Start();





}