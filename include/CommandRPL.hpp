#pragma once

#define FLAG_KEY 1
#define FLAG_INV 2
#define FLAG_TOPIC 4
#define FLAG_NOOUTSIDE 8
#define FLAG_LIMIT 16


// my includes
#define RPL_JOIN(source, channel) ":" + source + " JOIN " + channel + "\r\n"
#define RPL_PRIVMSG(source, target, message) ":" + source + " PRIVMSG " + target + " :" + message + "\r\n"
#define ERR_ALREADYOPERATOR(nick, channel) (string(":") + "IRC" + " 482 " + nick + " " + channel + " :You're already an operator\r\n")


#define RPL_WELCOME(nick, rfc1459) ": 001 " + nick + " :Welcome to the Internet Relay Network " + rfc1459 + "\r\n"
#define RPL_NONE ": 300 :None" + "\r\n"
#define RPL_USERHOST(nick, host) ": 302 " + nick + " :*1" + host + "\r\n"
#define RPL_ISON(source, nick) ": 303 " + source + " :" + nick + "\r\n"
#define RPL_AWAY(source, nick, message) ": 301 " + source + " " + nick + " :is away: " + message + "\r\n"
#define RPL_UNAWAY ": 305 :You are no longer marked as being away\r\n"
#define RPL_NOWAWAY ": 306 :You have been marked as being away\r\n"
#define RPL_WHOISUSER(source, nick, user, host, realname) ": 311 " + source + " " + nick + " " + user + " " + host + " * :" + realname + "\r\n"
#define RPL_WHOISSERVER(nick, server, serverinfo) ": 312 " + nick + " " + server + " : " + serverinfo + "\r\n"
#define RPL_WHOISOPERATOR(nick) ": 313 " + nick + " :is an IRC operator" + "\r\n"
#define RPL_WHOISIDLE(nick, seconds) ": 317 " + nick + " " + seconds + " :seconds idle" + "\r\n"
#define RPL_ENDOFWHOIS(source, nick) ": 318 " + source + " " + nick + " :End of /WHOIS list" + "\r\n"
#define RPL_WHOISCHANNELS(source, nick, channels) ": 319 " + source + " " + nick + " :" + channels + "\r\n"
#define RPL_WHOWASUSER(nick, user, host, server, realname) ": 314 " + nick + " " + user + " " + host + " * : " + realname + "\r\n"
#define RPL_ENDOFWHOWAS(nick) ": 369 " + nick + " :End of WHOWAS" + "\r\n"
# define RPL_LISTSTART(nick, numusers)			    ": 321 " + nick + " Channel : "+ numusers + "\r\n"
# define RPL_LIST(nick, channel, numusers, topic)   ": 322 " + nick + " " + channel + " " + numusers + " " + topic + "\r\n"
# define RPL_LISTEND(nick)						    ": 323 " + nick + " :End of /LIST\r\n"
#define RPL_CHANNELMODEIS(source, channel, mode) ": 324 " + source + " " + channel + " " + mode + "\r\n"
#define RPL_MODE(source, channel, mode, modeparams) ":" + source + " MODE " + channel + " " + mode + " " + modeparams + "\r\n"
#define RPL_NOTOPIC(source, channel) ": 331 " + source + " " + channel + " :No topic is set" + "\r\n"
#define RPL_TOPIC(source, channel, topic) ": 332 " + source + " " + channel + " " + topic + "\r\n"
#define RPL_INVITING(source, channel, nick) ": 341 " + source + " " + channel + " " + nick + "\r\n"
#define RPL_SUMMONING(user) ": 342 " + user + " :Summoning user to IRC" + "\r\n"
#define RPL_VERSION(version, debuglevel, server, comments) ": 351 " + version + " " + debuglevel + " " + server + " : " + comments + "\r\n"
#define RPL_NAMREPLY(nick, channel, users)			": 353 " + nick + " = " + channel + " :" + users + "\r\n"
#define RPL_ENDOFNAMES(nick, channel) ": 366 " + nick + " " + channel + " :End of NAMES list" + "\r\n"
#define RPL_LINKS(mask, server, hopcount, serverinfo) ": 364 " + mask + " " + server + " " + hopcount + " " + serverinfo + "\r\n"
#define RPL_ENDOFLINKS(mask) ": 365 " + mask + " :End of LINKS list" + "\r\n"
#define RPL_BANLIST(channel, banmask) ": 367 " + channel + " " + banmask + "\r\n"
#define RPL_ENDOFBANLIST(channel) ": 368 " + channel + " :End of BAN list" + "\r\n"
#define RPL_INFO(info) ": 371 : " + info + "\r\n"
#define RPL_ENDOFINFO ": 374 :End of INFO list" + "\r\n"
#define RPL_MOTDSTART ": 375 :- " + "\r\n"
#define RPL_MOTD(motd) ": 372 :- " + motd + "\r\n"
#define RPL_ENDOFMOTD ": 376 :End of MOTD command" + "\r\n"
#define RPL_YOUREOPER ": 381 :You are now an IRC operator" + "\r\n"
#define RPL_REHASHING(configfile) ": 382 " + configfile + " :Rehashing" + "\r\n"
#define RPL_TIME(server, time) ": 391 " + server + " " + time + "\r\n"
#define RPL_USERSSTART ": 392 :UserID Terminal Host" + "\r\n"
#define RPL_USERS(user, terminal, host, server) ": 393 " + user + " " + terminal + " " + host + " " + server + "\r\n"
#define RPL_ENDOFUSERS ": 394 :End of users" + "\r\n"
#define RPL_NOUSERS ": 395 :Nobody logged in" + "\r\n"
#define RPL_TRACELINK(version, debuglevel, dest, nextserver) ": 200 " + version + " " + debuglevel + " " + dest + " " + nextserver + "\r\n"
#define RPL_TRACECONNECTING(server) ": 201 " + server + " :Try. Class" + "\r\n"
#define RPL_TRACEHANDSHAKE(server) ": 202 " + server + " :H.S. Class" + "\r\n"
#define RPL_TRACEUNKNOWN(server) ": 203 " + server + " :Unknown Class" + "\r\n"
#define RPL_TRACEOPERATOR(server) ": 204 " + server + " :Operator Class" + "\r\n"
#define RPL_TRACEUSER(server) ": 205 " + server + " :User Class" + "\r\n"
#define RPL_TRACESERVER(server, serverinfo) ": 206 " + server + " " + serverinfo + "\r\n"
#define RPL_TRACENEWTYPE(newtype, client) ": 208 " + newtype + " " + client + " :New type" + "\r\n"
#define RPL_TRACELOG(server, logfile, debuglevel) ": 261 " + server + " " + logfile + " " + debuglevel + "\r\n"
#define RPL_STATSLINKINFO(server, sendq, sentmessages, sentkbytes, receivedmessages, receivedkbytes, timeopen) ": 211 " + server + " " + sendq + " " + sentmessages + " " + sentkbytes + " " + receivedmessages + " " + receivedkbytes + " " + timeopen + "\r\n"
#define RPL_STATSCOMMANDS(command, count) ": 212 " + command + " " + count + "\r\n"
#define RPL_STATSCLINE(host, servername, port, class) ": 213 " + host + " " + servername + " " + port + " " + class + "\r\n"
#define RPL_STATSNLINE(host, servername, port, class) ": 214 " + host + " " + servername + " " + port + " " + class + "\r\n"
#define RPL_STATSILINE(host, servername, port, class) ": 215 " + host + " " + servername + " " + port + " " + class + "\r\n"
#define RPL_STATSKLINE(host, servername, port, class) ": 216 " + host + " " + servername + " " + port + " " + class + "\r\n"
#define RPL_STATSYLINE(host, class, pingfreq, conntime) ": 218 " + host + " " + class + " " + pingfreq + " " + conntime + "\r\n"
#define RPL_ENDOFSTATS(stats) ": 219 " + stats + " :End of STATS report" + "\r\n"
#define RPL_STATSLLINE(hostmask, servername, maxdepth) ": 241 " + hostmask + " " + servername + " " + maxdepth + "\r\n"
#define RPL_STATSUPTIME(uptime) ": 242 :Server Up " + uptime + "\r\n"
#define RPL_STATSOLINE(hostmask, name) ": 243 " + hostmask + " " + name + "\r\n"
#define RPL_STATSHLINE(hostmask, servername) ": 244 " + hostmask + " " + servername + "\r\n"
#define RPL_UMODEIS(mode) ": 221 " + mode + "\r\n"
#define RPL_LUSERCLIENT(integer) ": 251 :There are " + integer + " users and " + integer + " invisible on " + integer + " servers" + "\r\n"
#define RPL_LUSEROP(integer) ": 252 " + integer + " :operator(s) online" + "\r\n"
#define RPL_LUSERUNKNOWN(integer) ": 253 " + integer + " :unknown connection(s)" + "\r\n"
#define RPL_LUSERCHANNELS(integer) ": 254 " + integer + " :channels formed" + "\r\n"
#define RPL_LUSERME(integer, integer1, integer2) ": 255 :I have " + integer1 + " clients and " + integer2 + " servers" + "\r\n"
#define RPL_ADMINME(server) ": 256 :Administrative info about " + server + "\r\n"
#define RPL_ADMINLOC1(info) ": 257 : " + info + "\r\n"
#define RPL_ADMINLOC2(info) ": 258 : " + info + "\r\n"
#define RPL_ADMINEMAIL(info) ": 259 : " + info + "\r\n"

/*
6.2 Command responses.

        300     RPL_NONE
                        Dummy reply number. Not used.

        302     RPL_USERHOST
                        ":[<reply>{<space><reply>}]"

                - Reply format used by USERHOST to list replies to
                  the query list.  The reply string is composed as
                  follows:

                  <reply> ::= <nick>['*'] '=' <'+'|'-'><hostname>

                  The '*' indicates whether the client has registered
                  as an Operator.  The '-' or '+' characters represent
                  whether the client has set an AWAY message or not
                  respectively.

        303     RPL_ISON
                        ":[<nick> {<space><nick>}]"

                - Reply format used by ISON to list replies to the
                  query list.

        301     RPL_AWAY
                        "<nick> :<away message>"

        305     RPL_UNAWAY
                        ":You are no longer marked as being away"
        306     RPL_NOWAWAY
                        ":You have been marked as being away"

                - These replies are used with the AWAY command (if
                  allowed).  RPL_AWAY is sent to any client sending a
                  PRIVMSG to a client which is away.  RPL_AWAY is only
                  sent by the server to which the client is connected.
                  Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the
                  client removes and sets an AWAY message.

        311     RPL_WHOISUSER
                        "<nick> <user> <host> * :<real name>"
        312     RPL_WHOISSERVER
                        "<nick> <server> :<server info>"
        313     RPL_WHOISOPERATOR
                        "<nick> :is an IRC operator"
        317     RPL_WHOISIDLE
                        "<nick> <integer> :seconds idle"
        318     RPL_ENDOFWHOIS
                        "<nick> :End of /WHOIS list"
        319     RPL_WHOISCHANNELS
                        "<nick> :{[@|+]<channel><space>}"

                - Replies 311 - 313, 317 - 319 are all replies
                  generated in response to a WHOIS message.  Given that
                  there are enough parameters present, the answering
                  server must either formulate a reply out of the above
                  numerics (if the query nick is found) or return an
                  error reply.  The '*' in RPL_WHOISUSER is there as
                  the literal character and not as a wild card.  For
                  each reply set, only RPL_WHOISCHANNELS may appear
                  more than once (for long lists of channel names).
                  The '@' and '+' characters next to the channel name
                  indicate whether a client is a channel operator or
                  has been granted permission to speak on a moderated
                  channel.  The RPL_ENDOFWHOIS reply is used to mark
                  the end of processing a WHOIS message.

        314     RPL_WHOWASUSER
                        "<nick> <user> <host> * :<real name>"
        369     RPL_ENDOFWHOWAS
                        "<nick> :End of WHOWAS"

                - When replying to a WHOWAS message, a server must use
                  the replies RPL_WHOWASUSER, RPL_WHOISSERVER or
                  ERR_WASNOSUCHNICK for each nickname in the presented
                  list.  At the end of all reply batches, there must
                  be RPL_ENDOFWHOWAS (even if there was only one reply
                  and it was an error).

        321     RPL_LISTSTART
                        "Channel :Users  Name"
        322     RPL_LIST
                        "<channel> <# visible> :<topic>"
        323     RPL_LISTEND
                        ":End of /LIST"

                - Replies RPL_LISTSTART, RPL_LIST, RPL_LISTEND mark
                  the start, actual replies with data and end of the
                  server's response to a LIST command.  If there are
                  no channels available to return, only the start
                  and end reply must be sent.

        324     RPL_CHANNELMODEIS
                        "<channel> <mode> <mode params>"

        331     RPL_NOTOPIC
                        "<channel> :No topic is set"
        332     RPL_TOPIC
                        "<channel> :<topic>"

                - When sending a TOPIC message to determine the
                  channel topic, one of two replies is sent.  If
                  the topic is set, RPL_TOPIC is sent back else
                  RPL_NOTOPIC.

        341     RPL_INVITING
                        "<channel> <nick>"

                - Returned by the server to indicate that the
                  attempted INVITE message was successful and is
                  being passed onto the end client.

        342     RPL_SUMMONING
                        "<user> :Summoning user to IRC"

                - Returned by a server answering a SUMMON message to
                  indicate that it is summoning that user.

        351     RPL_VERSION
                        "<version>.<debuglevel> <server> :<comments>"

                - Reply by the server showing its version details.
                  The <version> is the version of the software being
                  used (including any patchlevel revisions) and the
                  <debuglevel> is used to indicate if the server is
                  running in "debug mode".

                  The "comments" field may contain any comments about
                  the version or further version details.

        352     RPL_WHOREPLY
                        "<channel> <user> <host> <server> <nick> \
                         <H|G>[*][@|+] :<hopcount> <real name>"
        315     RPL_ENDOFWHO
                        "<name> :End of /WHO list"

                - The RPL_WHOREPLY and RPL_ENDOFWHO pair are used
                  to answer a WHO message.  The RPL_WHOREPLY is only
                  sent if there is an appropriate match to the WHO
                  query.  If there is a list of parameters supplied
                  with a WHO message, a RPL_ENDOFWHO must be sent
                  after processing each list item with <name> being
                  the item.

        353     RPL_NAMREPLY
                        "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
        366     RPL_ENDOFNAMES
                        "<channel> :End of /NAMES list"

                - To reply to a NAMES message, a reply pair consisting
                  of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
                  server back to the client.  If there is no channel
                  found as in the query, then only RPL_ENDOFNAMES is
                  returned.  The exception to this is when a NAMES
                  message is sent with no parameters and all visible
                  channels and contents are sent back in a series of
                  RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
                  the end.

        364     RPL_LINKS
                        "<mask> <server> :<hopcount> <server info>"
        365     RPL_ENDOFLINKS
                        "<mask> :End of /LINKS list"

                - In replying to the LINKS message, a server must send
                  replies back using the RPL_LINKS numeric and mark the
                  end of the list using an RPL_ENDOFLINKS reply.

        367     RPL_BANLIST
                        "<channel> <banid>"
        368     RPL_ENDOFBANLIST

                        "<channel> :End of channel ban list"

                - When listing the active 'bans' for a given channel,
                  a server is required to send the list back using the
                  RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
                  RPL_BANLIST is sent for each active banid.  After the
                  banids have been listed (or if none present) a
                  RPL_ENDOFBANLIST must be sent.

        371     RPL_INFO
                        ":<string>"
        374     RPL_ENDOFINFO
                        ":End of /INFO list"

                - A server responding to an INFO message is required to
                  send all its 'info' in a series of RPL_INFO messages
                  with a RPL_ENDOFINFO reply to indicate the end of the
                  replies.

        375     RPL_MOTDSTART
                        ":- <server> Message of the day - "
        372     RPL_MOTD
                        ":- <text>"
        376     RPL_ENDOFMOTD
                        ":End of /MOTD command"

                - When responding to the MOTD message and the MOTD file
                  is found, the file is displayed line by line, with
                  each line no longer than 80 characters, using
                  RPL_MOTD format replies.  These should be surrounded
                  by a RPL_MOTDSTART (before the RPL_MOTDs) and an
                  RPL_ENDOFMOTD (after).

        381     RPL_YOUREOPER
                        ":You are now an IRC operator"

                - RPL_YOUREOPER is sent back to a client which has
                  just successfully issued an OPER message and gained
                  operator status.

        382     RPL_REHASHING
                        "<config file> :Rehashing"

                - If the REHASH option is used and an operator sends
                  a REHASH message, an RPL_REHASHING is sent back to
                  the operator.

        391     RPL_TIME



Oikarinen & Reed                                               [Page 52]

RFC 1459              Internet Relay Chat Protocol              May 1993


                        "<server> :<string showing server's local time>"

                - When replying to the TIME message, a server must send
                  the reply using the RPL_TIME format above.  The string
                  showing the time need only contain the correct day and
                  time there.  There is no further requirement for the
                  time string.

        392     RPL_USERSSTART
                        ":UserID   Terminal  Host"
        393     RPL_USERS
                        ":%-8s %-9s %-8s"
        394     RPL_ENDOFUSERS
                        ":End of users"
        395     RPL_NOUSERS
                        ":Nobody logged in"

                - If the USERS message is handled by a server, the
                  replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and
                  RPL_NOUSERS are used.  RPL_USERSSTART must be sent
                  first, following by either a sequence of RPL_USERS
                  or a single RPL_NOUSER.  Following this is
                  RPL_ENDOFUSERS.

        200     RPL_TRACELINK
                        "Link <version & debug level> <destination> \
                         <next server>"
        201     RPL_TRACECONNECTING
                        "Try. <class> <server>"
        202     RPL_TRACEHANDSHAKE
                        "H.S. <class> <server>"
        203     RPL_TRACEUNKNOWN
                        "???? <class> [<client IP address in dot form>]"
        204     RPL_TRACEOPERATOR
                        "Oper <class> <nick>"
        205     RPL_TRACEUSER
                        "User <class> <nick>"
        206     RPL_TRACESERVER
                        "Serv <class> <int>S <int>C <server> \
                         <nick!user|*!*>@<host|server>"
        208     RPL_TRACENEWTYPE
                        "<newtype> 0 <client name>"
        261     RPL_TRACELOG
                        "File <logfile> <debug level>"

                - The RPL_TRACE* are all returned by the server in
                  response to the TRACE message.  How many are
                  returned is dependent on the the TRACE message and
                  whether it was sent by an operator or not.  There
                  is no predefined order for which occurs first.
                  Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and
                  RPL_TRACEHANDSHAKE are all used for connections
                  which have not been fully established and are either
                  unknown, still attempting to connect or in the
                  process of completing the 'server handshake'.
                  RPL_TRACELINK is sent by any server which handles
                  a TRACE message and has to pass it on to another
                  server.  The list of RPL_TRACELINKs sent in
                  response to a TRACE command traversing the IRC
                  network should reflect the actual connectivity of
                  the servers themselves along that path.
                  RPL_TRACENEWTYPE is to be used for any connection
                  which does not fit in the other categories but is
                  being displayed anyway.

        211     RPL_STATSLINKINFO
                        "<linkname> <sendq> <sent messages> \
                         <sent bytes> <received messages> \
                         <received bytes> <time open>"
        212     RPL_STATSCOMMANDS
                        "<command> <count>"
        213     RPL_STATSCLINE
                        "C <host> * <name> <port> <class>"
        214     RPL_STATSNLINE
                        "N <host> * <name> <port> <class>"
        215     RPL_STATSILINE
                        "I <host> * <host> <port> <class>"
        216     RPL_STATSKLINE
                        "K <host> * <username> <port> <class>"
        218     RPL_STATSYLINE
                        "Y <class> <ping frequency> <connect \
                         frequency> <max sendq>"
        219     RPL_ENDOFSTATS
                        "<stats letter> :End of /STATS report"
        241     RPL_STATSLLINE
                        "L <hostmask> * <servername> <maxdepth>"
        242     RPL_STATSUPTIME
                        ":Server Up %d days %d:%02d:%02d"
        243     RPL_STATSOLINE
                        "O <hostmask> * <name>"
        244     RPL_STATSHLINE
                        "H <hostmask> * <servername>"

        221     RPL_UMODEIS
                        "<user mode string>"
                        - To answer a query about a client's own mode,
                          RPL_UMODEIS is sent back.

        251     RPL_LUSERCLIENT
                        ":There are <integer> users and <integer> \
                         invisible on <integer> servers"
        252     RPL_LUSEROP
                        "<integer> :operator(s) online"
        253     RPL_LUSERUNKNOWN
                        "<integer> :unknown connection(s)"
        254     RPL_LUSERCHANNELS
                        "<integer> :channels formed"
        255     RPL_LUSERME
                        ":I have <integer> clients and <integer> \
                          servers"

                        - In processing an LUSERS message, the server
                          sends a set of replies from RPL_LUSERCLIENT,
                          RPL_LUSEROP, RPL_USERUNKNOWN,
                          RPL_LUSERCHANNELS and RPL_LUSERME.  When
                          replying, a server must send back
                          RPL_LUSERCLIENT and RPL_LUSERME.  The other
                          replies are only sent back if a non-zero count
                          is found for them.

        256     RPL_ADMINME
                        "<server> :Administrative info"
        257     RPL_ADMINLOC1
                        ":<admin info>"
        258     RPL_ADMINLOC2
                        ":<admin info>"
        259     RPL_ADMINEMAIL
                        ":<admin info>"

                        - When replying to an ADMIN message, a server
                          is expected to use replies RLP_ADMINME
                          through to RPL_ADMINEMAIL and provide a text
                          message with each.  For RPL_ADMINLOC1 a
                          description of what city, state and country
                          the server is in is expected, followed by
                          details of the university and department
                          (RPL_ADMINLOC2) and finally the administrative
                          contact for the server (an email address here
                          is required) in RPL_ADMINEMAIL.



*/
