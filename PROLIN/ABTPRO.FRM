VERSION 2.00
Begin Form frmAbtPro 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "About VFEdit ® ProLine/2V Control"
   ClientHeight    =   4440
   ClientLeft      =   1308
   ClientTop       =   1740
   ClientWidth     =   6372
   Height          =   4812
   Icon            =   ABTPRO.FRX:0000
   KeyPreview      =   -1  'True
   Left            =   1284
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4440
   ScaleWidth      =   6372
   Top             =   1392
   Width           =   6420
   Begin PictureBox grpRegLic 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   1212
      Left            =   120
      ScaleHeight     =   1212
      ScaleWidth      =   4452
      TabIndex        =   11
      Top             =   3720
      Width           =   4452
   End
   Begin PictureBox grpVIS 
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      ForeColor       =   &H00000000&
      Height          =   2295
      Left            =   120
      ScaleHeight     =   2292
      ScaleWidth      =   6132
      TabIndex        =   0
      Top             =   0
      Width           =   6135
      Begin Label lblem_adr 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "sales@vinfo.com"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   252
         Left            =   3720
         TabIndex        =   5
         Top             =   1440
         Width           =   2292
      End
      Begin Label lblDomSal 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "Sales: 1-800-234-VISI"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   252
         Left            =   3720
         TabIndex        =   1
         Top             =   240
         Width           =   2292
      End
      Begin Label lblIntSal 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "Int'l: +310-392-8780"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   252
         Left            =   3720
         TabIndex        =   3
         Top             =   840
         Width           =   2292
      End
      Begin Label lblDomFax 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "Fax: 1-800-234-FXIT"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   252
         Left            =   3720
         TabIndex        =   2
         Top             =   540
         Width           =   2292
      End
      Begin Label lblIntFax 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "Fax: +310-392-5511"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   252
         Left            =   3720
         TabIndex        =   4
         Top             =   1140
         Width           =   2292
      End
      Begin Label lblNetNam 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "www.vinfo.com"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   252
         Left            =   3720
         TabIndex        =   6
         Top             =   1740
         Width           =   2292
      End
      Begin Image imgVISLgo 
         Height          =   1608
         Left            =   120
         Picture         =   ABTPRO.FRX:0302
         Top             =   240
         Width           =   3468
      End
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4680
      TabIndex        =   13
      Top             =   3960
      Width           =   1575
   End
   Begin PictureBox picVFELgo 
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      Height          =   384
      Left            =   120
      Picture         =   ABTPRO.FRX:50F4
      ScaleHeight     =   384
      ScaleWidth      =   384
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   2400
      Width           =   384
   End
   Begin Label lblDemTxt 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Height          =   252
      Left            =   720
      TabIndex        =   14
      Top             =   3000
      Width           =   4932
   End
   Begin Label lblVerTxt 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Caption         =   "ProLine/2V Control Application"
      Height          =   252
      Left            =   720
      TabIndex        =   9
      Top             =   2760
      Width           =   4932
   End
   Begin Label lblLckCod 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Caption         =   "2.00a.0"
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   7.8
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   255
      Left            =   4680
      TabIndex        =   12
      Top             =   3600
      Width           =   1575
   End
   Begin Label lblCopyRight 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Caption         =   "Copyright © 1987-1996 Andrew J. Michalik."
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   7.8
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
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   9.6
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   315
      Left            =   720
      TabIndex        =   8
      Top             =   2400
      Width           =   4935
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1996
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Sub CmdOK_Click ()
    Unload Me
End Sub

Sub Form_Activate ()
    Dim sRegTxt As String
    On Error GoTo Form_ActivateErr
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Retrieve input arguments from tag
    lblDemTxt = tag

    'Set focus to OK button
    cmdOK.SetFocus
    Exit Sub

Form_ActivateErr:
    Exit Sub

End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then CmdOK_Click
End Sub

Function KeyChkEsc (KeyAscii As Integer) As Integer
    If (KEY_ESCAPE = KeyAscii) Then
        KeyAscii = 0
        KeyChkEsc = True
        Exit Function
    End If
    KeyChkEsc = False
End Function

