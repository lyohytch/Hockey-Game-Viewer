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

void GameViewer::on_calendarWidget_activated(QDate date)
{
    qDebug()<<"New date"<<":"<<date;
    emit GamingDaySelected(date);
}
void GameViewer::init()
{
     QVBoxLayout *layout = new QVBoxLayout(this);
     this->setCalendar(new QCalendarWidget(this));
     calendar()->setFirstDayOfWeek(Qt::DayOfWeek(1));;
     this->setTable(new QTableView(this));
     connect(this->calendar(), SIGNAL(activated(QDate)), SLOT(on_calendarWidget_activated(QDate)));

     layout->addWidget(this->calendar());
     layout->addWidget(this->table());
     this->centralWidget()->setLayout(layout);
}
