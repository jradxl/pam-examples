#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>

/*  
 * Wrapper around conversation function (a callback function provided by
 * the PAM application to interact with the user)
 * (based on converse in pam_unix/support.c)
 * I've taken from otpw
 */
static int converse(pam_handle_t *pamh, int nargs,
                    struct pam_message **message,
                    struct pam_response **response,
                    int debug)
{
    int retval;
    struct pam_conv *conv;

    /* get pointer to conversation function */
    retval = pam_get_item(pamh, PAM_CONV, (const void **) &conv);
    if (retval != PAM_SUCCESS) {
        //log_message(LOG_ERR, pamh, "no conversation function: %s", pam_strerror(pamh, retval));
        pam_syslog(pamh, LOG_ERR, "Pam_Clear: no conversation function:  %s", pam_strerror(pamh, retval));
        return retval;
    }

    /* call conversation function */
    retval = conv->conv(nargs, (const struct pam_message **) message,
                        response, conv->appdata_ptr);

    if (retval != PAM_SUCCESS) {
        //log_message(LOG_WARNING, pamh, "conversation function failed: %s", pam_strerror(pamh, retval));
        pam_syslog(pamh, LOG_INFO, "Pam_Clear: conversation function failed: %s", pam_strerror(pamh, retval));
    }

    /* propagate error status */
    return retval;
}

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
    pam_syslog(pamh, LOG_INFO, "Pam_Clear: pam_sm_setcred not used");
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    pam_syslog(pamh, LOG_INFO, "Pam_Clear: pam_sm_acct_mgmt not used");
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
	int retval;
    int i;

    pam_syslog(pamh, LOG_INFO, "Pam_Clear: Getting username from PAM stack");

	const char* pUsername;
	retval = pam_get_user(pamh, &pUsername, "Username: ");
    if (retval != PAM_SUCCESS) {
        pam_syslog(pamh, LOG_ERR, "Pam_Clear: Couldn't get username from PAM stack");
		return retval;
	}
    pam_syslog(pamh, LOG_INFO, "Pam_Clear: Username: %s", pUsername);

    retval = pam_set_item(pamh, PAM_AUTHTOK, NULL);
    if (retval != PAM_SUCCESS) {
        pam_syslog(pamh, LOG_ERR, "Pam_Clear: Couldn't use Set_Item to Clear PAM_AUTHTOK");
		return retval;
	}

    retval = pam_set_item(pamh, PAM_OLDAUTHTOK, NULL);
    if (retval != PAM_SUCCESS) {
        pam_syslog(pamh, LOG_ERR, "Pam_Clear: Couldn't use Set_Item to Clear PAM_OLDAUTHTOK");
		return retval;
	}

    pam_syslog(pamh, LOG_INFO, "Pam_Clear: Cleared both passwords.");
	return PAM_SUCCESS;
}
