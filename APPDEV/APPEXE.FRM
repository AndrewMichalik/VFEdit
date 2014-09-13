VERSION 2.00
Begin Form Form1 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Test"
   ClientHeight    =   1224
   ClientLeft      =   1140
   ClientTop       =   1608
   ClientWidth     =   3600
   ControlBox      =   0   'False
   Height          =   1596
   Left            =   1116
   LinkTopic       =   "Form1"
   ScaleHeight     =   1224
   ScaleWidth      =   3600
   Top             =   1260
   Width           =   3648
   Begin CommandButton cmdRunVFE 
      Caption         =   "Run VFEdit"
      Height          =   372
      Left            =   1080
      TabIndex        =   0
      Top             =   720
      Width           =   1452
   End
   Begin Label lblFilNam 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "File: c:\vfedit\sample\hello.wav"
      Height          =   192
      Left            =   120
      TabIndex        =   2
      Top             =   360
      Width           =   2592
   End
   Begin Label lblExe 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Run: c:\vfedit\vfedit"
      Height          =   192
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1608
   End
End
Option Explicit

Declare Function WinExec Lib "Kernel" (ByVal lpCmdLin As String, ByVal nCmdShow As Integer) As Integer
Declare Function GetModuleUsage Lib "Kernel" (ByVal hModule As Integer) As Integer

Const SW_SHOW = 5
Const SI_WININSMEM = 0            ' Insufficient memory
Const SI_WINFILNOF = 2            ' Program not found
Const SI_WINPTHNOF = 3            ' Path not found
Const SI_WINLNKTSK = 5            ' Attempt to link to task
Const SI_WINSEPSEG = 6            ' Library requires sep segs
Const SI_WINUNK008 = 8            ' Insufficient memory to load
Const SI_WINWINVER = 10           ' Incorrect Windows version
Const SI_WINBADEXE = 11           ' Invalid controller EXE file
Const SI_WINOS2APP = 12           ' OS/2 application
Const SI_WINDOSAPP = 13           ' Dos 4.0 Application
Const SI_WINUNKEXE = 14           ' Unknow EXE type
Const SI_WINMODVER = 15           ' Protected mode wrong version
Const SI_WINSECINS = 16           ' Attempt to load second inst
Const SI_WINEMSERR = 17           ' Large frame EMS error
Const SI_WINPROMOD = 18           ' Attempt to load protected mode

Sub cmdRunVFE_Click ()
  Dim hDosIns As Integer
  
  ' Execute command line
  hDosIns = WinExec("c:\vfedit\vfedit c:\vfedit\sample\hello.wav", SW_SHOW)
  
  ' Check for valid return
  If (hDosIns <= 32) Then
    Select Case hDosIns
      Case SI_WININSMEM: MsgBox "Insufficient memory!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINFILNOF: MsgBox "Program not found!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINPTHNOF: MsgBox "Path not found!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINLNKTSK: MsgBox "Attempt to link to task!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINSEPSEG: MsgBox "Library requires separate segments!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINUNK008: MsgBox "Insufficient memory to load!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINWINVER: MsgBox "Incorrect Windows version!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINBADEXE: MsgBox "Invalid EXE file!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINOS2APP: MsgBox "OS/2 application!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINDOSAPP: MsgBox "Dos 4.0 Application!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINUNKEXE: MsgBox "Unknown EXE type!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINMODVER: MsgBox "Protected mode wrong version!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINSECINS: MsgBox "Attempt to load second instance!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINEMSERR: MsgBox "Large frame EMS error!", MB_ICONEXCLAMATION, "Execute Error"
      Case SI_WINPROMOD: MsgBox "Attempt to load protected mode!", MB_ICONEXCLAMATION, "Execute Error"
    Case Else
      MsgBox "Unknown Error", MB_ICONEXCLAMATION, "Execute Error"
    End Select
    ' Exit error
    Exit Sub
  End If

  ' Show Hourglass & wait for process to complete
  screen.MousePointer = 11
  Do While GetModuleUsage(hDosIns) > 0
    DoEvents
  Loop
  screen.MousePointer = 0

End Sub

