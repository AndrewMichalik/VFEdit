VERSION 2.00
Begin Form frmFtrCfg 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Filter Configure"
   ClientHeight    =   1908
   ClientLeft      =   1776
   ClientTop       =   1872
   ClientWidth     =   5280
   Height          =   2280
   KeyPreview      =   -1  'True
   Left            =   1752
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1908
   ScaleWidth      =   5280
   Top             =   1524
   Width           =   5328
   Begin SSFrame grpFrqCnv 
      Caption         =   "&Frequency Conversion"
      ForeColor       =   &H00000000&
      Height          =   1635
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3735
      Begin ComboBox cboResAlg 
         Height          =   300
         Left            =   240
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   1260
         Width           =   3255
      End
      Begin ComboBox cboAAFAlg 
         Height          =   288
         Left            =   240
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   600
         Width           =   3252
      End
      Begin Label lblAAFAlg 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Anti-aliasing Filter:"
         Height          =   252
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   3012
      End
      Begin Label lblResAlg 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Re-sample Algorithm:"
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   1020
         Width           =   3015
      End
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3960
      TabIndex        =   6
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3960
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3960
      TabIndex        =   7
      Top             =   1440
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Future: Convert the "Record / Play Configure" filter section to behave like
' "File Import / Export" and "Effects Change Frequency" which use this form as
' the only entry point.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
    SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    FrmModRet Me, Str$(cboAAFAlg.ItemData(cboAAFAlg.ListIndex)) & Chr$(VFEARGDEL) & Str$(cboResAlg.ItemData(cboResAlg.ListIndex))
End Sub

Sub Form_Activate ()
    Dim sInpVar As String
    Dim iDefAlg As Integer
    Dim iAlgEnu As Integer
    Dim sDesStr As String
    sDesStr = String(255, Chr$(STRNULDEL))
    
    ' Retrieve input arguments from tag: OffSet, Length, Format
    sInpVar = tag
    Caption = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Scan for supported anti-aliasing filter algorithms; set default
    iDefAlg = Val(StrTokStr(sInpVar, Chr$(VFEARGDEL)))
    cboAAFAlg.Clear
    iAlgEnu = 0

    While (AudFilAAFEnu(iAlgEnu, sDesStr, Len(sDesStr)))
        cboAAFAlg.AddItem (StrTokStr(sDesStr, Chr$(STRNULDEL)))
        cboAAFAlg.ItemData(cboAAFAlg.NewIndex) = iAlgEnu
        
        If (iAlgEnu = iDefAlg) Then cboAAFAlg.ListIndex = cboAAFAlg.NewIndex
        
        sDesStr = String(255, Chr$(STRNULDEL))
    Wend
    
    If (-1 = cboAAFAlg.ListIndex) Then cboAAFAlg.ListIndex = FndLstIdx(cboAAFAlg, AAFALGNRM)

    ' Scan for supported resample algorithms; set default
    iDefAlg = Val(StrTokStr(sInpVar, Chr$(VFEARGDEL)))
    cboResAlg.Clear
    iAlgEnu = 0
    
    While (AudFilResEnu(iAlgEnu, sDesStr, Len(sDesStr)))
        cboResAlg.AddItem (StrTokStr(sDesStr, Chr$(STRNULDEL)))
        cboResAlg.ItemData(cboResAlg.NewIndex) = iAlgEnu
        If (iAlgEnu = iDefAlg) Then cboResAlg.ListIndex = cboResAlg.NewIndex
        sDesStr = String(255, Chr$(STRNULDEL))
    Wend
    
    If (-1 = cboResAlg.ListIndex) Then cboResAlg.ListIndex = FndLstIdx(cboResAlg, RESALGNRM)
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    HelpContextID = HLP_FTRCFG
    
    ' Disable options for "VFEdit Jr." version
    If (lVFEVer_Jr) Then SetMnu_Jr

    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub SetMnu_Jr ()
    ' Disable options for "VFEdit Jr." version

    ' Filter options
    grpFrqCnv.Enabled = False
    cboAAFAlg.ForeColor = OPTDISCLR
    cboResAlg.ForeColor = OPTDISCLR
    lblAAFAlg.Enabled = False
    lblResAlg.Enabled = False
    cboAAFAlg.Enabled = False
    cboResAlg.Enabled = False

End Sub

