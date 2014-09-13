VERSION 2.00
Begin Form frmEdtCfg 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Edit Configure"
   ClientHeight    =   1572
   ClientLeft      =   1920
   ClientTop       =   2148
   ClientWidth     =   4920
   Height          =   1944
   KeyPreview      =   -1  'True
   Left            =   1896
   LinkTopic       =   "Form1"
   ScaleHeight     =   1572
   ScaleWidth      =   4920
   Top             =   1800
   Width           =   4968
   Begin SSFrame grpTrmSil 
      Caption         =   "&Trim Silence"
      ForeColor       =   &H00000000&
      Height          =   1092
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3372
      Begin TextBox edtGrdTim 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   2160
         TabIndex        =   4
         Text            =   "0"
         Top             =   600
         Width           =   855
      End
      Begin SpinButton spnGrdTim 
         Height          =   315
         Left            =   3000
         Top             =   600
         Width           =   255
      End
      Begin TextBox edtSndThr 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   2160
         TabIndex        =   2
         Text            =   "0"
         Top             =   240
         Width           =   855
      End
      Begin SpinButton spnSndThr 
         Height          =   315
         Left            =   3000
         Top             =   240
         Width           =   255
      End
      Begin Label lblGrdTim 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Guard Time (sec):"
         Height          =   252
         Left            =   120
         TabIndex        =   3
         Top             =   660
         Width           =   1692
      End
      Begin Label lblSndThr 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Threshold (%Max):"
         Height          =   252
         Left            =   120
         TabIndex        =   1
         Top             =   300
         Width           =   1692
      End
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3600
      TabIndex        =   7
      Top             =   1080
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3600
      TabIndex        =   6
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3600
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Const ALLPCTINC = 1             ' All percent increment
Const ALLPCTMIN = 0             ' All percent minimum
Const ALLPCTMAX = 100           ' All percent maximum
Const ALLPCTFMT = "#0.0"        ' All percent display format

Const ALLSECINC = 1             ' All seconds increment
Const ALLSECMIN = 0             ' All seconds minimum
Const ALLSECMAX = 1000000       ' All seconds maximum
Const ALLSECFMT = "#0.0"        ' All seconds display format

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Verify valid edit parameter entries
    If EdtRngBad(edtSndThr, ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtGrdTim, ALLSECMIN, ALLSECMAX) Then Exit Sub
    
    ' Save settings
    PrfSetStr PRF_EDTCFGSEC, PRF_TRMTHRKEY, edtSndThr
    PrfSetStr PRF_EDTCFGSEC, PRF_TRMGRDKEY, edtGrdTim
    
    ' Return
    FrmModRet Me, ""
    
End Sub

Sub edtGrdTim_GotFocus ()
    EdtTxtSel edtGrdTim
End Sub

Sub edtGrdTim_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnGrdTim_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnGrdTim_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtGrdTim.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtSndThr_GotFocus ()
    EdtTxtSel edtSndThr
End Sub

Sub edtSndThr_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnSndThr_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnSndThr_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtSndThr.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_EDTCFG

    ' Retrieve current defaults
    edtSndThr = PrfGetStr(PRF_EDTCFGSEC, PRF_TRMTHRKEY, Str$(TRMTHRDEF))
    edtGrdTim = PrfGetStr(PRF_EDTCFGSEC, PRF_TRMGRDKEY, Str$(TRMGRDDEF))
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub spnGrdTim_SpinDown ()
    EdtBoxSpn edtGrdTim, -ALLSECINC, ALLSECMIN, ALLSECMAX, ALLSECFMT
End Sub

Sub spnGrdTim_SpinUp ()
    EdtBoxSpn edtGrdTim, ALLSECINC, ALLSECMIN, ALLSECMAX, ALLSECFMT
End Sub

Sub spnSndThr_SpinDown ()
    EdtBoxSpn edtSndThr, -ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnSndThr_SpinUp ()
    EdtBoxSpn edtSndThr, ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

