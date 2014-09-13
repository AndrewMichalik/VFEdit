VERSION 2.00
Begin Form frmProLin 
   BackColor       =   &H00C0C0C0&
   Caption         =   "VFEdit ® ProLine/2v Control"
   ClientHeight    =   2052
   ClientLeft      =   876
   ClientTop       =   2076
   ClientWidth     =   3972
   FontBold        =   -1  'True
   FontItalic      =   0   'False
   FontName        =   "System"
   FontSize        =   9.6
   FontStrikethru  =   0   'False
   FontUnderline   =   0   'False
   Height          =   2748
   Icon            =   PROLIN.FRX:0000
   Left            =   852
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   2052
   ScaleWidth      =   3972
   Tag             =   "MainForm"
   Top             =   1404
   Width           =   4020
   Begin CommandButton cmdLinSta 
      Caption         =   "&RJ-11 Jack"
      Height          =   372
      Index           =   1
      Left            =   2520
      TabIndex        =   3
      Top             =   600
      Width           =   1332
   End
   Begin CommandButton cmdLinSta 
      Caption         =   "Ha&ngup"
      Height          =   372
      Index           =   3
      Left            =   2520
      TabIndex        =   5
      Top             =   1560
      Width           =   1332
   End
   Begin CommandButton cmdLinSta 
      Caption         =   "&Pickup"
      Height          =   372
      Index           =   2
      Left            =   2520
      TabIndex        =   4
      Top             =   1080
      Width           =   1332
   End
   Begin CommandButton cmdLinSta 
      Caption         =   "&Audio Jack"
      Height          =   372
      Index           =   0
      Left            =   2520
      TabIndex        =   2
      Top             =   120
      Width           =   1332
   End
   Begin TextBox edtLinNum 
      BackColor       =   &H00FFFFFF&
      Height          =   288
      Left            =   1560
      TabIndex        =   1
      Text            =   "2"
      Top             =   780
      Width           =   492
   End
   Begin Label lblStaLin 
      Alignment       =   2  'Center
      BackColor       =   &H00C0C0C0&
      Height          =   252
      Left            =   240
      TabIndex        =   6
      Top             =   1680
      Width           =   1812
   End
   Begin Label lblLinNum 
      BackColor       =   &H00C0C0C0&
      Caption         =   "&Line Number:"
      Height          =   252
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   1332
   End
   Begin Menu MNU_FileMenu 
      Caption         =   "&File"
      Begin Menu MNU_File_Exit 
         Caption         =   "E&xit"
      End
   End
   Begin Menu MNU_LineMenu 
      Caption         =   "&Line"
      Begin Menu MNU_Line_Audio 
         Caption         =   "&Audio Jack"
      End
      Begin Menu MNU_Line_RJ11 
         Caption         =   "&RJ-11 Jack"
      End
      Begin Menu MNU_Line_Pickup 
         Caption         =   "&Pickup"
      End
      Begin Menu MNU_Line_Hangup 
         Caption         =   "&Hangup"
      End
   End
   Begin Menu MNU_HelpMenu 
      Caption         =   "&Help"
      Begin Menu MNU_Help_About 
         Caption         =   "&About ProLin..."
      End
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1996
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim sPrfFilNam          As String       ' Default .INI File name
Dim sAppWrkDir          As String       ' Default application working directory
Dim iLinCnt             As Integer      ' Total Line Count

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const LINAUDJCK = 0                     ' Audio Jack
Const LINRJ__11 = 1                     ' RJ-11 Jack
Const LINPCK_UP = 2                     ' Pickup
Const LINHNG_UP = 3                     ' Hang Up
Const LINWAITIM = 2                     ' Line event wait time

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Const CH_AUDIOLINEIN = &HE05            ' Parm id for enabling audio jacks
Const LINEIN_DISABLE = &H0              ' Disable audio in from audio jack
Const LINEIN_ENABLE = &H1               ' Enable  audio in from audio jack

' Profile section and key strings
Const PRF_PRFNAMDEF = "PROLIN.INI"
Const PRF_SCRPOSSEC = "Screen Position"
Const PRF_SCRSTAKEY = "WindowState"
Const PRF_SCRLFTKEY = "PositionLeft"
Const PRF_SCRTOPKEY = "PositionTop"
Const PRF_SCRHGTKEY = "PositionHeight"
Const PRF_SCRWIDKEY = "PositionWidth"
Const STRNULDEL = 0                         ' Null


' Error Messages
Const MSG_PROINIERR = "Error during initialization, continue?"

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Declare Function GetSystemMetrics Lib "User" (ByVal iReqFlg As Integer) As Integer
Declare Function GetPrivateProfileString Lib "Kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer, ByVal lpFilename As String) As Integer
Declare Function WritePrivateProfileString Lib "Kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As String, ByVal lplFileName As String) As Integer

' GetSystemMetrics
Const SM_CXMin = 28
Const SM_CYMin = 29

Sub cmdLinSta_Click (Index As Integer)
    Dim TIFEVTBLK As TIFEVTBLK
    Dim iCurEvt As Integer
    Dim iEvtDat As Integer
    Dim iLinNum As Integer
    Dim iErrCod As Integer
    Dim Start!
    Dim Msg$

    '
    ' System running, Verify that VFEdit has already requested the line
    '
    iLinNum = Val(edtLinNum)
    If (0 <> TIFLinGet(iLinNum, 0&, 0&)) Then
        Msg$ = "Line " & edtLinNum & " is not currently in use." & CRLF()
        Msg$ = Msg$ & "Please start VFEdit and activate line " & edtLinNum & " by selecting" & CRLF()
        Msg$ = Msg$ & "Options... Device Select... Click Configure, OK and set Line Number."
        MsgBox Msg$
        iLinNum = TifLinRel(iLinNum, 0&, 0&)
        Exit Sub
    End If

    ' Test for request type
    Select Case Index
        Case LINAUDJCK
            cmdLinSta_Click (LINHNG_UP)
            iErrCod = setiparm(iLinNum, CH_AUDIOLINEIN, LINEIN_ENABLE)
            If (0 <> iErrCod) Then
                MsgBox ("Sorry, could not activate audio jack. Error #" & Trim$(Str$(iErrCod)) & CRLF() & "Please check your system configuration.")
                Exit Sub
            End If
        Case LINRJ__11
            iErrCod = setiparm(iLinNum, CH_AUDIOLINEIN, LINEIN_DISABLE)
        Case LINPCK_UP
            cmdLinSta_Click (LINRJ__11)
            iErrCod = sethook(iLinNum, H_OFFH)
        Case LINHNG_UP
            cmdLinSta_Click (LINRJ__11)
            iErrCod = sethook(iLinNum, H_ONH)
    End Select

    '
    ' Wait at least a second for operation to complete
    '
    Start! = Timer
    lblStaLin = "Working..."
    Me.Enabled = False
    screen.MousePointer = HourGlass
    Do While Abs(Timer - Start!) <= LINWAITIM
        iErrCod = GetLinEvt(iLinNum, iEvtDat, TIFEVTBLK)
        iCurEvt = DoEvents()
    Loop
    lblStaLin = ""
    screen.MousePointer = Default
    Me.Enabled = True


End Sub

Function CRLF () As String
    CRLF = Chr$(13) + Chr$(10)
End Function

Sub edtLinNum_Change ()
    edtLinNum = Max(1, Min(Val(edtLinNum), iLinCnt))
End Sub

Sub ErrMsgExi (sErrMsg As String)
    If ("" <> sErrMsg) Then MsgBox sErrMsg, MB_ICONEXCLAMATION + MB_OK, frmProLin.Caption
    Unload frmProLin
End Sub

Sub Form_Load ()
    On Error GoTo Form_LoadErr
    Dim iRetCod As Integer
    Dim Msg$
    
    ' Save application working directory spec (may be different from executable directory)
    sAppWrkDir = CurDir$
    
    ' Set working directory to directory containing the application.
    ' This will insure that DLL's can be found (if not in path)
    ChDrive App.Path
    ChDir App.Path

    ' Initialize name of .INI file
    If ("" = sPrfFilNam) Then sPrfFilNam = PRF_PRFNAMDEF

    ' Initialize DLL support
    iRetCod = TIFSupVer()

    ' Read last screen position
    Left = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRLFTKEY, Str$(Left))
    Top = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRTOPKEY, Str$(Top))
    Height = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRHGTKEY, Str$(Height))
    Width = PrfGetStr(PRF_SCRPOSSEC, PRF_SCRWIDKEY, Str$(Width))
    SafWndSta Me, PrfGetStr(PRF_SCRPOSSEC, PRF_SCRSTAKEY, Str$(WindowState))

    ' Calculate Minimum x / y measurements
    Dim iMinX
    Dim iMinY

    iMinX = screen.TwipsPerPixelX * GetSystemMetrics(SM_CXMin)
    iMinY = screen.TwipsPerPixelY * GetSystemMetrics(SM_CYMin)
    
    ' Check for valid width and Height
    Width = Min(screen.Width, Max(Width, 3 * iMinX))
    Height = Min(screen.Height, Max(Height, 6 * iMinY))
    
    ' Check for valid Left and Top
    If (Left + Width <= iMinX) Or (Left >= screen.Width - iMinX) Then Left = (screen.Width - Width) / 2
    If (Top + Height <= iMinY) Or (Top >= screen.Height - iMinY) Then Top = (screen.Height - Height) / 2
    
    ' Verify that system is active
    If TifSupIni(0, 0&, 0&) Then
        Msg$ = "TSR Not Active!" & CRLF()
        Msg$ = Msg$ & "Verify that your telephony board driver is installed" & CRLF()
        Msg$ = Msg$ & "and run the manufacturer's diagnostic tests."
        ErrMsgExi Msg$
    End If
    If startsys(0, 0, 0, iLinCnt) Then
        If startsys(5, 0, 0, iLinCnt) Then
            Msg$ = "Cannot Start Voice Board System!" & CRLF()
            Msg$ = Msg$ & "Verify that your telephony board driver is installed" & CRLF()
            Msg$ = Msg$ & "and run the manufacturer's diagnostic tests."
            ErrMsgExi Msg$
        End If
    End If

    ' Everything ready to go!
    Exit Sub

Form_LoadErr:
    If (2 = MsgBox(MSG_PROINIERR, MB_RETRYCANCEL, Caption)) Then ErrMsgExi ("")
    Resume Next

End Sub

Sub Form_Unload (Cancel As Integer)
    Dim iErrCod As Integer
    
    ' Save current window state (if not minimized)
    If (MINIMIZED <> WindowState) Then PrfSetStr PRF_SCRPOSSEC, PRF_SCRSTAKEY, WindowState
    ' Save current screen position
    If (NORMAL = WindowState) Then
    PrfSetStr PRF_SCRPOSSEC, PRF_SCRLFTKEY, Left
    PrfSetStr PRF_SCRPOSSEC, PRF_SCRTOPKEY, Top
    PrfSetStr PRF_SCRPOSSEC, PRF_SCRHGTKEY, Height
    PrfSetStr PRF_SCRPOSSEC, PRF_SCRWIDKEY, Width
    End If

    ' Release system resources
    iErrCod = stopsys()
    iErrCod = TifSupTrm()
    End

End Sub

Function Max (ByVal vVal1 As Variant, ByVal vVal2 As Variant) As Variant
    Max = vVal1
    If (Val(vVal2) > Val(vVal1)) Then Max = vVal2
End Function

Function Min (ByVal vVal1 As Variant, ByVal vVal2 As Variant) As Variant
    Min = vVal1
    If (Val(vVal2) < Val(vVal1)) Then Min = vVal2
End Function

Sub MNU_File_Exit_Click ()
    Unload Me
End Sub

Sub MNU_Help_About_Click ()
    ' Display About Box
    frmAbtPro.Show MODAL
End Sub

Sub MNU_Line_Audio_Click ()
    cmdLinSta_Click (LINAUDJCK)
End Sub

Sub MNU_Line_Hangup_Click ()
    cmdLinSta_Click (LINHNG_UP)
End Sub

Sub MNU_Line_Pickup_Click ()
    cmdLinSta_Click (LINPCK_UP)
End Sub

Sub MNU_Line_RJ11_Click ()
    cmdLinSta_Click (LINRJ__11)
End Sub

Function PrfGetStr (ByVal sSecNam As String, ByVal sKeyNam As String, ByVal sDefVal As String)
    Dim sRetStr As String
    sRetStr = String(255, Chr$(STRNULDEL))
    If (0 <> GetPrivateProfileString(sSecNam, sKeyNam, sDefVal, sRetStr, Len(sRetStr), sPrfFilNam)) Then
      PrfGetStr = Trim$(StrTokStr(sRetStr, Chr$(STRNULDEL)))
    Else
      PrfGetStr = Trim$(sDefVal)
    End If
End Function

Sub PrfSetStr (ByVal sSecNam As String, ByVal sKeyNam As String, ByVal sDefVal As String)
    Dim iRetCod As Integer

    iRetCod = WritePrivateProfileString(sSecNam, sKeyNam, sDefVal, sPrfFilNam)
End Sub

Sub SafWndSta (fActFrm As Form, iWndSta)
    ' Set form and control focus
    On Error GoTo SafWndStaErr

    fActFrm.WindowState = iWndSta

    Exit Sub

SafWndStaErr:
    On Error GoTo 0

    Resume Next
End Sub

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

