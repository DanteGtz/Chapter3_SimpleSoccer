#pragma once
#ifndef SOCCER_MESSAGES_H
#define SOCCER_MESSAGES_H

#include <string>
//An easy translator for the message send-receive by the entities
enum MessageType
{
	Msg_ReceiveBall,
	Msg_PassToMe,
	Msg_SupportAttacker,
	Msg_GoHome,
	Msg_Wait
};

//converts an enumerated value to a string
inline std::string MessageToString(int msg);


#endif