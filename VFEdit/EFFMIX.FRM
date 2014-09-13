VERSION 2.00
Begin Form frmEffMix 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Edit Mix"
   ClientHeight    =   3000
   ClientLeft      =   1116
   ClientTop       =   1488
   ClientWidth     =   7080
   Height          =   3372
   KeyPreview      =   -1  'True
   Left            =   1092
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3000
   ScaleWidth      =   7080
   Top             =   1140
   Width           =   7128
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   5760
      TabIndex        =   16
      Top             =   2520
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5760
      TabIndex        =   15
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   5760
      TabIndex        =   14
      Top             =   120
      Width           =   1215
   End
   Begin SSFrame grpTrk000 
      Caption         =   "Track &1"
      ForeColor       =   &H00000000&
      Height          =   1335
      Index           =   1
      Left            =   120
      TabIndex        =   7
      Top             =   1560
      Width           =   5535
      Begin CommandButton cmdFilNam 
         Caption         =   "&Browse"
         Height          =   315
         Index           =   1
         Left            =   2760
         TabIndex        =   9
         Top             =   300
         Width           =   1215
      End
      Begin SpinButton spnMixLvl 
         Height          =   315
         Index           =   1
         Left            =   5160
         Top             =   660
         Width           =   255
      End
      Begin TextBox edtMixLvl 
         Alignment       =   2  'Center
         Height          =   312
         Index           =   1
         Left            =   4200
         TabIndex        =   12
         Text            =   "0"
         Top             =   660
         Width           =   972
      End
      Begin TextBox edtFilNam 
         Height          =   315
         Index           =   1
         Left            =   120
         TabIndex        =   11
         Top             =   660
         Width           =   3855
      End
      Begin Label lblMixLvl 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Mix &Level (%):"
         Height          =   240
         Index           =   1
         Left            =   4200
         TabIndex        =   10
         Top             =   360
         Width           =   1212
      End
      Begin Label lblFilFmt 
         BackColor       =   &H00C0C0C0&
         Caption         =   "File Format"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   13
         Top             =   1020
         Width           =   4455
      End
      Begin Label lblFilNam 
         BackColor       =   &H00C0C0C0&
         Caption         =   "File &Name:"
         Height          =   240
         Index           =   1
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   1200
      End
   End
   Begin SSFrame grpTrk000 
      Caption         =   "Track &0"
      ForeColor       =   &H00000000&
      Height          =   1335
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   60
      Width           =   5535
      Begin CommandButton cmdFilNam 
         Caption         =   "&Browse"
         Enabled         =   0   'False
         Height          =   315
         Index           =   0
         Left            =   2760
         TabIndex        =   2
         Top             =   300
         Visible         =   0   'False
         Width           =   1215
      End
      Begin TextBox edtFilNam 
         Enabled         =   0   'False
         Height          =   312
         Index           =   0
         Left            =   120
         TabIndex        =   4
         Top             =   660
         Width           =   3852
      End
      Begin TextBox edtMixLvl 
         Alignment       =   2  'Center
         Height          =   312
         Index           =   0
         Left            =   4200
         TabIndex        =   5
         Text            =   "0"
         Top             =   660
         Width           =   972
      End
      Begin SpinButton spnMixLvl 
         Height          =   315
         Index           =   0
         Left            =   5160
         Top             =   660
         Width           =   255
      End
      Begin Label lblFilNam 
         BackColor       =   &H00C0C0C0&
         Caption         =   "File &Name:"
         Height          =   240
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   1200
      End
      Begin Label lblFilFmt 
         BackColor       =   &H00C0C0C0&
         Caption         =   "File Format"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   6
         Top             =   1020
         Width           =   4455
      End
      Begin Label lblMixLvl 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Mix &Level (%):"
         Height          =   240
         Index           =   0
         Left            =   4200
         TabIndex        =   3
         Top             =   360
         Width           =   1212
      End
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const MAXMIXCNT = 2             ' Maximum number of mix files


Dim tFilDocTyp() As VFEDOCTYP   ' Current file document type
Dim pDocSesEdt As Long          ' Document session edit
Dim lAudSmpOff As Long          ' Audio sample offset
Dim lAudSmpLen As Long          ' Audio sample len

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const ALLPCTINC = 1             ' All percent increment
Const ALLPCTMIN = 1             ' All percent minimum
Const ALLPCTMAX = 100           ' All percent maximum
Const ALLPCTFMT = "#0"          ' All percent display format

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdFilNam_Click (Index As Integer)
    Dim sFilNam As String
    
    ' Ask user for file name
    sFilNam = VFEFilMix(tFilDocTyp(Index))
    If ("" = sFilNam) Then Exit Sub

    ' Fill in file name
    edtFilNam(Index) = sFilNam
    lblFilFmt(Index) = AudDocTypTxt(tFilDocTyp(Index))

End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Verify valid entries
    If EdtRngBad(edtMixLvl(0), ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtMixLvl(1), ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If (0 = Len(edtFilNam(1))) Then
        edtFilNam(1).SetFocus
        Beep
        Exit Sub
    End If

    ' Save level settings
    PrfSetStr PRF_MIXFRMSEC, PRF_MIXL00KEY, edtMixLvl(0)
    PrfSetStr PRF_MIXFRMSEC, PRF_MIXL01KEY, edtMixLvl(1)
    
    ' Save file settings
    PrfSetStr PRF_MIXFRMSEC, PRF_MIXF01KEY, edtFilNam(1) & Chr$(VFEARGDEL) & TypDocToStr(tFilDocTyp(1))
    
    ' Return entered full file name, document type and mix level
    FrmModRet Me, edtFilNam(1) & Chr$(VFEARGDEL) & TypDocToStr(tFilDocTyp(1)) & Chr$(VFEARGDEL) & edtMixLvl(0) & Chr$(VFEARGDEL) & edtMixLvl(1)

End Sub

Sub edtMixLvl_GotFocus (Index As Integer)
    EdtTxtSel edtMixLvl(Index)
End Sub

Sub edtMixLvl_KeyDown (Index As Integer, KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnMixLvl_SpinUp (Index)
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnMixLvl_SpinDown (Index)
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtMixLvl(Index).SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_Activate ()
    Dim sInpArg As String
    
    ' Retrieve input arguments from tag
    sInpArg = tag

    ' Set Caption
    Caption = MSG_EFFMIXCAP
    
    ' Yield to complete re-paints
    DoEvents

    ' Parse for file name
    edtFilNam(0) = StrTokStr(sInpArg, Chr$(VFEARGDEL))
    edtFilNam(0).Enabled = False

    ' Parse for previously selected document type
    TypStrToDoc sInpArg, tFilDocTyp(0)

    ' Update format description
    lblFilFmt(0) = AudDocTypTxt(tFilDocTyp(0))
  
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_EDTMIX
    Dim sXfrArg As String

    ' Create document array
    ReDim tFilDocTyp(MAXMIXCNT - 1) As VFEDOCTYP
    
    ' Retrieve default mix levels
    edtMixLvl(0) = PrfGetStr(PRF_MIXFRMSEC, PRF_MIXL00KEY, Str$(MIXLVLDEF))
    edtMixLvl(1) = PrfGetStr(PRF_MIXFRMSEC, PRF_MIXL01KEY, Str$(MIXLVLDEF))
    
    ' Retrieve default mix file
    sXfrArg = PrfGetStr(PRF_MIXFRMSEC, PRF_MIXF01KEY, "")
    edtFilNam(1) = StrTokStr(sXfrArg, Chr$(VFEARGDEL))
    TypStrToDoc sXfrArg, tFilDocTyp(1)
    lblFilFmt(1) = AudDocTypTxt(tFilDocTyp(1))
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub spnMixLvl_SpinDown (Index As Integer)
    EdtBoxSpn edtMixLvl(Index), -ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnMixLvl_SpinUp (Index As Integer)
    EdtBoxSpn edtMixLvl(Index), ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

