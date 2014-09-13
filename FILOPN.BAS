''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

 Function FilPthAdj (ByVal sFileName As String, iMaxLen As Integer) As String
    If Len(sFileName) Then
	Dim iPos As Integer, iPos0 As Integer, iPos1 As Integer, iPos2 As Integer, iPos3 As Integer, iPos4 As Integer
	iPos = FilPthIns(0, Left$(sFileName, Len(sFileName) - 1), "\")
	iPos0 = InStr(sFileName, ":")
	iPos1 = InStr(sFileName, "\")
	iPos2 = InStr(iPos1, sFileName, "\"): iPos2 = iPos1 + iPos2
	iPos3 = InStr(iPos2, sFileName, "\"): iPos3 = iPos2 + iPos3
	iPos4 = InStr(iPos3, sFileName, "\"): iPos4 = iPos3 + iPos4
	If Len(sFileName) > iMaxLen Then
	    If (iPos4 <> 0) And iPos4 + Len(Right(sFileName, iPos)) <= iMaxLen - 2 Then
		sFileName = Left$(sFileName, iPos4) & "..." & Right(sFileName, Len(sFileName) - iPos)
	    ElseIf (iPos3 > 0) And iPos3 + Len(Mid$(sFileName, iPos)) <= iMaxLen - 2 Then
		sFileName = Left$(sFileName, iPos3) & "..." & Right(sFileName, Len(sFileName) - iPos)
	    ElseIf (iPos3 > 0) And iPos3 + Len(Mid$(sFileName, iPos)) <= iMaxLen - 2 Then
		sFileName = Left$(sFileName, iPos2) & "..." & Right(sFileName, Len(sFileName) - iPos)
	    Else
		sFileName = Left$(sFileName, iPos0 + 1) & "..." & Right(sFileName, Len(sFileName) - iPos)
	    End If
	End If
    End If
 FilPthAdj = sFileName
'    FilPthAdj = Left$(sFileName, Len(sFileName) - 1)
End Function

Private Function FilPthIns (ByVal iStart As Integer, ByVal sTarget As String, ByVal SPattern As String)
    Dim IPtr As Integer, IPLen As Integer
    IPLen = Len(SPattern)
    If ((Len(sTarget) = 0) Or (IPLen = 0) Or (Len(SPattern) > Len(sTarget))) Then Exit Function
    If (iStart = 0) Then iStart = 1
    If (iStart >= (Len(sTarget))) Then iStart = Len(sTarget)
    iStart = Len(sTarget) - iStart + 1
    On Error Resume Next
    For IPtr = iStart To 1 Step True
	If (SPattern = Mid$(sTarget, IPtr, IPLen)) Then
	    'found it
	    FilPthIns = IPtr
	    Exit For
	End If
    Next IPtr
End Function

Sub FilTypCBxIni (ByVal iFilFmt As Integer, cCboBox As ComboBox)
    ' Initialize file type combo box
    Dim iCurIdx As Integer
    Dim dsFilTyp As dynaset
    Set dsFilTyp = dFilTypMDB.CreateDynaset("SELECT sDocTyp, iFilFmt FROM tbFilTyp GROUP BY sDocTyp, iFilFmt")

    cCboBox.Clear
    iCurIdx = 0
    Do While (Not dsFilTyp.EOF)
	cCboBox.AddItem dsFilTyp("sDocTyp")
	cCboBox.ItemData(cCboBox.NewIndex) = dsFilTyp("iFilFmt")
	If iFilFmt = dsFilTyp("iFilFmt") Then
	    'If the requested iFilFmt format is current entry, remember its index
	    iCurIdx = cCboBox.NewIndex
	End If
	dsFilTyp.MoveNext
    Loop

    ' Note: This triggers the combo box click event
    cCboBox.ListIndex = iCurIdx

End Sub

Private Function FilAskNam (ByVal sReqTyp As String, ByVal sFilNam As String, tNewDoc As VFEDOCTYP, iRd_Onl As Integer, iSelReg As Integer) As String
    Dim sRetVal As String

    ' Suggest default directory & file name
    If ("" = sFilNam) Then sFilNam = PrfGetStr(PRF_AUDDOCSEC, PRF_DOCPRVKEY, "")

    ' Ask user
    sRetVal = FrmModShw(frmVFEMDI, frmFilOpn, sReqTyp & Chr$(VFEARGDEL) & sFilNam & Chr$(VFEARGDEL) & iRd_Onl & Chr$(VFEARGDEL) & iSelReg & Chr$(VFEARGDEL) & TypDocToStr(tNewDoc), CTR_MIDMIDNON)

    ' Cancel?
    If (sRetVal = "") Then
	FilAskNam = ""
	Exit Function
    End If

    ' Retrieve selected file name
    sFilNam = StrTokStr(sRetVal, Chr$(VFEARGDEL))
    
    ' Retrieve Read Only checkbox
    iRd_Onl = Val(StrTokStr(sRetVal, Chr$(VFEARGDEL)))
    
    ' Retrieve Selected Region checkbox
    iSelReg = Val(StrTokStr(sRetVal, Chr$(VFEARGDEL)))

    ' Retrieve document type
    TypStrToDoc sRetVal, tNewDoc
  
    ' Save default file name & directory suggestion
    PrfSetStr PRF_AUDDOCSEC, PRF_DOCPRVKEY, sFilNam

    ' Indicate success
    FilAskNam = sFilNam

End Function

Function VFEFilExp (tOpnDoc As VFEDOCTYP, iSelReg As Integer) As String
    ' Get file name; default format to full current document type
    VFEFilExp = FilAskNam(MSG_FILEXPCAP, "", tOpnDoc, False, iSelReg)
End Function

Function VFEFilImp (tOpnDoc As VFEDOCTYP) As String
    ' Get file name; default format to full current document type
    VFEFilImp = FilAskNam(MSG_FILIMPCAP, "", tOpnDoc, False, False)
End Function

Function VFEFilMix (tOpnDoc As VFEDOCTYP) As String
    ' Get file name; default format to full current document type
    VFEFilMix = FilAskNam(MSG_FILMIXCAP, "", tOpnDoc, False, False)
End Function

Sub VFEFilNew (sVFEDoc As String, bQryUsr As Integer)
    Dim tNewDoc As VFEDOCTYP

    ' Request format type if requested or not specified
    If (bQryUsr Or ("" = sVFEDoc)) Then
	sVFEDoc = FrmModShw(frmVFEMDI, frmFmtSel, MSG_FILNEWCAP & Chr$(VFEARGDEL) & sVFEDoc, CTR_MIDMIDNON)
	If ("" = sVFEDoc) Then Exit Sub      ' Cancel?
    End If

    ' Retrieve document type and index
    TypStrToDoc sVFEDoc, tNewDoc
    
    ' Open new document
    If ("" <> AudDocOpn("", tNewDoc, False, "")) Then Exit Sub

    ' Update recent files list (will update new document form also)
    RcnFilUpd
    
End Sub

Sub VFEFilOpn (ByVal sFilNam As String, ByVal sVFEDoc As String, sSegDes As String)
    Dim iRd_Onl As Integer

    ' sFilNam and sVFEDoc are empty except when the command line is used to specify a file
    Dim tOpnDoc As VFEDOCTYP

    ' Retrieve requested document format
    ' Note: TypStrToDoc destroys input text string to simplify parsing of input arguments
    TypStrToDoc CStr(sVFEDoc), tOpnDoc

    ' Request missing information (name or document type)
    If (("" = sFilNam) Or ("" = sVFEDoc)) Then sFilNam = FilAskNam(MSG_FILOPNCAP, sFilNam, tOpnDoc, iRd_Onl, False)

    ' Open specified document, update recent file list
    If ("" <> sFilNam) Then
	If ("" = AudDocOpn(sFilNam, tOpnDoc, iRd_Onl, sSegDes)) Then RcnFilWrt sFilNam, tOpnDoc, iRd_Onl
    End If

End Sub

Function VFEFilSvA (sFilNam As String, tVFEDoc As VFEDOCTYP) As String
    ' Get file name; default format to full current document type
    VFEFilSvA = FilAskNam(MSG_FILSVACAP, sFilNam, tVFEDoc, False, False)
End Function

