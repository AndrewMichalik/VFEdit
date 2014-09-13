VERSION 2.00
Begin Form frmAudDoc 
   BackColor       =   &H00FFFFFF&
   Caption         =   "Untitled"
   ClientHeight    =   4572
   ClientLeft      =   72
   ClientTop       =   936
   ClientWidth     =   9408
   FillColor       =   &H00FFFFFF&
   Height          =   5268
   Icon            =   AUDDOC.FRX:0000
   KeyPreview      =   -1  'True
   Left            =   48
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4572
   ScaleWidth      =   9408
   Top             =   264
   Width           =   9456
   Begin SSPanel pnlAudTxt 
      BevelInner      =   1  'Inset
      BorderWidth     =   2
      FloodColor      =   &H00FFFFFF&
      Height          =   1215
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Visible         =   0   'False
      Width           =   9375
      Begin TextBox edtAudTxt 
         BorderStyle     =   0  'None
         Height          =   975
         HideSelection   =   0   'False
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   5
         Top             =   120
         Width           =   9150
      End
   End
   Begin PictureBox picAmpDsp 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      FillColor       =   &H00FFFFFF&
      ForeColor       =   &H00FFFFFF&
      Height          =   3135
      Left            =   0
      ScaleHeight     =   3132
      ScaleWidth      =   9396
      TabIndex        =   1
      Top             =   1200
      Width           =   9390
      Begin ccSubClass sbcLngPol 
         Left            =   0
         Messages        =   AUDDOC.FRX:0302
         Retval20Mode    =   0   'False
         Top             =   480
      End
      Begin Timer tmrAmpTic 
         Interval        =   125
         Left            =   0
         Top             =   0
      End
   End
   Begin Label funInpArg 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "InpArg"
      Height          =   255
      Left            =   1680
      TabIndex        =   4
      Top             =   4320
      Visible         =   0   'False
      Width           =   855
   End
   Begin Label funPrcNam 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "PrcNam"
      Height          =   255
      Left            =   840
      TabIndex        =   3
      Top             =   4320
      Visible         =   0   'False
      Width           =   855
   End
   Begin Label funRetVal 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "RetVal"
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   4320
      Visible         =   0   'False
      Width           =   855
   End
   Begin Menu mnuFile 
      Caption         =   "&File"
      Begin Menu mnuFNew 
         Caption         =   "&New..."
         Shortcut        =   ^N
      End
      Begin Menu mnuFOpen 
         Caption         =   "&Open..."
         Shortcut        =   ^O
      End
      Begin Menu mnuFRevert 
         Caption         =   "&Revert"
      End
      Begin Menu mnuFSep1 
         Caption         =   "-"
      End
      Begin Menu mnuFSave 
         Caption         =   "&Save"
         Enabled         =   0   'False
         Shortcut        =   ^S
      End
      Begin Menu mnuFSaveAs 
         Caption         =   "Save &As..."
      End
      Begin Menu mnuFClose 
         Caption         =   "&Close"
      End
      Begin Menu mnuFSep2 
         Caption         =   "-"
      End
      Begin Menu mnuFImport 
         Caption         =   "&Import..."
      End
      Begin Menu mnuFExport 
         Caption         =   "&Export..."
      End
      Begin Menu mnuFSep3 
         Caption         =   "-"
      End
      Begin Menu mnuFExit 
         Caption         =   "E&xit"
      End
      Begin Menu mnuFRecent 
         Caption         =   "-"
         Index           =   0
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFile1"
         Index           =   1
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFiIe2"
         Index           =   2
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFile3"
         Index           =   3
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFile4"
         Index           =   4
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFile5"
         Index           =   5
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFile6"
         Index           =   6
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFile7"
         Index           =   7
         Visible         =   0   'False
      End
      Begin Menu mnuFRecent 
         Caption         =   "RecentFile8"
         Index           =   8
         Visible         =   0   'False
      End
   End
   Begin Menu mnuIndex 
      Caption         =   "&Index"
      Enabled         =   0   'False
      Begin Menu mnuISelect 
         Caption         =   "&Select..."
         Shortcut        =   ^E
      End
      Begin Menu mnuICreate 
         Caption         =   "&Create..."
      End
      Begin Menu mnuIDelete 
         Caption         =   "&Delete..."
      End
      Begin Menu mnuISep1 
         Caption         =   "-"
      End
      Begin Menu mnuIFirst 
         Caption         =   "&First"
      End
      Begin Menu mnuILast 
         Caption         =   "&Last"
      End
      Begin Menu mnuIPrevious 
         Caption         =   "&Previous"
         Shortcut        =   ^Q
      End
      Begin Menu mnuINext 
         Caption         =   "&Next"
         Shortcut        =   ^W
      End
      Begin Menu mnuISep2 
         Caption         =   "-"
      End
      Begin Menu mnuITextEdit 
         Caption         =   "&Text Edit"
      End
      Begin Menu mnuIFont 
         Caption         =   "F&ont..."
      End
      Begin Menu mnuISep3 
         Caption         =   "-"
      End
      Begin Menu mnuIRevert 
         Caption         =   "&Revert"
      End
   End
   Begin Menu mnuEdit 
      Caption         =   "&Edit"
      Begin Menu mnuEUndo 
         Caption         =   "&Undo                                   "
         Enabled         =   0   'False
      End
      Begin Menu mnuERedo 
         Caption         =   "R&edo"
         Enabled         =   0   'False
      End
      Begin Menu mnuESep1 
         Caption         =   "-"
      End
      Begin Menu mnuECut 
         Caption         =   "Cu&t"
         Shortcut        =   ^X
      End
      Begin Menu mnuECrop 
         Caption         =   "C&rop"
      End
      Begin Menu mnuECopy 
         Caption         =   "&Copy"
         Shortcut        =   ^C
      End
      Begin Menu mnuEPaste 
         Caption         =   "&Paste"
         Enabled         =   0   'False
         Shortcut        =   ^V
      End
      Begin Menu mnuEPasteLink 
         Caption         =   "Paste &Link..."
         Visible         =   0   'False
      End
      Begin Menu mnuEDelete 
         Caption         =   "&Delete"
         Shortcut        =   {DEL}
      End
      Begin Menu mnuESep2 
         Caption         =   "-"
      End
      Begin Menu mnuEErase 
         Caption         =   "Er&ase"
      End
      Begin Menu mnuETrimSilence 
         Caption         =   "Tri&m Silence"
      End
      Begin Menu mnuEInsertSilence 
         Caption         =   "&Insert Silence"
      End
      Begin Menu mnuESep3 
         Caption         =   "-"
      End
      Begin Menu mnuESelectAll 
         Caption         =   "&Select All"
         Shortcut        =   ^A
      End
      Begin Menu mnuESelectExtents 
         Caption         =   "Select E&xtents..."
      End
      Begin Menu mnuSep4 
         Caption         =   "-"
      End
      Begin Menu mnuEConfigure 
         Caption         =   "Confi&gure..."
      End
   End
   Begin Menu mnuView 
      Caption         =   "&View"
      Begin Menu mnuVResolution 
         Caption         =   "&Resolution"
         Begin Menu mnuVRLow 
            Caption         =   "&Low"
         End
         Begin Menu mnuVRMed 
            Caption         =   "&Medium"
         End
         Begin Menu mnuVRHgh 
            Caption         =   "&High"
         End
      End
      Begin Menu mnuVSep1 
         Caption         =   "-"
      End
      Begin Menu mnuVZoom 
         Caption         =   "&Zoom"
         Begin Menu mnuVZIn 
            Caption         =   "&In~Up Arrow"
         End
         Begin Menu mnuVZOut 
            Caption         =   "&Out~Down Arrow"
         End
         Begin Menu mnuVZFit 
            Caption         =   "to &Fit~Center Key"
         End
      End
      Begin Menu mnuVSep2 
         Caption         =   "-"
      End
      Begin Menu mnuVScroll 
         Caption         =   "&Scroll"
         Begin Menu mnuVSLeft 
            Caption         =   "&Left~Left Arrow"
         End
         Begin Menu mnuVSRight 
            Caption         =   "&Right~Right Arrow"
         End
         Begin Menu mnuVSStart 
            Caption         =   "&Start~Home Key"
         End
         Begin Menu mnuVSEnd 
            Caption         =   "&End~End Key"
         End
      End
      Begin Menu mnuVScrollTo 
         Caption         =   "Scroll &To..."
      End
      Begin Menu mnuVSep3 
         Caption         =   "-"
      End
      Begin Menu mnuCueMark 
         Caption         =   "&Cue Mark"
         Visible         =   0   'False
         Begin Menu mnuVCMNext 
            Caption         =   "&Next"
         End
         Begin Menu mnuVCMPrevious 
            Caption         =   "&Previous"
         End
         Begin Menu mnuVCMSelect 
            Caption         =   "&Select"
         End
         Begin Menu mnuVCMToggle 
            Caption         =   "&Toggle"
         End
         Begin Menu mnuVCMClearAll 
            Caption         =   "&Clear All"
         End
      End
      Begin Menu mnuVSep4 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin Menu mnuVToolBar 
         Caption         =   "Tool &Bar"
         Checked         =   -1  'True
      End
      Begin Menu mnuVStatusLine 
         Caption         =   "Status &Line"
         Checked         =   -1  'True
      End
      Begin Menu mnuVSep5 
         Caption         =   "-"
      End
      Begin Menu mnuVConfigure 
         Caption         =   "Confi&gure..."
      End
   End
   Begin Menu mnuEffects 
      Caption         =   "Effe&cts"
      Begin Menu mnuApplyFilter 
         Caption         =   "&Apply Filter (beta)"
         Visible         =   0   'False
      End
      Begin Menu mnuCChangeFrequency 
         Caption         =   "&Change Frequency..."
      End
      Begin Menu mnuDCBiasAdjust 
         Caption         =   "DC &Bias Adjust (beta)"
         Visible         =   0   'False
      End
      Begin Menu mnuCCompressExpand 
         Caption         =   "D&ynamic Compress/Expand"
      End
      Begin Menu mnuCEcho 
         Caption         =   "&Echo"
      End
      Begin Menu mnuCEqualize 
         Caption         =   "E&qualize..."
      End
      Begin Menu mnuCFadeIn 
         Caption         =   "Fade &In"
      End
      Begin Menu mnuCFadeOut 
         Caption         =   "Fade &Out"
      End
      Begin Menu mnuCMixFrom 
         Caption         =   "&Mix From..."
      End
      Begin Menu mnuCVNormalize 
         Caption         =   "&Normalize"
      End
      Begin Menu mnuCReduceNoise 
         Caption         =   "&Reduce Noise"
      End
      Begin Menu mnuCPitchHigher 
         Caption         =   "Pitch &Higher (beta)"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin Menu mnuCPitchLower 
         Caption         =   "Pitch &Lower (beta)"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin Menu mnuCSpeedFaster 
         Caption         =   "Speed &Faster (beta)"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin Menu mnuCSpeedSlower 
         Caption         =   "Speed &Slower (beta)"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin Menu mnuCToneGenerator 
         Caption         =   "&Tone Generator..."
      End
      Begin Menu mnuCVolumeUp 
         Caption         =   "Volume &Up"
      End
      Begin Menu mnuCVolumeDown 
         Caption         =   "Volume &Down"
      End
      Begin Menu mnuCSep1 
         Caption         =   "-"
      End
      Begin Menu mnuCConfigure 
         Caption         =   "Confi&gure..."
      End
   End
   Begin Menu mnuPlay 
      Caption         =   "&Play"
      Begin Menu mnuPOnce 
         Caption         =   "&Once"
         Shortcut        =   ^P
      End
      Begin Menu mnuPLoop 
         Caption         =   "&Loop"
         Shortcut        =   ^L
      End
      Begin Menu mnuPFFW 
         Caption         =   "&Fast Forward"
         Shortcut        =   ^F
      End
      Begin Menu mnuPStop 
         Caption         =   "Stop~Spacebar"
      End
      Begin Menu mnuPSep1 
         Caption         =   "-"
      End
      Begin Menu mnuPConfigure 
         Caption         =   "Confi&gure..."
      End
   End
   Begin Menu mnuRecord 
      Caption         =   "&Record"
      Begin Menu mnuROnce 
         Caption         =   "&Once"
         Shortcut        =   ^R
      End
      Begin Menu mnuRPreRoll 
         Caption         =   "&Pre-Roll..."
         Visible         =   0   'False
      End
      Begin Menu mnuRStop 
         Caption         =   "Stop~Spacebar"
      End
      Begin Menu mnuRSep1 
         Caption         =   "-"
      End
      Begin Menu mnuRConfigure 
         Caption         =   "Confi&gure..."
      End
   End
   Begin Menu mnuOptions 
      Caption         =   "&Options"
      Begin Menu mnuOEnvironment 
         Caption         =   "&Environment..."
      End
      Begin Menu mnuODeviceSelect 
         Caption         =   "&Device Select..."
      End
   End
   Begin Menu mnuWindow 
      Caption         =   "&Window"
      WindowList      =   -1  'True
      Begin Menu mnuWCascade 
         Caption         =   "&Cascade"
      End
      Begin Menu mnuWTile 
         Caption         =   "&Tile"
      End
      Begin Menu mnuWArrange 
         Caption         =   "&Arrange Icons"
      End
   End
   Begin Menu mnuHelp 
      Caption         =   "&Help"
      Begin Menu mnuHContents 
         Caption         =   "&Contents"
      End
      Begin Menu mnuHSearch 
         Caption         =   "&Search For Help On..."
      End
      Begin Menu mnuTechSupport 
         Caption         =   "&Obtaining Technical Support"
      End
      Begin Menu mnuHSep1 
         Caption         =   "-"
      End
      Begin Menu mnuHAbout 
         Caption         =   "&About VFEdit"
      End
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim tAudDocTyp As VFEDOCTYP         ' Currently open document type
Dim iDocRd_Onl As Integer           ' Read-Only indicator
Dim cPrvActCtl As Control           ' Previously active control
Dim iAudTxtChg As Integer           ' Audio text modified indicator

Dim pDocAmpDsp As Long              ' Document amplitude display
Dim pDocSesEdt As Long              ' Document session edit

Dim iBsyAudFlg As Integer           ' Audio busy flag
Dim iBsyPrcFlg As Integer           ' Document processing busy flag

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Play / Record control variables
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim sRecOvrMod As String                ' Overlay / replace mode
Dim lDevSmpOff As Long                  ' Audio sample offset
Dim lDevSmpLen As Long                  ' Audio sample length
Dim lRecRepLen As Long                  ' Record overlay mode

Sub AmpDspAct (iActSta As Integer)
    ' Inhibit Amp Dsp mouse clicks
    picAmpDsp.Enabled = iActSta
    edtAudTxt.Enabled = iActSta

    ' Enable / Disable scroll timer to preserve timer resources
    tmrAmpTic.Enabled = iActSta
End Sub

Sub AudDocBsySet (iBsyFlg As Integer)
    ' Disable this window and edit functions
    BsyPrcSet (iBsyFlg)
    BsyMenUpd
End Sub

Function AudDocCapGet (fAudDoc As Form) As String
    Dim sDocCap As String
    
    If fAudDoc.Caption Like (MSG_FILUNTCAP & "*") Then
	sDocCap = Mid(fAudDoc.Caption, Len(MSG_FILUNTCAP) + 1)
	AudDocCapGet = MSG_FILUNTCAP & StrTokStr(sDocCap, Chr$(CAPFILDEL))
    Else
	sDocCap = fAudDoc.Caption
	' Strip change indicator
	sDocCap = StrTokStr(sDocCap, MSG_FILCHGCAP)
	AudDocCapGet = StrTokStr(sDocCap, MSG_FILSEGBEG)
    End If
End Function

Sub AudDocCapSet (sFilNam As String)
    Dim ii As Integer
    Dim jj As Integer
    Dim sSegDes As String

    ' Find next untitled file name
    If ("" = sFilNam) Then
	For jj = 1 To forms.Count + 1
	    sFilNam = MSG_FILUNTCAP & jj
	    For ii = 0 To forms.Count - 1
		If TypeOf forms(ii) Is frmAudDoc Then If (sFilNam = AudDocCapGet(forms(ii))) Then sFilNam = ""
	    Next ii
	    If ("" <> sFilNam) Then Exit For
	Next jj
    End If
    
    ' Set the caption
    Caption = sFilNam
    sSegDes = AudDocSegDes()
    
    ' Set segment number
    If (Len(sSegDes)) Then Caption = Caption & MSG_FILSEGBEG & sSegDes & MSG_FILSEGEND
    
    ' Set changed indicator
    If (AudDocModGet()) Then Caption = Caption & MSG_FILCHGCAP
End Sub

Function AudDocDevPla (ByVal sInpArg As String) As String
    Dim fCvtVec As Single
    Dim lLopCnt As Long
    Dim lCuePos As Long
    Dim bRewFlg As Integer
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer
    Dim iRetCod As Integer

    ' Aready active?
    If AudDevAct() Then
	MsgBox MSG_BADDEVACT, MB_OK, Caption
	AudDocDevPla = MSG_BADDEVACT
	Exit Function
    End If

    ' Get input arguments
    fCvtVec = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    lLopCnt = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    lCuePos = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    bRewFlg = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Rewind request (don't query)?
    If (Not bRewFlg) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocExtGet(MSG_AUDPLACAP, lDevSmpOff, lDevSmpLen)) Then
	    AudDocDevPla = MSG_USRCANREQ
	    Exit Function
	End If
    End If

    ' Get default filter and resample types; don't query user
    iRetCod = AAFResGet("", PRF_PLACFGSEC, iAAFTyp, iResTyp)
    
    ' Prepare file for playback
    If (0 <> AudDevPlaCue(AudDevGet(), SesEdtFil(pDocSesEdt), lDevSmpOff, lDevSmpLen, lCuePos, fCvtVec, lLopCnt, iAAFTyp, iResTyp, pDocAmpDsp, frmVFEMDI.picAudBar.hWnd, CBK_WNDPOLMSG)) Then
	MsgBox MSG_BADAUDCUE, MB_OK, Caption
	AudDocDevPla = MSG_BADAUDCUE
	Exit Function
    End If

    ' Begin playback
    If (0 <> AudDevPlaBeg(AudDevGet())) Then
	' Release "cue-ed" file (could be re-submitted if device is busy)
	lCuePos = AudDevStp(AudDevGet())
	MsgBox MSG_BADAUDPLA, MB_OK, Caption
	AudDocDevPla = MSG_BADAUDPLA
	Exit Function
    End If

    ' Test for playback type, indicate operational
    Select Case fCvtVec
	Case PLANRMDEF
	    If (lLopCnt <> 0) Then
		No_EvtSet frmVFEMDI.optAudLoo, True
	    Else
		No_EvtSet frmVFEMDI.optAudPla, True
	    End If
	Case PLAFFWDEF
	    No_EvtSet frmVFEMDI.optAudFFw, True
    End Select

    ' Disable this window and edit functions
    BsyPrcSet (True)
    BsyAudSet (True)
    BsyMenUpd

    ' No error message
    AudDocDevPla = ""

End Function

Function AudDocDevRec () As String
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    ' Recording is controlled by the environment options settings
    ' Selection region simply determines whether to use the whole file when nothing is selected
    ' RecOvrMod     Auto-Extend
    ' * Replace     * On/Off    Replace the selected region (may be whole file) with a recording of "infinite" length.
    ' * Overlay     * On        Overlay the selected region (may be whole file) with a recording of same length.
    '                           If the selected region goes past the end of the file, the file will be automatically lengthened.
    '               * Off       If the selected region goes past the end of the file, stop recording at the end of the original length
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

    ' Aready active?
    If AudDevAct() Then
	MsgBox MSG_BADDEVACT, MB_OK, Caption
	AudDocDevRec = MSG_BADDEVACT
	Exit Function
    End If
    
    ' Get Record mode indicator; default to replace mode
    sRecOvrMod = PrfGetStr(PRF_RECCFGSEC, PRF_RECMODKEY, RECMODREP)
    
    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_AUDRECCAP & ": " & sRecOvrMod, lDevSmpOff, lDevSmpLen)) Then
	AudDocDevRec = MSG_USRCANREQ
	Exit Function
    End If

    ' The replacement is the original length requested
    lRecRepLen = lDevSmpLen
    
    ' Default: Record Replace mode is set, get position, assume length is infinite
    If (RECMODREP = sRecOvrMod) Then lDevSmpLen = EOFSMPVAL

    ' Prepare file for recording
    ' Post process filtering during record to insure enough time for proper record operation
    If (0 <> AudDevRecCue(AudDevGet(), SesEdtFil(pDocSesEdt), lDevSmpOff, lDevSmpLen, 0, 0, 0, pDocAmpDsp, frmVFEMDI.picAudBar.hWnd, CBK_WNDPOLMSG)) Then
	MsgBox MSG_BADAUDCUE, MB_OK, Caption
	AudDocDevRec = MSG_BADAUDCUE
	Exit Function
    End If

    ' Begin recording
    If (0 <> AudDevRecBeg(AudDevGet())) Then
	' Release "cue-ed" file (could be re-submitted if device is busy)
	Dim lCuePos As Long
	lCuePos = AudDevStp(AudDevGet())
	MsgBox MSG_BADAUDREC, MB_OK, Caption
	AudDocDevRec = MSG_BADAUDREC
	Exit Function
    End If

    ' Disable this window and edit functions
    BsyPrcSet (True)
    BsyAudSet (True)
    BsyMenUpd

    ' No error message
    AudDocDevRec = ""

End Function

Function AudDocDevRes (ByVal sInpArg As String) As String
    Dim lTimPos As Long
    
    ' Audio active?
    If (0 <> AudDevSta(AudDevGet(), lTimPos)) Then
	' Stop I/O
	lTimPos = AudDevStp(AudDevGet())
	' Allow stop message processing to complete
	DoEvents
	' Set new cue position to zero
	AudDocDevRes = AudDocDevPla(sInpArg & Chr$(VFEARGDEL) & Str$(0) & Chr$(VFEARGDEL) & Str$(True))
    End If

End Function

Function AudDocDevRew (ByVal sInpArg As String) As String
    Dim lTimPos As Long
    Dim lSmpPos As Long
 
    ' Audio active?
    If (0 <> AudDevSta(AudDevGet(), lTimPos)) Then
	' Stop I/O
	lTimPos = AudDevStp(AudDevGet())
	' Allow stop message processing to complete
	DoEvents
	' Calculate new cue sample position
	lSmpPos = AudFilMSecToSmp(SesEdtFil(pDocSesEdt), (lTimPos - min(lTimPos, CUETIMDEF)))
	AudDocDevRew = AudDocDevPla(sInpArg & Chr$(VFEARGDEL) & Str$(lSmpPos) & Chr$(VFEARGDEL) & Str$(True))
    End If

End Function

Sub AudDocDevStp ()
    Dim lTimPos As Long
    Dim iRecFlg As Integer
    Dim pRecFil As Long
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer
    Dim iRetCod As Integer

    ' Exit if already inactive
    If (Not AudDevAct()) Then Exit Sub

    ' Check whether the device is playing or recording
    iRecFlg = (CTLPROINP = (AudDevSta(AudDevGet(), lTimPos) And CTLPRODIR))
	
    ' Stop I/O
    lTimPos = AudDevStp(AudDevGet())

    ' Was this a recording?
    If (iRecFlg) Then
	' Get current recording paste information
	pRecFil = AudDevRecGet(AudDevGet())                     ' Get recording file object
    
	' Get default filter and resample types; don't query user
	iRetCod = AAFResGet("", PRF_RECCFGSEC, iAAFTyp, iResTyp)
    
	' If Record Overlay mode is set, overlay just the length in common.
	If (RECMODOVR = sRecOvrMod) Then
	    Dim lPstMax As Long
	    Dim lCutMax As Long
	    ' Convert recorded sample count limit to pDocSesEdt relative samples
	    lPstMax = AudFilMSecToSmp(SesEdtFil(pRecFil), AudFilSmpToMSec(SesEdtFil(pDocSesEdt), lRecRepLen))
	    lCutMax = AudFilMSecToSmp(SesEdtFil(pDocSesEdt), AudFilSmpToMSec(SesEdtFil(pRecFil), AudFilSmpCnt(SesEdtFil(pRecFil))))
	    iRetCod = SesEdtPst(pDocSesEdt, pRecFil, lDevSmpOff, min(lRecRepLen, lCutMax), 0, min(AudFilSmpCnt(SesEdtFil(pRecFil)), lPstMax), iAAFTyp, iResTyp, PSTRAWDEF, MSG_AUDRECCAP)
	Else
	    ' Record Replace mode is set,
	    iRetCod = SesEdtPst(pDocSesEdt, pRecFil, lDevSmpOff, lRecRepLen, 0, EOFSMPVAL, iAAFTyp, iResTyp, PSTRAWDEF, MSG_AUDRECCAP)
	End If
    End If

    ' Update the display caret position
    iRetCod = AmpDspCarSet(pDocAmpDsp, lDevSmpOff)
    
    ' Enable this window and edit functions
    BsyPrcSet (False)
    BsyAudSet (False)
    BsyMenUpd

End Sub

Private Function AudDocExtAsk (sTtlStr As String, lSmpOff As Long, lSmpLen As Long) As Integer
    Static fExtFrm As Single     ' Extents Selection offset default
    Static fExtLen As Single     ' Extents Selection length default
    Static sExtFmt As String     ' Extents Selection data format
    Dim sReqStr As String
    Dim sRetVal As String

    ' Return FALSE to indicate no selection
    AudDocExtAsk = False
    
    ' Convert incoming defaults
    fExtFrm = AudFilSmpToMSec(SesEdtFil(pDocSesEdt), lSmpOff) / 1000#
    fExtLen = AudFilSmpToMSec(SesEdtFil(pDocSesEdt), lSmpLen) / 1000#
    
    ' Initialize defaults
    If (0 = fExtLen) Then
	fExtLen = SELLENDEF
	sExtFmt = MSG_DESSELSEC
    End If

    ' Build request string
    sReqStr = sExtFmt & Chr$(VFEARGDEL) & fExtFrm & Chr$(VFEARGDEL) & sExtFmt & Chr$(VFEARGDEL) & fExtLen

    ' Ask user for selection extents
    sRetVal = FrmModShw(Me, frmExtSel, sTtlStr & Chr$(VFEARGDEL) & sReqStr, CTR_MIDMIDNON)
    If ("" = sRetVal) Then Exit Function
    
    ' Retrieve input arguments from tag
    sExtFmt = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    fExtFrm = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    lSmpOff = AudFilMSecToSmp(SesEdtFil(pDocSesEdt), fExtFrm * 1000#)
    
    sExtFmt = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    fExtLen = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    lSmpLen = AudFilMSecToSmp(SesEdtFil(pDocSesEdt), fExtLen * 1000#)

    ' Return TRUE to indicate success
    AudDocExtAsk = True

End Function

Function AudDocExtGet (sTtlStr As String, lSmpOff As Long, lSmpLen As Long) As Integer
    Dim iRetCod As Integer
    ' This function retrieves extents as position and length.
    ' The position and length can be past the end of the file if silence extension is on.
    ' Set the amp display extents to the selected position
    
    ' Return FALSE to indicate no selection
    AudDocExtGet = False
    
    ' Check display selection extents
    If (0 <> AmpDspSelGet(pDocAmpDsp, lSmpOff, lSmpLen)) Then
	' Limit sample offsets to end of file if auto-extend silence is not selected
	SilExtOffLen lSmpOff, lSmpLen
	iRetCod = AmpDspSelSet(pDocAmpDsp, lSmpOff, lSmpLen)
    Else
	' User has not selected a region
	If (SELREGWHL = PrfGetStr(PRF_OPTENVSEC, PRF_SELREGKEY, SELREGWHL)) Then
	    lSmpOff = 0
	    lSmpLen = AudFilSmpCnt(SesEdtFil(pDocSesEdt))
	Else
	    SilExtOffLen lSmpOff, lSmpLen
	    If (Not AudDocExtAsk(sTtlStr, lSmpOff, lSmpLen)) Then Exit Function
	    SilExtOffLen lSmpOff, lSmpLen
	End If
    End If

    ' Return TRUE to indicate success
    AudDocExtGet = True

End Function

Private Function AudDocLod (ByVal sInpArg As String) As String
    Dim sFilNam As String
    Dim sSegDes As String
    Dim iRetCod As Integer
    Dim fResDef As Single

    ' Retrieve file name and document type info and index selection
    sFilNam = StrTokStr(sInpArg, Chr$(VFEARGDEL))
    TypStrToDoc sInpArg, tAudDocTyp
    iDocRd_Onl = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    sSegDes = StrTokStr(sInpArg, Chr$(VFEARGDEL))

    ' Open session file; fill in correct data for headered file types
    If (0 <> AudDocSesOpn(pDocSesEdt, sFilNam, sSegDes, tAudDocTyp)) Then
	AudDocLod = ""
	Exit Function
    End If

    ' Verify against database and update strings stored in tAudDocTyp
    TypStrToDoc AudDocTypFnd(TypDocToStr(tAudDocTyp)), tAudDocTyp

    ' Verify that document is not read-only
    ' May have changed or been incorrectly specified by explicit load or recent file open
    If (Not iDocRd_Onl) Then iDocRd_Onl = (GetAttr_LF(sFilNam) And FILE_ATTRIBUTE_READONLY)

    ' Load snippet text
    If (Len(AudDocSegDes())) Then
	' Initialize edit box
	AudDocTxtGet edtAudTxt
	' Set defaults
	pnlAudTxt.Visible = Val(PrfGetStr(PRF_IDXTXTSEC, PRF_TXTEDTKEY, ""))
	edtAudTxt.FontName = PrfGetStr(PRF_IDXTXTSEC, PRF_TXTFNTKEY, edtAudTxt.FontName)
	edtAudTxt.FontSize = PrfGetStr(PRF_IDXTXTSEC, PRF_TXTSIZKEY, edtAudTxt.FontSize)
	mnuIndex.Enabled = True
	' Force re-size
	If pnlAudTxt.Visible Then Form_Resize
    End If

    ' Get & set default view resolution
    Select Case PrfGetStr(PRF_VIWCFGSEC, PRF_VIWDEFKEY, MSG_VIWRESMED)
	Case MSG_VIWRESLOW
	    fResDef = Val(PrfGetStr(PRF_VIWCFGSEC, PRF_VIWLOWKEY, Str$(RESLOWDEF)))
	    mnuVRLow_Click
	Case MSG_VIWRESMED
	    fResDef = Val(PrfGetStr(PRF_VIWCFGSEC, PRF_VIWMEDKEY, Str$(RESMEDDEF)))
	    mnuVRMed_Click
	Case MSG_VIWRESHGH
	    fResDef = Val(PrfGetStr(PRF_VIWCFGSEC, PRF_VIWHGHKEY, Str$(RESHGHDEF)))
	    mnuVRHgh_Click
	Case Else
	    fResDef = Val(PrfGetStr(PRF_VIWCFGSEC, MSG_VIWRESMED, Str$(RESMEDDEF)))
	    mnuVRMed_Click
    End Select
    
    ' Allocate and associate display window
    If (0 <> AmpDspOpn(pDocAmpDsp, SesEdtFil(pDocSesEdt), fResDef, picAmpDsp.hWnd)) Then
	MsgBox MSG_FILNAMSTR & sFilNam & CRLF() & WRN_INSWINRES, MB_OK, frmVFEMDI.Caption
	AudDocLod = ""
	Exit Function
    End If
    
    ' Update open document returned type (retrieves updated info for headered & segmented files)
    AudDocLod = TypDocToStr(tAudDocTyp)
    
    ' Set caption
    AudDocCapSet sFilNam

    ' Force form active
    Form_Activate

End Function

Function AudDocLodRel ()
    Dim iRetCod As Integer
    
    'Release amplitude display windows and files (OK to close in either order)
    iRetCod = SesEdtCls(pDocSesEdt)
    iRetCod = AmpDspCls(pDocAmpDsp)
    
    ' Return success
    AudDocLodRel = 0
End Function

Sub AudDocLodSeg (iSegQry)
    Dim iRetCod As Integer
    
    ' If not a "NUL" request (ie, initial load or revert) then save current text
    If ((SEGNULQRY <> iSegQry) And (iAudTxtChg)) Then iAudTxtChg = AudDocTxtSet(edtAudTxt)
    
    ' Select the specified segment; Automatically saved if not "NUL" request
    iRetCod = SesEdtSegSel(pDocSesEdt, iSegQry)
    
    ' Display error message for demo limit and other errors
    If (0 <> iRetCod) Then
	' Temporary to eliminate extra dialog box; review low level and effect on "initial" load
	Dim sTmp As String
	sTmp = CIFGetStr(iRetCod, MSG_UNKERRCAP)
	If (sTmp = "Operation cancelled at user's request.") Then
	    Beep
	Else
	    MsgBox sTmp, MB_OK, frmVFEMDI.Caption
	End If
	Exit Sub
    End If

    ' Retrieve new segments
    AudDocTxtGet edtAudTxt

End Sub

Function AudDocModGet ()
    AudDocModGet = SesEdtMod(pDocSesEdt, False) Or iAudTxtChg
End Function

Private Function AudDocPosAsk (sTtlStr As String, lSmpOff As Long, lSmpLen As Long, iAskLen As Integer) As Integer
    Static fPos_At As Single     ' Position At default
    Static fPosLen As Single     ' Position Selection length default
    Static sPosFmt As String     ' Position At data format
    Dim sReqStr As String
    Dim sRetVal As String

    ' Return FALSE to indicate no selection
    AudDocPosAsk = False
    
    ' Convert incoming defaults
    fPos_At = AudFilSmpToMSec(SesEdtFil(pDocSesEdt), lSmpOff) / 1000#
    fPosLen = AudFilSmpToMSec(SesEdtFil(pDocSesEdt), lSmpLen) / 1000#
    
    ' Initialize defaults
    If (0 = fPosLen) Then
	fPosLen = SELLENDEF
	sPosFmt = MSG_DESSELSEC
    End If

    ' Build request string & Inhibit length request (if not asked)
    sReqStr = sPosFmt & Chr$(VFEARGDEL) & Str(fPos_At)
    If (iAskLen) Then sReqStr = sReqStr & Chr$(VFEARGDEL) & sPosFmt & Chr$(VFEARGDEL) & Str(fPosLen)

    ' Ask user for new position
    sRetVal = FrmModShw(Me, frmPosSel, sTtlStr & Chr$(VFEARGDEL) & sReqStr, CTR_MIDMIDNON)
    If ("" = sRetVal) Then Exit Function
    
    ' Retrieve input arguments from tag
    sPosFmt = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    fPos_At = Val(StrTokStr(sRetVal, Chr$(VFEARGDEL)))
    lSmpOff = AudFilMSecToSmp(SesEdtFil(pDocSesEdt), fPos_At * 1000#)
    
    sPosFmt = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    fPosLen = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    lSmpLen = AudFilMSecToSmp(SesEdtFil(pDocSesEdt), fPosLen * 1000#)

    ' Return TRUE to indicate success
    AudDocPosAsk = True

End Function

Function AudDocPosGet (sTtlStr As String, lSmpOff As Long, lSmpLen As Long, iAskLen As Integer) As Integer
    Dim iRetCod As Integer
    ' This function retrieves position and, optionally, length.
    ' The position can be past the end of the file if silence extension is on.
    ' Set the amp display caret to the selected position
    ' The length is arbitrary and may extend past the end of the file even if silence extension is off.
 
    ' Return FALSE to indicate no selection
    AudDocPosGet = False
    
    ' Query amplitude display for cursor position
    ' Note: Position is always selected in this release
    iRetCod = AmpDspCarGet(pDocAmpDsp, lSmpOff)
    
    ' Limit sample offset to end of file if auto-extend silence is not selected
    SilExtOff (lSmpOff)

    ' Title string indicates whether to query user or use defaults
    If ("" <> sTtlStr) Then
	' Ask user for both position and length
	If (Not AudDocPosAsk(sTtlStr, lSmpOff, lSmpLen, iAskLen)) Then Exit Function
    End If

    ' Limit sample offset to end of file if auto-extend silence is not selected
    ' Future release: limit offset in dialog box
    SilExtOff (lSmpOff)

    ' Reset amp display caret position
    ' Note: AmpDsp insures valid position
    iRetCod = AmpDspCarSet(pDocAmpDsp, lSmpOff)
    
    ' Return TRUE to indicate success
    AudDocPosGet = True

End Function

Function AudDocSav (ByVal sFilNam As String) As Integer
    Dim iRetCod As Integer

    ' Is the file read-only?
    If (iDocRd_Onl) Then
	sFilNam = VFEFilSvA("", tAudDocTyp)
	If ("" = sFilNam) Then
	    AudDocSav = False
	    Exit Function
	End If
    End If

    ' Has the file been "saved as" yet?
    If ("" = sFilNam) Then
	' File is not named
	sFilNam = VFEFilSvA("", tAudDocTyp)
	If ("" = sFilNam) Then
	    AudDocSav = False
	    Exit Function
	End If
    End If

    ' Update annotation text
    If (iAudTxtChg) Then iAudTxtChg = AudDocTxtSet(edtAudTxt)

    ' Save file to specified name
    iRetCod = SesEdtSav(pDocSesEdt, sFilNam, Val(PrfGetStr(PRF_OPTENVSEC, PRF_AUTBAKKEY, Str$(AUTBAKDEF))))
    If (0 <> iRetCod) Then
	Beep
	MsgBox MSG_FILNAMSTR & sFilNam & CRLF() & CIFGetStr(iRetCod, MSG_UNKERRCAP), MB_OK, Caption
	AudDocSav = False
	Exit Function
    End If

    ' Set caption
    RcnFilWrt sFilNam, tAudDocTyp, False
    AudDocCapSet sFilNam
    AudDocSav = True

End Function

Function AudDocSegDes () As String
    Dim sDesStr As String
    Dim iRetCod As Integer
    sDesStr = String(255, Chr$(STRNULDEL))

    ' Get the description for this document segment
    iRetCod = SesEdtDes(pDocSesEdt, sDesStr, Len(sDesStr), False)
    AudDocSegDes = StrTokStr(sDesStr, Chr$(STRNULDEL))

End Function

Function AudDocSesOpn (pSesEdt As Long, ByVal sFilNam As String, sSegDes As String, tOpnDoc As VFEDOCTYP) As Integer
    Dim iRetCod As Integer
    
    ' Assume success
    AudDocSesOpn = 0
    
    ' SesEdtOpn and SesEdtRev insure that pSesEdt is set to zero for safe release on error
    ' Open a fresh file or revert to saved
    If (0 = pSesEdt) Then
	' Demo limit about to be reached? Display "About Box" with working demo message
	If (1 >= SesEdtDemLim(0, 0)) Then iRetCod = Val(FrmModShw(frmVFEMDI, frmAbtVFE, MSG_DEMVERCAP, CTR_MIDMIDNON))
	iRetCod = SesEdtOpn(pSesEdt, sFilNam, Val(sSegDes), tOpnDoc.iFilFmt, tOpnDoc.iPCMTyp, tOpnDoc.iChnCnt, tOpnDoc.lSmpFrq, 0, SafGetDir(PrfGetStr(PRF_OPTENVSEC, PRF_WRKDIRKEY, WRKDIRDEF)), hWnd, CBK_WNDPOLMSG)
    Else
	iRetCod = SesEdtRev(pSesEdt)
	If (0 = iRetCod) Then iRetCod = AmpDspCls(pDocAmpDsp)
    End If

    ' Display error message
    If (0 <> iRetCod) Then
	If ("" = sFilNam) Then sFilNam = MSG_FILUNTCAP
	MsgBox MSG_FILNAMSTR & sFilNam & CRLF() & CIFGetStr(iRetCod, MSG_UNKERRCAP), MB_OK, frmVFEMDI.Caption
	AudDocSesOpn = iRetCod
	Exit Function
    End If

    ' Set currently selected undo level
    ' Disable undo/redo for "VFEdit Jr." version
    Dim iUndLvl As Integer
    If (0 <> Val(PrfGetStr(PRF_OPTENVSEC, PRF_UNDLVLKEY, Str$(UNDLVLDEF))) And (0 = lVFEVer_Jr)) Then
	iUndLvl = UNDLVLMAX
    Else
	iUndLvl = 0
    End If
    iRetCod = SesEdtUndMax(pSesEdt, iUndLvl)

End Function

Sub AudDocTxtGet (edtAudTxt As TextBox)
    ' VB cannot exchange strings > 255 bytes
    ' This reads and writes as an array, thereby avoiding use of the VB CDK
    ' May want to switch to VBCreateHlstr(lpFarStr, _fstrlen (lpFarStr)) in future
    
    Dim ii As Integer
    Dim sAudTxt As String
    Dim cLowChr As String * 1
    Dim cHghChr As String * 1
    Dim iTmpArr() As Integer
    ReDim iTmpArr(IDXTXTMAX / 2)

    ' Get long string as integer array
    If (SesEdtSegTxtGet(pDocSesEdt, iTmpArr(0), IDXTXTMAX)) Then
	sAudTxt = ""
    Else
	' Unpack integer array into string
	For ii = 0 To ((IDXTXTMAX / 2) - 1) Step 1
	    ' Retrieve low byte
	    cLowChr = Chr$(iTmpArr(ii) And &HFF)
	    If (cLowChr = Chr$(0)) Then Exit For
	    sAudTxt = sAudTxt & cLowChr
	    ' Retrieve high byte
	    cHghChr = Chr$((iTmpArr(ii) / 256) And &HFF)
	    If (cHghChr = Chr$(0)) Then Exit For
	    sAudTxt = sAudTxt & cHghChr
	Next ii
    End If

    ' Indicate unchanged from original
    edtAudTxt = sAudTxt
    iAudTxtChg = False
    
End Sub

Function AudDocTxtSet (ByVal sTxtStr As String) As Integer
    ' VB cannot exchange strings > 255 bytes
    ' This reads and writes as an array, thereby avoiding use of the VB CDK
    ' May want to switch to VBCreateHlstr(lpFarStr, _fstrlen (lpFarStr)) in future
    
    Dim ii As Integer
    Dim cLowChr As String
    Dim cHghChr As String
    Dim iTmpInt As Integer
    Dim iTmpArr() As Integer
    ReDim iTmpArr(IDXTXTMAX / 2)
    
    ' Insure maximum length
    sTxtStr = Left(sTxtStr, IDXTXTMAX - 1)
    
    ' Pack string into integer array
    For ii = 0 To ((IDXTXTMAX / 2) - 1) Step 1
	iTmpInt = 0
	cLowChr = Mid(sTxtStr, (ii * 2) + 1, 1)
	If Len(cLowChr) Then iTmpInt = Asc(cLowChr)
	cHghChr = Mid(sTxtStr, (ii * 2) + 2, 1)
	If Len(cHghChr) Then iTmpInt = iTmpInt + (256 * Asc(cHghChr))
	iTmpArr(ii) = iTmpInt
	If (0 = iTmpInt) Then Exit For
    Next ii
    
    ' Set long string from integer array
    AudDocTxtSet = SesEdtSegTxtSet(pDocSesEdt, iTmpArr(0))

End Function

Sub BsyAudSet (iBsyFlg As Integer)
    iBsyAudFlg = iBsyFlg
End Sub

Function BsyEna_OK ()
    BsyEna_OK = (0 = (iBsyPrcFlg Or iBsyAudFlg))
End Function

Sub BsyMenUpd ()
    Dim sDesStr As String
    sDesStr = String(255, Chr$(STRNULDEL))
    
    ' Test if document is enabled for text or audio processing; adjust menus
    If (BsyEna_OK() And picAmpDsp = cPrvActCtl) Then
	' Update Undo menu option
	If (SesEdtUndDes(pDocSesEdt, sDesStr, Len(sDesStr))) Then
'            Const MAXMENLEN = 40
'            Const UNDACCTXT = " Ctrl+Z"
	    mnuEUndo.Caption = MSG_MENUNDCAP & " " & StrTokStr(sDesStr, Chr$(STRNULDEL))
'            If (Len(mnuEUndo.Caption & UNDACCTXT) < MAXMENLEN) Then mnuEUndo.Caption = mnuEUndo.Caption & Space$(MAXMENLEN - Len(mnuEUndo.Caption & UNDACCTXT)) & UNDACCTXT
	    mnuEUndo.Enabled = True
	Else
	    mnuEUndo.Caption = MSG_MENUNDCAP
	    mnuEUndo.Enabled = False
	End If

	' Update Redo menu option
	If (SesEdtRedDes(pDocSesEdt, sDesStr, Len(sDesStr))) Then
	    mnuERedo.Caption = MSG_MENREDCAP & " " & StrTokStr(sDesStr, Chr$(STRNULDEL))
	    mnuERedo.Enabled = True
	Else
	    mnuERedo.Caption = MSG_MENREDCAP
	    mnuERedo.Enabled = False
	End If
	
	' Update Paste Insert / Overlay menu

	' Update Edit menu
	mnuECut.Enabled = True
	mnuECrop.Enabled = True
	mnuECopy.Enabled = True
	mnuEPaste.Enabled = (0 <> AudFilSmpCnt(pAudClpFil))
	mnuEPasteLink.Enabled = False
	mnuEDelete.Enabled = True
	mnuEErase.Enabled = True
	mnuETrimSilence.Enabled = True
	mnuEInsertSilence.Enabled = True
	mnuESelectExtents.Enabled = True
    
	' Update Effects menu
	mnuEffects.Enabled = True

    End If
    
    If (BsyEna_OK() And edtAudTxt = cPrvActCtl) Then
	' Disable Undo / Redo menu option
	mnuEUndo.Enabled = False
	mnuERedo.Enabled = False
	
	' Update Paste Insert / Overlay menu

	' Update Cut / Copy / Paste
	mnuECut.Enabled = Len(edtAudTxt.SelText)
	mnuECrop.Enabled = Len(edtAudTxt.SelText)
	mnuECopy.Enabled = Len(edtAudTxt.SelText)
	mnuEPaste.Enabled = ClipBoard.GetFormat(CF_TEXT)
	mnuEDelete.Enabled = Len(edtAudTxt.SelText)
	mnuEErase.Enabled = Len(edtAudTxt.SelText)

	' Disable CopyTo / PasteFrom, etc
	mnuEPasteLink.Enabled = False
	mnuETrimSilence.Enabled = False
	mnuEInsertSilence.Enabled = False
	mnuESelectExtents.Enabled = False
	
	' Update Effects menu
	mnuEffects.Enabled = False

    End If

    ' If document is in long processing, disable menus
    If (BsyEna_OK()) Then
	' Enable "File Import / Save / Revert / Close" menus
	mnuFSave.Enabled = AudDocModGet() And Not iDocRd_Onl
	mnuFSaveAs.Enabled = True
	mnuFRevert.Enabled = AudDocModGet()
	mnuFImport = True
	mnuFExport = True
	mnuFClose.Enabled = True
	mnuFExit.Enabled = True
	' Enable "Edit / Effects" menus
	mnuIndex.Enabled = Len(AudDocSegDes())
	mnuEdit.Enabled = True
	mnuView.Enabled = True
	' Enable Play / Record - done processing
	frmVFEMDI.optAudRes.Enabled = False
	frmVFEMDI.optAudRew.Enabled = False
	frmVFEMDI.optAudStp.Enabled = True
	frmVFEMDI.optAudPla.Enabled = True
	frmVFEMDI.optAudPau.Enabled = True
	frmVFEMDI.optAudLoo.Enabled = True
	frmVFEMDI.optAudFFw.Enabled = True
	frmVFEMDI.optAudRec.Enabled = True
    Else
	' Disable "File Import / Save / Revert / Close" menus
	mnuFSave.Enabled = False
	mnuFSaveAs.Enabled = False
	mnuFRevert.Enabled = False
	mnuFImport = False
	mnuFExport = False
	mnuFExport = False
	mnuFClose.Enabled = False
	mnuFExit.Enabled = False
	' Disable "Edit / Effects" menus
	mnuEdit.Enabled = False
	mnuView.Enabled = False
	mnuEffects.Enabled = False
	' Disable Play / Record if busy processing
	If (Not iBsyAudFlg) Then
	    frmVFEMDI.optAudRes.Enabled = False
	    frmVFEMDI.optAudRew.Enabled = False
	    frmVFEMDI.optAudStp.Enabled = False
	    frmVFEMDI.optAudPla.Enabled = False
	    frmVFEMDI.optAudPau.Enabled = False
	    frmVFEMDI.optAudLoo.Enabled = False
	    frmVFEMDI.optAudFFw.Enabled = False
	    frmVFEMDI.optAudRec.Enabled = False
	Else
	    ' Enable rewind/restart if not recording
	    frmVFEMDI.optAudRes.Enabled = Not frmVFEMDI.optAudRec
	    frmVFEMDI.optAudRew.Enabled = Not frmVFEMDI.optAudRec
	End If
    End If

    ' Enable / Disable Amplitude Display
    AmpDspAct (BsyEna_OK())

    ' Update file menu entries
    mnuFile_Click

    ' Update main form menus and buttons
    sDesStr = FrmFunExe(frmVFEMDI, "VFEMDIMenUpd", "0")

End Sub

Sub BsyPrcSet (iBsyFlg As Integer)
    iBsyPrcFlg = iBsyFlg
End Sub

Sub edtAudTxt_Change ()
    If (True = iAudTxtChg) Then Exit Sub
    
    ' Update Clean / iDirty indicators
    iAudTxtChg = True
    AudDocCapSet AudDocCapGet(Me)
End Sub

Sub edtAudTxt_GotFocus ()
    ' Indicate active control
    Set cPrvActCtl = edtAudTxt

    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub edtAudTxt_MouseUp (Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' Update Edit / File menu options
     BsyMenUpd
End Sub

Sub Form_Activate ()
    Dim iRetCod As Integer

    ' Yield to complete re-paints
    DoEvents

    ' Update status line
    frmVFEMDI.ctlStaLin.Segment = MID_FILTYPDES
    frmVFEMDI.ctlStaLin.SegCaption = SegCapGet(tAudDocTyp)
    
    ' Re-Enable Amp Dsp components
    AmpDspAct (BsyEna_OK())
    
    ' Activate previously active control
    SafFocCtl Me, cPrvActCtl

    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub Form_Deactivate ()
    ' Indicate previously active form
    ' Works for maximized switched by window menu
    Set fPrvActFrm = frmVFEMDI.ActiveForm
    
    ' Disable Amp Dsp components
    AmpDspAct (False)
End Sub

Sub Form_GotFocus ()
    ' Activate previously active control
    ' This causes infinite loop on foreground maximized window, open large existing file
    ' SafFocCtl Me, cPrvActCtl
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    Dim sErrMsg As String
    ' If this form is currently playing or recording, let space bar stop operation
    If (AudDevAct()) Then frmVFEMDI.cmdAudStp = True
End Sub

Sub Form_Load ()
    Dim iRetCod As Integer
    HelpContextID = HLP_AUDDOC

    ' Disable options for "VFEdit Jr." version
    If (lVFEVer_Jr) Then SetMnu_Jr
    
    ' Fix menu item tabs
    Call SetMnuTab(mnuVZIn)
    Call SetMnuTab(mnuVZOut)
    Call SetMnuTab(mnuVZFit)
    
    Call SetMnuTab(mnuVSLeft)
    Call SetMnuTab(mnuVSRight)
    Call SetMnuTab(mnuVSStart)
    Call SetMnuTab(mnuVSEnd)
    
    Call SetMnuTab(mnuPStop)
    Call SetMnuTab(mnuRStop)

    ' Subclass this form for long polling display
    sbcLngPol.HwndParam = hWnd

    ' Initialize active control
    Set cPrvActCtl = picAmpDsp
    
End Sub

Sub Form_LostFocus ()
    ' Indicate previously active form
    ' Works for switch from audio bar switch
    Set fPrvActFrm = frmVFEMDI.ActiveForm
End Sub

Sub Form_QueryUnload (Cancel As Integer, UnloadMode As Integer)
    Dim iRetCod As Integer

    ' Disable close if document is active
    If (Not BsyEna_OK()) Then
	Beep
	Cancel = True
	Exit Sub
    End If

    If (AudDocModGet()) Then
	iRetCod = MsgBox(Chr$(34) & AudDocCapGet(Me) & Chr$(34) & " " & MSG_FILSAVCHG & Chr$(10) & Chr$(13) & MSG_FILSAVASK, MB_YESNOCANCEL Or MB_ICONEXCLAMATION, frmVFEMDI.Caption)
	' Check user response
	Select Case iRetCod
	  Case IDYES
	    ' User selected Yes, load the File Save dialog
	    ' Don't unload if save failed or user selects Cancel on the file save dialog
	    If (Not AudDocSav(AudDocCapFnd(Me))) Then Cancel = True
	  Case IDNO
	    ' User selected No, OK to unload
	    Cancel = False
	  Case IDCANCEL
	    ' User selected Cancel
	    Cancel = True
	End Select
    End If
End Sub

Sub Form_Resize ()
    Dim iRemHgt As Integer
    Dim iBrdSiz As Integer

    iRemHgt = ScaleHeight

    If WindowState <> 1 And ScaleHeight <> 0 Then
	
	'Resize Embedded Text Control
	If pnlAudTxt.Visible Then
	    pnlAudTxt.Visible = False
	    
	    iBrdSiz = pnlAudTxt.BorderWidth + 2 * pnlAudTxt.BevelWidth
	    pnlAudTxt.Height = ScaleHeight / 4
	    pnlAudTxt.Width = ScaleWidth
	    edtAudTxt.Height = pnlAudTxt.Height - 2 * iBrdSiz * Screen.TwipsPerPixelY
	    edtAudTxt.Width = pnlAudTxt.Width - 2 * iBrdSiz * Screen.TwipsPerPixelX
	    edtAudTxt.Top = iBrdSiz * Screen.TwipsPerPixelY
	    edtAudTxt.Left = iBrdSiz * Screen.TwipsPerPixelX
	    iRemHgt = 3 * ScaleHeight / 4
	    
	    pnlAudTxt.Visible = True
	End If

	'Resize Amplitude Display
	picAmpDsp.Visible = False
	picAmpDsp.Height = iRemHgt
	picAmpDsp.Width = ScaleWidth
	picAmpDsp.Top = ScaleHeight - iRemHgt
	picAmpDsp.Visible = True

    End If
End Sub

Sub Form_Unload (Cancel As Integer)
    Dim iRetCod As Integer
    Dim sErrMsg As String

    'Release amplitude display windows and files
    iRetCod = AudDocLodRel()
    
    ' Clear status line
    frmVFEMDI.ctlStaLin.Segment = MID_FILTYPDES
    frmVFEMDI.ctlStaLin.SegCaption = ""
    
    ' Update main form menus and buttons, indicate 1 closing
    sErrMsg = FrmFunExe(frmVFEMDI, "VFEMDIMenUpd", "1")

    ' Indicate previously active form is main form
    ' Prevents weird invisible form after play/record since VB
    ' does not properly activate the remaining form
    Set fPrvActFrm = frmVFEMDI

End Sub

Sub funPrcNam_Change ()
    ' Visual Basic does not permit functions within
    ' forms to be called directly. This routine provides
    ' that capability.
    
    ' Ignore self changing procedure name to null
    If ("" = funPrcNam) Then Exit Sub

    ' Initialize return value
    funRetVal = ""

    ' Parse incoming request
    If (funPrcNam = "") Then Exit Sub
    If (funPrcNam = "AudDocLod") Then funRetVal = AudDocLod(funInpArg)
    If (funPrcNam = "mnuFNew_Click") Then VFEFilNew (TypDocToStr(tAudDocTyp)), False    ' No user query
    If (funPrcNam = "mnuFOpen_Click") Then mnuFOpen_Click
    If (funPrcNam = "mnuFSave_Click") Then mnuFSave_Click
    If (funPrcNam = "mnuEdit_Click") Then mnuEdit_Click
    If (funPrcNam = "mnuECut_Click") Then mnuECut_Click
    If (funPrcNam = "mnuECopy_Click") Then mnuECopy_Click
    If (funPrcNam = "mnuEPaste_Click") Then mnuEPaste_Click
    If (funPrcNam = "mnuEDelete_Click") Then mnuEDelete_Click
    If (funPrcNam = "mnuECrop_Click") Then mnuECrop_Click
    If (funPrcNam = "mnuETrimSilence_Click") Then mnuETrimSilence_Click
    If (funPrcNam = "mnuEErase_Click") Then mnuEErase_Click
    If (funPrcNam = "mnuCVolumeDown_Click") Then mnuCVolumeDown_Click
    If (funPrcNam = "mnuCVolumeUp_Click") Then mnuCVolumeUp_Click
    If (funPrcNam = "mnuCVNormalize_Click") Then mnuCVNormalize_Click
    If (funPrcNam = "AudDocDevPla") Then funRetVal = AudDocDevPla(funInpArg)
    If (funPrcNam = "AudDocDevRec") Then funRetVal = AudDocDevRec()
    If (funPrcNam = "AudDocDevRes") Then funRetVal = AudDocDevRes(funInpArg)
    If (funPrcNam = "AudDocDevRew") Then funRetVal = AudDocDevRew(funInpArg)
    If (funPrcNam = "AudDocDevStp") Then AudDocDevStp
    If (funPrcNam = "AudDocBsyChk") Then funRetVal = Not BsyEna_OK()
    If (funPrcNam = "AudDocBsySet") Then AudDocBsySet Val(funInpArg)
					
    ' Clear for next call
    funPrcNam = ""

End Sub

Sub mnuCChangeFrequency_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim sRetArg As String
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer
    Dim fFrqMul As Single
    Dim lDstFrq As Long
    Dim iRetCod As Integer

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_CHGFRQCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Get conversion algorithms and frequency shift percentage
    sRetArg = FrmModShw(frmVFEMDI, frmEffFrq, "", CTR_MIDMIDNON)
    If ("" = sRetArg) Then Exit Sub
    fFrqMul = StrTokStr(sRetArg, Chr$(VFEARGDEL))
    iAAFTyp = StrTokStr(sRetArg, Chr$(VFEARGDEL))
    iResTyp = StrTokStr(sRetArg, Chr$(VFEARGDEL))

    ' Check destination frequency
    If (1 = fFrqMul) Then Exit Sub
    If ((0 = fFrqMul) Or (0 = (tAudDocTyp.lSmpFrq * fFrqMul)) Or ((tAudDocTyp.lSmpFrq * fFrqMul) > SMPFRQMAX)) Then
	Beep
	Exit Sub
    End If

    ' Change frequency
    iRetCod = SesEffChgFrq(pDocSesEdt, lSmpOff, lSmpLen, fFrqMul, iAAFTyp, iResTyp, MSG_CHGFRQCAP)

End Sub

Sub mnuCCompressExpand_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer
    Dim ceCmpExp As CMPEXPTYP

    ' Retrieve current defaults
    ceCmpExp.fCmpThr = CMPTHRDEF
    ceCmpExp.lCmpAtk = 50
    ceCmpExp.fCmpMin = PrfGetStr(PRF_EFFCFGSEC, PRF_DCEMAXKEY, Str$(DCEMAXDEF))
    ceCmpExp.fExpThr = EXPTHRDEF
    ceCmpExp.lExpAtk = EXPATKDEF
    ceCmpExp.fExpMax = PrfGetStr(PRF_EFFCFGSEC, PRF_DCEMAXKEY, Str$(DCEMAXDEF))
    ceCmpExp.lCE_Dcy = CE_DCYDEF
    ceCmpExp.fNoiThr = NOITHRDEF
    ceCmpExp.fNoiAtt = NOIATTDEF
    
    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFDCECAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Compress / Expand
    iRetCod = SesEffCmpExp(pDocSesEdt, lSmpOff, lSmpLen, ceCmpExp, MSG_EFFDCECAP)
    
End Sub

Sub mnuCConfigure_Click ()
    Dim sRetArg As String
    sRetArg = FrmModShw(frmVFEMDI, frmEffCfg, "", CTR_MIDMIDNON)
End Sub

Sub mnuCEcho_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFECHCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Perform echo operation
    iRetCod = SesEffEchDec(pDocSesEdt, lSmpOff, lSmpLen, Val(PrfGetStr(PRF_EFFCFGSEC, PRF_ECHDLYKEY, Str$(ECHDLYDEF))), Val(PrfGetStr(PRF_EFFCFGSEC, PRF_ECHDCYKEY, Str$(ECHDCYDEF))), MSG_EFFECHCAP)
    
End Sub

Sub mnuCEqualize_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim sRetArg As String

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFEQUCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Frequency Equalize
    sRetArg = FrmModShw(frmVFEMDI, frmEffEqu, Str$(pDocSesEdt) & Chr$(VFEARGDEL) & Str$(lSmpOff) & Chr$(VFEARGDEL) & Str$(lSmpLen), CTR_MIDMIDNON)
End Sub

Sub mnuCFadeIn_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFFADCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Fade in/ out
    iRetCod = SesEffFad_IO(pDocSesEdt, lSmpOff, lSmpLen, Val(PrfGetStr(PRF_EFFCFGSEC, PRF_FDIBEGKEY, Str$(FDIBEGDEF))), Val(PrfGetStr(PRF_EFFCFGSEC, PRF_FDIENDKEY, Str$(FDIENDDEF))), FADALGNRM, MSG_EFFFADCAP)
    
End Sub

Sub mnuCFadeOut_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFFADCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Scan for normalization level
    iRetCod = SesEffFad_IO(pDocSesEdt, lSmpOff, lSmpLen, Val(PrfGetStr(PRF_EFFCFGSEC, PRF_FDOBEGKEY, Str$(FDOBEGDEF))), Val(PrfGetStr(PRF_EFFCFGSEC, PRF_FDOENDKEY, Str$(FDOENDDEF))), FADALGNRM, MSG_EFFFADCAP)
    
End Sub

Sub mnuCMixFrom_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim sRetArg As String
    Dim sFilNam As String
    Dim tMixDoc As VFEDOCTYP
    ReDim iMixLvl(1) As Integer
    Dim pMixFil As Long
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer
    Dim iRetCod As Integer

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFMIXCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Ask user for mix file name, document type and mix level
    sRetArg = FrmModShw(frmVFEMDI, frmEffMix, Caption & Chr$(VFEARGDEL) & TypDocToStr(tAudDocTyp), CTR_MIDMIDNON)
    If ("" = sRetArg) Then Exit Sub

    ' Parse for file name
    sFilNam = StrTokStr(sRetArg, Chr$(VFEARGDEL))

    ' Parse for selected document type
    TypStrToDoc sRetArg, tMixDoc
    
    ' Parse for mix levels
    iMixLvl(0) = Val(StrTokStr(sRetArg, Chr$(VFEARGDEL)))
    iMixLvl(1) = Val(StrTokStr(sRetArg, Chr$(VFEARGDEL)))

    ' Open file for input
    iRetCod = AudFilOpn(pMixFil, sFilNam, 0, tMixDoc.iFilFmt, tMixDoc.iPCMTyp, tMixDoc.iChnCnt, tMixDoc.lSmpFrq, 0, hWnd, CBK_WNDPOLMSG)
    If (0 <> iRetCod) Then
	MsgBox MSG_FILNAMSTR & sFilNam & CRLF() & CIFGetStr(iRetCod, MSG_UNKERRCAP), MB_OK, Caption
	Exit Sub
    End If

    ' Get default filter and resample types; don't query user
    iRetCod = AAFResGet("", PRF_EDTFTRSEC, iAAFTyp, iResTyp)
    
    ' Mix files
    iRetCod = SesEffMixFil(pDocSesEdt, lSmpOff, lSmpLen, 1, pMixFil, 0, iMixLvl(0), 0, iAAFTyp, iResTyp, MSG_EFFMIXCAP)

    ' Close mix file
    iRetCod = AudFilCls(pMixFil)

End Sub

Sub mnuCReduceNoise_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFREDCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Scan for normalization level
    iRetCod = SesEffRedNoi(pDocSesEdt, lSmpOff, lSmpLen, Val(PrfGetStr(PRF_EFFCFGSEC, PRF_REDTHRKEY, Str$(REDTHRDEF))), Val(PrfGetStr(PRF_EFFCFGSEC, PRF_REDATTKEY, Str$(REDATTDEF))), MSG_EFFREDCAP)
    
End Sub

Sub mnuCToneGenerator_Click ()
    On Error GoTo mnuCToneGeneratorErr
    ' Note: The file creation section should probably be moved to the
    ' Tone Generator API in a future release
    Dim pTonFil As Long
    Dim iPCMTyp As Integer
    Dim iChnCnt As Integer
    Dim lSmpFrq As Long
    Dim sTonFil As String
    Dim lSmpOff As Long
    Dim iRetCod As Integer
    
    ' Get the current audio document settings
    iChnCnt = tAudDocTyp.iChnCnt
    lSmpFrq = tAudDocTyp.lSmpFrq

    ' Query amplitude display for cursor position
    ' Note: Position is always selected in this release
    iRetCod = AudDocPosGet("", lSmpOff, 0, False)
    
    ' Create the temporary tone file at default PCM type but same channel count and frequency as current
    sTonFil = SafGetDir(PrfGetStr(PRF_OPTENVSEC, PRF_WRKDIRKEY, WRKDIRDEF)) & MSG_TONGENPFX & Hex$(GetCurrentTask()) & MSG_TONGENEXT
    Open sTonFil For Binary Access Write As #1
    Close #1
    iRetCod = AudFilOpn(pTonFil, sTonFil, 0, 0, 0, iChnCnt, lSmpFrq, 0, hWnd, CBK_WNDPOLMSG)

    ' On error display tone gen open error message
    If (0 <> iRetCod) Then
	MsgBox MSG_BADTONGEN, MB_OK, frmVFEMDI.Caption
	Exit Sub
    End If

    ' Generate Tones
    If ("" = FrmModShw(frmVFEMDI, frmTonGen, Str$(pTonFil), CTR_MIDMIDNON)) Then
	' Paste data (always insert). Ignore resample and anti-alias filters since same frequency
	iRetCod = SesEdtPst(pDocSesEdt, pTonFil, lSmpOff, 0, 0, EOFSMPVAL, 0, 0, PSTRAWDEF, MSG_TONGENCAP)
	If (0 <> iRetCod) Then MsgBox CIFGetStr(iRetCod, MSG_UNKERRCAP), MB_OK, Caption
    End If

    ' Close temporary file
    iRetCod = AudFilCls(pTonFil)
    SafFilDel sTonFil
    Exit Sub

mnuCToneGeneratorErr:
    MsgBox MSG_BADTONGEN, MB_OK, frmVFEMDI.Caption
    Exit Sub

End Sub

Sub mnuCVNormalize_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim fNrmLvl As Single
    Dim fNrmExc As Single
    Dim fNrmMax As Single
    Dim fLvl_dB As Single
    Dim iRetCod As Integer

    ' Set default selection values & get current selection (if any)
    If (Not AudDocExtGet(MSG_EFFVNZCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Retrieve current defaults
    fNrmLvl = PrfGetStr(PRF_EFFCFGSEC, PRF_NRMLVLKEY, Str$(NRMLVLDEF))
    fNrmExc = PrfGetStr(PRF_EFFCFGSEC, PRF_NRMEXCKEY, Str$(NRMEXCDEF))
    fNrmMax = NRMMAXDEF

    ' Scan for normalization level, exit if zero dB
    If (0 <> SesEffNrmLvl(pDocSesEdt, lSmpOff, lSmpLen, fNrmLvl, fNrmExc, fNrmMax, fLvl_dB)) Then Exit Sub
    If (0 = fLvl_dB) Then Exit Sub
    
    ' Normalize
    iRetCod = SesEffVolAdj(pDocSesEdt, lSmpOff, lSmpLen, fLvl_dB, MSG_EFFVNZCAP)
    
End Sub

Sub mnuCVolumeDown_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer
    Dim fLvl_dB As Single
    
    ' Set default selection values & get current selection (if any), exit if zero dB
    If (Not AudDocExtGet(MSG_EFFVDNCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Get volume adjust level
    fLvl_dB = Val(PrfGetStr(PRF_EFFCFGSEC, PRF_VOLDWNKEY, Str$(VOLDWNDEF)))
    If (0 = fLvl_dB) Then Exit Sub
    
    ' Adjust volume
    iRetCod = SesEffVolAdj(pDocSesEdt, lSmpOff, lSmpLen, fLvl_dB, MSG_EFFVDNCAP)

End Sub

Sub mnuCVolumeUp_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer
    Dim fLvl_dB As Single
    
    ' Set default selection values & get current selection (if any), exit if zero dB
    If (Not AudDocExtGet(MSG_EFFVUPCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Get volume adjust level
    fLvl_dB = Val(PrfGetStr(PRF_EFFCFGSEC, PRF_VOL_UPKEY, Str$(VOL_UPDEF)))
    If (0 = fLvl_dB) Then Exit Sub
    
    ' Adjust volume
    iRetCod = SesEffVolAdj(pDocSesEdt, lSmpOff, lSmpLen, fLvl_dB, MSG_EFFVUPCAP)

End Sub

Sub mnuEConfigure_Click ()
    Dim sRetArg As String
    sRetArg = FrmModShw(frmVFEMDI, frmEdtCfg, "", CTR_MIDMIDNON)
End Sub

Sub mnuECopy_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    If (picAmpDsp = cPrvActCtl) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocExtGet(MSG_AUDCOPCAP, lSmpOff, lSmpLen)) Then Exit Sub
	iRetCod = SesEdtCop(pDocSesEdt, pAudClpFil, lSmpOff, lSmpLen, MSG_AUDCOPCAP)
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Copy selected text to Clipboard
	ClipBoard.SetText edtAudTxt.SelText
    End If
    
    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuECrop_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    If (picAmpDsp = cPrvActCtl) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocExtGet(MSG_AUDCRPCAP, lSmpOff, lSmpLen)) Then Exit Sub
	iRetCod = SesEdtCrp(pDocSesEdt, 0, lSmpOff, lSmpLen, EOFSMPVAL, MSG_AUDCRPCAP)
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Crop selected text.
	edtAudTxt = edtAudTxt.SelText
    End If
    
    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuECut_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    If (picAmpDsp = cPrvActCtl) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocExtGet(MSG_AUDCUTCAP, lSmpOff, lSmpLen)) Then Exit Sub
	iRetCod = SesEdtCut(pDocSesEdt, pAudClpFil, lSmpOff, lSmpLen, MSG_AUDCUTCAP)
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Cut selected text to Clipboard
	ClipBoard.SetText edtAudTxt.SelText
	' Delete selected text.
	edtAudTxt.SelText = ""
    End If

    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuEDelete_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    If (picAmpDsp = cPrvActCtl) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocExtGet(MSG_AUDDELCAP, lSmpOff, lSmpLen)) Then Exit Sub
	iRetCod = SesEdtCut(pDocSesEdt, 0, lSmpOff, lSmpLen, MSG_AUDDELCAP)
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Delete selected text.
	edtAudTxt.SelText = ""
    End If
    
    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuEdit_Click ()
    ' Update Edit / File menu options
    BsyMenUpd
End Sub

Sub mnuEErase_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim iRetCod As Integer

    If (picAmpDsp = cPrvActCtl) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocExtGet(MSG_AUDERACAP, lSmpOff, lSmpLen)) Then Exit Sub
	iRetCod = SesEdtEra(pDocSesEdt, 0, lSmpOff, lSmpLen, lSmpLen, MSG_AUDERACAP)
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Delete selected text.
	edtAudTxt.SelText = Space(Len(edtAudTxt.SelText))
    End If
    
    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuEInsertSilence_Click ()
    Static lSmpOff As Long
    Static lSmpLen As Long
    Dim iRetCod As Integer

    If (picAmpDsp = cPrvActCtl) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocPosGet(MSG_AUDSILCAP, lSmpOff, lSmpLen, True)) Then Exit Sub
	iRetCod = SesEdtEra(pDocSesEdt, 0, lSmpOff, 0, lSmpLen, MSG_AUDSILCAP)
    End If

End Sub

Sub mnuEPaste_Click ()
    Dim lSmpOff As Long
    Dim iRetCod As Integer
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer
    
    If (picAmpDsp = cPrvActCtl) Then
	' Query amplitude display for cursor position
	' Note: Position is always selected in this release
	iRetCod = AudDocPosGet("", lSmpOff, 0, False)
	
	' Check for frequency resampling and get default filter types
	If (0 = AudFilCmpChk(pDocSesEdt, pAudClpFil, PrfGetStr(PRF_EDTFTRSEC, PRF_RESTHRKEY, Str$(RESTHRDEF)))) Then
	    If (Not AAFResGet(MSG_AUDPSTCAP, PRF_EDTFTRSEC, iAAFTyp, iResTyp)) Then Exit Sub
	    AAFResSet PRF_EDTFTRSEC, iAAFTyp, iResTyp   ' Update defaults
	End If

	' Paste data (always insert)
	iRetCod = SesEdtPst(pDocSesEdt, pAudClpFil, lSmpOff, 0, 0, EOFSMPVAL, iAAFTyp, iResTyp, PSTRAWDEF, MSG_AUDPSTCAP)
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Paste selected text.
	edtAudTxt.SelText = ClipBoard.GetText(CF_TEXT)
    End If

    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuERedo_Click ()
    Dim iRetCod As Integer
    iRetCod = SesEdtRedNxt(pDocSesEdt)
End Sub

Sub mnuESelectAll_Click ()
    Dim iRetCod As Integer

    If (picAmpDsp = cPrvActCtl) Then
	' Update amplitude display with new selection
	iRetCod = AmpDspSelSet(pDocAmpDsp, 0, AudFilSmpCnt(SesEdtFil(pDocSesEdt)))
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Select all text.
	frmVFEMDI.ActiveForm.edtAudTxt.SelStart = 0
	frmVFEMDI.ActiveForm.edtAudTxt.SelLength = Len(frmVFEMDI.ActiveForm.edtAudTxt.Text)
    End If
    
    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuESelectExtents_Click ()
    Dim iRetCod As Integer
    Static lSmpOff As Long
    Static lSmpLen As Long

    ' Check display selection extents
    iRetCod = AmpDspSelGet(pDocAmpDsp, lSmpOff, lSmpLen)
    
    ' Query user
    If (Not AudDocExtAsk(MSG_SELEXTCAP, lSmpOff, lSmpLen)) Then Exit Sub
    
    ' Update amplitude display with new selection
    iRetCod = AmpDspSelSet(pDocAmpDsp, lSmpOff, lSmpLen)

End Sub

Sub mnuETrimSilence_Click ()
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim lCrpOff As Long
    Dim lCrpLen As Long
    Dim iRetCod As Integer
    Static fPrmArr(8) As Single

    If (picAmpDsp = cPrvActCtl) Then
	' Set default selection values & get current selection (if any)
	If (Not AudDocExtGet(MSG_AUDTRMCAP, lSmpOff, lSmpLen)) Then Exit Sub
	lCrpOff = lSmpOff
	lCrpLen = lSmpLen
	iRetCod = SesEffSndPos(SesEdtFil(pDocSesEdt), lCrpOff, lCrpLen, Val(PrfGetStr(PRF_EDTCFGSEC, PRF_TRMTHRKEY, Str$(TRMTHRDEF))), Val(PrfGetStr(PRF_EDTCFGSEC, PRF_TRMGRDKEY, Str$(TRMGRDDEF))), fPrmArr(0))
	iRetCod = SesEdtCrp(pDocSesEdt, lSmpOff, lCrpOff, lCrpLen, lSmpLen, MSG_AUDTRMCAP)
    End If
    If (edtAudTxt = cPrvActCtl) Then
	' Crop selected text.
	edtAudTxt = Trim$(edtAudTxt.SelText)
    End If
    
    ' Update Edit / File menu options
    BsyMenUpd

End Sub

Sub mnuEUndo_Click ()
    Dim iRetCod As Integer
    iRetCod = SesEdtUndPrv(pDocSesEdt)
End Sub

Sub mnuFClose_Click ()
    Unload Me
End Sub

Sub mnuFExit_Click ()
    ' Unloading the MDI form invokes the QueryUnload event
    ' for each child form, then the MDI form - before unloading
    ' the MDI form. Setting the Cancel argument to True in any of the
    ' QueryUnload events aborts the unload.

    Unload frmVFEMDI

End Sub

Sub mnuFExport_Click ()
    Dim pExpFil As Long
    Dim iRetCod As Integer
    Dim iSelReg As Integer
    Dim lSmpOff As Long
    Dim lSmpLen As Long
    Dim sFilNam As String
    Dim tExpDoc As VFEDOCTYP
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer
    
    ' Initialize import document to current doc type
    tExpDoc = tAudDocTyp

    ' Set default to whole file
    lSmpOff = 0
    lSmpLen = AudFilSmpCnt(SesEdtFil(pDocSesEdt))
    
    ' Check display selection extents
    iSelReg = AmpDspSelGet(pDocAmpDsp, 0, 0)

    ' Create copy of current document type
    tExpDoc = tAudDocTyp

    ' Query for document type and file name
    sFilNam = VFEFilExp(tExpDoc, iSelReg)

    ' Cancel?
    If ("" = sFilNam) Then Exit Sub

    If (0 <> iSelReg) Then iSelReg = AmpDspSelGet(pDocAmpDsp, lSmpOff, lSmpLen)

    ' Open a "new" session file, paste in data and "save as"; use frmVFEMDI for progress reporting
    If (0 <> AudDocSesOpn(pExpFil, "", "", tExpDoc)) Then Exit Sub

    ' Get default filter and resample types; don't query user
    iRetCod = AAFResGet("", PRF_EDTFTRSEC, iAAFTyp, iResTyp)
  
    ' Paste data into new file
    iRetCod = SesEdtPst(pExpFil, SesEdtFil(pDocSesEdt), 0, 0, lSmpOff, lSmpLen, iAAFTyp, iResTyp, PSTRAWDEF, MSG_FILEXPCAP)
    If (0 = iRetCod) Then iRetCod = SesEdtSav(pExpFil, sFilNam, False)
    
    ' Success?
    If (0 <> iRetCod) Then MsgBox MSG_FILNAMSTR & sFilNam & CRLF() & CIFGetStr(iRetCod, MSG_UNKERRCAP), MB_OK, Caption

    ' Close export file
    AudDocSesCls (pExpFil)

End Sub

Sub mnuFile_Click ()
    ' Global Const MSG_DEMNEWCAP = "Demo - No New"
    ' Global Const MSG_DEMOPNCAP = "Demo - No Open"
    ' Global Const MSG_DEMIMPCAP = "Demo - No Import"
    ' Global Const MSG_DEMPFMCAP = "Demo - No Paste From"
    If (0 = SesEdtDemLim(0, 0)) Then
	' Disable File New menu
	' Note: shortcut key prevents changing menu caption
	' mnuFNew.Caption = MSG_DEMNEWCAP
	mnuFNew.Enabled = False
	' Disable File Open menu
	' Note: shortcut key prevents changing menu caption
	' mnuFOpen.Caption = MSG_DEMOPNCAP
	mnuFOpen.Enabled = False
	' Disable File Import menu
	' Note: shortcut key prevents changing menu caption
	' mnuFImport.Caption = MSG_DEMIMPCAP
	mnuFImport.Enabled = False
	mnuFExport.Enabled = False
    End If
End Sub

Sub mnuFImport_Click ()
    Dim tImpDoc As VFEDOCTYP
    Dim pImpFil As Long
    Dim sFilNam As String
    Dim iRetCod As Integer
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer
    Dim lSmpOff As Long

    ' Initialize import document to current doc type
    tImpDoc = tAudDocTyp

    ' Ask user for file name
    sFilNam = VFEFilImp(tImpDoc)
    If ("" = sFilNam) Then Exit Sub

    ' Open file for input
    iRetCod = AudFilOpn(pImpFil, sFilNam, 0, tImpDoc.iFilFmt, tImpDoc.iPCMTyp, tImpDoc.iChnCnt, tImpDoc.lSmpFrq, 0, hWnd, CBK_WNDPOLMSG)
    If (0 <> iRetCod) Then
	MsgBox MSG_FILNAMSTR & sFilNam & CRLF() & CIFGetStr(iRetCod, MSG_UNKERRCAP), MB_OK, Caption
	Exit Sub
    End If

    ' Get default filter and resample types; don't query user
    iRetCod = AAFResGet("", PRF_EDTFTRSEC, iAAFTyp, iResTyp)
    
    ' Query amplitude display for cursor position
    ' Note: Position is always selected in this release
    iRetCod = AudDocPosGet("", lSmpOff, 0, False)
    
    ' Paste data (always insert)
    iRetCod = SesEdtPst(pDocSesEdt, pImpFil, lSmpOff, 0, 0, EOFSMPVAL, iAAFTyp, iResTyp, PSTRAWDEF, MSG_FILIMPCAP)
    If (0 <> iRetCod) Then MsgBox MSG_FILNAMSTR & sFilNam & CRLF() & CIFGetStr(iRetCod, MSG_UNKERRCAP), MB_OK, Caption
    
    ' Close import file
    iRetCod = AudFilCls(pImpFil)

End Sub

Sub mnuFNew_Click ()
    ' Query user with format defaults from active document
    VFEFilNew (TypDocToStr(tAudDocTyp)), True
End Sub

Sub mnuFOpen_Click ()
    ' Default format to partial match current document type
    VFEFilOpn "", TypDocToSec(tAudDocTyp), ""
End Sub

Sub mnuFRecent_Click (index As Integer)
    RcnFilOpn (index)
End Sub

Sub mnuFRevert_Click ()
    Dim iRetCod As Integer
    Dim sFilNam As String
    
    ' Query for confirmation
    ' Future: Is AudDocModGet() necessary, since Revert is grayed if not modified?
    If (AudDocModGet()) Then
	' User did not select Yes, exit
	If (IDYES <> MsgBox(Chr$(34) & AudDocCapGet(Me) & Chr$(34) & " " & MSG_FILSAVCHG & Chr$(10) & Chr$(13) & MSG_FILREVASK, MB_YESNO Or MB_ICONEXCLAMATION, frmVFEMDI.Caption)) Then Exit Sub
    End If
    
    ' Retrieve current file name; Force caption to null file name
    sFilNam = AudDocCapFnd(Me)
    Caption = ""

    ' Re-Open document
    If ("" = AudDocLod(sFilNam & Chr$(VFEARGDEL) & TypDocToStr(tAudDocTyp) & Chr$(VFEARGDEL) & Str(iDocRd_Onl) & Chr$(VFEARGDEL) & "")) Then
	' The document unload will close the pDocSesEdt object
	Unload Me
	Exit Sub
    End If

End Sub

Sub mnuFSave_Click ()
    Dim iRetCod As Integer
    iRetCod = AudDocSav(AudDocCapFnd(Me))
End Sub

Sub mnuFSaveAs_Click ()
    Dim iRetCod As Integer
    iRetCod = AudDocSav("")
End Sub

Sub mnuHAbout_Click ()
    Dim sRetVal As String
    sRetVal = FrmModShw(frmVFEMDI, frmAbtVFE, "", CTR_MIDMIDNON)
End Sub

Sub mnuHContents_Click ()
  HelpContents
End Sub

Sub mnuHSearch_Click ()
    HelpSearch
End Sub

Sub mnuICreate_Click ()
    If (SesEdtSegCre(pDocSesEdt)) Then Beep
End Sub

Sub mnuIDelete_Click ()
    If (SesEdtSegDel(pDocSesEdt)) Then Beep
End Sub

Sub mnuIFirst_Click ()
    AudDocLodSeg SEGFSTQRY
End Sub

Sub mnuIFont_Click ()
    Dim sXfrArg As String
    Dim sFntNam As String
    sXfrArg = FrmModShw(frmVFEMDI, frmFntSel, edtAudTxt.FontName & Chr$(VFEARGDEL) & edtAudTxt.FontSize, CTR_MIDMIDNON)
    sFntNam = StrTokStr(sXfrArg, Chr$(VFEARGDEL))
    If ("" <> sFntNam) Then
	edtAudTxt.FontName = sFntNam
	edtAudTxt.FontSize = Val(StrTokStr(sXfrArg, Chr$(VFEARGDEL)))
	PrfSetStr PRF_IDXTXTSEC, PRF_TXTFNTKEY, edtAudTxt.FontName
	PrfSetStr PRF_IDXTXTSEC, PRF_TXTSIZKEY, edtAudTxt.FontSize
    End If
End Sub

Sub mnuILast_Click ()
    AudDocLodSeg SEGLSTQRY
End Sub

Sub mnuIndex_Click ()
    mnuITextEdit.Checked = pnlAudTxt.Visible
    mnuIRevert.Enabled = SesEdtMod(pDocSesEdt, True) Or iAudTxtChg
End Sub

Sub mnuINext_Click ()
    AudDocLodSeg SEGNXTQRY
End Sub

Sub mnuIPrevious_Click ()
    AudDocLodSeg SEGPRVQRY
End Sub

Sub mnuIRevert_Click ()
    ' User did not select Yes, exit
    If (IDYES <> MsgBox(MSG_FILSEGCHG & " " & Chr$(34) & "[" & AudDocSegDes() & "]" & Chr$(34) & " " & MSG_FILSAVCHG & Chr$(10) & Chr$(13) & MSG_FILREVASK, MB_YESNO Or MB_ICONEXCLAMATION, frmVFEMDI.Caption)) Then Exit Sub
    AudDocLodSeg SEGNULQRY
End Sub

Sub mnuISelect_Click ()
    AudDocLodSeg SEGSELQRY
End Sub

Sub mnuITextEdit_Click ()
    pnlAudTxt.Visible = Not pnlAudTxt.Visible
    ' Update default setting
    PrfSetStr PRF_IDXTXTSEC, PRF_TXTEDTKEY, pnlAudTxt.Visible
    Form_Resize
End Sub

Sub mnuODeviceSelect_Click ()
    Dim sErrMsg As String
    sErrMsg = AudDevSel("")
    If ("" <> sErrMsg) Then MsgBox sErrMsg, MB_OK, frmVFEMDI.Caption
End Sub

Sub mnuOEnvironment_Click ()
    Dim sRetVal As String
    sRetVal = FrmModShw(frmVFEMDI, frmOptEnv, "", CTR_MIDMIDNON)
End Sub

Sub mnuOptions_Click ()
    mnuODeviceSelect.Enabled = (AudDevCnt() > 0) And (Not AudDevAct())
End Sub

Sub mnuPConfigure_Click ()
    Dim sRetArg As String
    sRetArg = FrmModShw(frmVFEMDI, frmPlaCfg, MSG_PLACFGCAP, CTR_MIDMIDNON)
End Sub

Sub mnuPFFW_Click ()
    frmVFEMDI.optAudFFw = True
End Sub

Sub mnuPlay_Click ()
    Dim iEnaFlg
    iEnaFlg = (0 <> AudDevGet()) And (Not AudDevAct()) And (Not iBsyPrcFlg)
    mnuPLoop.Enabled = iEnaFlg
    mnuPOnce.Enabled = iEnaFlg
    mnuPFFW.Enabled = iEnaFlg
    mnuPStop.Enabled = AudDevAct()
End Sub

Sub mnuPLoop_Click ()
    frmVFEMDI.optAudLoo = True
End Sub

Sub mnuPOnce_Click ()
    frmVFEMDI.optAudPla = True
End Sub

Sub mnuPStop_Click ()
    frmVFEMDI.optAudStp = True
End Sub

Sub mnuRConfigure_Click ()
    Dim sRetArg As String
    sRetArg = FrmModShw(frmVFEMDI, frmRecCfg, MSG_RECCFGCAP, CTR_MIDMIDNON)
End Sub

Sub mnuRecord_Click ()
    Dim iEnaFlg
    iEnaFlg = (0 <> AudDevGet()) And (Not AudDevAct()) And (Not iBsyPrcFlg)
    mnuROnce.Enabled = iEnaFlg
    mnuRPreRoll.Enabled = iEnaFlg
    mnuRStop.Enabled = AudDevAct()
End Sub

Sub mnuROnce_Click ()
    frmVFEMDI.optAudRec = True
End Sub

Sub mnuRStop_Click ()
    frmVFEMDI.optAudStp = True
End Sub

Sub mnuTechSupport_Click ()
  GetConHlp Me, HLP_TCHSUP
End Sub

Sub mnuVConfigure_Click ()
    Dim sRetArg As String
    sRetArg = FrmModShw(frmVFEMDI, frmViwCfg, "", CTR_MIDMIDNON)
    
    ' Update current document resolution if changed
    If ("" <> sRetArg) Then
	If ((mnuVRLow.Checked) And 0 <> InStr(1, sRetArg, MSG_VIWRESLOW)) Then mnuVRLow_Click
	If ((mnuVRMed.Checked) And 0 <> InStr(1, sRetArg, MSG_VIWRESMED)) Then mnuVRMed_Click
	If ((mnuVRHgh.Checked) And 0 <> InStr(1, sRetArg, MSG_VIWRESHGH)) Then mnuVRHgh_Click
    End If
End Sub

Sub mnuView_Click ()
    mnuVToolbar.Checked = frmVFEMDI.picTolBar.Visible
    mnuVStatusLine.Checked = frmVFEMDI.ctlStaLin.Visible
End Sub

Sub mnuVRHgh_Click ()
    If (0 = AmpDspRes(pDocAmpDsp, Val(PrfGetStr(PRF_VIWCFGSEC, PRF_VIWHGHKEY, Str$(RESHGHDEF))))) Then Beep
    mnuVRLow.Checked = False
    mnuVRMed.Checked = False
    mnuVRHgh.Checked = True
    mnuVZFit.Checked = False
End Sub

Sub mnuVRLow_Click ()
    If (0 = AmpDspRes(pDocAmpDsp, Val(PrfGetStr(PRF_VIWCFGSEC, PRF_VIWLOWKEY, Str$(RESLOWDEF))))) Then Beep
    mnuVRLow.Checked = True
    mnuVRMed.Checked = False
    mnuVRHgh.Checked = False
    mnuVZFit.Checked = False
End Sub

Sub mnuVRMed_Click ()
    If (0 = AmpDspRes(pDocAmpDsp, Val(PrfGetStr(PRF_VIWCFGSEC, PRF_VIWMEDKEY, Str$(RESMEDDEF))))) Then Beep
    mnuVRLow.Checked = False
    mnuVRMed.Checked = True
    mnuVRHgh.Checked = False
    mnuVZFit.Checked = False
End Sub

Sub mnuVScrollTo_Click ()
    Dim lOrgOff As Long
    Dim lSmpOff As Long
    Dim iRetCod As Integer

    ' Save current position
    iRetCod = AudDocPosGet("", lSmpOff, 0, False)

    ' Ask user for new position
    If (Not AudDocPosGet(MSG_SCR_TOCAP, lSmpOff, 0, False)) Then Exit Sub
    iRetCod = AmpDspScr(pDocAmpDsp, lSmpOff)

End Sub

Sub mnuVSEnd_Click ()
    SendKeys ("{END}")
End Sub

Sub mnuVSLeft_Click ()
    SendKeys ("{LEFT}")
End Sub

Sub mnuVSRight_Click ()
    SendKeys ("{RIGHT}")
End Sub

Sub mnuVSStart_Click ()
    SendKeys ("{HOME}")
End Sub

Sub mnuVStatusLine_Click ()
    ViwStaClk
End Sub

Sub mnuVToolbar_Click ()
    ViwTolClk
End Sub

Sub mnuVZFit_Click ()
    ' Zoom to Fit does not check for whole file default; Future version?
    SendKeys ("{CLEAR}")
    
    ' Clear any active preset zooms
    mnuVRLow.Checked = False
    mnuVRMed.Checked = False
    mnuVRHgh.Checked = False
    mnuVZFit.Checked = True
End Sub

Sub mnuVZIn_Click ()
    SendKeys ("{UP}")
End Sub

Sub mnuVZOut_Click ()
    SendKeys ("{DOWN}")
End Sub

Sub mnuWArrange_Click ()
    frmVFEMDI.Arrange ARRANGE_ICONS
End Sub

Sub mnuWCascade_Click ()
    frmVFEMDI.Arrange CASCADE
End Sub

Sub mnuWTile_Click ()
    frmVFEMDI.Arrange TILE_HORIZONTAL
End Sub

Sub picAmpDsp_GotFocus ()
    ' Indicate active control
    Set cPrvActCtl = picAmpDsp
    
    ' Update Edit / File menu options
    BsyMenUpd
End Sub

Sub picAmpDsp_KeyDown (KeyCode As Integer, Shift As Integer)
    Dim iRetCod As Integer
    iRetCod = AmpDspKey(pDocAmpDsp, KeyCode, 1, Shift)
End Sub

Sub picAmpDsp_Paint ()
    Dim iRetCod As Integer
    
    iRetCod = AmpDspPnt(pDocAmpDsp, picAmpDsp.hWnd)

    ' Update Clean / iDirty indicator
    AudDocCapSet AudDocCapGet(Me)

End Sub

Sub sbcLngPol_WndMessage (wnd As Integer, msg As Integer, wp As Integer, lp As Long, retval As Long, nodef As Integer)
    Static sDesStr As String
    AudDocLngPol Me, sDesStr, wnd, msg, wp, lp, retval, nodef
End Sub

Private Function SegCapGet (tVFEDoc As VFEDOCTYP) As String
    ' Parse for file type description; append data description
    If (("" = tVFEDoc.sDocTyp) Or (0 = InStr(tVFEDoc.sDocTyp, "("))) Then
	SegCapGet = MSG_DESFMTUNK & MSG_STALINSEP & AudDocTypTxt(tAudDocTyp)
    Else
	SegCapGet = Trim(Left(tVFEDoc.sDocTyp, InStr(tVFEDoc.sDocTyp, "(") - 1)) & MSG_STALINSEP & AudDocTypTxt(tAudDocTyp)
    End If
End Function

Sub SetMnu_Jr ()
    ' Disable options for "VFEdit Jr." version
    
    ' File menu
    mnuFImport.Visible = False
    mnuFExport.Visible = False
    mnuFSep3.Visible = False

    ' Index menu
    mnuISep1.Visible = False
    mnuIFirst.Visible = False
    mnuILast.Visible = False
    mnuIPrevious.Visible = False
    mnuINext.Visible = False
    mnuIFont.Visible = False

    ' Edit menu
    mnuEUndo.Visible = False
    mnuERedo.Visible = False
    mnuESep1.Visible = False
    mnuETrimSilence.Visible = False
    mnuEInsertSilence.Visible = False
    mnuESelectExtents.Visible = False
    mnuSep4.Visible = False
    mnuEConfigure.Visible = False
    
    ' Effects menu
    mnuCChangeFrequency.Visible = False
    mnuCCompressExpand.Visible = False
    mnuCEqualize.Visible = False
    mnuCVNormalize.Visible = False
    mnuCToneGenerator.Visible = False

    ' Set icon bar
    frmVFEMDI.optEdtTrm.Visible = False
    frmVFEMDI.optEffVNz.Visible = False
    
End Sub

Sub SetMnuTab (mnu As Menu)
    Dim i%
    ' Add tabs to menu item that use non-standard accelerators
		  
    i = InStr(mnu.Caption, "~")
    If i > 0 Then
	Dim cap$
	cap = mnu.Caption
	Mid(cap, i, 1) = Chr(9)
	mnu.Caption = cap
    End If
End Sub

Sub SilExtOff (lSmpOff As Long)
    ' Insure positive numbers
    If (0 = Val(PrfGetStr(PRF_OPTENVSEC, PRF_SILEXTKEY, Str$(SILEXTDEF)))) Then lSmpOff = min(Max(0, lSmpOff), AudFilSmpCnt(SesEdtFil(pDocSesEdt)))
End Sub

Sub SilExtOffLen (lSmpOff As Long, lSmpLen As Long)
    On Error GoTo SilExtOffLenErr
    ' Ignore limits if silence extension is on
    If (0 <> Val(PrfGetStr(PRF_OPTENVSEC, PRF_SILEXTKEY, Str$(SILEXTDEF)))) Then Exit Sub
    
    ' No silence extend - limit to existing file
    Dim lSmpCnt As Long
    lSmpCnt = AudFilSmpCnt(SesEdtFil(pDocSesEdt))
    
    ' Insure positive numbers
    lSmpOff = Max(0, lSmpOff)
    lSmpLen = Max(0, lSmpLen)
    
    ' Calculate extents
    lSmpOff = min(lSmpOff, lSmpCnt)
    lSmpLen = min(lSmpLen, lSmpCnt - lSmpOff)

SilExtOffLenErr:
    Exit Sub

End Sub

Sub tmrAmpTic_Timer ()
    Dim iRetCod As Integer
    iRetCod = AmpDspTic(pDocAmpDsp, 0)
End Sub

