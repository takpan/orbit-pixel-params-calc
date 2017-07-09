#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "orbitpixparams.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void storeIntVal(QString val, int *var);

    void storeDoubleVal(QString val, double *var);

    double convToRad(double angle, QString measure);

    double convToDeg(double angle);

    double convToGrad(double angle);

private slots:
    void on_hLineEdit_textChanged(const QString &arg1);

    void on_fovLineEdit_textChanged(const QString &arg1);

    void on_angLineEdit_textChanged(const QString &arg1);

    void on_rLineEdit_textChanged(const QString &arg1);

    void on_pxLineEdit_textChanged(const QString &arg1);

    void on_calcPushButton_clicked();

    void on_fovComboBox_currentIndexChanged(const QString &arg1);

    void on_angComboBox_currentIndexChanged(const QString &arg1);

    void on_selDirPushButton_clicked();

    void on_pathLineEdit_textChanged(const QString &arg1);

    void on_filenameLineEdit_textChanged(const QString &arg1);

    void on_exportPushButton_clicked();


private:   
    void clearScene(QGraphicsScene *scene);

    void drawFig();

    Ui::MainWindow *ui;

    int px;

    double h, fov, viewAng, r;

    QMessageBox msgBox;

    QString fovMeas, angMeas, dir, filename;

    OrbitPixParams *orbitPixParamsObj;

    vector<double> angVec, dAngSidesVec, pixVec, losVec;

    QGraphicsScene *scene;

};

#endif // MAINWINDOW_H
