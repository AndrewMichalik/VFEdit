''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1996
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

Global Const MSG_FILREVASK = "Do you want to lose the changes and revert to the last saved version?"
Global Const MSG_FILRDONLY = "is read only."
Global Const MSG_FILOVRASK = "exists, overwrite?"
Global Const MSG_FILNEWCAP = "File New"
Global Const MSG_FILOPNCAP = "File Open"
Global Const MSG_FILSVACAP = "File Save As"
Global Const MSG_FILIMPCAP = "Import"
Global Const MSG_FILEXPCAP = "Export"
Global Const MSG_FILMIXCAP = "Mix"
Global Const MSG_FILUNTCAP = "Untitled: "
Global Const MSG_FILBADCHR = "> ,+|/"
Global Const MSG_FILNAMSTR = "File "
Global Const MSG_DEMVERCAP = "Working Demo"
Global Const MSG_JR_VERCAP = "VFEdit Jr. Version"
Global Const MSG_AUDPLACAP = "Play"
Global Const MSG_SELEXTCAP = "Select Region Extents"


Global Const VFEARGDEL = 44             ' Comma - argument delimeter
Global Const VFECMDDEL = 45             ' Dash - command line delimeter
Global Const NEWLINDEL = 10             ' Linefeed
Global Const CAPFILDEL = 32             ' Space


' Pre-defined Error numbers
Global Const ERR_DSKNOTRDY = 71
Global Const ERR_DEVNOTAVA = 68
Global Const ERR_DEMLIMERR = -2

' Error Messages
Global Const MSG_UNKERRXXX = "Unknown error! Please save your work and exit!"

' Warning messages
Global Const WRN_DSKNOTRDY = "Device not ready! Please check drive door."
Global Const WRN_BADDEVPTH = "This drive or path does not exist"
Global Const WRN_INSWINRES = "Insufficient resources. Close one or more windows."




Function KeyChkEsc (KeyAscii As Integer) As Integer
    If (KEY_ESCAPE = KeyAscii) Then
	KeyAscii = 0
	KeyChkEsc = True
	Exit Function
    End If
    KeyChkEsc = False
End Function

Function SafFilExi (ByVal sFilNam As String, iFilAtr As Integer) As Integer
    On Error GoTo SafFilExiErr

    ' Test if file is safe for input; Initialize to bad
    SafFilExi = False

    ' Verify valid directory specification
    iFilAtr = GetAttr(sFilNam)

    If (-1 = iFilAtr) Then Exit Function

    ' Return success
    SafFilExi = True

    Exit Function

SafFilExiErr:
    On Error GoTo 0

    iFilAtr = -1

    Resume Next
End Function

Function SafGetDir (ByVal sDirStr As String) As String
    On Error GoTo SafGetDirErr

    Dim iFilAtr As Integer

    iFilAtr = 0

    ' Accept null string as valid (.Exe Working) directory
'ajm    If ("" = sDirStr) Then sDirStr = sAppWrkDir

    ' If not "\" only then add or subtract "\"
    If (Len(sDirStr) > 1) Then
	' Add full path and "\" if drive specification only
	If (Right(sDirStr, 1) = ":") Then
	    ' Side effect of CurDir$(x) causes drive change; force back to original
	    Dim sOrgDir As String
	    sOrgDir = CurDir$
	    sDirStr = CurDir$(sDirStr)
	    ChDrive (sOrgDir)
	End If

	' Strip "\" by default (any path other than drive root)
	If (Right(sDirStr, 1) = "\") Then sDirStr = Left(sDirStr, Len(sDirStr))

	' Add full path and "\" if drive specification only
	If (Right(sDirStr, 1) = ":") Then sDirStr = sDirStr & "\"
    End If

    ' Verify valid directory specification
    ' Note: for some reason, this fails with cdrom root directory!
    iFilAtr = GetAttr(sDirStr) And ATTR_DIRECTORY

SafGetDirExit:
    On Error GoTo 0

    ' If bad directory spec, reset to valid (.Exe Working) directory
'ajm    If (0 = iFilAtr) Then sDirStr = sAppWrkDir

    ' Add "\" if not already present
    If (Right(sDirStr, 1) <> "\") Then sDirStr = sDirStr & "\"

    SafGetDir = sDirStr

    Exit Function

SafGetDirErr:
    ' Beep on directory error - don't bother with message box
    ' MsgBox "[" & Err & "] " & Error, MB_ICONEXCLAMATION, frmVFEMDI.Caption
    ' Future: eliminate beep also?
    Beep
    Resume SafGetDirExit
End Function

Function StrTokStr (sInpStr As String, ByVal sDelStr As String)
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

