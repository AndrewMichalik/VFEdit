Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1996
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

Declare Function FindFirstFile Lib "Kernel" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Declare Function FindClose Lib "Kernel" (ByVal hFindFile As Long) As Long

Declare Function FIOFndFst Lib "dlgfio.dll" (ByVal lpFilNam As String, lpFindFileData As WIN32_FIND_DATA) As Long
Declare Function FIOFndNxt Lib "dlgfio.dll" (ByVal hFndHdl As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Declare Function FIOFndEnd Lib "dlgfio.dll" (ByVal hFndHdl As Long) As Long

Const STRNULDEL = 0

Const FILE_ATTRIBUTE_READONLY = &H1
Const FILE_ATTRIBUTE_HIDDEN = &H2
Const FILE_ATTRIBUTE_SYSTEM = &H4
Const FILE_ATTRIBUTE_DIRECTORY = &H10
Const FILE_ATTRIBUTE_ARCHIVE = &H20
Const FILE_ATTRIBUTE_NORMAL = &H80
Const FILE_ATTRIBUTE_TEMPORARY = &H100
Const FILE_ATTRIBUTE_COMPRESSED = &H800



Sub GetDirLst (ctlDirLst As Control, sPthTxt As String, iIndLvl As Integer)
    Dim lFndHdl As Long
    Dim sFilNam As String
    Dim lpFindFileData As WIN32_FIND_DATA
    
    ' Append trailing "\"
    If (Right(sPthTxt, 1) <> "\") Then sPthTxt = sPthTxt & "\"
    
    ' Get first directory name; test for valid handle
    lFndHdl = FIOFndFst(sPthTxt & "*", lpFindFileData)
    If (-1 = lFndHdl) Then Exit Sub
    
    ' Add to list if attributes are OK
    sFilNam = StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
    If ((FILE_ATTRIBUTE_DIRECTORY And lpFindFileData.dwFileAttributes) And ("." <> sFilNam)) Then
        ctlDirLst.AddItem sFilNam
        ctlDirLst.Indent(ctlDirLst.ListCount - 1) = iIndLvl
    End If
            
    ' Find additional matches
    While (0 <> FIOFndNxt(lFndHdl, lpFindFileData))
        sFilNam = StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
        If ((FILE_ATTRIBUTE_DIRECTORY And lpFindFileData.dwFileAttributes) And (".." <> sFilNam)) Then
            ctlDirLst.AddItem sFilNam
            ctlDirLst.Indent(ctlDirLst.ListCount - 1) = iIndLvl
        End If
    Wend
    lFndHdl = FIOFndEnd(lFndHdl)

End Sub

Function GetDirPth (ctlDirLst As Control) As String
    On Error GoTo GetDirPthErr
    ' Request for current path name
    GetDirPth = ctlDirLst.FullPath(ctlDirLst.ListIndex)
    Exit Function

GetDirPthErr:
    GetDirPth = ""
    Exit Function
End Function

Sub GetFilLst (ctlFilLst As Control, ByVal sPthTxt As String)
    Dim lFndHdl As Long
    Dim ulRetCod As Long
    Dim lpFindFileData As WIN32_FIND_DATA
    Const FILINCFLG = FILE_ATTRIBUTE_READONLY Or FILE_ATTRIBUTE_ARCHIVE Or FILE_ATTRIBUTE_NORMAL
    Const FILEXCFLG = FILE_ATTRIBUTE_HIDDEN Or FILE_ATTRIBUTE_SYSTEM Or FILE_ATTRIBUTE_DIRECTORY
    

    ' Get long file name; test for valid handle
    lFndHdl = FIOFndFst(sPthTxt, lpFindFileData)
    If (-1 = lFndHdl) Then Exit Sub
    
    ' Add to list if attributes are OK
    If (FILINCFLG And lpFindFileData.dwFileAttributes) And (0 = (FILEXCFLG And lpFindFileData.dwFileAttributes)) Then
        ctlFilLst.AddItem StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
    End If
 
    ' Find additional matches
    While (0 <> FIOFndNxt(lFndHdl, lpFindFileData))
        If (FILINCFLG And lpFindFileData.dwFileAttributes) And (0 = (FILEXCFLG And lpFindFileData.dwFileAttributes)) Then
            ctlFilLst.AddItem StrTokStr(lpFindFileData.cFileName, Chr$(STRNULDEL))
        End If
    Wend
    lFndHdl = FIOFndEnd(lFndHdl)
End Sub

Sub SetDirPth (ctlDirLst As Control, ByVal sPthTxt As String)
    Dim sSubDir As String
    Dim iIndLvl As Integer
    Dim ii As Integer

    ' Is this the drive letter from the DriveListBox?
    If (sPthTxt Like "?: *") Then sPthTxt = Left(sPthTxt, 2)
    
    ' Clear file name list
    ctlDirLst.Clear

    ' Add directory list
    sSubDir = sPthTxt
    While ("" <> sSubDir)
        ctlDirLst.AddItem (StrTokStr(sSubDir, "\"))
        ctlDirLst.Indent(iIndLvl) = iIndLvl
        iIndLvl = iIndLvl + 1
    Wend

    GetDirLst ctlDirLst, sPthTxt, iIndLvl

    For ii = 0 To (iIndLvl - 1)
        ctlDirLst.Expand(ii) = True
    Next ii

    ctlDirLst.ListIndex = iIndLvl - 1

End Sub

