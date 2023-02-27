#pragma once

#include <QMainWindow>
#include <QFile>
#include <QSoundEffect>
#include <QFileInfoList>
#include <QSettings>
#include <QHostAddress>

#include "netServer.h"
#include "paneldirection.h"
#include "generalsetuparguments.h"
#include <connection.h>


QT_FORWARD_DECLARE_CLASS(QUdpSocket)
QT_FORWARD_DECLARE_CLASS(QWebSocket)
QT_FORWARD_DECLARE_CLASS(QHBoxLayout)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(ClientListDialog)


class ScoreController : public QMainWindow
{
    Q_OBJECT

public:
    ScoreController(QWidget *parent = nullptr);
    ~ScoreController();

signals:

protected slots:
//    void onProcessConnectionRequest();
    void onNewConnection(QWebSocket *pClient);
    void onProcessTextMessage(QString sMessage);
    void onProcessBinaryMessage(QByteArray message);
    void onClientDisconnected();

    void onButtonStartStopSpotLoopClicked();
    void onButtonStartStopSlideShowClicked();
    void onButtonStartStopLiveCameraClicked();
    void onButtonSetupClicked();
    void onButtonPanelControlClicked();
    void onButtonShutdownClicked();

    void onStartCamera(const QString& sClientIp);
    void onStopCamera();
    void onSetNewPanValue(const QString& sClientIp, int newPan);
    void onSetNewTiltValue(const QString& sClientIp, int newTilt);

    void onGetPanelDirection(const QString& sClientIp);
    void onChangePanelDirection(const QString& sClientIp, PanelDirection direction);

    void onGetIsPanelScoreOnly(const QString& sClientIp);
    void onSetScoreOnly(const QString& sClientIp, bool bScoreOnly);

protected:
    bool            prepareLogFile();
    int             WaitForNetworkReady();
    bool            isConnectedToNetwork();
    void            prepareDirectories();
    virtual void    SaveStatus();
    virtual void    GetGeneralSetup();
    void            prepareServices();
    void            sendAcceptConnection(QUdpSocket *pDiscoverySocket, const QHostAddress& hostAddress, quint16 port);
    void            RemoveClient(const QHostAddress& hAddress);
    void            UpdateUI();
    bool            prepareServer();
    virtual QString FormatStatusMsg();
    int             SendToOne(QWebSocket* pSocket, const QString& sMessage);
    int             SendToAll(const QString& sMessage);
    QHBoxLayout*    CreateSpotButtons();
    void            connectButtonSignals();
    int             sendSlideDir();
    int             sendSpotDir();

protected:
    GeneralSetupArguments generalSetupArguments;
    ClientListDialog*     pClientListDialog;
    QString               sLogDir;
    QString               logFileName;
    QFile*                pLogFile;
    QSoundEffect*         pButtonClick;
    QStringList           sIpAddresses;
    QString               sSlideDir;
    QFileInfoList         slideList;
    int                   iCurrentSlide;
    QString               sSpotDir;
    QFileInfoList         spotList;
    int                   iCurrentSpot;
    QSettings*            pSettings;
    QList<Connection>     connectionList;
    NetServer*            pPanelServer{};
    quint16               serverPort;
    QPushButton*          startStopLoopSpotButton{};
    QPushButton*          startStopSlideShowButton{};
    QPushButton*          startStopLiveCameraButton{};
    QPushButton*          panelControlButton{};
    QPushButton*          generalSetupButton{};
    QPushButton*          shutdownButton{};
    QHBoxLayout*          pSpotButtonsLayout;
    enum status {
        showPanel,
        showSpots,
        showSlides,
        showCamera
    };
    status                myStatus;
};
