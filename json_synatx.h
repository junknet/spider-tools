#ifndef JSON_SYNAX_H
#define JSON_SYNAX_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

  public:
    Highlighter(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text) override;

  private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat    format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat valueFormat;
    QTextCharFormat keyFormat;
};

#endif