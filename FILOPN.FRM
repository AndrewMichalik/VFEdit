VERSION 2.00
Begin Form frmFilOpn 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "File Form"
   ClientHeight    =   4560
   ClientLeft      =   372
   ClientTop       =   2376
   ClientWidth     =   8412
   FontBold        =   -1  'True
   FontItalic      =   0   'False
   FontName        =   "System"
   FontSize        =   9.6
   FontStrikethru  =   0   'False
   FontUnderline   =   0   'False
   Height          =   4932
   Icon            =   FILOPN.FRX:0000
   KeyPreview      =   -1  'True
   Left            =   348
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4560
   ScaleWidth      =   8412
   Top             =   2028
   Width           =   8460
   Begin SSCheck chkSelReg 
      Caption         =   "&Selected Region Only"
      Height          =   252
      Left            =   5760
      TabIndex        =   16
      Top             =   1920
      Visible         =   0   'False
      Width           =   2292
   End
   Begin SSFrame grpIXpFtr 
      Caption         =   "F&ilters"
      ForeColor       =   &H00000000&
      Height          =   1695
      Left            =   5760
      TabIndex        =   14
      Top             =   120
      Visible         =   0   'False
      Width           =   2535
      Begin ListBox lstIXpFtr 
         Height          =   1176
         Left            =   120
         TabIndex        =   15
         Top             =   360
         Width           =   2292
      End
   End
   Begin SSFrame grpFilNam 
      ForeColor       =   &H00000000&
      Height          =   3615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5535
      Begin ListBox lstFilLst 
         Height          =   1944
         Left            =   120
         Sorted          =   -1  'True
         TabIndex        =   3
         Top             =   960
         Width           =   2652
      End
      Begin Outline outDirLst 
         Height          =   1932
         Left            =   2880
         PictureClosed   =   FILOPN.FRX:0302
         PictureLeaf     =   FILOPN.FRX:045C
         PictureMinus    =   FILOPN.FRX:053E
         PictureOpen     =   FILOPN.FRX:0620
         PicturePlus     =   FILOPN.FRX:077A
         TabIndex        =   8
         Top             =   960
         Width           =   2532
      End
      Begin ComboBox cboFilTyp 
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   5
         Top             =   3180
         Width           =   2655
      End
      Begin DriveListBox drvDrvLst 
         Height          =   288
         Left            =   2880
         TabIndex        =   10
         Top             =   3180
         Width           =   2532
      End
      Begin TextBox edtFilNam 
         Height          =   285
         Left            =   120
         TabIndex        =   2
         Top             =   480
         Width           =   2655
      End
      Begin Label lblFilTyp 
         BackColor       =   &H00C0C0C0&
         Caption         =   "List Files of &Type:"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   2940
         Width           =   2655
      End
      Begin Label lblDrvCap 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Dri&ves:"
         Height          =   255
         Left            =   3000
         TabIndex        =   9
         Top             =   2940
         Width           =   2415
      End
      Begin Label lblDirCur 
         BackColor       =   &H00C0C0C0&
         Height          =   252
         Left            =   2880
         TabIndex        =   7
         Top             =   504
         Width           =   2532
      End
      Begin Label lblDirCap 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Directories:"
         Height          =   240
         Left            =   2880
         TabIndex        =   6
         Top             =   180
         Width           =   2532
      End
      Begin Label lblFilNam 
         BackColor       =   &H00C0C0C0&
         Caption         =   "File &Name:"
         Height          =   240
         Left            =   120
         TabIndex        =   1
         Top             =   180
         Width           =   2655
      End
   End
   Begin SSCheck chkRd_Onl 
      Caption         =   "&Read Only"
      Height          =   252
      Left            =   5760
      TabIndex        =   17
      Top             =   2280
      Visible         =   0   'False
      Width           =   1332
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   7080
      TabIndex        =   20
      Top             =   4080
      Width           =   1215
   End
   Begin CommandButton cmdAudBut 
      Caption         =   "Audition"
      Height          =   375
      Left            =   5760
      TabIndex        =   21
      Top             =   4080
      Visible         =   0   'False
      Width           =   1215
   End
   Begin SSFrame grpFilFmt 
      ForeColor       =   &H00000000&
      Height          =   735
      Left            =   120
      TabIndex        =   11
      Top             =   3720
      Width           =   5535
      Begin CommandButton cmdFilFmt 
         Caption         =   "&Format"
         Height          =   375
         Left            =   120
         TabIndex        =   12
         Top             =   240
         Width           =   1215
      End
      Begin Label lblFilFmt 
         Alignment       =   2  'Center
         BackColor       =   &H00C0C0C0&
         Caption         =   "Format Description"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   7.8
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   255
         Left            =   1440
         TabIndex        =   13
         Top             =   360
         Width           =   3975
         WordWrap        =   -1  'True
      End
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   7080
      TabIndex        =   18
      Top             =   3120
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   7080
      TabIndex        =   19
      Top             =   3600
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim iChdWasAct As Integer     ' Indicates that the child form triggered activation
Dim iDirWasAct As Integer     ' Indicates that the directory list was active
Dim tFilDocTyp As VFEDOCTYP   ' Current file document type
Dim iIXpAAFTyp As Integer
Dim iIXpResTyp As Integer

Sub cboFilTyp_Click ()
    ' If unchanged, exit
    If ((cboFilTyp = tFilDocTyp.sDocTyp) And (cboFilTyp.ItemData(cboFilTyp.ListIndex) = tFilDocTyp.iFilFmt)) Then Exit Sub
    
    ' Retrieve defaults for selected document type
    TypStrToDoc AudDocTypFnd(cboFilTyp & Chr$(VFEARGDEL) & cboFilTyp.ItemData(cboFilTyp.ListIndex)), tFilDocTyp

    ' Get file extension for this type & update file selection controls
    FilPatSet lstFilLst, AudDocTypExt(tFilDocTyp)
    
    ' Show the current search pattern in the edtFilNam control
    edtFilNam.Text = FilPatGet(lstFilLst)
    
    ' Refresh file list for pattern change
    FilLstUpd lstFilLst, edtFilNam, DirPthGet(outDirLst), FilPatGet(lstFilLst)
  
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
    Dim sFilNam As String
    Dim iFilExi As Integer
    Dim iFilAtr As Integer

    ' The directory list box does not respond to the enter key (?!)
    ' This detects if the directory list box was active
    If (iDirWasAct) Then
        outDirLst_PictureDblClick (outDirLst.ListIndex)
        Exit Sub
    End If

    ' Remove leading and trailing spaces
    edtFilNam = Trim$(edtFilNam.Text)

    If edtFilNam.Text Like ("*[" & FilBadChr() & "]*") Then
        ' Select the offending text and Beep.
        edtFilNam.SetFocus
        edtFilNam.SelStart = InStr(edtFilNam.Text, "*[" & FilBadChr() & "]*")
        edtFilNam.SelLength = Len(edtFilNam.Text) - edtFilNam.SelStart
        Beep
        Exit Sub
    End If

    ' Separate path name and file name if path or wild cards specified
    If edtFilNam.Text Like ("*[" & MSG_FILWLDCHR & "]*") Then
        ' Initialize file name text edit and directory list; Refresh file entries
        If ("" <> FilRemPth(edtFilNam.Text)) Then FilPatSet lstFilLst, FilRemPth(edtFilNam.Text)
        SetFilSpc edtFilNam.Text, edtFilNam, outDirLst
        ' Save wildcard for this document type in .INI file
        If (0 <> lstFilLst.ListCount) Then PrfSetStr TypDocToSec(tFilDocTyp), PRF_TYPPATKEY, FilPatGet(lstFilLst)
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
    sFilNam = DirPthGet(outDirLst) & edtFilNam.Text
    
    ' Check for existance and attributes
    iFilExi = SafFilExi(sFilNam, iFilAtr)
    
    ' If File Open or Import, file must exist and not be weird
    If ((MSG_FILOPNCAP = Caption) Or (MSG_FILIMPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) And ((Not iFilExi) Or (0 <> (iFilAtr And (ATTR_VOLUME Or FILE_ATTRIBUTE_DIRECTORY)))) Then
        ' Select the offending text and Beep.
        edtFilNam.SetFocus
        edtFilNam.SelStart = InStr(edtFilNam.Text, "*[" & FilBadChr() & "]*")
        edtFilNam.SelLength = Len(edtFilNam.Text) - edtFilNam.SelStart
        Beep
        Exit Sub
    End If

    ' Cannot save as / export if read only (or weird)
    If (((MSG_FILSVACAP = Caption) Or (MSG_FILEXPCAP = Caption)) And iFilExi) Then
        If (0 <> (iFilAtr And (FILE_ATTRIBUTE_READONLY Or ATTR_VOLUME Or FILE_ATTRIBUTE_DIRECTORY))) Then
            MsgBox Chr$(34) & sFilNam & Chr$(34) & " " & MSG_FILRDONLY, MB_OK Or MB_ICONEXCLAMATION, Caption
            Exit Sub
        End If
        ' Query for overwrite
        If (IDOK <> MsgBox(Chr$(34) & sFilNam & Chr$(34) & " " & MSG_FILOVRASK, MB_OKCANCEL Or MB_ICONEXCLAMATION, Caption)) Then Exit Sub
    End If

    ' Force read only flag according to file attributes if not set by user
    If (0 = chkRd_Onl) Then chkRd_Onl = CChk(iFilAtr And FILE_ATTRIBUTE_READONLY)

    ' Update Import/ Export / Mix filter defaults
    If ((MSG_FILIMPCAP = Caption) Or (MSG_FILEXPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) Then
        AAFResSet PRF_EDTFTRSEC, iIXpAAFTyp, iIXpResTyp
    End If

    ' Return entered full file name & and document type
    FrmModRet Me, sFilNam & Chr$(VFEARGDEL) & chkRd_Onl & Chr$(VFEARGDEL) & chkSelReg & Chr$(VFEARGDEL) & TypDocToStr(tFilDocTyp)
    
End Sub

Sub drvDrvLst_Change ()
    On Error GoTo drvDrvLstErr
    Dim dirDirOrg As String
    
    ' Save original valid drive
    dirDirOrg = DirPthGet(outDirLst)

    ' Propagate directory changes to other controls
    ChDrive (drvDrvLst.Drive)
    DirPthSet outDirLst, lblDirCur, CurDir
    FilLstUpd lstFilLst, edtFilNam, DirPthGet(outDirLst), FilPatGet(lstFilLst)
    
    Exit Sub

drvDrvLstErr:
    ' Do not disable err handler; could have invalid drive!
    If (Err = ERR_DSKNOTRDY) Then
        If (MsgBox(WRN_DSKNOTRDY, MB_ICONEXCLAMATION + MB_OKCANCEL, Caption) = MB_OK) Then
            Resume
        Else
            SetDrvSpc drvDrvLst, dirDirOrg
            Resume
        End If
    End If
    
    ' Device or path not available
    If ((Err = ERR_DEVNOTAVA) Or (Err = ERR_PTHNOTAVA)) Then
        MsgBox WRN_BADDEVPTH, MB_ICONEXCLAMATION, Caption
        SetDrvSpc drvDrvLst, dirDirOrg
        Resume
    End If

    ' Unknown error
    MsgBox MSG_UNKERRXXX + "  (#" + Error + ")", MB_ICONSTOP, Caption
    SetDrvSpc drvDrvLst, dirDirOrg
    Resume

End Sub

Sub edtFilNam_Change ()
    ' Disable OK button if no filename.
    cmdOK.Enabled = (Len(edtFilNam.Text) > 0)
    chkRd_Onl.Enabled = True
    chkRd_Onl = False
End Sub

Function FilBadChr () As String
    ' Return bad character string based upon long file name support
    If (GetSysVer("") > 0) Then
        FilBadChr = MSG_FILBAD_32
    Else
        FilBadChr = MSG_FILBAD_16
    End If
End Function

Function FilPatGet (ctlFilLst As Control) As String
    ' Return current pattern value
    FilPatGet = ctlFilLst.Tag
End Function

Sub FilPatSet (ctlFilLst As Control, ByVal sPatTxt As String)
    ' Replaces the _PathChange and _PatternChange events for standard control
    ' Store pattern in tag field
    ctlFilLst.Tag = sPatTxt
End Sub

Function FilRemPth (ByVal sFulNam As String) As String
    Dim sPthNam As String
    Dim sLocNam As String
    Dim usi As Integer

    ' Check for any path characters
    If Not (sFulNam Like ("*[" & MSG_FILPTHCHR & "]*")) Then
        FilRemPth = sFulNam
        Exit Function
    End If

    ' Split full path into component parts
    For usi = 1 To Len(sFulNam) Step 1
        If (Right(sFulNam, usi) Like ("*[" & MSG_FILPTHCHR & "]*")) Then Exit For
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
    sInpVar = Tag

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
        chkRd_Onl.Visible = True
        chkSelReg.Visible = False
        cmdAudBut.Visible = False
        grpIXpFtr.Visible = False
    End If

    ' If File Import, Export or Paste To dialog, re-enable format selection controls
    If ((MSG_FILIMPCAP = Caption) Or (MSG_FILEXPCAP = Caption) Or (MSG_FILMIXCAP = Caption)) Then
        cboFilTyp.Enabled = True
        cmdFilFmt.Enabled = True
        lblFilFmt.Enabled = True
        chkRd_Onl.Visible = False
        chkSelReg.Visible = (MSG_FILEXPCAP = Caption)
        cmdAudBut.Visible = False
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
        chkRd_Onl.Visible = False
        chkSelReg.Visible = False
        cmdAudBut.Visible = False
        grpIXpFtr.Visible = False
        cboFilTyp.ForeColor = &H808080
        lblFilTyp.ForeColor = &H808080
    End If

    ' Suggest file name; if file or directory does not exist, will force to default
    ' Initialize file controls
    FilPatSet lstFilLst, AudDocTypExt(tFilDocTyp)
    SetFilSpc sPrvFil, edtFilNam, outDirLst

    ' Re-enable input, set mouse to default
    FrmUsrEna Me
    
    ' Highlight and set focus to the current selection
    edtFilNam.SelStart = 0
    edtFilNam.SelLength = Len(edtFilNam.Text)
    edtFilNam.SetFocus
End Sub

Sub Form_KeyPress (keyAscii As Integer)
    If KeyChkEsc(keyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_FILOPN

    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub lstFilLst_Click ()
    ' Echo the selected name in the Text box
    edtFilNam.Text = lstFilLst.List(lstFilLst.ListIndex)
    
    ' Set read only flag according to file attributes
    chkRd_Onl = CChk(GetAttr_LF(DirPthGet(outDirLst) & edtFilNam.Text) And FILE_ATTRIBUTE_READONLY)
    chkRd_Onl.Enabled = (0 = chkRd_Onl)
End Sub

Sub lstFilLst_DblClick ()
    'Final selection from the File Save dialog
    CmdOK_Click
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

Sub outDirLst_Collapse (ListIndex As Integer)
    outDirLst.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
End Sub

Sub outDirLst_DblClick ()
    outDirLst_PictureDblClick (outDirLst.ListIndex)
End Sub

Sub outDirLst_Expand (ListIndex As Integer)
    outDirLst.PictureType(ListIndex) = MSOUTLINE_PICTURE_OPEN
End Sub

Sub outDirLst_GotFocus ()
    iDirWasAct = True
End Sub

Sub outDirLst_KeyPress (keyAscii As Integer)
    Dim ii As Integer
    
    ' Forward search for first letter match
    For ii = outDirLst.ListIndex + 1 To (outDirLst.ListCount - 1)
        If (keyAscii = Asc(outDirLst.List(ii))) Then
            outDirLst.ListIndex = ii
            Exit Sub
        End If
    Next ii
    
    ' Wrap-around search for first letter match
    For ii = 0 To (outDirLst.ListCount - 1)
        If (keyAscii = Asc(outDirLst.List(ii))) Then
            outDirLst.ListIndex = ii
            Exit Sub
        End If
    Next ii

End Sub

Sub outDirLst_LostFocus ()
    iDirWasAct = False
End Sub

Sub outDirLst_PictureDblClick (ListIndex As Integer)
    On Error GoTo outDirLstErr
    
    ' Reset path value
    DirPthSet outDirLst, lblDirCur, outDirLst.FullPath(ListIndex) & "\"

    ' Propagate directory changes to other controls
    FilLstUpd lstFilLst, edtFilNam, DirPthGet(outDirLst), FilPatGet(lstFilLst)
    Exit Sub

outDirLstErr:
    Beep
    Exit Sub

End Sub

Sub SetDrvSpc (cDrvCtl As Control, sDrvSpc As String)
    On Error GoTo SetDrvSpcErr
    drvDrvLst.Drive = sDrvSpc
    Exit Sub

SetDrvSpcErr:
    drvDrvLst.Drive = sAppWrkDir
    Exit Sub

End Sub

Sub SetFilSpc (ByVal sFilSpc As String, cFilNam As Control, cDirLst As Control)
    On Error GoTo SetFilSpcErr
    Dim sDrvNam As String
    Dim sPthNam As String
    Dim sFilNam As String
    Dim ii As Integer

    ' Use current directory and wildcard specification if empty setting; append trailing "\"
    If ("" = sFilSpc) Then
        sFilSpc = CurDir
        If (Right(sFilSpc, 1) <> "\") Then sFilSpc = sFilSpc & "\"
    End If

    ' Break into component parts
    sFilNam = FilRemPth(sFilSpc)
    sPthNam = Left(sFilSpc, Len(sFilSpc) - Len(sFilNam))

    ' Propagate directory changes to other controls
    If (sPthNam Like MSG_FILDRVCHR) And (Left(drvDrvLst.Drive, 2) <> Left(sFilSpc, 2)) Then
        Dim sOrgDrv As String
        sOrgDrv = drvDrvLst.Drive
        ' Update on drive automatically does directory & file list
        ' But must set current directory (if not default) on other drive so
        ' that the drive change events results in the correct drive
        ' Future: may want to do a "long name" ChDir() so as not to trigger duplicate
        ' directory refresh from this DirPthSet() and on in drive change event
        If ("" <> sPthNam) Then DirPthSet outDirLst, lblDirCur, sPthNam
        drvDrvLst.Drive = sFilSpc
        ' Force a file list update if change drive event is not triggered
        If (sOrgDrv = drvDrvLst.Drive) Then
            FilLstUpd lstFilLst, edtFilNam, DirPthGet(outDirLst), FilPatGet(lstFilLst)
        End If
    Else
        ' Refresh file list for directory change
        If ("" <> sPthNam) Then DirPthSet outDirLst, lblDirCur, sPthNam
        FilLstUpd lstFilLst, edtFilNam, DirPthGet(outDirLst), FilPatGet(lstFilLst)
    End If
    
    ' Initialize file list box to previously selected name
    If ("" <> sFilNam) Then
        cFilNam.Text = sFilNam
        For ii = 0 To lstFilLst.ListCount
            If (sFilNam = lstFilLst.List(ii)) Then
                lstFilLst.ListIndex = ii
                lstFilLst.TopIndex = ii
                Exit For
            End If
        Next ii
    Else cFilNam.Text = FilPatGet(lstFilLst)
    End If
    
    Exit Sub

SetFilSpcErr:
    Beep
    Resume Next

End Sub

