#ifndef RECIPEEDIT_H
#define RECIPEEDIT_H

#include <QWidget>


class QDialogButtonBox;
class QLineEdit;
class QDoubleSpinBox;
class QComboBox;
class QTextEdit;
class QLabel;
class QPushButton;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QToolButton;
class Recipe;
class QCloseEvent;
class QScrollArea;

class RecipeEdit : public QWidget
{
    Q_OBJECT
public:
    explicit RecipeEdit(Recipe * _recipe, QWidget *parent = nullptr);
    explicit RecipeEdit(QWidget *parent = nullptr);
    void initializeWithRecipe(Recipe * _recipe);
signals:
    void recipeEdited();
private slots:
    void addIngredientButtonClicked();
    void delIngredientButtonClicked();
    void abortButtonClicked();
    void okButtonClicked();
private:
    void initializeVariables();
    int nextId = 0;
    Recipe * recipe;

    QLabel * titleHeader;
    QLineEdit * title;
    QLabel * categorysTitle;
    QTextEdit * categorys;
    QLabel * categorysHelp;
    QLabel * describtionTitle;
    QTextEdit * describtion;

    QLabel * ingredientsTitle;
    struct editIngredeintsElementType{
        QLineEdit * ingredientName;
        QDoubleSpinBox * ingredientUnitCounter;
        QComboBox * ingredientUnitType;
        QHBoxLayout * ingredientLayout;
        QToolButton * delIngredient;
    };
    QWidget * scrollWidgetBuffer;
    QScrollArea * scrollWidget;
    QList<editIngredeintsElementType> editIngredientsElements;
    QHBoxLayout * ingredientsToolBar;
    QLabel * ingredientsToolBarSpacer;
    QToolButton * addIngredient;

    QLabel * preparationTitle;
    QTextEdit * preparation;
    QLabel * preparationHelp;

    QPushButton * okButton;
    QPushButton * escapeButton;
    QLabel * buttonBoxSpacer;
    QHBoxLayout * buttonBoxLayout;
    QVBoxLayout * Layout;
    QVBoxLayout * generelLayout;
};

#endif // RECIPEEDIT_H
