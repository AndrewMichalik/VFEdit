/////////////////////////////////////////////////////////////////////////////
// VFECIF.h : VFEDIT CI/F Support header
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Forward references
/////////////////////////////////////////////////////////////////////////////
class	CTmpFil;
class	CAudFil;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#define ERR___DEB       0x0002          // Debug error messages flag 
#define KEY___DEB       0x0008          // Debug key flag            
#define MEM___DEB       0x0020          // Debug memory messages flag
#define CFG___DEB       0x0080          // Debug config settings flag
#define INI___DEB       0x0200          // Debug init   settings flag

/////////////////////////////////////////////////////////////////////////////
// 						Initialization request codes
/////////////////////////////////////////////////////////////////////////////
typedef enum _CIFINIREQ {
    CIFSYSINI =   0,                    // Initialize CIF DLL          
    CIFSUBINI =   4,                    // Initialize CIF subsystems   
    CIFPRFINI =   8,                    // Initialize profile settings 
} CIFINIREQ;                  

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class 	CVFECIF : public CWinApp
{
public:
	CVFECIF	(const char* pszAppName) : CWinApp (pszAppName) {}
	virtual	BOOL		InitInstance();		
	virtual	int			ExitInstance();		

	/////////////////////////////////////////////////////////////////////////
	typedef enum _INIREQ {
		INIREQBEG = 0,					// Begin init operation
	} INIREQ;

private: 	

};

/////////////////////////////////////////////////////////////////////////////
extern	CVFECIF	vfecif;




