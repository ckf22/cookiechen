#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QList>
#include "class_recipe.h"


class QAction;
class QMenu;
class QMenuBar;
class QToolBar;
class QSpacerItem;
class QMenuBar;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QResizeEvent;
class QLabel;
class QFileDialog;
class QToolButton;
class QTextEdit;
class QDoubleSpinBox;
class QFileDialog;
class Handler;
class RecipeEdit;
class QMessageBox;
class searchDialog;
class QPushButton;
class QCloseEvent;
class QScrollArea;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow( Handler * _handler, QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void updateMembers(Recipe* recipe, double portions = 1);
    void recipeChanged();
    void portionsSpinBoxValueChanged(double portions);
private slots:
    void editButtonClicked(); 

    void openActClicked();
    void saveActClicked();
    void saveAsActClicked();
    void fileDialogDirectoyChoosen(QString _directory);
    void fileDialogFileChoosen(QString _filename);
    void addRecipeActClicked();
    void delRecipeActClicked();
    void delRecipe();
    void searchRecipes();
    void messageBoxAccecpted();
protected:
    void closeEvent(QCloseEvent * event);
private:
    void initializingUi();
    void initializingBasics();
    void initializingRecipeArea();
    void settingUpConnections();

    enum FileChooseDo{
        save,
        open,
        non
    };

    enum MessageBoxDo{
        delRec,
        openRec,
        openFile,
        closeWin,
        nothing
    };

    MessageBoxDo messageBoxDo = nothing;
    bool someChanges = false;
    RecipeEdit * editWindow;
    Recipe * showingRecipe;
    QFileDialog * fileDialog;
    FileChooseDo fileChooseDo = non;
    bool fileOpend = false;
    bool recipeOpend = false;
    QString directory;
    QString filename;
    Handler * handler;
    QMessageBox * messageBox;
    searchDialog * searchWindow;

    QAction * openAct;
    QAction * saveAct;
    QAction * saveAsAct;
    QAction * newAct;

    QAction * copyAct;
    QAction * cutAct;
    QAction * pasteAct;

    QAction * addRecipeAct;
    QAction * delRecipeAct;
    QAction * changeRecipeAct;
    QAction * searchAct;
    QAction * recipeShowAct;
    QAction * reloadPortionsAct;

    QAction * helpAct;
    QAction * aboutAct;

    QMenu * fileMenu;
    QMenu * editMenu;
    QMenu * recipeMenu;
    QMenu * helpMenu;
    QMenuBar * menuBar;

    QToolBar * fileToolBar;
    QToolBar * recipeToolBar;

    QSpacerItem * toolBarSpacerLeft;
    QSpacerItem * toolBarSpacerRight;

    QDoubleSpinBox * portionsSpinBox;
    QLabel * topRecipereaSpacer; // weil QLabel dynanisch verändert, wenn Fenster groesser, und sizepolicy immer Fixed
    QPushButton * editButton;

    QHBoxLayout * topRecipeAreaLayout;
    QHBoxLayout * toolBarLayout;
    QVBoxLayout * generelLayout;



    QWidget * recipeShowWidget;
    QScrollArea * recipeScrollArea;
    QPushButton * openRecipe;
    QVBoxLayout * recipeLayout;


    QLabel * title;
    QHBoxLayout * titleLayout;

    QLabel * categorys;

    QLabel * describtionTitle;
    QLabel * describtion;
    QTextEdit * describtionEdit;
    QPushButton * editDescribtionButton;
    QHBoxLayout * describtionLayout;

    QLabel * ingredientsTitle;
    QHBoxLayout * ingriedientsTitleLayout;
    QLabel * ingredientsNamesLabel;
    QLabel * ingredientsCrowdLabel;
    QHBoxLayout * ingredients;
    QHBoxLayout * ingredientsLayout;

    QLabel * preparationTitle;
    QHBoxLayout * titlePreparationLayout;
    QLabel * preparation;
};
#endif // MAINWINDOW_H
