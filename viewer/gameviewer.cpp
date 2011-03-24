#include "gameviewer.h"
#include "ui_gameviewer.h"
#include "constants.h"

GameViewer::GameViewer(QWidget *parent) :
    IView(parent),
    ui(new Ui::GameViewer)
{
    ui->setupUi(this);
    new presentation(this);
}

GameViewer::~GameViewer()
{
    delete ui;
}