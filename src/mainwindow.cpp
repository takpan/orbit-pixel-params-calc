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
    orbitPixParamsObj = NULL;

    ui->hLineEdit->setText("550");
    ui->fovLineEdit->setText("18");
    ui->angLineEdit->setText("15");
    ui->rLineEdit->setText("6371");
    ui->pxLineEdit->setText("640");


    // Validators:
    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
    ui->hLineEdit->setValidator(doubleValidator);
    ui->angLineEdit->setValidator(doubleValidator);
    ui->rLineEdit->setValidator(doubleValidator);

    QDoubleValidator* doubleValidatorUnsigned = new QDoubleValidator(this);
    doubleValidatorUnsigned->setBottom(0); // set the lowest acceptable value
    ui->fovLineEdit->setValidator(doubleValidatorUnsigned);

    QIntValidator* intValidator = new QIntValidator(this);
    ui->pxLineEdit->setValidator(intValidator);

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
    clearScene(scene);
    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &h);
}

// fovLineEdit --> fov
void MainWindow::on_fovLineEdit_textChanged(const QString &arg1)
{
    double temp;

    clearScene(scene);
    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &temp);
    fov = convToRad(temp, fovMeas);
}

void MainWindow::on_fovComboBox_currentIndexChanged(const QString &arg1)
{
    double temp;

    clearScene(scene);
    ui->tableWidget->setRowCount(0);
    fovMeas = arg1;
    storeDoubleVal(ui->fovLineEdit->text(), &temp);
    fov = convToRad(temp, fovMeas);
}

// angLineEdit --> viewAng
void MainWindow::on_angLineEdit_textChanged(const QString &arg1)
{
    double temp;

    clearScene(scene);
    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &temp);
    viewAng = convToRad(temp, angMeas);
}

void MainWindow::on_angComboBox_currentIndexChanged(const QString &arg1)
{
    double temp;

    clearScene(scene);
    ui->tableWidget->setRowCount(0);
    angMeas = arg1;
    storeDoubleVal(ui->angLineEdit->text(), &temp);
    viewAng = convToRad(temp, angMeas);
}

// rLineEdit --> r
void MainWindow::on_rLineEdit_textChanged(const QString &arg1)
{
    clearScene(scene);
    ui->tableWidget->setRowCount(0);
    storeDoubleVal(arg1, &r);
}

// pxLineEdit --> px
void MainWindow::on_pxLineEdit_textChanged(const QString &arg1)
{
    clearScene(scene);
    ui->tableWidget->setRowCount(0);
    storeIntVal(arg1, &px);
}

void MainWindow::on_calcPushButton_clicked()
{
    if (orbitPixParamsObj == NULL)
        orbitPixParamsObj = new OrbitPixParams(h, fov, viewAng, r, px); // create a OrbitPixParams object
    else
    {
        orbitPixParamsObj->setH(h);
        orbitPixParamsObj->setFov(fov);
        orbitPixParamsObj->setAng(viewAng);
        orbitPixParamsObj->setR(r);
        orbitPixParamsObj->setPx(px);
    }

    orbitPixParamsObj->losCalc(); // calculate the line of sight for all cases (pixels)
    orbitPixParamsObj->pixSizeCalc(); // calculate the corresponding size (on Earth) of all pixels

    if (!orbitPixParamsObj->getErrFov() && !orbitPixParamsObj->getErrViewAng())
    {
        // Get the results (vectors) from OrbitPixParams class
        angVec = orbitPixParamsObj->getAngVec();
        losVec = orbitPixParamsObj->getLosVec();
        pixVec = orbitPixParamsObj->getPixVec();

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

        drawFig();
    }
    else
    {
        QString prTxt = QString(orbitPixParamsObj->getErrMsg().c_str());
        if (orbitPixParamsObj->getErrFov())
        {
            if (fovMeas == "rad")
                prTxt += " (" + QString::number(orbitPixParamsObj->getMaxFov()) + ")";
            else if (fovMeas == "deg")
                prTxt += " (" + QString::number(convToDeg(orbitPixParamsObj->getMaxFov())) + ")";
            else if (fovMeas == "grad")
                prTxt += " (" + QString::number(convToGrad(orbitPixParamsObj->getMaxFov())) + ")";
        }

        else if (orbitPixParamsObj->getErrViewAng())
        {
            if (fovMeas == "rad")
                prTxt += " (+/- " + QString::number(orbitPixParamsObj->getmaxViewAng()) + ")";
            else if (fovMeas == "deg")
                prTxt += " (+/- " + QString::number(convToDeg(orbitPixParamsObj->getmaxViewAng())) + ")";
            else if (fovMeas == "grad")
                prTxt += " (+/- " + QString::number(convToGrad(orbitPixParamsObj->getmaxViewAng())) + ")";
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

    ok = orbitPixParamsObj->printToFile(fullPath.toStdString().c_str(), angMeas.toStdString());

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

// Clear preview window
void MainWindow::clearScene(QGraphicsScene *scene)
{
    if (scene)
        scene->clear();
}

void MainWindow::drawFig()
{
    double side1Y, side1X, side2Y, side2X, side1, side2, dx, dy, factor, margin, winH, winW;
    QPixmap image;
    QGraphicsLineItem *line_1, *line_2;
    QGraphicsEllipseItem *planet;
    QPen linePen;
    QPen planetSurface;
    QBrush planetBrush;
    QColor planetFillColor;
    QGraphicsPixmapItem *pixmapItem;

    // Get the length of the fov angle sides
    side1 = orbitPixParamsObj->getDAngSizeVec()[0];
    side2 = orbitPixParamsObj->getDAngSizeVec()[px];

    // Calculate the coordinates of the end of the fov angle sides
    side1X = side1 * sin(viewAng + fov / 2);
    side1Y = side1 * cos(viewAng + fov / 2);
    side2X = side2 * sin(viewAng - fov / 2);
    side2Y = side2 * cos(viewAng - fov / 2);

    // Calculate the horizontal distance between the end of the fov angle sides
    if (viewAng >=0)
        dx = side1X - side2X > side1X ? side1X - side2X : side1X;
    else
        dx = fabs(side2X - side1X) > fabs(side2X) ? fabs(side2X - side1X) : fabs(side2X);

    // Drawing parameters
    image.load("img/sat.png");
    linePen.setWidth(2);
    linePen.setColor(Qt::gray);
    linePen.setStyle(Qt::DotLine);
    planetSurface.setWidth(2);
    planetBrush.setStyle(Qt::Dense4Pattern);
    planetFillColor.setRgb(102,77,0);
    planetBrush.setColor(planetFillColor);

    // Calculate the faactor and the margin
    winH = ui->graphicsView->height();
    winW = ui->graphicsView->width();
    dy = fabs(side1Y - side2Y);
    factor = (winH - 100) / (h + dy);
    if ((winW - 100) / dx < factor)
        factor = (winW - 100) / dx;

    if ((winW - dx * factor) > 100)
        margin = (winW - dx * factor) / 2;
    else
        margin = 50;

    scene = new QGraphicsScene;

    // Draw the lines
    line_1 = scene->addLine(r * factor, -h * factor, (-side1X + r) * factor, (side1Y - h) * factor);
    line_2 = scene->addLine(r * factor, -h * factor, (-side2X + r) * factor, (side2Y - h) * factor);
    line_1->setPen(linePen);
    line_2->setPen(linePen);

    // Draw  the satellite image
    pixmapItem = scene->addPixmap(image);
    pixmapItem->setOffset(-25, -25);
    pixmapItem->setPos(factor * r, -h * factor);
    pixmapItem->setRotation((180 / PI) * viewAng);

    // Draw the planet
    planet = scene->addEllipse(0, 0, 2 * r * factor, 2 * r * factor);
    planet->setBrush(planetBrush);
    planet->setPen(planetSurface);

    // Set the scene rectangle
    if (viewAng > fov / 2)
        scene->setSceneRect((r - side1X) * factor - margin, -h * factor - 50, winW, (h + dy) * factor + 100);
    else if (viewAng < - fov / 2)
        scene->setSceneRect(r * factor - margin, -h * factor - 50, winW, (h + dy) * factor + 100);
    else
        scene->setSceneRect((r - side1X) * factor - margin, -h * factor - 50, winW, (h + dy) * factor + 100);

    // Set the scene
    ui->graphicsView->setScene(scene);

    // Remove scroll bars
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
