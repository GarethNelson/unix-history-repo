/*
 * The new sysinstall program.
 *
 * This is probably the last program in the `sysinstall' line - the next
 * generation being essentially a complete rewrite.
 *
 * $Id: system.c,v 1.43 1995/05/30 08:28:57 rgrimes Exp $
 *
 * Jordan Hubbard
 *
 * My contributions are in the public domain.
 *
 * Parts of this file are also blatently stolen from Poul-Henning Kamp's
 * previous version of sysinstall, and as such fall under his "BEERWARE license"
 * so buy him a beer if you like it!  Buy him a beer for me, too!
 * Heck, get him completely drunk and send me pictures! :-)
 */

#include "sysinstall.h"
#include <signal.h>
#include <sys/reboot.h>
#include <machine/console.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

/*
 * Handle interrupt signals - this probably won't work in all cases
 * due to our having bogotified the internal state of dialog or curses,
 * but we'll give it a try.
 */
static void
handle_intr(int sig)
{
    if (!msgYesNo("Are you sure you want to abort the installation?"))
	systemShutdown();
}

/* Welcome the user to the system */
void
systemWelcome(void)
{
    printf("Installation system initializing..\n");
}

/* Initialize system defaults */
void
systemInitialize(int argc, char **argv)
{
    int i;

    signal(SIGINT, SIG_IGN);
    globalsInit();

    /* Are we running as init? */
    if (getpid() == 1) {
	setsid();
	if (argc > 1 && strchr(argv[1],'C')) {
	    /* Kernel told us that we are on a CDROM root */
	    close(0); open("/bootcd/dev/console", O_RDWR);
	    close(1); dup(0);
	    close(2); dup(0);
	    OnCDROM = TRUE;
	    chroot("/bootcd");
	} else {
	    close(0); open("/dev/ttyv0", O_RDWR);
	    close(1); dup(0);
	    close(2); dup(0);
	}
	printf("%s running as init\n", argv[0]);

	i = ioctl(0, TIOCSCTTY, (char *)NULL);
	setlogin("root");
	setenv("PATH", "/stand:/bin:/sbin:/usr/sbin:/usr/bin:/mnt/bin:/mnt/sbin:/mnt/usr/sbin:/mnt/usr/bin", 1);
	setbuf(stdin, 0);
	setbuf(stderr, 0);
    }

    for(i = 0; i < 256; i++)
	default_scrnmap[i] = i;

    if (set_termcap() == -1) {
	printf("Can't find terminal entry\n");
	exit(-1);
    }

    /* XXX - libdialog has particularly bad return value checking */
    init_dialog();
    /* If we haven't crashed I guess dialog is running ! */
    DialogActive = TRUE;

    signal(SIGINT, handle_intr);
}

/* Close down and prepare to exit */
void
systemShutdown(void)
{
    if (DialogActive) {
	end_dialog();
	DialogActive = FALSE;
    }
    /* REALLY exit! */
    if (RunningAsInit) {
	/* Put the console back */
	ioctl(0, VT_ACTIVATE, 2);
	reboot(RB_HALT);
    }
    else
	exit(1);
}

/* Run some general command */
int
systemExecute(char *command)
{
    int status;

    dialog_clear();
    dialog_update();
    end_dialog();
    DialogActive = FALSE;
    status = system(command);
    DialogActive = TRUE;
    dialog_clear();
    dialog_update();
    return status;
}

/* Find and execute a shell */
int
systemShellEscape(void)
{
    char *sh = NULL;

    if (file_executable("/bin/sh"))
	sh = "/bin/sh";
    else if (file_executable("/stand/sh"))
	sh = "/stand/sh";
    else {
	msgWarn("No shell available, sorry!");
	return 1;
    }
    setenv("PS1", "freebsd% ", 1);
    dialog_clear();
    dialog_update();
    move(0, 0);
    standout();
    addstr("Type `exit' to leave this shell and continue installation");
    standend();
    refresh();
    end_dialog();
    DialogActive = FALSE;
    if (fork() == 0)
	execlp(sh, "-sh", 0);
    else
	wait(NULL);
    dialog_clear();
    DialogActive = TRUE;
    return 0;
}

/* Display a file in a filebox */
int
systemDisplayFile(char *file)
{
    char *fname = NULL;
    char buf[FILENAME_MAX];
    WINDOW *w;

    fname = systemHelpFile(file, buf);
    if (!fname) {
	snprintf(buf, FILENAME_MAX, "The %s file is not provided on this particular floppy image.", file);
	use_helpfile(NULL);
	use_helpline(NULL);
	w = dupwin(newscr);
	dialog_mesgbox("Sorry!", buf, -1, -1);
	touchwin(w);
	wrefresh(w);
	delwin(w);
	return 1;
    }
    else {
	use_helpfile(NULL);
	use_helpline(NULL);
	w = dupwin(newscr);
	dialog_textbox(file, fname, LINES, COLS);
	touchwin(w);
	wrefresh(w);
	delwin(w);
    }
    return 0;
}

char *
systemHelpFile(char *file, char *buf)
{
    char *cp;
    static char oldfile[64];	/* Should be FILENAME_MAX but I don't feel like wasting that much space */

    if (!file)
	return NULL;

    if ((cp = getenv("LANG")) != NULL) {
	snprintf(buf, FILENAME_MAX, "%s/%s", cp, file);
	if (oldfile[0]) {
	    if (!strcmp(buf, oldfile))
		return oldfile;
	    else {
		unlink(oldfile);
		oldfile[0] = '\0';
	    }
	}
	vsystem("cd /stand && zcat help.tgz | cpio --format=tar -idv %s > /dev/null 2>&1",buf);
	snprintf(buf, FILENAME_MAX, "/stand/%s/%s", cp, file);
	if (file_readable(buf)) {
	    strcpy(oldfile, buf);
	    return buf;
	}
    }
    /* Fall back to normal imperialistic mode :-) */
    cp = "en_US.ISO8859-1";
    snprintf(buf, FILENAME_MAX, "%s/%s", cp, file);
    if (oldfile[0]) {
	if (!strcmp(buf, oldfile))
	    return oldfile;
	else {
	    unlink(oldfile);
	    oldfile[0] = '\0';
	}
    }
    vsystem("cd /stand && zcat help.tgz | cpio --format=tar -idv %s > /dev/null 2>&1",buf);
    snprintf(buf, FILENAME_MAX, "/stand/%s/%s", cp, file);
    if (file_readable(buf)) {
	strcpy(oldfile, buf);
	return buf;
    }
    return NULL;
}

void
systemChangeFont(const u_char font[])
{
    if (OnVTY && ColorDisplay) {
	if (ioctl(0, PIO_FONT8x16, font) < 0)
	    msgConfirm("Sorry!  Unable to load font for %s", getenv("LANG"));
    }
    dialog_clear();
}

void
systemChangeLang(char *lang)
{
    variable_set2("LANG", lang);
}

void
systemChangeTerminal(char *color, const u_char c_term[],
		     char *mono, const u_char m_term[])
{
    extern void init_acs(void);

    if (OnVTY) {
	if (ColorDisplay) {
	    setenv("TERM", color, 1);
	    setenv("TERMCAP", c_term, 1);
	    reset_shell_mode();
	    setterm(color);
	    init_acs();
	    cbreak(); noecho();
	}
	else {
	    setenv("TERM", mono, 1);
	    setenv("TERMCAP", m_term, 1);
	    reset_shell_mode();
	    setterm(mono);
	    init_acs();
	    cbreak(); noecho();
	}
	dialog_clear();
    }
}

void
systemChangeScreenmap(const u_char newmap[])
{
    if (OnVTY) {
	if (ioctl(0, PIO_SCRNMAP, newmap) < 0)
	    msgConfirm("Sorry!  Unable to load the screenmap for %s",
		       getenv("LANG"));
    }
    dialog_clear();
}

int
vsystem(char *fmt, ...)
{
    va_list args;
    int pstat;
    pid_t pid;
    int omask;
    sig_t intsave, quitsave;
    char *cmd,*p;
    int i,magic=0;

    cmd = (char *)malloc(FILENAME_MAX);
    cmd[0] = '\0';
    va_start(args, fmt);
    vsnprintf(cmd, FILENAME_MAX, fmt, args);
    va_end(args);

    /* Find out if this command needs the wizardry of the shell */
    for (p="<>|'`=\"()" ; *p; p++)
	if (strchr(cmd, *p))
	    magic++;
    omask = sigblock(sigmask(SIGCHLD));
    if (isDebug())
	msgDebug("Executing command `%s' (Magic=%d)\n", cmd, magic);
    switch(pid = fork()) {
    case -1:			/* error */
	(void)sigsetmask(omask);
	i = 127;

    case 0:				/* child */
	(void)sigsetmask(omask);
	if (DebugFD != -1) {
	    if (OnVTY && isDebug())
		msgInfo("Command output is on debugging screen - type ALT-F2 to see it");
	    dup2(DebugFD, 0);
	    dup2(DebugFD, 1);
	    dup2(DebugFD, 2);
	}
#ifdef NOT_A_GOOD_IDEA_CRUNCHED_BINARY
	if (magic) {
	    char *argv[100];
	    i = 0;
	    argv[i++] = "crunch";
	    argv[i++] = "sh";
	    argv[i++] = "-c";
	    argv[i++] = cmd;
	    argv[i] = 0;
	    exit(crunched_main(i,argv));
	} else {
	    char *argv[100];
	    i = 0;
	    argv[i++] = "crunch";
	    while (cmd && *cmd) {
		argv[i] = strsep(&cmd," \t");
		if (*argv[i])
		    i++;
	    }
	    argv[i] = 0;
	    if (crunched_here(argv[1]))
		exit(crunched_main(i,argv));
	    else
		execvp(argv[1],argv+1);
	    kill(getpid(),9);
	}
#else /* !CRUNCHED_BINARY */
	execl("/stand/sh", "sh", "-c", cmd, (char *)NULL);
	kill(getpid(),9);
#endif /* CRUNCHED_BINARY */
    }
    intsave = signal(SIGINT, SIG_IGN);
    quitsave = signal(SIGQUIT, SIG_IGN);
    pid = waitpid(pid, &pstat, 0);
    (void)sigsetmask(omask);
    (void)signal(SIGINT, intsave);
    (void)signal(SIGQUIT, quitsave);
    i = (pid == -1) ? -1 : WEXITSTATUS(pstat);
    if (isDebug())
	msgDebug("Command `%s' returns status of %d\n", cmd, i);
    free(cmd);
    return i;
}
