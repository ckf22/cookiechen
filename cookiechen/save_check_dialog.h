#ifndef SAVE_CHECK_DIALOG_H
#define SAVE_CHECK_DIALOG_H

#include <QWidget>
class QHBoxLayout;
class QVBoxLayout;
class QIcon;
class QLabel;
class QPushButton;
class QCloseEvent;
class QImage;

class save_check_dialog : public QWidget
{
    Q_OBJECT
public:
    explicit save_check_dialog(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent * event);
private:
    QImage * icon;
    QLabel * label;
    QHBoxLayout * topLayout;
    QPushButton * notSaveButton;
    QPushButton * saveButton;
    QPushButton * breakButton;
    QHBoxLayout * buttonLayout;
    QVBoxLayout * layout;
    void initialize();
signals:
    void save();
    void dontSave();
    void breaked();
};

#endif // SAVE_CHECK_DIALOG_H
