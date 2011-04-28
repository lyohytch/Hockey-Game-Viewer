#include "gameviewer.h"
#include "ui_gameviewer.h"
#include "constants.h"


void BasicViewer::gamingDaySelected(const QDate &gameDate)
{
    emit GamingDaySelected(gameDate);
}

GameViewer::GameViewer(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::GameViewer)
{
    ui->setupUi(this);
    init();
    new presentation(view, viewerSettings);
}

GameViewer::~GameViewer()
{
    delete ui;
}

void GameViewer::DateChanged(const QDate &date)
{
    qDebug()<<"New date"<<":"<<date;
    emit  view->gamingDaySelected(date);
}
void GameViewer::init()
{
     QVBoxLayout *vlayout = new QVBoxLayout();

     view = new BasicViewer(this);
     view->setCalendar(new QDateEdit(this));
     view->calendar()->setCalendarPopup(true);
     view->calendar()->setDate(QDate::currentDate());
     qDebug();
     view->setTable(new QTableView(this));
     connect(view->calendar(), SIGNAL(dateChanged(const QDate&)), this, SLOT(DateChanged(const QDate&)), Qt::DirectConnection);
     qDebug();
     vlayout->addWidget(view->calendar());
     vlayout->addWidget(view->table());
     centralWidget()->setLayout(vlayout);

     stateLabel = new QLabel();
     statusBar()->addWidget(stateLabel);



     connect(view, SIGNAL(SetStatusOnForm(const QString&)), this, SLOT(setStatusOnForm(const QString&)), Qt::UniqueConnection);

     view->setStatus(tr("Select day"));

     viewerSettingsForm = new GameViewerSettings();
     viewerSettings = viewerSettingsForm->getBasicViewerSettings();
     viewerSettings->prepareSettings();
     connect(ui->action_Preferences, SIGNAL(triggered()),viewerSettingsForm, SLOT(show()), Qt::UniqueConnection);
}

void GameViewer::setStatusOnForm(const QString &status)
{
    qDebug()<<"Status changed to "<<status;
    stateLabel->setText(status);
}
