#include "screenshoter.h"
#include "qtransparentlabel.h"
#include "math.h"

/**************************************/
/*           FullScreenshoter         */
/**************************************/

void FullScreenshoter::makeScreenshot() {
    QScreen* screen = QApplication::primaryScreen();
    screenshot = screen->grabWindow(QApplication::desktop()->winId());

    if (settings.autoSave) {
        saveToFile(settings.saveDir, settings.saveFormat, settings.saveQuality);
    }

    if (settings.autoCopy) {
        QApplication::clipboard()->setImage(screenshot.toImage());
    }
}

void FullScreenshoter::saveToFile(QString filename, const char* format, int quality) {
    QDir directory;
    if (!directory.exists(filename))
        directory.mkdir(filename);

    QDateTime time = QDateTime::currentDateTime();

    if (!strcmp(format, "jpg") && !strcmp(format, "gif")) {
        screenshot.save(filename + "Screenshot " + time.toString("dd.MM.yyyy hh:mm:ss") + "." + format, format, quality);
    }
    else
        screenshot.save(filename + "Screenshot " + time.toString("dd.MM.yyyy hh:mm:ss") + "." + format, format, 40); //magic number
}

/**************************************/
/*           PartScreenshoter         */
/**************************************/

void PartScreenshoter::makeScreenshot() {
    QScreen* screen = QApplication::primaryScreen();
    screenshot = screen->grabWindow(QApplication::desktop()->winId());

    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    QLabel* image = new QLabel(this);
    image->show();
    image->setPixmap(screenshot);
    image->move(0, 0);
    image->resize(screenWidth, screenHeight);

    /* Overlays */

    QString borderStyle = "border: 1px solid gray;";

    topLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    topLeftOverlay->show();
    topLeftOverlay->setStyleSheet(borderStyle);

    topRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    topRightOverlay->show();
    topRightOverlay->setStyleSheet(borderStyle);

    bottomLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    bottomLeftOverlay->show();
    bottomLeftOverlay->setStyleSheet(borderStyle);

    bottomRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    bottomRightOverlay->show();
    bottomRightOverlay->setStyleSheet(borderStyle);

    moveOverlays();

    /* End overlays */

    installEventFilter(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowTitle("Screenshot");
    showFullScreen();

    setCursor(QCursor(QPixmap(":/img/cursor.ico")));
}

void PartScreenshoter::moveOverlays(bool isSelecting) {
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    if (!isSelecting) {
        topLeftOverlay->move(0, 0);
        topLeftOverlay->resize(cursor().pos().x(), cursor().pos().y());

        topRightOverlay->move(cursor().pos().x() - 1, 0);
        topRightOverlay->resize(screenWidth - cursor().pos().x(), cursor().pos().y());

        bottomLeftOverlay->move(0, cursor().pos().y() - 1);
        bottomLeftOverlay->resize(cursor().pos().x(), screenHeight - cursor().pos().y());

        bottomRightOverlay->move(cursor().pos().x() - 1, cursor().pos().y() - 1);
        bottomRightOverlay->resize(screenWidth - cursor().pos().x(), screenHeight - cursor().pos().y());
    } else {
        topLeftOverlay->move(0, 0);
        topLeftOverlay->resize(rect.x(), rect.y());

        topRightOverlay->move(cursor().pos().x() - 1, 0);
        topRightOverlay->resize(screenWidth - rect.width() - rect.x(), rect.y());

        bottomLeftOverlay->move(0, rect.y() - 1);
        bottomLeftOverlay->resize(rect.x(), screenHeight - rect.height() - rect.y());

        bottomRightOverlay->move(rect.x() - 1, rect.y() - 1);
        bottomRightOverlay->resize(screenWidth - rect.width() - rect.x(), screenHeight - rect.height() - rect.y());
    }
}

bool PartScreenshoter::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        switch (((QKeyEvent*) event)->key()) {
            case Qt::Key_Escape:
                close();
                break;
        }
    }

    if (event->type() == QEvent::MouseButtonPress) {
        start = QPoint(((QMouseEvent*) event)->x(), ((QMouseEvent*) event)->y());
        selecting = true;
    }

    if (event->type() == QEvent::HoverMove) {
        int tempX = ((QHoverEvent*) event)->pos().x();
        int tempY = ((QHoverEvent*) event)->pos().y();

        if (tempX < start.x()) {
            rect.setX(tempX);
            rect.setWidth(start.x() - tempX);
        } else {
            rect.setX(start.x());
            rect.setWidth(tempX - start.x());
        }

        if (tempY < start.y()) {
            rect.setY(tempY);
            rect.setHeight(start.y() - tempY);
        } else {
            rect.setY(start.y());
            rect.setHeight(tempY - start.y());
        }

        moveOverlays(selecting);

        /*QImage temp = QImage(rect.width(), rect.height(), QImage::Format_RGB888);
        for (int i = rect.x(); i < rect.x() + rect.width(); i++) {
            for (int j = rect.y(); j < rect.y() + rect.height(); j++) {

                //рисуем рамку
                if (i == rect.x() || i == rect.x() + rect.width() - 1) {
                    temp.setPixel(i - rect.x(), j - rect.y(), settings.frameColor);
                    continue;
                }

                if (j == rect.y() || j == rect.y() + rect.height() - 1) {
                    temp.setPixel(i - rect.x(), j - rect.y(), settings.frameColor);
                    continue;
                }
                //закончили рисовать

                temp.setPixel(i - rect.x(), j - rect.y(), screenshot.toImage().pixel(i, j));
            }
        }

        selected.setPixmap(QPixmap::fromImage(temp));

        if (selected.x() != rect.x() || selected.y() != rect.y())
            selected.setGeometry(rect);
        else
            selected.resize(rect.width(), rect.height());*/


    }

    if (event->type() == QEvent::MouseButtonRelease) {
        QImage temp = QImage(rect.width(), rect.height(), QImage::Format_RGB32);
        for (int i = rect.x(); i < rect.x() + rect.width(); i++) {
            for (int j = rect.y(); j < rect.y() + rect.height(); j++) {
                temp.setPixel(i - rect.x(), j - rect.y(), screenshot.toImage().pixel(i, j));
            }
        }

        QPixmap pixmap = QPixmap::fromImage(temp);

        if (settings.autoSave) {
            screenshot = pixmap;
            saveToFile(settings.saveDir, settings.saveFormat, settings.saveQuality);
        }

        if (settings.autoCopy) {
            QApplication::clipboard()->setImage(temp);
        }

        if (settings.autoSend) {
            //как-нибудь потом
        }

        selecting = false;
        close();
    }

    return QMainWindow::eventFilter(obj, event);
}
