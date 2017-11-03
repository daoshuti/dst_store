import pyhk
 
def fun():
    print "Do something"
    exit()
 
#create pyhk class instance
hot = pyhk.pyhk()
 
#add hotkey
hot.addHotkey(['Ctrl', 'Alt','7'],fun)
 
#start looking for hotkey.
hot.start()
