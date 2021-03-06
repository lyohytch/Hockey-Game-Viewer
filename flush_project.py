#!/usr/bin/python

import os
import shutil

buildDir = './build/'
currDir = './'
domainDir = './Domain/'
platformKhlRuDir = './Platforms/KhlRu/'

def removeMakeFiles(mkfDir):
    if os.path.isdir(mkfDir):
        if os.path.exists(mkfDir + '/' + 'Makefile'):     
            os.remove(mkfDir + '/' + 'Makefile')
            print 'Makefile from ' + mkfDir + ' removed.'
        if os.path.exists(mkfDir + '/' + 'Makefile.Release'):
            os.remove(mkfDir + '/' + 'Makefile.Release')
            print 'Makefile.Release from ' + mkfDir + ' removed.'
        if os.path.exists(mkfDir + '/' + 'Makefile.Debug'):
            os.remove(mkfDir + '/' + 'Makefile.Debug')
            print 'Makefile.Debug from ' + mkfDir + ' removed.'           
       

def removeBuildFolders(tmpDir):
    if os.path.isdir(tmpDir):
        if os.path.exists(tmpDir):
            shutil.rmtree(tmpDir)
            print tmpDir + ' deleted.'
#MAIN
if __name__ == '__main__':
    print 'Flushing project started.'
    dirList = os.listdir(currDir)
    try:
        dirPlatform  = os.listdir(platformKhlRuDir)
        dirDomain  = os.listdir(domainDir)
        buildDirList = os.listdir(buildDir)
        removeMakeFiles(currDir)
        for dirname in dirList:
            removeMakeFiles(currDir + dirname)
        for dirname in dirPlatform:
            removeMakeFiles(platformKhlRuDir + dirname)
        for dirname in dirDomain:
            removeMakeFiles(domainDir + dirname)   
        for dirname in buildDirList:
            removeBuildFolders(buildDir + dirname)
    except Exception:
        pass
    finally:
        print 'Project successfully flushed.'
