#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <filesystem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setFolderPath(std::filesystem::path Path);

private slots:
    void on_TB_ChooseFolder_clicked();

private:
    Ui::MainWindow *ui;
    const std::string strHack1 = "hackGU_vol1.dll";
    const std::string strHack2 = "hackGU_vol2.dll";
    const std::string strHack3 = "hackGU_vol3.dll";
    const std::string strHack4 = "hackGU_vol4.dll";
    std::filesystem::path FolderPath;

    void initialFolderCheck();
    void ReadAppliedPatches();
    Q_PROPERTY(std::filesystem::path FolderPath WRITE setFolderPath FINAL)
};
#endif // MAINWINDOW_H
