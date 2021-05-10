# Pam Examples
Linux PAM Example Modules

I was interested in how PAM worked, but after reading the documentation, I couldn't work out why I couldn't get two consecutive password prompts, using this change to Common-Auth (Ubuntu 21.04)

	# common-auth - After initial comments
	auth    required    pam_pwdfile.so    pwdfile=/root/passwd_file
	auth    required    pam_clear.so
	# Anything below this comment will be changed by pam-auth-update(8) #

Note that it is Debian/Ubuntu that introduces the @include (don't go loading LINUX Pam 1.5.1 in, as it won't work - Linux Pam contains no /etc/pam.d configurations)

I've always puzzled as to why you type your own passwd into sudo!.
Surely anyone hacking your account can then get to root.
The argument goes, that in the days before sudo, the System Admin was persuaded to give out then root password, then of course everyone got it!
So by inventing sudo and requiring your own password, there was at least some control.

If you search Github and beyond there are many other auth options.
I chose to try, 
https://github.com/tiwe-de/libpam-pwdfile
But the first password prompt passed the password to the second line - if they were not the same then auth was denied - they would need to be the same to get access, hence rather pointless.

In asking I got this helpful response, the try_first_pass was now baked in and couldn't be turned off, but the suggestion was that it could be cleared.
Hence pam_clear
See
https://github.com/linux-pam/linux-pam/issues/364

It's very confusing to get two password prompts, especially for sudo, but it does work.

	$ sudo -i
	[sudo] password for XXXX: 
	[sudo] password for XXXX: 

	May 11 00:41:46 u2104ab sudo[48697]: pam_clear(sudo:auth): Pam_Clear: Getting username from PAM stack
	May 11 00:41:46 u2104ab sudo[48697]: pam_clear(sudo:auth): Pam_Clear: Username: XXXXX
	May 11 00:41:46 u2104ab sudo[48697]: pam_clear(sudo:auth): Pam_Clear: Cleared both passwords.
	May 11 00:41:50 u2104ab sudo[48697]:  XXXXX : TTY=pts/7 ; PWD=/root ; USER=root ; COMMAND=/bin/bash
	May 11 00:41:50 u2104ab sudo[48697]: pam_clear(sudo:setcred): Pam_Clear: pam_sm_setcred not used
	May 11 00:41:50 u2104ab sudo[48697]: pam_unix(sudo:session): session opened for user root by (uid=1000)


