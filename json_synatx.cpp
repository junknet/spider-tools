#include "json_synatx.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{

    HighlightingRule rule;
    keywordFormat.setForeground(QColor("#ff26d7"));
    keywordFormat.setFontWeight(QFont::Bold);

    const QString keywordPatterns[] = {
        QStringLiteral("\\bfalse\\b"),
        QStringLiteral("\\btrue\\b"),
        QStringLiteral("\\bnull\\b"),

    };

    for (const QString &pattern : keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format  = keywordFormat;
        highlightingRules.append(rule);
    }

    numberFormat.setForeground(QColor("#11d3ff"));
    numberFormat.setFontWeight(QFont::Bold);
    auto pattern = QStringLiteral("\\s([0-9]+)");
    rule.pattern = QRegularExpression(pattern);
    rule.format  = numberFormat;
    highlightingRules.append(rule);

    valueFormat.setForeground(QColor("#3cb54a"));
    valueFormat.setFontWeight(QFont::Bold);
    pattern      = QStringLiteral(": \".*\"");
    rule.pattern = QRegularExpression(pattern);
    rule.format  = valueFormat;
    highlightingRules.append(rule);

    keyFormat.setForeground(QColor("#cda4d1"));
    keyFormat.setFontWeight(QFont::Bold);
    pattern      = QStringLiteral(" \".*?\":");
    rule.pattern = QRegularExpression(pattern);
    rule.format  = keyFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules))
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
