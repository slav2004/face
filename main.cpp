
#include "mainwindow.h"
#include "surfacegraph.h"

#include <QApplication>
#include <QtWidgets/QWidget>
#include <QtDataVisualization/Q3DSurface>
#include <QtGui/QScreen>
#include <QtCore/qmath.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Эмулятор");
    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);


    if (!graph->hasContext())
    {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

//      SurfaceGraph *modifier = new SurfaceGraph(graph);
//    modifier->enableSqrtSinModel(1);
//    modifier->fillSqrtSinProxy();
    w.SetPlot(container);
    const int sampleCountX = 50;
    const int sampleCountZ = 50;
//    const int heightMapGridStepX = 6;
//    const int heightMapGridStepZ = 6;
    const float sampleMin = -8.0f;
    const float sampleMax = 8.0f;


    graph->setAxisX(new QValue3DAxis);
    graph->setAxisY(new QValue3DAxis);
    graph->setAxisZ(new QValue3DAxis);


    //! [0]

    QSurfaceDataProxy *m_sqrtSinProxy = new QSurfaceDataProxy();
    QSurface3DSeries *m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);
    //! [0]

    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    for (int i = 0 ; i < sampleCountZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        // Keep values within range bounds, since just adding step can cause minor drift due
        // to the rounding errors.
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }

    m_sqrtSinProxy->resetArray(dataArray);

    m_sqrtSinSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    m_sqrtSinSeries->setFlatShadingEnabled(true);

    graph->axisX()->setLabelFormat("%.2f");
    graph->axisZ()->setLabelFormat("%.2f");
    graph->axisX()->setRange(sampleMin, sampleMax);
    graph->axisY()->setRange(0.0f, 2.0f);
    graph->axisZ()->setRange(sampleMin, sampleMax);
    graph->axisX()->setLabelAutoRotation(30);
    graph->axisY()->setLabelAutoRotation(90);
    graph->axisZ()->setLabelAutoRotation(30);

    QSurface3DSeries *m_heightMapSeries;
    graph->removeSeries(m_heightMapSeries);
    graph->addSeries(m_sqrtSinSeries);
    //! [3]

    //! [8]
    // Reset range sliders for Sqrt&Sin
//    float m_rangeMinX;
//    float m_rangeMinZ;
//    float m_stepX;
//    float m_stepZ;


container->show();

    w.show();
//    w.show_g();


    return a.exec();
}
