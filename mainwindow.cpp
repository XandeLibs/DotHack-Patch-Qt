#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("DotHack Patch");

    initialFolderCheck();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TB_ChooseFolder_clicked()
{
    auto strpath = QFileDialog::getExistingDirectory(this, tr("Game Folder"));
    std::filesystem::path Temp_FolderPath = strpath.toStdString();

    using namespace std::filesystem;

    if (!(exists(Temp_FolderPath/c_filePath[0]) ||
          exists(Temp_FolderPath/c_filePath[1]) ||
          exists(Temp_FolderPath/c_filePath[2]) ||
          exists(Temp_FolderPath/c_filePath[3]))){
        QMessageBox::warning(this, tr("Error"), (tr("Game folder must have the following files: \n")) +
                                                 QString::fromStdString(c_filePath[0]) + '\n' +
                                                 QString::fromStdString(c_filePath[1]) + '\n' +
                                                 QString::fromStdString(c_filePath[2]) + '\n' +
                                                 QString::fromStdString(c_filePath[3]) + '\n');
        return;
    }

    setFolderPath(Temp_FolderPath);
}

void MainWindow::EnablePatches(){
    ui->GB_DmgScaling->setEnabled(true);
    ui->GB_Exp->setEnabled(true);
    ui->TB_Apply->setEnabled(true);
}

void MainWindow::setFolderPath(std::filesystem::path Path){
    FolderPath = Path;
    ui->LE_FolderPath->setText(QString::fromStdString(FolderPath.string()));
    EnablePatches();
    ReadAppliedPatches();
}

void MainWindow::initialFolderCheck(){
    std::filesystem::path defWinPath = "C:/Program Files (x86)/Steam/steamapps/common/hackGU";

    if ((exists(defWinPath/c_filePath[0]) ||
          exists(defWinPath/c_filePath[1]) ||
          exists(defWinPath/c_filePath[2]) ||
          exists(defWinPath/c_filePath[3]))){
        setFolderPath(defWinPath);
    }
}

void MainWindow::ReadAppliedPatches(){
    auto dll1_filePath = QDir::toNativeSeparators(QString::fromStdString((FolderPath/c_filePath[0]).generic_string()));
    std::fstream dll1(dll1_filePath.toStdString());

    dll1.seekg(c_lvlScaleAddress[0]);
    auto byte = dll1.get();

    if(byte == c_lvlScaleInstructions[0]){
        ui->RB_DSEnabled->setChecked(true);
    }
    else{
        ui->RB_DSDisabled->setChecked(true);
    }

    dll1.seekg(c_xpAddress[0]);
    byte = dll1.get();

    switch (byte) {
    case c_xpValuesOriginal[0]:
        ui->RB_EXPOriginal->setChecked(true);
        ui->LE_EXPPercent->setEnabled(false);
        break;
    case (c_xpValuesLR[0]):
        ui->RB_EXPLastRecode->setChecked(true);
        ui->LE_EXPPercent->setEnabled(false);
        break;
    default:
        ui->RB_EXPCustom->setChecked(true);
        ui->LE_EXPPercent->setText(QString::number((int)((float)byte / (float)c_xpValuesOriginal[0] * 100)));
        break;
    }
}

void MainWindow::on_TB_Apply_clicked()
{
    if (!(ui->RB_DSDisabled->isChecked() || ui->RB_DSEnabled->isChecked())){
        return;
    }
    if (!(ui->RB_EXPOriginal->isChecked() || ui->RB_EXPLastRecode->isChecked() || ui->RB_EXPCustom->isChecked())){
        return;
    }

    auto *v_ScaleInstructions = &c_lvlScaleInstructions;
    if (ui->RB_DSDisabled->isChecked()){
        v_ScaleInstructions = &c_noop;
    }

    auto v_xpValues = c_xpValuesLR;
    if (ui->RB_EXPOriginal->isChecked()){
        v_xpValues = c_xpValuesOriginal;
    }
    else if (ui->RB_EXPCustom->isChecked()){
        v_xpValues = c_xpValuesOriginal;
        auto xpmult = ui->LE_EXPPercent->text().toFloat() / 100;
        for (int i = 0; i < v_xpValues.size(); ++i) {
            v_xpValues[i] *= xpmult;
        }
    }

    for (auto v_filenumber = 0; v_filenumber < 4; v_filenumber++){
        QFile v_file(FolderPath/c_filePath[v_filenumber]);

        v_file.open(QIODeviceBase::WriteOnly | QIODeviceBase::ExistingOnly | QIODeviceBase::Append);
        v_file.seek(c_lvlScaleAddress[v_filenumber]);
        v_file.write(reinterpret_cast<const char*>(v_ScaleInstructions->data()), v_ScaleInstructions->size());

        v_file.seek(c_xpAddress[v_filenumber]);
        v_file.write(reinterpret_cast<const char*>(v_xpValues.data()), v_xpValues.size());

        v_file.close();
    }

    QMessageBox::information(this, "Success", "Patch applied successfully");
}


void MainWindow::on_RB_EXPCustom_toggled(bool checked)
{
    ui->LE_EXPPercent->setEnabled(checked);
}

