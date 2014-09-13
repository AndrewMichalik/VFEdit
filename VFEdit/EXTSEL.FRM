VERSION 2.00
Begin Form frmExtSel 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Extents Select"
   ClientHeight    =   1560
   ClientLeft      =   1170
   ClientTop       =   4110
   ClientWidth     =   5040
   Height          =   1905
   KeyPreview      =   -1  'True
   Left            =   1140
   LinkTopic       =   "Form1"
   ScaleHeight     =   1560
   ScaleWidth      =   5040
   Top             =   3795
   Width           =   5100
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3720
      TabIndex        =   8
      Top             =   1080
      Width           =   1215
   End
   Begin SSFrame grpSel_To 
      Caption         =   "&To"
      ForeColor       =   &H00000000&
      Height          =   615
      Left            =   120
      TabIndex        =   3
      Top             =   840
      Width           =   3495
      Begin TextBox edtSel_To 
         Height          =   312
         Left            =   1920
         TabIndex        =   5
         Text            =   "30.0"
         Top             =   240
         Width           =   1212
      End
      Begin SpinButton spnSel_To 
         Height          =   315
         Left            =   3120
         Top             =   240
         Width           =   255
      End
      Begin Label lblSel_To 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Seconds:"
         Height          =   285
         Left            =   585
         TabIndex        =   4
         Top             =   270
         Width           =   1350
      End
   End
   Begin SSFrame grpSelFrm 
      Caption         =   "&From"
      ForeColor       =   &H00000000&
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      Begin TextBox edtSelFrm 
         Height          =   312
         Left            =   1920
         TabIndex        =   2
         Text            =   "0.0"
         Top             =   240
         Width           =   1212
      End
      Begin SpinButton spnSelFrm 
         Height          =   315
         Left            =   3120
         Top             =   240
         Width           =   255
      End
      Begin Label lblSelFrm 
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

Const EXTSELINC = 1             ' Extents selection increment
Const EXTSELMIN = 0             ' Extents selection maximum
Const EXTSELMAX = 1000000       ' Extents selection maximum
Const EXTSELFMT = "#0.0"        ' Extents selection display format

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Verify valid extents entries
    If EdtRngBad(edtSelFrm, EXTSELMIN, Min(EXTSELMAX, edtSel_To)) Then Exit Sub
    If EdtRngBad(edtSel_To, edtSelFrm, EXTSELMAX) Then Exit Sub
    FrmModRet Me, lblSelFrm & Chr$(VFEARGDEL) & edtSelFrm & Chr$(VFEARGDEL) & lblSel_To & Chr$(VFEARGDEL) & Str$(Val(edtSel_To) - Val(edtSelFrm)) & Chr$(VFEARGDEL) & MSG_DESSELSEC
End Sub

Sub edtSel_To_GotFocus ()
    EdtTxtSel edtSel_To
End Sub

Sub edtSel_To_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnSel_To_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnSel_To_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtSel_To.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtSelFrm_GotFocus ()
    EdtTxtSel edtSelFrm
End Sub

Sub edtSelFrm_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnSelFrm_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnSelFrm_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtSelFrm.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_Activate ()
    Dim sInpVar As String
    
    ' Retrieve input arguments from tag: OffSet, Length, Format
    sInpVar = tag
    Caption = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    
    ' Convert to "From - To", format
    lblSelFrm = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    edtSelFrm = Format$(Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))), EXTSELFMT)
    
    lblSel_To = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    edtSel_To = Format$(Val(edtSelFrm) + Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))), EXTSELFMT)

    ' Yield to complete re-paints
    DoEvents
    
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_EXTSEL
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub spnSel_To_SpinDown ()
    EdtBoxSpn edtSel_To, -EXTSELINC, EXTSELMIN, EXTSELMAX, EXTSELFMT
End Sub

Sub spnSel_To_SpinUp ()
    EdtBoxSpn edtSel_To, EXTSELINC, EXTSELMIN, EXTSELMAX, EXTSELFMT
End Sub

Sub spnSelFrm_SpinDown ()
    EdtBoxSpn edtSelFrm, -EXTSELINC, EXTSELMIN, EXTSELMAX, EXTSELFMT
End Sub

Sub spnSelFrm_SpinUp ()
    EdtBoxSpn edtSelFrm, EXTSELINC, EXTSELMIN, EXTSELMAX, EXTSELFMT
End Sub

