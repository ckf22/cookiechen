#include "save_check_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QPixmap>
#include <QImage>

save_check_dialog::save_check_dialog(QWidget *parent)
    : QWidget{parent}
{

}


void save_check_dialog::closeEvent(QCloseEvent * event){

}


void save_check_dialog::initialize(){
    icon = new QImage("../images/speachbubble.png");
    label = new QLabel("Möchten Sie fortfahren?\n\nIhre Änderungen werden nicht gespeichert");
    topLayout = new QHBoxLayout;
    //topLayout->addWidget(icon);
    topLayout->addWidget(label);
    notSaveButton = new QPushButton(QIcon(QPixmap("../images/abort.png")),"Nicht Speichern");
    saveButton = new QPushButton(QIcon(QPixmap("../images/ok.png")), "Speichern");
    breakButton = new QPushButton("Abbrechen");
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(breakButton);
    buttonLayout->addWidget(notSaveButton);
    buttonLayout->addWidget(saveButton);

    layout = new QVBoxLayout;
    layout->addLayout(topLayout);
    layout->addLayout(buttonLayout);

    connect(breakButton, SIGNAL(pressed()),
            this, SLOT(close()) );
}

