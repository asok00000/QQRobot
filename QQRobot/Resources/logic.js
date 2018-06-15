window.Logic = new Object();
Logic.getUserFriends = function(){
	mq.model.buddylist.getUserFriends();
	setTimeout(function(){
		bridge.setFriends(mq.model.buddylist.getFriends());
	},1000);
};
Logic.getSelfInfo = function(){
    bridge.setSelfInfo(mq.model.buddylist.getSelfInfo());
}
Logic.sendMsg = function (recieverUin,content,type){
    //TODO:
    if(type == 0)
    {
        //single chat
        var _param = {to: 1508935800, content: "[\"$content$\",[\"font\",{\"name\":\"宋体\",\"size\":10,\"style\":[0,0,0],\"color\":\"000000\"}]]", face: 585}
        _param.to = parseInt(recieverUin);
        _param.content = _param.content.replace("$content$",content);
        mq.model.chat.sendMsg(_param);
    }
    else if(type == 1)
    {
        //group chat
        var _param = {group_uin: 1508935800, content: "[\"$content$\",[\"font\",{\"name\":\"宋体\",\"size\":10,\"style\":[0,0,0],\"color\":\"000000\"}]]", face: 585}
        _param.group_uin = parseInt(recieverUin);
        _param.content = _param.content.replace("$content$",content);
        mq.model.chat.sendGroupMsg(_param);
    }
}
Logic.onLoginSuccess = function(data){
    //TODO:
    console.log("onLoginSuccess:",data);
    Logic.getSelfInfo();
}
Logic.onGroupListChanged = function(groupList){
    //TODO:
    console.log("onGroupListChanged:",groupList);
    bridge.setGroups(groupList);
}
Logic.onRecentListChanged = function(recentList){
    //TODO:
    console.log("onRecentListChanged:",recentList);
}
Logic.onDiscussListChanged = function(discussList){
    //TODO:
    console.log("onDiscussListChanged:",discussList);
}
Logic.onFriendListChanged = function(categoriesList,friendsList){
    //TODO:
    console.log("onFriendListChanged:",categoriesList,friendsList);
    bridge.setFriends(friendsList);
}
Logic.onGroupInfoChanged = function(data){
    //TODO:
}
Logic.onFriendInfoChanged = function(data){
    //TODO:
}
Logic.onGetFirstSelfInfo = function(data){
    //TODO:
}
Logic.onMessageReceived = function(message){
    //TODO:
    console.log("onMessageReceived:",message);
    bridge.setMessage(message);
}
Logic.onMessageDispatch = function(message){
    //TODO:
    console.log("onMessageDispatch:",message);
}
function initMessageHandler(){
    JM.event.on(mq.rpcService, "LoginSuccess", Logic.onLoginSuccess);
    JM.event.on(mq.model.buddylist, "groupListChange", Logic.onGroupListChanged);
    JM.event.on(mq.model.buddylist, "discussListChange", Logic.onDiscussListChanged);
    JM.event.on(mq.model.buddylist, "recentListChange", Logic.onRecentListChanged);
    JM.event.on(mq.model.buddylist, "groupInfoUpdate", Logic.onGroupInfoChanged);
    JM.event.on(mq.model.buddylist, "discussInfoUpdate", Logic.onDiscussInfoChanged);
    JM.event.on(mq.model.buddylist, "friendInfoUpdate", Logic.onFriendInfoChanged);
    JM.event.on(mq.model.buddylist, "getFirstSelfInfo", Logic.onGetFirstSelfInfo);
    JM.event.on(mq.model.buddylist, "friendsListChange", Logic.onFriendListChanged);
    JM.event.on(mq.model.chat, "messageReceived", Logic.onMessageReceived);
    JM.event.on(mq.model.chat, "groupMessageReceived", Logic.onMessageReceived);
    JM.event.on(mq.model.chat, "discussMessageReceived", Logic.onMessageReceived);
    JM.event.on(mq.model.chat, "messageDispatch", Logic.onMessageDispatch);
}
new QWebChannel(qt.webChannelTransport, function (channel) {
    window.bridge = channel.objects.bridge;
    //Js log write to qt console
    window.writeLog = function (log) {
        try {
            if (typeof log == "number" || typeof log == "boolean")
                log += "";
            else if (typeof log == "object") {
                if (log == null) {
                    log = "null";
                }
                else {
                    log = JSON.stringify(log);
                }
            }
            else if (typeof log == "undefined") {
                log = "undefine";
            }
        }
        catch (error) {
            log = "写日志失败:" + error;
        }
        bridge.writeLog(log);
    }
    // Connect to a signal:
	bridge.signalGetUserFriends.connect(Logic.getUserFriends);
    bridge.signalGetSelfInfo.connect(Logic.getSelfInfo);
    bridge.signalSendMsg.connect(Logic.sendMsg);
});
//Hook event
initMessageHandler();

