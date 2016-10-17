(char*) " !=========================================================== ",
(char*) " ! Name : ",
(char*) " ! Author : ",
(char*) " ! Revision : $Revision: #26 $ ",
(char*) " ! ",
(char*) " ! Copyright 2009-2016 ECMWF. ",
(char*) " ! This software is licensed under the terms of the Apache Licence version 2.0 ",
(char*) " ! which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. ",
(char*) " ! In applying this licence, ECMWF does not waive the privileges and immunities ",
(char*) " ! granted to it by virtue of its status as an intergovernmental organisation ",
(char*) " ! nor does it submit to any jurisdiction. ",
(char*) " ! ",
(char*) " ! Description : ",
(char*) " ! this file may be found in ",
(char*) " ! - ecflowview sources in order to generate ecflowview.menu.h ",
(char*) " ! - ~/.ecflowrc/ecflowview.menu # edit backup remove (reset) ",
(char*) " ! - ~/ is preferred to $HOME ",
(char*) " ! - menus can call ecflow client command (start with 'ecflow_client') ",
(char*) " ! - menus can call system command (start with sh) ",
(char*) " !=========================================================== ",
(char*) " ! ",
(char*) " ! Format ",
(char*) " !------- ",
(char*) " ! menu TITLE ",
(char*) " ! { ",
(char*) " ! (vis flg,enable flg,title,command,question,answer) ",
(char*) " ! } ",
(char*) " ! ",
(char*) " !=========================================================== ",
(char*) " ! ",
(char*) " ! Values for the status flags ",
(char*) " !---------------------------- ",
(char*) " ! ",
(char*) " !NONE ALL UNKNOWN SUSPENDED COMPLETE QUEUED SUBMITTED ACTIVE ",
(char*) " !ABORTED CLEAR SET SHUTDOWN HALTED ",
(char*) " ! ",
(char*) " ! Values for type flags ",
(char*) " !---------------------- ",
(char*) " ! ",
(char*) " !NONE ALL SERVER SUITE FAMILY TASK EVENT ",
(char*) " ! ",
(char*) " ! Values for visible flags ",
(char*) " !------------------------- ",
(char*) " ! ",
(char*) " !NONE ALL SERVER SUITE FAMILY TASK EVENT ",
(char*) " ! ",
(char*) " ! Values for special flags ",
(char*) " !------------------------- ",
(char*) " ! ",
(char*) " !NONE ALL HAS_TRIGGERS HAS_TIME HAS_DATE ",
(char*) " ! ",
(char*) " !=========================================================== ",
(char*) "  ",
(char*) " !============================================================================== ",
(char*) " ! Main menu ",
(char*) " !============================================================================== ",
(char*) "  ",
(char*) " version 1 0 0 ; ",
(char*) "  ",
(char*) " menu 'MAIN' ",
(char*) " { ",
(char*) " (~SUSPENDED & NODE, ALL, 'Suspend', 'ecflow_client --suspend <full_name>') ",
(char*) " (SUSPENDED & NODE, ALL, 'Resume', 'ecflow_client --resume <full_name>') ",
(char*) "  ",
(char*) " ( TASK, ~ACTIVE & ~SUBMITTED, 'Rerun', 'ecflow_client --force queued <full_name>') ",
(char*) "  ",
(char*) " (TASK | ALIAS, ALL, 'Set', MENU) ",
(char*) "  ",
(char*) " (TASK|ALIAS, ~ACTIVE & ~SUBMITTED, 'Execute', 'ecflow_client --run <full_name>') ",
(char*) "  ",
(char*) " (SUITE|TASK|FAMILY, ~ACTIVE & ~SUBMITTED, 'Requeue', ",
(char*) " 'ecflow_client --requeue force <full_name>', ",
(char*) " 'Confirm requeuing of <full_name>', YES) ",
(char*) "  ",
(char*) " (SUITE|FAMILY, ABORTED | SUSPENDED, 'Requeue aborted', ",
(char*) " 'ecflow_client --requeue abort <full_name>', ",
(char*) " 'Confirm requeuing of aborted tasks from <full_name>', YES) ",
(char*) "  ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) "  ",
(char*) " (SUITE|TASK|FAMILY,(QUEUED|SUSPENDED|ACTIVE) & (HAS_TRIGGERS|HAS_TIME|HAS_DATE),'Delete',MENU) ",
(char*) " (NODE | ALIAS, ALL, 'Special', MENU) ",
(char*) " (NODE | ALIAS, ALL, 'Defstatus', MENU) ",
(char*) " (NODE & ADMIN, ALL, 'Force', MENU) ",
(char*) " ((NODE|ALIAS)& ADMIN, ALL,'Order', MENU) ",
(char*) "  ",
(char*) " (ALL,ALL,'-',SEPARATOR ,'',YES) ",
(char*) " (SUITE|FAMILY, ALL, 'Web...', 'ecflow_client --url <full_name> ', '', YES) ",
(char*) " (TASK, ALL, 'Web', MENU) ",
(char*) "  ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) "  ",
(char*) " (SUITE & (OPER|ADMIN) ,UNKNOWN|COMPLETE,'Begin', ",
(char*) " 'ecflow_client --begin <node_name>','',YES) ",
(char*) "  ",
(char*) " (SUITE & (OPER|ADMIN) ,~SUBMITTED & ~ACTIVE,'Cancel', ",
(char*) " 'ecflow_client --delete yes <full_name>', ",
(char*) " 'Do you really want to cancel suite <full_name> ?',NO) ",
(char*) "  ",
(char*) " ! Events ",
(char*) " !--------------------------------- ",
(char*) "  ",
(char*) " (EVENT, CLEAR, 'Set' , ",
(char*) " 'ecflow_client --alter change event <node_name> set <parent_name>', '',YES) ",
(char*) " (EVENT, SET, 'Clear', ",
(char*) " 'ecflow_client --alter change event <node_name> clear <parent_name>', '',YES) ",
(char*) "  ",
(char*) " !!----------------------------------- ",
(char*) "  ",
(char*) " (SERVER & (ADMIN|OPER) & LOCKED , ALL , 'Unlock', 'unlock -y', ",
(char*) " 'Before going further, please check why the server was locked.',NO) ",
(char*) " (ALL,ALL,'-',SEPARATOR,'',YES) ",
(char*) "  ",
(char*) " !!----------------------------------- ",
(char*) "  ",
(char*) " (SERVER,SHUTDOWN|HALTED, 'Restart', ",
(char*) " 'ecflow_client --restart yes','Restart the server in <node_name>?' ,NO) ",
(char*) " (SERVER,~SHUTDOWN, 'Shutdown', ",
(char*) " 'ecflow_client --shutdown yes','Shutdown the server in <node_name>?',NO) ",
(char*) " (SERVER,~HALTED, 'Halt', ",
(char*) " 'ecflow_client --halt yes','Halt the server in <node_name>?',NO) ",
(char*) " (SERVER,HALTED|UNKNOWN, 'Terminate', ",
(char*) " 'ecflow_client --terminate yes','Terminate the server in <node_name>?',NO) ",
(char*) " (ALL,ALL,'-',SEPARATOR,'',YES) ",
(char*) " (SERVER,ALL, 'Checkpoint','ecflow_client --check_pt','',YES) ",
(char*) " (SERVER,HALTED, 'Recover', ",
(char*) " 'ecflow_client --restore_from_checkpt','Recover the server in <node_name>?',NO) ",
(char*) "  ",
(char*) " !!----------------------------------- ",
(char*) "  ",
(char*) " (LIMIT , ALL, 'Reset' , ",
(char*) " 'ecflow_client --alter change limit_value <node_name> 0 <parent_name>', ",
(char*) " 'Confirm resetting <full_name>', YES) ",
(char*) " (ALIAS , ALL, 'Remove', 'ecflow_client --delete yes <full_name>', ",
(char*) " 'Confirm remove alias <full_name>', YES) ",
(char*) "  ",
(char*) " !!----------------------------------- ",
(char*) "  ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) "  ",
(char*) " (TASK|LIMIT|LABEL|METER|REPEAT|VARIABLE, ALL , 'Edit...', WINDOW(Edit)) ",
(char*) " (TASK|ALIAS, ALL , 'Output...', WINDOW(Output) ) ",
(char*) "  ",
(char*) " (TASK|ALIAS, SUBMITTED|ACTIVE , 'Status...', WINDOW(Jobstatus)) ",
(char*) " (ALIAS, ALL , 'Job...', WINDOW(Job) ) ",
(char*) " (TASK|ALIAS, ALL , 'Script...', WINDOW(Script) ) ",
(char*) "  ",
(char*) " (SERVER, ALL , 'Suites...', WINDOW(Suites) ) ",
(char*) " (SERVER, ALL , 'History...', WINDOW(History) ) ",
(char*) " (SERVER, ALL , 'Zombies...', WINDOW(Zombies) ) ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER, ALL , 'Options...', WINDOW(Options) ) ",
(char*) " (SERVER, ALL , 'Extra', MENU ) ",
(char*) " (SERVER, ALL , 'Ping', 'sh ecflow_client --port %ECF_PORT% --host %ECF_NODE% --ping' ) ",
(char*) " (SERVER, ALL , 'Stat', 'sh ecflow_client --port %ECF_PORT% --host %ECF_NODE% --stats' ) ",
(char*) " } ",
(char*) "  ",
(char*) " menu 'Set' ",
(char*) " { ",
(char*) " (TASK|ALIAS, SUBMITTED|ACTIVE, 'Set complete', ",
(char*) " 'ecflow_client --force complete <full_name>', ",
(char*) " 'Have you checked that the job is not active anymore (jobstatus) ?', YES) ",
(char*) " (TASK|ALIAS, UNKNOWN|QUEUED|ABORTED, 'Set complete', ",
(char*) " 'ecflow_client --force complete <full_name>') ",
(char*) " (TASK|ALIAS, SUBMITTED|ACTIVE, 'Set aborted', ",
(char*) " 'ecflow_client --force aborted <full_name>', ",
(char*) " 'Have you checked that the job is not active anymore (jobstatus) ?', YES) ",
(char*) " (TASK|ALIAS, UNKNOWN|QUEUED|COMPLETE, 'Set aborted', ",
(char*) " 'ecflow_client --force aborted <full_name>') ",
(char*) " } ",
(char*) "  ",
(char*) " menu 'Web' ",
(char*) " { ",
(char*) " ! (TASK, ALL, 'Web...', 'ecflow_client --url <full_name> ', '', YES) ",
(char*) " (NODE, ALL , 'WebM', MENU ) ",
(char*) " (NODE, ALL , 'WebW', MENU ) ",
(char*) " } ",
(char*) "  ",
(char*) " menu 'WebM' ",
(char*) " { ",
(char*) " (TASK, ALL, 'Web...', 'ecflow_client --url <full_name> ', '', YES) ",
(char*) " (TASK, ALL, 'Man', 'sh firefox %ECF_URL_BASE%/%ECF_URL%', '', YES) ",
(char*) " (TASK, ALL, 'Script', 'sh xterm -T Script -e vim %ECF_SCRIPT%', '', YES) ",
(char*) " (TASK, ALL, 'Job', 'sh xterm -T Job -e vim %ECF_JOB%', '', YES) ",
(char*) " (TASK, ALL, 'Output', 'sh xterm -T Output -e vim %ECF_JOBOUT%', '', YES) ",
(char*) " (TASK, ALL , 'TimeLine...', WINDOW(Timeline)) ",
(char*) " ! request from Lidström Jonas https://software.ecmwf.int/issues/browse/SUP-829 ",
(char*) " (TASK, ALL, 'Details', 'sh xterm -T Details-%ECF_NAME% -e \"grep %ECF_NAME% %ECF_LOG% ; read\"') ",
(char*) " } ",
(char*) "  ",
(char*) " menu 'WebW' ",
(char*) " { ",
(char*) " (TASK, ALL, 'WMan', 'sh firefox ${ECFLOW_WEB:-http://eurus.ecmwf.int:8000/api/v1/ecflow}/%ECF_NODE:%/%ECF_PORT:%/man/%ECF_NAME:%', '', YES) ",
(char*) " (TASK, ALL, 'WScript', 'sh firefox ${ECFLOW_WEB:-http://eurus.ecmwf.int:8000/api/v1/ecflow}/%ECF_NODE:%/%ECF_PORT:%/script/%ECF_NAME:%', '', YES) ",
(char*) " (TASK, ALL, 'WJob', 'sh firefox ${ECFLOW_WEB:-http://eurus.ecmwf.int:8000/api/v1/ecflow}/%ECF_NODE:%/%ECF_PORT:%/job/%ECF_NAME:%', '', YES) ",
(char*) " (TASK, ALL, 'WOut', 'sh firefox ${ECFLOW_WEB:-http://eurus.ecmwf.int:8000/api/v1/ecflow}/%ECF_NODE:%/%ECF_PORT:%/output/%ECF_NAME:%', '', YES) ",
(char*) " (TASK, ALL, 'Suites', 'sh firefox ${ECFLOW_WEB:-http://eurus.ecmwf.int:8000/api/v1/ecflow}/%ECF_NODE:%/%ECF_PORT:%/suites', '', YES) ",
(char*) " (TASK, ALL, 'Treemap', 'sh firefox ${ECFLOW_WEB:-http://eurus.ecmwf.int:8000/api/v1/ecflow}/%ECF_NODE:%/%ECF_PORT:%/suite/treemap/SAR/none/7/%SUITE:%', '', YES) ",
(char*) " (TASK, ALL, 'Flask', 'sh firefox ${ECFLOW_WEB_MONITOR:-http://eurus.ecmwf.int:5001}', '', YES) ",
(char*) " } ",
(char*) "  ",
(char*) " !============================================================================== ",
(char*) " ! Status submenu ",
(char*) " !============================================================================== ",
(char*) "  ",
(char*) " menu 'Status' ",
(char*) " { ",
(char*) " (SUITE|TASK|FAMILY, ~SUSPENDED,'Suspend', 'ecflow_client --suspend <full_name>', '',YES) ",
(char*) " (SUITE|TASK|FAMILY, SUSPENDED ,'Resume', 'ecflow_client --resume <full_name>', '',YES) ",
(char*) "  ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) "  ",
(char*) " (TASK, ~ACTIVE & ~SUBMITTED, 'Rerun', 'ecflow_client --force queued <full_name>', '',YES) ",
(char*) " (TASK, ~COMPLETE, 'Set complete', 'ecflow_client --force complete <full_name>', '',YES) ",
(char*) "  ",
(char*) " (SUITE|TASK|FAMILY|ALIAS, ~ACTIVE & ~SUBMITTED, ",
(char*) " 'Requeue','ecflow_client --requeue force <full_name>', 'Confirm requeuing of <full_name>', YES) ",
(char*) "  ",
(char*) " (SUITE|FAMILY, ABORTED | SUSPENDED, ",
(char*) " 'Requeue aborted','ecflow_client --requeue abort <full_name>', ",
(char*) " 'Confirm requeuing aborted tasks below <full_name>', YES) ",
(char*) " } ",
(char*) "  ",
(char*) " !============================================================================== ",
(char*) " ! Suite submenu ",
(char*) " !============================================================================== ",
(char*) "  ",
(char*) " menu 'Suite' ",
(char*) " { ",
(char*) " (SUITE,UNKNOWN|COMPLETE,'Begin','ecflow_client --begin <node_name>','',YES) ",
(char*) "  ",
(char*) " (SUITE,ALL,'Cancel','ecflow_client --delete yes <full_name>', ",
(char*) " 'Do you really want to cancel <full_name> ?',NO) ",
(char*) "  ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " } ",
(char*) "  ",
(char*) " !============================================================================== ",
(char*) " ! Delete submenu ",
(char*) " !============================================================================== ",
(char*) "  ",
(char*) " menu 'Delete' ",
(char*) " { ",
(char*) " (ALL,HAS_TRIGGERS|HAS_TIME|HAS_DATE, 'All dependencies','ecflow_client --free-dep all <full_name>') ",
(char*) " (ALL,HAS_TRIGGERS, 'Trigger dependencies','ecflow_client --free-dep trigger <full_name>') ",
(char*) " (ALL,HAS_TIME, 'Time dependencies','ecflow_client --free-dep time <full_name>') ",
(char*) " (ALL,QUEUED, 'Date dependencies','ecflow_client --free-dep date <full_name>') ",
(char*) " } ",
(char*) "  ",
(char*) " menu \"Order\" ",
(char*) " { ",
(char*) " (ALL,ALL,'Top','ecflow_client --order <full_name> top') ",
(char*) " (ALL,ALL,'Up','ecflow_client --order <full_name> up') ",
(char*) " (ALL,ALL,'Down','ecflow_client --order <full_name> down') ",
(char*) " (ALL,ALL,'Bottom','ecflow_client --order <full_name> bottom') ",
(char*) " (ALL,ALL,'Alphabetically','ecflow_client --order <full_name> alpha') ",
(char*) " } ",
(char*) "  ",
(char*) " menu \"Force\" ",
(char*) " { ",
(char*) " (NODE, ~UNKNOWN, 'Unknown', 'ecflow_client --force unknown recursive <full_name>') ",
(char*) " (NODE, ~COMPLETE & ~ACTIVE & ~SUBMITTED, 'Complete', ",
(char*) " 'ecflow_client --force complete recursive <full_name>', ",
(char*) " 'Check running/queued jobs and Confirm force complete of <full_name>', YES) ",
(char*) " (NODE, ~QUEUED & ~ACTIVE & ~SUBMITTED, 'Queued', ",
(char*) " 'ecflow_client --force queued recursive <full_name>') ",
(char*) " (NODE, ~SUBMITTED & ~ACTIVE,'Submitted', ",
(char*) " 'ecflow_client --force submitted recursive <full_name>') ",
(char*) " (NODE, ~ACTIVE, 'Active', 'ecflow_client --force active recursive <full_name>') ",
(char*) " (NODE, ~ABORTED, 'Aborted', 'ecflow_client --force aborted recursive <full_name>', ",
(char*) " 'Check running/queued jobs and Confirm force submitted of <full_name>', YES) ",
(char*) " } ",
(char*) "  ",
(char*) " menu \"Defstatus\" ",
(char*) " { ",
(char*) " (NODE, ALL, 'Complete', 'ecflow_client --alter change defstatus complete <full_name>') ",
(char*) " (NODE, ALL, 'Queued', 'ecflow_client --alter change defstatus queued <full_name>') ",
(char*) " } ",
(char*) "  ",
(char*) " menu \"Special\" ",
(char*) " { ",
(char*) " ! ( (SUITE|FAMILY) & (COMPLETE|QUEUED|SUSPENDED) & ~MIGRATED,ALL,'Migrate', 'ecflow_client --migrate <full_name>','',NO) ",
(char*) " ! ( (SUITE|FAMILY) & MIGRATED,ALL,'Restore','ecflow_client --restore <full_name>','',YES) ",
(char*) "  ",
(char*) " ( (SUITE|FAMILY) & (COMPLETE|QUEUED|SUSPENDED) & ~MIGRATED,ALL,'Migrate', 'ecflow_client --alter set_flag migrated <full_name>') ",
(char*) " ( (SUITE|FAMILY) & MIGRATED,ALL,'Restore','ecflow_client --alter clear_flag migrated <full_name>', 'click shift-update to display content below', YES) ",
(char*) "  ",
(char*) " (SUITE|FAMILY,(ACTIVE|SUBMITTED|ABORTED),'Kill', 'ecflow_client --kill <full_name>','',YES) ",
(char*) " (TASK|ALIAS,(ACTIVE|SUBMITTED),'Kill','ecflow_client --kill <full_name>','',YES) ",
(char*) " (ALL,ALL,'CheckCmd',WINDOW(Check),'',YES) ",
(char*) " (ALL,ALL,'CheckT','sh xterm -hold -e ecflow_client --port %ECF_PORT% --host %ECF_NODE% --check /%SUITE%/%FAMILY:%%TASK:%') ",
(char*) "  ",
(char*) " (TASK|ALIAS,ALL,'Free password','ecflow_client --alter add variable ECF_PASS FREE <full_name>') ",
(char*) " (TASK|ALIAS,ALL,'ClearZ','ecflow_client --alter clear_flag zombie <full_name>') ",
(char*) " (TASK|ALIAS,ALL,'ClearLate','ecflow_client --alter clear_flag late <full_name>') ",
(char*) " (TASK|ALIAS,ALL,'ClearKill','ecflow_client --alter clear_flag killed <full_name>') ",
(char*) "  ",
(char*) " (FAMILY, ~ACTIVE & ~SUBMITTED, 'Execute', 'ecflow_client --run <full_name>') ",
(char*) " ((SUITE|FAMILY|TASK), SELECTION, 'Plug into selected node', PLUG) ",
(char*) " (FAMILY|TASK,ALL,'get','ecflow_client --get <full_name>') ",
(char*) " (TASK,ALL,'status','ecflow_client --status <full_name>') ",
(char*) " (SUITE|SERVER, ALL, 'Collect...', WINDOW(Collector)) ",
(char*) " (SUITE|FAMILY, ALL, 'Walk', 'ecflow_client --force-dep-eval <full_name>') ",
(char*) " } ",
(char*) "  ",
(char*) " menu \"Extra\" ",
(char*) " { ",
(char*) " (SERVER|SUITE,ALL,'Windows', MENU) ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER,ALL,'ClearLate','ecflow_client --alter clear_flag late <full_name>') ",
(char*) " ! (SERVER|SUITE,ALL,'tail log', 'sh /usr/bin/xterm -e rsh %ECF_NODE% tail -f %ECF_HOME%/%ECF_LOG%&') ",
(char*) " (SERVER|SUITE,ALL,'tail log', 'sh /usr/bin/xterm -e tail -f /tmp/$USER/$HOST*.ecf.log&') ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER|SUITE,ALL,'svr load','ecflow_load.sh -h %ECF_HOME% -l %ECF_LOG% -n %ECF_NODE% -p %ECF_PORT%') ",
(char*) " ! (SERVER|SUITE,ALL,'svr load','ecflow_client --server_load') ",
(char*) " ! (SERVER|SUITE,ALL,'svr load log','ecflow_client --server_load %ECF_LOG%') ",
(char*) " ! (SERVER|SUITE,ALL,'svr load home/log','ecflow_client --server_load %ECF_HOME%/%ECF_LOG%') ",
(char*) " ! (SERVER|SUITE,ALL,'show png','sh ${EOG:-eog} %ECF_NODE%.%ECF_PORT%.png') ",
(char*) " ! one menu to replace four previous when it works ",
(char*) " ! (SERVER|SUITE,ALL,'show load','sh ecflow_show_load.sh -n %ECF_NODE% -p %ECF_PORT% -h %ECF_HOME% %ECF_LOG%') ",
(char*) "  ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER|SUITE,ALL,'overwrite', 'write menu') ",
(char*) " (SERVER|SUITE,ALL,'edit menu', 'sh /usr/bin/xterm -e vi ~/.ecflowrc/ecflowview.menu') ",
(char*) " (SERVER|SUITE,ALL,'bkup menu', 'sh /bin/cp ~/.ecflowrc/ecflowview.menu ~/.ecflowrc/ecflowview.menu.bak') ",
(char*) " (SERVER|SUITE,ALL,'rm menu', 'sh /bin/rm ~/.ecflowrc/ecflowview.menu') ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER|SUITE,ALL,'debug on', 'ecflow_client --debug_server_on') ",
(char*) " (SERVER|SUITE,ALL,'debug off','ecflow_client --debug_server_off') ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER|SUITE,ALL,'stats','ecflow_client --stats') ",
(char*) " (SERVER|SUITE,ALL,'suites','ecflow_client --suites') ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER|SUITE,ALL,'log get','ecflow_client --log get') ",
(char*) " (SERVER|SUITE,ALL,'log clear','ecflow_client --log clear') ",
(char*) " (SERVER|SUITE,ALL,'log new','ecflow_client --log new') ",
(char*) " (ALL,ALL,'-',SEPARATOR) ",
(char*) " (SERVER|SUITE,ALL,'client logging on','ecflow_client --enable_logging') ",
(char*) " (SERVER|SUITE,ALL,'client loggging off','ecflow_client --disable_logging') ",
(char*) " } ",
(char*) "  ",
(char*) " menu \"Windows\" ",
(char*) " { ",
(char*) " (SERVER, ALL , 'Info...', WINDOW(Info)) ",
(char*) " (SERVER, ALL , 'Man...', WINDOW(Manual)) ",
(char*) " (SERVER, ALL , 'Var...', WINDOW(Variables)) ",
(char*) " (SERVER, ALL , 'Msg...', WINDOW(Messages)) ",
(char*) " (SERVER, ALL , 'Why...', WINDOW(Why)) ",
(char*) " (SERVER, ALL , 'Triggers...', WINDOW(Triggers)) ",
(char*) " (SERVER, ALL , 'Check...', WINDOW(Check)) ",
(char*) " (SERVER, ALL , 'Jobstatus...', WINDOW(Jobstatus)) ",
(char*) " (SERVER, ALL , 'TimeLine...', WINDOW(Timeline)) ",
(char*) " } ",
(char*) "  ",
(char*) " ! DIRRC=~/.ecflowrc; rm -rf $DIRRC; mkdir $DIRRC ",
(char*) "  ",
(char*) " ! lm=src/ecflowview.menu; um=$HOME/.ecflowrc/ecflowview.menu; rm $um ",
(char*) " ! sh src/menu2c.sh < $lm > ${lm}.h && cp -f $lm $um ",
NULL
