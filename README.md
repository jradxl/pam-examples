# pam-examples
Linux PAM example Modules

I was interested in how PAM worked, but after reading the documentation, I could work out why I couldn't get two consecutive password prompts, using this change to Common-Auth (Ubuntu 21.04)

# common-auth - After initial comments
auth    required   pam_pwdfile.so  pwdfile=/root/passwd_file
auth	  required   pam_clear.so
# Anything below this comment will be changed by pam-auth-update(8) #

Note that it is Debian/Ubuntu that introduces the @include (don't go loading LINUX Pam 1.5.1 in, as it won't work - Linux Pam contains no /etc/pam.d configurations)

I've always puzzled as to why you type your own passwd into sudo!.
Surely anyone hacking your account can then get to root.
The arguement goes, that in the days before sudo, the System Admin was persuaded to give out root password, then of course everyone got it!
So by inventing sudo and requiring your own password, there was at least some control.

If you search Github and beyond there are many other auth options.
I choose to try, 
https://github.com/tiwe-de/libpam-pwdfile
But the first password prompt passed it to the second line - if they were not the same then auth was denied, hence rather pointless.

In asking I got this helpful response, the try_file_pass was now baked in and couldn't be turned off, but the suggestion was that it could be cleared.
Hence pam_clear
See
https://github.com/linux-pam/linux-pam/issues/364



