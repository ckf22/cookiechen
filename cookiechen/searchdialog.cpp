#include "searchdialog.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QModelIndex>


searchDialog::searchDialog(Handler * _handler, QWidget *parent)
    : QWidget(parent)
{
    this->handler = _handler;
    searchName = new QLineEdit;
    openRecipeButton = new QPushButton("Öffnen");
    openRecipeButton->setEnabled(false);
    searchNameAreaLayout = new QHBoxLayout;
    searchNameAreaLayout->addWidget(searchName);
    searchNameAreaLayout->addWidget(openRecipeButton);

    recipes = new QListWidget;
    updateList();

    Layout = new QVBoxLayout;
    Layout->addLayout(searchNameAreaLayout);
    Layout->addWidget(recipes);

    setLayout(Layout);

    connect(searchName, SIGNAL(textEdited(QString)),
            this, SLOT(searchNameTextChanged(QString)));

    connect(recipes, SIGNAL(clicked(QModelIndex)),
            this, SLOT(recipeMarked(QModelIndex)));

    connect(recipes, SIGNAL(activated(QModelIndex)),
            this, SLOT(recipeSelected(QModelIndex)));

    connect(openRecipeButton, SIGNAL(clicked()),
            this, SLOT(openRecipeButtonClicked()));
}

void searchDialog::searchNameTextChanged(QString text){
    handler->get_all_recipes_name( text.toStdWString() );
    recipes->clear();
    for(auto it : *handler->find_list)
        recipes->addItem( QString::fromStdWString(it->name) );
}

void searchDialog::recipeSelected(QModelIndex index){
    close();
    emit itemSelected( handler->find_list->operator[](index.row())  );
    emit recipeSelected();
}

void searchDialog::recipeMarked(QModelIndex index){
    openRecipeButton->setEnabled(true);
    position = index.row();
}

void searchDialog::openRecipeButtonClicked(){
    close();
    emit itemSelected( handler->find_list->operator[](position)  );
    emit recipeSelected();
}

void searchDialog::updateList(){
    recipes->clear();
    for(auto& it : *handler->get_all_recipes())
        recipes->addItem( QString::fromStdWString(it->name) );
}
