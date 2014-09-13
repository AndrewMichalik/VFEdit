''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Installation Library functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Declare Function InsDLLIni Lib "vfeins.dll" (ByVal usReqCod As Integer, ByVal ulPrm001 As Long, ByVal ulPrm002 As String) As Integer
Declare Function ChkRegSer Lib "vfeins.dll" (ByVal usRsv001 As Integer, ByVal szSerNum As String) As Integer

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' C Interface Library functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Declare Function CIFDLLIni Lib "vfecif.dll" (ByVal usReqCod As Integer, ByVal ulPrm001 As Long, ByVal ulPrm002 As String) As Integer
Declare Function CIFLodStr Lib "VFECIF" (ByVal usMsgSID As Integer, ByVal lpMsgTxt As String, ByVal usMaxLen As Integer) As Integer

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' C Interface Library query codes
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Global Const INIREQBEG = 0

' User message strings
Global Const MSG_FILREVCAP = "File Revert"
Global Const MSG_FILSEGCHG = "Segment"
Global Const MSG_FILSAVCHG = "has changed."
Global Const MSG_FILSAVASK = "Do you want to save the changes?"
Global Const MSG_FILREVASK = "Do you want to lose the changes and revert to the last saved version?"
Global Const MSG_FILRDONLY = "is read only."
Global Const MSG_FILOVRASK = "exists, overwrite?"
Global Const MSG_FILNEWCAP = "File New"
Global Const MSG_FILOPNCAP = "File Open"
Global Const MSG_FILSVACAP = "File Save As"
Global Const MSG_FILIMPCAP = "Import"
Global Const MSG_FILEXPCAP = "Export"
Global Const MSG_FILMIXCAP = "Mix"
' ajm 1/17/99
'Global Const MSG_FILUNTCAP = "Untitled: "
'Global Const MSG_FILCHGCAP = " *"
'Global Const MSG_FILSEGBEG = " ["
Global Const MSG_FILUNTCAP = "Untitled:·"
Global Const MSG_FILCHGCAP = "·*"
Global Const MSG_FILSEGBEG = "·["
Global Const MSG_FILSEGEND = "]"

Global Const MSG_FILDRVCHR = "?:*"
Global Const MSG_FILDRVCTL = "?: *"
Global Const MSG_FILDRVROO = "?:\"
Global Const MSG_FILDRVDEF = ":"
Global Const MSG_FILPTHCHR = ":\"
Global Const MSG_FILWLDCHR = ":\*?"
Global Const MSG_FILBAD_16 = "<>,|+/ "
Global Const MSG_FILBAD_32 = "<>,|+/"
Global Const MSG_FILNAMSTR = "File "
Global Const MSG_DEMVERCAP = "Working Demo"
Global Const MSG_JR_VERCAP = "VFEdit Jr. Version"
Global Const MSG_AUDPLACAP = "Play"
Global Const MSG_SELEXTCAP = "Select Region Extents"
Global Const MSG_SCR_TOCAP = "Scroll To"
Global Const MSG_AUDRECCAP = "Record"
Global Const MSG_AUDCUTCAP = "Cut"
Global Const MSG_AUDPSTCAP = "Paste"
Global Const MSG_AUDCRPCAP = "Crop"
Global Const MSG_AUDCOPCAP = "Copy"
Global Const MSG_AUDDELCAP = "Delete"
Global Const MSG_AUDERACAP = "Erase"
Global Const MSG_AUDSILCAP = "Insert Silence"
Global Const MSG_AUDTRMCAP = "Trim Silence"
Global Const MSG_MENUNDCAP = "&Undo"
Global Const MSG_MENREDCAP = "R&edo"
Global Const MSG_CHGFRQCAP = "Change Frequency"
Global Const MSG_EFFDCECAP = "Dynamic C/E"
Global Const MSG_EFFECHCAP = "Echo"
Global Const MSG_EFFFADCAP = "Fade"
Global Const MSG_EFFREDCAP = "Reduce Noise"
Global Const MSG_EFFVUPCAP = "Volume Up"
Global Const MSG_EFFVDNCAP = "Volume Down"
Global Const MSG_EFFVNZCAP = "Volume Normalize"
Global Const MSG_EFFEQUCAP = "Frequency Equalizer"
Global Const MSG_EFFMIXCAP = "Mix From"
Global Const MSG_TONGENCAP = "Tone Generator"
Global Const MSG_PLACFGCAP = "Play Configure"
Global Const MSG_RECCFGCAP = "Record Configure"
Global Const MSG_DESFRQ_HZ = "Hz"
Global Const MSG_DESSELSEC = "Seconds:"
Global Const MSG_DESFMTUNK = "Unknown"
Global Const MSG_STALINSEP = ": "
Global Const MSG_VIWRESLOW = "Low"
Global Const MSG_VIWRESMED = "Medium"
Global Const MSG_VIWRESHGH = "High"
Global Const MSG_FILTYPMDB = "FILTYP.MDB"
Global Const MSG_FILTYPPFX = "V_FT"
Global Const MSG_FILTYPEXT = ".MDB"
Global Const MSG_TONGENPFX = "V_TG"
Global Const MSG_TONGENEXT = ".VOX"
Global Const MSG_MODVERVER = ", Version "                   ' Module version
Global Const MSG_MODVERUNK = "Unknown"                      ' Module version unknown
Global Const MSG_MIDVERNOL = " (not loaded)"                ' Module not loaded

' Error Messages
Global Const MSG_BADFILMDB = "Error initializing file type database. Please rename or replace older versions of VBDB300.DLL - exiting..."
Global Const MSG_ERRFILMDB = "Error reading file type database."
Global Const MSG_VFEINIERR = "Error during initialization, continue?"
Global Const MSG_BADFILTYP = "This file does not have a valid 'type'."
Global Const MSG_BADDEVACT = "Device already active."
Global Const MSG_BADAUDCUE = "Error cueing audio file."
Global Const MSG_BADDEVOPN = "Error opening audio device."
Global Const MSG_BADAUDPLA = "Error playing audio file."
Global Const MSG_BADAUDREC = "Error recording audio file."
Global Const MSG_BADCLPOPN = "Error opening clipboard audio file."
Global Const MSG_BADTONGEN = "Error opening tone generation audio file."
Global Const MSG_USRCANREQ = "User cancelled request."
Global Const MSG_UNKERRGTO = "An unknown error occurred. Continue?"
Global Const MSG_UNKERRCAP = "Unknown Error"
Global Const MSG_UNKERRXXX = "Unknown error! Please save your work and exit!"

' Warning messages
Global Const WRN_DSKNOTRDY = "Device not ready! Please check drive door."
Global Const WRN_BADDEVPTH = "This drive or path does not exist"
Global Const WRN_INSWINRES = "Insufficient resources. Close one or more windows."
Global Const WRN_BADFILOPN = "Cannot open file."
Global Const WRN_FILALROPN = "File already open."
Global Const WRN_WRKDEMLIM = "Working Demo limit."
Global Const WRN_BADDEFVAL = "Bad default value."
Global Const WRN_SHRNOTLOD = "File sharing not available, SHARE.EXE not loaded."

' Window messages
Global Const CBK_WNDPOLMSG = WM_USER + 1

' Status bar segment definitions
Global Const MID_LNGPOLDSP = 0
Global Const MID_FILTYPDES = 1
Global Const MID_INPOUTDEV = 2

' Profile section and key strings
Global Const PRF_PRFNAMDEF = "VFEDIT.INI"
Global Const PRF_SCRPOSSEC = "Screen Position"
Global Const PRF_SCRSTAKEY = "WindowState"
Global Const PRF_SCRLFTKEY = "PositionLeft"
Global Const PRF_SCRTOPKEY = "PositionTop"
Global Const PRF_SCRHGTKEY = "PositionHeight"
Global Const PRF_SCRWIDKEY = "PositionWidth"
Global Const PRF_BAKCLRKEY = "BackColor"
Global Const PRF_FNTNAMKEY = "FontName"
Global Const PRF_FNTSIZKEY = "FontSize"
Global Const PRF_FORCLRKEY = "ForeColor"
Global Const PRF_RCNFILSEC = "Recent Files"
Global Const PRF_RCNFILKEY = "RecentFile"
Global Const PRF_AUDDOCSEC = "Audio Document"
Global Const PRF_DOCPRVKEY = "DocumentPrevious"
Global Const PRF_DOCTYPKEY = "DocumentType"
Global Const PRF_TYPDATKEY = "TypeData"
Global Const PRF_TYPPATKEY = "TypePattern"
Global Const PRF_IDXTXTSEC = "Index Text"
Global Const PRF_TXTEDTKEY = "TextEdit"
Global Const PRF_TXTFNTKEY = "TextFont"
Global Const PRF_TXTSIZKEY = "TextSize"
Global Const PRF_EDTCFGSEC = "Edit Configure"
Global Const PRF_TRMTHRKEY = "TrimSoundThreshold"
Global Const PRF_TRMGRDKEY = "TrimGuardTime"
Global Const PRF_VIWCFGSEC = "View Configure"
Global Const PRF_VIWDEFKEY = "DefaultResolution"
Global Const PRF_VIWLOWKEY = "LowResolution"
Global Const PRF_VIWMEDKEY = "MediumResolution"
Global Const PRF_VIWHGHKEY = "HighResolution"
Global Const PRF_EFFCFGSEC = "Effects Configure"
Global Const PRF_CHGFRQKEY = "ChangeFrequency"
Global Const PRF_DCEMAXKEY = "DCEMaximum"
Global Const PRF_ECHDLYKEY = "EchoDelay"
Global Const PRF_ECHDCYKEY = "EchoDecay"
Global Const PRF_FDIBEGKEY = "FadeInStart "
Global Const PRF_FDIENDKEY = "FadeInStop"
Global Const PRF_FDOBEGKEY = "FadeOutStart"
Global Const PRF_FDOENDKEY = "FadeOutStop"
Global Const PRF_NRMLVLKEY = "NormalizeTo"
Global Const PRF_NRMEXCKEY = "NormalizeOver"
Global Const PRF_REDATTKEY = "ReduceNoiseAttenuation"
Global Const PRF_REDTHRKEY = "ReduceNoiseThreshold"
Global Const PRF_VOL_UPKEY = "VolumeAdjustUp"
Global Const PRF_VOLDWNKEY = "VolumeAdjustDown"
Global Const PRF_EQUBNDKEY = "EqualizerBand"
Global Const PRF_TONGENSEC = "Tone Generator"
Global Const PRF_DTMSTRKEY = "TonePadString"
Global Const PRF_DTMAMPKEY = "TonePadAmplitude"
Global Const PRF_DTMON_KEY = "TonePadOnLength"
Global Const PRF_DTMOFFKEY = "TonePadOffLength"
Global Const PRF_DTMLOW001 = "DTMFLowFrequency1"
Global Const PRF_DTMLOW002 = "DTMFLowFrequency2"
Global Const PRF_DTMLOW003 = "DTMFLowFrequency3"
Global Const PRF_DTMLOW004 = "DTMFLowFrequency4"
Global Const PRF_DTMHGH001 = "DTMFHighFrequency1"
Global Const PRF_DTMHGH002 = "DTMFHighFrequency2"
Global Const PRF_DTMHGH003 = "DTMFHighFrequency3"
Global Const PRF_DTMHGH004 = "DTMFHighFrequency4"
Global Const PRF_DTMBUT__0 = "DTMFButton0"
Global Const PRF_DTMBUT__1 = "DTMFButton1"
Global Const PRF_DTMBUT__2 = "DTMFButton2"
Global Const PRF_DTMBUT__3 = "DTMFButton3"
Global Const PRF_DTMBUT__4 = "DTMFButton4"
Global Const PRF_DTMBUT__5 = "DTMFButton5"
Global Const PRF_DTMBUT__6 = "DTMFButton6"
Global Const PRF_DTMBUT__7 = "DTMFButton7"
Global Const PRF_DTMBUT__8 = "DTMFButton8"
Global Const PRF_DTMBUT__9 = "DTMFButton9"
Global Const PRF_DTMBUT__A = "DTMFButtonA"
Global Const PRF_DTMBUT__B = "DTMFButtonB"
Global Const PRF_DTMBUT__C = "DTMFButtonC"
Global Const PRF_DTMBUT__D = "DTMFButtonD"
Global Const PRF_DTMBUT__S = "DTMFButton*"
Global Const PRF_DTMBUT__P = "DTMFButton#"
Global Const PRF_CUSF01KEY = "CustomFrequency1"
Global Const PRF_CUSF02KEY = "CustomFrequency2"
Global Const PRF_CUSA01KEY = "CustomAmplitude1"
Global Const PRF_CUSA02KEY = "CustomAmplitude2"
Global Const PRF_CUSLENKEY = "CustomLength"
Global Const PRF_MIXFRMSEC = "Edit Mix"
Global Const PRF_MIXL00KEY = "MixLevel0"
Global Const PRF_MIXL01KEY = "MixLevel1"
Global Const PRF_MIXF01KEY = "MixFile1"
Global Const PRF_DEVOPNSEC = "Device Open"
Global Const PRF_DEVTYPKEY = "DeviceType"
Global Const PRF_EDTFTRSEC = "Edit Filter Configure"        ' Import / Export / Paste
Global Const PRF_PLACFGSEC = "Play Configure"
Global Const PRF_RECCFGSEC = "Record Configure"
Global Const PRF_RECMODKEY = "RecordMode"
Global Const PRF_AAFTYPKEY = "Anti-aliasingType"
Global Const PRF_RESTYPKEY = "ResampleType"
Global Const PRF_RESTHRKEY = "ResampleThreshold"
Global Const PRF_OPTENVSEC = "Environment Options"
Global Const PRF_UNDLVLKEY = "UndoLevel"
Global Const PRF_SELREGKEY = "SelectionRegion"
Global Const PRF_AUTBAKKEY = "AutoBackup"
Global Const PRF_SILEXTKEY = "SilenceExtend"
Global Const PRF_WRKDIRKEY = "WorkFileDirectory"
Global Const PRF_DEVDIRKEY = "DeviceFileDirectory"
Global Const PRF_REGLICFIL = "VFEdit.Lic"
Global Const PRF_REGLICSEC = "VFEdit Licensee"
Global Const PRF_REGUSRKEY = "User"
Global Const PRF_REGCMPKEY = "Company"
Global Const PRF_REGSERKEY = "SerialNumber"
Global Const PRF_MODUSESEC = "Module Verification"

' Dialog box options enabled/ disabled
Global Const OPTENACLR = &H80000008     ' Option enable color
Global Const OPTDISCLR = &H808080       ' Option disable color

' Command line argument switch definitions
Global Const ARG_PRFNAMDEF = "p"
Global Const ARG_FILDOCTYP = "d"
Global Const ARG_DEVOUTTYP = "o"
Global Const ARG_FILSEGIDX = "si"
Global Const ARG_CMDMENREQ = "cm"
Global Const ARG_CMDMENWAI = "wait"

' Pre-defined Error numbers
Global Const ERR_DSKNOTRDY = 71
Global Const ERR_DEVNOTAVA = 68
Global Const ERR_DEMLIMERR = -2
Global Const ERR_PTHNOTAVA = 76

' Default values
Global Const SMPFRQMAX = 65000          ' Maximum sample frequency
Global Const SMPFRQMIN = 100            ' Minimum sample frequency
Global Const VFEARGDEL = 44             ' Comma - argument delimeter
Global Const VFECMDDEL = 45             ' Dash - command line delimeter
Global Const NEWLINDEL = 10             ' Linefeed
' ajm 1/17/99
' Global Const CAPFILDEL = 32             ' Space
Global Const CAPFILDEL = 183            ' Bullet "·"
Global Const STRNULDEL = 0              ' Null
Global Const DECPRCDEF = 2              ' Decision precision default
Global Const EOFSMPVAL = &HFFFFFFFF     ' End of file sample value
Global Const IDXTXTMAX = 16384
Global Const RCNFILCNT = 8

Global Const PLANRMDEF = 1              ' Play normal speed
Global Const PLALOODEF = &HFFFF         ' Play loop count
Global Const PLAFFWDEF = 2              ' Play fast forward speed
Global Const CUETIMDEF = 500            ' Play cue time offset (ms)
Global Const PSTRAWDEF = False          ' Paste raw mode inhibit default

Global Const SELLENDEF = 30             ' Extents Selection length default
Global Const RESLOWDEF = 2000           ' Ms / major division
Global Const RESMEDDEF = 500            ' Ms / major division
Global Const RESHGHDEF = 100            ' Ms / major division
Global Const SCRPOSDEF = 0              ' Scroll to position default
Global Const RESTHRDEF = 1              ' Resample frequency threshold % default

Global Const TRMTHRDEF = 2#             ' Edit Trim silence sound threshold default
Global Const TRMGRDDEF = .05            ' Edit Trim silence guard time default

Global Const CHGFRQDEF = 100            ' Effects change frequency default
Global Const DCEMAXDEF = 6
Global Const ECHDLYDEF = .2
Global Const ECHDCYDEF = -6
Global Const FDIBEGDEF = -20
Global Const FDIENDDEF = 0
Global Const FDOBEGDEF = 0
Global Const FDOENDDEF = -20
Global Const NRMLVLDEF = 80
Global Const NRMEXCDEF = 1
Global Const NRMMAXDEF = 6
Global Const REDATTDEF = 6
Global Const REDTHRDEF = 3
Global Const VOL_UPDEF = 3
Global Const VOLDWNDEF = -3

Global Const DTMAMPDEF = 80             ' Tone generator pad amplitude default
Global Const CUSFRQDEF = 0
Global Const CUSAMPDEF = 0
Global Const CUSLENDEF = 0

Global Const DTMON_LEN = 50             ' DTMF on time default
Global Const DTMOFFLEN = 50
Global Const DTMLOW001 = 697            ' North America DTMF frequencies
Global Const DTMLOW002 = 770
Global Const DTMLOW003 = 852
Global Const DTMLOW004 = 941
Global Const DTMHGH001 = 1209
Global Const DTMHGH002 = 1336
Global Const DTMHGH003 = 1477
Global Const DTMHGH004 = 1633

Global Const MIXLVLDEF = 50             ' Default mix levels

Global Const WRKDIRDEF = ""             ' Environment temporary directory default
Global Const RECMODREP = "Replace"      ' Environment record mode replace
Global Const RECMODOVR = "Overlay"      ' Environment record mode overlay
Global Const SELREGWHL = "Whole File"   ' Environment selection region default whole
Global Const SELREGASK = "Ask User"     ' Environment selection region default ask user
Global Const AUTBAKDEF = 1              ' Environment auto backup default
Global Const SILEXTDEF = 1              ' Environment silence extend default
Global Const UNDLVLDEF = 3              ' Environment undo level default
Global Const UNDLVLMAX = 3              ' Environment undo level max

' Dialog box positioning
Global Const CTR_MIDMIDNON = 1

' Callback poll procedure definitions
Global Const LNGPOLBEG = 0
Global Const LNGPOLCNT = 1
Global Const LNGPOLPAU = 2
Global Const LNGPOLEMP = 3
Global Const LNGPOLEND = 4

' File segment query types
Global Const SEGNULQRY = 0
Global Const SEGJMPQRY = 2
Global Const SEGSELQRY = 4
Global Const SEGFSTQRY = 16
Global Const SEGLSTQRY = 20
Global Const SEGPRVQRY = 24
Global Const SEGNXTQRY = 28


' Graphic Equalizer/ Analyzer constants
Global Const EQUBNDCNT = 8              ' Number of equalizer bands
Global Const EQUSLDRNG = 24             ' Range of equalizer slider control
Global Const EQUGAIDEF = 0              ' Gain (in dB)
Global Const EQUFFTORD = 8              ' Equalizer FFT order (Ord^2 = # of frequency points)
Global Const ANATIMDEF = 32             ' Number of time points in equalizer graph
Global Const ANAFFTORD = 4              ' Analyzer FFT order (Ord^2 = # of frequency points)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Context sensitive help
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Global Const HLP_VFECON = 10             ' Contents
Global Const HLP_ABTVIS = 20             ' About Dialog
Global Const HLP_TCHSUP = 30             ' Technical support
Global Const HLP_OTHPRD = 40             ' Other products
Global Const HLP_FILOPN = 50             ' File open dialog
Global Const HLP_FILFMT = 60             ' File data format
Global Const HLP_FNTSEL = 70             ' Font selection
Global Const HLP_VIWCFG = 80             ' View config
Global Const HLP_POSSEL = 90             ' Position selection
Global Const HLP_EXTSEL = 100            ' Extents selection
Global Const HLP_EDTCFG = 110            ' Edit configure
Global Const HLP_EDTMIX = 120            ' Edit mix
Global Const HLP_EFFEQU = 130            ' Effects equalize
Global Const HLP_TONGEN = 140            ' Tone generation
Global Const HLP_EFFCFG = 150            ' Effects config
Global Const HLP_DEVSEL = 160            ' Audio device select
Global Const HLP_PLACFG = 170            ' Play config
Global Const HLP_RECCFG = 180            ' Record config
Global Const HLP_FTRCFG = 190            ' Filter config
Global Const HLP_AUDDOC = 200            ' Audio document
Global Const HLP_ENVOPT = 210            ' Environment options
Global Const HLP_MODVER = 220            ' Module version
Global Const HLP_VERINF = 230            ' Version information

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Globals types shared by all modules
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Type VFEOPNTYP
    iRd_Onl As Integer                  ' Read only indicator
    iIdxMrk As Integer                  ' Index marks
End Type

Type VFEDOCTYP
    sDocTyp As String
    iFilFmt As Integer
    sPCMDes As String
    iPCMTyp As Integer
    iChnCnt As Integer
    lSmpFrq As Long
End Type

Type VFEDEVTYP
    sDevDes As String
    iCtlPro As Integer
    iPCMTyp As Integer
    iChnCnt As Integer
    lSmpFrq As Long
    iBlkLen As Integer
    iBlkCnt As Integer
    iCfgQry As Long
End Type

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Globals types for sound effects
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Type CMPEXPTYP
    fCmpThr As Single                   ' Comp  threshold (%)
    lCmpAtk As Long                     ' Comp  attack time (Hz)
    fCmpMin As Single                   ' Comp  minimum attenuation (dB)
    fExpThr As Single                   ' Exp   threshold (%)
    lExpAtk As Long                     ' Exp   attack time (Hz)
    fExpMax As Single                   ' Exp   max amplification (dB)
    lCE_Dcy As Long                     ' C/E   decay time (Hz)
    fNoiThr As Single                   ' Noise Gate threshold (%)
    fNoiAtt As Single                   ' Noise Gate attenuation (dB)
End Type

Global Const CMPTHRDEF = 80             ' Comp  threshold (%)
Global Const CMPATKDEF = 50             ' Comp  attack time (Hz)
Global Const EXPTHRDEF = 30             ' Exp   threshold (%)
Global Const EXPATKDEF = 5              ' Exp   attack time (Hz)
Global Const CE_DCYDEF = 5              ' C/E   decay time (Hz)
Global Const NOITHRDEF = 2              ' Noise Gate threshold (%)
Global Const NOIATTDEF = 3              ' Noise Gate attenuation (dB)

Function CChk (chkVal As Integer) As Integer
    CChk = 0
    If (0 <> chkVal) Then CChk = 1
End Function

Function CIFGetStr (iMsgSID As Integer, sDefStr As String) As String
    Dim iOrgLen As Integer
    Dim sRetStr As String
    
    ' Retrieve a text string from the CIF library
    If (0 = iMsgSID) Then
        CIFGetStr = "sDefStr"
    Else
        sRetStr = String(255, Chr$(STRNULDEL))
        iOrgLen = CIFLodStr(iMsgSID, sRetStr, Len(sRetStr))
        CIFGetStr = StrTokStr(sRetStr, Chr$(STRNULDEL))
    End If
End Function

Function CRLF () As String
    CRLF = Chr$(13) + Chr$(10)
End Function

Function DblRndAsc (ByVal dbSrcVal As Double, ByVal iDecCnt As Integer) As String
    Dim sSrcVal As String
    Dim sFmtStr As String
    Dim ii As Integer

    ' Convert a floating pointing value to a rounded ascii string
    If (0 = dbSrcVal) Then
        DblRndAsc = "0"
        Exit Function
    End If
    
    ' Round to required precision
    dbSrcVal = DblRndDbl(dbSrcVal, iDecCnt)

    ' Generate format string
    sFmtStr = "."
    For ii = 1 To iDecCnt
        sFmtStr = sFmtStr + "0"
    Next ii
    DblRndAsc = Format$(dbSrcVal, sFmtStr)

End Function

Function DblRndDbl (ByVal dbSrcVal As Double, ByVal iDecCnt As Integer) As Double
    Const Log_10 = 2.302585093              ' Natural log of 10
    Dim dbPrcFac As Double

    ' Compute precision factor
    dbPrcFac = Exp(iDecCnt * Log_10)
    
    ' Compute rounding value
    DblRndDbl = Int(((dbSrcVal * dbPrcFac) + .5)) / dbPrcFac

End Function

Function TypDevToStr (tDevTyp As VFEDEVTYP) As String
    TypDevToStr = tDevTyp.sDevDes & Chr$(VFEARGDEL) & tDevTyp.iCtlPro & Chr$(VFEARGDEL) & tDevTyp.iPCMTyp & Chr$(VFEARGDEL) & tDevTyp.iChnCnt & Chr$(VFEARGDEL) & tDevTyp.lSmpFrq & Chr$(VFEARGDEL) & tDevTyp.iBlkLen & Chr$(VFEARGDEL) & tDevTyp.iBlkCnt & Chr$(VFEARGDEL) & tDevTyp.iCfgQry
End Function

Function TypDocToDef (tVFEDoc As VFEDOCTYP) As String
    TypDocToDef = tVFEDoc.sPCMDes & Chr$(VFEARGDEL) & tVFEDoc.iPCMTyp & Chr$(VFEARGDEL) & tVFEDoc.iChnCnt & Chr$(VFEARGDEL) & tVFEDoc.lSmpFrq
End Function

Function TypDocToSec (tVFEDoc As VFEDOCTYP) As String
    TypDocToSec = tVFEDoc.sDocTyp & Chr$(VFEARGDEL) & tVFEDoc.iFilFmt
End Function

Function TypDocToStr (tVFEDoc As VFEDOCTYP) As String
    TypDocToStr = tVFEDoc.sDocTyp & Chr$(VFEARGDEL) & tVFEDoc.iFilFmt & Chr$(VFEARGDEL) & tVFEDoc.sPCMDes & Chr$(VFEARGDEL) & tVFEDoc.iPCMTyp & Chr$(VFEARGDEL) & tVFEDoc.iChnCnt & Chr$(VFEARGDEL) & tVFEDoc.lSmpFrq
End Function

Sub TypStrToDev (ByVal sTxtStr As String, tDevTyp As VFEDEVTYP)
    ' Returns unknown control protocol (0) if input string is null
    ' Convert string to tDevTyp
    tDevTyp.sDevDes = StrTokStr(sTxtStr, Chr$(VFEARGDEL))
    tDevTyp.iCtlPro = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tDevTyp.iPCMTyp = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tDevTyp.iChnCnt = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tDevTyp.lSmpFrq = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tDevTyp.iBlkLen = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tDevTyp.iBlkCnt = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tDevTyp.iCfgQry = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
End Sub

Sub TypStrToDoc (sTxtStr As String, tVFEDoc As VFEDOCTYP)
    ' Convert string to tVFEDoc
    ' Returns unknown file format (0) if input string is null
    ' Note: TypStrToDoc destroys input text string to simplify parsing of input arguments
    tVFEDoc.sDocTyp = StrTokStr(sTxtStr, Chr$(VFEARGDEL))
    tVFEDoc.iFilFmt = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tVFEDoc.sPCMDes = StrTokStr(sTxtStr, Chr$(VFEARGDEL))
    tVFEDoc.iPCMTyp = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tVFEDoc.iChnCnt = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
    tVFEDoc.lSmpFrq = Val(StrTokStr(sTxtStr, Chr$(VFEARGDEL)))
End Sub

