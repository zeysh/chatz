#ifndef _IRC_H
#define _IRC_H

int irc_user (char *buffer, const char *ident, char *server);
int irc_nick (char *buffer, const char *nick);
int irc_pong (const char *server);
int irc_join (char *buffer, const char *channels, const char *keys);
int irc_quit (char *buffer, const char *message);
int irc_operator (char *buffer, const char *nick, const char *passwd);
int irc_privmsg (char *buffer, const char *recip, const char *message);

#endif
