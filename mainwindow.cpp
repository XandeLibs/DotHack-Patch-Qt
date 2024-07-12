#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    if (!(exists(Temp_FolderPath/c_strHack1) ||
          exists(Temp_FolderPath/c_strHack2) ||
          exists(Temp_FolderPath/c_strHack3) ||
          exists(Temp_FolderPath/c_strHack4))){
        QMessageBox::warning(this, tr("Error"), (tr("Game folder must have the following files: \n")) +
                                                 QString::fromStdString(c_strHack1) + '\n' +
                                                 QString::fromStdString(c_strHack2) + '\n' +
                                                 QString::fromStdString(c_strHack3) + '\n' +
                                                 QString::fromStdString(c_strHack4) + '\n');
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

    if ((exists(defWinPath/c_strHack1) ||
          exists(defWinPath/c_strHack2) ||
          exists(defWinPath/c_strHack3) ||
          exists(defWinPath/c_strHack4))){
        setFolderPath(defWinPath);
    }
}

void MainWindow::ReadAppliedPatches(){
    auto dll1_filePath = QDir::toNativeSeparators(QString::fromStdString((FolderPath/c_strHack1).generic_string()));
    std::fstream dll1(dll1_filePath.toStdString());

    dll1.seekg(lvlScaleAddress[0]);
    auto byte = dll1.get();

    if(byte == lvlScaleInstructions[0]){
        ui->RB_DSEnabled->setChecked(true);
    }
    else{
        ui->RB_DSEnabled->setChecked(false);
    }

    dll1.seekg(xpAddress[0]);
    byte = dll1.get();

    switch (byte) {
    case xpValuesOriginal[0]:
        ui->RB_EXPOriginal->setChecked(true);
        break;
    case (int)((double)xpValuesOriginal[0] * 1.3):
        ui->RB_EXPLastRecode->setChecked(true);
        break;
    default:
        ui->RB_EXPCustom->setChecked(true);
        ui->LE_EXPPercent->setText(QString::number(byte / xpValuesOriginal[0] * 100));
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


}

