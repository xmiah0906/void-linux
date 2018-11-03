///---Modifiers---///
#define MOD             XCB_MOD_MASK_4       

///--Speed---///
/* Move this many pixels when moving or resizing with keyboard unless the window has hints saying otherwise.*/
static const uint16_t movements[] = {10,20,10,400};

/* resize by line like in mcwm -- jmbi */
static const bool     resize_by_line          = true;

/* the ratio used when resizing and keeping the aspect */
static const float    resize_keep_aspect_ratio= 1;

///---Offsets---///
static const uint8_t offsets[] = {6,5,12,36};

///---Colors---///
static const char *colors[] = {"#35586c","#333333","#7a8c5c","#ff6666","#cc9933","#0d131a","#000000"};

/* if this is set to true the inner border and outer borders colors will be swapped */
static const bool inverted_colors = true;

///---Cursor---///
/* default position of the cursor:
 * correct values are:
 * TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, MIDDLE
 * All these are relative to the current window. */
#define CURSOR_POSITION BOTTOM_LEFT

///---Borders---///
static const uint8_t borders[] = {3,5,10,2};

//--WM_NAME-- using `xprop WM_NAME`//
#define LOOK_INTO "WM_NAME"
static const char *ignore_names[] = {"bar", "xclock"};

///--Menus and Programs---///
static const char *termcmd[]   = {"urxvtc", "-geometry", "65x38", NULL };
static const char *menucmd[]   = { "", NULL };

///--Custom foo---///
static void halfandcentered(const Arg *arg)
{
	Arg arg2 = {.i=TWOBWM_MAXHALF_VERTICAL_LEFT};
	maxhalf(&arg2);
	Arg arg3 = {.i=TWOBWM_TELEPORT_CENTER};
	teleport(&arg3);
}

static void killandfocus(const Arg *arg)
{
	deletewin(arg);
	Arg arg3 = {.i=TWOBWM_FOCUS_PREVIOUS};
	focusnext(&arg3);
}

static void sendandfocus(const Arg *arg)
{
	sendtoworkspace(arg);
	Arg arg2 = {.i=TWOBWM_FOCUS_PREVIOUS};
	focusnext(&arg2);
}

#define WORKSPACES 7

///---Shortcuts---///
#define DESKTOPCHANGE(K,N) \
{  MOD ,             K,              changeworkspace, {.i=N}}, \
{  MOD |SHIFT,       K,              sendtoworkspace, {.i=N}},
static key keys[] = {
    /* modifier           key            function           argument */
    // Focus to next/previous window
    {  MOD ,              XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_NEXT}},
    {  MOD |SHIFT,        XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_PREVIOUS}},
    // Kill a window
    {  MOD ,              XK_q,          killandfocus,      {.i=TWOBWM_FOCUS_PREVIOUS}},
    // Resize a window
    {  MOD |SHIFT,        XK_k,          resizestep,        {.i=TWOBWM_RESIZE_UP}},
    {  MOD |SHIFT,        XK_j,          resizestep,        {.i=TWOBWM_RESIZE_DOWN}},
    {  MOD |SHIFT,        XK_l,          resizestep,        {.i=TWOBWM_RESIZE_RIGHT}},
    {  MOD |SHIFT,        XK_h,          resizestep,        {.i=TWOBWM_RESIZE_LEFT}},
    // Resize a window slower
    {  MOD |SHIFT|CONTROL,XK_k,          resizestep,        {.i=TWOBWM_RESIZE_UP_SLOW}},
    {  MOD |SHIFT|CONTROL,XK_j,          resizestep,        {.i=TWOBWM_RESIZE_DOWN_SLOW}},
    {  MOD |SHIFT|CONTROL,XK_l,          resizestep,        {.i=TWOBWM_RESIZE_RIGHT_SLOW}},
    {  MOD |SHIFT|CONTROL,XK_h,          resizestep,        {.i=TWOBWM_RESIZE_LEFT_SLOW}},
    // Move a window
    {  MOD ,              XK_k,          movestep,          {.i=TWOBWM_MOVE_UP}},
    {  MOD ,              XK_j,          movestep,          {.i=TWOBWM_MOVE_DOWN}},
    {  MOD ,              XK_l,          movestep,          {.i=TWOBWM_MOVE_RIGHT}},
    {  MOD ,              XK_h,          movestep,          {.i=TWOBWM_MOVE_LEFT}},
    // Move a window slower
    {  MOD |CONTROL,      XK_k,          movestep,          {.i=TWOBWM_MOVE_UP_SLOW}},
    {  MOD |CONTROL,      XK_j,          movestep,          {.i=TWOBWM_MOVE_DOWN_SLOW}},
    {  MOD |CONTROL,      XK_l,          movestep,          {.i=TWOBWM_MOVE_RIGHT_SLOW}},
    {  MOD |CONTROL,      XK_h,          movestep,          {.i=TWOBWM_MOVE_LEFT_SLOW}},
    // Teleport the window to an area of the screen.
    // Center:
    {  MOD ,              XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER}},
    // Center y:
    {  MOD |SHIFT,        XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_Y}},
    // Center x:
    {  MOD |CONTROL,      XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_X}},
    // Top left:
    {  MOD ,              XK_y,          teleport,          {.i=TWOBWM_TELEPORT_TOP_LEFT}},
    // Top right:
    {  MOD ,              XK_u,          teleport,          {.i=TWOBWM_TELEPORT_TOP_RIGHT}},
    // Bottom left:
    {  MOD ,              XK_b,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_LEFT}},
    // Bottom right:
    {  MOD ,              XK_n,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_RIGHT}},
    // Resize while keeping the window aspect
    {  MOD ,              XK_Home,       resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_GROW}},
    {  MOD ,              XK_End,        resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_SHRINK}},
    // Full screen window without borders
    {  MOD ,              XK_f,          maximize,          {.i=TWOBWM_FULLSCREEN_OVERRIDE_OFFSETS}},
    //Full screen window without borders overiding offsets
    {  MOD |SHIFT ,       XK_f,          maximize,          {.i=TWOBWM_FULLSCREEN}},
    // Maximize vertically
    {  MOD ,              XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_VERTICALLY}},
    // Maximize horizontally
    {  MOD |SHIFT,        XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_HORIZONTALLY}},
    // Maximize and move
    // vertically left
    {  MOD |SHIFT,        XK_y,          maxhalf,           {.i=TWOBWM_MAXHALF_VERTICAL_LEFT}},
    // vertically right
    {  MOD |SHIFT,        XK_u,          maxhalf,           {.i=TWOBWM_MAXHALF_VERTICAL_RIGHT}},
    // horizontally left
    {  MOD |SHIFT,        XK_b,          maxhalf,           {.i=TWOBWM_MAXHALF_HORIZONTAL_BOTTOM}},
    // horizontally right
    {  MOD |SHIFT,        XK_n,          maxhalf,           {.i=TWOBWM_MAXHALF_HORIZONTAL_TOP}},
    //fold half vertically
    {  MOD |SHIFT|CONTROL,XK_y,          maxhalf,           {.i=TWOBWM_MAXHALF_FOLD_VERTICAL}},
    //fold half horizontally
    {  MOD |SHIFT|CONTROL,XK_b,          maxhalf,           {.i=TWOBWM_MAXHALF_FOLD_HORIZONTAL}},
    //unfold vertically
    {  MOD |SHIFT|CONTROL,XK_u,          maxhalf,           {.i=TWOBWM_MAXHALF_UNFOLD_VERTICAL}},
    //unfold horizontally
    {  MOD |SHIFT|CONTROL,XK_n,          maxhalf,           {.i=TWOBWM_MAXHALF_UNFOLD_HORIZONTAL}},
    // Next/Previous screen
//    {  MOD ,              XK_comma,      changescreen,      {.i=TWOBWM_NEXT_SCREEN}},
//    {  MOD ,              XK_period,     changescreen,      {.i=TWOBWM_PREVIOUS_SCREEN}},
    // Raise or lower a window
    {  MOD ,              XK_r,          raiseorlower,      {}},
    // Next/Previous workspace
    {  MOD ,              XK_period,     nextworkspace,     {}},
    {  MOD ,              XK_comma,      prevworkspace,     {}},
    // Move to Next/Previous workspace
    {  MOD |SHIFT ,       XK_period,     sendtonextworkspace,{}},
    {  MOD |SHIFT ,       XK_comma,      sendtoprevworkspace,{}},
        // Make the window unkillable
    {  MOD ,              XK_a,          unkillable,        {}},
    // Make the window appear always on top
    {  MOD,               XK_t,          always_on_top,     {}},
    // Make the window stay on all workspaces
    {  MOD ,              XK_x,          fix,               {}},
    // Start programs
    {  MOD ,              XK_Return,     start,             {.com = termcmd}},
    // Exit or restart 2bwm
    {  MOD |CONTROL,      XK_q,          twobwm_exit,       {.i=0}},
    {  MOD |CONTROL,      XK_r,          twobwm_restart,    {.i=0}},
    {  MOD ,              XK_space,      halfandcentered,   {.i=0}},
    // Change current workspace
       DESKTOPCHANGE(     XK_1,                             0)
       DESKTOPCHANGE(     XK_2,                             1)
       DESKTOPCHANGE(     XK_3,                             2)
       DESKTOPCHANGE(     XK_4,                             3)
       DESKTOPCHANGE(     XK_5,                             4)
       DESKTOPCHANGE(     XK_6,                             5)
       DESKTOPCHANGE(     XK_7,                             6)
};
// the last argument makes it a root window only event
static Button buttons[] = {
    {  MOD        ,XCB_BUTTON_INDEX_1,     mousemotion,   {.i=TWOBWM_MOVE}, false},
    {  MOD        ,XCB_BUTTON_INDEX_3,     mousemotion,   {.i=TWOBWM_RESIZE}, false},
    {  0          ,XCB_BUTTON_INDEX_3,     start,         {.com = menucmd}, true},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace, {.i=0}, false},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace, {.i=1}, false},
    {  MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,    {.i=1}, false},
    {  MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,    {.i=0}, false}
};
