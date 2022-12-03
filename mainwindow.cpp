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
    // fmt.setUnderlineColor("red");

    //背景色
    // fmt.setBackground(QBrush(backColor));
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

    for (const auto &i : diff)
    {
        cout << i.str() << endl;
        if (i.operation == EQUAL)
        {
            string text;
            text.append(i.text.from, i.text.till);
            auto q_text = QString::fromStdString(text);

            InsertText(raw_window, q_text, 14, QColor("black"), QColor("white"));
            InsertText(diff_window, q_text, 14, QColor("black"), QColor("white"));
        }
    }

    qDebug() << "end";
}

bool diff_started = false;
void MainWindow::on_diff_raw_window_textChanged()
{
    if (diff_started)
    {
        return;
    }
    diff_started = true;
    DiffText(ui->diff_raw_window, ui->diff_diff_window);
    diff_started = false;
}

void MainWindow::on_diff_diff_window_textChanged()
{
    if (diff_started)
    {
        return;
    }
    DiffText(ui->diff_raw_window, ui->diff_diff_window);
}

void MainWindow::on_json_raw_window_textChanged()
{
    auto text           = ui->json_raw_window->toPlainText();
    auto doc            = QJsonDocument::fromJson(text.toUtf8());
    auto formatted_json = doc.toJson(QJsonDocument::Indented);
    // ui->json_formatted_window->setPlainText(formatted_json);
    InsertText(ui->json_formatted_window, "whoami", 15, QColor("red"), QColor("black"));
    InsertText(ui->json_formatted_window, " 123", 15, QColor("yellow"), QColor("black"));
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
