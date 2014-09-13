VERSION 2.00
Begin Form frmOptEnv 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Environment Options"
   ClientHeight    =   4104
   ClientLeft      =   1092
   ClientTop       =   1488
   ClientWidth     =   5040
   Height          =   4476
   KeyPreview      =   -1  'True
   Left            =   1068
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4104
   ScaleWidth      =   5040
   Top             =   1140
   Width           =   5088
   Begin SSFrame grpEnvDir 
      Caption         =   "&Temporary Directories"
      ForeColor       =   &H00000000&
      Height          =   1815
      Left            =   120
      TabIndex        =   6
      Top             =   2160
      Width           =   3495
      Begin TextBox edtDevDir 
         Height          =   315
         Left            =   120
         TabIndex        =   10
         Top             =   1320
         Width           =   3255
      End
      Begin TextBox edtWrkDir 
         Height          =   315
         Left            =   120
         TabIndex        =   8
         Top             =   600
         Width           =   3255
      End
      Begin Label lblDevDir 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Device Files:"
         Height          =   240
         Left            =   120
         TabIndex        =   9
         Top             =   1080
         Width           =   3255
      End
      Begin Label lblWrkDir 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Work Files:"
         Height          =   240
         Left            =   120
         TabIndex        =   7
         Top             =   360
         Width           =   3255
      End
   End
   Begin SSFrame grpUsrPrf 
      Caption         =   "&Preferences"
      ForeColor       =   &H00000000&
      Height          =   2052
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3492
      Begin CheckBox chkAutBak 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "Auto-backup on save"
         Height          =   252
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   3252
      End
      Begin CheckBox chkUndLvl 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "Undo/ Redo On"
         Height          =   252
         Left            =   120
         TabIndex        =   5
         Top             =   1680
         Width           =   3252
      End
      Begin CheckBox chkSilExt 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "Auto-extend file with silence"
         Height          =   252
         Left            =   120
         TabIndex        =   4
         Top             =   1320
         Width           =   3252
      End
      Begin ComboBox cboSelReg 
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   600
         Width           =   3255
      End
      Begin Label lblSelReg 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Selection Region Default:"
         Height          =   240
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   3255
      End
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   12
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3720
      TabIndex        =   11
      Top             =   120
      Width           =   1215
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3720
      TabIndex        =   13
      Top             =   3360
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Test for valid work & device files directory
    If EdtDirBad(edtWrkDir) Then Exit Sub
    If EdtDirBad(edtDevDir) Then Exit Sub
    
    ' Update profile settings
    PrfSetStr PRF_OPTENVSEC, PRF_SELREGKEY, cboSelReg.Text
    PrfSetStr PRF_OPTENVSEC, PRF_AUTBAKKEY, Str$(chkAutBak)
    PrfSetStr PRF_OPTENVSEC, PRF_SILEXTKEY, Str$(chkSilExt)
    PrfSetStr PRF_OPTENVSEC, PRF_UNDLVLKEY, Str$(chkUndLvl)
    PrfSetStr PRF_OPTENVSEC, PRF_WRKDIRKEY, edtWrkDir.Text
    PrfSetStr PRF_OPTENVSEC, PRF_DEVDIRKEY, edtDevDir.Text
    FrmModRet Me, ""
End Sub

Sub edtDevDir_Change ()
    lblDevDir.Enabled = Len(edtDevDir)
End Sub

Sub edtWrkDir_Change ()
    lblWrkDir.Enabled = Len(edtWrkDir)
End Sub

Sub Form_Activate ()
    Dim sDefMod As String
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Get default region setting & clear default region selection box
    sDefMod = PrfGetStr(PRF_OPTENVSEC, PRF_SELREGKEY, SELREGWHL)
    cboSelReg.Clear
    
    ' Load default region selection box
    cboSelReg.AddItem (SELREGWHL)
    If (SELREGWHL = sDefMod) Then cboSelReg.ListIndex = cboSelReg.NewIndex
    cboSelReg.AddItem (SELREGASK)
    If (SELREGASK = sDefMod) Then cboSelReg.ListIndex = cboSelReg.NewIndex

    ' Get default auto backup setting
    chkAutBak = CChk(Val(PrfGetStr(PRF_OPTENVSEC, PRF_AUTBAKKEY, Str$(AUTBAKDEF))))

    ' Get default silence extend setting
    chkSilExt = CChk(Val(PrfGetStr(PRF_OPTENVSEC, PRF_SILEXTKEY, Str$(SILEXTDEF))))

    ' Get default Undo/ Redo setting
    chkUndLvl = CChk(Val(PrfGetStr(PRF_OPTENVSEC, PRF_UNDLVLKEY, Str$(UNDLVLDEF))))

    ' Load Work & Device temporary files directory
    edtWrkDir = PrfGetStr(PRF_OPTENVSEC, PRF_WRKDIRKEY, WRKDIRDEF)
    lblWrkDir.Enabled = Len(edtWrkDir)
    edtDevDir = PrfGetStr(PRF_OPTENVSEC, PRF_DEVDIRKEY, WRKDIRDEF)
    lblDevDir.Enabled = Len(edtDevDir)
    
    ' Set focus to OK button
    cmdOK.SetFocus
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    HelpContextID = HLP_ENVOPT

    ' Disable options for "VFEdit Jr." version
    If (lVFEVer_Jr) Then SetMnu_Jr
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub SetMnu_Jr ()
    ' Disable options for "VFEdit Jr." version
    chkUndLvl.Enabled = False
End Sub

