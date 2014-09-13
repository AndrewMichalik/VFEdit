VERSION 2.00
Begin Form frmEffFrq 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Change Frequency"
   ClientHeight    =   2508
   ClientLeft      =   1092
   ClientTop       =   1488
   ClientWidth     =   4560
   Height          =   2880
   KeyPreview      =   -1  'True
   Left            =   1068
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2508
   ScaleWidth      =   4560
   Top             =   1140
   Width           =   4608
   Begin SSFrame grpChgFrq 
      Caption         =   "&Change Frequency"
      ForeColor       =   &H00000000&
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3015
      Begin TextBox edtChgFrq 
         Alignment       =   2  'Center
         Height          =   315
         Left            =   1800
         TabIndex        =   2
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
      Begin SpinButton spnChgFrq 
         Height          =   315
         Left            =   2640
         Top             =   300
         Width           =   255
      End
      Begin Label lblChgFrq 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Multiply by (%):"
         Height          =   252
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   1692
      End
   End
   Begin SSFrame grpFrqFtr 
      Caption         =   "F&ilters"
      ForeColor       =   &H00000000&
      Height          =   1455
      Left            =   120
      TabIndex        =   3
      Top             =   960
      Width           =   3015
      Begin ListBox lstFrqFtr 
         Height          =   984
         Left            =   120
         TabIndex        =   4
         Top             =   360
         Width           =   2772
      End
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3240
      TabIndex        =   6
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3240
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3240
      TabIndex        =   7
      Top             =   2040
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Const ALLPCTFMT = "#0.0"        ' All percent display format

Const MULPCTINC = 10            ' Multiplier percent increment
Const MULPCTMIN = 20            ' Multiplier percent minimum
Const MULPCTMAX = 500           ' Multiplier percent maximum

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim iChdWasAct As Integer     ' Indicates that the child form triggered activation
Dim iFrqAAFTyp As Integer
Dim iFrqResTyp As Integer

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    ' Verify valid effects entries
    If EdtRngBad(edtChgFrq, MULPCTMIN, MULPCTMAX) Then Exit Sub
    
    ' Save settings
    PrfSetStr PRF_EFFCFGSEC, PRF_CHGFRQKEY, edtChgFrq
    AAFResSet PRF_EFFCFGSEC, iFrqAAFTyp, iFrqResTyp

    ' Return
    FrmModRet Me, Str$(edtChgFrq / 100#) & Chr$(VFEARGDEL) & Str$(iFrqAAFTyp) & Chr$(VFEARGDEL) & Str$(iFrqResTyp)
    
End Sub

Sub edtChgFrq_GotFocus ()
    EdtTxtSel edtChgFrq
End Sub

Sub edtChgFrq_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnChgFrq_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnChgFrq_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtChgFrq.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_Activate ()
   Dim iRetCod As Integer
    
    ' Did the format or filter selection button trigger re-activation?
    If iChdWasAct Then
        iChdWasAct = False
        Exit Sub
    End If
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Retrieve current defaults
    edtChgFrq = PrfGetStr(PRF_EFFCFGSEC, PRF_CHGFRQKEY, Str$(CHGFRQDEF))
    
    ' Get default filter and resample types; don't query user
    iRetCod = AAFResGet("", PRF_EFFCFGSEC, iFrqAAFTyp, iFrqResTyp)
    lstFrqFtr.Clear
    lstFrqFtr.AddItem FtrAAFNam(iFrqAAFTyp)
    lstFrqFtr.AddItem FtrResNam(iFrqResTyp)
    
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    HelpContextID = HLP_EFFCFG

    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub lstFrqFtr_Click ()
    ' Query user for default filter and resample types, don't save as default (yet)
    ' Indicate that frmFtrCfg caused re-activation
    iChdWasAct = True
    If (Not AAFResGet(Caption, "", iFrqAAFTyp, iFrqResTyp)) Then Exit Sub
    
    ' Re-load filter list box
    lstFrqFtr.Clear
    lstFrqFtr.AddItem FtrAAFNam(iFrqAAFTyp)
    lstFrqFtr.AddItem FtrResNam(iFrqResTyp)
End Sub

Sub spnChgFrq_SpinDown ()
    EdtBoxSpn edtChgFrq, -MULPCTINC, MULPCTMIN, MULPCTMAX, ALLPCTFMT
End Sub

Sub spnChgFrq_SpinUp ()
    EdtBoxSpn edtChgFrq, MULPCTINC, MULPCTMIN, MULPCTMAX, ALLPCTFMT
End Sub

