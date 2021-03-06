#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
#include <QWidget>
#include <QtCore>
#include <QtWidgets>
#include <const.h>
#include <qcustomkeysequenceedit.h>

class Label: public QLabel {
       Q_OBJECT

       public:
           Label(QWidget *parent = 0, Qt::WindowFlags f = 0): QLabel(parent, f) {}
           Label(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f) {}

       protected:
           void mousePressEvent(QMouseEvent* /*ev*/) {
               emit clicked();
           }

       signals:
           void clicked();
};

class SettingsWindow: public QWidget {
    Q_OBJECT

    public:
        SettingsWindow(Settings settings, QWidget *parent = 0);
        ~SettingsWindow();

    private:
        /* Main */
        QGroupBox* mainGroup;

        Label* autoSaveLabel;
        QCheckBox* autoSaveCheckBox;
        Label* saveDirLabel;
        QLineEdit* saveDirEdit;
        QPushButton* saveDirButton;
        Label* saveFormatLabel;
        QComboBox* saveFormatComboBox;
        Label* saveQualityLabel;
        QLineEdit* saveQualityEdit;
        Label* autoCopyLabel;
        QCheckBox* autoCopyCheckBox;
        Label* autoSendLabel;
        QCheckBox* autoSendCheckBox;
        Label* soundLabel;
        QCheckBox* soundCheckBox;

        /* Additional */
        QGroupBox* additionalGroup;

        Label* opacityLabel;
        QLineEdit* opacityEdit;
        Label* frameColorLabel;
        Label* frameColorImage;
        QPushButton* frameColorButton;
        Label* activeGrabbingLabel;
        QCheckBox* activeGrabbingCheckBox;

        /* Shortcuts */
        QGroupBox* shortcutsGroup;

        Label* partLabel;
        QCustomKeySequenceEdit* partGrabber;
        Label* fullLabel;
        QCustomKeySequenceEdit* fullGrabber;

        /* Buttons */
        QPushButton* cancelButton;
        QPushButton* saveButton;

        /* Other */
        Settings settings;

        void load();

    signals:
        void saved(Settings settings);

    private slots:
        void autoSaveChanged();
        void autoSaveLabelClicked();
        void autoSendLabelClicked();
        void autoCopyLabelClicked();
        void soundLabelClicked();
        void activeGrabbingLabelClicked();
        void saveFormatComboBoxSelected(int index);
        void saveDirButtonClicked();
        void frameColorButtonClicked();

        void saveClicked();
        void cancelClicked();
};

#endif // SETTINGSWINDOW_H
