#pragma once
// myrpls
#define ERR_NOTPASSWORDED(source) ": 002 " + source + " :Your connection is not passworded\r\n"
//
#define ERR_NOSUCHNICK(source, nick) ": 401 " + source + " " + nick + " :No such nick/channel" + "\r\n"
#define ERR_NOSUCHSERVER(source, server) ": 402 " + source + " " + server + " :No such server" + "\r\n"
#define ERR_NOSUCHCHANNEL(source, channel) ": 403 " + source + " " + channel + " :No such channel" + "\r\n"
#define ERR_CANNOTSENDTOCHAN(source, channel) ": 404 " + source + " " + channel + " :Cannot send to channel" + "\r\n"
#define ERR_TOOMANYCHANNELS(source, channel) ": 405 " + source + " " + channel + " :You have joined too many channels" + "\r\n"
#define ERR_WASNOSUCHNICK(source, nick) ": 406 " + source + " " + nick + " :There was no such nickname" + "\r\n"
#define ERR_TOOMANYTARGETS(source, target) ": 407 " + source + " " + target + " :Duplicate recipients. No message" + "\r\n"

#define ERR_NOORIGIN ": 409 :No origin specified" + "\r\n"
#define ERR_NORECIPIENT(source, command) ": 411 " + source + " " + command + " :No recipient given" + "\r\n"
#define ERR_NOTEXTTOSEND(source) ": 412 " + source + " :No text to send" + "\r\n"
#define ERR_NOTOPLEVEL(mask) ": 413 " + mask + " :No toplevel domain specified" + "\r\n"
#define ERR_WILDTOPLEVEL(mask) ": 414 " + mask + " :Wildcard in toplevel domain" + "\r\n"
#define ERR_UNKNOWNCOMMAND(source, command) ": 421 " + source + " " + command + " :Unknown command" + "\r\n"
#define ERR_NOMOTD ": 422 :MOTD File is missing" + "\r\n"
#define ERR_NOADMININFO(server) ": 423 " + server + " :No administrative info available" + "\r\n"
#define ERR_FILEERROR(file, fileop) ": 424 :File error doing " + fileop + " on " + file + "\r\n"
#define ERR_NONICKNAMEGIVEN(source) ": 431 " + source + " :No nickname given" + "\r\n"
#define ERR_ERRONEUSNICKNAME(source, nick) ": 432 " + source + " " + nick + " :Erroneus nickname" + "\r\n"
#define ERR_NICKNAMEINUSE(source, nick) ": 433 " + source + " " + nick + " :Nickname is already in use" + "\r\n"
//#define ERR_NICKCOLLISION(nick) ": 436 " + nick + " :Nickname collision KILL" + "\r\n"
#define ERR_USERNOTINCHANNEL(nick, channel) ": 441 " + nick + " " + channel + " :They aren't on that channel" + "\r\n"
#define ERR_NOTONCHANNEL(source, channel) ": 442 " + source + " " + channel + " :You're not on that channel" + "\r\n"
#define ERR_USERONCHANNEL(user, channel) ": 443 " + user + " " + channel + " :is already on channel" + "\r\n"
#define ERR_NOLOGIN(user) ": 444 " + user + " :User not logged in" + "\r\n"
#define ERR_SUMMONDISABLED ": 445 :SUMMON has been disabled" + "\r\n"
#define ERR_USERSDISABLED ": 446 :USERS has been disabled" + "\r\n"
#define ERR_NOTREGISTERED(source) ": 451 " + source + " :You have not registered" + "\r\n"
#define ERR_NEEDMOREPARAMS(source, command) ": 461 " + source + " " + command + " :Not enough parameters" + "\r\n"
#define ERR_ALREADYREGISTRED(source) ": 462 " + source + " :You may not reregister" + "\r\n"
#define ERR_NOPERMFORHOST ": 463 :Your host isn't among the privileged" + "\r\n"
#define ERR_PASSWDMISMATCH(source) ": 464 " + source + " :Password incorrect" + "\r\n"
#define ERR_YOUREBANNEDCREEP ": 465 :You are banned from this server" + "\r\n"
#define ERR_KEYSET(channel) ": 467 " + channel + " :Channel key already set" + "\r\n"
#define ERR_CHANNELISFULL(source, channel) ": 471 " + source + " " + channel + " :Cannot join channel (+l)" + "\r\n"
#define ERR_UNKNOWNMODE(source, char) ": 472 " + source + " " + char + " :is unknown mode char to me" + "\r\n"
#define ERR_INVITEONLYCHAN(source, channel) ": 473 " + source + " " + channel + " :Cannot join channel (+i)" + "\r\n"
#define ERR_BANNEDFROMCHAN(channel) ": 474 " + channel + " :Cannot join channel (+b)" + "\r\n"
#define ERR_BADCHANNELKEY(source, channel) ": 475 " + source + " " + channel + " :Cannot join channel (+k)" + "\r\n"
#define ERR_BADLIMIT(source, channel) ": 476 " + source + " " + channel + " :Bad channel limit" + "\r\n"
#define ERR_NOPRIVILEGES ": 481 :Permission Denied- You're not an IRC operator" + "\r\n"
#define ERR_CHANOPRIVSNEEDED(source, channel) ": 482 " + source + " " + channel + " :You're not channel operator" + "\r\n"
#define ERR_CANTKILLSERVER ": 483 :You cant kill a server!" + "\r\n"
#define ERR_NOOPERHOST ": 491 :No O-lines for your host" + "\r\n"
#define ERR_UMODEUNKNOWNFLAG ": 501 :Unknown MODE flag" + "\r\n"
#define ERR_USERSDONTMATCH ": 502 :Cant change mode for other users" + "\r\n"

/*
6.1 Error Replies.

        401     ERR_NOSUCHNICK
                        "<nickname> :No such nick/channel"

                - Used to indicate the nickname parameter supplied to a
                  command is currently unused.

        402     ERR_NOSUCHSERVER
                        "<server name> :No such server"

                - Used to indicate the server name given currently
                  doesn't exist.

        403     ERR_NOSUCHCHANNEL
                        "<channel name> :No such channel"

                - Used to indicate the given channel name is invalid.

        404     ERR_CANNOTSENDTOCHAN
                        "<channel name> :Cannot send to channel"

                - Sent to a user who is either (a) not on a channel
                  which is mode +n or (b) not a chanop (or mode +v) on
                  a channel which has mode +m set and is trying to send
                  a PRIVMSG message to that channel.

        405     ERR_TOOMANYCHANNELS
                        "<channel name> :You have joined too many \
                         channels"
                - Sent to a user when they have joined the maximum
                  number of allowed channels and they try to join
                  another channel.

        406     ERR_WASNOSUCHNICK
                        "<nickname> :There was no such nickname"

                - Returned by WHOWAS to indicate there is no history
                  information for that nickname.

        407     ERR_TOOMANYTARGETS
                        "<target> :Duplicate recipients. No message \
                - Returned to a client which is attempting to send a
                  PRIVMSG/NOTICE using the user@host destination format
                  and for a user@host which has several occurrences.

        409     ERR_NOORIGIN
                        ":No origin specified"

                - PING or PONG message missing the originator parameter
                  which is required since these commands must work
                  without valid prefixes.

        411     ERR_NORECIPIENT
                        ":No recipient given (<command>)"
        412     ERR_NOTEXTTOSEND
                        ":No text to send"
        413     ERR_NOTOPLEVEL
                        "<mask> :No toplevel domain specified"
        414     ERR_WILDTOPLEVEL
                        "<mask> :Wildcard in toplevel domain"

                - 412 - 414 are returned by PRIVMSG to indicate that
                  the message wasn't delivered for some reason.
                  ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
                  are returned when an invalid use of
                  "PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.

        421     ERR_UNKNOWNCOMMAND
                        "<command> :Unknown command"

                - Returned to a registered client to indicate that the
                  command sent is unknown by the server.

        422     ERR_NOMOTD
                        ":MOTD File is missing"

                - Server's MOTD file could not be opened by the server.

        423     ERR_NOADMININFO
                        "<server> :No administrative info available"

                - Returned by a server in response to an ADMIN message
                  when there is an error in finding the appropriate
                  information.

        424     ERR_FILEERROR
                ":File error doing <file op> on <file>"
                - Generic error message used to report a failed file
                  operation during the processing of a message.

        431     ERR_NONICKNAMEGIVEN
                        ":No nickname given"

                - Returned when a nickname parameter expected for a
                  command and isn't found.

        432     ERR_ERRONEUSNICKNAME
                        "<nick> :Erroneus nickname"

                - Returned after receiving a NICK message which contains
                  characters which do not fall in the defined set.  See
                  section x.x.x for details on valid nicknames.

        433     ERR_NICKNAMEINUSE
                        "<nick> :Nickname is already in use"

                - Returned when a NICK message is processed that results
                  in an attempt to change to a currently existing
                  nickname.

        436     ERR_NICKCOLLISION
                        "<nick> :Nickname collision KILL"

                - Returned by a server to a client when it detects a
                  nickname collision (registered of a NICK that
                  already exists by another server).

        441     ERR_USERNOTINCHANNEL
                        "<nick> <channel> :They aren't on that channel"

                - Returned by the server to indicate that the target
                  user of the command is not on the given channel.

        442     ERR_NOTONCHANNEL
                        "<channel> :You're not on that channel"

                - Returned by the server whenever a client tries to
                  perform a channel effecting command for which the
                  client isn't a member.

        443     ERR_USERONCHANNEL
                        "<user> <channel> :is already on channel"

                - Returned when a client tries to invite a user to a
                  channel they are already on.

        444     ERR_NOLOGIN
                        "<user> :User not logged in"

                - Returned by the summon after a SUMMON command for a
                  user was unable to be performed since they were not
                  logged in.

        445     ERR_SUMMONDISABLED
                        ":SUMMON has been disabled"

                - Returned as a response to the SUMMON command.  Must be
                  returned by any server which does not implement it.

        446     ERR_USERSDISABLED
                        ":USERS has been disabled"

                - Returned as a response to the USERS command.  Must be
                  returned by any server which does not implement it.

        451     ERR_NOTREGISTERED
                        ":You have not registered"

                - Returned by the server to indicate that the client
                  must be registered before the server will allow it
                  to be parsed in detail.

        461     ERR_NEEDMOREPARAMS
                        "<command> :Not enough parameters"

                - Returned by the server by numerous commands to
                  indicate to the client that it didn't supply enough
                  parameters.

        462     ERR_ALREADYREGISTRED
                        ":You may not reregister"

                - Returned by the server to any link which tries to
                  change part of the registered details (such as
                  password or user details from second USER message).


        463     ERR_NOPERMFORHOST
                        ":Your host isn't among the privileged"

                - Returned to a client which attempts to register with
                  a server which does not been setup to allow
                  connections from the host the attempted connection
                  is tried.

        464     ERR_PASSWDMISMATCH
                        ":Password incorrect"

                - Returned to indicate a failed attempt at registering
                  a connection for which a password was required and
                  was either not given or incorrect.

        465     ERR_YOUREBANNEDCREEP
                        ":You are banned from this server"

                - Returned after an attempt to connect and register
                  yourself with a server which has been setup to
                  explicitly deny connections to you.

        467     ERR_KEYSET
                        "<channel> :Channel key already set"
        471     ERR_CHANNELISFULL
                        "<channel> :Cannot join channel (+l)"
        472     ERR_UNKNOWNMODE
                        "<char> :is unknown mode char to me"
        473     ERR_INVITEONLYCHAN
                        "<channel> :Cannot join channel (+i)"
        474     ERR_BANNEDFROMCHAN
                        "<channel> :Cannot join channel (+b)"
        475     ERR_BADCHANNELKEY
                        "<channel> :Cannot join channel (+k)"
        481     ERR_NOPRIVILEGES
                        ":Permission Denied- You're not an IRC operator"

                - Any command requiring operator privileges to operate
                  must return this error to indicate the attempt was
                  unsuccessful.

        482     ERR_CHANOPRIVSNEEDED
                        "<channel> :You're not channel operator"

                - Any command requiring 'chanop' privileges (such as
                  MODE messages) must return this error if the client
                  making the attempt is not a chanop on the specified
                  channel.

        483     ERR_CANTKILLSERVER
                        ":You cant kill a server!"

                - Any attempts to use the KILL command on a server
                  are to be refused and this error returned directly
                  to the client.

        491     ERR_NOOPERHOST
                        ":No O-lines for your host"

                - If a client sends an OPER message and the server has
                  not been configured to allow connections from the
                  client's host as an operator, this error must be
                  returned.

        501     ERR_UMODEUNKNOWNFLAG
                        ":Unknown MODE flag"

                - Returned by the server to indicate that a MODE
                  message was sent with a nickname parameter and that
                  the a mode flag sent was not recognized.

        502     ERR_USERSDONTMATCH
                        ":Cant change mode for other users"

                - Error sent to any user trying to view or change the
                  user mode for a user other than themselves.

*/
