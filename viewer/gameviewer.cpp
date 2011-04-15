#include "gameviewer.h"
#include "ui_gameviewer.h"
#include "constants.h"

GameViewer::GameViewer(QWidget *parent) :
    IView(parent),
    ui(new Ui::GameViewer)
{
    ui->setupUi(this);
    init();
    new presentation(this);
}

GameViewer::~GameViewer()
{
    delete ui;
}

void GameViewer::DateChanged(const QDate &date)
{
    qDebug()<<"New date"<<":"<<date;
    emit GamingDaySelected(date);
}
void GameViewer::init()
{
     QVBoxLayout *vlayout = new QVBoxLayout();
     setCalendar(new QDateEdit(this));
     calendar()->setCalendarPopup(true);
     calendar()->setDate(QDate::currentDate());
     qDebug();
     setTable(new QTableView(this));
     connect(calendar(), SIGNAL(dateChanged(const QDate&)), this, SLOT(DateChanged(const QDate&)), Qt::DirectConnection);
     qDebug();
     vlayout->addWidget(calendar());
     vlayout->addWidget(table());
     centralWidget()->setLayout(vlayout);

     stateLabel = new QLabel();
     statusBar()->addWidget(stateLabel);

     connect(this, SIGNAL(SetStatusOnForm(const QString&)), this, SLOT(setStatusOnForm(const QString&)), Qt::UniqueConnection);

     setStatus(tr("Select day"));     
}

void GameViewer::setStatusOnForm(const QString &status)
{
    qDebug()<<"Status changed to "<<status;
    stateLabel->setText(status);
}
