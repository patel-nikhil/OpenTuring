/****************/
/* edcommands.h */
/****************/

// File menu
// Note the new base starts at 3001.  Don't set any commands from 4000-4100
#define COMMAND_NEW_BASE		4000
#define COMMAND_LAST_NEW_COMMAND	4099
#define COMMAND_NEW_UNNAMED		1001
#define COMMAND_OPEN_FILE		1002
// Note the command base starts at 4101.  Don't set any commands from 4100-4200
#define COMMAND_RECENT_BASE		4100
#define COMMAND_LAST_RECENT_COMMAND	4199
#define COMMAND_CLOSE_FILE		1004
#define COMMAND_SAVE_FILE		1005
#define COMMAND_SAVEAS_FILE		1006
#define COMMAND_SAVE_SELECTION		1007
#define COMMAND_REVERT_FILE		1008
#define COMMAND_PRINT_FILE		1009
#define COMMAND_PAGE_SETUP		1010
#define COMMAND_FIX_MAIN		1011
#define COMMAND_FLOAT_MAIN		1012
#define COMMAND_REDRAW			1013
#define COMMAND_COPY_EXAMPLES		1014
#define COMMAND_PREFS			1015
#define COMMAND_EXIT			1016
#define COMMAND_EXIT_IMMEDIATE		1017

// Edit menu
#define COMMAND_UNDO			1101
#define COMMAND_REDO			1102
#define COMMAND_CUT			1103
#define COMMAND_COPY			1104
#define COMMAND_PASTE			1105
#define COMMAND_SELECT_ALL		1106
#define COMMAND_COMMENT_RANGE		1107
#define COMMAND_UNCOMMENT_RANGE		1108
#define COMMAND_COMPLETE_STRUCT		1109
#define COMMAND_INSERT_BASE		4200
#define COMMAND_LAST_INSERT_COMMAND	4299
#define COMMAND_INDENT			1110

// Search menu
#define COMMAND_FIND			1201
#define COMMAND_FIND_NEXT		1202
#define COMMAND_FIND_SELECTION		1203
#define COMMAND_REPLACE			1204
#define COMMAND_FIND_NEXT_ERROR		1205
#define COMMAND_FIND_MATCH_BRACE	1206
#define COMMAND_GOTO_LINE		1207
#define COMMAND_FIND_PREV		1210

// Mark menu
// Note the command base starts at 3001.  Don't set any commands from 3000-3999
#define COMMAND_MARK_BASE		3001
#define COMMAND_LAST_MARK_COMMAND	3999

// Run menu
#define COMMAND_RUN			1401
#define COMMAND_RUN_ARGS		1402
// Java specific
#define COMMAND_COMPILE			1403
#define COMMAND_STOP			1404
#define COMMAND_SUBMIT			1405
#define COMMAND_PAUSERESUME		1406
// Turing specific
#define COMMAND_COMPILER_RESET		1407
#define COMMAND_CREATE_EXE		1408
#define COMMAND_CLOSE_ALL_RUN_WIN	1409
#define COMMAND_SHOW_HIDE_DEBUG_MENU	1410

// Debugger menu
#define COMMAND_DEBUG_SHOW_HIDE_CONTROLS	1501
#define COMMAND_DEBUG_SHOW_BREAKPOINTS		1502
#define COMMAND_DEBUG_CLEAR_BREAKPOINTS		1503
#define COMMAND_DEBUG_SHOW_UNIT_LIST		1504
#define COMMAND_DEBUG_SHOW_PROCESSES		1505
#define COMMAND_DEBUG_SHOW_QUEUES		1506
#define COMMAND_DEBUG_SHOW_ALLOCATED_OBJECTS	1507
#define COMMAND_DEBUG_SHOW_EXECUTION_LINE	1508
#define COMMAND_DEBUG_SHOW_DEFINITION		1509
#define COMMAND_DEBUG_STEP			1510
#define COMMAND_DEBUG_STEP_OVER			1511
#define COMMAND_DEBUG_STEP_RETURN		1512
#define COMMAND_DEBUG_TRACE			1513
#define COMMAND_DEBUG_SHOWVARS			1514
#define COMMAND_DEBUG_STREAM_0_TO_STDERR	1515
#define COMMAND_DEBUG_ERRORS_TO_STDERR		1516
#define COMMAND_DEBUG_LIB_INFO_TO_STDERR	1517

// Window menu


// Help menu
// Java specific
#define COMMAND_HELP_EDITOR		1701
#define COMMAND_HELP_LANG		1702
#define COMMAND_HELP_CLASSLIB		1703
#define COMMAND_ABOUT			1704
#define COMMAND_HELP_READY_HOME		1710
#define COMMAND_HELP_READY_SUPPORT	1711
#define COMMAND_HELP_READY_TEXTBOOKS	1712
#define COMMAND_HELP_READY_RESOURCES	1713
#define COMMAND_HELP_JAVA_HELP		1714
#define COMMAND_HELP_HSA_HOME		1715
#define COMMAND_HELP_READY_OBTAIN	1716
#define COMMAND_HELP_IBM_ACAD		1721
#define COMMAND_HELP_IBM_HOME		1722
#define COMMAND_HELP_TURING_HOME	1723
#define COMMAND_HELP_TURING_SUPPORT	1724
#define COMMAND_HELP_TURING_UPDATE	1725
#define COMMAND_HELP_TURING_TEXTBOOKS	1726
#define COMMAND_HELP_TURING_RESOURCES	1727
#define COMMAND_HELP_TURING_HELP	1728
#define COMMAND_HELP_TURING_OBTAIN	1729
#define COMMAND_HELP_TURING_REF		1730
#define COMMAND_KEYWORD_PROTO		1731
#define COMMAND_KEYWORD_REF		1732

// Keystrokes
#define COMMAND_DEL_EOL			1801
#define COMMAND_JOIN			1802
#define COMMAND_DEL_LINE		1803
#define COMMAND_DEL			1804
#define COMMAND_BACKTAB			1805
#define COMMAND_SHOW_LINENO		1806

// Caret movement
#define COMMAND_MOVE_COLUMN_LEFT	1901
#define COMMAND_MOVE_COLUMN_RIGHT	1902
#define COMMAND_MOVE_LINE_UP		1903
#define COMMAND_MOVE_LINE_DOWN		1904
#define COMMAND_MOVE_LINE_BEGIN		1905
#define COMMAND_MOVE_LINE_END		1906
#define COMMAND_MOVE_WORD_PREV		1907
#define COMMAND_MOVE_WORD_NEXT		1908
#define COMMAND_MOVE_PAGE_HALF_UP	1909
#define COMMAND_MOVE_PAGE_HALF_DOWN	1910
#define COMMAND_MOVE_PAGE_UP		1911
#define COMMAND_MOVE_PAGE_DOWN		1912
#define COMMAND_MOVE_PROGRAM_TOP	1913
#define COMMAND_MOVE_PROGRAM_BOTTOM	1914

// Selection caret movement
#define COMMAND_SELECT_COLUMN_LEFT	2001
#define COMMAND_SELECT_COLUMN_RIGHT	2002
#define COMMAND_SELECT_LINE_UP		2003
#define COMMAND_SELECT_LINE_DOWN	2004
#define COMMAND_SELECT_LINE_BEGIN	2005
#define COMMAND_SELECT_LINE_END		2006
#define COMMAND_SELECT_WORD_PREV	2007
#define COMMAND_SELECT_WORD_NEXT	2008
#define COMMAND_SELECT_PAGE_HALF_UP	2009
#define COMMAND_SELECT_PAGE_HALF_DOWN	2010
#define COMMAND_SELECT_PAGE_UP		2011
#define COMMAND_SELECT_PAGE_DOWN	2012
#define COMMAND_SELECT_PROGRAM_TOP	2013
#define COMMAND_SELECT_PROGRAM_BOTTOM	2014

// Command used only in the Replace dialog shortcuts
#define COMMAND_CLOSE_DIALOG		5000

// Used to get a crash for testing purpose
#define COMMAND_CRASH_ENVIRONMENT	6000

// Used to get an assertion failure for testing purposes
#define COMMAND_CAUSE_ASSERT_FAIL	6001

// Debug keystroke
#define COMMAND_DUMP_MEMORY		6002

// Command used to create RTF		
#define COMMAND_SAVE_TO_RTF		6003



#define MDI_WINDOW_BASE			7001

// Note the command base starts at 2001.  Don't set any commands from 2000-3000
#define COMMAND_FIRST_MOVEMENT_COMMAND	COMMAND_MOVE_COLUMN_LEFT
#define COMMAND_LAST_MOVEMENT_COMMAND	COMMAND_SELECT_PROGRAM_BOTTOM