#include "downloadremotewidget.h"
#include "downloadsettingmanager.h"
#include "downloadrightareawidget.h"
#include "downloadtopareawidget.h"
#include "downloaduiobject.h"

#include <QMenu>
#include <QPainter>

DownloadRemoteWidget::DownloadRemoteWidget(QWidget *parent)
    : DownloadAbstractMoveWidget(parent)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_DeleteOnClose);

    setGeometry(200, 200, 64, 64);
    adjustPostion(this);

    drawWindowShadow(false);
    setMouseTracking(true);

    m_value = 0;
}

DownloadRemoteWidget::~DownloadRemoteWidget()
{
    M_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionChoiced, false);
}

QString DownloadRemoteWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadRemoteWidget::setValue(int value)
{
    if(value > 100) value = 100;
    else if(value < 0) value = 0;
    m_value = height()*1.0f/100*value;
    update();
}

void DownloadRemoteWidget::show()
{
    DownloadAbstractMoveWidget::show();
    M_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionChoiced, true);
}

void DownloadRemoteWidget::adjustPostion(QWidget *w)
{
    QSize windowSize = M_SETTING_PTR->value(DownloadSettingManager::ScreenSize).toSize();
    w->move(windowSize.width() - w->width() - 150, w->height() + 70);
}

void DownloadRemoteWidget::contextMenuEvent(QContextMenuEvent *event)
{
    DownloadAbstractMoveWidget::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(DownloadUIObject::MMenuStyle02);

    DownloadRightAreaWidget *rw = DownloadRightAreaWidget::instance();
    menu.addAction(QIcon(":/contextMenu/lb_new_normal"), tr("NewDownload(N)"), rw, SLOT(showNewFileDialog()));
    menu.addAction(QIcon(":/contextMenu/lb_start_normal"), tr("Start"), rw, SLOT(startToDownload()));
    menu.addAction(QIcon(":/contextMenu/lb_stop_normal"), tr("Stop"), rw, SLOT(stopToDownload()));

    bool ishow = M_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionChoiced).toBool();
    DownloadTopAreaWidget *tw = DownloadTopAreaWidget::instance();
    QMenu floatMenu(tr("FloatSetting"), &menu);
    floatMenu.addAction(QIcon( ishow ? ":/contextMenu/lb_selected" : QString()), tr("Show"), tw, SLOT(showRemoteSpeedWidget()));
    floatMenu.addAction(QIcon(!ishow ? ":/contextMenu/lb_selected" : QString()), tr("Hide"), tw, SLOT(closeRemoteSpeedWidget()));
    menu.addMenu(&floatMenu);

    menu.addAction(tr("quit"), tw, SLOT(closeRemoteSpeedWidget()));

    menu.exec(QCursor::pos());
}

void DownloadRemoteWidget::paintEvent(QPaintEvent *event)
{
    DownloadAbstractMoveWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    painter.drawPixmap(0, 0, QPixmap(":/remote/lb_back"));

    QPainterPath rectp;
    rectp.addRect(QRect(0, height() - m_value, width(), m_value));
    QPainterPath rectr;
    rectr.addEllipse(rect());
    painter.fillPath(rectr.intersected(rectp), QColor(0xff, 0xff, 0, 0x32));

    if(M_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionPerChoiced).toBool())
    {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, QString("%1%").arg(m_value*100/height()));
    }
}
