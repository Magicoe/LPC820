__author__ = 'nxp39054'
import os
import os.path as path
g_nKeep = 0
def DelTree(treeName, isDelDir=False, isDelRoot=False, lstKeep = []):
    'delete a tree, recursively, it can be non empty!'
    global g_nKeep
    if not path.exists(treeName):
        if not isDelDir and not isDelRoot:
            os.mkdir(treeName)
        return -1L

    for root, dirs, files in os.walk(treeName, topdown=False):
        for name in files:
            sExt = path.splitext(name)[1].lower()
            isToKeep = False
            for s in lstKeep:
                if s == sExt:
                    g_nKeep += 1
                    isToKeep = True
                    break
            if not isToKeep:
                os.remove(path.join(root, name))
            else:
                print "%d, keep file %s" % (g_nKeep, name)
            # print "deleting file %s" % name
        if isDelDir == True:
            for name in dirs:
                dirFull = path.join(root, name)
                lstDir = os.listdir(dirFull)
                if lstDir == []:
                    os.rmdir(path.join(root, name))
                # print "deleting folder %s" % name
    if isDelDir == True and isDelRoot == True and g_nKeep == 0:
        os.rmdir(treeName)


def DistCleanFile(treeName):
    'delete a tree, recursively, it can be non empty!'
    dict = {}
    dict['.bak'] = 1
    dict['.crf'] = 1 ; dict['.d'] = 1
    dict['.lnp'] = 1 ; dict['.lst'] = 1 ;
    dict['.o'] = 1
    dict['.plg'] = 1 ; dict['.srec'] = 1 
    dict['.pbi'] = 1 ; dict['.cout'] = 1 ;
    dict['.pbd'] = 1 ; dict['.browse'] = 1 ;
    dict['.elf'] = 1
    dict['.axf'] = 1 ; dict['.out'] = 1 ;
    dict['.wrn'] = 1 ; dict['.viafile'] = 1 ; dict['.vias'] = 1 ;
    dict['.scr'] = 1 ; dict['.orig'] = 1
    dict['.sdf'] = 1 ; dict['.obj'] = 1 ; dict['.tlog'] = 1 ;
    lstKeys = dict.keys()
    if not path.exists(treeName):
        return -1L
    for root, dirs, files in os.walk(treeName, topdown=False):
        for name in files:
            name = name.lower()
            sExt = path.splitext(name)[1]
            for sKey in lstKeys:
                if sKey == sExt or name.find('.uvgui.') > 0 or name.find('.uvguix.') > 0:
                    print 'Deleting File: ' + name
                    os.remove(path.join(root, name))
                    break
            # print "deleting file %s" % namE

if __name__ == '__main__':
    sWorkDir = path.abspath('.')
    DistCleanFile(sWorkDir)
    for root, dirs, files in os.walk(sWorkDir, topdown=False):
        for name in dirs:
            name = name.lower()
            if name == 'keil_output' or name == 'out_keil' or name == 'iar_output' or name == 'out_iar':
                print "Deleting Dir :" + name
                DelTree(path.join(root,name), True, True, ['.lib','.a'])

