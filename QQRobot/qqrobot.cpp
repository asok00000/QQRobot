#include "qqrobot.h"

QQRobot::QQRobot(QWidget *parent)
	: QMainWindow(parent), m_webChannel(nullptr), m_jsBridge(nullptr)
{
	ui.setupUi(this);
	QWebEngineSettings*webEngineSettings = QWebEngineSettings::defaultSettings();
	webEngineSettings->setDefaultTextEncoding("UTF-8");
	webEngineSettings->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
	webEngineSettings->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
	webEngineSettings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
	webEngineSettings->setAttribute(QWebEngineSettings::XSSAuditingEnabled, true);
	webEngineSettings->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
	webEngineSettings->setAttribute(QWebEngineSettings::ScreenCaptureEnabled, true);
	webEngineSettings->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
	webEngineSettings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
	injectionChannelJs();
	m_jsBridge = new QtJsBridge(this);
	m_webChannel = new QWebChannel(this);
	m_webChannel->registerObject("bridge", m_jsBridge);
	ui.webEngine->page()->setWebChannel(m_webChannel);
	ui.webEngine->load(QUrl("https://web2.qq.com"));
	connect(ui.webEngine->page(), &QWebEnginePage::loadFinished, this, &QQRobot::pageLoadFinished, Qt::UniqueConnection);
	connect(m_jsBridge, &QtJsBridge::signalMessageRecieved, this, [&](QVariant msg) {
		qDebug() << msg;
		QVariantMap _msg = msg.toMap();
		QString _uin = QString::number(_msg["from_uin"].toDouble(), 'f', 0);
		if (_msg.contains("from_group"))
		{
			//Group msg
			emit m_jsBridge->signalSendMsg(_uin, "Hello buddy.", 1);
		}
		else
		{
			//friend msg
			emit m_jsBridge->signalSendMsg(_uin, "Hello buddy.", 0);
		}
	});
}

void QQRobot::on_btnRun_clicked()
{
	QString _js = ui.txtJavaScript->toPlainText();
	/*ui.webEngine->page()->runJavaScript(_js, [&](QVariant result) {
		qDebug() << result;
	});*/
	emit m_jsBridge->signalGetUserFriends();
}

void QQRobot::pageLoadFinished(bool ok)
{
	QFile _logicJs(R"(./Resources/logic.js)");
	if (!_logicJs.open(QIODevice::ReadOnly))
	{
		qDebug() << _logicJs.errorString();
	}
	QByteArray _logic = "";
	_logic = _logicJs.readAll();
	_logicJs.close();
	ui.webEngine->page()->runJavaScript(_logic, [&](QVariant result) {
		qDebug() << "Injection logic js into page.";
	});
}

void QQRobot::injectionChannelJs()
{
	QByteArray  _qwebChannel = "";
	QFile _webChangeJs(R"(./Resources/qwebchannel.js)");
	if (!_webChangeJs.open(QIODevice::ReadOnly))
	{
		qDebug() << _webChangeJs.errorString();
	}
	_qwebChannel = _webChangeJs.readAll();
	_webChangeJs.close();
	QWebEngineProfile* _profile = QWebEngineProfile::defaultProfile();
	QWebEngineScript script;
	script.setSourceCode(_qwebChannel);
	script.setName("qwebchannel.js");
	script.setWorldId(QWebEngineScript::MainWorld);
	script.setInjectionPoint(QWebEngineScript::DocumentCreation);
	script.setRunsOnSubFrames(false);
	_profile->scripts()->insert(script);
}
