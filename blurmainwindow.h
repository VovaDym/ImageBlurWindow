#ifndef IMAGEBLURWINDOW_BLURMAINWINDOW_H
#define IMAGEBLURWINDOW_BLURMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>
#include <QPainter>
#include <QImage>
#include <QString>
#include <QPixmap>
#include <QtWidgets/QSlider>



class BlurMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    BlurMainWindow(QWidget* parent = nullptr): QMainWindow(parent) {}
    QLabel* label = nullptr;
    QSlider* horizontalSlider = new QSlider(nullptr);

    QImage blurImage(QImage source,int blurRadius)
    {
        if(source.isNull()) return QImage();
        QGraphicsScene scene;
        QGraphicsPixmapItem item;
        item.setPixmap(QPixmap::fromImage(source));
        //
        auto* blur = new QGraphicsBlurEffect;
        blur->setBlurRadius(blurRadius);
        item.setGraphicsEffect(blur);
        scene.addItem(&item);
        QImage result(source.size(), QImage::Format_ARGB32);
        result.fill(Qt::transparent);
        QPainter painter(&result);
        scene.render(&painter,QRectF(),QRectF(0,0,source.width(), source.height()));
        return result;
    }

    void outLabel(QString fPath,int value)
    {
        newValue = value;
        label->clear();
        label->setPixmap(QPixmap::fromImage(blurImage(QImage(filePath),newValue).scaled(
                label->width(),label->height(),Qt::KeepAspectRatio)));
    }
public slots:

    void slot1()
    {
       newValue = 0;
       filePath = QFileDialog::getOpenFileName(nullptr, "Open", "C:/photo_non_blured/",
                                               "png files (*.png)");
       outLabel(filePath,newValue);

    };

    void slot2()
    {
        newValue = horizontalSlider->value();
        outLabel(filePath,newValue);
    }
private:
    QString filePath;
    int newValue = 0;
};

#endif //IMAGEBLURWINDOW_BLURMAINWINDOW_H
