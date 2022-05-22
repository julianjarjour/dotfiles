/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Liberation Sans:size=12" };
static const char dmenufont[]       =   "Liberation Sans:size=12";
static const char col_bgn[]         = "#282a36";
static const char col_bgs[]         = "#44475a";
static const char col_fg[]          = "#f8f8f2";
static const char col_red[]         = "#ff5555";
static const char *colors[][3]      = {
	/*               fg      bg       border   */
	[SchemeNorm] = { col_fg, col_bgn, col_bgs},
	[SchemeSel]  = { col_fg, col_bgs, col_red },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
//   class         instance   title      tags mask    float        monitor
    { "Sxiv",      NULL,      NULL,      0,           1,           -1 },
    { "feh",       NULL,      NULL,      0,           1,           -1 },
    { "Thunar",    NULL,      NULL,      0,           1,           -1 },
    { "mpv",       NULL,      NULL,      0,           1,           -1 },
    { "Steam",     NULL,      NULL,      0,           1,           -1 },
    { "Lutris",    NULL,      NULL,      0,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bgn, "-nf", col_fg, "-sb", col_bgs, "-sf", col_fg, NULL };
static const char *maimc[]  = { "dwm_run", "c", NULL };
static const char *maims[]  = { "dwm_run", "s", NULL };
static const char *papepick[]  = { "dwm_run", "w", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *chromcmd[]  = { "chromium", NULL };
static const char *discordcmd[]  = { "discord", NULL };
static const char *spotifycmd[]  = { "spotify", NULL };
static const char *zathuracmd[]  = { "zathura", NULL };
static const char *upvol[] = { "dwm_run", "u", NULL };
static const char *downvol[] = { "dwm_run", "d", NULL };
static const char *headphone[] = { "pacmd", "set-default-sink", "alsa_output.usb-Kingston_HyperX_Virtual_Surround_Sound_00000000-00.analog-stereo", NULL };
static const char *speakers[] = { "pacmd", "set-default-sink", "alsa_output.pci-0000_00_1b.0.analog-stereo", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[]  = { "alacritty", "-t", scratchpadname, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_Up,     spawn,         {.v = upvol } },
  { MODKEY,                       XK_Down,   spawn,         {.v = downvol } },
	{ MODKEY,                       XK_space,  spawn,         {.v = dmenucmd } },
	{ MODKEY,                       XK_Left,   spawn,         {.v = discordcmd } },
	{ MODKEY,                       XK_Right,  spawn,         {.v = spotifycmd } },
	{ MODKEY,                       XK_Return, spawn,         {.v = termcmd } },
	{ MODKEY,                       XK_Print,  spawn,         {.v = maimc } },
	{ MODKEY|ShiftMask,             XK_Print,  spawn,         {.v = maims } },
	{ MODKEY|ControlMask,           XK_w,      spawn,         {.v = papepick } },
	{ MODKEY,                       XK_r,      spawn,         {.v = chromcmd } },
	{ MODKEY,                       XK_p,      togglescratch, {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_F11,    spawn,         {.v = headphone } },
	{ MODKEY|ShiftMask,             XK_F12,    spawn,         {.v = speakers } },
	{ MODKEY,                       XK_v,      spawn,          {.v = zathuracmd } },
	{ MODKEY,                       XK_f,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_period, setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_p,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_o,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

