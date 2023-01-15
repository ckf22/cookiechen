#include "mainwindow.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QIcon>
#include <QSpacerItem>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <iostream>
#include <QDoubleSpinBox>
#include <QSizePolicy>
#include <QLineEdit>
#include <QTextEdit>
#include <QScrollArea>
#include <QFileDialog>
#include <QLayoutItem>
#include <QMessageBox>
#include <QCloseEvent>
#include "searchdialog.h"
#include "recipeedit.h"
#include "class_handler.h"


MainWindow::MainWindow( Handler * _handler, QWidget *parent)
    : QWidget(parent)
{
    this->handler = _handler;
    initializingBasics();
    initializingRecipeArea();
    initializingUi();
    settingUpConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateMembers(Recipe* recipe, double portions){
    recipeOpend = true;
    showingRecipe = recipe;


    title->setText("<h2><center>"+QString::fromStdWString(recipe->name)+"<\\center><\\h2>" );
    title->setSizePolicy( QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed) );

    categorys->setText( QString::fromStdWString(recipe->categorys[0]) );
    for(size_t i = 1; i < recipe->categorys.size(); ++i)
        if(recipe->categorys[i].find_first_not_of(L" ") != std::string::npos)
            categorys->setText( categorys->text() + "," + QString::fromStdWString(recipe->categorys[i]) );
    categorys->setSizePolicy( QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed) );

    describtion->setText( QString::fromStdWString(recipe->describtion) );
    describtion->setSizePolicy( QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed) );


    QString ingredientsNames = "";
    QString ingredientsCrowds = "";
    for(auto& it : recipe->ingredients){
        ingredientsNames = ingredientsNames + QString::fromStdWString( it.name ) + " \n";
        ingredientsCrowds = ingredientsCrowds + QString::number(it.unit_counter*portions)
                + QString::fromStdWString(it.unit) + "\n";
    }
    ingredientsNamesLabel->setText(ingredientsNames);
    ingredientsCrowdLabel->setText(ingredientsCrowds);


    QString preparationSteps;
    int i = 0;
    for(auto& it : recipe->preparation)
        preparationSteps = preparationSteps + QString::number(++i) + ". " + QString::fromStdWString(it) + "\n";
    preparation->setText(preparationSteps);

    openRecipe->hide();
    recipeScrollArea->setHidden(false);
    recipeScrollArea->setSizeIncrement(recipeShowWidget->width(), recipeShowWidget->height());
}

void MainWindow::recipeChanged(){
    updateMembers(showingRecipe);
    someChanges = true;
}

void MainWindow::portionsSpinBoxValueChanged(double portions){
    QString ingredientsCrowds = "";
    for(auto& it : showingRecipe->ingredients){
        ingredientsCrowds = ingredientsCrowds + QString::number(it.unit_counter*portions)
                + QString::fromStdWString(it.unit) + "\n";
    }
    ingredientsCrowdLabel->setText(ingredientsCrowds);
}

// protected functions


void MainWindow::closeEvent(QCloseEvent * event){
    if(someChanges == true){
        event->setAccepted(false);
        messageBox->setText("Wenn sie jetzt schließen,\nwerden ihre Änderungen nicht gespeichert");
        messageBox->setWindowTitle("Programm schließen");
        messageBox->setButtonText(0, "Nicht speichern");
        messageBox->setIconPixmap(QPixmap("../images/question.png"));
        messageBoxDo = closeWin;
        messageBox->show();
    }
    else{
        event->accept();
    }
}


// Slots

void MainWindow::messageBoxAccecpted(){
    if(messageBoxDo == delRec)
        delRecipe();
    if(messageBoxDo == openRec){
        searchWindow->updateList();
        searchWindow->show();
    }
    if(messageBoxDo == closeWin)
        close();
    if(messageBoxDo == openFile){
        fileChooseDo = open;
        fileDialog->show();
    }
    messageBoxDo = nothing;
}

void MainWindow::searchRecipes(){
    if(fileOpend == true){
        searchWindow->updateList();
        searchWindow->show();
    }
    else{
        messageBox->setText( "Öffnen sie zuerst eine Datei" );
        messageBox->setWindowTitle( "Datei öffnen" );
        messageBox->setIconPixmap( QPixmap("../images/speachbubble.png") );
        messageBoxDo = openFile;
        messageBox->show();
    }
}

void MainWindow::delRecipe(){
    recipeOpend = false;
    handler->delRecipe(showingRecipe->id);
    recipeScrollArea->hide();
    openRecipe->setHidden( false );
    someChanges = true;
}

void MainWindow::addRecipeActClicked(){
    Recipe _new;
    showingRecipe = handler->addRecipe(_new);
    editWindow->initializeWithRecipe( showingRecipe );
    editWindow->show();
}

void MainWindow::delRecipeActClicked(){
    if(recipeOpend == true){
        messageBox->setText( "Soll das Rezept \""+QString::fromStdWString(showingRecipe->name)
                             +"\" \nwirklich gelöscht werden?" );
        messageBox->setWindowTitle( "Rezept löschen" );
        messageBox->setIconPixmap( QPixmap("../images/question.png") );
        messageBoxDo = delRec;
        messageBox->show();
    }
    else{
        messageBox->setText( "Es ist zurzeit kein Rezept geöffnet,\ndass Sie löschen können" );
        messageBox->setWindowTitle( "Rezept öffnen" );
        messageBox->setIconPixmap( QPixmap("../images/speachbubble.png") );
        messageBoxDo = openRec;
        messageBox->show();
    }
}

void MainWindow::editButtonClicked(){
    if(recipeOpend == true){
        editWindow->initializeWithRecipe(showingRecipe);
        editWindow->show();
    }
    else{
        messageBox->setText( "Öffnen Sie zuerst ein Rezept" );
        messageBox->setWindowTitle( "Rezept öffnen" );
        messageBox->setIconPixmap( QPixmap("../images/speachbubble.png") );
        messageBoxDo = openRec;
        messageBox->show();
    }
}

void MainWindow::fileDialogDirectoyChoosen(QString _directory){
    this->directory = _directory;
}

void MainWindow::fileDialogFileChoosen(QString _filename){
    filename = _filename;
    if(fileChooseDo == open){
        if( handler->open_file(filename.toStdString()) )
            fileOpend = true;
    }
    if(fileChooseDo == save){
        handler->save( directory.toStdString()+"/"+filename.toStdString() );
        someChanges = false;
    }
    fileChooseDo = non;
}

void MainWindow::saveActClicked(){
    if(fileOpend){
        this->handler->save( filename.toStdString() );
        someChanges = false;
    }
    else{
        fileChooseDo = save;
        fileDialog->show();
    }
}
void MainWindow::saveAsActClicked(){
    fileChooseDo = save;
    fileDialog->show();
}

void MainWindow::openActClicked(){
    fileChooseDo = open;
    fileDialog->show();
}

// MainWindow initializing functions

void MainWindow::settingUpConnections(){
    connect(editButton, SIGNAL(clicked()),
            this, SLOT(editButtonClicked()));
    connect(openAct, SIGNAL(triggered()),
            this, SLOT(openActClicked()));
    connect(saveAct, SIGNAL(triggered()),
            this, SLOT(saveActClicked()));
    connect(saveAsAct, SIGNAL(triggered()),
            this, SLOT(saveAsActClicked()));
    editWindow = new RecipeEdit;
    connect(editWindow, SIGNAL(recipeEdited()),
            this, SLOT(recipeChanged()));
    connect(changeRecipeAct, SIGNAL(triggered()),
            this, SLOT(editButtonClicked()));
    connect(addRecipeAct, SIGNAL(triggered()),
            this, SLOT(addRecipeActClicked()));
    connect(delRecipeAct, SIGNAL(triggered()),
            this, SLOT(delRecipeActClicked()));
    connect(searchAct, SIGNAL(triggered()),
            this, SLOT(searchRecipes()));
    connect(openRecipe, SIGNAL(clicked()),
            this, SLOT(searchRecipes()));
    connect(recipeShowAct, SIGNAL(triggered()),
            this, SLOT(searchRecipes()));
    connect(searchWindow, SIGNAL(itemSelected(Recipe*)),
            this, SLOT(updateMembers(Recipe*)));
    connect(portionsSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(portionsSpinBoxValueChanged(double)));
}

void MainWindow::initializingBasics(){
    this->fileDialog = new QFileDialog;
    connect(fileDialog, SIGNAL(directoryEntered(QString)),
            this, SLOT(fileDialogDirectoyChoosen(QString)));
    connect(fileDialog, SIGNAL(fileSelected(QString)),
            this, SLOT(fileDialogFileChoosen(QString)));
    messageBox = new QMessageBox;
    connect(messageBox, SIGNAL(accepted()),
            this, SLOT(messageBoxAccecpted()));
    searchWindow = new searchDialog(handler);
}

void MainWindow::initializingRecipeArea(){
    title = new QLabel();

    describtionTitle = new QLabel("<b>Beschreibung<\\b>");
    describtion = new QLabel;

    categorys = new QLabel;

    ingredientsTitle = new QLabel("<b>Zutaten<\\b>");
    ingredientsNamesLabel = new QLabel;
    ingredientsCrowdLabel = new QLabel;
    ingredients = new QHBoxLayout;
    ingredients->addWidget(ingredientsNamesLabel);
    ingredients->addWidget(ingredientsCrowdLabel);

    preparationTitle = new QLabel("<b>Zubereitung<\\b>");
    preparation = new QLabel;


    recipeLayout = new QVBoxLayout;
    recipeLayout->addWidget(title);
    recipeLayout->addWidget(categorys);
    recipeLayout->addWidget(describtionTitle);
    recipeLayout->addWidget(describtion);
    recipeLayout->addWidget(ingredientsTitle);
    recipeLayout->addLayout(ingredients);
    recipeLayout->addWidget(preparationTitle);
    recipeLayout->addWidget(preparation);

    recipeShowWidget = new QWidget;
    recipeShowWidget->setLayout(recipeLayout);
    recipeShowWidget->setSizePolicy( QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding) );

    recipeScrollArea = new QScrollArea;
    recipeScrollArea->setWidgetResizable(true);
    recipeScrollArea->setWidget(recipeShowWidget);
}

void MainWindow::initializingUi(){
    // Initializing qaction objects
    newAct = new QAction("Erstellt eine neue Datei");
    newAct->setIcon( QIcon(QPixmap("../images/new.png")) );

    openAct = new QAction("Öffnet eine Datei");
    openAct->setIcon( QIcon(QPixmap("../images/open.png")) );

    saveAct = new QAction("Speichert die Daten");
    saveAct->setIcon( QIcon(QPixmap("../images/save.png")) );

    saveAsAct = new QAction("Speichert die Daten unter");
    saveAsAct->setIcon( QIcon(QPixmap("../images/save.png")) );


    copyAct = new QAction("Kopieren");
    copyAct->setIcon( QIcon(QPixmap("../images/copy.png")) );

    cutAct = new QAction("Ausschneiden");
    cutAct->setIcon( QIcon(QPixmap("../images/cut.png")) );

    pasteAct = new QAction("Einfügen");
    pasteAct->setIcon( QIcon(QPixmap("../images/paste.png")) );


    delRecipeAct = new QAction("Löscht das Rezept");
    delRecipeAct->setIcon( QIcon(QPixmap("../images/delete-recipe.png")) );

    addRecipeAct = new QAction("Erzeugt ein neues Rezept");
    addRecipeAct->setIcon( QIcon(QPixmap("../images/new-recipe.png")) );

    changeRecipeAct = new QAction("Ändern");
    changeRecipeAct->setIcon( QIcon(QPixmap("../images/edit.png")) );

    searchAct = new QAction("Rezepte durchsuchen");
    searchAct->setIcon( QIcon(QPixmap("../images/search.png")) );

    recipeShowAct = new QAction("Rezept anzeigen");
    recipeShowAct->setIcon( QIcon(QPixmap("../images/show-recipe.png")) );

    reloadPortionsAct = new QAction("Portionen neu laden");
    reloadPortionsAct->setIcon( QIcon(QPixmap("../images/reload-portions.png")) );


    helpAct = new QAction("Wie bediene ich dieses Programm");
    helpAct->setIcon( QIcon(QPixmap("../images/help.png")) );

    aboutAct = new QAction("Über dieses Programm");
    aboutAct->setIcon( QIcon(QPixmap("../images/about.png")) );


    // Initializing menus
    fileMenu = new QMenu("Datei");
    fileMenu->addActions({newAct, openAct, saveAct, saveAsAct});

    editMenu = new QMenu("Bearbeiten");
    editMenu->addActions({copyAct, cutAct, pasteAct});

    recipeMenu = new QMenu("Rezept");
    recipeMenu->addActions({addRecipeAct, delRecipeAct, changeRecipeAct,
                            searchAct, recipeShowAct, reloadPortionsAct});

    helpMenu = new QMenu("Hilfe");
    helpMenu->addActions({helpAct, aboutAct});

    menuBar = new QMenuBar;
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(recipeMenu);
    menuBar->addMenu(helpMenu);
    menuBar->setSizePolicy( QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed) );

    // Initializing Toolbars
    fileToolBar = new QToolBar;
    fileToolBar->addActions({newAct, saveAct, openAct});
    fileToolBar->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );

    recipeToolBar = new QToolBar;
    recipeToolBar->addActions({addRecipeAct, delRecipeAct, changeRecipeAct,
                               recipeShowAct, searchAct});
    recipeToolBar->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );


    // Initializing spacers
    toolBarSpacerLeft = new QSpacerItem(15,15);
    toolBarSpacerRight = new QSpacerItem(15,15);


    // Initializing top recipe area
    portionsSpinBox = new QDoubleSpinBox;
    portionsSpinBox->setRange(0.01, 10000);
    portionsSpinBox->setValue(1);
    portionsSpinBox->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );

    topRecipereaSpacer = new QLabel("");

    editButton = new QPushButton("Bearbeiten");
    editButton->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );


    // Initializing layouts
    toolBarLayout = new QHBoxLayout;
    toolBarLayout->addWidget(fileToolBar);
    toolBarLayout->addSpacerItem(toolBarSpacerLeft);
    toolBarLayout->addWidget(recipeToolBar);
    toolBarLayout->addSpacerItem(toolBarSpacerRight);

    topRecipeAreaLayout = new QHBoxLayout;
    topRecipeAreaLayout->addWidget(portionsSpinBox);
    topRecipeAreaLayout->addWidget(topRecipereaSpacer);
    topRecipeAreaLayout->addWidget(editButton);

    openRecipe = new QPushButton("Rezept öffnen");
    openRecipe->setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );
    recipeScrollArea->hide();
    generelLayout = new QVBoxLayout;
    generelLayout->addWidget(menuBar);
    generelLayout->addLayout(toolBarLayout);
    generelLayout->addLayout(topRecipeAreaLayout);
    generelLayout->addWidget(recipeScrollArea);
    generelLayout->addWidget(openRecipe);


    setLayout(generelLayout);
    setWindowTitle("cookiechen");
    setWindowIcon( QIcon(QPixmap("../images/icon.png")) );
}
