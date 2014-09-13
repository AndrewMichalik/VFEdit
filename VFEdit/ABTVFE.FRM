VERSION 2.00
Begin Form frmAbtVFE 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "About VFEdit ®"
   ClientHeight    =   5055
   ClientLeft      =   1305
   ClientTop       =   1740
   ClientWidth     =   6375
   Height          =   5400
   KeyPreview      =   -1  'True
   Left            =   1275
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5055
   ScaleWidth      =   6375
   Top             =   1425
   Width           =   6435
   Begin SSFrame grpRegLic 
      Caption         =   "This product is licensed to:"
      ForeColor       =   &H00000000&
      Height          =   1212
      Left            =   120
      TabIndex        =   11
      Top             =   3720
      Width           =   4452
      Begin Label lblRegLic 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Warning: Unlicensed copy!"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   732
         Left            =   120
         TabIndex        =   12
         Top             =   360
         Width           =   4212
      End
   End
   Begin SSFrame grpVIS 
      ForeColor       =   &H00000000&
      Height          =   2295
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   6135
      Begin Label lblem_adr 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "sales@vinfo.com"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   4800
         TabIndex        =   5
         Top             =   1440
         Width           =   1215
      End
      Begin Label lblDomSal 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Sales: 1-800-234-VISI"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   4470
         TabIndex        =   1
         Top             =   240
         Width           =   1545
      End
      Begin Label lblIntSal 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Int'l: +310-392-8780"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   4605
         TabIndex        =   3
         Top             =   840
         Width           =   1410
      End
      Begin Label lblDomFax 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Fax: 1-800-234-FXIT"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   4560
         TabIndex        =   2
         Top             =   540
         Width           =   1455
      End
      Begin Label lblIntFax 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Fax: +310-392-5511"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   4590
         TabIndex        =   4
         Top             =   1140
         Width           =   1425
      End
      Begin Label lblNetNam 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "www.vinfo.com"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   4920
         TabIndex        =   6
         Top             =   1740
         Width           =   1095
      End
      Begin Image imgVISLgo 
         Height          =   2010
         Left            =   120
         Picture         =   ABTVFE.FRX:0000
         Top             =   240
         Width           =   4335
      End
   End
   Begin CommandButton cmdVerInf 
      Caption         =   "&System Info..."
      Height          =   375
      Left            =   4680
      TabIndex        =   14
      Top             =   3960
      Width           =   1575
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4680
      TabIndex        =   15
      Top             =   4440
      Width           =   1575
   End
   Begin PictureBox picVFELgo 
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      Height          =   480
      Left            =   120
      Picture         =   ABTVFE.FRX:4DF2
      ScaleHeight     =   480
      ScaleWidth      =   480
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   2400
      Width           =   480
   End
   Begin Label lblDemTxt 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Height          =   252
      Left            =   720
      TabIndex        =   16
      Top             =   3000
      Width           =   4932
   End
   Begin Label lblVerTxt 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Height          =   252
      Left            =   720
      TabIndex        =   9
      Top             =   2760
      Width           =   4932
   End
   Begin Label lblLckCod 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Caption         =   "00000000"
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   255
      Left            =   4680
      TabIndex        =   13
      Top             =   3600
      Width           =   1575
   End
   Begin Label lblCopyRight 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Caption         =   "Copyright © 1987-1999 Andrew J. Michalik."
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   252
      Left            =   1440
      TabIndex        =   10
      Top             =   3360
      Width           =   3492
   End
   Begin Label lblVFEdit 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Caption         =   "VFEdit® Professional Prompt Editor"
      Height          =   315
      Left            =   720
      TabIndex        =   8
      Top             =   2400
      Width           =   4935
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Sub CmdOK_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdVerInf_Click ()
    Dim sRetArg As String
    
    sRetArg = FrmModShw(frmVFEMDI, frmAbtVer, "", CTR_MIDMIDNON)
End Sub

Sub Form_Activate ()
    Dim sRegTxt As String
    On Error GoTo Form_ActivateErr
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Retrieve input arguments from tag
    lblDemTxt = tag

    ' Retrieve license information
    sRegTxt = RegGetStr(PRF_REGLICSEC, PRF_REGUSRKEY, "")
    If ("" <> sRegTxt) Then sRegTxt = sRegTxt & CRLF()
    sRegTxt = sRegTxt & RegGetStr(PRF_REGLICSEC, PRF_REGCMPKEY, "")
    If ("" <> sRegTxt) Then sRegTxt = sRegTxt & CRLF()
    sRegTxt = sRegTxt & RegGetStr(PRF_REGLICSEC, PRF_REGSERKEY, "")
    
    ' Set license information
    If ChkRegSer(0, RegGetStr(PRF_REGLICSEC, PRF_REGSERKEY, "")) And ("" <> sRegTxt) Then lblRegLic = sRegTxt

    'Set focus to OK button
    cmdOK.SetFocus
    Exit Sub

Form_ActivateErr:
    sRegTxt = sRegTxt & RegGetStr(PRF_REGLICSEC, PRF_REGSERKEY, "")
    Exit Sub

End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then CmdOK_Click
End Sub

Sub Form_Load ()
    ' Change label for "VFEdit Jr." version
    If (lVFEVer_Jr) Then SetMnu_Jr
End Sub

Private Function RegGetStr (ByVal sSecNam As String, ByVal sKeyNam As String, ByVal sDefVal As String)
    Dim sRetStr As String
    
    sRetStr = String(255, Chr$(STRNULDEL))

    ' Check application original directory for registration file
    If (0 <> GetPrivateProfileString(sSecNam, sKeyNam, sDefVal, sRetStr, Len(sRetStr), SafGetDir(App.Path) & PRF_REGLICFIL)) Then
        RegGetStr = Trim$(StrTokStr(sRetStr, Chr$(STRNULDEL)))
    Else
        RegGetStr = Trim$(sDefVal)
    End If
End Function

Sub SetMnu_Jr ()
    ' Change label for "VFEdit Jr." version
    lblVerTxt = MSG_JR_VERCAP
End Sub

