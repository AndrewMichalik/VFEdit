VERSION 2.00
Begin Form frmEffCfg 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Effects Configure"
   ClientHeight    =   4920
   ClientLeft      =   300
   ClientTop       =   1092
   ClientWidth     =   6600
   Height          =   5292
   KeyPreview      =   -1  'True
   Left            =   276
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4920
   ScaleWidth      =   6600
   Top             =   744
   Width           =   6648
   Begin SSFrame grpFadOut 
      Caption         =   "Fade &Out"
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   120
      TabIndex        =   13
      Top             =   3720
      Width           =   3135
      Begin TextBox edtFdOEnd 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   17
         Text            =   "0"
         Top             =   720
         Width           =   855
      End
      Begin SpinButton spnFdOEnd 
         Height          =   315
         Left            =   2760
         Top             =   720
         Width           =   255
      End
      Begin TextBox edtFdOBeg 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   15
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin SpinButton spnFdOBeg 
         Height          =   315
         Left            =   2760
         Top             =   300
         Width           =   255
      End
      Begin Label lblFdOEnd 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Stop Level (dB):"
         Height          =   252
         Left            =   120
         TabIndex        =   16
         Top             =   780
         Width           =   1692
      End
      Begin Label lblFdOBeg 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Start Level (dB):"
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   360
         Width           =   1695
      End
   End
   Begin SSFrame grpEchLvl 
      Caption         =   "&Echo"
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   120
      TabIndex        =   3
      Top             =   1320
      Width           =   3135
      Begin SpinButton spnEchDly 
         Height          =   315
         Left            =   2760
         Top             =   300
         Width           =   255
      End
      Begin TextBox edtEchDly 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   5
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin SpinButton spnEchDcy 
         Height          =   315
         Left            =   2760
         Top             =   720
         Width           =   255
      End
      Begin TextBox edtEchDcy 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   7
         Text            =   "0"
         Top             =   720
         Width           =   855
      End
      Begin Label lblEchDly 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Delay Time (sec):"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   360
         Width           =   1695
      End
      Begin Label lblEchDcy 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Decay (dB):"
         Height          =   252
         Left            =   120
         TabIndex        =   6
         Top             =   780
         Width           =   1692
      End
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3480
      TabIndex        =   34
      Top             =   4440
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   5160
      TabIndex        =   33
      Top             =   3840
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5160
      TabIndex        =   35
      Top             =   4440
      Width           =   1215
   End
   Begin SSFrame grpFad_In 
      Caption         =   "Fade &In"
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   120
      TabIndex        =   8
      Top             =   2520
      Width           =   3135
      Begin SpinButton spnFdIBeg 
         Height          =   315
         Left            =   2760
         Top             =   300
         Width           =   255
      End
      Begin TextBox edtFdIBeg 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   10
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin SpinButton spnFdIEnd 
         Height          =   315
         Left            =   2760
         Top             =   720
         Width           =   255
      End
      Begin TextBox edtFdIEnd 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   12
         Text            =   "0"
         Top             =   720
         Width           =   855
      End
      Begin Label lblFdIBeg 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Start Level (dB):"
         Height          =   252
         Left            =   120
         TabIndex        =   9
         Top             =   360
         Width           =   1692
      End
      Begin Label lblFdIEnd 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Stop Level (dB):"
         Height          =   252
         Left            =   120
         TabIndex        =   11
         Top             =   720
         Width           =   1692
      End
   End
   Begin SSFrame grpVolAdj 
      Caption         =   "&Volume Adjust"
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   3360
      TabIndex        =   28
      Top             =   2520
      Width           =   3135
      Begin SpinButton spnVol_Up 
         Height          =   315
         Left            =   2760
         Top             =   300
         Width           =   255
      End
      Begin TextBox edtVol_Up 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   30
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin TextBox edtVolDwn 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   32
         Text            =   "0"
         Top             =   720
         Width           =   855
      End
      Begin SpinButton spnVolDwn 
         Height          =   315
         Left            =   2760
         Top             =   720
         Width           =   255
      End
      Begin Label lblVolDwn 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Down (dB):"
         Height          =   252
         Left            =   120
         TabIndex        =   31
         Top             =   780
         Width           =   1692
      End
      Begin Label lblVol_Up 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Up (dB):"
         Height          =   252
         Left            =   120
         TabIndex        =   29
         Top             =   360
         Width           =   1692
      End
   End
   Begin SSFrame grpNrmLvl 
      Caption         =   "&Normalize"
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   3360
      TabIndex        =   18
      Top             =   120
      Width           =   3135
      Begin TextBox edtNrmExc 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   22
         Text            =   "0"
         Top             =   720
         Width           =   855
      End
      Begin SpinButton spnNrmExc 
         Height          =   315
         Left            =   2760
         Top             =   720
         Width           =   255
      End
      Begin SpinButton spnNrmLvl 
         Height          =   315
         Left            =   2760
         Top             =   300
         Width           =   255
      End
      Begin TextBox edtNrmLvl 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   20
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin Label lblNrmExc 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Over (%Total):"
         Height          =   252
         Left            =   120
         TabIndex        =   21
         Top             =   780
         Width           =   1692
      End
      Begin Label lblNrmLvl 
         BackColor       =   &H00C0C0C0&
         Caption         =   "To (%Max):"
         Height          =   255
         Left            =   120
         TabIndex        =   19
         Top             =   360
         Width           =   1695
      End
   End
   Begin SSFrame grpCmpExp 
      Caption         =   "D&ynamic Compress/Expand"
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3135
      Begin TextBox edtDCEMax 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   2
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin SpinButton spnDCEMax 
         Height          =   315
         Left            =   2760
         Top             =   300
         Width           =   255
      End
      Begin Label lblDCEMax 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Maximum (dB):"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   1695
      End
   End
   Begin SSFrame grpRedNoi 
      Caption         =   "&Reduce Noise"
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   3360
      TabIndex        =   23
      Top             =   1320
      Width           =   3135
      Begin TextBox edtRedThr 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   27
         Text            =   "0"
         Top             =   720
         Width           =   855
      End
      Begin SpinButton spnRedThr 
         Height          =   315
         Left            =   2760
         Top             =   720
         Width           =   255
      End
      Begin SpinButton spnRedAtt 
         Height          =   315
         Left            =   2760
         Top             =   300
         Width           =   255
      End
      Begin TextBox edtRedAtt 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1920
         TabIndex        =   25
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin Label lblRedThr 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Threshold (%Max):"
         Height          =   252
         Left            =   120
         TabIndex        =   26
         Top             =   780
         Width           =   1692
      End
      Begin Label lblRedAtt 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Attenuation (dB):"
         Height          =   255
         Left            =   120
         TabIndex        =   24
         Top             =   360
         Width           =   1695
      End
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

Const ALLDB_INC = 1             ' All dB increment
Const ALLDB_MIN = 0             ' All dB minimum
Const ALLDB_MAX = 60            ' All dB maximum
Const ALLDB_FMT = "#0.0"        ' All dB display format

Const ATTDB_MIN = -60           ' Attenuation dB minimum
Const ATTDB_MAX = 0             ' Attenuation dB maximum

Const MULPCTINC = 10            ' Multiplier percent increment
Const MULPCTMIN = 20            ' Multiplier percent minimum
Const MULPCTMAX = 500           ' Multiplier percent maximum

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
    ' Verify valid effects entries
    If EdtRngBad(edtDCEMax, ALLDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtEchDly, ALLSECMIN, ALLSECMAX) Then Exit Sub
    If EdtRngBad(edtEchDcy, ATTDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtFdIBeg, ATTDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtFdIEnd, ATTDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtFdOBeg, ATTDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtFdOEnd, ATTDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtNrmLvl, ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtNrmExc, ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtRedAtt, ATTDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtRedThr, ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtVol_Up, ALLDB_MIN, ALLDB_MAX) Then Exit Sub
    If EdtRngBad(edtVolDwn, ATTDB_MIN, ALLDB_MAX) Then Exit Sub

    ' Save settings
    PrfSetStr PRF_EFFCFGSEC, PRF_DCEMAXKEY, edtDCEMax
    PrfSetStr PRF_EFFCFGSEC, PRF_ECHDLYKEY, edtEchDly
    PrfSetStr PRF_EFFCFGSEC, PRF_ECHDCYKEY, edtEchDcy
    PrfSetStr PRF_EFFCFGSEC, PRF_FDIBEGKEY, edtFdIBeg
    PrfSetStr PRF_EFFCFGSEC, PRF_FDIENDKEY, edtFdIEnd
    PrfSetStr PRF_EFFCFGSEC, PRF_FDOBEGKEY, edtFdOBeg
    PrfSetStr PRF_EFFCFGSEC, PRF_FDOENDKEY, edtFdOEnd
    PrfSetStr PRF_EFFCFGSEC, PRF_NRMLVLKEY, edtNrmLvl
    PrfSetStr PRF_EFFCFGSEC, PRF_NRMEXCKEY, edtNrmExc
    PrfSetStr PRF_EFFCFGSEC, PRF_REDATTKEY, edtRedAtt
    PrfSetStr PRF_EFFCFGSEC, PRF_REDTHRKEY, edtRedThr
    PrfSetStr PRF_EFFCFGSEC, PRF_VOL_UPKEY, edtVol_Up
    PrfSetStr PRF_EFFCFGSEC, PRF_VOLDWNKEY, edtVolDwn

    ' Return
    FrmModRet Me, ""
    
End Sub

Sub edtDCEMax_GotFocus ()
    EdtTxtSel edtDCEMax
End Sub

Sub edtDCEMax_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnDCEMax_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnDCEMax_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtDCEMax.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtEchDcy_GotFocus ()
    EdtTxtSel edtEchDcy
End Sub

Sub edtEchDcy_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnEchDcy_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnEchDcy_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtEchDcy.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtEchDly_GotFocus ()
    EdtTxtSel edtEchDly
End Sub

Sub edtEchDly_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnEchDly_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnEchDly_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtEchDly.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtFdIBeg_GotFocus ()
    EdtTxtSel edtFdIBeg
End Sub

Sub edtFdIBeg_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnFdIBeg_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnFdIBeg_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtFdIBeg.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtFdIEnd_GotFocus ()
    EdtTxtSel edtFdIEnd
End Sub

Sub edtFdIEnd_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnFdIEnd_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnFdIEnd_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtFdIEnd.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtFdOBeg_GotFocus ()
    EdtTxtSel edtFdOBeg
End Sub

Sub edtFdOBeg_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnFdOBeg_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnFdOBeg_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtFdOBeg.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtFdOEnd_GotFocus ()
    EdtTxtSel edtFdOEnd
End Sub

Sub edtFdOEnd_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnFdOEnd_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnFdOEnd_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtFdOEnd.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtNrmExc_GotFocus ()
    EdtTxtSel edtNrmExc
End Sub

Sub edtNrmExc_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnNrmExc_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnNrmExc_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtNrmExc.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtNrmLvl_GotFocus ()
    EdtTxtSel edtNrmLvl
End Sub

Sub edtNrmLvl_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnNrmLvl_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnNrmLvl_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtNrmLvl.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtRedAtt_GotFocus ()
    EdtTxtSel edtRedAtt
End Sub

Sub edtRedAtt_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnRedAtt_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnRedAtt_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtRedAtt.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtRedThr_GotFocus ()
    EdtTxtSel edtRedThr
End Sub

Sub edtRedThr_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnRedThr_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnRedThr_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtRedThr.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtVol_Up_GotFocus ()
    EdtTxtSel edtVol_Up
End Sub

Sub edtVolDwn_GotFocus ()
    EdtTxtSel edtVolDwn
End Sub

Sub edtVolDwn_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnVolDwn_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnVolDwn_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtVolDwn.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_Activate ()
    ' Yield to complete re-paints
    DoEvents
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_EFFCFG

    ' Disable options for "VFEdit Jr." version
    If (lVFEVer_Jr) Then SetMnu_Jr

    ' Retrieve current defaults
    edtDCEMax = PrfGetStr(PRF_EFFCFGSEC, PRF_DCEMAXKEY, Str$(DCEMAXDEF))
    edtEchDly = PrfGetStr(PRF_EFFCFGSEC, PRF_ECHDLYKEY, Str$(ECHDLYDEF))
    edtEchDcy = PrfGetStr(PRF_EFFCFGSEC, PRF_ECHDCYKEY, Str$(ECHDCYDEF))
    edtFdIBeg = PrfGetStr(PRF_EFFCFGSEC, PRF_FDIBEGKEY, Str$(FDIBEGDEF))
    edtFdIEnd = PrfGetStr(PRF_EFFCFGSEC, PRF_FDIENDKEY, Str$(FDIENDDEF))
    edtFdOBeg = PrfGetStr(PRF_EFFCFGSEC, PRF_FDOBEGKEY, Str$(FDOBEGDEF))
    edtFdOEnd = PrfGetStr(PRF_EFFCFGSEC, PRF_FDOENDKEY, Str$(FDOENDDEF))
    edtNrmLvl = PrfGetStr(PRF_EFFCFGSEC, PRF_NRMLVLKEY, Str$(NRMLVLDEF))
    edtNrmExc = PrfGetStr(PRF_EFFCFGSEC, PRF_NRMEXCKEY, Str$(NRMEXCDEF))
    edtRedAtt = PrfGetStr(PRF_EFFCFGSEC, PRF_REDATTKEY, Str$(REDATTDEF))
    edtRedThr = PrfGetStr(PRF_EFFCFGSEC, PRF_REDTHRKEY, Str$(REDTHRDEF))
    edtVol_Up = PrfGetStr(PRF_EFFCFGSEC, PRF_VOL_UPKEY, Str$(VOL_UPDEF))
    edtVolDwn = PrfGetStr(PRF_EFFCFGSEC, PRF_VOLDWNKEY, Str$(VOLDWNDEF))
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
    
End Sub

Sub SetMnu_Jr ()
    ' Disable options for "VFEdit Jr." version
    grpCmpExp.Enabled = False
    lblDCEMax.Enabled = False
    edtDCEMax.Enabled = False
    grpNrmLvl.Enabled = False
    lblNrmLvl.Enabled = False
    edtNrmLvl.Enabled = False
    lblNrmExc.Enabled = False
    edtNrmExc.Enabled = False
End Sub

Sub spnDCEMax_SpinDown ()
    EdtBoxSpn edtDCEMax, -ALLDB_INC, ALLDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnDCEMax_SpinUp ()
    EdtBoxSpn edtDCEMax, ALLDB_INC, ALLDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnEchDcy_SpinDown ()
    EdtBoxSpn edtEchDcy, -ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnEchDcy_SpinUp ()
    EdtBoxSpn edtEchDcy, ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnEchDly_SpinDown ()
    EdtBoxSpn edtEchDly, -ALLSECINC, ALLSECMIN, ALLSECMAX, ALLSECFMT
End Sub

Sub spnEchDly_SpinUp ()
    EdtBoxSpn edtEchDly, ALLSECINC, ALLSECMIN, ALLSECMAX, ALLSECFMT
End Sub

Sub spnFdIBeg_SpinDown ()
    EdtBoxSpn edtFdIBeg, -ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnFdIBeg_SpinUp ()
    EdtBoxSpn edtFdIBeg, ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnFdIEnd_SpinDown ()
    EdtBoxSpn edtFdIEnd, -ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnFdIEnd_SpinUp ()
    EdtBoxSpn edtFdIEnd, ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnFdOBeg_SpinDown ()
    EdtBoxSpn edtFdOBeg, -ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnFdOBeg_SpinUp ()
    EdtBoxSpn edtFdOBeg, ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnFdOEnd_SpinDown ()
    EdtBoxSpn edtFdOEnd, -ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnFdOEnd_SpinUp ()
    EdtBoxSpn edtFdOEnd, ALLDB_INC, ATTDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnNrmExc_SpinDown ()
    EdtBoxSpn edtNrmExc, -ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnNrmExc_SpinUp ()
    EdtBoxSpn edtNrmExc, ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnNrmLvl_SpinDown ()
    EdtBoxSpn edtNrmLvl, -ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnNrmLvl_SpinUp ()
    EdtBoxSpn edtNrmLvl, ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnRedAtt_SpinDown ()
    EdtBoxSpn edtRedAtt, -ALLDB_INC, ATTDB_MIN, ATTDB_MAX, ALLDB_FMT
End Sub

Sub spnRedAtt_SpinUp ()
    EdtBoxSpn edtRedAtt, ALLDB_INC, ATTDB_MIN, ATTDB_MAX, ALLDB_FMT
End Sub

Sub spnRedThr_SpinDown ()
    EdtBoxSpn edtRedThr, -ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnRedThr_SpinUp ()
    EdtBoxSpn edtRedThr, ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnVol_Up_SpinDown ()
    EdtBoxSpn edtVol_Up, -ALLDB_INC, ALLDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnVol_Up_SpinUp ()
    EdtBoxSpn edtVol_Up, ALLDB_INC, ALLDB_MIN, ALLDB_MAX, ALLDB_FMT
End Sub

Sub spnVolDwn_SpinDown ()
    EdtBoxSpn edtVolDwn, -ALLDB_INC, ATTDB_MIN, ATTDB_MAX, ALLDB_FMT
End Sub

Sub spnVolDwn_SpinUp ()
    EdtBoxSpn edtVolDwn, ALLDB_INC, ATTDB_MIN, ATTDB_MAX, ALLDB_FMT
End Sub

