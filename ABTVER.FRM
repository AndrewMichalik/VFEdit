VERSION 2.00
Begin Form frmAbtVer 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Version Information"
   ClientHeight    =   4935
   ClientLeft      =   1155
   ClientTop       =   1500
   ClientWidth     =   5895
   Height          =   5280
   KeyPreview      =   -1  'True
   Left            =   1125
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4935
   ScaleWidth      =   5895
   Top             =   1185
   Width           =   5955
   Begin CommandButton Command1 
      Caption         =   "Edit .Ini File"
      Height          =   375
      Left            =   3000
      TabIndex        =   35
      Top             =   4320
      Width           =   1215
   End
   Begin SSFrame grpVFEEdi 
      Caption         =   "Edition"
      ForeColor       =   &H00000000&
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5655
      Begin Label lblSysVer 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Version 3.20c.1"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   120
         TabIndex        =   39
         Top             =   270
         Width           =   1110
      End
      Begin Label lblVFEVer 
         Alignment       =   2  'Center
         BackColor       =   &H00C0C0C0&
         Caption         =   "Version 3.20c.1"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   255
         Left            =   3960
         TabIndex        =   1
         Top             =   280
         Width           =   1575
      End
   End
   Begin SSFrame grpVBXVer 
      Caption         =   "Visual Basic Controls"
      ForeColor       =   &H00000000&
      Height          =   3252
      Left            =   3000
      TabIndex        =   20
      Top             =   840
      Width           =   2772
      Begin Label lblMSOutlin 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "MSOutlin:"
         Height          =   192
         Left            =   120
         TabIndex        =   37
         Top             =   1800
         Width           =   792
      End
      Begin Label txtMSOutlin 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   38
         Top             =   1800
         Width           =   96
      End
      Begin Label txtChart2FX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   22
         Top             =   360
         Width           =   96
      End
      Begin Label lblChart2FXVBX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Chart2FX:"
         Height          =   192
         Left            =   120
         TabIndex        =   21
         Top             =   360
         Width           =   804
      End
      Begin Label txtMhTip 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   26
         Top             =   1080
         Width           =   96
      End
      Begin Label mhTipVBX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "MhTip:"
         Height          =   192
         Left            =   120
         TabIndex        =   25
         Top             =   1080
         Width           =   600
      End
      Begin Label txtMhGMul 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   24
         Top             =   720
         Width           =   96
      End
      Begin Label txtMhSL200 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   28
         Top             =   1440
         Width           =   96
      End
      Begin Label lblThreeDVBX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "ThreeD:"
         Height          =   192
         Left            =   120
         TabIndex        =   33
         Top             =   2880
         Width           =   708
      End
      Begin Label lblSpinVBX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Spin:"
         Height          =   192
         Left            =   120
         TabIndex        =   31
         Top             =   2520
         Width           =   456
      End
      Begin Label lblSBCVBX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "SBC:"
         Height          =   192
         Left            =   120
         TabIndex        =   29
         Top             =   2160
         Width           =   432
      End
      Begin Label txtThreeD 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   34
         Top             =   2880
         Width           =   96
      End
      Begin Label txtSpin 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   32
         Top             =   2520
         Width           =   96
      End
      Begin Label txtSBC 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1080
         TabIndex        =   30
         Top             =   2160
         Width           =   96
      End
      Begin Label lblMhSL200VBX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "MhSL200:"
         Height          =   192
         Left            =   120
         TabIndex        =   27
         Top             =   1440
         Width           =   876
      End
      Begin Label mhGMulVBX 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "MhGMul:"
         Height          =   192
         Left            =   120
         TabIndex        =   23
         Top             =   720
         Width           =   768
      End
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   36
      Top             =   4320
      Width           =   1215
   End
   Begin SSFrame grpDLLVer 
      Caption         =   "Dynamic Link Libraries"
      ForeColor       =   &H00000000&
      Height          =   3972
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   2772
      Begin ListBox lstCIFEnu 
         BackColor       =   &H00FFFFFF&
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "Courier New"
         FontSize        =   9
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   480
         Left            =   1320
         TabIndex        =   5
         TabStop         =   0   'False
         Top             =   600
         Width           =   1335
      End
      Begin Label lblMSAJT200DLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "MSAJT200:"
         Height          =   192
         Left            =   120
         TabIndex        =   12
         Top             =   2520
         Width           =   948
      End
      Begin Label txtMSAJT200 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   13
         Top             =   2520
         Width           =   96
      End
      Begin Label lblInsDLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "VFEIns:"
         Height          =   192
         Left            =   120
         TabIndex        =   18
         Top             =   3600
         Width           =   648
      End
      Begin Label txtIns 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   19
         Top             =   3600
         Width           =   96
      End
      Begin Label txtVer 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   17
         Top             =   3240
         Width           =   96
      End
      Begin Label lblVerDLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Ver:"
         Height          =   192
         Left            =   120
         TabIndex        =   16
         Top             =   3240
         Width           =   348
      End
      Begin Label txtMSAJT112 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   11
         Top             =   2160
         Width           =   96
      End
      Begin Label txtVBDB300 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   15
         Top             =   2880
         Width           =   96
      End
      Begin Label lblMSAJT112DLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "MSAJT112:"
         Height          =   192
         Left            =   120
         TabIndex        =   10
         Top             =   2160
         Width           =   948
      End
      Begin Label lblVBDB300DLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "VBDB300:"
         Height          =   192
         Left            =   120
         TabIndex        =   14
         Top             =   2880
         Width           =   888
      End
      Begin Label txtVFECIF 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   4
         Top             =   360
         Width           =   84
      End
      Begin Label txtMhRun300 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   9
         Top             =   1800
         Width           =   96
      End
      Begin Label txtDWSpyDLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "?"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   192
         Left            =   1320
         TabIndex        =   7
         Top             =   1440
         Width           =   96
      End
      Begin Label lblMhRun300DLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "MhRun400:"
         Height          =   192
         Left            =   120
         TabIndex        =   8
         Top             =   1800
         Width           =   996
      End
      Begin Label lblVFECIFDLL 
         BackColor       =   &H00C0C0C0&
         Caption         =   "VFECIF:"
         Height          =   252
         Left            =   120
         TabIndex        =   3
         Top             =   360
         Width           =   1092
      End
      Begin Label lblDWSpyDLL 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "DWSpyDLL:"
         Height          =   192
         Left            =   120
         TabIndex        =   6
         Top             =   1440
         Width           =   1056
      End
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Declare Function CIFSupVerEnu Lib "vfecif.dll" (pusSupTyp As Integer, pusVerNum As Integer, ByVal sDesStr As String, ByVal usMaxLen As Integer) As Integer

Sub CmdOK_Click ()
    FrmModRet Me, ""
End Sub

Sub Command1_Click ()
    Dim hInst%
    hInst = Shell("notepad " & sPrfFilNam, 3)
End Sub

Sub Form_Activate ()
    ' Yield to complete re-paints
    DoEvents
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then CmdOK_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_ABTVIS

    Dim lSysVer As Long
    Dim iMajVer As Integer
    Dim iMinVer As Integer
    Dim iSubMaj As Integer
    Dim iSubMin As Integer
    Dim sDesStr As String
    Dim iSupTyp As Integer
    sDesStr = String(255, Chr$(STRNULDEL))
    
    ' Get operating system version info
    lSysVer = GetSysVer(sDesStr)
    lblSysVer = sDesStr

    ' Get Version numbers for VFECIF components
    lstCIFEnu.Clear

    While (0 <> CIFSupVerEnu(iSupTyp, iMajVer, sDesStr, Len(sDesStr)))
        lstCIFEnu.AddItem (Trim$(StrTokStr(sDesStr, Chr$(STRNULDEL))) + " " + Hex$(iMajVer))
        sDesStr = String(255, Chr$(STRNULDEL))
    Wend

    ' Get version numbers for DLL's
    txtVFECIF.Caption = GetFileVersion(GetLoadedModule("VFECIF.DLL"))
    txtDWSpyDLL.Caption = GetFileVersion(GetLoadedModule("DWSpyDLL.DLL"))
    txtMhRun300.Caption = GetFileVersion(GetLoadedModule("MhRun400.DLL"))
    txtMSAJT112.Caption = GetFileVersion(GetLoadedModule("MSAJT112.DLL"))   ' Called by VBDB300
    txtMSAJT200.Caption = GetFileVersion(GetLoadedModule("MSAJT200.DLL"))   ' Called by MSAJT112
    txtVBDB300.Caption = GetFileVersion(GetLoadedModule("VBDB300.DLL"))
    txtVer.Caption = GetFileVersion(GetLoadedModule("Ver.DLL"))
    txtIns.Caption = GetFileVersion(GetLoadedModule("VFEIns.DLL"))

    ' Get version numbers for VBX's
    txtChart2FX.Caption = GetFileVersion(GetLoadedModule("Chart2FX.VBX"))
    txtMhGMul.Caption = GetFileVersion(GetLoadedModule("MhGMul.VBX"))
    txtMhSL200.Caption = GetFileVersion(GetLoadedModule("MhSL200.VBX"))
    txtMhTip.Caption = GetFileVersion(GetLoadedModule("MhTip.VBX"))
    txtMSOutlin.Caption = GetFileVersion(GetLoadedModule("MSOutlin.VBX"))
    txtSBC.Caption = GetFileVersion(GetLoadedModule("SBC.VBX"))
    txtSpin.Caption = GetFileVersion(GetLoadedModule("Spin.VBX"))
    txtThreeD.Caption = GetFileVersion(GetLoadedModule("ThreeD.VBX"))
    
    ' Insure that the controls contents are visible
    SafCtlClr Me

End Sub

