#pragma once

#include "calculator.h"
#include "enums.h"

#include <QMainWindow>
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

    // колбэк-функцию нужно вызывать при нажатии кнопки с цифрами от 0 до 9;
    void SetDigitKeyCallback(std::function<void(int key)> cb);
    // колбэк-функцию нужно вызывать при нажатии кнопки операции (сложение, вычитание, умножение, деление, возведение в степень);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    // колбэк-функцию нужно вызывать при нажатии других кнопок;
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    // колбэк-функцию нужно вызывать при изменении типа чисел;
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:

    void on_btn_clear_clicked();
    void on_cmb_controller_currentIndexChanged(int index);
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_pow_clicked();
    void on_btn_div_clicked();
    void on_btn_mul_clicked();
    void on_btn_sub_clicked();
    void on_btn_sum_clicked();
    void on_btn_equal_clicked();
    void on_btn_switch_clicked();
    void on_btn_delete_clicked();
    void on_btn_mc_clicked();
    void on_btn_mr_clicked();
    void on_btn_ms_clicked();
    void on_tb_extra_clicked();

private:
    Ui::MainWindow* ui;
    std::function<void(int key)> digit_cb_;
    std::function<void(Operation key)> operation_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;
};