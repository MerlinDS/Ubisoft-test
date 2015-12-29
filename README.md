#Test application for Ubisoft

This is a simple console application. 
Stimulates behavior of free falling body, without air resistance.
Used WinAPI for showing of a simulation result.
 
After input of user command, app will open two separated thread:

    * For simulation calculations.
    * For result drawing.
    
Application will create log file with debug information.

[Component/Entity System](http://entity-systems.wikidot.com/) is a base concept of application structure.
But for this test, parameters saves directly into entities, not into components. 

##Launch arguments

* `-w` - width of window *(default:960)*
* `-h` - height of window *(default:640)*
* `-s` - scaling. pixel * scaling = meter *(default:20)*

*Example:*

` \ ubi_soft_test.exe -w 1024 -h 786 -s 30`

**Window with simulation drawing will be opened only after `create` command execution!**

##Commands:

* `help` - show help information in console
* `exit` - terminate simulation, close opened window (if it exists), close application.
* `create` - Creates entity for simulation with provided parameters.
             Opens new window for drawing, if it does not exist. Starts simulation, if it was not started yet.
     * `-v` - initial velocity
     * `-a` - initial angle
     * `-m` - mass
 

