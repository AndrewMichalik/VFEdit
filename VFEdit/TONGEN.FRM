VERSION 2.00
Begin Form frmTonGen 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Tones"
   ClientHeight    =   3480
   ClientLeft      =   492
   ClientTop       =   1680
   ClientWidth     =   5760
   Height          =   3852
   KeyPreview      =   -1  'True
   Left            =   468
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3480
   ScaleWidth      =   5760
   Top             =   1332
   Width           =   5808
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   2400
      TabIndex        =   31
      Top             =   2520
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4440
      TabIndex        =   30
      Top             =   3000
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4440
      TabIndex        =   29
      Top             =   2520
      Width           =   1215
   End
   Begin SSFrame grpCusFrq 
      Caption         =   "&Custom"
      ForeColor       =   &H00000000&
      Height          =   2295
      Left            =   2400
      TabIndex        =   20
      Top             =   120
      Width           =   3255
      Begin SpinButton spnCusFrq 
         Height          =   315
         Index           =   2
         Left            =   1440
         Top             =   1080
         Width           =   255
      End
      Begin SpinButton spnCusFrq 
         Height          =   315
         Index           =   1
         Left            =   1440
         Top             =   720
         Width           =   255
      End
      Begin SpinButton spnCusLen 
         Height          =   315
         Left            =   1440
         Top             =   1800
         Width           =   255
      End
      Begin SpinButton spnCusAmp 
         Height          =   315
         Index           =   2
         Left            =   2880
         Top             =   1080
         Width           =   255
      End
      Begin SpinButton spnCusAmp 
         Height          =   315
         Index           =   1
         Left            =   2880
         Top             =   720
         Width           =   255
      End
      Begin TextBox edtCusLen 
         Alignment       =   1  'Right Justify
         Height          =   315
         Left            =   120
         TabIndex        =   28
         Text            =   "20"
         Top             =   1800
         Width           =   1335
      End
      Begin TextBox edtCusAmp 
         Alignment       =   1  'Right Justify
         Height          =   315
         Index           =   2
         Left            =   1920
         TabIndex        =   26
         Text            =   "80"
         Top             =   1080
         Width           =   975
      End
      Begin TextBox edtCusAmp 
         Alignment       =   1  'Right Justify
         Height          =   315
         Index           =   1
         Left            =   1920
         TabIndex        =   25
         Text            =   "80"
         Top             =   720
         Width           =   975
      End
      Begin TextBox edtCusFrq 
         Alignment       =   1  'Right Justify
         Height          =   315
         Index           =   2
         Left            =   120
         TabIndex        =   23
         Text            =   "0"
         Top             =   1080
         Width           =   1335
      End
      Begin TextBox edtCusFrq 
         Alignment       =   1  'Right Justify
         Height          =   315
         Index           =   1
         Left            =   120
         TabIndex        =   22
         Text            =   "0"
         Top             =   720
         Width           =   1335
      End
      Begin Label lblCusLen 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Length (msec):"
         Height          =   255
         Left            =   120
         TabIndex        =   27
         Top             =   1560
         Width           =   1575
      End
      Begin Label lblCusAmp 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Amplitude (%):"
         Height          =   255
         Left            =   1920
         TabIndex        =   24
         Top             =   420
         Width           =   1215
      End
      Begin Label lblCusFrq 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Frequency (Hz):"
         Height          =   255
         Left            =   120
         TabIndex        =   21
         Top             =   420
         Width           =   1575
      End
   End
   Begin SSFrame grpTonPad 
      Caption         =   "&DTMF"
      ForeColor       =   &H00000000&
      Height          =   3255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2175
      Begin SpinButton spnPadAmp 
         Height          =   285
         Left            =   1080
         Top             =   2760
         Width           =   255
      End
      Begin TextBox edtPadAmp 
         Alignment       =   1  'Right Justify
         Height          =   288
         Left            =   120
         TabIndex        =   19
         Text            =   "80"
         Top             =   2760
         Width           =   972
      End
      Begin TextBox edtTonStr 
         Height          =   285
         Left            =   120
         TabIndex        =   17
         Top             =   2040
         Width           =   1935
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "D"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   13
         Left            =   1560
         TabIndex        =   16
         Top             =   1560
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "C"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   12
         Left            =   1560
         TabIndex        =   12
         Top             =   1140
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "B"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   11
         Left            =   1560
         TabIndex        =   8
         Top             =   720
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "A"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   10
         Left            =   1560
         TabIndex        =   4
         Top             =   300
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "#"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   15
         Left            =   1080
         TabIndex        =   15
         Top             =   1560
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "*"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   14
         Left            =   120
         TabIndex        =   13
         Top             =   1560
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "9"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   9
         Left            =   1080
         TabIndex        =   11
         Top             =   1140
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "8"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   8
         Left            =   600
         TabIndex        =   10
         Top             =   1140
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "7"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   7
         Left            =   120
         TabIndex        =   9
         Top             =   1140
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "6"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   6
         Left            =   1080
         TabIndex        =   7
         Top             =   720
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "5"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   5
         Left            =   600
         TabIndex        =   6
         Top             =   720
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "4"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   4
         Left            =   120
         TabIndex        =   5
         Top             =   720
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "3"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   3
         Left            =   1080
         TabIndex        =   3
         Top             =   300
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "2"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   2
         Left            =   600
         TabIndex        =   2
         Top             =   300
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "1"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   1
         Left            =   120
         TabIndex        =   1
         Top             =   300
         Width           =   495
      End
      Begin SSCommand cmdTonPad 
         Caption         =   "0"
         FontBold        =   -1  'True
         FontItalic      =   0   'False
         FontName        =   "Arial"
         FontSize        =   18
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   435
         Index           =   0
         Left            =   600
         TabIndex        =   14
         Top             =   1560
         Width           =   495
      End
      Begin Label lblPadAmp 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Amplitude (%):"
         Height          =   252
         Left            =   120
         TabIndex        =   18
         Top             =   2520
         Width           =   1212
      End
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim pTonAudFil As Long                  ' Tone session edit temporary file
Dim fTonKeyTab(15, 1) As Single         ' DTMF Tone table: Key, Low freq, High freq

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const TONCHRARR = "0123456789ABCD*#"
Const Low = 0
Const Hgh = 1

Const ALLPCTINC = 1             ' All percent increment
Const ALLPCTMIN = 0             ' All percent minimum
Const ALLPCTMAX = 100           ' All percent maximum
Const ALLPCTFMT = "#0"          ' All percent display format

Const ALLMILINC = 1             ' All milliseconds increment
Const ALLMILMIN = 0             ' All milliseconds minimum
Const ALLMILMAX = 1000          ' All milliseconds maximum
Const ALLMILFMT = "#0"          ' All milliseconds display format

Const ALLFRQINC = 500           ' All frequency increment
Const ALLFRQMIN = 0             ' All frequency minimum
Const ALLFRQMAX = SMPFRQMAX     ' All frequency maximum
Const ALLFRQFMT = "#0"          ' All frequency display format

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Sub cmdCancel_Click ()
    FrmModRet Me, MSG_USRCANREQ
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    Dim iRetCod As Integer
    Dim ii As Integer
    Dim sTonStr As String

    ' Verify valid entries
    If EdtRngBad(edtPadAmp, ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtCusFrq(1), ALLFRQMIN, ALLFRQMAX) Then Exit Sub
    If EdtRngBad(edtCusFrq(2), ALLFRQMIN, ALLFRQMAX) Then Exit Sub
    If EdtRngBad(edtCusAmp(1), ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtCusAmp(2), ALLPCTMIN, ALLPCTMAX) Then Exit Sub
    If EdtRngBad(edtCusLen, ALLMILMIN, ALLMILMAX) Then Exit Sub
    
    ' Call tone generator
    sTonStr = edtTonStr
    Do While (0 <> Len(sTonStr))
        Dim iChrPos As Integer
        iChrPos = InStr(TONCHRARR, Left(sTonStr, 1))
        If (0 <> iChrPos) Then
            ' Generate tone and silence
            If (GenOneTon(Val(edtPadAmp), fTonKeyTab(iChrPos - 1, Low), Val(edtPadAmp), fTonKeyTab(iChrPos - 1, Hgh), DTMON_LEN)) Then Exit Do
            If (GenOneTon(0, 0, 0, 0, DTMOFFLEN)) Then Exit Do
        End If
        sTonStr = Right(sTonStr, Len(sTonStr) - 1)
    Loop
    
    ' Add in custom Tones
    If (0 <> Val(edtCusLen)) Then
        iRetCod = GenOneTon(Val(edtCusAmp(1)), Val(edtCusFrq(1)), Val(edtCusAmp(2)), Val(edtCusFrq(2)), Val(edtCusLen))
    End If

    ' Save settings
    PrfSetStr PRF_TONGENSEC, PRF_DTMSTRKEY, edtTonStr
    PrfSetStr PRF_TONGENSEC, PRF_DTMAMPKEY, edtPadAmp
    PrfSetStr PRF_TONGENSEC, PRF_CUSF01KEY, edtCusFrq(1)
    PrfSetStr PRF_TONGENSEC, PRF_CUSF02KEY, edtCusFrq(2)
    PrfSetStr PRF_TONGENSEC, PRF_CUSA01KEY, edtCusAmp(1)
    PrfSetStr PRF_TONGENSEC, PRF_CUSA02KEY, edtCusAmp(2)
    PrfSetStr PRF_TONGENSEC, PRF_CUSLENKEY, edtCusLen
    
    FrmModRet Me, ""
End Sub

Sub cmdTonPad_Click (Index As Integer)
    ' Place in edit field
    edtTonStr = edtTonStr & Mid$(TONCHRARR, Index + 1, 1)

End Sub

Sub edtCusAmp_Change (Index As Integer)
    If (Val(edtCusAmp(Index))) Then
        edtCusFrq(Index).ForeColor = OPTENACLR
        edtCusAmp(Index).ForeColor = OPTENACLR
    Else
        edtCusFrq(Index).ForeColor = OPTDISCLR
        edtCusAmp(Index).ForeColor = OPTDISCLR
    End If
End Sub

Sub edtCusAmp_GotFocus (Index As Integer)
    EdtTxtSel edtCusAmp(Index)
End Sub

Sub edtCusAmp_KeyDown (Index As Integer, KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnCusAmp_SpinUp (Index)
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnCusAmp_SpinDown (Index)
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtCusAmp(Index).SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtCusFrq_GotFocus (Index As Integer)
    EdtTxtSel edtCusFrq(Index)
End Sub

Sub edtCusFrq_KeyDown (Index As Integer, KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnCusFrq_SpinUp (Index)
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnCusFrq_SpinDown (Index)
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtCusFrq(Index).SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtCusLen_Change ()
    If (Val(edtCusLen)) Then
        lblCusFrq.ForeColor = OPTENACLR
        lblCusAmp.ForeColor = OPTENACLR
        lblCusLen.ForeColor = OPTENACLR
        edtCusLen.ForeColor = OPTENACLR
    Else
        lblCusFrq.ForeColor = OPTDISCLR
        lblCusAmp.ForeColor = OPTDISCLR
        lblCusLen.ForeColor = OPTDISCLR
        edtCusLen.ForeColor = OPTDISCLR
    End If

End Sub

Sub edtCusLen_GotFocus ()
    EdtTxtSel edtCusLen
End Sub

Sub edtPadAmp_GotFocus ()
    EdtTxtSel edtPadAmp
End Sub

Sub edtPadAmp_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnPadAmp_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnPadAmp_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtPadAmp.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtTonStr_GotFocus ()
    EdtTxtSel edtTonStr
End Sub

Sub Form_Activate ()
    Dim sInpArg As String
    
    ' Retrieve input arguments from tag
    sInpArg = tag

    ' Set caption
    Caption = MSG_TONGENCAP
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Retrieve temporary session file pointer
    pTonAudFil = Val(StrTokStr(sInpArg, Chr$(VFEARGDEL)))

    ' Retrieve current defaults
    edtTonStr = PrfGetStr(PRF_TONGENSEC, PRF_DTMSTRKEY, "")
    edtPadAmp = PrfGetStr(PRF_TONGENSEC, PRF_DTMAMPKEY, Str$(DTMAMPDEF))
    edtCusFrq(1) = PrfGetStr(PRF_TONGENSEC, PRF_CUSF01KEY, Str$(CUSFRQDEF))
    edtCusFrq(2) = PrfGetStr(PRF_TONGENSEC, PRF_CUSF02KEY, Str$(CUSFRQDEF))
    edtCusAmp(1) = PrfGetStr(PRF_TONGENSEC, PRF_CUSA01KEY, Str$(CUSAMPDEF))
    edtCusAmp(2) = PrfGetStr(PRF_TONGENSEC, PRF_CUSA02KEY, Str$(CUSAMPDEF))
    edtCusLen = PrfGetStr(PRF_TONGENSEC, PRF_CUSLENKEY, Str$(CUSLENDEF))
    
    ' Set Focus to tone string entry field
    edtTonStr.SetFocus

End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    HelpContextID = HLP_TONGEN

    Const A = 10
    Const B = 11
    Const C = 12
    Const D = 13
    Const S = 14                ' *
    Const P = 15                ' #
    
    ' Initialize tone key table
    fTonKeyTab(0, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton0", Str$(DTMLOW004))
    fTonKeyTab(1, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton1", Str$(DTMLOW001))
    fTonKeyTab(2, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton2", Str$(DTMLOW001))
    fTonKeyTab(3, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton3", Str$(DTMLOW001))
    fTonKeyTab(4, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton4", Str$(DTMLOW002))
    fTonKeyTab(5, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton5", Str$(DTMLOW002))
    fTonKeyTab(6, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton6", Str$(DTMLOW002))
    fTonKeyTab(7, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton7", Str$(DTMLOW003))
    fTonKeyTab(8, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton8", Str$(DTMLOW003))
    fTonKeyTab(9, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton9", Str$(DTMLOW003))
    fTonKeyTab(A, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButtonA", Str$(DTMLOW001))
    fTonKeyTab(B, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButtonB", Str$(DTMLOW002))
    fTonKeyTab(C, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButtonC", Str$(DTMLOW003))
    fTonKeyTab(D, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButtonD", Str$(DTMLOW004))
    fTonKeyTab(S, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton*", Str$(DTMLOW004))
    fTonKeyTab(P, Low) = PrfGetStr(PRF_TONGENSEC, "DTMFButton#", Str$(DTMLOW004))

    fTonKeyTab(0, Hgh) = DTMHGH002
    fTonKeyTab(1, Hgh) = DTMHGH001
    fTonKeyTab(2, Hgh) = DTMHGH002
    fTonKeyTab(3, Hgh) = DTMHGH003
    fTonKeyTab(4, Hgh) = DTMHGH001
    fTonKeyTab(5, Hgh) = DTMHGH002
    fTonKeyTab(6, Hgh) = DTMHGH003
    fTonKeyTab(7, Hgh) = DTMHGH001
    fTonKeyTab(8, Hgh) = DTMHGH002
    fTonKeyTab(9, Hgh) = DTMHGH003
    fTonKeyTab(A, Hgh) = DTMHGH004
    fTonKeyTab(B, Hgh) = DTMHGH004
    fTonKeyTab(C, Hgh) = DTMHGH004
    fTonKeyTab(D, Hgh) = DTMHGH004
    fTonKeyTab(S, Hgh) = DTMHGH001
    fTonKeyTab(P, Hgh) = DTMHGH003

    ' Insure that the controls contents are visible
    SafCtlClr Me

End Sub

Function GenOneTon (fAmpLow As Single, fFrqLow As Single, fAmpHgh As Single, fFrqHgh As Single, fSigLen As Long) As Integer
    ReDim fSigArr(1, 1) As Single
    Dim iSigCnt As Integer
    Dim iSigMul As Integer
    Dim iRetCod As Integer

    ' Verify correct frequencies
    ' MsgBox "Generating tone " & fFrqLow & " " & fAmpLow & "%, " & fFrqHgh & " Length: " & fSigLen

    ' Normally, the array would be set to one entry if only one signal was active.
    ' This approach is equivalent, but similiar
    If (fAmpLow * fAmpHgh) Then
        iSigMul = 1
    Else
        iSigMul = 2
    End If

    ' Note: VB stores multi-dimensional arrays different from 'C'
    iSigCnt = 2
    fSigArr(0, 0) = fAmpLow * iSigMul
    fSigArr(1, 0) = fFrqLow
    fSigArr(0, 1) = fAmpHgh * iSigMul
    fSigArr(1, 1) = fFrqHgh

    ' Call Tone generator
    iRetCod = SesEffTonGen(pTonAudFil, -1, 0, iSigCnt, fSigArr(0, 0), fSigLen / 1000#, MSG_TONGENCAP)

End Function

Sub spnCusAmp_SpinDown (Index As Integer)
    EdtBoxSpn edtCusAmp(Index), -ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnCusAmp_SpinUp (Index As Integer)
    EdtBoxSpn edtCusAmp(Index), ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnCusFrq_SpinDown (Index As Integer)
    EdtBoxSpn edtCusFrq(Index), -ALLFRQINC, ALLFRQMIN, ALLFRQMAX, ALLFRQFMT
End Sub

Sub spnCusFrq_SpinUp (Index As Integer)
    EdtBoxSpn edtCusFrq(Index), ALLFRQINC, ALLFRQMIN, ALLFRQMAX, ALLFRQFMT
End Sub

Sub spnCusLen_SpinDown ()
    EdtBoxSpn edtCusLen, -ALLMILINC, ALLMILMIN, ALLMILMAX, ALLMILFMT
End Sub

Sub spnCusLen_SpinUp ()
    EdtBoxSpn edtCusLen, ALLMILINC, ALLMILMIN, ALLMILMAX, ALLMILFMT
End Sub

Sub spnPadAmp_SpinDown ()
    EdtBoxSpn edtPadAmp, -ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

Sub spnPadAmp_SpinUp ()
    EdtBoxSpn edtPadAmp, ALLPCTINC, ALLPCTMIN, ALLPCTMAX, ALLPCTFMT
End Sub

