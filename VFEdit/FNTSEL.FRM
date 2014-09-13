VERSION 2.00
Begin Form frmFntSel 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Font Selection"
   ClientHeight    =   1572
   ClientLeft      =   1116
   ClientTop       =   1572
   ClientWidth     =   6480
   Height          =   1944
   Left            =   1092
   LinkTopic       =   "Form1"
   ScaleHeight     =   1572
   ScaleWidth      =   6480
   Top             =   1224
   Width           =   6528
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   5160
      TabIndex        =   7
      Top             =   1080
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5160
      TabIndex        =   6
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   5160
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin SSFrame Frame3D1 
      ForeColor       =   &H00000000&
      Height          =   1215
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4935
      Begin SpinButton spnFntSiz 
         Height          =   315
         Left            =   4560
         Top             =   600
         Width           =   255
      End
      Begin TextBox edtFntSiz 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   3600
         TabIndex        =   4
         Text            =   "8.0"
         Top             =   600
         Width           =   975
      End
      Begin ComboBox cboFntNam 
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   3
         Top             =   600
         Width           =   3255
      End
      Begin Label Label1 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Size (pts):"
         Height          =   240
         Left            =   3600
         TabIndex        =   2
         Top             =   240
         Width           =   1095
      End
      Begin Label lblFntNam 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Name:"
         Height          =   240
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   2655
      End
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Const FNTSELINC = 1             ' Font size selection increment
Const FNTSELMIN = 4             ' Font size selection minimum
Const FNTSELMAX = 128           ' Font size selection maximum
Const FNTSELFMT = "#0.0"        ' Font size selection display format

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Verify valid entries
    If EdtRngBad(edtFntSiz, FNTSELMIN, FNTSELMAX) Then Exit Sub
    
    ' Return font name and size
    FrmModRet Me, cboFntNam.Text & Chr$(VFEARGDEL) & edtFntSiz
End Sub

Sub edtFntSiz_GotFocus ()
    EdtTxtSel edtFntSiz
End Sub

Sub edtFntSiz_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnFntSiz_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnFntSiz_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtFntSiz.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_Activate ()
    Dim sInpVar As String
    Dim sFntNam As String
    Dim ii As Integer

    ' Yield to complete re-paints
    DoEvents
    
    ' Retrieve input arguments from tag
    sInpVar = Tag

    ' Retrieve current font name
    sFntNam = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    
    ' Initialize selection to current font name and size
    If ("" <> sFntNam) Then
        For ii = 0 To cboFntNam.ListCount
            If (sFntNam = cboFntNam.List(ii)) Then
                cboFntNam.ListIndex = ii
                Exit For
            End If
        Next ii
        edtFntSiz = Val(StrTokStr(sInpVar, Chr$(VFEARGDEL)))
    End If

End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    Dim ii As Integer
    HelpContextID = HLP_FNTSEL
    
    ' Initialize font name selection box
    cboFntNam.Clear
    For ii = 0 To screen.FontCount - 1
        cboFntNam.AddItem (screen.Fonts(ii))
    Next
    cboFntNam.ListIndex = 0
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub spnFntSiz_SpinDown ()
    EdtBoxSpn edtFntSiz, -FNTSELINC, FNTSELMIN, FNTSELMAX, FNTSELFMT
End Sub

Sub spnFntSiz_SpinUp ()
    EdtBoxSpn edtFntSiz, FNTSELINC, FNTSELMIN, FNTSELMAX, FNTSELFMT
End Sub

