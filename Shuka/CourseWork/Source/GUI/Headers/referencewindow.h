#ifndef REFERENCEWINDOW_H
#define REFERENCEWINDOW_H

#include <QDialog>
#include <QFile>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui
{
class ReferenceWindow;
}
QT_END_NAMESPACE


class ReferenceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReferenceWindow (QDialog* parent = nullptr);

    ~ReferenceWindow();

signals:
    void change_textBrowser_signal (const QString& fileName);

private slots:
    void on_fanoShannon_pushButton_clicked();

    void on_huffman_pushButton_clicked();

    void on_decode_pushButton_clicked();

    void on_aboutTheProgram_pushButton_clicked();

    void change_textBrowser (const QString& fileName);

private:
    Ui::ReferenceWindow *ui;
};

#endif // REFERENCEWINDOW_H
