VERSION 2.00
Begin MDIForm frmVFEMDI 
   Caption         =   "VFEdit ®"
   ClientHeight    =   5355
   ClientLeft      =   1200
   ClientTop       =   1320
   ClientWidth     =   9435
   Height          =   5985
   Icon            =   VFEMDI.FRX:0000
   Left            =   1170
   LinkTopic       =   "MDIForm1"
   Top             =   720
   Visible         =   0   'False
   Width           =   9495
   Begin PictureBox picFrmCtl 
      Align           =   1  'Align Top
      Height          =   495
      Left            =   0
      ScaleHeight     =   465
      ScaleWidth      =   9405
      TabIndex        =   11
      Top             =   390
      Visible         =   0   'False
      Width           =   9435
      Begin ccSubClass sbcLngPol 
         Left            =   3360
         Messages        =   VFEMDI.FRX:0442
         Retval20Mode    =   0   'False
         Top             =   0
      End
      Begin ccSubClass sbcElaTim 
         Left            =   2640
         Messages        =   VFEMDI.FRX:0848
         Retval20Mode    =   0   'False
         Top             =   0
      End
      Begin Label funInpArg 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Caption         =   "InpArg"
         Height          =   252
         Left            =   1680
         TabIndex        =   8
         Top             =   120
         Visible         =   0   'False
         Width           =   852
      End
      Begin Label funPrcNam 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Caption         =   "PrcNam"
         Height          =   252
         Left            =   840
         TabIndex        =   9
         Top             =   120
         Visible         =   0   'False
         Width           =   852
      End
      Begin Label funRetVal 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Caption         =   "RetVal"
         Height          =   252
         Left            =   0
         TabIndex        =   10
         Top             =   120
         Visible         =   0   'False
         Width           =   852
      End
   End
   Begin Mh3dMulLabel ctlStaLin 
      Align           =   2  'Align Bottom
      BorderColor     =   &H80000006&
      FillColor       =   &H00C0C0C0&
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   315
      Left            =   0
      LightColor      =   &H80000005&
      Scalemode       =   3  'Pixels
      SegBevelStyle   =   VFEMDI.FRX:0C4E
      SegCaption      =   VFEMDI.FRX:0DD5
      SegDataField    =   VFEMDI.FRX:0DDF
      SegFormat       =   VFEMDI.FRX:0DE9
      Segment         =   1
      Segments        =   3
      SegmentStyle    =   1  'Tile Horizontal
      SegmentVarsize  =   -1
      ShadowColor     =   &H80000010&
      TabIndex        =   1
      Top             =   5040
      Width           =   9435
   End
   Begin PictureBox picTolBar 
      Align           =   1  'Align Top
      BackColor       =   &H8000000F&
      Height          =   390
      Left            =   0
      ScaleHeight     =   360
      ScaleWidth      =   9405
      TabIndex        =   0
      Top             =   0
      Width           =   9435
      Begin PictureBox picAudBar 
         BackColor       =   &H00C0C0C0&
         BorderStyle     =   0  'None
         Height          =   360
         Left            =   4680
         ScaleHeight     =   360
         ScaleWidth      =   4695
         TabIndex        =   5
         Top             =   36
         Visible         =   0   'False
         Width           =   4695
         Begin CommandButton cmdAudStp 
            Caption         =   "Stop"
            Default         =   -1  'True
            Height          =   336
            Left            =   3600
            TabIndex        =   7
            Tag             =   "Stop audio action|Stop"
            Top             =   0
            Visible         =   0   'False
            Width           =   972
         End
         Begin SSRibbon optAudFFw 
            Height          =   264
            Left            =   1980
            PictureDisabled =   VFEMDI.FRX:0DF3
            PictureUp       =   VFEMDI.FRX:0EED
            Tag             =   "Fast forward from cue|Fast forward"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optAudRec 
            GroupNumber     =   3
            Height          =   264
            Left            =   3240
            PictureDisabled =   VFEMDI.FRX:0FE7
            PictureUp       =   VFEMDI.FRX:10E1
            Tag             =   "Record audio beginning at cue|Record"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optAudStp 
            Height          =   264
            Left            =   660
            PictureUp       =   VFEMDI.FRX:11DB
            Tag             =   "Stop audio cue|Stop"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optAudPau 
            GroupNumber     =   2
            Height          =   264
            Left            =   990
            PictureUp       =   VFEMDI.FRX:12D5
            Tag             =   "Pause audio cue|Pause"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optAudRew 
            GroupNumber     =   2
            Height          =   264
            Left            =   330
            PictureDisabled =   VFEMDI.FRX:13CF
            PictureUp       =   VFEMDI.FRX:14C9
            Tag             =   "Rewind audio cue|Rewind"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optAudRes 
            GroupNumber     =   2
            Height          =   264
            Left            =   0
            PictureDisabled =   VFEMDI.FRX:15C3
            PictureUp       =   VFEMDI.FRX:16BD
            Tag             =   "Reset audio cue|Reset"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optAudPla 
            Height          =   264
            Left            =   1320
            PictureDisabled =   VFEMDI.FRX:17B7
            PictureUp       =   VFEMDI.FRX:18B1
            Tag             =   "Play audio cue|Play"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optAudLoo 
            Height          =   264
            Left            =   1650
            PictureDisabled =   VFEMDI.FRX:19AB
            PictureUp       =   VFEMDI.FRX:1AA5
            Tag             =   "Play audio cue continuously|Play loop"
            Top             =   0
            Width           =   264
         End
         Begin SSPanel pnlAudPos 
            BevelOuter      =   1  'Inset
            Caption         =   "0.0"
            FloodColor      =   &H0000FFFF&
            FloodShowPct    =   0   'False
            Height          =   315
            Left            =   2280
            TabIndex        =   6
            Top             =   0
            Width           =   975
         End
         Begin MhTip MhTip1 
            AutoSize        =   -1  'True
            AutosizeToText  =   -1  'True
            BackColor       =   &H0000FFFF&
            BevelSize       =   0
            BorderColor     =   &H00000000&
            BorderStyle     =   1  'Regular border
            Caption         =   "MhTip1"
            FillColor       =   &H0000FFFF&
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            ForeColor       =   &H00000000&
            Height          =   255
            Index           =   3
            Interval        =   750
            Left            =   0
            LightColor      =   &H00C0C0C0&
            NoTipCapture    =   0   'False
            ShadowColor     =   &H00000000&
            TextColor       =   &H00000000&
            TipChildren     =   0   'False
            TipOffsetLeft   =   10
            TipOffsetTop    =   10
            TipStyle        =   0  'Square
            Top             =   360
            WallPaper       =   0  'StrBlt
            Width           =   615
         End
      End
      Begin PictureBox picEffBar 
         BackColor       =   &H00C0C0C0&
         BorderStyle     =   0  'None
         Height          =   360
         Left            =   3480
         ScaleHeight     =   360
         ScaleWidth      =   1095
         TabIndex        =   4
         Top             =   36
         Visible         =   0   'False
         Width           =   1095
         Begin MhTip MhTip1 
            AutoSize        =   -1  'True
            AutosizeToText  =   -1  'True
            BackColor       =   &H0000FFFF&
            BevelSize       =   0
            BorderColor     =   &H00000000&
            BorderStyle     =   1  'Regular border
            Caption         =   "MhTip1"
            FillColor       =   &H0000FFFF&
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            ForeColor       =   &H00000000&
            Height          =   255
            Index           =   2
            Interval        =   750
            Left            =   0
            LightColor      =   &H00C0C0C0&
            NoTipCapture    =   0   'False
            ShadowColor     =   &H00000000&
            TextColor       =   &H00000000&
            TipChildren     =   0   'False
            TipOffsetLeft   =   10
            TipOffsetTop    =   10
            TipStyle        =   0  'Square
            Top             =   360
            WallPaper       =   0  'StrBlt
            Width           =   615
         End
         Begin SSRibbon optEffVNz 
            Height          =   330
            Left            =   660
            PictureDisabled =   VFEMDI.FRX:1B9F
            PictureUp       =   VFEMDI.FRX:1C99
            Tag             =   "Normalize audio|Normalize"
            Top             =   0
            Width           =   330
         End
         Begin SSRibbon optEffVDn 
            Height          =   330
            Left            =   330
            PictureDisabled =   VFEMDI.FRX:1D93
            PictureUp       =   VFEMDI.FRX:1E8D
            Tag             =   "Decrease volume|-Volume"
            Top             =   0
            Width           =   330
         End
         Begin SSRibbon optEffVUp 
            Height          =   330
            Left            =   0
            PictureDisabled =   VFEMDI.FRX:1F87
            PictureUp       =   VFEMDI.FRX:2081
            Tag             =   "Increase volume|+Volume"
            Top             =   0
            Width           =   330
         End
      End
      Begin PictureBox picEdtBar 
         BackColor       =   &H00C0C0C0&
         BorderStyle     =   0  'None
         Height          =   360
         Left            =   1320
         ScaleHeight     =   360
         ScaleWidth      =   2115
         TabIndex        =   3
         Top             =   36
         Visible         =   0   'False
         Width           =   2115
         Begin SSRibbon optEdtTrm 
            Height          =   264
            Left            =   1320
            PictureDisabled =   VFEMDI.FRX:217B
            PictureUp       =   VFEMDI.FRX:22FD
            Tag             =   "Cut audio to clipboard|Cut"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optEdtCrp 
            Height          =   264
            Left            =   960
            PictureDisabled =   VFEMDI.FRX:23F7
            PictureUp       =   VFEMDI.FRX:2579
            Tag             =   "Cut audio to clipboard|Cut"
            Top             =   0
            Width           =   264
         End
         Begin MhTip MhTip1 
            AutoSize        =   -1  'True
            AutosizeToText  =   -1  'True
            BackColor       =   &H0000FFFF&
            BevelSize       =   0
            BorderColor     =   &H00000000&
            BorderStyle     =   1  'Regular border
            Caption         =   "MhTip1"
            FillColor       =   &H0000FFFF&
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            ForeColor       =   &H00000000&
            Height          =   255
            Index           =   1
            Interval        =   750
            Left            =   0
            LightColor      =   &H00C0C0C0&
            NoTipCapture    =   0   'False
            ShadowColor     =   &H00000000&
            TextColor       =   &H00000000&
            TipChildren     =   0   'False
            TipOffsetLeft   =   10
            TipOffsetTop    =   10
            TipStyle        =   0  'Square
            Top             =   360
            WallPaper       =   0  'StrBlt
            Width           =   615
         End
         Begin SSRibbon optEdtEra 
            Height          =   264
            Left            =   1680
            PictureDisabled =   VFEMDI.FRX:2673
            PictureUp       =   VFEMDI.FRX:276D
            Tag             =   "Erase audio|Erase"
            Top             =   0
            Width           =   264
         End
         Begin SSRibbon optEdtPst 
            Height          =   330
            Left            =   660
            PictureDisabled =   VFEMDI.FRX:2867
            PictureUp       =   VFEMDI.FRX:29E9
            Tag             =   "Paste audio from clipboard|Paste"
            Top             =   0
            Width           =   330
         End
         Begin SSRibbon optEdtCop 
            Height          =   330
            Left            =   330
            PictureDisabled =   VFEMDI.FRX:2AE3
            PictureUp       =   VFEMDI.FRX:2C65
            Tag             =   "Copy audio from clipboard|Copy"
            Top             =   0
            Width           =   330
         End
         Begin SSRibbon optEdtCut 
            Height          =   330
            Left            =   0
            PictureDisabled =   VFEMDI.FRX:2D5F
            PictureUp       =   VFEMDI.FRX:2EE1
            Tag             =   "Cut audio to clipboard|Cut"
            Top             =   0
            Width           =   330
         End
      End
      Begin PictureBox picFilBar 
         BackColor       =   &H00C0C0C0&
         BorderStyle     =   0  'None
         Height          =   360
         Left            =   120
         ScaleHeight     =   360
         ScaleWidth      =   1155
         TabIndex        =   2
         Top             =   36
         Width           =   1155
         Begin MhTip MhTip1 
            AutoSize        =   -1  'True
            AutosizeToText  =   -1  'True
            BackColor       =   &H0000FFFF&
            BevelSize       =   0
            BorderColor     =   &H00000000&
            BorderStyle     =   1  'Regular border
            Caption         =   "MhTip1"
            FillColor       =   &H0000FFFF&
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            ForeColor       =   &H00000000&
            Height          =   255
            Index           =   0
            Interval        =   750
            Left            =   0
            LightColor      =   &H00C0C0C0&
            NoTipCapture    =   0   'False
            ShadowColor     =   &H00000000&
            TextColor       =   &H00000000&
            TipChildren     =   0   'False
            TipOffsetLeft   =   10
            TipOffsetTop    =   10
            TipStyle        =   0  'Square
            Top             =   360
            WallPaper       =   0  'StrBlt
            Width           =   615
         End
         Begin SSRibbon optFilSav 
            Enabled         =   0   'False
            Height          =   330
            Left            =   720
            PictureDisabled =   VFEMDI.FRX:2FDB
            PictureUp       =   VFEMDI.FRX:30D5
            Tag             =   "Save audio file|Save"
            Top             =   0
            Width           =   330
         End
         Begin SSRibbon optFilOpn 
            Height          =   330
            Left            =   345
            PictureDisabled =   VFEMDI.FRX:31CF
            PictureUp       =   VFEMDI.FRX:3351
            Tag             =   "Open existing audio file|Open"
            Top             =   0
            Width           =   330
         End
         Begin SSRibbon optFilNew 
            Height          =   264
            Left            =   0
            PictureDisabled =   VFEMDI.FRX:344B
            PictureUp       =   VFEMDI.FRX:35CD
            Tag             =   "Create new audio file|New"
            Top             =   0
            Width           =   264
         End
      End
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
      Begin Menu mnuFSep1 
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
         Caption         =   "RecentFile2"
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
   Begin Menu mnuView 
      Caption         =   "&View"
      Begin Menu mnuVToolbar 
         Caption         =   "&Toolbar"
         Checked         =   -1  'True
      End
      Begin Menu mnuVStatusLine 
         Caption         =   "&Status Line"
         Checked         =   -1  'True
      End
   End
   Begin Menu mnuOptions 
      Caption         =   "&Options"
      Begin Menu mnuOEnvironment 
         Caption         =   "&Environment..."
      End
      Begin Menu mnuODeviceSelect 
         Caption         =   "Device &Select..."
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
      Begin Menu mnuFSep2 
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
' Global form control variables
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim iTolButSiz       As Integer         ' Button sizes (auto-size)
Dim iTolButMrg       As Integer         ' Button Margin
Dim iMDIBrdWid       As Integer         ' MDI frame border width
Dim fReqActFrm       As form            ' Previously active form Audio Doc

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const RECLVLTIM = .1                    ' Recording level meter update period (sec)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim iAJMTest As String * 200

Sub cmdAudStp_Click ()
    Dim iRetCod As Integer
    
    ' Send message to terminate audio
    iRetCod = Val(FrmFunExe(fReqActFrm, "AudDocDevStp", ""))

    ' Pop all buttons
    No_EvtSet optAudRes, False
    No_EvtSet optAudRew, False
    No_EvtSet optAudStp, False
    No_EvtSet optAudPau, False
    No_EvtSet optAudPla, False
    No_EvtSet optAudLoo, False
    No_EvtSet optAudFFW, False
    No_EvtSet optAudRec, False
    
    ' Indicate audio inactive
    cmdAudStp.Visible = False
    
    ' Reset focus to previously active form
    SafFocFrm fPrvActFrm

    ' A DoEvents does provide slightly cleaner operation, but
    ' appears to cause an unknown system hang when clicking
    ' alot of buttons and then pressing record with
    ' a TMI device
    ' DoEvents

End Sub

Sub DetectShare ()
    Dim fh%
  ' Check for appropriate Windows version or that SHARE.EXE is loaded
    On Error GoTo DetectShare_Err
    fh = FreeFile
  
    Open App.Path & "\" & App.EXEName & ".exe" For Binary As fh
    Lock fh
    Close fh
  
    ' Simulate error to test file sharing violation
    ' Error 70  ' kbk 9.18.95
    Exit Sub

DetectShare_Err:
    Select Case Err
	Case 70  ' permission denied
	MsgBox WRN_SHRNOTLOD, MB_ICONEXCLAMATION, Caption
    End Select

    Resume Next
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
    If (funPrcNam = "VFEMDIMenUpd") Then VFEMDIMenUpd (Val(funInpArg))
    
    ' Clear for next call
    funPrcNam = ""

End Sub

Sub IniModUse (sDLLNam As String)
    Dim hIns As Integer

    ' Only free module if no other instances are running
    ' If (0 <> AppPrevInstance()) Then Exit Sub
  
    ' Note: App.PrevInstance is not set when running under VB design mode,
    ' thus cannot test in design mode - this approach corrects problem
    hIns = GetModuleHandle(App.EXEName & ".exe")
    If (0 <> hIns) Then If (0 <> GetModuleUsage(hIns)) Then Exit Sub

    ''''''''''''''''''''''''''''''''''''''''
    ' DLL already loaded?
    ''''''''''''''''''''''''''''''''''''''''
    hIns = GetModuleHandle(sDLLNam)
    If (0 = hIns) Then Exit Sub
    Do While (0 <> GetModuleUsage(hIns))
	Call FreeLibrary(hIns)
	DoEvents
    Loop

End Sub

Sub MDIForm_Activate ()
    ' Update menu and toolbar options
    VFEMDIMenUpd 0
    
    ' Yield to complete re-paints
    DoEvents
End Sub

Sub MDIForm_Load ()
    HelpContextID = HLP_VFECON
    On Error GoTo MDIForm_LoadErr
    
    ' Enable/ Disable options for "VFEdit Jr." version
    lVFEVer_Jr = Val(VFE_JRSTR)

    ' Show initial splash screen
    FrmCtrMov frmVFEIni, 0, Screen.Width, 0, Screen.Height
    frmVFEIni.Show
    
    ' Show hour glass, permit splash screen to appear
    FrmUsrDis Me
    DoEvents
    
    ' Check for appropriate Windows version or that SHARE.EXE is loaded
    DetectShare

    ' VFEdit application starts here
    Dim sCmdLin As String
    Dim sCmdArg As String
    Dim sFilNam As String
    Dim sVFEDoc As String
    Dim sSegDes As String
    Dim sOutDev As String
    Dim sMenCmd As String
    Dim iRetCod As Integer
    Dim sErrMsg As String
    Dim tDocDef As VFEDOCTYP

    ' Save application working directory spec (may be different from executable directory)
    sAppWrkDir = CurDir$
    
    ' Set working directory to directory containing the application.
    ' This will insure that DLL's can be found (if not in path)
    ChDrive App.Path
    ChDir App.Path

    ' Retrieve command line arguments
    sCmdLin = Trim$(Command$)

    ' Sample .INI file settings and there equivalent command line values
    ' DeviceType=WaveAudio,64,0,1,0,16,4,0
    ' RecentFile1=c:\windows\chimes.wav,Wave Audio (*.wav),36,Multimedia unsigned 8 bit,52,1,22050
    ' sCmdLin = "c:\windows\chimes.wav -dWave Audio (*.wav),36,Multimedia unsigned 8 bit,52,1,22050 -oWaveAudio,64,0,1,0,16,4,0 -pvfetst.ini"
    ' RecentFile1=c:\vfedit\sample\hello.vox,Pure Audio (*.vox),8,Dialogic 4 bit ADPCM,16,1,6000
    ' sCmdLin = "c:\vfedit\sample\hello.vox -dPure Audio (*.vox),8,Dialogic 4 bit ADPCM,16,1,6000 -oWaveAudio,64,0,1,0,16,4,0 -pvfetst.ini"
    ' Play a file: -m%p~
    ' sCmdLin = "c:\windows\chimes.wav -dWave Audio (*.wav),36,Multimedia unsigned 8 bit,52,1,22050 -oWaveAudio,64,0,1,0,16,4,0 -m%p~"
    ' Play a file, wait for completion and exit: -cm%p~,wait,%fx
    ' Open and play an indexed file
    ' sCmdLin = "c:\vfedit\sample\index.vap -dIndexed Audio (*.vap),28,Dialogic 4 bit ADPCM,16,1,6000 -si2 -cm%p~"

    If ("" <> sCmdLin) Then
	' Parse for file name
	If (Left$(sCmdLin, 1) <> "-") Then sFilNam = Trim(StrTokStr(sCmdLin, Chr$(VFECMDDEL)))
	
	' Parse for command line arguments
	sCmdArg = StrTokStr(sCmdLin, Chr$(VFECMDDEL))
	While ("" <> sCmdArg)
	    If (Left$(sCmdArg, Len(ARG_PRFNAMDEF)) = ARG_PRFNAMDEF) Then sPrfFilNam = Trim(Mid(sCmdArg, Len(ARG_PRFNAMDEF) + 1))
	    If (Left$(sCmdArg, Len(ARG_FILDOCTYP)) = ARG_FILDOCTYP) Then sVFEDoc = Trim(Mid(sCmdArg, Len(ARG_FILDOCTYP) + 1))
	    If (Left$(sCmdArg, Len(ARG_DEVOUTTYP)) = ARG_DEVOUTTYP) Then sOutDev = Trim(Mid(sCmdArg, Len(ARG_DEVOUTTYP) + 1))
	    If (Left$(sCmdArg, Len(ARG_FILSEGIDX)) = ARG_FILSEGIDX) Then sSegDes = Trim(Mid(sCmdArg, Len(ARG_FILSEGIDX) + 1))
	    If (Left$(sCmdArg, Len(ARG_CMDMENREQ)) = ARG_CMDMENREQ) Then sMenCmd = Trim(Mid(sCmdArg, Len(ARG_CMDMENREQ) + 1))
	    sCmdArg = StrTokStr(sCmdLin, Chr$(VFECMDDEL))
	Wend
    End If

    ' Initialize name of .INI file
    If ("" = sPrfFilNam) Then sPrfFilNam = PrfGetDir() & PRF_PRFNAMDEF

    ' Initialize name of application help file
    App.HelpFile = App.Path & "\VFEdit.Hlp"
    
    ' Initialize use of the database engine
    Const DB_OPTIONINITPATH = 1
    SetDataAccessOption DB_OPTIONINITPATH, sPrfFilNam
    
    ' Free top level DLL to insure fresh load
    ' Note: This seems to work pretty well, but what if another program is using VFECIF.DLL?
    ' If I couple this with a .INI flag, will need to isolate from another copy running concurrently
    ' IniModUse ("vfecif.dll")
    
    ' Initialize DLL support
    iRetCod = CIFDLLIni(INIREQBEG, 0&, REGKEYSTR)

    ' Initialize Installation DLL support
    iRetCod = InsDLLIni(0, 0&, "")
  
    ' Verify DLL's and VBX's being used
    VerModUse

    ' Reset button sizes (auto-size = 0 sets to minimum) & store
    optFilNew.Height = 0
    iTolButSiz = optFilNew.Height
    iTolButMrg = Screen.TwipsPerPixelX
    iMDIBrdWid = (frmVFEMDI.Width - frmVFEMDI.ScaleWidth) / 2

    ' Size ToolBar and Status Bar
    picTolBar.Height = iTolButSiz + 7 * iTolButMrg
    ctlStaLin.Height = Screen.TwipsPerPixelX * (2 * (ctlStaLin.SegTop + ctlStaLin.BevelSize) + ctlStaLin.SegHeight)

    ' Read last screen position
    Left = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRLFTKEY, Str$(Left))
    Top = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRTOPKEY, Str$(Top))
    Height = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRHGTKEY, Str$(Height))
    Width = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRWIDKEY, Str$(Width))
    SafWndSta Me, PrfGetStr(PRF_SCRPOSSEC, PRF_SCRSTAKEY, Str$(WindowState))

    ' Calculate Minimum x / y measurements
    Dim iMinX
    Dim iMinY

    iMinX = Screen.TwipsPerPixelX * GetSystemMetrics(SM_CXMin)
    iMinY = Screen.TwipsPerPixelY * GetSystemMetrics(SM_CYMin)
    
    ' Check for valid width and Height
    Width = min(Screen.Width, Max(Width, 3 * iMinX))
    Height = min(Screen.Height, Max(Height, 6 * iMinY))
    
    ' Check for valid Left and Top
    If (Left + Width <= iMinX) Or (Left >= Screen.Width - iMinX) Then Left = (Screen.Width - Width) / 2
    If (Top + Height <= iMinY) Or (Top >= Screen.Height - iMinY) Then Top = (Screen.Height - Height) / 2
    
    ' Subclass this form for long polling display
    sbcElaTim.HwndParam = picAudBar.hWnd
    sbcLngPol.HwndParam = hWnd

    ' Enumerate available file types & initialize Database support
    AudDocMDBOpn
    
    ' Initialize default file format from .INI
    If ("" = sVFEDoc) Then
	' Retrieve default document type from .Ini
	sVFEDoc = PrfGetStr(PRF_AUDDOCSEC, PRF_DOCTYPKEY, "")
    End If
    
    ' Verify the selected document type; replace with default if not OK
    sVFEDoc = AudDocTypFnd(sVFEDoc)
    
    ' Open global clipboard file
    AudClpOpn

    ' Update MDI recent files list (even if file new/open cancelled)
    RcnFilUpd
    
    'Hide initial splash screen, hide hourglass, show main screen
    Unload frmVFEIni
    FrmUsrEna Me
    Show
    
    ' Open/ New file
    If ("" = sFilNam) Then
	' Create new using current default; Query if .INI is empty
	VFEFilNew sVFEDoc, ("" = PrfGetStr(PRF_AUDDOCSEC, PRF_DOCTYPKEY, ""))
    Else
	' Open file (optional specified type)
	' Future: Optionally pass index number/description for segmented files
	VFEFilOpn sFilNam, sVFEDoc, sSegDes
    End If

    ' Open audio device if any are available
    If ("" = sOutDev) Then sOutDev = PrfGetStr(PRF_DEVOPNSEC, PRF_DEVTYPKEY, sOutDev)
    If (AudDevCnt() > 0) Then sErrMsg = AudDevSel(sOutDev)

    ' Issue menu commands
    While (0 <> Len(sMenCmd))
	Dim sCmd As String
	sCmd = StrTokStr(sMenCmd, Chr$(VFEARGDEL))

	' Perform wait command if requested
	If (ARG_CMDMENWAI = Trim(sCmd)) Then
	    While (FrmFunExe(frmVFEMDI.ActiveForm, "AudDocBsyChk", ""))
	    DoEvents
	    Wend
	Else SendKeys sCmd
	End If
	
	' SendKeys sCmd
	DoEvents
    Wend
    
    ' Everything ready to go!
    Exit Sub

MDIForm_LoadErr:
    If (2 = MsgBox(MSG_VFEINIERR, MB_RETRYCANCEL, Caption)) Then ErrMsgExi ("")
    Resume Next

End Sub

Sub MDIForm_QueryUnload (Cancel As Integer, UnloadMode As Integer)
    ' Disable close if audio is active
    If (AudDevAct()) Then
	Cancel = True
	Beep
	Exit Sub
    End If
End Sub

Sub MDIForm_Resize ()
    Dim iAudBarMax
    Dim iAudBarClp
    
    ' Calculate audio bar form max width
    iAudBarMax = cmdAudStp.Left + cmdAudStp.Width
    iAudBarClp = ScaleWidth - (2 * Screen.TwipsPerPixelX) - (picEffBar.Left + picEffBar.Width + iTolButSiz + iTolButMrg)
    
    If iAudBarClp > iAudBarMax Then iAudBarClp = iAudBarMax
    If iAudBarClp < 0 Then iAudBarClp = 0

    ' Resize audio bar picture
    picAudBar.Height = iTolButSiz + iTolButMrg
    
    If (iAudBarMax > iAudBarClp) Then
	picAudBar.Left = picEffBar.Left + picEffBar.Width + iTolButSiz
	picAudBar.Width = iAudBarClp
    Else
	picAudBar.Left = ScaleWidth - (2 * Screen.TwipsPerPixelX) - iAudBarMax
	picAudBar.Width = iAudBarMax
    End If

End Sub

Sub MDIForm_Unload (Cancel As Integer)
    ' Save current window state (if not minimized)
    If (MINIMIZED <> WindowState) Then PrfSetStr PRF_SCRPOSSEC, PRF_SCRSTAKEY, WindowState
    ' Save current screen position
    If (NORMAL = WindowState) Then
	PrfSetStr PRF_SCRPOSSEC, PRF_SCRLFTKEY, Left
	PrfSetStr PRF_SCRPOSSEC, PRF_SCRTOPKEY, Top
	PrfSetStr PRF_SCRPOSSEC, PRF_SCRHGTKEY, Height
	PrfSetStr PRF_SCRPOSSEC, PRF_SCRWIDKEY, Width
    End If

    ' If the Unload was not canceled (in the QueryUnload events for the Audio Doc forms)
    ' there will be no document windows left, so go ahead and end the application.
    If (0 = AudDocCnt()) Then
	' Close any open audio devices
	AudDevSelNul
	' Delete clipboard files
	AudClpCls
	' Close Databases
	AudDocMDBCls
	End
    End If

End Sub

Sub MhTip1_SetCaption (index As Integer, controlName As String, hWnd As Integer, makeVisible As Integer, MouseX As Integer, MouseY As Integer)
  ' The tip control will try to display tips for controls
  ' that are not even visible. To prevent this from happening
  ' you must test for visibility and set the 'makeVisible' argument
  ' accordingly
  
  ' Limit the Y-axis to insure that the tip does not overlap the document window and cause
  ' a repaint every time the tip changes
    mhTip1(index).TipOffsetTop = -MouseY + 1

  Select Case LCase(controlName)
    ' file toolbar
    Case "optfilnew"
      mhTip1(index).Caption = " New"
      makeVisible = picFilBar.Visible
    Case "optfilopn"
      mhTip1(index).Caption = " Open"
      makeVisible = picFilBar.Visible
    Case "optfilsav"
      mhTip1(index).Caption = " Save"
      makeVisible = picFilBar.Visible
    
    ' edit toolbar
    Case "optedtcut"
      mhTip1(index).Caption = " Cut"
      makeVisible = picEdtBar.Visible
    Case "optedtcop"
      mhTip1(index).Caption = " Copy"
      makeVisible = picEdtBar.Visible
    Case "optedtpst"
      mhTip1(index).Caption = " Paste"
      makeVisible = picEdtBar.Visible
    Case "optedtcrp"
      mhTip1(index).Caption = " Crop"
      makeVisible = picEdtBar.Visible
    Case "optedttrm"
      mhTip1(index).Caption = " Trim Silence"
      makeVisible = picEdtBar.Visible
    Case "optedtera"
      mhTip1(index).Caption = " Erase"
      makeVisible = picEdtBar.Visible
    
    ' effects toolbar
    Case "opteffvup"
      mhTip1(index).Caption = " Volume Up"
      makeVisible = picEffBar.Visible
    Case "opteffvdn"
      mhTip1(index).Caption = " Volume Down"
      makeVisible = picEffBar.Visible
    Case "opteffvnz"
      mhTip1(index).Caption = " Normalize"
      makeVisible = picEffBar.Visible
    
    ' audio toolbar
    Case "optaudres"
      mhTip1(index).Caption = " Restart"
      makeVisible = picAudBar.Visible
    Case "optaudrew"
      mhTip1(index).Caption = " Rewind"
      makeVisible = picEffBar.Visible
    Case "optaudstp"
      mhTip1(index).Caption = " Stop"
      makeVisible = picEffBar.Visible
    Case "optaudpau"
      mhTip1(index).Caption = " Pause"
      makeVisible = picEffBar.Visible
    Case "optaudpla"
      mhTip1(index).Caption = " Play"
      makeVisible = picEffBar.Visible
    Case "optaudloo"
      mhTip1(index).Caption = " Loop"
      makeVisible = picEffBar.Visible
    Case "optaudffw"
      mhTip1(index).Caption = " Play Fast"
      makeVisible = picEffBar.Visible
    Case "optaudrec"
      mhTip1(index).Caption = " Record"
      makeVisible = picEffBar.Visible
    Case "pnlaudpos"
      mhTip1(index).Caption = " Position"
      makeVisible = picEffBar.Visible
    Case "cmdaudstp"
      mhTip1(index).Caption = " Stop"
      makeVisible = picEffBar.Visible
  End Select
End Sub

Sub mnuFExit_Click ()
    MDIForm_Unload (Cancel)
End Sub

Sub mnuFile_Click ()
    ' Global Const MSG_DEMNEWCAP = "Demo - No New"
    ' Global Const MSG_DEMOPNCAP = "Demo - No Open"
    ' Global Const MSG_DEMIMPCAP = "Demo - No Import"
    ' Global Const MSG_DEMPFMCAP = "Demo - No Paste From"
    If (0 = SesEdtDemLim(0, 0)) Then
	' Disable File New menu
	' Note: shortcut prevents changing menu
	' mnuFNew.Caption = MSG_DEMNEWCAP
	mnuFNew.Enabled = False
	' Disable File Open menu
	' Note: shortcut prevents changing menu
	' mnuFOpen.Caption = MSG_DEMOPNCAP
	mnuFOpen.Enabled = False
    End If
End Sub

Sub mnuFNew_Click ()
    ' No audio documents active; Query user with defaults from .INI
    VFEFilNew (AudDocTypFnd(PrfGetStr(PRF_AUDDOCSEC, PRF_DOCTYPKEY, ""))), True
End Sub

Sub mnuFOpen_Click ()
    VFEFilOpn "", AudDocTypFnd(PrfGetStr(PRF_AUDDOCSEC, PRF_DOCTYPKEY, "")), ""
End Sub

Sub mnuFRecent_Click (index As Integer)
    RcnFilOpn (index)
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

Sub mnuODeviceSelect_Click ()
    Dim sErrMsg As String
    sErrMsg = AudDevSel("")
    If ("" <> sErrMsg) Then MsgBox sErrMsg, MB_OK, Caption
End Sub

Sub mnuOEnvironment_Click ()
    Dim sRetVal As String
    sRetVal = FrmModShw(frmVFEMDI, frmOptEnv, "", CTR_MIDMIDNON)
End Sub

Sub mnuOptions_Click ()
    mnuODeviceSelect.Enabled = (AudDevCnt() > 0) And (Not AudDevAct())
End Sub

Sub mnuTechSupport_Click ()
  GetConHlp Me, HLP_TCHSUP
End Sub

Sub mnuView_Click ()
    mnuVToolbar.Checked = frmVFEMDI.picTolBar.Visible
    mnuVStatusLine.Checked = frmVFEMDI.ctlStaLin.Visible
End Sub

Sub mnuVStatusLine_Click ()
    ViwStaClk
End Sub

Sub mnuVToolbar_Click ()
    ViwTolClk
End Sub

Function No_EvtChk (cCtl As Control)
    No_EvtChk = Not cCtl.Enabled
End Function

Sub optAudFFW_Click (Value As Integer)
    Dim sErrMsg As String
    ' Exit if control was set without event
    If No_EvtChk(optAudFFW) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
	No_EvtSet optAudFFW, True
	Exit Sub
    End If

    ' If other audio active, terminate current audio and resubmit
    If AudDevAct() Then cmdAudStp_Click
 
    ' Set source of audio request
    Set fReqActFrm = frmVFEMDI.ActiveForm
    
    ' Request playback of active form
    sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevPla", Str$(PLAFFWDEF) & Chr$(VFEARGDEL) & Str$(0))
    
    ' Reset button if request failed
    If ("" <> sErrMsg) Then cmdAudStp_Click

End Sub

Sub optAudLoo_Click (Value As Integer)
    Dim sErrMsg As String
    ' Exit if control was set without event
    If No_EvtChk(optAudLoo) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
	No_EvtSet optAudLoo, True
	Exit Sub
    End If

    ' If other audio active, terminate current audio and resubmit
    If AudDevAct() Then cmdAudStp_Click
    
    ' Set source of audio request
    Set fReqActFrm = frmVFEMDI.ActiveForm
    
    ' Request playback of active form
    sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevPla", Str$(PLANRMDEF) & Chr$(VFEARGDEL) & Str$(PLALOODEF))
    
    ' Reset button if request failed
    If ("" <> sErrMsg) Then cmdAudStp_Click

End Sub

Sub optAudPau_Click (Value As Integer)
    Dim lLstPos As Long
    ' Exit if control was set without event
    If No_EvtChk(optAudPau) Then Exit Sub
    
    ' Disable toggle and reset focus if audio inactive
    If AudDevAct() Then
	lLstPos = AudDevPau(AudDevGet(), Not Value)
    Else
	optAudPau.Value = False
    End If

End Sub

Sub optAudPla_Click (Value As Integer)
    Dim sErrMsg As String
    ' Exit if control was set without event
    If No_EvtChk(optAudPla) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
	No_EvtSet optAudPla, True
	Exit Sub
    End If

    ' If other audio active, terminate current audio and resubmit
    If AudDevAct() Then cmdAudStp_Click
    
    ' Set source of audio request
    Set fReqActFrm = frmVFEMDI.ActiveForm
    
    ' Request playback of active form
    sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevPla", Str$(PLANRMDEF) & Chr$(VFEARGDEL) & Str$(0))
    
    ' Reset button if request failed
    If ("" <> sErrMsg) Then cmdAudStp_Click

End Sub

Sub optAudRec_Click (Value As Integer)
    Dim sErrMsg As String
    ' Exit if control was set without event
    If No_EvtChk(optAudRec) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
	No_EvtSet optAudRec, True
	Exit Sub
    End If

    ' If other audio active, terminate current audio and resubmit
    If AudDevAct() Then cmdAudStp_Click
    
    ' Set source of audio request
    Set fReqActFrm = frmVFEMDI.ActiveForm
    
    ' Request playback of active form
    sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevRec", "")
    
    ' Reset button if request failed
    If ("" <> sErrMsg) Then cmdAudStp_Click

End Sub

Sub optAudRes_Click (Value As Integer)
    Dim sErrMsg As String
    ' Exit if control was set without event
    If No_EvtChk(optAudRes) Then Exit Sub
    
    ' Exit if already down
    If (Value = False) Then Exit Sub
    
    ' Disable toggle and reset focus if audio inactive
    If AudDevAct() Then
	' Request re-start of active form
	If (False <> optAudPla) Then sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevRes", Str$(PLANRMDEF) & Chr$(VFEARGDEL) & Str$(0))
	If (False <> optAudLoo) Then sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevRes", Str$(PLANRMDEF) & Chr$(VFEARGDEL) & Str$(PLALOODEF))
	If (False <> optAudFFW) Then sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevRes", Str$(PLAFFWDEF) & Chr$(VFEARGDEL) & Str$(0))
	If ("" <> sErrMsg) Then cmdAudStp_Click
    End If
    
    ' Pop button (momentary contact), bounce focus to parent
    optAudRes.Value = False
    
End Sub

Sub optAudRew_Click (Value As Integer)
    Dim sErrMsg As String
    ' Exit if control was set without event
    If No_EvtChk(optAudRew) Then Exit Sub
    
    ' Exit if already down
    If (Value = False) Then Exit Sub
    
    ' Audio active?
    If AudDevAct() Then
	' Request rewind of active form
	If (False <> optAudPla) Then sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevRew", Str$(PLANRMDEF) & Chr$(VFEARGDEL) & Str$(0))
	If (False <> optAudLoo) Then sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevRew", Str$(PLANRMDEF) & Chr$(VFEARGDEL) & Str$(PLALOODEF))
	If (False <> optAudFFW) Then sErrMsg = FrmFunExe(fReqActFrm, "AudDocDevRew", Str$(PLAFFWDEF) & Chr$(VFEARGDEL) & Str$(0))
	If ("" <> sErrMsg) Then cmdAudStp_Click
    End If
    
    ' Pop button (momentary contact), bounce focus to parent
    optAudRew.Value = False
    
End Sub

Sub optAudStp_Click (Value As Integer)
    ' Exit if already down
    If (Value = False) Then Exit Sub
    
    ' Stop playback of current document
    cmdAudStp_Click
    
    ' Reset after operation is complete, bounce focus to parent
    optAudStp.Value = False

End Sub

Sub optEdtCop_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub
    
    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuECopy_Click", "")
    
    ' Reset after operation is complete
    optEdtCop.Value = False

End Sub

Sub optEdtCrp_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub

    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuECrop_Click", "")
    
    ' Reset after operation is complete
    optEdtCrp.Value = False

End Sub

Sub optEdtCut_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub

    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuECut_Click", "")
    
    ' Reset after operation is complete
    optEdtCut.Value = False

End Sub

Sub optEdtEra_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub

    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuEErase_Click", "")
    
    ' Reset after operation is complete
    optEdtEra.Value = False

End Sub

Sub optEdtPst_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub

    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuEPaste_Click", "")
    
    ' Reset after operation is complete
    optEdtPst.Value = False

End Sub

Sub optEdtTrm_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub

    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuETrimSilence_Click", "")
    
    ' Reset after operation is complete
    optEdtTrm.Value = False

End Sub

Sub optEffVDn_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub
    
    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuCVolumeDown_Click", "")
    
    ' Reset after operation is complete
    optEffVDn.Value = False

End Sub

Sub optEffVNz_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub
    
    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuCVNormalize_Click", "")
    
    ' Reset after operation is complete
    optEffVNz.Value = False
End Sub

Sub optEffVUp_Click (Value As Integer)
    Dim sErrMsg As String
    If (Value = False) Then Exit Sub
    
    ' Request cut of active form
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuCVolumeUp_Click", "")
    
    ' Reset after operation is complete
    optEffVUp.Value = False
End Sub

Sub optFilNew_Click (Value As Integer)
    Dim sErrMsg As String
    
    If (Value = False) Then Exit Sub
    
    If SafActDoc() Then
	' Use active document for format defaults
	sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuFNew_Click", "")
    Else
	' No audio documents active; use defaults from .INI (no query)
	VFEFilNew (AudDocTypFnd(PrfGetStr(PRF_AUDDOCSEC, PRF_DOCTYPKEY, ""))), False
    End If

    ' Reset after operation is complete
    optFilNew.Value = False
End Sub

Sub optFilOpn_Click (Value As Integer)
    Dim sErrMsg As String
    
    If (Value = False) Then Exit Sub

    If SafActDoc() Then
	' Use active document defaults
	sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuFOpen_Click", "")
    Else
	' Simulate menu selection
	mnuFOpen_Click
    End If

    ' Reset after operation is complete
    optFilOpn.Value = False

End Sub

Sub optFilSav_Click (Value As Integer)
    Dim sErrMsg As String
    
    If (Value = False) Then Exit Sub
    
    optFilSav.Value = False

    ' Save active document
    sErrMsg = FrmFunExe(frmVFEMDI.ActiveForm, "mnuFSave_Click", "")

    ' Reset after operation is complete
    optFilSav.Value = False

End Sub

Sub picAudBar_Paint ()
    Dim iBrdSiz As Integer
    
    ' Draw option buttons
    optAudRes.Left = 0
    optAudRew.Left = optAudRes.Left + iTolButSiz
    optAudStp.Left = optAudRew.Left + iTolButSiz
    optAudPau.Left = optAudStp.Left + iTolButSiz
    optAudPla.Left = optAudPau.Left + iTolButSiz
    optAudLoo.Left = optAudPla.Left + iTolButSiz
    optAudFFW.Left = optAudLoo.Left + iTolButSiz

    pnlAudPos.Left = optAudFFW.Left + iTolButSiz
    pnlAudPos.Height = iTolButSiz - (1 * Screen.TwipsPerPixelY)
    pnlAudPos.Top = Screen.TwipsPerPixelY

    optAudRec.Left = pnlAudPos.Left + pnlAudPos.Width

    ' Draw Stop button
    cmdAudStp.Height = iTolButSiz
    cmdAudStp.Left = optAudRec.Left + optAudRec.Width


End Sub

Sub picEdtBar_Paint ()
    Dim sErrMsg As String
    
    ' Draw edit buttons
    optEdtCop.Left = optEdtCut.Left + iTolButSiz
    
    optEdtPst.Left = optEdtCop.Left + iTolButSiz
    optEdtCrp.Left = optEdtPst.Left + iTolButSiz
    optEdtTrm.Left = optEdtCrp.Left + iTolButSiz
    
    optEdtEra.Left = optEdtTrm.Left + iTolButSiz
    picEdtBar.Height = iTolButSiz + iTolButMrg
    picEdtBar.Width = optEdtEra.Left + iTolButSiz
End Sub

Sub picEffBar_Paint ()
    ' Paint effects buttons
    optEffVDn.Left = optEffVUp.Left + iTolButSiz
    optEffVNz.Left = optEffVDn.Left + iTolButSiz
    picEffBar.Height = iTolButSiz + iTolButMrg
    picEffBar.Width = optEffVNz.Left + iTolButSiz
End Sub

Sub picFilBar_Paint ()
    ' Paint file buttons
    optFilOpn.Left = optFilNew.Left + iTolButSiz
    optFilSav.Left = optFilOpn.Left + iTolButSiz
    picFilBar.Height = iTolButSiz + iTolButMrg
    picFilBar.Width = optFilSav.Left + iTolButSiz
End Sub

Sub sbcElaTim_WndMessage (wnd As Integer, msg As Integer, wp As Integer, lp As Long, retval As Long, nodef As Integer)
    Static sDesStr As String
    Static lLstTim As Long
    Dim iRetCod As Integer
    
    ' Initialize activity description string & start time
    If (LNGPOLBEG = wp) Then
	sDesStr = CIFGetStr(CInt(lp), "Working") & "... "
	pnlAudPos.Caption = DblRndAsc(0, DECPRCDEF)
	lLstTim = 0
	lp = 0
    End If
    
    ' Update displays if time has changed & update last time setting
    If (lLstTim <> lp) Then
	LvlPolPct wp, sDesStr, AudDevRecLvl(AudDevGet(), RECLVLTIM)
	pnlAudPos.Caption = DblRndAsc(lp / 1000!, DECPRCDEF)
	lLstTim = lp
    End If

    ' Stop if buffers are empty
    If (LNGPOLEMP = wp) Then
	cmdAudStp_Click
    End If
    
    If (LNGPOLEND = wp) Then
	LvlPolPct wp, "", 0
    End If
    
    ' Return TRUE to continue processing
    retval = True
End Sub

Sub sbcLngPol_WndMessage (wnd As Integer, msg As Integer, wp As Integer, lp As Long, retval As Long, nodef As Integer)
    Static sDesStr As String
    AudDocLngPol Me, sDesStr, wnd, msg, wp, lp, retval, nodef
End Sub

Sub VerModUse ()
    ' Verify that the version of components loaded in memory is same as installed on disk
    ' DLL's used
    VerifyModule App.Path & "\DWSpyDLL.DLL"
    VerifyModule App.Path & "\MhRun400.DLL"
    VerifyModule App.Path & "\MSAJT112.DLL"   ' Called by VBDB300
    VerifyModule App.Path & "\MSAJT200.DLL"   ' Called by MSAJT112
    VerifyModule App.Path & "\VBDB300.DLL"
    VerifyModule App.Path & "\VFECIF.DLL"

    ' VBX's used
    VerifyModule App.Path & "\Chart2FX.VBX"
    VerifyModule App.Path & "\MhGMul.VBX"
    VerifyModule App.Path & "\MhSL200.VBX"
    VerifyModule App.Path & "\MhTip.VBX"
    VerifyModule App.Path & "\MSOutlin.VBX"
    VerifyModule App.Path & "\SBC.VBX"
    VerifyModule App.Path & "\Spin.VBX"
    VerifyModule App.Path & "\ThreeD.VBX"
End Sub

Sub VFEMDIMenUpd (iDocDecCnt As Integer)
    ' Update file menu entries
    mnuFile_Click

    If (0 <> (AudDocCnt() - iDocDecCnt)) Then
	' Make sure toolbar buttons are visible
	picEdtBar.Visible = True
	picEffBar.Visible = True
	optFilSav.Enabled = True
	' Display audio bar (if device is active)
	SetAudBar (True)
	' Update toolbar controls
	optFilSav.Enabled = frmVFEMDI.ActiveForm.mnuFSave.Enabled
	optEdtCut.Enabled = frmVFEMDI.ActiveForm.mnuEdit And frmVFEMDI.ActiveForm.mnuECut.Enabled
	optEdtCrp.Enabled = frmVFEMDI.ActiveForm.mnuEdit And frmVFEMDI.ActiveForm.mnuECrop.Enabled
	optEdtCop.Enabled = frmVFEMDI.ActiveForm.mnuEdit And frmVFEMDI.ActiveForm.mnuECopy.Enabled
	optEdtPst.Enabled = frmVFEMDI.ActiveForm.mnuEdit And frmVFEMDI.ActiveForm.mnuEPaste.Enabled
	optEdtTrm.Enabled = frmVFEMDI.ActiveForm.mnuEdit And frmVFEMDI.ActiveForm.mnuETrimSilence.Enabled
	optEdtEra.Enabled = frmVFEMDI.ActiveForm.mnuEdit And frmVFEMDI.ActiveForm.mnuEErase.Enabled
	optEffVUp.Enabled = frmVFEMDI.ActiveForm.mnuEffects.Enabled
	optEffVDn.Enabled = frmVFEMDI.ActiveForm.mnuEffects.Enabled
	optEffVNz.Enabled = frmVFEMDI.ActiveForm.mnuEffects.Enabled
	' Set focus to stop button for space termination
	If (cmdAudStp.Visible) Then SafFocCtl Me, cmdAudStp
    Else
	' Update toolbar controls
	picEdtBar.Visible = False
	picEffBar.Visible = False
	optFilSav.Enabled = False
	' Hide audio bar
	SetAudBar (False)
    End If

End Sub

