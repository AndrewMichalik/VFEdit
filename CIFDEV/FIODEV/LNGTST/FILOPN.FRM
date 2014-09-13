VERSION 2.00
Begin Form frmFilOpn 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "File Form"
   ClientHeight    =   3492
   ClientLeft      =   540
   ClientTop       =   4716
   ClientWidth     =   7068
   FontBold        =   -1  'True
   FontItalic      =   0   'False
   FontName        =   "System"
   FontSize        =   9.6
   FontStrikethru  =   0   'False
   FontUnderline   =   0   'False
   Height          =   3864
   Icon            =   FILOPN.FRX:0000
   KeyPreview      =   -1  'True
   Left            =   516
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3492
   ScaleWidth      =   7068
   Top             =   4368
   Width           =   7116
   Begin Outline outDirLst 
      Height          =   1932
      Left            =   3000
      PictureClosed   =   FILOPN.FRX:0302
      PictureOpen     =   FILOPN.FRX:045C
      TabIndex        =   11
      Top             =   840
      Width           =   2532
   End
   Begin ListBox lstFilLst 
      Height          =   1944
      Left            =   120
      TabIndex        =   10
      Top             =   840
      Width           =   2652
   End
   Begin TextBox edtFilNam 
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Top             =   420
      Width           =   2655
   End
   Begin DriveListBox drvDrvLst 
      Height          =   288
      Left            =   3000
      TabIndex        =   8
      Top             =   3120
      Width           =   2412
   End
   Begin ComboBox cboFilTyp 
      Height          =   288
      Left            =   120
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   3120
      Width           =   2652
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   5640
      TabIndex        =   5
      Top             =   240
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5640
      TabIndex        =   6
      Top             =   720
      Width           =   1215
   End
   Begin Label lblDirCur 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Label1"
      Height          =   252
      Left            =   3000
      TabIndex        =   9
      Top             =   480
      Width           =   2412
   End
   Begin Label lblFilNam 
      BackColor       =   &H00C0C0C0&
      Caption         =   "File &Name:"
      Height          =   240
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   2652
   End
   Begin Label lblDirCap 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&Directories:"
      Height          =   240
      Left            =   3000
      TabIndex        =   2
      Top             =   120
      Width           =   2412
   End
   Begin Label lblDrvCap 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Dri&ves:"
      Height          =   252
      Left            =   3000
      TabIndex        =   3
      Top             =   2880
      Width           =   2412
   End
   Begin Label lblFilTyp 
      BackColor       =   &H00C0C0C0&
      Caption         =   "List Files of &Type:"
      Height          =   252
      Left            =   120
      TabIndex        =   4
      Top             =   2880
      Width           =   2652
   End
End

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1996
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Sub cboFilTyp_Click ()
'    ' If unchanged, exit
'    If ((cboFilTyp = tFilDocTyp.sDocTyp) And (cboFilTyp.ItemData(cboFilTyp.ListIndex) = tFilDocTyp.iFilFmt)) Then Exit Sub
'
'    ' Retrieve defaults for selected document type
'    TypStrToDoc AudDocTypFnd(cboFilTyp & Chr$(VFEARGDEL) & cboFilTyp.ItemData(cboFilTyp.ListIndex)), tFilDocTyp
'
'    ' Get file extension for this type & update file selection controls
'    lstFilLst.Pattern = AudDocTypExt(tFilDocTyp)
'    lstFilLst.Refresh
'
'    ' Update format description
'    lblFilFmt = AudDocTypTxt(tFilDocTyp)
    
End Sub

Sub cmdCancel_Click ()
End Sub

Sub CmdOK_Click ()
    
lstFilLst.Clear
GetFilLst lstFilLst, edtFilNam.Text
Exit Sub
    
    Dim iFilExi As Integer
    Dim iFilAtr As Integer

    ' Remove leading and trailing spaces
    edtFilNam = Trim$(edtFilNam.Text)

    If edtFilNam.Text Like ("*[" & MSG_FILBADCHR & "]*") Then
        ' Select the offending text and Beep.
        edtFilNam.SetFocus
        edtFilNam.SelStart = InStr(edtFilNam.Text, "*[" & MSG_FILBADCHR & "]*")
        edtFilNam.SelLength = Len(edtFilNam.Text) - edtFilNam.SelStart
        Beep
        Exit Sub
    End If

    ' Initialize file name text edit and directory list
    SetFilSpc edtFilNam.Text, edtFilNam, outDirLst
        
    ' Separate path name and file name if path or wild cards specified
    If edtFilNam.Text Like "*[\:*?]*" Then
        ' Refresh all entries
'ajm        lstFilLst.Pattern = edtFilNam.Text
        lstFilLst.Refresh
        ' Save wildcard for this document type in .INI file
'ajm        If (0 <> lstFilLst.ListCount) Then PrfSetStr TypDocToSec(tFilDocTyp), PRF_TYPPATKEY, lstFilLst.Pattern
        Exit Sub
    End If
    
    ' Append default extension if there is none
    If ((MSG_FILSVACAP = Caption) Or (MSG_FILEXPCAP = Caption)) Then
        If (0 = InStr(edtFilNam.Text, ".")) Then
            Dim sExtStr As String
            Dim iDotPos As Integer
'ajm            sExtStr = AudDocTypExt(tFilDocTyp)
'ajm            iDotPos = InStr(AudDocTypExt(tFilDocTyp), ".")
            If (0 <> iDotPos) Then edtFilNam.Text = edtFilNam.Text & Mid(sExtStr, iDotPos)
        End If
    End If

    ' Append full path name
    If Right$(lblDirCur, 1) <> "\" Then lblDirCur = lblDirCur + "\"
    
    ' Check for existance and attributes
    iFilExi = SafFilExi(lblDirCur & edtFilNam.Text, iFilAtr)
    
    ' If File Open or Import, file must exist and not be weird
    If ((MSG_FILOPNCAP = Caption) Or (MSG_FILIMPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) And ((Not iFilExi) Or (0 <> (iFilAtr And (ATTR_VOLUME Or ATTR_DIRECTORY)))) Then
        ' Select the offending text and Beep.
        edtFilNam.SetFocus
        edtFilNam.SelStart = InStr(edtFilNam.Text, "*[" & MSG_FILBADCHR & "]*")
        edtFilNam.SelLength = Len(edtFilNam.Text) - edtFilNam.SelStart
        Beep
        Exit Sub
    End If

    ' Cannot save as / export if read only (or weird)
    If (((MSG_FILSVACAP = Caption) Or (MSG_FILEXPCAP = Caption)) And iFilExi) Then
        If (0 <> (iFilAtr And (ATTR_READONLY Or ATTR_VOLUME Or ATTR_DIRECTORY))) Then
            MsgBox Chr$(34) & lblDirCur & edtFilNam.Text & Chr$(34) & " " & MSG_FILRDONLY, MB_OK Or MB_ICONEXCLAMATION, Caption
            Exit Sub
        End If
        ' Query for overwrite
        If (IDOK <> MsgBox(Chr$(34) & lblDirCur & edtFilNam.Text & Chr$(34) & " " & MSG_FILOVRASK, MB_OKCANCEL Or MB_ICONEXCLAMATION, Caption)) Then Exit Sub
    End If

    ' Force read only flag if not set by user
'ajm    If (0 = chkRd_Onl) Then chkRd_Onl = CChk(iFilAtr And ATTR_READONLY)

    ' Update Import/ Export / Mix filter defaults
'ajm    If ((MSG_FILIMPCAP = Caption) Or (MSG_FILEXPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) Then
'        AAFResSet PRF_EDTFTRSEC, iIXpAAFTyp, iIXpResTyp
'    End If
Dim chkRd_Onl
Dim chkSelReg

    ' Return entered full file name & and document type
'ajm    FrmModRet Me, lblDirCur & edtFilNam.Text & Chr$(VFEARGDEL) & chkRd_Onl & Chr$(VFEARGDEL) & chkSelReg & Chr$(VFEARGDEL) & TypDocToStr(tFilDocTyp)
    
End Sub

Sub drvDrvLst_Change ()
    Dim dirDirOrg As String
    
    dirDirOrg = GetDirPth(outDirLst)
    
    ' change the outDirLst control path, it will
    ' pass the change on to the lstFilLst control
    On Error GoTo CheckError
    
    ' Get drive letter (with volume label)
    SetDirPth outDirLst, drvDrvLst.Drive
    
    ChDrive (drvDrvLst.Drive)
    
    Exit Sub

CheckError:
    'Do not disable err handler; could have invalid drive!
    
    If (Err = ERR_DSKNOTRDY) Then
        If (MsgBox(WRN_DSKNOTRDY, MB_ICONEXCLAMATION + MB_OKCANCEL, Caption) = MB_OK) Then
            Resume
        Else
            drvDrvLst.Drive = dirDirOrg
            Resume
        End If
    End If
    
    If (Err = ERR_DEVNOTAVA) Then
        MsgBox WRN_BADDEVPTH, MB_ICONEXCLAMATION, Caption
        drvDrvLst.Drive = dirDirOrg
        Resume
    End If

    MsgBox MSG_UNKERRXXX + " (#" + Error + ")", MB_ICONSTOP, Caption
    
    drvDrvLst.Drive = dirDirOrg
    
    Resume
End Sub

Sub edtFilNam_Change ()
    ' Disable OK button if no filename.
    cmdOK.Enabled = (Len(edtFilNam.Text) > 0)
End Sub

Function FilRemPth (ByVal sFulNam As String) As String
    Dim sPthNam As String
    Dim sLocNam As String
    Dim usi As Integer

    ' Check for any path characters
    If Not (sFulNam Like "*[\:]*") Then
        FilRemPth = sFulNam
        Exit Function
    End If

    ' Split full path into component parts
    For usi = 1 To Len(sFulNam) Step 1
        If (Right(sFulNam, usi) Like "*[\:]*") Then Exit For
    Next usi
    FilRemPth = Right(sFulNam, usi - 1)
    
End Function

Sub Form_Activate ()
    Dim sInpVar As String
    Dim sPrvFil As String
    Dim iRetCod As Integer
    Dim ii As Integer
    
'    ' Did the format or filter selection button trigger re-activation?
'    If iChdWasAct Then
'        iChdWasAct = False
'        Exit Sub
'    End If
    
    ' Disable input, set mouse to hourglass
'ajm    FrmUsrDis Me

    ' Retrieve input arguments from tag
    sInpVar = tag

    ' Parse for caption
    Caption = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    
    ' Yield to complete re-paints
    DoEvents

    ' Parse for previously selected file name
    sPrvFil = StrTokStr(sInpVar, Chr$(VFEARGDEL))

    ' Parse for Read Only checkbox
'ajm    chkRd_Onl = CChk(Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))))
    
    ' Parse for Selected Region checkbox
'ajm    chkSelReg = CChk(Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))))

    'Parse for previously selected document type
'ajm    TypStrToDoc AudDocTypFnd(sInpVar), tFilDocTyp

    ' Initialize file type combo box to all available, set default selection
'ajm    FilTypCBxIni tFilDocTyp.iFilFmt, cboFilTyp
'ajm    lblFilFmt = AudDocTypTxt(tFilDocTyp)

    ' If File Open dialog, re-enable format selection controls
'    If MSG_FILOPNCAP = Caption Then
'        cboFilTyp.Enabled = True
'        cmdFilFmt.Enabled = True
'        lblFilFmt.Enabled = True
'        cmdAudBut.Visible = False
'        chkRd_Onl.Visible = False
'        chkSelReg.Visible = False
'        grpIXpFtr.Visible = False
'    End If

'    ' If File Import, Export or Paste To dialog, re-enable format selection controls
'    If ((MSG_FILIMPCAP = Caption) Or (MSG_FILEXPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) Then
'        cboFilTyp.Enabled = True
'        cmdFilFmt.Enabled = True
'        lblFilFmt.Enabled = True
'        cmdAudBut.Visible = False
'        chkRd_Onl.Visible = False
'        chkSelReg.Visible = (MSG_FILEXPCAP = Caption)
'        grpIXpFtr.Visible = True
        
'        ' Get default filter and resample types; don't query user
'        iRetCod = AAFResGet("", PRF_EDTFTRSEC, iIXpAAFTyp, iIXpResTyp)
'        lstIXpFtr.Clear
'        lstIXpFtr.AddItem FtrAAFNam(iIXpAAFTyp)
'        lstIXpFtr.AddItem FtrResNam(iIXpResTyp)
'    End If

'    ' If File Save As dialog, set format selection to disabled
'    If MSG_FILSVACAP = Caption Then
'        cboFilTyp.Enabled = False
'        cmdFilFmt.Enabled = False
'        lblFilFmt.Enabled = False
'        cmdAudBut.Visible = False
'        chkRd_Onl.Visible = False
'        chkSelReg.Visible = False
'        grpIXpFtr.Visible = False
'        cboFilTyp.ForeColor = &H808080
'        lblFilTyp.ForeColor = &H808080
'    End If

'    ' Suggest file name; if file or directory does not exist, will force to default
'    ' Initialize file controls
'    SetFilSpc sPrvFil, edtFilNam, outDirLst
'    lstFilLst.Pattern = AudDocTypExt(tFilDocTyp)
'    lstFilLst.Refresh
    
    ' Initialize file list box to previously selected name
    sPrvFil = FilRemPth(sPrvFil)
    If ("" <> sPrvFil) Then
        For ii = 0 To lstFilLst.ListCount
            If (sPrvFil = lstFilLst.List(ii)) Then
                lstFilLst.ListIndex = ii
                Exit For
            End If
        Next ii
    End If
    
    ' Re-enable input, set mouse to default
'ajm    FrmUsrEna Me
    
    ' Highlight and set focus to the current selection
    edtFilNam.SelStart = 0
    edtFilNam.SelLength = Len(edtFilNam.Text)
    edtFilNam.SetFocus
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
'    helpContextID = HLP_FILOPN

    ' Display full path name in a label (first time)
    lblDirCur.Caption = GetDirPth(outDirLst)
    
    ' Insure that the controls contents are visible
'ajm    SafCtlClr Me
End Sub

Sub lstFilLst_Click ()
    ' Echo the selected name in the Text box
'ajm    edtFilNam.Text = lstFilLst.FileName
End Sub

Sub lstFilLst_DblClick ()
    'Final selection from the File Save dialog
    CmdOK_Click
End Sub

Sub lstFilLst_PathChange ()
'ajm    outDirLst.FullPath = lstFilLst.Path
'ajm    drvDrvLst.Drive = lstFilLst.Path
End Sub

Sub lstFilLst_PatternChange ()
    'Show the current search pattern in the edtFilNam control
'ajm    edtFilNam.Text = lstFilLst.Pattern
'ajm    outDirLst.FullPath = lstFilLst.Path
End Sub

Sub outDirLst_Change ()
    ' Propagate directory changes to other controls
'ajm    lstFilLst.Path = outDirLst.FullPath
    lblDirCur.Caption = GetDirPth(outDirLst)
    ChDir GetDirPth(outDirLst)
'ajm    edtFilNam.Text = lstFilLst.Pattern
End Sub

Sub outDirLst_Collapse (ListIndex As Integer)
    outDirLst.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
End Sub

Sub outDirLst_DblClick ()
    outDirLst_PictureDblClick (outDirLst.ListIndex)
End Sub

Sub outDirLst_Expand (ListIndex As Integer)
    outDirLst.PictureType(ListIndex) = MSOUTLINE_PICTURE_OPEN
End Sub

Sub outDirLst_PictureDblClick (ListIndex As Integer)
    ' Reset path value
    SetDirPth outDirLst, outDirLst.FullPath(ListIndex)
End Sub

Sub SetFilSpc (ByVal sFulNam As String, CFilNam As Control, cDirLst As Control)
    ' Update local file name
    If (sFulNam <> "") Then CFilNam.Text = FilRemPth(sFulNam)

    ' Update path and/or file name if not zero length
    If (Len(sFulNam) > Len(CFilNam.Text)) Then
        cDirLst.Path = SafGetDir(Left(sFulNam, Len(sFulNam) - Len(CFilNam.Text)))
    End If
End Sub

