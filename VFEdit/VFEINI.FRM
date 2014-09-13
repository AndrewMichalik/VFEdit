VERSION 2.00
Begin Form frmVFEIni 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   5172
   ClientLeft      =   1224
   ClientTop       =   1992
   ClientWidth     =   6372
   ControlBox      =   0   'False
   Height          =   5544
   Left            =   1200
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5172
   ScaleWidth      =   6372
   Top             =   1644
   Visible         =   0   'False
   Width           =   6420
   Begin SSPanel pnlVFEIni 
      BevelWidth      =   2
      BorderWidth     =   2
      Height          =   5175
      Left            =   0
      TabIndex        =   10
      Top             =   0
      Width           =   6375
      Begin SSFrame grpVIS 
         ForeColor       =   &H00000000&
         Height          =   3855
         Left            =   120
         TabIndex        =   0
         Top             =   120
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
            Height          =   1245
            Left            =   3600
            Picture         =   VFEINI.FRX:0000
            Stretch         =   -1  'True
            Top             =   2520
            Width           =   2385
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
         Begin Image imgBoxArt 
            Height          =   3495
            Left            =   120
            Picture         =   VFEINI.FRX:4DF2
            Stretch         =   -1  'True
            Top             =   240
            Width           =   3315
         End
      End
      Begin Label lblVerTxt 
         Alignment       =   2  'Center
         BackColor       =   &H00C0C0C0&
         Height          =   315
         Left            =   720
         TabIndex        =   8
         Top             =   4440
         Width           =   4935
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
         TabIndex        =   7
         Top             =   4080
         Width           =   4935
      End
      Begin Label lblCopyRight 
         Alignment       =   2  'Center
         BackColor       =   &H00C0C0C0&
         Caption         =   "Copyright © 1987-1999 Andrew J. Michalik."
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   255
         Left            =   1440
         TabIndex        =   9
         Top             =   4800
         Width           =   3495
      End
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Sub Form_Load ()
    ' Change label for "VFEdit Jr." version
    If (lVFEVer_Jr) Then SetMnu_Jr
End Sub

Sub SetMnu_Jr ()
    ' Change label for "VFEdit Jr." version
    lblVerTxt = MSG_JR_VERCAP
End Sub

