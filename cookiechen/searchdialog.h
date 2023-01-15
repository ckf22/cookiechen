#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QWidget>
#include <QModelIndex>
#include <QList>
#include "class_handler.h"

class QListWidget;
class QCheckBox;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QScrollArea;
class QLabel;


class searchDialog : public QWidget
{
    Q_OBJECT
public:
    explicit searchDialog(Handler * _handler, QWidget *parent = nullptr);
    void updateList();
signals:
    void itemSelected(Recipe* test);
    void recipeSelected();
private slots:
    void searchNameTextChanged(QString text);
    void recipeSelected(QModelIndex index);
    void recipeMarked(QModelIndex index);
    void openRecipeButtonClicked();
private:
    Handler * handler;


    QLineEdit * searchName;
    QPushButton * openRecipeButton;
    QHBoxLayout * searchNameAreaLayout;

    QListWidget * recipes;
    QVBoxLayout * Layout;
    size_t position = std::string::npos;
};

#endif // SEARCHDIALOG_H
