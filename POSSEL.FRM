VERSION 2.00
Begin Form frmPosSel 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Position Selection"
   ClientHeight    =   1560
   ClientLeft      =   1125
   ClientTop       =   1515
   ClientWidth     =   5040
   Height          =   1905
   KeyPreview      =   -1  'True
   Left            =   1095
   LinkTopic       =   "Form1"
   ScaleHeight     =   1560
   ScaleWidth      =   5040
   Top             =   1200
   Width           =   5100
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3720
      TabIndex        =   8
      Top             =   1080
      Width           =   1215
   End
   Begin SSFrame grpSelLen 
      Caption         =   "&Length"
      ForeColor       =   &H00000000&
      Height          =   615
      Left            =   120
      TabIndex        =   3
      Top             =   840
      Width           =   3495
      Begin TextBox edtSelLen 
         Height          =   312
         Left            =   1920
         TabIndex        =   5
         Text            =   "100.0"
         Top             =   240
         Width           =   1212
      End
      Begin SpinButton spnSelLen 
         Height          =   315
         Left            =   3120
         Top             =   240
         Width           =   255
      End
      Begin Label lblSelLen 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Seconds:"
         Height          =   285
         Left            =   585
         TabIndex        =   4
         Top             =   270
         Width           =   1350
      End
   End
   Begin SSFrame grpSelPos 
      Caption         =   "&Position"
      ForeColor       =   &H00000000&
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      Begin TextBox edtSelPos 
         Height          =   312
         Left            =   1920
         TabIndex        =   2
         Text            =   "0.0"
         Top             =   240
         Width           =   1212
      End
      Begin SpinButton spnSelPos 
         Height          =   315
         Left            =   3120
         Top             =   240
         Width           =   255
      End
      Begin Label lblSelPos 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Seconds:"
         Height          =   285
         Left            =   585
         TabIndex        =   1
         Top             =   270
         Width           =   1350
      End
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   7
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3720
      TabIndex        =   6
      Top             =   120
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Const POSSELINC = 1             ' Extents selection increment
Const POSSELMIN = 0             ' Extents selection maximum
Const POSSELMAX = 1000000       ' Extents selection maximum
Const POSSELFMT = "#0.0"        ' Extents selection display format

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Verify valid extents entries
    If EdtRngBad(edtSelPos, POSSELMIN, POSSELMAX) Then Exit Sub
    If EdtRngBad(edtSelLen, POSSELMIN, POSSELMAX - Val(edtSelPos)) Then Exit Sub
    FrmModRet Me, lblSelPos & Chr$(VFEARGDEL) & edtSelPos & Chr$(VFEARGDEL) & lblSelLen & Chr$(VFEARGDEL) & edtSelLen
End Sub

Sub edtSelLen_GotFocus ()
    EdtTxtSel edtSelLen
End Sub

Sub edtSelLen_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnSelLen_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnSelLen_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtSelLen.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtSelPos_GotFocus ()
    EdtTxtSel edtSelPos
End Sub

Sub edtSelPos_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnSelPos_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnSelPos_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtSelPos.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_Activate ()
    Dim sInpVar As String

    ' Retrieve input arguments from tag: OffSet, Length, Format
    sInpVar = tag
    Caption = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    
    lblSelPos = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    edtSelPos = Format$(Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))), POSSELFMT)
    
    lblSelLen = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    edtSelLen = Format$(Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))), POSSELFMT)

    ' Enable / disable length request
    grpSelLen.Visible = Len(lblSelLen)
    
    ' Yield to complete re-paints
    DoEvents
    
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    HelpContextID = HLP_POSSEL
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub spnSelLen_SpinDown ()
    EdtBoxSpn edtSelLen, -POSSELINC, POSSELMIN, POSSELMAX, POSSELFMT
End Sub

Sub spnSelLen_SpinUp ()
    EdtBoxSpn edtSelLen, POSSELINC, POSSELMIN, POSSELMAX, POSSELFMT
End Sub

Sub spnSelPos_SpinDown ()
    EdtBoxSpn edtSelPos, -POSSELINC, POSSELMIN, POSSELMAX, POSSELFMT
End Sub

Sub spnSelPos_SpinUp ()
    EdtBoxSpn edtSelPos, POSSELINC, POSSELMIN, POSSELMAX, POSSELFMT
End Sub

