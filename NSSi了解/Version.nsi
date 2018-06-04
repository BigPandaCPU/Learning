!IfNDef INSTALLER_VERSION_INCLUDE
!define INSTALLER_VERSION_INCLUDE

!Macro SET_INSTALLER_VESION
;  LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
  ;--------------------------------
  ;Version Information

    VIProductVersion "3.1.112.61293"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" ""
    VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "m1Platform Inc."
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "7Medical"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Copyright ? 7Medical 2015"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "${PRODUCT_NAME} Installer"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "3.1.112.61293"
!MacroEnd  SET_INSTALLER_VESION

!endif ; INSTALLER_VERSION_INCLUDE
