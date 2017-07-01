#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PI 3.141592653589793

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Window title:
    MainWindow::setWindowTitle("Orbit pixel parameters calculator");

    // initializations:
    fovMeas = "deg";
    angMeas = "deg";
    OrbitPixParamsObj = NULL;

    ui->hLineEdit->setText("550");
    ui->fovLineEdit->setText("18");
    ui->angLineEdit->setText("15");
    ui->rLineEdit->setText("6371");
    ui->pxLineEdit->setText("640");


    // Validators:
    QDoubleValidator* double_validator = new QDoubleValidator(this);
    ui->hLineEdit->setValidator(double_validator);
    ui->fovLineEdit->setValidator(double_validator);
    ui->angLineEdit->setValidator(double_validator);
    ui->rLineEdit->setValidator(double_validator);

    QIntValidator* int_validator = new QIntValidator(this);
    ui->pxLineEdit->setValidator(int_validator);

    // Table widget parameters:
    ui->tableWidget->setFixedWidth(379);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(90);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(20);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->tableWidget->setColumnWidth(0,90);
    ui->tableWidget->setColumnWidth(1,90);
    ui->tableWidget->setColumnWidth(2,90);
    ui->tableWidget->setColumnWidth(3,90);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------------------------------------------------
// PRIVATE SLOTS:
//-----------------------------------------------------------------------------

// hLineEdit --> h
void MainWindow::on_hLineEdit_textChanged(const QString &arg1)
{
    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &h);
}

// fovLineEdit --> fov
void MainWindow::on_fovLineEdit_textChanged(const QString &arg1)
{
    double temp;

    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &temp);
    fov = convToRad(temp, fovMeas);
}

void MainWindow::on_fovComboBox_currentIndexChanged(const QString &arg1)
{
    double temp;

    ui->tableWidget->setRowCount(0);
    fovMeas = arg1;
    storeDoubleVal(ui->fovLineEdit->text(), &temp);
    fov = convToRad(temp, fovMeas);
}

// angLineEdit --> viewAng
void MainWindow::on_angLineEdit_textChanged(const QString &arg1)
{
    double temp;

    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &temp);
    viewAng = convToRad(temp, angMeas);
}

void MainWindow::on_angComboBox_currentIndexChanged(const QString &arg1)
{
    double temp;

    ui->tableWidget->setRowCount(0);
    angMeas = arg1;
    storeDoubleVal(ui->angLineEdit->text(), &temp);
    viewAng = convToRad(temp, angMeas);
}

// rLineEdit --> r
void MainWindow::on_rLineEdit_textChanged(const QString &arg1)
{
    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &r);
}

// pxLineEdit --> px
void MainWindow::on_pxLineEdit_textChanged(const QString &arg1)
{
    ui->tableWidget->setRowCount(0);
    storeIntVal(arg1, &px);
}

void MainWindow::on_calcPushButton_clicked()
{
    if (OrbitPixParamsObj == NULL)
        OrbitPixParamsObj = new OrbitPixParams(h, fov, viewAng, r, px); // create a OrbitPixParams object
    else
    {
        OrbitPixParamsObj->setH(h);
        OrbitPixParamsObj->setFov(fov);
        OrbitPixParamsObj->setAng(viewAng);
        OrbitPixParamsObj->setR(r);
        OrbitPixParamsObj->setPx(px);
    }

    OrbitPixParamsObj->losCalc(); // calculate the line of sight for all cases (pixels)
    OrbitPixParamsObj->pixSizeCalc(); // calculate the corresponding size (on Earth) of all pixels

    if (!OrbitPixParamsObj->getErrFov() && !OrbitPixParamsObj->getErrViewAng())
    {
        // Get the results (vectors) from OrbitPixParams class
        angVec = OrbitPixParamsObj->getAngVec();
        losVec = OrbitPixParamsObj->getLosVec();
        pixVec = OrbitPixParamsObj->getPixVec();

        // Prepare the table
        ui->tableWidget->setRowCount(px);
        ui->tableWidget->setColumnCount(4);
        QStringList header;
        header << "Pixel" << "Angle (center)" << "LoS (km)" << "Size (m)";
        ui->tableWidget->setHorizontalHeaderLabels(header);

        // Create the cells
        for(int i = 0; i < px; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem());
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }

        // Fill the table
        for (int i = 0; i < px; i++)
        {
            ui->tableWidget->item(i, 0)->setText(QString::number(i + 1));

            if (angMeas == "rad")
                ui->tableWidget->item(i, 1)->setText(QString::number(angVec[i], 'f', 5));
            else if (angMeas == "deg")
                ui->tableWidget->item(i, 1)->setText(QString::number(convToDeg(angVec[i]), 'f', 3)); // convert the output value to deg (same as the input)
            else if (angMeas == "grad")
                ui->tableWidget->item(i, 1)->setText(QString::number(convToGrad(angVec[i]), 'f', 3)); // convert the output value to grad (same as the input)

            ui->tableWidget->item(i, 2)->setText(QString::number(losVec[i], 'f', 3));
            ui->tableWidget->item(i, 3)->setText(QString::number(pixVec[i] * 1000, 'f', 2)); // convert the size to meters
        }
    }
    else
    {
        QString prTxt = QString(OrbitPixParamsObj->getErrMsg().c_str());
        if (OrbitPixParamsObj->getErrFov())
        {
            if (fovMeas == "rad")
                prTxt += " (" + QString::number(OrbitPixParamsObj->getMaxFov()) + ")";
            else if (fovMeas == "deg")
                prTxt += " (" + QString::number(convToDeg(OrbitPixParamsObj->getMaxFov())) + ")";
            else if (fovMeas == "grad")
                prTxt += " (" + QString::number(convToGrad(OrbitPixParamsObj->getMaxFov())) + ")";
        }

        else if (OrbitPixParamsObj->getErrViewAng())
        {
            if (fovMeas == "rad")
                prTxt += " (" + QString::number(OrbitPixParamsObj->getmaxViewAng()) + ")";
            else if (fovMeas == "deg")
                prTxt += " (" + QString::number(convToDeg(OrbitPixParamsObj->getmaxViewAng())) + ")";
            else if (fovMeas == "grad")
                prTxt += " (" + QString::number(convToGrad(OrbitPixParamsObj->getmaxViewAng())) + ")";
        }

        msgBox.setText(prTxt);
        msgBox.exec();
    }
}

// pathLineEdit --> dir
void MainWindow::on_pathLineEdit_textChanged(const QString &arg1)
{
    dir = arg1;
}

void MainWindow::on_selDirPushButton_clicked()
{
    dir = QFileDialog::getExistingDirectory(this, "Select directory", QCoreApplication::applicationDirPath(), QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    ui->pathLineEdit->setText(dir);
}

// filenameLineEdit --> filename
void MainWindow::on_filenameLineEdit_textChanged(const QString &arg1)
{
    filename = arg1;
}

// Expot to a text file
void MainWindow::on_exportPushButton_clicked()
{
    QString fullPath = dir + "/" + filename; // prepare the filepath
    QFileInfo info (fullPath);
    bool ok;

    ok = OrbitPixParamsObj->printToFile(fullPath.toStdString().c_str(), angMeas.toStdString());

    if(ok)
    {
        msgBox.setText("Succesful export!");
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Can't create the file. Check the file path.");
        msgBox.exec();
    }
}

//-----------------------------------------------------------------------------
// CUSTOM METHODS:
//-----------------------------------------------------------------------------

void MainWindow::storeIntVal(QString val, int *var)
{
    int temp = val.toInt();
    *var = temp;
}

void MainWindow::storeDoubleVal(QString val, double *var)
{
    double temp = val.toDouble();
    *var = temp;
}

// Convert any input to rad. Store all angles in rads
double MainWindow::convToRad(double angle, QString measure)
{
    double val;
    //const double pi = 3.141592653589793;

    if (measure == "rad")
        val = angle;
    else if (measure == "deg")
        val = (PI / 180) * angle;
    else if (measure == "grad")
        val = (PI / 200) * angle;

    return val;
}

// Convert a stored value (in rads) to degs (for presentation)
double MainWindow::convToDeg(double angle)
{
    double val;

    val = 180 * angle / PI;

    return val;
}

// Convert a stored value (in rads) to grads (for presentation)
double MainWindow::convToGrad(double angle)
{
    double val;

    val = 200 *angle / PI;

    return val;
}
