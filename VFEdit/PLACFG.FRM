VERSION 2.00
Begin Form frmPlaCfg 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Play Configure"
   ClientHeight    =   2040
   ClientLeft      =   1605
   ClientTop       =   4320
   ClientWidth     =   5040
   Height          =   2385
   KeyPreview      =   -1  'True
   Left            =   1575
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2040
   ScaleWidth      =   5040
   Top             =   4005
   Width           =   5100
   Begin SSFrame grpFrqCnv 
      Caption         =   "&Frequency Conversion"
      ForeColor       =   &H00000000&
      Height          =   1755
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      Begin ComboBox cboResAlg 
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   1260
         Width           =   3255
      End
      Begin ComboBox cboAAFAlg 
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   600
         Width           =   3255
      End
      Begin Label lblAAFAlg 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Anti-aliasing Filter:"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   3015
      End
      Begin Label lblResAlg 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Resample Algorithm:"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   1020
         Width           =   3015
      End
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   6
      Top             =   600
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3720
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3720
      TabIndex        =   7
      Top             =   1500
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Future: Convert the "Record / Play Configure" filter section to behave like
' Import / Export which uses this form as the only entry point.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    PrfSetStr PRF_PLACFGSEC, PRF_AAFTYPKEY, Str$(cboAAFAlg.ItemData(cboAAFAlg.ListIndex))
    PrfSetStr PRF_PLACFGSEC, PRF_RESTYPKEY, Str$(cboResAlg.ItemData(cboResAlg.ListIndex))
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
    iAlgEnu = 0
    cboAAFAlg.Clear
    iDefAlg = Val(PrfGetStr(PRF_PLACFGSEC, PRF_AAFTYPKEY, Str$(AAFALGNRM)))
    While (AudDevPlaAAFEnu(iAlgEnu, sDesStr, Len(sDesStr)))
        cboAAFAlg.AddItem (StrTokStr(sDesStr, Chr$(STRNULDEL)))
        cboAAFAlg.ItemData(cboAAFAlg.NewIndex) = iAlgEnu
        If (iAlgEnu = iDefAlg) Then cboAAFAlg.ListIndex = cboAAFAlg.NewIndex
        sDesStr = String(255, Chr$(STRNULDEL))
    Wend
    If (-1 = cboAAFAlg.ListIndex) Then cboAAFAlg.ListIndex = FndLstIdx(cboAAFAlg, AAFALGNRM)

    ' Scan for supported resample algorithms; set default
    iAlgEnu = 0
    cboResAlg.Clear
    iDefAlg = Val(PrfGetStr(PRF_PLACFGSEC, PRF_RESTYPKEY, Str$(RESALGNRM)))
    While (AudDevPlaResEnu(iAlgEnu, sDesStr, Len(sDesStr)))
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
    HelpContextID = HLP_PLACFG
    
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

