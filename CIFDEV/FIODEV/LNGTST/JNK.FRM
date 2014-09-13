VERSION 2.00
Begin Form frmFilOpn 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "File Form"
   ClientHeight    =   3492
   ClientLeft      =   504
   ClientTop       =   4704
   ClientWidth     =   7068
   FontBold        =   -1  'True
   FontItalic      =   0   'False
   FontName        =   "System"
   FontSize        =   9.6
   FontStrikethru  =   0   'False
   FontUnderline   =   0   'False
   Height          =   3864
   Icon            =   LNGTST.FRX:0000
   KeyPreview      =   -1  'True
   Left            =   480
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3492
   ScaleWidth      =   7068
   Top             =   4356
   Width           =   7116
   Begin TextBox edtFilNam 
      Height          =   285
      Left            =   120
      TabIndex        =   12
      Top             =   420
      Width           =   2655
   End
   Begin FileListBox filFilLst 
      BackColor       =   &H00FFFFFF&
      Height          =   1944
      Left            =   120
      Pattern         =   "xxxxxxxx.xxx"
      TabIndex        =   11
      Top             =   780
      Width           =   2652
   End
   Begin DirListBox dirDirLst 
      Height          =   1752
      Left            =   3000
      TabIndex        =   10
      Top             =   780
      Width           =   2412
   End
   Begin DriveListBox drvDrvLst 
      Height          =   288
      Left            =   3000
      TabIndex        =   9
      Top             =   3120
      Width           =   2412
   End
   Begin ComboBox cboFilTyp 
      Height          =   288
      Left            =   120
      Style           =   2  'Dropdown List
      TabIndex        =   8
      Top             =   3120
      Width           =   2652
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   5640
      TabIndex        =   6
      Top             =   240
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5640
      TabIndex        =   7
      Top             =   720
      Width           =   1215
   End
   Begin Label lblFilNam 
      BackColor       =   &H00C0C0C0&
      Caption         =   "File &Name:"
      Height          =   240
      Left            =   120
      TabIndex        =   16
      Top             =   120
      Width           =   2652
   End
   Begin Label lblDirCap 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&Directories:"
      Height          =   240
      Left            =   3000
      TabIndex        =   15
      Top             =   120
      Width           =   2412
   End
   Begin Label lblDrvCap 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Dri&ves:"
      Height          =   252
      Left            =   3000
      TabIndex        =   14
      Top             =   2880
      Width           =   2412
   End
   Begin Label lblFilTyp 
      BackColor       =   &H00C0C0C0&
      Caption         =   "List Files of &Type:"
      Height          =   252
      Left            =   120
      TabIndex        =   13
      Top             =   2880
      Width           =   2652
   End
End

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1996
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim iChdWasAct As Integer     ' Indicates that the child form triggered activation
Dim tFilDocTyp As VFEDOCTYP   ' Current file document type
Dim iIXpAAFTyp As Integer
Dim iIXpResTyp As Integer

Sub cboFilTyp_Click ()
    ' If unchanged, exit
    If ((cboFilTyp = tFilDocTyp.sDocTyp) And (cboFilTyp.ItemData(cboFilTyp.ListIndex) = tFilDocTyp.iFilFmt)) Then Exit Sub
    
    ' Retrieve defaults for selected document type
    TypStrToDoc AudDocTypFnd(cboFilTyp & Chr$(VFEARGDEL) & cboFilTyp.ItemData(cboFilTyp.ListIndex)), tFilDocTyp

    ' Get file extension for this type & update file selection controls
    filFilLst.Pattern = AudDocTypExt(tFilDocTyp)
    filFilLst.Refresh

    ' Update format description
    lblFilFmt = AudDocTypTxt(tFilDocTyp)
    
End Sub

Sub cmdCancel_Click ()
    ' Return null file name
    FrmModRet Me, ""
End Sub

Sub cmdFilFmt_Click ()
    Dim sRetVal As String
    
    ' Indicate that frmFmtSel caused re-activation; get selected format
    iChdWasAct = True
    sRetVal = FrmModShw(Me, frmFmtSel, Caption & Chr$(VFEARGDEL) & TypDocToStr(tFilDocTyp), CTR_MIDMIDNON)

    ' Cancel?
    If (sRetVal = "") Then Exit Sub

    ' Retrieve new format selection
    TypStrToDoc sRetVal, tFilDocTyp
    
    ' Set format description
    lblFilFmt = AudDocTypTxt(tFilDocTyp)

End Sub

Sub cmdHlpBut_Click ()
     SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
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
    SetFilSpc edtFilNam.Text, edtFilNam, dirDirLst
        
    ' Separate path name and file name if path or wild cards specified
    If edtFilNam.Text Like "*[\:*?]*" Then
        ' Refresh all entries
        filFilLst.Pattern = edtFilNam.Text
        filFilLst.Refresh
        ' Save wildcard for this document type in .INI file
        If (0 <> filFilLst.ListCount) Then PrfSetStr TypDocToSec(tFilDocTyp), PRF_TYPPATKEY, filFilLst.Pattern
        Exit Sub
    End If
    
    ' Append default extension if there is none
    If ((MSG_FILSVACAP = Caption) Or (MSG_FILEXPCAP = Caption)) Then
        If (0 = InStr(edtFilNam.Text, ".")) Then
            Dim sExtStr As String
            Dim iDotPos As Integer
            sExtStr = AudDocTypExt(tFilDocTyp)
            iDotPos = InStr(AudDocTypExt(tFilDocTyp), ".")
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
    If (0 = chkRd_Onl) Then chkRd_Onl = CChk(iFilAtr And ATTR_READONLY)

    ' Update Import/ Export / Mix filter defaults
    If ((MSG_FILIMPCAP = Caption) Or (MSG_FILEXPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) Then
        AAFResSet PRF_EDTFTRSEC, iIXpAAFTyp, iIXpResTyp
    End If

    ' Return entered full file name & and document type
    FrmModRet Me, lblDirCur & edtFilNam.Text & Chr$(VFEARGDEL) & chkRd_Onl & Chr$(VFEARGDEL) & chkSelReg & Chr$(VFEARGDEL) & TypDocToStr(tFilDocTyp)
    
End Sub

Sub dirDirLst_Change ()
    ' Propagate directory changes to other controls
    filFilLst.Path = dirDirLst.Path
    lblDirCur.Caption = dirDirLst.Path
    ChDir dirDirLst.Path
    edtFilNam.Text = filFilLst.Pattern
End Sub

Sub drvDrvLst_Change ()
    Dim dirDirOrg As String
    
    dirDirOrg = dirDirLst.Path

    ' change the dirDirLst control path, it will
    ' pass the change on to the filFilLst control
    On Error GoTo CheckError
    
    dirDirLst.Path = drvDrvLst.Drive
    
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

Sub filFilLst_Click ()
    ' Echo the selected name in the Text box
    edtFilNam.Text = filFilLst.FileName
End Sub

Sub filFilLst_DblClick ()
    'Final selection from the File Save dialog
    CmdOK_Click
End Sub

Sub filFilLst_PathChange ()
    dirDirLst.Path = filFilLst.Path
    drvDrvLst.Drive = filFilLst.Path
End Sub

Sub filFilLst_PatternChange ()
    'Show the current search pattern in the edtFilNam control
    edtFilNam.Text = filFilLst.Pattern
    dirDirLst.Path = filFilLst.Path
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
    
    ' Did the format or filter selection button trigger re-activation?
    If iChdWasAct Then
        iChdWasAct = False
        Exit Sub
    End If
    
    ' Disable input, set mouse to hourglass
    FrmUsrDis Me

    ' Retrieve input arguments from tag
    sInpVar = tag

    ' Parse for caption
    Caption = StrTokStr(sInpVar, Chr$(VFEARGDEL))
    
    ' Yield to complete re-paints
    DoEvents

    ' Parse for previously selected file name
    sPrvFil = StrTokStr(sInpVar, Chr$(VFEARGDEL))

    ' Parse for Read Only checkbox
    chkRd_Onl = CChk(Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))))
    
    ' Parse for Selected Region checkbox
    chkSelReg = CChk(Val(StrTokStr(sInpVar, Chr$(VFEARGDEL))))

    'Parse for previously selected document type
    TypStrToDoc AudDocTypFnd(sInpVar), tFilDocTyp

    ' Initialize file type combo box to all available, set default selection
    FilTypCBxIni tFilDocTyp.iFilFmt, cboFilTyp
    lblFilFmt = AudDocTypTxt(tFilDocTyp)

    ' If File Open dialog, re-enable format selection controls
    If MSG_FILOPNCAP = Caption Then
        cboFilTyp.Enabled = True
        cmdFilFmt.Enabled = True
        lblFilFmt.Enabled = True
        cmdAudBut.Visible = False
        chkRd_Onl.Visible = False
        chkSelReg.Visible = False
        grpIXpFtr.Visible = False
    End If

    ' If File Import, Export or Paste To dialog, re-enable format selection controls
    If ((MSG_FILIMPCAP = Caption) Or (MSG_FILEXPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) Then
        cboFilTyp.Enabled = True
        cmdFilFmt.Enabled = True
        lblFilFmt.Enabled = True
        cmdAudBut.Visible = False
        chkRd_Onl.Visible = False
        chkSelReg.Visible = (MSG_FILEXPCAP = Caption)
        grpIXpFtr.Visible = True
        
        ' Get default filter and resample types; don't query user
        iRetCod = AAFResGet("", PRF_EDTFTRSEC, iIXpAAFTyp, iIXpResTyp)
        lstIXpFtr.Clear
        lstIXpFtr.AddItem FtrAAFNam(iIXpAAFTyp)
        lstIXpFtr.AddItem FtrResNam(iIXpResTyp)
    End If

    ' If File Save As dialog, set format selection to disabled
    If MSG_FILSVACAP = Caption Then
        cboFilTyp.Enabled = False
        cmdFilFmt.Enabled = False
        lblFilFmt.Enabled = False
        cmdAudBut.Visible = False
        chkRd_Onl.Visible = False
        chkSelReg.Visible = False
        grpIXpFtr.Visible = False
        cboFilTyp.ForeColor = &H808080
        lblFilTyp.ForeColor = &H808080
    End If

    ' Suggest file name; if file or directory does not exist, will force to default
    ' Initialize file controls
    SetFilSpc sPrvFil, edtFilNam, dirDirLst
    filFilLst.Pattern = AudDocTypExt(tFilDocTyp)
    filFilLst.Refresh
    
    ' Initialize file list box to previously selected name
    sPrvFil = FilRemPth(sPrvFil)
    If ("" <> sPrvFil) Then
        For ii = 0 To filFilLst.ListCount
            If (sPrvFil = filFilLst.List(ii)) Then
                filFilLst.ListIndex = ii
                Exit For
            End If
        Next ii
    End If
    
    ' Re-enable input, set mouse to default
    FrmUsrEna Me
    
    ' Highlight and set focus to the current selection
    edtFilNam.SelStart = 0
    edtFilNam.SelLength = Len(edtFilNam.Text)
    edtFilNam.SetFocus
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_FILOPN

    ' Display full path name in a label (first time)
    lblDirCur.Caption = dirDirLst.Path
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub lstIXpFtr_Click ()
    ' Query user for default filter and resample types, don't save as default (yet)
    ' Indicate that frmFtrCfg caused re-activation
    iChdWasAct = True
    If (Not AAFResGet(Caption, "", iIXpAAFTyp, iIXpResTyp)) Then Exit Sub
    
    ' Re-load filter list box
    lstIXpFtr.Clear
    lstIXpFtr.AddItem FtrAAFNam(iIXpAAFTyp)
    lstIXpFtr.AddItem FtrResNam(iIXpResTyp)
End Sub

Sub SetFilSpc (ByVal sFulNam As String, CFilNam As Control, cDirLst As Control)
    ' Update local file name
    If (sFulNam <> "") Then CFilNam.Text = FilRemPth(sFulNam)

    ' Update path and/or file name if not zero length
    If (Len(sFulNam) > Len(CFilNam.Text)) Then
        cDirLst.Path = SafGetDir(Left(sFulNam, Len(sFulNam) - Len(CFilNam.Text)))
    End If
End Sub

