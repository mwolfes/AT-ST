import sys

class PBar:
    def __init__(self,text='',length = 65, nticks = 48,fillchar='#',emptychar='-'):

        self.fillchar  = fillchar
        self.emptychar = emptychar

        self.__length    = length
        self.__nticks    = nticks
        
        self.__percent = 0.0
        self.__ticklen = length * 100.0 / nticks
        self.__pertick = 100.0 / nticks


        sys.stdout.write( text + "  [" + emptychar * length + "]" 
                          + chr(8) * (length + 1) )
        sys.stdout.flush()

    def Tick(self):
        np = self.__percent + self.__pertick
        if np < 0:
            self.SetPercent(0)
        elif 0 <= np and np <= 100:
            self.SetPercent(np)
        else:
            self.SetPercent(100.0)
        

    def SetPercent(self, x):
        self.__percent = 1.0 * x
        nfill = int( x * self.__length // 100 )
        sys.stdout.write( self.fillchar * nfill + self.emptychar * ( self.__length - nfill ) + "]"
                          + chr(8) * (self.__length + 1) )
        sys.stdout.flush()

    def __del__(self):
        sys.stdout.write(self.fillchar * self.__length + "]\n")
        sys.stdout.flush()
