#include "qtjsbridge.h"

QtJsBridge::QtJsBridge(QObject *parent)
	: QObject(parent)
{
}

QtJsBridge::~QtJsBridge()
{
}

void QtJsBridge::writeLog(QString log)
{
	qDebug() << "JavaScript Log:" << log;
}

void QtJsBridge::setFriends(QVariant friends)
{
	qDebug() << "Get Friends:" << friends;
	emit signalFriendsListRecieved(friends);
}

void QtJsBridge::setSelfInfo(QVariant selfInfo)
{
	qDebug() << "Get Self Info:" << selfInfo;
	emit signalSelfInfoRecieved(selfInfo);
}

void QtJsBridge::setGroups(QVariant groups)
{
	qDebug() << "Get Group List:"<<groups;
	emit signalGroupsListRecieved(groups);
}

void QtJsBridge::setMessage(QVariant msg)
{
	qDebug() << "Get Message:" << msg;
	emit signalMessageRecieved(msg);
}

void QtJsBridge::setDispatchMessage(QVariant msg)
{
	qDebug() << "Get Dispatch Message:"<<msg;
	emit signalDispatchMessageRecieved(msg);
}
