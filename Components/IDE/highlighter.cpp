#include "highlighter.h"
#include <QRegularExpressionMatchIterator>

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    numericFormat.setForeground(Qt::darkGreen);
    numericFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("[-+]?[0-9]*\\.?[0-9]*");
    rule.format = numericFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bbool\\b" << "\\bint\\b"
                    << "\\bfloat\\b" << "\\bif\\b" << "\\bwhile\\b"
                    << "\\belse\\b" << "\\bend\\b" << "\\bnot\\b"
                    << "\\btrue\\b" << "\\band\\b";
    foreach(const QString &pattern,  keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    builtInFunctionFormat.setForeground(Qt::darkRed);
    builtInFunctionFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("Robot\\.*(ObstacleDetected|Stop|BlobVisible|SpinLeft|SpinRight|DriveForward|DriveBackward|Pause|GetBlobHAlignment|GetDistance)+\\(([\\w,]*)\\)");
    rule.format = builtInFunctionFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    singleLineCommentFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\/\/.+");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkGreen);
    quotationFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("[A-Za-z0-9]+\\(([\\w,]*)\\){1}:");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach(const HighlightingRule &rule, highlightingRules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while(matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }


    // Handle multiline comments
    setCurrentBlockState(0);

    int startIndex = 0;
    if(previousBlockState() != 1)
    {
        startIndex = text.indexOf(commentStartExpression);
    }

    while(startIndex >= 0)
    {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if(endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
