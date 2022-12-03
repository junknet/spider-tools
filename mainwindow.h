#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qsourcehighliter.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void on_url_raw_window_textChanged();

    void on_url_encode_window_textChanged();

    void on_json_raw_window_textChanged();

    void on_diff_raw_window_textChanged();

    void on_diff_diff_window_textChanged();

    void on_timestamp_raw_window_textChanged();

  private:
    Ui::MainWindow                    *ui;
    QSourceHighlite::QSourceHighliter *highlighter;
};
#endif // MAINWINDOW_H
