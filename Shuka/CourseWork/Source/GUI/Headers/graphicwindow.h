#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsTextItem>
#include <QFontMetrics>
#include <QMessageBox>
#include <QStringList>

#include <QDebug>

#include <math.h>

#include "../../BinaryTree/Headers/fanoshannontree.h"
#include "../../BinaryTree/Headers/decode.h"
#include "../../BinaryTree/Headers/huffmantree.h"



constexpr int DIAMETER_NODE = 52;
constexpr int SIZE_FONT = 12;
constexpr const char* const FONT = "Times";


QT_BEGIN_NAMESPACE
namespace Ui
{
class GraphicWindow;
}
QT_END_NAMESPACE


class GraphicWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicWindow (QWidget* parent = nullptr);

    ~GraphicWindow();

private slots:
    void closeEvent (QCloseEvent* event);

    void drawTree (const EncodeTree* node,
                   int depth, int nodeNo = 0);

    void drawText (const QString& text, int positionX,
                   int positionY);

    void drawEncoding (EncodeTree& node, const QString& text);

    void clearScene();

    int calculateNodePositionX (int depth, int nodeNo);

public slots:
    void huffmanEncoding (const QString& text);

    void fanoShannonEncoding (const QString& text);

    void decoding (const QString& text);

signals:
    void myCloseEvent();

private:
    Ui::GraphicWindow* ui;
    QGraphicsScene* graphicsScene;
    int currentPositionY;
};

#endif // GRAPHICWINDOW_H
