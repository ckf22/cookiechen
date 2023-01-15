#include "recipeedit.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QSizePolicy>
#include <QComboBox>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QStringList>
#include <QStringList>
#include "class_recipe.h"
#include "class_config.cpp"
#include <iostream>

RecipeEdit::RecipeEdit(QWidget *parent)
    : QWidget{parent}
{
    initializeVariables();
}

RecipeEdit::RecipeEdit(Recipe * _recipe, QWidget *parent)
    : QWidget{parent}
{
    recipe = _recipe;
    initializeVariables();
    initializeWithRecipe(recipe);
}

void RecipeEdit::initializeVariables(){
    titleHeader = new QLabel("<b>Rezeptname<\\b>");
    title = new QLineEdit;
    categorysTitle = new QLabel("<b>Stichworte<\\b>");
    categorys = new QTextEdit;
    categorysHelp = new QLabel("<i>Einzelne Stichworte werden mit einem Komma abgretrennt<\\i>");
    describtionTitle = new QLabel("<b>Beschreibung<\\b>");
    describtion = new QTextEdit;
    ingredientsTitle = new QLabel( "<b>Zutaten<\\b>" );
    ingredientsToolBarSpacer = new QLabel;
    addIngredient = new QToolButton;
    addIngredient->setIcon( QIcon(QPixmap("../images/new-recipe.png")) );
    addIngredient->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );
    ingredientsToolBar = new QHBoxLayout;
    ingredientsToolBar->addWidget(addIngredient);
    ingredientsToolBar->addWidget(ingredientsToolBarSpacer);

    preparationTitle = new QLabel("<b>Zubereitung<\\b>");
    preparation = new QTextEdit;

    preparationHelp = new QLabel("<i>Zeilenumbruch für neuen Zubereitungsschritt<\\i>");

    okButton = new QPushButton(QIcon(QPixmap("../images/ok.png")), "ok" );
    escapeButton = new QPushButton(QIcon(QPixmap("../images/abort.png")), "Abbrechen");
    buttonBoxSpacer = new QLabel;
    buttonBoxLayout = new QHBoxLayout;
    buttonBoxLayout->addWidget( buttonBoxSpacer );
    buttonBoxLayout->addWidget( escapeButton );
    buttonBoxLayout->addWidget( okButton );

    Layout = new QVBoxLayout;
    Layout->addWidget(titleHeader);
    Layout->addWidget(title);
    Layout->addWidget(categorysTitle);
    Layout->addWidget(categorys);
    Layout->addWidget(categorysHelp);
    Layout->addWidget(describtionTitle);
    Layout->addWidget(describtion);
    Layout->addWidget(ingredientsTitle);
    Layout->addLayout(ingredientsToolBar);
    Layout->addWidget(preparationTitle);
    Layout->addWidget(preparation);
    Layout->addWidget(preparationHelp);

    scrollWidgetBuffer = new QWidget;
    scrollWidgetBuffer->setLayout(Layout);
    scrollWidgetBuffer->setSizePolicy( QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum) );

    scrollWidget = new QScrollArea;
    scrollWidget->setWidget(scrollWidgetBuffer);
    scrollWidget->setSizePolicy( QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum) );

    generelLayout = new QVBoxLayout;
    generelLayout->addWidget(scrollWidget);
    generelLayout->addLayout(buttonBoxLayout);

    setLayout(generelLayout);
    connect(addIngredient, SIGNAL(pressed()),
            this, SLOT(addIngredientButtonClicked()));
    connect(okButton, SIGNAL(clicked()),
            this, SLOT(okButtonClicked()));
    connect(escapeButton, SIGNAL(clicked()),
            this, SLOT(abortButtonClicked()));
}

void RecipeEdit::initializeWithRecipe(Recipe * _recipe){
    recipe = _recipe;
    title->setText( QString::fromStdWString(recipe->name) );
    describtion->setPlainText( QString::fromStdWString(recipe->describtion) );
    categorys->setPlainText( QString::fromStdWString(recipe->categorys[0]) );
    for(size_t i = 1; i < recipe->categorys.size(); ++i)
        categorys->setPlainText( categorys->toPlainText() + ", " + QString::fromStdWString(recipe->categorys[i]) );
    for(auto& it : editIngredientsElements){
        delete it.delIngredient;
        delete it.ingredientName;
        delete it.ingredientUnitCounter;
        delete it.ingredientUnitType;
        delete it.ingredientLayout;
    }
    editIngredientsElements.clear();
    for(auto& it : recipe->ingredients){
        editIngredeintsElementType append;
        append.ingredientName = new QLineEdit;
        append.ingredientName->setText( QString::fromStdWString(it.name) );
        append.ingredientUnitCounter = new QDoubleSpinBox;
        append.ingredientUnitCounter->setRange(0.00000001, 10000);
        append.ingredientUnitCounter->setValue(it.unit_counter);
        append.ingredientUnitType = new QComboBox;
        Config config;
        for(auto& _it : config.possibleUnitTypes){
            append.ingredientUnitType->addItem(_it);
            if( QString::fromStdWString(it.unit) == _it)
                append.ingredientUnitType->setCurrentText(_it);
        }
        append.delIngredient = new QToolButton;
        append.delIngredient->setIcon( QIcon(QPixmap("../images/delete-recipe.png")) );
        append.delIngredient->setObjectName( QString::number(editIngredientsElements.size()) );
        append.delIngredient->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );
        connect(append.delIngredient, SIGNAL(clicked()),
                this, SLOT(delIngredientButtonClicked()));

        append.ingredientLayout = new QHBoxLayout;
        append.ingredientLayout->addWidget( append.ingredientName );
        append.ingredientLayout->addWidget( append.ingredientUnitCounter );
        append.ingredientLayout->addWidget( append.ingredientUnitType );
        append.ingredientLayout->addWidget( append.delIngredient );
        Layout->insertLayout( editIngredientsElements.size()+8, append.ingredientLayout );
        // 8 ist die position zwischen dem addIngredient-button und der Zutaten-Ueberschrift
        editIngredientsElements.push_back(append);
    }
    preparation->setPlainText("");
    for(auto& it : recipe->preparation)
        preparation->setPlainText( preparation->toPlainText() + QString::fromStdWString(it) + "\n" );
}

void RecipeEdit::abortButtonClicked(){
    close();
}
void RecipeEdit::okButtonClicked(){
    recipe->name = title->text().toStdWString();
    recipe->describtion = describtion->toPlainText().toStdWString();
    recipe->categorys = {};
    QStringList buffer = categorys->toPlainText().split(",");
    for(auto& it : buffer)
        recipe->categorys.push_back(it.toStdWString());
    recipe->ingredients = {};
    for(auto& it : editIngredientsElements){
        recipe->ingredients.push_back( {it.ingredientName->text().toStdWString(),
                                        it.ingredientUnitType->currentText().toStdWString(),
                                        static_cast<long>(it.ingredientUnitCounter->value())} );
    }
    recipe->preparation = {};
    QString _buffer = preparation->toPlainText();
    buffer = _buffer.split("\n");
    for(auto& it : buffer){
        if(it.toStdString().find_first_not_of(" ") != std::string::npos)
            recipe->preparation.push_back(it.toStdWString());
    }
    emit recipeEdited();
    close();
}

void RecipeEdit::addIngredientButtonClicked(){
    editIngredeintsElementType append;
    append.ingredientName = new QLineEdit;
    append.ingredientUnitCounter = new QDoubleSpinBox;
    append.ingredientUnitCounter->setRange(0, 10000);
    append.ingredientUnitCounter->setValue(1);
    append.ingredientUnitType = new QComboBox;
    append.delIngredient = new QToolButton;
    append.delIngredient->setIcon( QIcon(QPixmap("../images/delete-recipe.png")) );
    append.delIngredient->setObjectName( QString::number(editIngredientsElements.size()) );
    append.delIngredient->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );
    connect(append.delIngredient, SIGNAL(clicked()),
            this, SLOT(delIngredientButtonClicked()));
    Config config;
    for(auto& _it : config.possibleUnitTypes){
        append.ingredientUnitType->addItem(_it);
    }
    append.ingredientLayout = new QHBoxLayout;
    append.ingredientLayout->addWidget( append.ingredientName );
    append.ingredientLayout->addWidget( append.ingredientUnitCounter );
    append.ingredientLayout->addWidget( append.ingredientUnitType );
    append.ingredientLayout->addWidget( append.delIngredient );
    Layout->insertLayout( editIngredientsElements.size()+8, append.ingredientLayout );
    editIngredientsElements.push_back(append);
}

void RecipeEdit::delIngredientButtonClicked(){
    int pos = sender()->objectName().toInt();
    delete editIngredientsElements[pos].delIngredient;
    delete editIngredientsElements[pos].ingredientLayout;
    delete editIngredientsElements[pos].ingredientName;
    delete editIngredientsElements[pos].ingredientUnitCounter;
    delete editIngredientsElements[pos].ingredientUnitType;
    editIngredientsElements.removeAt(pos);
    int i = 0;
    for(auto& it : editIngredientsElements){
        it.delIngredient->setObjectName( QString::number(i) );
        ++i;
    }
}
