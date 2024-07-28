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

    void on_TB_Apply_clicked();

    void on_RB_EXPCustom_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    static constexpr std::array c_filePath = {"hackGU_vol1.dll", "hackGU_vol2.dll", "hackGU_vol3.dll", "hackGU_vol4.dll"};
    static constexpr std::array c_xpAddress = {0x7d4cc0, 0x8fb2d0, 0x9fa140, 0x9d9260};
    static constexpr std::array<uint8_t, 19*4> c_xpValuesOriginal = {0x95, 0x00, 0x00, 0x00
                                                                   , 0x91, 0x00, 0x00, 0x00
                                                                   , 0x8c, 0x00, 0x00, 0x00
                                                                   , 0x87, 0x00, 0x00, 0x00
                                                                   , 0x82, 0x00, 0x00, 0x00
                                                                   , 0x7d, 0x00, 0x00, 0x00
                                                                   , 0x78, 0x00, 0x00, 0x00
                                                                   , 0x73, 0x00, 0x00, 0x00
                                                                   , 0x64, 0x00, 0x00, 0x00
                                                                   , 0x55, 0x00, 0x00, 0x00
                                                                   , 0x4b, 0x00, 0x00, 0x00
                                                                   , 0x41, 0x00, 0x00, 0x00
                                                                   , 0x2d, 0x00, 0x00, 0x00
                                                                   , 0x14, 0x00, 0x00, 0x00
                                                                   , 0x0a, 0x00, 0x00, 0x00
                                                                   , 0x07, 0x00, 0x00, 0x00
                                                                   , 0x05, 0x00, 0x00, 0x00
                                                                   , 0x04, 0x00, 0x00, 0x00
                                                                   , 0x03, 0x00, 0x00, 0x00
    };
    static constexpr std::array<uint8_t, 19*4> c_xpValuesLR = 	  {0xc3, 0x00, 0x00, 0x00
                                                                 , 0xbd, 0x00, 0x00, 0x00
                                                                 , 0xb6, 0x00, 0x00, 0x00
                                                                 , 0xb0, 0x00, 0x00, 0x00
                                                                 , 0xa9, 0x00, 0x00, 0x00
                                                                 , 0xa3, 0x00, 0x00, 0x00
                                                                 , 0x9c, 0x00, 0x00, 0x00
                                                                 , 0x96, 0x00, 0x00, 0x00
                                                                 , 0x82, 0x00, 0x00, 0x00
                                                                 , 0x6f, 0x00, 0x00, 0x00
                                                                 , 0x62, 0x00, 0x00, 0x00
                                                                 , 0x55, 0x00, 0x00, 0x00
                                                                 , 0x3b, 0x00, 0x00, 0x00
                                                                 , 0x1a, 0x00, 0x00, 0x00
                                                                 , 0x0d, 0x00, 0x00, 0x00
                                                                 , 0x0a, 0x00, 0x00, 0x00
                                                                 , 0x08, 0x00, 0x00, 0x00
                                                                 , 0x06, 0x00, 0x00, 0x00
                                                                 , 0x04, 0x00, 0x00, 0x00
    };
    static constexpr std::array<uint8_t, 5> c_lvlScaleInstructions = {0xF3, 0x41, 0x0F, 0x59, 0xD8};
    static constexpr std::array c_lvlScaleAddress = {0x48f695, 0x56b5f5, 0x5744c1, 0x557cb1};
    static constexpr std::array<uint8_t, 5> c_noop = {0x90, 0x90, 0x90, 0x90, 0x90};
    std::filesystem::path FolderPath;

    void initialFolderCheck();
    void EnablePatches();
    void ReadAppliedPatches();
    void ApplyPatches();
    Q_PROPERTY(std::filesystem::path FolderPath WRITE setFolderPath FINAL)
};
#endif // MAINWINDOW_H
