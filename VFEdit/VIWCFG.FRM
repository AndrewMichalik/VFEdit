VERSION 2.00
Begin Form frmViwCfg 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "View Configure"
   ClientHeight    =   2076
   ClientLeft      =   1116
   ClientTop       =   1536
   ClientWidth     =   5040
   Height          =   2448
   KeyPreview      =   -1  'True
   Left            =   1092
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2076
   ScaleWidth      =   5040
   Top             =   1188
   Width           =   5088
   Begin SSFrame grpDspRes 
      Caption         =   "&Display Resolution (msec/div)"
      ForeColor       =   &H00000000&
      Height          =   1875
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      Begin SpinButton spnResHgh 
         Height          =   315
         Left            =   3135
         Top             =   1440
         Width           =   255
      End
      Begin TextBox edtResHgh 
         Height          =   315
         Left            =   2040
         TabIndex        =   6
         Text            =   "100"
         Top             =   1440
         Width           =   1110
      End
      Begin SpinButton spnResMed 
         Height          =   315
         Left            =   3135
         Top             =   960
         Width           =   255
      End
      Begin TextBox edtResMed 
         Height          =   315
         Left            =   2040
         TabIndex        =   4
         Text            =   "500"
         Top             =   960
         Width           =   1110
      End
      Begin SpinButton spnResLow 
         Height          =   315
         Left            =   3135
         Top             =   480
         Width           =   255
      End
      Begin TextBox edtResLow 
         Height          =   315
         Left            =   2040
         TabIndex        =   2
         Text            =   "2000"
         Top             =   480
         Width           =   1110
      End
      Begin Label lblResHgh 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&High Resolution:"
         Height          =   330
         Left            =   120
         TabIndex        =   5
         Top             =   1485
         Width           =   1815
      End
      Begin Label lblResMed 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Medium Resolution:"
         Height          =   330
         Left            =   120
         TabIndex        =   3
         Top             =   1005
         Width           =   1815
      End
      Begin Label lblResLow 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Low Resolution:"
         Height          =   330
         Left            =   120
         TabIndex        =   1
         Top             =   525
         Width           =   1815
      End
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   8
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3720
      TabIndex        =   7
      Top             =   120
      Width           =   1215
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3720
      TabIndex        =   9
      Top             =   1560
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Const VIWRESINC = 100           ' View Resolution increment
Const VIWRESMin = 1             ' View Resolution maximum
Const VIWRESMAX = 1000000       ' View Resolution maximum
Const VIWRESFMT = "#0"          ' View Resolution display format

Dim sLowChg As String           ' Resolution Low changed
Dim sMedChg As String           ' Resolution Medium changed
Dim sHghChg As String           ' Resolution High changed

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Note - The view setting could actually be too low / high,
    ' dependant upon the type of file being edited. The AmpDspRes()
    ' function will enforce legal values. This document's view will
    ' be updated, but the user will need to re-select the resolution
    ' for other docs to have it take effect.
    PrfSetStr PRF_VIWCFGSEC, PRF_VIWLOWKEY, edtResLow
    PrfSetStr PRF_VIWCFGSEC, PRF_VIWMEDKEY, edtResMed
    PrfSetStr PRF_VIWCFGSEC, PRF_VIWHGHKEY, edtResHgh
    
    ' Indicate whether user changed anything
    FrmModRet Me, sLowChg & Chr$(VFEARGDEL) & sMedChg & Chr$(VFEARGDEL) & sHghChg
End Sub

Sub edtResHgh_Change ()
    ' Indicate that user changed something
    sHghChg = MSG_VIWRESHGH
End Sub

Sub edtResHgh_GotFocus ()
    EdtTxtSel edtResHgh
End Sub

Sub edtResHgh_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnResHgh_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnResHgh_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtResHgh.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtResLow_Change ()
    ' Indicate that user changed something
    sLowChg = MSG_VIWRESLOW
End Sub

Sub edtResLow_GotFocus ()
    EdtTxtSel edtResLow
End Sub

Sub edtResLow_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnResLow_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnResLow_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtResLow.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtResMed_Change ()
    ' Indicate that user changed something
    sMedChg = MSG_VIWRESMED
End Sub

Sub edtResMed_GotFocus ()
    EdtTxtSel edtResMed
End Sub

Sub edtResMed_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnResMed_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnResMed_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtResMed.SelStart = 0
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
    HelpContextID = HLP_VIWCFG
    
    ' Retrieve current defaults
    edtResLow = PrfGetStr(PRF_VIWCFGSEC, PRF_VIWLOWKEY, Str$(RESLOWDEF))
    edtResMed = PrfGetStr(PRF_VIWCFGSEC, PRF_VIWMEDKEY, Str$(RESMEDDEF))
    edtResHgh = PrfGetStr(PRF_VIWCFGSEC, PRF_VIWHGHKEY, Str$(RESHGHDEF))
    
    ' Indicate that user has not yet changed anything
    sLowChg = ""
    sMedChg = ""
    sHghChg = ""
    
    ' Insure that the controls contents are visible
    SafCtlClr Me

End Sub

Sub spnResHgh_SpinDown ()
    EdtBoxSpn edtResHgh, -VIWRESINC, VIWRESMin, VIWRESMAX, VIWRESFMT
End Sub

Sub spnResHgh_SpinUp ()
    EdtBoxSpn edtResHgh, VIWRESINC, VIWRESMin, VIWRESMAX, VIWRESFMT
End Sub

Sub spnResLow_SpinDown ()
    EdtBoxSpn edtResLow, -VIWRESINC, VIWRESMin, VIWRESMAX, VIWRESFMT
End Sub

Sub spnResLow_SpinUp ()
    EdtBoxSpn edtResLow, VIWRESINC, VIWRESMin, VIWRESMAX, VIWRESFMT
End Sub

Sub spnResMed_SpinDown ()
    EdtBoxSpn edtResMed, -VIWRESINC, VIWRESMin, VIWRESMAX, VIWRESFMT
End Sub

Sub spnResMed_SpinUp ()
    EdtBoxSpn edtResMed, VIWRESINC, VIWRESMin, VIWRESMAX, VIWRESFMT
End Sub

