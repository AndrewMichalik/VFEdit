VERSION 2.00
Begin Form frmEffEqu 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Frequency Equalizer"
   ClientHeight    =   5160
   ClientLeft      =   744
   ClientTop       =   1116
   ClientWidth     =   4464
   ControlBox      =   0   'False
   FillColor       =   &H00C0C0C0&
   Height          =   5532
   KeyPreview      =   -1  'True
   Left            =   720
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5160
   ScaleWidth      =   4464
   Top             =   768
   Width           =   4512
   Begin SSPanel pnlAnaGph 
      BevelInner      =   2  'Raised
      BevelOuter      =   0  'None
      BorderWidth     =   2
      Height          =   4935
      Left            =   4440
      TabIndex        =   19
      Top             =   120
      Width           =   4575
      Begin ChartFX20 cfxAnaGph 
         Prop10          =   ""
         BorderStyle     =   0  'None
         BottomGap       =   50
         DblClkDlg       =   1  'Dialog
         FixedGap        =   2
         Font            =   EFFEQU.FRX:0000
         GalleryTool     =   8255
         Grid            =   0  'None
         Height          =   4695
         Left            =   120
         LeftGap         =   64
         LineBkColor     =   &H00000000&
         LineColor       =   &H00000000&
         LineStyle       =   0  'Solid
         LineWidth       =   1
         MarkerSize      =   3
         MarkerVolume    =   75
         OpenData        =   EFFEQU.FRX:0050
         PointType       =   2  'Circle
         RGB2DBk         =   &H00C0C0C0&
         RGB3DBk         =   &H00FFFFFF&
         RGBBarHorz      =   &H00FFFF00&
         RGBBk           =   &H00C0C0C0&
         RigClkDlg       =   2  'None
         RightGap        =   26
         Scheme          =   0  'Solid
         Shape           =   0
         Stacked         =   0  'None
         ThisColor       =   EFFEQU.FRX:00E2
         TitleDlg        =   EFFEQU.FRX:0168
         Top             =   120
         TopGap          =   33
         Type            =   541962
         VertGridGap     =   1
         View3DDepth     =   65
         View3DLight     =   -1  'True
         ViewRot3D       =   EFFEQU.FRX:01F8
         WallWidth       =   4
         Width           =   4335
      End
   End
   Begin SSPanel pnlFrqEqu 
      BevelInner      =   2  'Raised
      BevelOuter      =   0  'None
      BorderWidth     =   2
      Height          =   3132
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4212
      Begin SSFrame grpEquBnd 
         ForeColor       =   &H00000000&
         Height          =   2892
         Left            =   120
         TabIndex        =   1
         Top             =   120
         Width           =   3972
         Begin CommandButton cmdEquRes 
            Caption         =   "Reset"
            Height          =   252
            Left            =   120
            TabIndex        =   13
            Top             =   2520
            Width           =   732
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   0
            LargeDown       =   10
            LargeUp         =   10
            Left            =   120
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:01FE
            Style           =   0  'Vertical
            TabIndex        =   2
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   1
            LargeDown       =   10
            LargeUp         =   10
            Left            =   600
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:0488
            Style           =   0  'Vertical
            TabIndex        =   3
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   2
            LargeDown       =   10
            LargeUp         =   10
            Left            =   1080
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:0712
            Style           =   0  'Vertical
            TabIndex        =   4
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   3
            LargeDown       =   10
            LargeUp         =   10
            Left            =   1560
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:099C
            Style           =   0  'Vertical
            TabIndex        =   5
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   4
            LargeDown       =   10
            LargeUp         =   10
            Left            =   2040
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:0C26
            Style           =   0  'Vertical
            TabIndex        =   6
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   5
            LargeDown       =   10
            LargeUp         =   10
            Left            =   2520
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:0EB0
            Style           =   0  'Vertical
            TabIndex        =   7
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   6
            LargeDown       =   10
            LargeUp         =   10
            Left            =   3000
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:113A
            Style           =   0  'Vertical
            TabIndex        =   8
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin MhSlide ctlEquBnd 
            BackColor       =   &H00C0C0C0&
            ForeColor       =   &H00C0C0C0&
            Height          =   2172
            Index           =   7
            LargeDown       =   10
            LargeUp         =   10
            Left            =   3480
            Max             =   100
            Min             =   0
            PictureSlide    =   EFFEQU.FRX:13C4
            Style           =   0  'Vertical
            TabIndex        =   9
            Top             =   120
            Value           =   50
            Width           =   372
         End
         Begin Label lblFrqRng 
            Alignment       =   1  'Right Justify
            BackColor       =   &H00C0C0C0&
            Caption         =   "1"
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   7.8
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   255
            Index           =   2
            Left            =   3000
            TabIndex        =   12
            Top             =   2280
            Width           =   855
         End
         Begin Label lblFrqRng 
            Alignment       =   2  'Center
            BackColor       =   &H00C0C0C0&
            Caption         =   ".5"
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   7.8
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   255
            Index           =   1
            Left            =   1560
            TabIndex        =   11
            Top             =   2280
            Width           =   855
         End
         Begin Label lblFrqRng 
            BackColor       =   &H00C0C0C0&
            Caption         =   "0"
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   7.8
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   10
            Top             =   2280
            Width           =   855
         End
      End
   End
   Begin CommandButton cmdEffEqu 
      Caption         =   "Equalize"
      Height          =   375
      Left            =   360
      TabIndex        =   14
      Top             =   3360
      Width           =   1215
   End
   Begin CommandButton cmdGphShw 
      Caption         =   "Show >>"
      Height          =   375
      Left            =   2880
      TabIndex        =   15
      Top             =   3360
      Width           =   1215
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   360
      TabIndex        =   17
      Top             =   4560
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   2880
      TabIndex        =   16
      Top             =   4080
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2880
      TabIndex        =   18
      Top             =   4560
      Width           =   1215
   End
End

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Frequency Equalizer / Analyzer variables
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim pDocSesEdt As Long                  ' Document session edit
Dim lAudSmpOff As Long                  ' Audio sample offset
Dim lAudSmpLen As Long                  ' Audio sample len

Dim iAnaFFTPts As Integer               ' Analyzer FFT size (frequency points)
Dim lAnaCmpCnt As Long                  ' Equalizer band completion count

Const EQUBNDMAX = 100#                  ' Equalizer band maximum

Sub BsyEnaSet (bEnaFlg As Integer)
    ' Don't disable whole form (allows Ctrl-C break processing)
    cmdEffEqu.Enabled = bEnaFlg And (0 <> lAudSmpLen)
    cmdGphShw.Enabled = bEnaFlg And (0 <> lAudSmpLen)
    CmdOK.Enabled = bEnaFlg
    cmdCancel.Enabled = bEnaFlg
    cmdHlpBut.Enabled = bEnaFlg
End Sub

Sub cfxAnaGph_GetLegend (bYLegend As Integer, nRes As Integer)
    ' Force Y axis zero legend to blank
    If (bYLegend = 1) Then
        If (0 = Val(cfxAnaGph.HText)) Then
            cfxAnaGph.HText = ""
            nRes = 1
        End If
    End If
End Sub

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdEffEqu_Click ()
    Dim iRetCod As Integer
    Dim ii As Integer
    
    ReDim fEquArr(EQUBNDCNT - 1) As Single

    ' Read equalizer settings
    ' Note: The slide range is from 0 (top) to 100 (bottom), max range is +/-12 dB
    For ii = 0 To EQUBNDCNT - 1 Step 1
        fEquArr(ii) = EquBndTodB(ctlEquBnd(ii).Value)
    Next ii

    ' Compute equalized value (disable form during processing)
    BsyEnaSet False
    iRetCod = SesEffFrqEqu(pDocSesEdt, lAudSmpOff, lAudSmpLen, EQUFFTORD, fEquArr(0), EQUBNDCNT, EQUGAIDEF, "Equalizer")
    BsyEnaSet True

    ' Set focus on graph controls
    cfxAnaGph.SetFocus

End Sub

Sub cmdEquRes_Click ()
    Dim ii
    ' Reset equalizer settings
    For ii = 0 To EQUBNDCNT - 1
        ctlEquBnd(ii).Value = EQUBNDMAX / 2
    Next ii

End Sub

Sub cmdGphShw_Click ()
    Dim fSumCnt As Single
    Dim lTimPnt As Long
    Dim iRetCod As Integer
    Dim iPltArr() As Integer
    Dim ii As Integer
    Dim jj As Integer

    ' Assume default band slice count
    lTimPnt = ANATIMDEF
    
    ' Compute number of power sums per default graph time slice
    fSumCnt = lAudSmpLen / (iAnaFFTPts * ANATIMDEF)
    If (fSumCnt < 1) Then fSumCnt = 1
    
    ' Re-compute number of time points
    lTimPnt = Max(lAudSmpLen / (iAnaFFTPts * fSumCnt), 1)

    ' Allocate space for spectrum power plot
    ' Note: VB stores multi-dimensional arrays different from 'C'
    ReDim iPltArr((lTimPnt * iAnaFFTPts) - 1)

    ' Compute power spectrum graph points (disable form during processing)
    BsyEnaSet False
    iRetCod = SesEffShwFrq(SesEdtFil(pDocSesEdt), lAudSmpOff, ANAFFTORD, fSumCnt, iPltArr(0), lTimPnt, lAnaCmpCnt)
    BsyEnaSet True

    ' Successful computation?
    If (0 <> iRetCod) Then
        Beep
        Exit Sub
    End If

    ' Re-size to make graph visible; set right margin = left
    Me.Width = pnlAnaGph.Left + pnlAnaGph.Width + 2 * grpEquBnd.Left

    ' Open the VALUE channel and allocate iTimPnt Series and iAnaFFTPts points
    ' Note: Chart uses 'C' style array dimensions
    cfxAnaGph.OpenData(COD_VALUES) = CHART_ML(CInt(lTimPnt), iAnaFFTPts)
    For ii = 0 To lTimPnt - 1 Step 1
        cfxAnaGph.ThisSerie = ii
        For jj = 0 To iAnaFFTPts - 1 Step 1
            cfxAnaGph.Value(jj) = iPltArr((ii * iAnaFFTPts) + jj)
        Next jj
    Next ii
    cfxAnaGph.CloseData(COD_VALUES) = 0

    ' Set focus on graph controls
    cfxAnaGph.SetFocus

End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    Dim ii
    ' Read last equalizer settings
    For ii = 0 To EQUBNDCNT - 1
        PrfSetStr PRF_EFFCFGSEC, PRF_EQUBNDKEY & ii, DblRndAsc(EquBndTodB(ctlEquBnd(ii).Value), 1)
    Next ii

    FrmModRet Me, ""

End Sub

Function EquBndTodB (ByVal iBndPct As Integer) As Single
    ' Note: The slide appears to go from 0 (top) to 100 (bottom), max range is +/-12 dB
    Dim fdB As Single
    fdB = EQUSLDRNG * (.5 - (iBndPct / EQUBNDMAX))
    fdB = Min(fdB, EQUSLDRNG)
    fdB = Max(fdB, -EQUSLDRNG)
    EquBndTodB = fdB
End Function

Function EqudBToBnd (fdB As Single) As Integer
    ' Note: The slide appears to go from 0 (top) to 100 (bottom), max range is +/-12 dB
    fdB = Min(fdB, EQUSLDRNG)
    fdB = Max(fdB, -EQUSLDRNG)
    EqudBToBnd = EQUBNDMAX * (.5 - (fdB / EQUSLDRNG))
End Function

Sub Form_Activate ()
    Dim sInpArg As String
    Dim ii As Integer

    ' Retrieve input arguments from tag
    sInpArg = tag

    ' Set caption
    Caption = MSG_EFFEQUCAP
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Retrieve session file pointer
    pDocSesEdt = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Retrieve sample offset and count
    lAudSmpOff = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    lAudSmpLen = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Assume default frequency bins
    iAnaFFTPts = ANAFFTORD ^ 2

    ' Set the ToolBar styles
    cfxAnaGph.ToolStyle(CTOOL_TB) = 0
    cfxAnaGph.ToolStyle(CTOOL_TB Or CTOOL_OPTIONS) = CHART_TBSTANDARD

    ' Set the Y axis style
    cfxAnaGph.LegStyle = CL_GETLEGEND Or CL_NOTCLIPPED

    ' Turn off all graph points
    cfxAnaGph.OpenData(COD_VALUES) = CHART_ML(1, 1)
    cfxAnaGph.ThisSerie = 0
    cfxAnaGph.Value(0) = 0
    cfxAnaGph.CloseData(COD_VALUES) = 0

    ' Initialize equalizer frequency range legend
    lblFrqRng(0) = "0"
    lblFrqRng(1) = DblRndAsc((AudFilSmpFrq(SesEdtFil(pDocSesEdt)) / 4) / 1000#, 1)
    lblFrqRng(2) = DblRndAsc((AudFilSmpFrq(SesEdtFil(pDocSesEdt)) / 2) / 1000#, 1)

    ' Initialize analyzer frequency range legend
    cfxAnaGph.KeyLeg(0) = 0
    cfxAnaGph.KeyLeg(iAnaFFTPts / 2) = lblFrqRng(1)
    cfxAnaGph.KeyLeg(iAnaFFTPts - 1) = lblFrqRng(2) & " kHz"

    ' Inhibit graph update if no data available
    cmdEffEqu.Enabled = (0 <> lAudSmpLen)
    cmdGphShw.Enabled = (0 <> lAudSmpLen)

    ' Read last equalizer settings
    For ii = 0 To EQUBNDCNT - 1
        ctlEquBnd(ii).Value = EqudBToBnd(Val(PrfGetStr(PRF_EFFCFGSEC, PRF_EQUBNDKEY & ii, "")))
    Next ii

End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    ' Insure that it is safe to exit
    If (KeyChkEsc(KeyAscii) And (True = cmdCancel.Enabled)) Then Call cmdCancel_Click
End Sub

Sub Form_Load ()
    HelpContextID = HLP_EFFEQU
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

