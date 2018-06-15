#pragma once

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
class QtJsBridge : public QObject
{
	Q_OBJECT

public:
	QtJsBridge(QObject *parent);
	~QtJsBridge();
signals:
	void signalTest(QString data);
	void signalGetUserFriends();
	void signalGetSelfInfo();
	void signalSendMsg(QString receiverUin, QString content, int type);

	void signalSelfInfoRecieved(QVariant selfInfo);
	void signalFriendsListRecieved(QVariant friendList);
	void signalGroupsListRecieved(QVariant groupList);
	void signalMessageRecieved(QVariant msg);
	void signalDispatchMessageRecieved(QVariant msg);
public slots:
	void writeLog(QString log);
	void setFriends(QVariant friends);
	void setSelfInfo(QVariant selfInfo);
	void setGroups(QVariant groups);
	void setMessage(QVariant msg);
	void setDispatchMessage(QVariant msg);
private:
};
