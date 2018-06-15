#pragma once

#include <QtWidgets/QMainWindow>
#include <QWebEngineView>
#include <QWebEnginePage> 
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>
#include <QFile>
#include <QWebChannel>
#include "ui_qqrobot.h"
#include "qtjsbridge.h"
class QQRobot : public QMainWindow
{
	Q_OBJECT

public:
	QQRobot(QWidget *parent = Q_NULLPTR);
private slots:
	void on_btnRun_clicked();
	void pageLoadFinished(bool ok);
private:
	void injectionChannelJs();
private:
	Ui::QQRobotClass ui;
	QWebChannel *m_webChannel;
	QtJsBridge *m_jsBridge;
};
