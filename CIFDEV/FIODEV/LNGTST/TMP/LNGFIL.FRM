VERSION 4.00
Begin VB.Form frmLngFil 
   Caption         =   "frmLngFil"
   ClientHeight    =   4548
   ClientLeft      =   2616
   ClientTop       =   1260
   ClientWidth     =   5772
   Height          =   4872
   Left            =   2568
   LinkTopic       =   "Form1"
   ScaleHeight     =   4548
   ScaleWidth      =   5772
   Top             =   984
   Width           =   5868
   Begin VBX.Outline outDirNam 
      Height          =   1692
      Left            =   120
      PictureClosed   =   "LNGFIL.frx":0000
      PictureLeaf     =   "LNGFIL.frx":0162
      PictureOpen     =   "LNGFIL.frx":02C4
      TabIndex        =   4
      Top             =   720
      Width           =   3612
   End
   Begin VB.DirListBox dirDirNam_MH 
      Height          =   1752
      Left            =   3960
      TabIndex        =   3
      Top             =   720
      Width           =   1572
   End
   Begin VB.ListBox lstFilNam 
      Height          =   1776
      Left            =   120
      Sorted          =   -1  'True
      TabIndex        =   2
      Top             =   2640
      Width           =   3612
   End
   Begin VB.CommandButton cmdFndNam 
      Caption         =   "&Find Name"
      Height          =   372
      Left            =   3960
      TabIndex        =   1
      Top             =   4080
      Width           =   1692
   End
   Begin VB.Label lblDirNam 
      Caption         =   "Directory:"
      Height          =   252
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   3612
   End
End
Attribute VB_Name = "frmLngFil"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit




Function outDirNam_Path(sPthTxt As String)
    Dim sSubDir As String
    Dim iIndLvl As Integer
    Dim ii As Integer
    
    ' Request for current path name
    If ("" = sPthTxt) Then
        outDirNam_Path = outDirNam.FullPath(outDirNam.ListIndex)
        Exit Function
    End If
    
    ' Clear file name list
    outDirNam.Clear
    
    ' Add directory list
    sSubDir = sPthTxt
    While ("" <> sSubDir)
        outDirNam.AddItem (StrTokStr(sSubDir, "\"))
        outDirNam.Indent(iIndLvl) = iIndLvl
        iIndLvl = iIndLvl + 1
    Wend
    
    GetDirLst outDirNam, sPthTxt, iIndLvl

    For ii = 0 To (iIndLvl - 1)
        outDirNam.Expand(ii) = True
    Next ii
    
    outDirNam.ListIndex = iIndLvl - 1

End Function


Private Sub cmdFndNam_Click()
    ' Clear file name list
    lstFilNam.Clear
    GetFilLst lstFilNam, outDirNam_Path("")
End Sub




Private Sub Form_Load()
    ' Set working directory to directory containing the application.
    ' This will insure that DLL's can be found (if not in path)
    ChDrive App.Path
    ChDir App.Path
    
    dirDirNam_MH.Path = "c:\inet"
    outDirNam_Path "c:\inet"
    
End Sub









Private Sub outDirNam_Collapse(ListIndex As Integer)
    outDirNam.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
End Sub


Private Sub outDirNam_DblClick()
    outDirNam_PictureDblClick (outDirNam.ListIndex)
End Sub


Private Sub outDirNam_Expand(ListIndex As Integer)
    outDirNam.PictureType(ListIndex) = MSOUTLINE_PICTURE_OPEN
End Sub


Private Sub outDirNam_PictureDblClick(ListIndex As Integer)
    ' This does not work!
    ' outDirNam.Expand(outDirNam.ListIndex) = Not (0 = outDirNam.Expand(outDirNam.ListIndex))

    ' Toggle expand / collapse setting
    ' outDirNam.Expand(outDirNam.ListIndex) = (outDirNam.PictureType(outDirNam.ListIndex) = MSOUTLINE_PICTURE_CLOSED)
    
    ' Reset path value
    outDirNam_Path (outDirNam.FullPath(ListIndex))
    
    ' Update file name list box
    cmdFndNam_Click
    
End Sub


