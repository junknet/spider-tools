#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dmp_diff.hpp"
#include <QJsonDocument>
#include <iostream>
#include <string>

using namespace std;

using MyersStringDiff = MyersDiff<string>;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void InsertText(QPlainTextEdit *plainTextEdit, QString text, int fontSize, QColor fontColor, QColor backColor)
{
    QTextCharFormat fmt;
    //字体色
    fmt.setForeground(QBrush(fontColor));

    //背景色
    fmt.setBackground(QBrush(backColor));
    //字体大小
    // fmt.setFontPointSize(fontSize);

    //文本框使用以上设定
    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->mergeCurrentCharFormat(fmt);
    plainTextEdit->insertPlainText(text);
}

void DiffText(QPlainTextEdit *raw_window, QPlainTextEdit *diff_window)
{
    auto            one = raw_window->toPlainText().toStdString();
    auto            two = diff_window->toPlainText().toStdString();
    MyersStringDiff diff{
        one,
        two,
    };
    raw_window->clear();
    diff_window->clear();

    auto del_color = QColor("#ff0000");
    auto add_color = QColor("#1827ff");
    del_color.setAlphaF(0.5);
    add_color.setAlphaF(0.5);

    for (const auto &i : diff)
    {
        string text;
        text.append(i.text.from, i.text.till);
        auto q_text = QString::fromStdString(text);
        switch (i.operation)
        {
        case EQUAL:
            InsertText(raw_window, q_text, 14, QColor("black"), QColor("white"));
            InsertText(diff_window, q_text, 14, QColor("black"), QColor("white"));
            break;
        case DELETE:
            InsertText(raw_window, q_text, 14, QColor("black"), del_color);
            break;
        case INSERT:
            InsertText(diff_window, q_text, 14, QColor("black"), add_color);
            break;
        default:
            break;
        }
    }
}

bool diff_locked = false;
void MainWindow::on_diff_raw_window_textChanged()
{
    if (diff_locked)
    {
        return;
    }
    diff_locked = true;
    DiffText(ui->diff_raw_window, ui->diff_diff_window);
    diff_locked = false;
}

void MainWindow::on_diff_diff_window_textChanged()
{
    if (diff_locked)
    {
        return;
    }
    diff_locked = true;
    DiffText(ui->diff_raw_window, ui->diff_diff_window);
    diff_locked = false;
}

void MainWindow::on_json_raw_window_textChanged()
{
    auto text           = ui->json_raw_window->toPlainText();
    auto doc            = QJsonDocument::fromJson(text.toUtf8());
    auto formatted_json = doc.toJson(QJsonDocument::Indented);
    ui->json_formatted_window->setPlainText(formatted_json);
}

bool raw_changed = false;
void MainWindow::on_url_raw_window_textChanged()
{
    raw_changed     = true;
    auto text       = ui->url_raw_window->toPlainText();
    auto encode_txt = QUrl::toPercentEncoding(text);
    ui->url_encode_window->setPlainText(encode_txt);
    raw_changed = false;
}

void MainWindow::on_url_encode_window_textChanged()
{
    if (raw_changed)
    {
        return;
    }
    auto text       = ui->url_encode_window->toPlainText();
    auto decode_txt = QUrl::fromPercentEncoding(text.toUtf8());
    ui->url_raw_window->setPlainText(decode_txt);
}

void MainWindow::on_timestamp_raw_window_textChanged()
{
    auto text = ui->timestamp_raw_window->toPlainText().trimmed();
    ui->timestamp_formated_window->clear();
    if (text.length() == 10)
    {
        auto time = text.toLongLong();
        if (time)
        {
            auto formattd_time = QDateTime::fromMSecsSinceEpoch(time).toString("yyyy-MM-dd hh:mm:ss.zzz");
            ui->timestamp_formated_window->setPlainText(formattd_time);
        }
    }
}
