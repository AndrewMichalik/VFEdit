VERSION 2.00
Begin Form frmAudBar 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   0  'None
   ClientHeight    =   795
   ClientLeft      =   1245
   ClientTop       =   5985
   ClientWidth     =   4605
   ControlBox      =   0   'False
   Height          =   1200
   KeyPreview      =   -1  'True
   Left            =   1185
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   795
   ScaleWidth      =   4605
   Top             =   5640
   Visible         =   0   'False
   Width           =   4725
   Begin SSPanel pnlAudPos 
      BevelOuter      =   1  'Inset
      Caption         =   "0.0"
      FloodColor      =   &H0000FFFF&
      FloodShowPct    =   0   'False
      Height          =   315
      Left            =   2280
      TabIndex        =   3
      Top             =   0
      Width           =   975
   End
   Begin ccSubClass sbcElaTim 
      Left            =   2640
      Messages        =   AUDBAR.FRX:0000
      PostOnMsgBox    =   -1  'True
      Top             =   300
   End
   Begin SSRibbon optAudLoo 
      Height          =   264
      Left            =   1650
      PictureUp       =   AUDBAR.FRX:0406
      Top             =   0
      Width           =   264
   End
   Begin SSRibbon optAudPla 
      Height          =   264
      Left            =   1320
      PictureUp       =   AUDBAR.FRX:0500
      Top             =   0
      Width           =   264
   End
   Begin SSRibbon optAudRes 
      Height          =   264
      Left            =   0
      PictureUp       =   AUDBAR.FRX:05FA
      Top             =   0
      Width           =   264
   End
   Begin SSRibbon optAudRew 
      Height          =   264
      Left            =   330
      PictureUp       =   AUDBAR.FRX:06F4
      Top             =   0
      Width           =   264
   End
   Begin SSRibbon optAudPau 
      GroupNumber     =   2
      Height          =   264
      Left            =   990
      PictureUp       =   AUDBAR.FRX:07EE
      Top             =   0
      Width           =   264
   End
   Begin SSRibbon optAudStp 
      Height          =   264
      Left            =   660
      PictureUp       =   AUDBAR.FRX:08E8
      Top             =   0
      Width           =   264
   End
   Begin SSRibbon optAudRec 
      GroupNumber     =   3
      Height          =   264
      Left            =   3240
      PictureUp       =   AUDBAR.FRX:09E2
      Top             =   0
      Width           =   264
   End
   Begin SSRibbon optAudFFw 
      Height          =   264
      Left            =   1980
      PictureUp       =   AUDBAR.FRX:0ADC
      Top             =   0
      Width           =   264
   End
   Begin CommandButton cmdAudStp 
      Caption         =   "Stop"
      Default         =   -1  'True
      Height          =   336
      Left            =   3600
      TabIndex        =   4
      Top             =   0
      Visible         =   0   'False
      Width           =   972
   End
   Begin Label funRetVal 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "RetVal"
      Height          =   252
      Left            =   0
      TabIndex        =   0
      Top             =   420
      Visible         =   0   'False
      Width           =   852
   End
   Begin Label funPrcNam 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "PrcNam"
      Height          =   252
      Left            =   840
      TabIndex        =   1
      Top             =   420
      Visible         =   0   'False
      Width           =   852
   End
   Begin Label funInpArg 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "InpArg"
      Height          =   252
      Left            =   1680
      TabIndex        =   2
      Top             =   420
      Visible         =   0   'False
      Width           =   852
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Global form control variables
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim fPrvActFrm As form                  ' Previously active form
Dim fReqActFrm As form                  ' Previously active form Audio Doc

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Play / Record control variables
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim lAudSmpOff As Long                  ' Audio sample offset
Dim lAudSmpLen As Long                  ' Audio sample len
Dim fPlaSpdVec As Single                ' Play conversion vector
Dim lAudLopCnt As Long                  ' Audio loop count
Dim iRecOvrFlg As Integer               ' Record overlay flag

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const RECLVLTIM = .1                    ' Recording level meter update period (sec)

Sub AudBarBeg ()
    ' Show stop button, indicate audio active
    cmdAudStp.Visible = True
    AudDevActSet True
End Sub

Private Function AudBarBegPla (ByVal sInpArg As String) As String
    Dim pSesEdt As Long
    Dim pAmpDsp As Long

    ' Aready active?
    If AudDevAct() Then Exit Function
    
    ' Set source of audio request
    Set fReqActFrm = frmVFEMDI.ActiveForm
    
    ' Retrieve snippet file & amp display pointers
    pSesEdt = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    pAmpDsp = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Retrieve sample offset and count
    lAudSmpOff = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    lAudSmpLen = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Retrieve speed vector and loop count
    fPlaSpdVec = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    lAudLopCnt = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Prepare file for playback
    If (0 <> AudDevPlaCue(AudDevGet(), SesEdtFil(pSesEdt), lAudSmpOff, lAudSmpLen, fPlaSpdVec, lAudLopCnt, Val(PrfGetStr(PRF_PLACFGSEC, PRF_CFGAAFKEY, Str$(AAFALGNRM))), Val(PrfGetStr(PRF_PLACFGSEC, PRF_CFGRESKEY, Str$(RESALGNRM))), pAmpDsp, hWnd, CBK_WNDPOLMSG)) Then
        AudBarBegPla = MSG_BADAUDPLA
        AudBarPop
        Exit Function
    End If

    ' Begin playback
    If (0 <> AudDevPlaBeg(AudDevGet())) Then
        AudBarBegPla = MSG_BADAUDPLA
        AudBarPop
        Exit Function
    End If

    ' Indicate I/O operational
    AudBarBeg

    ' Test for playback type
    Select Case fPlaSpdVec
        Case -2
            No_EvtSet optAudRew, True
        Case 1
            If (lAudLopCnt <> 0) Then
                No_EvtSet optAudLoo, True
            Else
                No_EvtSet optAudPla, True
            End If
        Case 2
            No_EvtSet optAudFFW, True
    End Select

    ' No error message
    AudBarBegPla = ""
    
End Function

Private Function AudBarBegRec (ByVal sInpArg As String) As String
    Dim pSesEdt As Long
    Dim pAmpDsp As Long
    Dim iAAFTyp As Integer
    Dim iResTyp As Integer

    ' Aready active?
    If AudDevAct() Then Exit Function
    
    ' Set source of audio request
    Set fReqActFrm = frmVFEMDI.ActiveForm
    
    ' Retrieve snippet file & amp display pointers
    pSesEdt = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    pAmpDsp = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Retrieve sample offset and count
    lAudSmpOff = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    lAudSmpLen = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Set speed vector
    fPlaSpdVec = 1
    
    ' Retrieve overlay indicator and loop count
    iRecOvrFlg = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))
    lAudLopCnt = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Prepare file for recording
    ' Post process filtering during record to insure enough time for proper record operation
    If (0 <> AudDevRecCue(AudDevGet(), SesEdtFil(pSesEdt), lAudSmpOff, lAudSmpLen, 0, 0, 0, pAmpDsp, hWnd, CBK_WNDPOLMSG)) Then
        AudBarBegRec = MSG_BADAUDREC
        AudBarPop
        Exit Function
    End If

    ' Begin recording
    If (0 <> AudDevRecBeg(AudDevGet())) Then
        AudBarBegRec = MSG_BADAUDREC
        AudBarPop
        Exit Function
    End If

    ' Indicate I/O operational
    AudBarBeg

    ' Set recording type
    No_EvtSet optAudRec, True

    ' No error message
    AudBarBegRec = ""
    
End Function

Sub AudBarEnd ()
    Dim lLstPos As Long
    Dim iRetCod As Integer
    
    If AudDevAct() Then
        ' Stop I/O
        lLstPos = AudDevStp(AudDevGet())

        ' Notify form & Retrieve recording (if in record mode)
        If (optAudRec.Value = True) Then
            iRetCod = Val(VFEFrmFun(fReqActFrm, "AudDocPlaRecStp", Str$(AudDevRecGet(AudDevGet())) & Chr$(VFEARGDEL) & Str$(lAudSmpOff) & Chr$(VFEARGDEL) & Str$(lAudSmpLen)))
        Else
            iRetCod = Val(VFEFrmFun(fReqActFrm, "AudDocPlaRecStp", ""))
        End If

        ' Pop all buttons
        AudBarPop

        ' Indicate audio inactive
        cmdAudStp.Visible = False
        AudDevActSet False

        ' Complete pending events
        DoEvents
        
    End If

    ' Reset focus
    SafFocFrm fPrvActFrm

End Sub

Sub AudBarPop ()
    ' Pop all buttons
    No_EvtSet optAudRes, False
    No_EvtSet optAudRew, False
    No_EvtSet optAudStp, False
    No_EvtSet optAudPau, False
    No_EvtSet optAudPla, False
    No_EvtSet optAudLoo, False
    No_EvtSet optAudFFW, False
    No_EvtSet optAudRec, False
End Sub

Sub cmdAudStp_Click ()
    AudBarEnd
End Sub

Sub Form_Activate ()
    ' Set currently active form
    Set fPrvActFrm = frmVFEMDI.ActiveForm
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChk_Z_(KeyAscii) Then Call cmdAudStp_Click
End Sub

Sub Form_Load ()
    ' Subclass this form for elapsed time polling display
    sbcElaTim.HwndParam = hWnd

    ' Yield to complete re-paints
    DoEvents
End Sub

Sub Form_Resize ()
    Dim iBrdSiz As Integer
    
    ' Resize height
    Height = iTolButSiz + iTolButMrg
    
    ' Draw option buttons
    optAudRes.Left = 0
    optAudRew.Left = optAudRes.Left + iTolButSiz
    optAudStp.Left = optAudRew.Left + iTolButSiz
    optAudPau.Left = optAudStp.Left + iTolButSiz
    optAudPla.Left = optAudPau.Left + iTolButSiz
    optAudLoo.Left = optAudPla.Left + iTolButSiz
    optAudFFW.Left = optAudLoo.Left + iTolButSiz
    
    pnlAudPos.Left = optAudFFW.Left + iTolButSiz
    pnlAudPos.Height = iTolButSiz - (1 * Screen.TwipsPerPixelY)
    pnlAudPos.Top = Screen.TwipsPerPixelY
'    lblAudPos.Height = pnlAudPos.Height - 2 * pnlAudPos.BorderWidth
'    lblAudPos.Top = pnlAudPos.Top + pnlAudPos.BorderWidth + 2 * Screen.TwipsPerPixelY

    optAudRec.Left = pnlAudPos.Left + pnlAudPos.Width

    ' Draw Stop button
    cmdAudStp.Height = iTolButSiz
    cmdAudStp.Left = optAudRec.Left + optAudRec.Width

End Sub

Sub funPrcNam_Change ()
    ' Visual Basic does not permit functions within
    ' forms to be called directly. This routine provides
    ' that capability.
    
    ' Ignore self changing procedure name to null
    If ("" = funPrcNam) Then Exit Sub

    ' Initialize return value
    funRetVal = ""

    ' Parse incoMing request
    If (funPrcNam = "") Then Exit Sub
    If (funPrcNam = "AudBarBegPla") Then funRetVal = AudBarBegPla(funInpArg)
    If (funPrcNam = "AudBarBegRec") Then funRetVal = AudBarBegRec(funInpArg)
    If (funPrcNam = "AudBarEnd") Then AudBarEnd
    
    ' VB Bug: Activate not called when other forms set focus
    If (funPrcNam = "Form_activate") Then Form_Activate
    
    ' Clear for next call
    funPrcNam = ""

End Sub

Function No_EvtChk (cCtl As Control)
    No_EvtChk = Not cCtl.Enabled
End Function

Sub No_EvtSet (cCtl As Control, iNewVal As Integer)
    Dim iEnaOrg As Integer
    iEnaOrg = cCtl.Enabled
   
   ' Disable to indicate that value was set by internal routine
    cCtl.Enabled = False
    cCtl.Value = iNewVal
    cCtl.Enabled = iEnaOrg
End Sub

Sub optAudFFw_Click (Value As Integer)
    ' Exit if control was set without event
    If No_EvtChk(optAudFFW) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
        No_EvtSet optAudFFW, True
        Exit Sub
    End If

    ' If other audio active, terMinate all and resubmit with value=TRUE
    If AudDevAct() Then
        AudBarEnd
        optAudFFW.Value = True
        Exit Sub
    End If
    
    ' Request playback of active form
    If ("" <> VFEFrmFun(frmVFEMDI.ActiveForm, "mnuPFFW_Click", "")) Then No_EvtSet optAudFFW, False
    
End Sub

Sub optAudLoo_Click (Value As Integer)
    ' Exit if control was set without event
    If No_EvtChk(optAudLoo) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
        No_EvtSet optAudLoo, True
        Exit Sub
    End If

    ' If other audio active, terMinate all and resubmit with value=TRUE
    If AudDevAct() Then
        AudBarEnd
        optAudLoo.Value = True
        Exit Sub
    End If
    
    ' Request playback of active form
    If ("" <> VFEFrmFun(frmVFEMDI.ActiveForm, "mnuPLoop_Click", "")) Then No_EvtSet optAudLoo, False
    
End Sub

Sub optAudPau_Click (Value As Integer)
    Dim lLstPos As Long
    
    ' Exit if control was set without event
    If No_EvtChk(optAudPau) Then Exit Sub
    
    ' Disable toggle if audio inactive
    If AudDevAct() Then
        lLstPos = AudDevPau(AudDevGet(), Not Value)
    Else
        optAudPau.Value = False
        frmVFEMDI.SetFocus
    End If
End Sub

Sub optAudPla_Click (Value As Integer)
    ' Exit if control was set without event
    If No_EvtChk(optAudPla) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
        No_EvtSet optAudPla, True
        Exit Sub
    End If

    ' If other audio active, terMinate all and resubmit with value=TRUE
    If AudDevAct() Then
        AudBarEnd
        optAudPla.Value = True
        Exit Sub
    End If
    
    ' Request playback of active form
    If ("" <> VFEFrmFun(frmVFEMDI.ActiveForm, "mnuPOnce_Click", "")) Then No_EvtSet optAudPla, False
    

End Sub

Sub optAudRec_Click (Value As Integer)
    ' Exit if control was set without event
    If No_EvtChk(optAudRec) Then Exit Sub
    
    ' Stay down if already down
    If Value = False Then
        No_EvtSet optAudRec, True
        Exit Sub
    End If

    ' If other audio active, terminate all and resubmit with value=TRUE
    If AudDevAct() Then
        AudBarEnd
        optAudRec.Value = True
        Exit Sub
    End If
    
    'Request recording for active form; reset button if record failed
    If ("" <> VFEFrmFun(frmVFEMDI.ActiveForm, "mnuROnce_Click", "")) Then No_EvtSet optAudRec, False

End Sub

Sub optAudRes_Click (Value As Integer)
    If (Value = False) Then Exit Sub
    optAudRes.Value = False
    
    ' Exit if control was set without event
    If No_EvtChk(optAudRes) Then Exit Sub
    
    ' Disable toggle if audio inactive
    If (Not AudDevAct()) Then frmVFEMDI.SetFocus
End Sub

Sub optAudRew_Click (Value As Integer)
    If (Value = False) Then Exit Sub
    optAudRew.Value = False
    
    ' Exit if control was set without event
    If No_EvtChk(optAudRew) Then Exit Sub
    
    ' Disable toggle if audio inactive
    If (Not AudDevAct()) Then frmVFEMDI.SetFocus
End Sub

Sub optAudStp_Click (Value As Integer)
    If (Value = False) Then Exit Sub
    AudBarEnd
    
    ' Reset after operation is complete
    optAudStp.Value = False
End Sub

Sub sbcElaTim_WndMessage (wnd As Integer, msg As Integer, wp As Integer, lp As Long, retval As Long, nodef As Integer)
    Static sDesStr As String
    Static lLstTim As Long
    Dim iRetCod As Integer
    
    ' Initialize activity description string & start time
    If (LNGPOLBEG = wp) Then
        sDesStr = CIFGetStr(CInt(lp), "Working") & "... "
        pnlAudPos.Caption = DblRndAsc(0, DECPRCDEF)
        lLstTim = 0
        lp = 0
    End If
    
    ' Update displays if time has changed & update last time setting
    If (lLstTim <> lp) Then
        LvlPolPct wp, sDesStr, AudDevRecLvl(AudDevGet(), RECLVLTIM)
        pnlAudPos.Caption = DblRndAsc(lp / 1000!, DECPRCDEF)
        lLstTim = lp
    End If

    ' Stop if buffers are empty
    If (LNGPOLEMP = wp) Then
        AudBarEnd
    End If
    
    If (LNGPOLEND = wp) Then
        LvlPolPct wp, "", 0
    End If
    
    ' Return TRUE to continue processing
    retval = True
End Sub

