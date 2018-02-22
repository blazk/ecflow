#!/usr/bin/env python2.7
import os
import ecflow  

def create_family_f1():
    f1 = ecflow.Family("f1")
    f1.add_variable("SLEEP", 20)
    f1.add_task("t1").add_meter("progress", 1, 100, 90)
    
    t2 = f1.add_task("t2")  
    t2.add_trigger("t1 eq complete") 
    t2.add_event("a")
    t2.add_event("b")
    
    f1.add_task("t3").add_trigger("t2:a")  
    
    t4 = f1.add_task("t4")
    t4.add_trigger("t2 eq complete")  
    t4.add_complete("t2:b") 
     
    f1.add_task("t5").add_trigger("t1:progress ge 30")  
    f1.add_task("t6").add_trigger("t1:progress ge 60")  
    f1.add_task("t7").add_trigger("t1:progress ge 90") 
    return f1 
   
print "Creating suite definition"   
defs = ecflow.Defs()
suite = defs.add_suite("test")
suite.add_variable("ECF_INCLUDE", os.getenv("HOME") + "/course")
suite.add_variable("ECF_HOME",    os.getenv("HOME") + "/course")

suite.add_family( create_family_f1() )
print defs

print "Checking job creation: .ecf -> .job0"   
print defs.check_job_creation()

print "Checking trigger expressions"
print defs.check()

print "Saving definition to file 'test.def'"
defs.save_as_defs("test.def")