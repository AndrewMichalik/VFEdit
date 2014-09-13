''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Global variables shared by all modules
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Anti-aliasing filter types; must synchronize with C def!
Global Const AAFALGNRM = 2              ' Fast integer

' Re-sampling interpolation types; must synchronize with C def!
Global Const RESALGNRM = 3              ' Linear Normal

' Fade In/Out types; must synchronize with C def!
Global Const FADALGNRM = 1              ' Exponential Normal

' Audio device interface functions
Declare Function AudDevCfgLod Lib "vfecif.dll" (pCfgMem As Long, ByVal usCtlPro As Integer, ByVal pszCfgFil As String, ByVal pszSecNam As String) As Integer
Declare Function AudDevCfgQry Lib "vfecif.dll" (pCfgMem As Long, ByVal usCtlPro As Integer, ByVal usUsrQry As Integer) As Integer
Declare Function AudDevCfgRel Lib "vfecif.dll" (pCfgMem As Long, ByVal usCtlPro As Integer, ByVal pszCfgFil As String, ByVal pszSecNam As String) As Integer
Declare Function AudDevOpn Lib "vfecif.dll" (ppAudRes As Long, ByVal usCtlPro As Integer, ByVal usPCMTyp As Integer, ByVal usChnCnt As Integer, ByVal ulSmpFrq As Long, ByVal usBlkLen As Integer, ByVal usBlkCnt As Integer, ByVal pCfgMem As Long, ByVal hEvtWnd As Integer, ByVal ulEvtArg As Long, ByVal pszTmpDIr As String, ByVal pszDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudDevCls Lib "vfecif.dll" (ppAudRes As Long) As Integer
Declare Function AudDevSta Lib "vfecif.dll" (ByVal pAudRes As Long, pTimPos As Long) As Integer
Declare Function AudDevPlaCue Lib "vfecif.dll" (ByVal pAudRes As Long, ByVal pAudFil As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal ulPosVec As Long, ByVal flCvtVec As Single, ByVal ulLopCnt As Long, ByVal usAAFTyp As Integer, ByVal usResAlg As Integer, ByVal pAmpDsp As Long, ByVal hPolWnd As Long, ByVal ulPolArg As Long) As Integer
Declare Function AudDevPlaBeg Lib "vfecif.dll" (ByVal pAudRes As Long) As Integer
Declare Function AudDevPlaResEnu Lib "vfecif.dll" (pusResAlg As Integer, ByVal szDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudDevPlaAAFEnu Lib "vfecif.dll" (pusAAFAlg As Integer, ByVal szDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudDevRecCue Lib "vfecif.dll" (ByVal pAudRes As Long, ByVal pAudFil As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal ulRsv001 As Long, ByVal usAAFTyp As Integer, ByVal usResAlg As Integer, ByVal pAmpDsp As Long, ByVal hPolWnd As Long, ByVal ulPolArg As Long) As Integer
Declare Function AudDevRecBeg Lib "vfecif.dll" (ByVal pAudRes As Long) As Integer
Declare Function AudDevRecLvl Lib "vfecif.dll" (ByVal pAudRes As Long, ByVal flLvlTim As Single) As Long
Declare Function AudDevRecGet Lib "vfecif.dll" (ByVal pAudRes As Long) As Long
Declare Function AudDevRecResEnu Lib "vfecif.dll" (pusResAlg As Integer, ByVal szDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudDevRecAAFEnu Lib "vfecif.dll" (pusAAFAlg As Integer, ByVal szDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudDevPau Lib "vfecif.dll" (ByVal pAudRes As Long, ByVal usResFlg As Integer) As Long
Declare Function AudDevStp Lib "vfecif.dll" (ByVal pAudRes As Long) As Long

Declare Function AudDevCtlEnu Lib "vfecif.dll" (usCtlPro As Integer, ByVal sDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudDevPCMEnu Lib "vfecif.dll" (ByVal usCtlPro As Integer, usPCMTyp As Integer, ByVal sDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudDevFrqEnu Lib "vfecif.dll" (ByVal usCtlPro As Integer, ByVal usPCMTyp As Integer, ByVal usChnCnt As Integer, ulSmpFrq As Long) As Integer
 

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Audio Device control protocol masks
' Note: Must match definitions in VFECIF.DLL
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Global Const CTLPROTYP = &HF000             ' Control protocol mask
Global Const CTLPRODIR = &HF00              ' Control protocol direction mask
Global Const CTLPROINP = &H200              ' Control protocol direction input
Global Const CTLPROOUT = &H400              ' Control protocol direction output

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Private variables for this modules
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim pAudResCur As Long                  ' Currently opened audio device

Function AudDevAct () As Integer
    Dim lTimPos As Long
    AudDevAct = (0 <> AudDevSta(AudDevGet(), lTimPos))
End Function

Function AudDevCnt ()
    Dim iCtlPro As Integer
    Dim sDesStr As String
    Dim iDevCnt As Integer
    sDesStr = String(255, Chr$(STRNULDEL))

    ' Scan for .DLL supported devices; count
    While (AudDevCtlEnu(iCtlPro, sDesStr, Len(sDesStr)))
        iDevCnt = iDevCnt + 1
    Wend
    AudDevCnt = iDevCnt

End Function

Function AudDevGet () As Long
    AudDevGet = pAudResCur
End Function

Function AudDevSel (sDevTyp As String) As String
    Dim tDevTyp As VFEDEVTYP
    Dim sOpnDes As String
    Dim iRetCod As Integer
    Dim lCfgMem As Long
    
    ' Assume success
    AudDevSel = ""

    ' Query for device selection
    If ("" = sDevTyp) Then sDevTyp = FrmModShw(frmVFEMDI, frmAudDev, sDevTyp, CTR_MIDMIDNON)
    If ("" = sDevTyp) Then Exit Function    ' Cancel?
    TypStrToDev sDevTyp, tDevTyp

    ' Query configuration if requested
    sOpnDes = String(255, Chr$(STRNULDEL))
    iRetCod = AudDevCfgLod(lCfgMem, tDevTyp.iCtlPro, sPrfFilNam, tDevTyp.sDevDes)
    If (tDevTyp.iCfgQry) Then
        iRetCod = AudDevCfgQry(lCfgMem, tDevTyp.iCtlPro, True)
        If (iRetCod) Then   ' Cancel?
            iRetCod = AudDevCfgRel(lCfgMem, tDevTyp.iCtlPro, "", "")
            Exit Function
        End If
    End If

    ' Close previously open device
    AudDevSelNul

    ' Attempt to open device
    iRetCod = AudDevOpn(pAudResCur, tDevTyp.iCtlPro, tDevTyp.iPCMTyp, tDevTyp.iChnCnt, tDevTyp.lSmpFrq, tDevTyp.iBlkLen, tDevTyp.iBlkCnt, lCfgMem, 0, 0&, SafGetDir(PrfGetStr(PRF_OPTENVSEC, PRF_DEVDIRKEY, WRKDIRDEF)), sOpnDes, Len(sOpnDes))
    If (0 <> iRetCod) Then
        iRetCod = AudDevCfgRel(lCfgMem, tDevTyp.iCtlPro, "", "")
        AudDevSel = MSG_BADDEVOPN
        Exit Function
    End If
    
    ' If another program has focus, and call comes in on
    ' "Wait for call", Windows does not re-enable
    frmVFEMDI.Enabled = True

    ' Open successful
    PrfSetStr PRF_DEVOPNSEC, PRF_DEVTYPKEY, TypDevToStr(tDevTyp)
    If (0 <> AudDocCnt()) Then SetAudBar (True)
    iRetCod = AudDevCfgRel(lCfgMem, tDevTyp.iCtlPro, sPrfFilNam, tDevTyp.sDevDes)
    
    ' Update status line
    frmVFEMDI.ctlStaLin.Segment = MID_INPOUTDEV
    frmVFEMDI.ctlStaLin.SegCaption = SegCapGet(tDevTyp, StrTokStr(sOpnDes, Chr$(STRNULDEL)))
    
End Function

Sub AudDevSelNul ()
    Dim iRetCod As Integer

    ' Exit if audio bar is already inactive
    If (0 = pAudResCur) Then Exit Sub
    
    ' De-activate audio bar
    If (AudDevAct()) Then frmVFEMDI.cmdAudStp = True

    ' Close previously open device
    iRetCod = AudDevCls(pAudResCur)
    
    ' Update status line
    frmVFEMDI.ctlStaLin.Segment = MID_INPOUTDEV
    frmVFEMDI.ctlStaLin.SegCaption = ""
    
    ' Deactivate Audio control bar
    SetAudBar (False)
End Sub

Private Function DevTypMax (aDevTyp() As VFEDEVTYP)
    On Error GoTo DevTypMaxErr
    
    DevTypMax = (UBound(aDevTyp))
    
    Exit Function

DevTypMaxErr:
    On Error GoTo 0
    
    DevTypMax = -1
    
    Resume Next
End Function

Function FndDevIdx (aDevTyp() As VFEDEVTYP, ByVal iDefCtl As Integer) As Integer
    Dim ii As Integer
    For ii = 0 To DevTypMax(aDevTyp())
        If (iDefCtl = aDevTyp(ii).iCtlPro) Then
            FndDevIdx = ii
            Exit Function
        End If
    Next ii
    FndDevIdx = -1
End Function

Private Function SegCapGet (tDevTyp As VFEDEVTYP, sOpnDes As String) As String
    Dim iPCMTyp As Integer
    Dim sPCMDes As String
    Dim sFrqDes As String
    Dim sDesStr As String
    sDesStr = String(255, Chr$(STRNULDEL))

' AJM Test
Const QRYBSTFMT = -1
Const SELBSTFMT = "Best Match"

    ' Set device frequency description text
    If (0 = tDevTyp.lSmpFrq) Then
        sFrqDes = SELBSTFMT
    Else
        sFrqDes = Str$(tDevTyp.lSmpFrq) & " " & MSG_DESFRQ_HZ
    End If

    ' Set device PCM description text
    iPCMTyp = QRYBSTFMT
    While (AudDevPCMEnu(tDevTyp.iCtlPro, iPCMTyp, sDesStr, Len(sDesStr)))
        If (iPCMTyp = tDevTyp.iPCMTyp) Then
            sPCMDes = StrTokStr(sDesStr, Chr$(STRNULDEL))
        End If
    Wend

    ' Parse for device type description; append data description
    If ((0 = tDevTyp.iPCMTyp) And (0 = tDevTyp.lSmpFrq)) Then
        SegCapGet = sOpnDes & MSG_STALINSEP & SELBSTFMT
    Else
        SegCapGet = sOpnDes & MSG_STALINSEP & sPCMDes & " @ " & sFrqDes
    End If
End Function

Sub SetAudBar (ByVal iVisFlg As Integer)
    ' Make Audio Bar visible, do not give focus
    frmVFEMDI.picAudBar.Visible = iVisFlg And (0 <> AudDevGet()) And (0 <> AudDocCnt())
    
    ' Show stop button to indicate audio active
    frmVFEMDI.cmdAudStp.Visible = frmVFEMDI.picAudBar.Visible And AudDevAct()
    
End Sub

