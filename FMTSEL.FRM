VERSION 2.00
Begin Form frmFmtSel 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "File Data Format"
   ClientHeight    =   2880
   ClientLeft      =   1260
   ClientTop       =   1212
   ClientWidth     =   5052
   Height          =   3252
   KeyPreview      =   -1  'True
   Left            =   1236
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2880
   ScaleWidth      =   5052
   Top             =   864
   Width           =   5100
   Begin SSFrame grpDatFmt 
      ForeColor       =   &H00000000&
      Height          =   1815
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   3495
      Begin ComboBox cboDatFrq 
         BackColor       =   &H00FFFFFF&
         Height          =   300
         Left            =   120
         TabIndex        =   6
         Top             =   1320
         Width           =   3255
      End
      Begin ComboBox cboDatFmt 
         BackColor       =   &H00FFFFFF&
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   420
         Width           =   3255
      End
      Begin Label lblDatFrq 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Frequency (Hz):"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   1080
         Width           =   2655
      End
      Begin Label lblDatFmt 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Data Format:"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   180
         Width           =   3015
      End
   End
   Begin SSFrame grpFilTyp 
      Caption         =   "File &Type:"
      ForeColor       =   &H00000000&
      Height          =   795
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      Begin ComboBox cboFilTyp 
         ForeColor       =   &H00000000&
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   360
         Width           =   3255
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
      Top             =   2400
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Dim tFilDocTyp As VFEDOCTYP   ' Current file document type

Sub cboDatFmt_Click ()
    ' Update SmpFrq combobox
    cboDatFrqIni cboFilTyp.ItemData(cboFilTyp.ListIndex), cboDatFmt.ItemData(cboDatFmt.ListIndex), tFilDocTyp.lSmpFrq, cboDatFrq
End Sub

Sub cboDatFmtIni (ByVal iFilFmt As Integer, ByVal iDefTyp As Integer, cCboBox As ComboBox)
    ' Initialize Data Format combo box
    Dim dsFilTyp As dynaset
    Dim iCurIdx As Integer

    Set dsFilTyp = dFilTypMDB.CreateDynaset("SELECT iPCMTyp, sPCMDes FROM tbFilTyp WHERE [iFilFmt] = " & iFilFmt & " GROUP BY [iPCMTyp], [sPCMDes]")

    If dsFilTyp.EOF Then
        cCboBox.ListIndex = -1
    Else
        cCboBox.Clear
        iCurIdx = 0
        Do While (Not dsFilTyp.EOF)
            cCboBox.AddItem dsFilTyp("sPCMDes")
            cCboBox.ItemData(cCboBox.NewIndex) = dsFilTyp("iPCMTyp")
            If iDefTyp = dsFilTyp("iPCMTyp") Then iCurIdx = cCboBox.NewIndex
            dsFilTyp.MoveNext
        Loop
        cCboBox.ListIndex = iCurIdx
    End If

  dsFilTyp.Close

End Sub

Sub cboDatFrqIni (ByVal iFilFmt As Integer, ByVal iPCMTyp As Integer, ByVal lDefFrq As Long, cCboBox As ComboBox)
    ' Initialize sample frequency combo box
    Dim dsFilTyp As dynaset
    Dim iCurIdx As Integer

    Set dsFilTyp = dFilTypMDB.CreateDynaset("SELECT lSmpFrq FROM tbFilTyp WHERE [iFilFmt] = " & iFilFmt & " AND [iPCMTyp] = " & iPCMTyp & " GROUP BY [lSmpFrq]")

    If dsFilTyp.EOF Then
        cCboBox.ListIndex = -1
    Else
        cCboBox.Clear
        iCurIdx = 0
        Do While (Not dsFilTyp.EOF)
            cCboBox.AddItem dsFilTyp("lSmpFrq")
            If lDefFrq = dsFilTyp("lSmpFrq") Then iCurIdx = cCboBox.NewIndex
            dsFilTyp.MoveNext
        Loop
        cCboBox.ListIndex = iCurIdx
  End If

  dsFilTyp.Close

End Sub

Sub cboFilTyp_Click ()
  'Update PCM Type combo box
  cboDatFmtIni cboFilTyp.ItemData(cboFilTyp.ListIndex), tFilDocTyp.iPCMTyp, cboDatFmt
  
  'Update Sample Frequency combo box
  cboDatFrqIni cboFilTyp.ItemData(cboFilTyp.ListIndex), cboDatFmt.ItemData(cboDatFmt.ListIndex), tFilDocTyp.lSmpFrq, cboDatFrq

End Sub

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    Dim tVFEDoc As VFEDOCTYP
    
    ' Test for valid frequency
    If EdtRngBad(cboDatFrq, SMPFRQMIN, SMPFRQMAX) Then Exit Sub
    
    'Fill in default values and update user selected entries
    tVFEDoc.sDocTyp = cboFilTyp
    tVFEDoc.iFilFmt = cboFilTyp.ItemData(cboFilTyp.ListIndex)
    tVFEDoc.sPCMDes = cboDatFmt
    tVFEDoc.iPCMTyp = cboDatFmt.ItemData(cboDatFmt.ListIndex)
    tVFEDoc.iChnCnt = 1
    tVFEDoc.lSmpFrq = Val(cboDatFrq.Text)

    'If File Open dialog, let File Open dialog update global type selection
    FrmModRet Me, TypDocToStr(tVFEDoc)

End Sub

Sub Form_Activate ()
  ' Disable input, set mouse to hourglass
  FrmUsrDis Me

  Dim sInpVar As String
  
  ' Retrieve input arguments from tag: caption, tVFEDoc (optional)
  sInpVar = tag
  
  ' Parse for caption
  Caption = StrTokStr(sInpVar, Chr$(VFEARGDEL))
  
  ' Yield to complete re-paints
  DoEvents

  'Parse for previously selected document type
  TypStrToDoc AudDocTypFnd(sInpVar), tFilDocTyp

  ' Initialize file type combo box to all available, set default selection
  FilTypCBxIni tFilDocTyp.iFilFmt, cboFilTyp

  ' If File New dialog, enable type selection
  If (MSG_FILNEWCAP = Caption) Then
      cboFilTyp.Enabled = True
      grpFilTyp.Enabled = True
  Else
      ' Disable type selection
      cboFilTyp.Enabled = False
      grpFilTyp.Enabled = False
      cboFilTyp.ForeColor = &H808080
  End If
  
  ' Re-enable input, set mouse to default
  FrmUsrEna Me
  
  'Set focus to OK button
  cmdOK.SetFocus
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    HelpContextID = HLP_FILFMT
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

