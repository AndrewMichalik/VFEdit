bfr   CIFDEV\5cREGDEV\5cACCKEY.TXT ACCKEY.TXT vfedit.mak vfesdk.mak -d
del   sdkdev\*.zip
pkzip sdkdev\sdk30a.zip vfesdk.mak *.bas *.frm *.frx acckey.txt constant.txt -ssoftparade
fd    sdkdev\*.zip/t12:00/d11-01-97
pkzip sdkdev\vfesdk.zip sdkdev\*.*
del   sdkdev\sdk30a.zip
fd    sdkdev\*.zip/t12:00/d11-01-97

