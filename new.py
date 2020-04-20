import glob
import os
import sys
from os import path
from os.path import expanduser
import platform

# CLion Activator v1.3
# By congard
# Script supports Linux, Windows and Mac OS
# Support me via Payeer: P36281059
# https://github.com/congard
# http://congard.pp.ua/support-me
# mailto:dbcongard@gmail.com
# https://t.me/congard
# If you have an opportunity, PLEASE, buy CLion: https://www.jetbrains.com/clion/buy/


def editIDEFiles():
    # removing evaluation key
    for dirPattern in ["config/eval/CLion*evaluation.key*", "eval/CLion*evaluation.key*"]:
        for keyFile in glob.glob(path.join(clionPath[index], dirPattern)):
            print("Removing " + keyFile)
            os.remove(keyFile)

    # removing line which containing evlsprt
    for filePattern in ["config/options/other.xml", "options/other.xml"]:
        for otherXml in glob.glob(path.join(clionPath[index], filePattern)):
            print("Clearing evlsprt in " + otherXml)

            # reading other.xml
            with open(otherXml, 'r') as file:
                data = file.read()

            # editing
            data = data.split("\n")
            newFile = ''
            for i in range(len(data)):
                if data[i].find("evlsprt") != -1:
                    print("Removing: ", data[i])
                else:
                    newFile += data[i] + "\n"

            # saving edited other.xml
            with open(otherXml, "w") as file:
                file.write(newFile)


home = expanduser("~")

# searching CLion folder
clionPath = []
for dirPattern in [".CLion*", "Library/Preferences/CLion*"]:
    for foundDir in glob.glob(path.join(home, dirPattern)):
        clionPath.append(foundDir)

if len(clionPath) > 0:
    print("Found CLion folders:", *clionPath, ' ')

    index = 0
    if len(clionPath) > 1:
        # you can specify default CLion folder by passing command-line argument - folder index
        if len(sys.argv) > 1:
            index = sys.argv[1]
        else:
            print("Enter folder index (by default 0): ")
            index = input()
            if index == '':
                index = 0
        # convert str to int
        index = int(index)

    print("Using directory: ", clionPath[index])

    editIDEFiles()
else:
    print("CLion directory not found. IDE files will not be edited")

# Removing the following entries for Linux, Windows and Mac OS is different.
# On Linux, they are stored simply in /home, on Windows, in the registry.
# IN WINDOWS YOU SHOULD LAUNCH THIS SCRIPT AS AN ADMINISTRATOR!

print("Editing prefs")

# removing clion userPrefs directory
if os.name == "posix":
    import shutil
    if platform.system() == "Linux":
        clionUserPrefs = path.join(home, ".java/.userPrefs/jetbrains/clion")
        print("Removing " + clionUserPrefs)
        shutil.rmtree(clionUserPrefs)

    elif platform.system() == "Darwin":
        for jbFile in glob.glob(path.join(home, "Library/Preferences/jetbrains*.plist*")):
            print("Removing " + jbFile)
            os.remove(jbFile)

        import plistlib

        with open(path.join(home, "Library/Preferences/com.apple.java.util.prefs.plist"), 'rb') as fp:
            pl = plistlib.load(fp)

        for key in ['JetBrains.UserIdOnMachine', 'jetbrains/']:
            if key in pl['/']:
                print("Removing Java User Pref Key: ", key, "\n")
                del pl['/'][key]

        with open(path.join(home, "Library/Preferences/com.apple.java.util.prefs.plist"), 'wb') as fp:
            plistlib.dump(pl, fp)

# removing registry entries
elif os.name == "nt":
    import winreg

    def deleteSubkey(hkey, key):
        open_key = winreg.OpenKey(hkey, key, 0, winreg.KEY_ALL_ACCESS)
        info_key = winreg.QueryInfoKey(open_key)
        for x in range(0, info_key[0]):
            sub_key = winreg.EnumKey(open_key, 0)
            try:
                winreg.DeleteKey(open_key, sub_key)
                print("Removed %s\\%s " % (key, sub_key))
            except WindowsError:
                deleteSubkey(hkey, key + "\\" + sub_key)

        winreg.DeleteKey(open_key, "")
        open_key.Close()
        print("Removed %s" % key)

    key = R"Software\JavaSoft\Prefs\jetbrains\clion"
    print("Removing " + key + " from registry")
    try:
        deleteSubkey(winreg.HKEY_CURRENT_USER, key)
    except WindowsError as e:
        print("Are you sure you ran this script as an administrator?")
        print(str(e))
    else:
        print("Registry edited")
