Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'    (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Global Const FILE_ATTRIBUTE_READONLY = &H1
Global Const FILE_ATTRIBUTE_HIDDEN = &H2
Global Const FILE_ATTRIBUTE_SYSTEM = &H4
Global Const FILE_ATTRIBUTE_DIRECTORY = &H10
Global Const FILE_ATTRIBUTE_ARCHIVE = &H20
Global Const FILE_ATTRIBUTE_NORMAL = &H80
Global Const FILE_ATTRIBUTE_TEMPORARY = &H100
Global Const FILE_ATTRIBUTE_COMPRESSED = &H800
Global Const FILE_ATTRIBUTE_BAD_EX = &H8000

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const MAX_PATH = 260
 
Type FILETIME
   dwLowDateTime As Long
   dwHighDateTime As Long
End Type

Type WIN32_FIND_DATA
   dwFileAttributes As Long
   ftCreationTime As FILETIME
   ftLastAccessTime As FILETIME
   ftLastWriteTime As FILETIME
   nFileSizeHigh As Long
   nFileSizeLow As Long
   dwReserved0 As Long
   dwReserved1 As Long
   cFileName As String * MAX_PATH
   cAlternate As String * 14
End Type

Const VER_PLATFORM_WIN16 = -1
Const VER_PLATFORM_WIN32s = 0
Const VER_PLATFORM_WIN32_WINDOWS = 1
Const VER_PLATFORM_WIN32_NT = 2
Type OSVERSIONINFO
   dwOSVersionInfoSize As Long
   dwMajorVersion As Long
   dwMinorVersion As Long
   dwBuildNumber As Long
   dwPlatformId As Long
   szCSDVersion As String * 128   ' Maintenance string for PSS usage.
End Type

Declare Function CIFFndFst Lib "vfecif.dll" (ByVal lpFilNam As String, lpFindFileData As WIN32_FIND_DATA) As Long
Declare Function CIFFndNxt Lib "vfecif.dll" (ByVal hFndHdl As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Declare Function CIFFndEnd Lib "vfecif.dll" (ByVal hFndHdl As Long) As Long

Declare Function CIFOS_Inf Lib "vfecif.dll" (lpVersionInformation As OSVERSIONINFO) As Long

Private Sub DirLstUpd (ctlDirLst As Control, ByVal sPthTxt As String, ByVal iIndLvl As Integer)
    Dim lpFindFileData As WIN32_FIND_DATA
    Dim lFndHdl As Long
    Dim sFilNam As String
    Dim iBegIdx As Integer
    Dim ii As Integer
    Dim jj As Integer

    ' Append trailing "\"
    If (Right(sPthTxt, 1) <> "\") Then sPthTxt = sPthTxt & "\"
    
    ' Get first directory name; test for valid handle
    lFndHdl = CIFFndFst(sPthTxt & "*", lpFindFileData)
    If (-1 = lFndHdl) Then Exit Sub
    
    ' Store beginning index for sort pass
    iBegIdx = ctlDirLst.ListCount

    ' Add to list if attributes are OK
' ajm: supress "." and ".." at lower level
    sFilNam = StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
    If ((FILE_ATTRIBUTE_DIRECTORY And lpFindFileData.dwFileAttributes) And ("." <> sFilNam) And (".." <> sFilNam)) Then
        ctlDirLst.AddItem sFilNam
        ctlDirLst.Indent(ctlDirLst.ListCount - 1) = iIndLvl
    End If
            
    ' Find additional matches
    While (0 <> CIFFndNxt(lFndHdl, lpFindFileData))
        sFilNam = StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
        If ((FILE_ATTRIBUTE_DIRECTORY And lpFindFileData.dwFileAttributes) And ("." <> sFilNam) And (".." <> sFilNam)) Then
            ctlDirLst.AddItem sFilNam
            ctlDirLst.Indent(ctlDirLst.ListCount - 1) = iIndLvl
        End If
    Wend
    lFndHdl = CIFFndEnd(lFndHdl)

    ' Perform a quick sort of directory entries
    Dim sTmpLst As String
    For ii = iBegIdx To ctlDirLst.ListCount - 1
        For jj = ii To ctlDirLst.ListCount - 1
            If NamGtrThn(ctlDirLst.List(ii), ctlDirLst.List(jj)) Then
                sTmpLst = ctlDirLst.List(jj)
                ctlDirLst.List(jj) = ctlDirLst.List(ii)
                ctlDirLst.List(ii) = sTmpLst
            End If
        Next jj
    Next ii

End Sub

Function DirPthGet (ctlDirLst As Control) As String
    On Error GoTo DirPthGetErr
    Dim ii As Integer
    Dim iDirIdx As Integer
    
    ' Find current expansion level. Note that ctlDirLst.ListIndex could refer to a
    ' recently single-clicked entry, and not the current directory
    ' DirPthGet = ctlDirLst.FullPath(ctlDirLst.ListIndex) & "\"
    ' Does not show last item as expanded:
    ' If (ctlDirLst.Expand(ii) = 0) Then Exit For
    iDirIdx = 0
    For ii = 1 To (ctlDirLst.ListCount - 1)
        If (ctlDirLst.PictureType(ii) <> MSOUTLINE_PICTURE_OPEN) Then Exit For
        iDirIdx = iDirIdx + 1
    Next ii

    ' Get current path name
    DirPthGet = ctlDirLst.FullPath(iDirIdx) & "\"
    Exit Function

DirPthGetErr:
    DirPthGet = sAppWrkDir
    Exit Function
End Function

Sub DirPthSet (ctlDirLst As Control, ctlDirLbl As Control, ByVal sPthTxt As String)
    ' Replaces the _Change events for standard control
    Const DIRTXTLEN = 25
    Dim sDirBeg As String
    Dim sDirEnd As String
    Dim sShtPth As String
    Dim iIndLvl As Integer
    Dim ii As Integer

    ' Use all lower case
    sPthTxt = LCase(sPthTxt)
    
    ' Is this the drive letter from the DriveListBox?
    If (sPthTxt Like MSG_FILDRVCTL) Then sPthTxt = Left(sPthTxt, 2)

    ' Check for any path characters; Get full path name if relative to current
    If Not ((sPthTxt Like ("*[" & MSG_FILDRVCHR & "]*")) Or ("\" = Left(sPthTxt, 1))) Then
        sPthTxt = DirPthGet(ctlDirLst) & sPthTxt
    End If

    ' Get full path name if drive spec without root
    If (Right(sPthTxt, 1) = MSG_FILDRVDEF) Then sPthTxt = SafGetDir(sPthTxt)

    ' Add "\" if not already present
    If (Right(sPthTxt, 1) <> "\") Then sPthTxt = sPthTxt & "\"
    
    ' Verify valid path name
    If (0 = (GetAttr_LF(sPthTxt) And FILE_ATTRIBUTE_DIRECTORY)) Then
        Beep
        Exit Sub
    End If

    ' Convert to lower case
    sPthTxt = LCase(sPthTxt)

    ' Clear file name list
    ctlDirLst.Clear

    ' Add directory list; Expand short directory names
    sDirBeg = ""
    sDirEnd = sPthTxt
    While ("" <> sDirEnd)
        sDirBeg = sDirBeg & StrTokStr(sDirEnd, "\")
        ctlDirLst.AddItem LngNamGet(sDirBeg, sShtPth)
        ctlDirLst.Indent(iIndLvl) = iIndLvl
        iIndLvl = iIndLvl + 1
        sDirBeg = sDirBeg & "\"
    Wend

    ' Update tree contents
    DirLstUpd ctlDirLst, sPthTxt, iIndLvl

    ' Expand current level and initial selection
    For ii = 0 To (iIndLvl - 1)
        ctlDirLst.Expand(ii) = True
    Next ii
    ctlDirLst.ListIndex = iIndLvl - 1

    ' Strip trailing "\" if not drive root
    If (Not (sPthTxt Like MSG_FILDRVROO)) Then sPthTxt = Left(sPthTxt, Len(sPthTxt) - 1)
    
    ' Update directory path label
    ctlDirLbl.Caption = FilPthAdj(sPthTxt, DIRTXTLEN)

    ' Attempt to set current directory
    ' May be valid drive or directory, but not ready or permission denied.
    ' Caller must be ready to trap error
    ' Strip trailing "\" if not drive root
    If (Not (sShtPth Like MSG_FILDRVROO)) Then sShtPth = Left(sShtPth, Len(sShtPth) - 1)
    ChDir sShtPth
    Exit Sub

End Sub

Sub FilLstUpd (ctlFilLst As Control, ctlFilNam As Control, ByVal sPthTxt As String, ByVal sPatTxt As String)
    Dim lFndHdl As Long
    Dim ulRetCod As Long
    Dim lpFindFileData As WIN32_FIND_DATA
    Const FILINCFLG = FILE_ATTRIBUTE_READONLY Or FILE_ATTRIBUTE_ARCHIVE Or FILE_ATTRIBUTE_NORMAL
    Const FILEXCFLG = FILE_ATTRIBUTE_HIDDEN Or FILE_ATTRIBUTE_SYSTEM Or FILE_ATTRIBUTE_DIRECTORY

    ' Clear current contents
    ctlFilLst.Clear
    ctlFilNam.Text = sPatTxt

    ' Append trailing "\"
    If (Right(sPthTxt, 1) <> "\") Then sPthTxt = sPthTxt & "\"
    sPthTxt = sPthTxt & sPatTxt

    ' Get long file name; test for valid handle
    lFndHdl = CIFFndFst(sPthTxt, lpFindFileData)
    If (-1 = lFndHdl) Then Exit Sub
    
    ' Add to list if attributes are OK
' 10/29/98 - Win '95/98 appears to NOT be setting the NORMAL flag will other settings are off
' If (FILINCFLG And lpFindFileData.dwFileAttributes) And (0 = (FILEXCFLG And lpFindFileData.dwFileAttributes)) Then
    If (0 = (FILEXCFLG And lpFindFileData.dwFileAttributes)) Then
        ctlFilLst.AddItem StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
    End If
 
    ' Find additional matches
    While (0 <> CIFFndNxt(lFndHdl, lpFindFileData))
' 10/29/98 - Win '95/98 appears to NOT be setting the NORMAL flag will other settings are off
' If (FILINCFLG And lpFindFileData.dwFileAttributes) And (0 = (FILEXCFLG And lpFindFileData.dwFileAttributes)) Then
        If (0 = (FILEXCFLG And lpFindFileData.dwFileAttributes)) Then
            ctlFilLst.AddItem StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
        End If
    Wend
    lFndHdl = CIFFndEnd(lFndHdl)
End Sub

Function GetAttr_LF (ByVal sPthTxt As String) As Integer
    Dim lpFindFileData As WIN32_FIND_DATA
    Dim lFndHdl As Long

    ' Strip "\" by default
    If (Right(sPthTxt, 1) = "\") Then sPthTxt = Left(sPthTxt, Len(sPthTxt) - 1)
    
    ' Note: VB GetAttr() fails with cdrom root directory.
    '       _dos_filefind() fails with drive root directory,
    ' If (Right(sPthTxt, 1) = MSG_FILDRVDEF) Then
    '    GetAttr_LF = GetAttr(sPthTxt & "\")
    '    Exit Function
    ' End If
    ' Work around using DriveListBox
    Dim ii As Integer
    If (Right(sPthTxt, 1) = MSG_FILDRVDEF) Then
        For ii = 0 To frmFilOpn.drvDrvLst.ListCount - 1
            If (sPthTxt = Left(frmFilOpn.drvDrvLst.List(ii), 2)) Then
                GetAttr_LF = FILE_ATTRIBUTE_DIRECTORY
                Exit Function
            End If
        Next ii
        GetAttr_LF = FILE_ATTRIBUTE_BAD_EX
        Exit Function
    End If

    ' Get long file name; test for valid handle
    lFndHdl = CIFFndFst(sPthTxt, lpFindFileData)
    If (-1 = lFndHdl) Then
        GetAttr_LF = FILE_ATTRIBUTE_BAD_EX
        Exit Function
    End If
    lFndHdl = CIFFndEnd(lFndHdl)
    GetAttr_LF = &HFFFF And lpFindFileData.dwFileAttributes

End Function

Function GetSysVer (sSysNam As String) As Long
    Dim osVerInf As OSVERSIONINFO
    Dim lRetCod As Long

    ' Return simple OS version string
    lRetCod = CIFOS_Inf(osVerInf)
    Select Case osVerInf.dwPlatformId
        Case VER_PLATFORM_WIN16
            sSysNam = "Windows 16 bit"
        Case VER_PLATFORM_WIN32s
            sSysNam = "Windows 16 bit with 32 bit extensions"
        Case VER_PLATFORM_WIN32_WINDOWS
            sSysNam = "Windows 95"
        Case VER_PLATFORM_WIN32_NT
            sSysNam = "Windows NT"
    End Select
    GetSysVer = osVerInf.dwPlatformId

    Exit Function

End Function

Function LngNamGet (sDirNam As String, sShtNam As String)
    Dim lpFindFileData As WIN32_FIND_DATA
    Dim lFndHdl As Long
    
    ' Strip "\"
    If (Right(sDirNam, 1) = "\") Then sDirNam = Left(sDirNam, Len(sDirNam) - 1)
    
    ' DOS returns VOLID, Win '95 return fail, NT returns first directory for drives
    If (Right(sDirNam, 1) = MSG_FILDRVDEF) Then
        LngNamGet = LCase(sDirNam)
        sShtNam = sShtNam & LCase(sDirNam) & "\"
        Exit Function
    End If
    
    ' Get long name; test for valid handle
    lFndHdl = CIFFndFst(sDirNam, lpFindFileData)
    If (-1 = lFndHdl) Then
        LngNamGet = LCase(sDirNam)
        sShtNam = sShtNam & LCase(sDirNam) & "\"
        Exit Function
    End If
    lFndHdl = CIFFndEnd(lFndHdl)
    LngNamGet = StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
    sShtNam = sShtNam & StrTokStr(lpFindFileData.cAlternate, Chr$(STRNULDEL)) & "\"

End Function

Function NamGtrThn (ByVal sStr__1 As String, ByVal sStr__2 As String) As Integer
    Dim fStr__1 As Single
    Dim fStr__2 As Single

    ' Calculate numeric value
    fStr__1 = Val(sStr__1)
    fStr__2 = Val(sStr__2)

    ' String compare if either are non-numeric
    If ((0 = fStr__1) Or (0 = fStr__2) Or (fStr__1 = fStr__2)) Then
        NamGtrThn = (1 = StrComp(sStr__1, sStr__2, 1))
        Exit Function
    End If
    NamGtrThn = fStr__1 > fStr__2
    
End Function

