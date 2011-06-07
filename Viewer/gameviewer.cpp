#include "gameviewer.h"
#include "ui_gameviewer.h"
#include "constants.h"


void BasicViewer::gamingDaySelected(const QDate &gameDate)
{
    emit GamingDaySelected(gameDate);
}

void BasicViewer::setModel(QAbstractItemModel *model)
{
    Q_ASSERT(model != 0);
    _table->setModel(model);
}

void BasicViewer::resizeTable()
{
    _table->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);;
    _table->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    _table->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    _table->horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);
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
     QHBoxLayout *hlayout = new QHBoxLayout();

     view = new BasicViewer(this);
     view->calendar()->setCalendarPopup(true);
     view->calendar()->setDate(QDate::currentDate());
     qDebug();
     connect(view->calendar(), SIGNAL(dateChanged(const QDate&)), this, SLOT(DateChanged(const QDate&)), Qt::DirectConnection);
     connect(view->update(), SIGNAL(clicked()), this, SLOT(Update()), Qt::DirectConnection);
     qDebug();
     hlayout->addWidget(view->calendar(),1);//Stretch calendar widget
     hlayout->addWidget(view->update());
     vlayout->addItem(hlayout);
     vlayout->addWidget(view->table());
     centralWidget()->setLayout(vlayout);

     statusBar()->addWidget(view->stateLabel());



     connect(view, SIGNAL(SetStatusOnForm(const QString&)), this, SLOT(setStatusOnForm(const QString&)), Qt::UniqueConnection);

     view->setStatus(tr("Select day"));

     viewerSettingsForm = new GameViewerSettings();
     viewerSettings = viewerSettingsForm->getBasicViewerSettings();
     viewerSettings->prepareSettings();
     connect(ui->action_Preferences, SIGNAL(triggered()),viewerSettingsForm, SLOT(show()), Qt::UniqueConnection);
}

void GameViewer::Update()
{
    qDebug()<<"Update button is pressed";
    emit view->gamingDaySelected(view->calendar()->date());
}

void GameViewer::setStatusOnForm(const QString &status)
{
    qDebug()<<"Status changed to "<<status;
    view->stateLabel()->setText(status);
}
