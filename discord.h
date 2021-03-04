#pragma once
#include <discord_rpc.h>

//void updatePresence(std::string state = "state", std::string details = "details");
//void handleReady(const DiscordUser* connectedUser);
//void handleDisconnect(int errcode, const char* msg);
//void handleError(int errcode, const char* msg);
//void handleJoin(const char* secret);
//void handleJoinReq(const DiscordUser* request);
//void handleSpectate(const char* secret);
//void initDiscord();



#define _CRT_SECURE_NO_WARNINGS // Never worry about CRT date

#pragma comment(lib, "discord-rpc.lib")

#include <iostream>
#include <string>
#include <time.h>
#include "discord.h"
#include <vector>

static const char* ID = "812733500889104444";

static int64_t start;
static int64_t end;

using std::string;
using std::vector;

void updatePresence(vector<string> strings)
{
	//start = time(0);
	start = strtoll(strings[2].c_str(), NULL, 10);
	end = strtoll(strings[3].c_str(), NULL, 10);

	DiscordRichPresence pres;
	memset(&pres, 0, sizeof(pres));

	pres.state = strings[0].c_str();
	pres.details = strings[1].c_str();
	if (start >= end)
	{	// Use start; it is newer
		pres.startTimestamp = start;
	}
	else
	{	// Use end; it is in the future
		pres.endTimestamp = end;
	}
	//large image key
	//pres.largeImageKey = "c";
	pres.largeImageText = "Large Test";
	//small image key
	//pres.smallImageKey = "r";
	pres.smallImageText = "Small Test";
	//party id
	pres.partySize = stoi(strings[4]);
	//party size
	pres.partyMax = stoi(strings[5]);
	//party max
	//party privacy
	//match secret
	//join secret
	//spectate secret
	//instance
	Discord_UpdatePresence(&pres);
}

static void handleReady(const DiscordUser* connectedUser)
{
	std::cout << "Discord Connection Established to user " <<
		connectedUser->username << " " <<
		connectedUser->discriminator << " " <<
		connectedUser->userId << std::endl;
}

static void handleDisconnect(int errcode, const char* msg)
{
	std::cout << "Discord Disconnect [" <<
		errcode << " " <<
		msg << "]" << std::endl;
}

static void handleError(int errcode, const char* msg)
{
	std::cout << "Discord Error [" <<
		errcode << " " <<
		msg << "]" << std::endl;
}

static void handleJoin(const char* secret)
{
	std::cout << "Discord Join [" << secret << "]" << std::endl;
}

static void handleJoinReq(const DiscordUser* request)
{
	int res = -1;
	std::string opt = "";
	std::cout << "Discord: join request from " <<
		request->username << " " <<
		request->discriminator << " " <<
		request->userId << std::endl;

	bool valid = false;

	do
	{
		std::cout << "Accept Join Request? (y/n)" << std::endl;
		std::cin >> opt;
		switch (opt[0])
		{
		case 'y':
		case 'Y':
			res = DISCORD_REPLY_YES;
			valid = true;
			break;
		case 'n':
		case 'N':
			res = DISCORD_REPLY_NO;
			valid = true;
			break;
		default:
			valid = false;
			break;
		}

	} while (!valid);

	if (res != -1)
	{
		Discord_Respond(request->userId, res);
	}

}

static void handleSpectate(const char* secret)
{
	std::cout << "Discord Spectate [" << secret << "]" << std::endl;
}


void initDiscord()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = handleReady;
	handlers.disconnected = handleDisconnect;
	handlers.errored = handleError;
	handlers.joinGame = handleJoin;
	handlers.joinRequest = handleJoinReq;
	handlers.spectateGame = handleSpectate;

	Discord_Initialize(ID, &handlers, 1, NULL);
}
