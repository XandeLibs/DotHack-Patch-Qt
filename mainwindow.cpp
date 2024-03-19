#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

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

    if (!(exists(Temp_FolderPath/strHack1) ||
          exists(Temp_FolderPath/strHack2) ||
          exists(Temp_FolderPath/strHack3) ||
          exists(Temp_FolderPath/strHack4))){
        QMessageBox::warning(this, tr("Error"), (tr("Game folder must have the following files: \n")) +
                                                 QString::fromStdString(strHack1) + '\n' +
                                                 QString::fromStdString(strHack2) + '\n' +
                                                 QString::fromStdString(strHack3) + '\n' +
                                                 QString::fromStdString(strHack4) + '\n');
        return;
    }

    setFolderPath(Temp_FolderPath);
}

void MainWindow::setFolderPath(std::filesystem::path Path){
    FolderPath = Path;
    ui->LE_FolderPath->setText(QString::fromStdString(FolderPath.string()));
    ReadAppliedPatches();
}

void MainWindow::initialFolderCheck(){
    std::filesystem::path defWinPath = "C:/Program Files (x86)/Steam/steamapps/common/hackGU";

    if ((exists(defWinPath/strHack1) ||
          exists(defWinPath/strHack2) ||
          exists(defWinPath/strHack3) ||
          exists(defWinPath/strHack4))){
        setFolderPath(defWinPath);
    }
}

void MainWindow::ReadAppliedPatches(){

}
