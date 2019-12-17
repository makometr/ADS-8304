#include "./GUI/Headers/graphicwindow.h"
#include "ui_graphicwindow.h"


GraphicWindow::GraphicWindow (QWidget* parent) :
    QWidget (parent),
    ui (new Ui::GraphicWindow)
{
    ui->setupUi (this);

    graphicsScene = new QGraphicsScene;

    currentPositionY = 0;

    ui->graphicsView->setAlignment (Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setScene (graphicsScene);
}



void GraphicWindow::closeEvent (QCloseEvent* event)
{
    Q_UNUSED (event)

    emit (myCloseEvent());
}


void GraphicWindow::drawTree (const EncodeTree* node,
                              int depth, int nodeNo)
{
    if (node == nullptr) {
        return;
    }

    QPen blackPen (Qt::black);
    QFont timesNewRoman (FONT, SIZE_FONT);
    QFontMetrics fontMetrics (timesNewRoman);


    int positionY = currentPositionY - depth * DIAMETER_NODE;
    int positionX = calculateNodePositionX (depth, nodeNo);

    graphicsScene->addEllipse (positionX, positionY,
                               DIAMETER_NODE, DIAMETER_NODE, blackPen);

    graphicsScene->addLine (positionX + DIAMETER_NODE / 2, positionY,
                            positionX + DIAMETER_NODE / 2,
                            positionY - DIAMETER_NODE / 2, blackPen);

    if (node->getLeft() != nullptr) {
        graphicsScene->addLine (positionX, positionY + DIAMETER_NODE / 2,
                                calculateNodePositionX (depth - 1,
                                                        nodeNo * 2) +
                                DIAMETER_NODE / 2, positionY +
                                DIAMETER_NODE / 2, blackPen);

        drawText ("0", calculateNodePositionX (depth - 1,
                                               nodeNo * 2) +
                  DIAMETER_NODE / 2 - fontMetrics.width ("0") *
                  2, positionY + DIAMETER_NODE / 2);
    }

    if (node->getRight() != nullptr) {
        graphicsScene->addLine (positionX + DIAMETER_NODE,
                                positionY + DIAMETER_NODE / 2,
                                calculateNodePositionX (depth - 1,
                                                        nodeNo * 2 + 1) +
                                DIAMETER_NODE / 2, positionY +
                                DIAMETER_NODE / 2,
                                blackPen);

        drawText("1", calculateNodePositionX (depth - 1,
                                              nodeNo * 2 + 1) +
                 DIAMETER_NODE / 2 + fontMetrics.width ("1"),
                 positionY + DIAMETER_NODE / 2);
    }

    if (node->isLeaf()) {
        QChar data = node->getData()->data_;

        QString result;
        if (data == ' ') {
            result = "space";
        }
        else if (data == '\n') {
            result = "\\n";
        }
        else if (data == '\t') {
            result = "tab";
        }
        else {
            result = data;
        }

        drawText (result, positionX + (DIAMETER_NODE -
                                       fontMetrics.width (result) / 2 * 3) / 2,
                  positionY + (DIAMETER_NODE - fontMetrics.height() / 2 * 3)/2);

        result = std::to_string(node->getData()->weight_).c_str();

        drawText (result, positionX + (DIAMETER_NODE -
                                       fontMetrics.width (result) / 2 * 3) / 2,
                  positionY + (DIAMETER_NODE - 1));
    }
    else {
         QString result(std::to_string(node->getData()->weight_).c_str());

         drawText (result, positionX + (DIAMETER_NODE -
                                        fontMetrics.width (result) / 2 * 3) / 2,
                   positionY + (DIAMETER_NODE - fontMetrics.height() / 2 * 3)/2);

    }

    drawTree (node->getLeft(), depth - 1, nodeNo * 2);
    drawTree (node->getRight(), depth - 1, (nodeNo * 2) + 1);
}


void GraphicWindow::drawText (const QString& text, int positionX,
                              int positionY)
{
    QGraphicsTextItem* textItem = nullptr;
    QFont timesNewRoman (FONT, SIZE_FONT);

    textItem = graphicsScene->addText (text, timesNewRoman);
    textItem->setPos (positionX, positionY);

    if (positionY == currentPositionY) {
        QFontMetrics fontMetrics (timesNewRoman);
        int nLines = text.count ('\n');
        int maxHeightChar = fontMetrics.height();
        currentPositionY += (nLines + 1) * maxHeightChar;
    }

}


void GraphicWindow::drawEncoding (EncodeTree& encodedTree,
                                  const QString& text)
{
    clearScene();

    QString encodedText = encodedTree.encodeText (text);

    {
        drawText ("Input text:", 0, currentPositionY);
        drawText (text, 0, currentPositionY);
    }

    {
        size_t height = encodedTree.getHeight();
        currentPositionY += height * DIAMETER_NODE;
        drawTree (&encodedTree, static_cast <int> (height - 1));
        currentPositionY += 2 * DIAMETER_NODE;
    }

    {
        drawText ("Encoded text:", 0, currentPositionY);
        drawText (encodedText, 0, currentPositionY);
    }

    this->show();
}


void GraphicWindow::clearScene()
{
    graphicsScene->clear();
    currentPositionY = 0;
}


int GraphicWindow::calculateNodePositionX (int depth, int nodeNo)
{
    double currentPositionX = ((pow(2, depth) - 1) / 2 +
                               pow(2, depth) * nodeNo) * DIAMETER_NODE;

    return static_cast <int> (currentPositionX);
}


void GraphicWindow::huffmanEncoding (const QString& text)
{
    HuffmanTree encodedTree;
    drawEncoding (encodedTree, text);
}


void GraphicWindow::fanoShannonEncoding (const QString& text)
{
    FanoShannonTree encodedTree;
    drawEncoding (encodedTree, text);
}


void GraphicWindow::decoding (const QString& text)
{
    clearScene();

    if (text.count ("\n\n") != 1) {
        QMessageBox::warning (this, "Error", "Incorrect input data!");
        return;
    }

    QStringList stringList = text.split ("\n\n");

    QMap <QString, QChar> characterCodes;
    QString characterCodesString = stringList[0];
    for (auto codeLine : characterCodesString.split ("\n")) {
        QStringList buffer = codeLine.split (" ");
        characterCodes.insert(buffer[buffer.size() - 1], buffer[0][0]);
    }

    qDebug() << characterCodes;

    QString encodedText = stringList[1];

    drawText ("CharacterCodes:", 0, currentPositionY);
    drawText (characterCodesString, 0, currentPositionY);

    drawText ("Encoded text:", 0, currentPositionY);
    drawText (encodedText, 0, currentPositionY);

    QPen redPen (Qt::red);
    QFont timesNewRoman (FONT, SIZE_FONT);
    QFontMetrics fontMetrics (timesNewRoman);

    int beginPositionX = 0;
    int endPositionX = 3;
    int positionY = currentPositionY + 2;

    QString buffer;
    for (auto elem : encodedText) {
        buffer += elem;
        endPositionX += fontMetrics.width (elem);

        if (characterCodes.contains (buffer)) {
            graphicsScene->addLine (beginPositionX + 3, positionY,
                                   endPositionX, positionY, redPen);

            beginPositionX = endPositionX;
            buffer.clear();
        }
    }

    QString result = decode::decode(characterCodes, encodedText);

    drawText ("Decoded text:", 0, currentPositionY);
    drawText (result, 0, currentPositionY);

    this->show();
}


GraphicWindow::~GraphicWindow()
{
    delete ui;
    delete graphicsScene;
}
