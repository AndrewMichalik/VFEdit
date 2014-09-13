Option Explicit

Public Const MAX_PATH = 260

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


Sub GetDirLst(ctlDirLst As Control, sPthTxt As String, iIndLvl As Integer)
    Dim lFndHdl As Long
    Dim sFilNam As String
    Dim lpFindFileData As WIN32_FIND_DATA
    
    ' Append trailing "\"
    If (Right(sPthTxt, 1) <> "\") Then sPthTxt = sPthTxt & "\"
    
    ' Get first directory name
    lFndHdl = FIOFndFst(sPthTxt & "*", lpFindFileData)
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

Sub GetFilLst(ctlFilLst As Control, sPthTxt As String)
    Dim lFndHdl As Long
    Dim ulRetCod As Long
    Dim lpFindFileData As WIN32_FIND_DATA
    
    ' Get long file name
    lFndHdl = FIOFndFst(sPthTxt & "\*", lpFindFileData)
    If (&HA1 And lpFindFileData.dwFileAttributes) Then ctlFilLst.AddItem (lpFindFileData.cFileName)
    
    ' Find additional matches
    While (0 <> FIOFndNxt(lFndHdl, lpFindFileData))
        If (&HA1 And lpFindFileData.dwFileAttributes) Then ctlFilLst.AddItem (lpFindFileData.cFileName)
    Wend
    lFndHdl = FIOFndEnd(lFndHdl)
End Sub



Function StrTokStr(sInpStr As String, ByVal sDelStr As String)
    ' Extract a token delimited string
    Dim iCurPos As Integer

    If ((sInpStr = Null) Or (sDelStr = Null) Or (0 = Len(sDelStr))) Then
        StrTokStr = sInpStr
        sInpStr = ""
        Exit Function
    End If

    iCurPos = InStr(sInpStr, sDelStr)
    If (0 = iCurPos) Then
        StrTokStr = sInpStr
        sInpStr = ""
        Exit Function
    End If

    StrTokStr = Left(sInpStr, iCurPos - 1)
    sInpStr = Right(sInpStr, Len(sInpStr) - iCurPos - Len(sDelStr) + 1)

End Function


