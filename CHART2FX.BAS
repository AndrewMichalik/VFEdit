' Function Prototypes
Declare Function chart_Send Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal wMsg As Integer, ByVal wParam As Integer, ByVal lParam As Any) As Long
Declare Function chart_OpenData Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal wCode As Integer, dwSize As Long) As Long
Declare Function chart_CloseData Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal wCode As Integer) As Integer
Declare Function chart_SetValue Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal nSerie As Integer, ByVal nPoint As Integer, ByVal dValue As Double) As Long
Declare Function chart_SetIniValue Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal nSerie As Integer, ByVal nPoint As Integer, ByVal dValue As Double) As Long
Declare Function chart_SetXvalue Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal nSerie As Integer, ByVal nPoint As Integer, ByVal dValue As Double) As Long
Declare Function chart_SetConst Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal nIndex As Integer, ByVal dValue As Double) As Long
Declare Function chart_SetColor Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal nIndex As Integer, ByVal lColor As Long, ByVal bBack As Integer) As Long
Declare Sub chart_SetAdm Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal nIndex As Integer, ByVal dValue As Double)
Declare Function chart_Get Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal lType As Long, ByVal wCode As Integer) As Double
Declare Function chart_SetStripe Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal nIndex As Integer, ByVal dIni As Double, ByVal dEnd As Double, ByVal lColor As Long) As Long
Declare Function chart_SetStatusItem Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal n As Integer, ByVal Text As Integer, ByVal idm As Integer, ByVal Frame As Integer, ByVal w As Integer, ByVal min As Integer, ByVal desp As Integer, ByVal s As Long)
Declare Sub chart_Paint Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal hDC As Integer, ByVal xLeft As Integer, ByVal yTop As Integer, ByVal xRight As Integer, ByVal yBottom As Integer, ByVal bPrintMode As Integer, ByVal l As Long)
Declare Function chart_OpenDataEx Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal wCode As Integer, ByVal n1 As Integer, ByVal n2 As Integer) As Long
Declare Function chart_GetAdm Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal wType As Integer) As Double
Declare Function chart_GetPaintInfo Lib "CHART2FX.VBX" (ByVal hWnd As Integer, ByVal wParam As Integer, pValue As Any) As Long

' Notification Codes for ChangeColor Event
Global Const CCC_SERIE = 0
Global Const CCC_SERIEBK = 1
Global Const CCC_ONE = 2
Global Const CCC_ONEBK = 3
Global Const CCC_BARHORZ = 4
Global Const CCC_BKGND = 5
Global Const CCC_2DBK = 6
Global Const CCC_3DBK = 7

' Notification Codes for ChangeString Event
Global Const CCS_LEGEND = 0
Global Const CCS_SERLEGEND = 1

' Notification Codes for ChangeString Event
Global Const CCP_SERIE = 0
Global Const CCP_ONE = 1

' Gallery Types
Global Const LINES = 1                                                        ' LINE is already defined in VB
Global Const BAR = 2
Global Const SPLINE = 3
Global Const MARK = 4
Global Const PIE = 5
Global Const AREA = 6
Global Const PARETO = 7
Global Const SCATTER = 8
Global Const HILOW = 9
Global Const SURFACE = 10
Global Const POLAR = 11
Global Const CUBE = 12
Global Const DOUGHNUT = 13
 
' Chart Types
Global Const CT_3D = &H100&
Global Const CT_HORZ = &H200&
Global Const CT_TOOL = &H400&
Global Const CT_PALETTE = &H800&
Global Const CT_LEGEND = &H1000&
Global Const CT_TOGETHER = &H2000&
Global Const CT_POINTS = &H4000&
Global Const CT_SHOWZERO = &H8000&
Global Const CT_EACHBAR = &H10000
Global Const CT_CLUSTER = &H20000
Global Const CT_SHOWDATA = &H40000
Global Const CT_DLGGRAY = &H80000
Global Const CT_PATTERN = &H100000
Global Const CT_SHOWVALUES = &H200000
Global Const CT_MENU = &H400000
Global Const CT_SHOWLINES = &H800000
Global Const CT_SCATTERLINE = &H800000
Global Const CT_COLORLINE = &H1000000
Global Const CT_NOAREALINE = &H2000000
Global Const CT_HILOWSTD = &H2000000
Global Const CT_NOBORDERS = &H4000000
Global Const CT_PIEVALUES = &H8000000
Global Const CT_TRACKMOUSE = &H10000000
Global Const CT_EVENSPACING = &H20000000
Global Const CT_SERLEGEND = &H40000000
Global Const CT_PAINTMARKER = &H80000000
			      
'Extended types
Global Const CTE_STEPLINES = &H1
Global Const CTE_SMOOTH = &H2
Global Const CTE_SQUAREPIE = &H4
Global Const CTE_NOLEGINVALIDATE = &H8
Global Const CTE_ACTMINMAX=&H10
Global Const CTE_NOTITLESHADOW=&H20
Global Const CTE_CREATELEGENDS=&H40
Global Const CTE_NOCROSS=&H80
Global Const CTE_LOGBREAK=&H100

'Extended types
Global Const CS_CHLINE = &H1&
Global Const CS_CHBAR = &H2&
Global Const CS_CHSPLINE = &H4&
Global Const CS_CHMARK = &H8&
Global Const CS_CHPIE = &H10&
Global Const CS_CHAREA = &H20&
Global Const CS_CHPARETO = &H40&
Global Const CS_CHSCATTER = &H80&
Global Const CS_CHHILOW = &H100&
Global Const CS_MULTITYPE = &H800&
Global Const CS_CHDEFAULT = &HFFF&
Global Const CS_MINMAX = &H1000&
Global Const CS_3D = &H2000&
Global Const CS_HORZ = &H4000&
Global Const CS_TOGETHER = &H8000&
Global Const CS_SHOWPOINT = &H10000
Global Const CS_SCALE = &H20000
Global Const CS_TITLES = &H40000
Global Const CS_FONTS = &H80000
Global Const CS_EDITABLE = &H100000
Global Const CS_FILEEXPORT = &H200000
Global Const CS_FILEIMPORT = &H400000
Global Const CS_SCROLLABLE = &H800000
Global Const CS_PRINTABLE = &H1000000
Global Const CS_3DVIEW = &H2000000
Global Const CS_GRID = &H4000000
Global Const CS_RESIZEABLE = &H8000000
Global Const CS_TEMPLATE = &H10000000
Global Const CS_COPY = &H20000000
Global Const CS_CLOSEABLE = &H40000000
Global Const CS_LOGSCALE = &H80000000
Global Const CS_ALL = &HFFFFFFFF

' Extended styles
Global Const CSE_NOSEPARATE=&H1
Global Const CSE_NOLASTPAGE=&H2
Global Const CSE_WIN95TOP=&H4

' Constants

' STYLE, TYPE
Global Const CHART_ADD = 0
Global Const CHART_SET = 1
Global Const CHART_REMOVE = 2

' STACKED
Global Const CHART_NOSTACKED = 0
Global Const CHART_STACKED = 1
Global Const CHART_STACKED100 = 2

' GRID
Global Const CHART_NOGRID = 0
Global Const CHART_HORZGRID = 1
Global Const CHART_VERTGRID = 2
Global Const CHART_BOTHGRID = 3
Global Const CHART_GRIDY2 = 4

' POINTTYPE
Global Const CHART_NONEMK = 0
Global Const CHART_RECTMK = 1
Global Const CHART_CIRCLEMK = 2
Global Const CHART_TRIANGLEMK = 3
Global Const CHART_MARBLEMK = 4
Global Const CHART_CUBEMK = 5
Global Const CHART_MANYMK = 6

' TITLES
Global Const CHART_LEFTTIT = 0
Global Const CHART_RIGHTTIT = 1
Global Const CHART_TOPTIT = 2
Global Const CHART_BOTTOMTIT = 3

' FONTS
Global Const CHART_LEFTFT = 0
Global Const CHART_RIGHTFT = 1
Global Const CHART_TOPFT = 2
Global Const CHART_BOTTOMFT = 3
Global Const CHART_XLEGFT = 4
Global Const CHART_YLEGFT = 5
Global Const CHART_FIXEDFT = 6
Global Const CHART_LEGENDFT = 7
Global Const CHART_VALUESFT = 8
Global Const CHART_POINTFT = 9

' DBLCLK and RIGHTCLK
Global Const CHART_BALOONCLK = 0
Global Const CHART_DIALOGCLK = 1
Global Const CHART_NONECLK = 2
Global Const CHART_MENUCLK = 3

' GAP
Global Const CHART_LEFTGAP = 0
Global Const CHART_RIGHGAP = 1
Global Const CHART_TOPGAP = 2
Global Const CHART_BOTTOMGAP = 3
Global Const CHART_ALLGAP = 4

' Colors
Global Const CHART_TRANSPARENT = &H80000000

Global Const CHART_WHITE = 1
Global Const CHART_BLACK = 2
Global Const CHART_LTGRAY = 3
Global Const CHART_DKGRAY = 4
Global Const CHART_RED = 5
Global Const CHART_DKRED = 6
Global Const CHART_BLUE = 7
Global Const CHART_DKBLUE = 8
Global Const CHART_GREEN = 9
Global Const CHART_DKGREEN = 10
Global Const CHART_CYAN = 11
Global Const CHART_DKCYAN = 12
Global Const CHART_YELLOW = 13
Global Const CHART_DKYELLOW = 14
Global Const CHART_VIOLET = 15
Global Const CHART_DKVIOLET = 16

' Line Styles
Global Const CHART_SOLID = 0
Global Const CHART_DASH = 1
Global Const CHART_DOT = 2
Global Const CHART_DASHDOT = 3
Global Const CHART_DASHDOTDOT = 4
Global Const CHART_PS_TRANSPARENT = &H4000&

' Color Schemes
Global Const CHART_CSSOLID = 0
Global Const CHART_CSBWPATTERN = 1
Global Const CHART_CSPATTERN = 2

' Color Types
Global Const CHART_FGROUND = 0
Global Const CHART_BGROUND = 1

' chart_Get Constants
Global Const CHART_GVALUES = 0
Global Const CHART_GINIVALUES = 1
Global Const CHART_GXVALUES = 2

' XLegType Constants
Global Const CL_NOTCLIPPED = &H1&
Global Const CL_NOTCHANGECOLOR = &H2&
Global Const CL_HIDE = &H4&                                                                ' Obsolete (use CL_HIDEXLEG)
Global Const CL_HIDEXLEG = &H4&
Global Const CL_FORCESERLEG = &H8&
Global Const CL_GETLEGEND = &H10&
Global Const CL_HIDEYLEG = &H20&
Global Const CL_2LEVELS = &H40&
Global Const CL_VERTXLEG = &H80&
Global Const CL_SHOWZLEG = &H100&
Global Const CL_PIELEGEND =	&H0200
Global Const CL_SINGLELINE = &H0400


' ConstType Constants
Global Const CC_HIDETEXT = &H1&
Global Const CC_HIDE = &H2&

' Item Indexes (ItemColor, ItemBkColor, ItemWidth, ItemStyle)
Global Const CI_HORZGRID = 0
Global Const CI_VERTGRID = 1
Global Const CI_2DLINE = 2
Global Const CI_FIXED = 3
Global Const CI_LOOPPOS = 4
Global Const CI_HORZGRID2 = 5

' DecimalsNum Indexes
Global Const CD_ALL = 0
Global Const CD_VALUES = 1
Global Const CD_YLEG = 2
Global Const CD_XLEG = 3
Global Const CD_YLEG2 = 4

' ChartStatus Constants
Global Const CHART_GSVALUES = &H1&
Global Const CHART_GSLEGENDS = &H2&
Global Const CHART_GSCOLORS = &H4&
Global Const CHART_GSPATTERNS = &H8&
Global Const CHART_GSPALETTE = &H10&
Global Const CHART_GSPATTPAL = &H20&
Global Const CHART_GSREADTEMP = &H40&
Global Const CHART_GSREADFILE = &H80&
Global Const CHART_GSGALLERY = &H100&
Global Const CHART_GSOPTIONS = &H200&

' SetTool Constants
Global Const CST_IMPORT = &H1&
Global Const CST_EXPORT = &H2&
Global Const CST_FILE = (CST_IMPORT Or CST_EXPORT)
Global Const CST_COPYBITMAP = &H4&
Global Const CST_COPYDATA = &H8&
Global Const CST_COPY = (CST_COPYBITMAP Or CST_COPYDATA)
Global Const CST_PRINT = &H10&
Global Const CST_FILEEDIT = (CST_FILE Or CST_COPY Or CST_PRINT)
Global Const CST_SPACE1 = &H20&
Global Const CST_GALLERY = &H40&
Global Const CST_SPACECOMBO = &H80&
Global Const CST_COLOR = &H100&
Global Const CST_SPACE2 = &H200&
Global Const CST_3D = &H400&
Global Const CST_ROTATE = &H800&
Global Const CST_CLUSTER = &H1000&
Global Const CST_ZOOM = &H2000&
Global Const CST_VIEW = (CST_3D Or CST_ROTATE Or CST_CLUSTER Or CST_ZOOM)
Global Const CST_SPACE3 = &H4000&
Global Const CST_LEGEND = &H8000&
Global Const CST_SERLEGEND = &H10000
Global Const CST_VGRID = &H20000
Global Const CST_HGRID = &H400007
Global Const CST_LEGGRID = (CST_LEGEND Or CST_SERLEGEND Or CST_VGRID Or CST_HGRID)
Global Const CST_SPACE4 = &H80000
Global Const CST_TITLES = &H100000
Global Const CST_FONTS = &H200000
Global Const CST_TOOLS = &H400000
Global Const CST_OPTIONS = &H800000
Global Const CST_OTHER = (CST_TITLES Or CST_FONTS Or CST_TOOLS Or CST_OPTIONS)

' GalleryTool Constants
Global Const CSG_LINE = &H1&
Global Const CSG_BAR = &H2&
Global Const CSG_SPLINE = &H4&
Global Const CSG_MARK = &H8&
Global Const CSG_PIE = &H10&
Global Const CSG_AREA = &H20&
Global Const CSG_PARETO = &H40&
Global Const CSG_SCATTER = &H80&
Global Const CSG_HILOW = &H100&
Global Const CSG_SURFACE = &H200&
Global Const CSG_POLAR = &H400&
Global Const CSG_CUBE = &H800&
Global Const CSG_DOUGHNUT = &H1000&
Global Const CSG_BARHORZ = &H2000&
Global Const CSG_ALL = &HFFFFFFFF

' Fonts
Global Const CF_BOLD = &H100&
Global Const CF_ITALIC = &H200&
Global Const CF_UNDERLINE = &H400&
Global Const CF_STRIKEOUT = &H800&
Global Const CF_FDONTCARE = &H0&
Global Const CF_FROMAN = &H1000&
Global Const CF_FSWISS = &H2000&
Global Const CF_FMODERN = &H3000&
Global Const CF_FSCRIPT = &H4000&
Global Const CF_FDECORATIVE = &H5000&
Global Const CF_ARIAL = &H0&
Global Const CF_COURIER = &H10000
Global Const CF_COURIERNEW = &H20000
Global Const CF_HELVETICA = &H30000
Global Const CF_MODERN = &H40000
Global Const CF_ROMAN = &H50000
Global Const CF_SCRIPT = &H60000
Global Const CF_SYMBOL = &H70000
Global Const CF_TIMES = &H80000
Global Const CF_TIMESNEWR = &H90000
Global Const CF_WINGDINGS = &HA0000

' chart_OpenData Constants
Global Const COD_VALUES = 1
Global Const COD_CONSTANTS = 2
Global Const COD_COLORS = 3
Global Const COD_STRIPES = 4
Global Const COD_INIVALUES = 5
Global Const COD_XVALUES = 6
Global Const COD_STATUSITEMS = 7

' chart_OpenData Actions
Global Const COD_SMOOTH = &H1000&
Global Const COD_NOINVALIDATE = &H2000&
Global Const COD_SCROLLLEGEND = &H4000&
Global Const COD_REALTIME = &H100&
Global Const COD_REALTIMESCROLL = &H300&
Global Const COD_ADDPOINTS = &H400&
Global Const COD_REMOVE = &H800&
Global Const COD_UNKNOWN = &HFFFF
Global Const COD_UNCHANGE = 0

'Same as FLT_MAX
Global Const CHART_HIDDEN = 3.402823466E+38

' chart_SetAdm,chart_GetAdm Constants
Global Const CSA_MIN = 0
Global Const CSA_MAX = 1
Global Const CSA_GAP = 2
Global Const CSA_SCALE = 3
Global Const CSA_YLEGGAP = 4
Global Const CSA_PIXXVALUE = 5
Global Const CSA_XMIN = 6
Global Const CSA_XMAX = 7
Global Const CSA_XGAP = 8
Global Const CSA_LOGBASE = 9
Global Const CSA_MIN2 = 10
Global Const CSA_MAX2 = 11
Global Const CSA_GAP2 = 12
Global Const CSA_SCALE2 = 13
Global Const CSA_XSCALE = 14
Global Const CSA_LOGBASE2 = 15
Global Const CSA_LOGBASEX = 16

Global Const CHART_LOGN = 0

' chart_OpenData - chart_SetValue, ... return values
Global Const CR_OUTRANGE = -1
Global Const CR_NOOPEN = -2
Global Const CR_FAIL = -3
Global Const CR_INVALID = -4
Global Const CR_BADCODE = -5
Global Const CR_SUCCESS = 0
Global Const CR_NEW = 1
Global Const CR_KEEPALL = 2
Global Const CR_LOSTLAST = 3

' StatusBar Item Structure
Type CHART_STITEM
	sText   As String
	wIdm    As Integer
	bFrame  As Integer
	nWidth  As Integer
	nMin    As Integer
	nDesp   As Integer
	dwStyle As Long
End Type

Type CHART_P3D
	x   As Integer
	y   As Integer
	z   As Integer
End Type

' HILOW Constants

' Hi-Low-Close
Global Const HLC_LOW = 0
Global Const HLC_CLOSE = 1
Global Const HLC_HIGH = 2

' Open-Hi-Low-Close
Global Const OHLC_LOW = 0
Global Const OHLC_OPEN = 1
Global Const OHLC_CLOSE = 2
Global Const OHLC_HIGH = 3

' ClearLegend Constants
Global Const CHART_LEGEND = 0
Global Const CHART_SERLEG = 1
Global Const CHART_KEYLEG = 2
Global Const CHART_KEYSER = 3
Global Const CHART_FIXLEG = 4
Global Const CHART_YLEG = 5

' RealTimeStyle
Global Const CRT_LOOPPOS = &H1&
Global Const CRT_NOWAITARROW = &H2&

' Export,Import,ExportStr,ImportStr Constants
Global Const CHART_DATA = 0
Global Const CHART_BITMAP = 1
Global Const CHART_METAFILE = 2
Global Const CHART_CFXFILE = 3
Global Const CHART_CFXTEMPLATE = 4
Global Const CHART_INTERNALFILE = 5
Global Const CHART_INTERNALTEMPLATE = 6

' ToolStyle,ToolSize Constants
Global Const CTOOL_LEGEND = 0
Global Const CTOOL_SERLEGEND = 1
Global Const CTOOL_TB = 2

Global Const CTOOL_OPTIONS = &H2000
Global Const CTOOL_MOVE = &H4000

' chart_Paint Modes
Global Const CPAINT_BKGND = &H1&
Global Const CPAINT_PRINT = &H4&

' TBButtonStyle
Global Const CTBS_BUTTON = &H1&
Global Const CTBS_SEPARATOR = &H2&
Global Const CTBS_MENU = &H4&
Global Const CTBS_ICONCOMBO = &H8&
Global Const CTBS_HWND = &H88&
Global Const CTBS_DESTROY = &H10&
Global Const CTBS_REPEAT = &H800&
Global Const CTBS_GROUP = &H1000&
Global Const CTBS_2STATE = &H2000&
Global Const CTBS_GROUP2STATE = &H3000&
Global Const CTBS_HEAD = &H4000&

' ToolStyle Constants
Global Const CTS_FLOATING = &H4000&
Global Const CTS_HIDEFOCUS = &H8000&
Global Const CTS_WHITELINE = &H10000
Global Const CTS_DELIMITER = &H20000
Global Const CTS_SIZEABLE = &H40000
Global Const CTS_HORZLAYER = &H80000
Global Const CTS_VERTLAYER = &H100000
Global Const CTS_SIZELAYER = &H200000
Global Const CTS_DBLCLKS = &H400000
Global Const CTS_DOCKABLE = &H800000
Global Const CTS_SPLITTER = &H1000000
Global Const CTS_3DFRAME = &H2000000
Global Const CTS_BORDERLAYER = &H4000000
Global Const CTS_BORDERIFLAYER = &H8000000

'Positions for tools (CM_TOOLPOS)
Global Const CTP_TOP = &H0&
Global Const CTP_LEFT = &H1&
Global Const CTP_BOTTOM = &H2&
Global Const CTP_RIGHT = &H3&
Global Const CTP_FIXED = &H4&
Global Const CTP_FLOAT = &H7FFF&
Global Const CTP_SWITCH = &H7FFE&

'Tools Options
'Legend Options
Global Const CHART_LWORDBREAK = &H1&
Global Const CHART_LSKIPEMPTY = &H2&
Global Const CHART_LSHOWMENU = &H4&
Global Const CHART_LOPTIONSDLG = &H8&
Global Const CHART_LRIGHTALIGN = &H10
Global Const CHART_LNOCOLOR = &H20

' Toolbar options
Global Const CHART_TBBALLOON = &H1
Global Const CHART_TBSTANDARD =	&H2
Global Const CHART_TBNOTOOLTIPS = &H4

' Menu and Toolbar IDS
Global Const CFX_ID_FIRST = &H7300&
Global Const CFX_ID_CLOSE = &H7301&
Global Const CFX_ID_EXPORTDATA = &H7302&
Global Const CFX_ID_EXPORTBITMAP = &H7303&
Global Const CFX_ID_LEGEND = &H7304&
Global Const CFX_ID_SERIESLEGEND = &H7305&
Global Const CFX_ID_TOOLBAR = &H7306&
Global Const CFX_ID_PALETTE = &H7307&
Global Const CFX_ID_PATTERN = &H7308&
Global Const CFX_ID_STATUS = &H7309&
Global Const CFX_ID_DATAEDITOR = &H730A&
Global Const CFX_ID_3D = &H730B&
Global Const CFX_ID_CLUSTER = &H730C&
Global Const CFX_ID_HORZGRID = &H730D&
Global Const CFX_ID_VERTGRID = &H730E&
Global Const CFX_ID_ZOOM = &H730F&
Global Const CFX_ID_GALLERY = &H7310&
Global Const CFX_ID_COLOR = &H7311&
Global Const CFX_ID_TOOLS = &H7312&
Global Const CFX_ID_PRINT = &H7313&
Global Const CFX_ID_HELPCONTENTS = &H7314&
Global Const CFX_ID_HELPHOWTOUSE = &H7315&
Global Const CFX_ID_EXPORTMETAFILE = &H7316&
Global Const CFX_ID_APPLY = &H7317&

' Gallery types
Global Const CFX_ID_LINE = &H7350&
Global Const CFX_ID_BAR = &H7351&
Global Const CFX_ID_SPLINE = &H7352&
Global Const CFX_ID_MARK = &H7353&
Global Const CFX_ID_PIE = &H7354&
Global Const CFX_ID_AREA = &H7355&
Global Const CFX_ID_PARETO = &H7356&
Global Const CFX_ID_SCATTER = &H7357&
Global Const CFX_ID_HILOW = &H7358&
Global Const CFX_ID_SURFACE = &H7359&
Global Const CFX_ID_POLAR = &H735A&
Global Const CFX_ID_CUBE = &H735B&
Global Const CFX_ID_DOUGHNUT = &H735C&
Global Const CFX_ID_HORZBAR = &H735D&
	
Global Const CFX_ID_DLGFIRST = &H7400&
Global Const CFX_ID_DLGLAST = &H74FF&
	
Global Const CFX_ID_ROTATE = &H7400&
Global Const CFX_ID_OPTIONS = &H7401&
Global Const CFX_ID_EDITTITLES = &H7402&
Global Const CFX_ID_PAGESETUP = &H7403&
Global Const CFX_ID_DLGPRINT = &H7404&
Global Const CFX_ID_EXPORTFILE = &H7405&
Global Const CFX_ID_IMPORTFILE = &H7406&
Global Const CFX_ID_EXPORTTEMPLATE = &H7407&
Global Const CFX_ID_IMPORTTEMPLATE = &H7408&
Global Const CFX_ID_ABOUT = &H7409&
Global Const CFX_ID_GENERAL = &H740A&
Global Const CFX_ID_SERIES = &H740B&
Global Const CFX_ID_SCALE = &H740C&
Global Const CFX_ID_FONTS = &H740D&
Global Const CFX_ID_FONTLT = &H740E&
Global Const CFX_ID_FONTRT = &H740F&
Global Const CFX_ID_FONTTT = &H7410&
Global Const CFX_ID_FONTBT = &H7411&
Global Const CFX_ID_FONTXL = &H7412&
Global Const CFX_ID_FONTYL = &H7413&
Global Const CFX_ID_FONTFX = &H7414&
Global Const CFX_ID_FONTLY = &H7415&
Global Const CFX_ID_FONTVAL = &H7416&

Global Const CFX_ID_LAST = &H74FF&

' Reserved IDS
Global Const CFX_ID_RESERVEDFIRST = &H7500&
Global Const CFX_ID_RESERVEDLAST = &H76FF&
 
' ShowDialog Constants
Global Const CDIALOG_EXPORTFILE = CFX_ID_EXPORTFILE
Global Const CDIALOG_IMPORTFILE = CFX_ID_IMPORTFILE
Global Const CDIALOG_WRITETEMPLATE = CFX_ID_EXPORTTEMPLATE
Global Const CDIALOG_READTEMPLATE = CFX_ID_IMPORTTEMPLATE
Global Const CDIALOG_PAGESETUP = CFX_ID_PAGESETUP
Global Const CDIALOG_ABOUT = CFX_ID_ABOUT
Global Const CDIALOG_OPTIONS = CFX_ID_OPTIONS
Global Const CDIALOG_EDITTITLES = CFX_ID_EDITTITLES
Global Const CDIALOG_FONTS = CFX_ID_FONTS
Global Const CDIALOG_ROTATE = CFX_ID_ROTATE
Global Const CDIALOG_GENERAL = CFX_ID_GENERAL
Global Const CDIALOG_SERIES = CFX_ID_SERIES
Global Const CDIALOG_SCALE = CFX_ID_SCALE

' PaintInfo Constants
Global Const CPI_GETDC = 0
Global Const CPI_RELEASEDC = 1
Global Const CPI_PIXELTOMARKER = 2
Global Const CPI_MARKERTOPIXEL = 3
Global Const CPI_VALUETOPIXEL = 4
Global Const CPI_PIXELTOVALUE = 5
Global Const CPI_POSITION = 6
Global Const CPI_DIMENSION = 7
Global Const CPI_PRINTINFO = 8
Global Const CPI_SCROLLINFO = 9
Global Const CPI_3DINFO = 10
Global Const CPI_3DTO2D = 11

Global Const CM_GETPAINTINFO = &H66&

' StatusBar Item Styles
Global Const CHART_STLEFT = &H0&
Global Const CHART_STCENTER = &H1&
Global Const CHART_STRIGHT = &H2&

Global Const CHART_STITEM_BYPOS = &H4000&

' Styles for DataStyle
Global Const CHART_DS_SERLEGEND = &H1&
Global Const CHART_DS_USETEXTASLEG = &H2&
Global Const CHART_DS_USEDATEASLEG = &H4&

' DataType Constants
Global Const CDT_STRING = 1
Global Const CDT_NUMBER = 7
Global Const CDT_NOTUSED = -1

Global Const CHART_MAXBOUNDFIELDS = 16
Global Const CHART_E = 2.71828182846

Function CHART_HIWORD (l As Long)
    CHART_HIWORD = CInt((l And &HFFFF0000) / &H10000)
End Function

Function CHART_LOWORD (ByVal l As Long)
    l2& = l And &HFFFF&
    If (l2& > 32767) Then
	l2& = l2& - 65536
    End If
    CHART_LOWORD = CInt(l2&)
End Function

Function CHART_ML (wLow As Integer, wHi As Integer)
    CHART_ML = CLng(&H10000 * wHi) + wLow
End Function

