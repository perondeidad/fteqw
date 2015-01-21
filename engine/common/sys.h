/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// sys.h -- non-portable functions

//
// file IO
// for the most part, we use stdio.
// if your system doesn't have stdio then urm... well.
//
void Sys_mkdir (char *path);	//not all pre-unix systems have directories (including dos 1)
qboolean Sys_remove (char *path);
qboolean Sys_Rename (char *oldfname, char *newfname);
qboolean Sys_FindGameData(const char *poshname, const char *gamename, char *basepath, int basepathlen);

//
// memory protection
//
void Sys_MakeCodeWriteable (void * startaddr, unsigned long length);

//
// system IO
//
int VARGS Sys_DebugLog(char *file, char *fmt, ...) LIKEPRINTF(2);

NORETURN void VARGS Sys_Error (const char *error, ...) LIKEPRINTF(1);
// an error will cause the entire program to exit

void VARGS Sys_Printf (char *fmt, ...) LIKEPRINTF(1);
// send text to the console
void Sys_Warn (char *fmt, ...) LIKEPRINTF(1);
//like Sys_Printf. dunno why there needs to be two of em.

void Sys_Quit (void);
void Sys_RecentServer(char *command, char *target, char *title, char *desc);

typedef struct {
	void **funcptr;
	char *name;
} dllfunction_t;
typedef void dllhandle_t;	//typically used as void*
dllhandle_t *Sys_LoadLibrary(const char *name, dllfunction_t *funcs);
void Sys_CloseLibrary(dllhandle_t *lib);
void *Sys_GetAddressForName(dllhandle_t *module, const char *exportname);
char *Sys_GetNameForAddress(dllhandle_t *module, void *address);

qboolean LibZ_Init(void);
qboolean LibJPEG_Init(void);
qboolean LibPNG_Init(void);

qboolean Sys_RunFile(const char *fname, int nlen);

unsigned int Sys_Milliseconds (void);
double Sys_DoubleTime (void);
qboolean Sys_RandomBytes(qbyte *string, int len);

char *Sys_ConsoleInput (void);

char *Sys_GetClipboard(void);	//A stub would return NULL
void Sys_CloseClipboard(char *buf); //a stub would do nothing
void Sys_SaveClipboard(char *text); //a stub would do nothing.

//stuff for dynamic dedicated console -> gfx and back.
void Sys_CloseTerminal (void);
qboolean Sys_InitTerminal (void);
void Con_PrintToSys(void);

void Sys_ServerActivity(void);
//make window flash on the taskbar - someone said something/connected

void Sys_SendKeyEvents (void);
// Perform Key_Event () callbacks until the input que is empty

int Sys_EnumerateFiles (const char *gpath, const char *match, int (QDECL *func)(const char *fname, qofs_t fsize, void *parm, searchpathfuncs_t *spath), void *parm, searchpathfuncs_t *spath);

void Sys_Vibrate(float count);

qboolean Sys_GetDesktopParameters(int *width, int *height, int *bpp, int *refreshrate);

#ifdef MULTITHREAD
#if defined(_WIN32) && defined(_DEBUG)
void Sys_SetThreadName(unsigned int dwThreadID, char *threadName);
#endif

void Sys_ThreadsInit(void);
//qboolean Sys_IsThread(void *thread);
qboolean Sys_IsMainThread(void);
void *Sys_CreateThread(char *name, int (*func)(void *), void *args, int priority, int stacksize);
void Sys_WaitOnThread(void *thread);
void Sys_DetachThread(void *thread);
void Sys_ThreadAbort(void);

#define THREADP_IDLE -5
#define THREADP_NORMAL 0
#define THREADP_HIGHEST 5

void *Sys_CreateMutex(void);
qboolean Sys_TryLockMutex(void *mutex);
qboolean Sys_LockMutex(void *mutex);
qboolean Sys_UnlockMutex(void *mutex);
void Sys_DestroyMutex(void *mutex);

/* Conditional wait calls */
void *Sys_CreateConditional(void);
qboolean Sys_LockConditional(void *condv);
qboolean Sys_UnlockConditional(void *condv);
qboolean Sys_ConditionWait(void *condv);		//lock first
qboolean Sys_ConditionSignal(void *condv);		//lock first
qboolean Sys_ConditionBroadcast(void *condv);	//lock first
void Sys_DestroyConditional(void *condv);
#else
#define Sys_IsMainThread() true
#define Sys_CreateMutex() NULL
#define Sys_LockMutex(m) true
#define Sys_UnlockMutex(m) true
#define Sys_DestroyMutex(m)
#define Sys_IsThread(t) !t
#endif

void Sys_Sleep(double seconds);

#ifdef NPFTE
qboolean NPQTV_Sys_Startup(int argc, char *argv[]);
void NPQTV_Sys_MainLoop(void);
#endif

#ifdef _WIN32
int StartLocalServer(int close);

#define HAVEAUTOUPDATE
int Sys_GetAutoUpdateSetting(void);
void Sys_SetAutoUpdateSetting(int newval);
#else
#define Sys_GetAutoUpdateSetting() -1
#define Sys_SetAutoUpdateSetting(n)
#endif

void Sys_Init (void);
void Sys_Shutdown(void);

