# Define all things which is used by many pages or parts

!IfNDef MIIS_COMMON_INCLUDE
!Define MIIS_COMMON_INCLUDE

!Include "CommonNSI_ENG\Version.nsi"

!Macro COMMON_DEFINE
  !Define PRODUCT_VERSION         "2.0"
  !Define PRODUCT_PUBLISHER       "7 Medical Systems, LLC."
  !Define PRODUCT_UNINST_KEY      "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
  !Define PRODUCT_UNINST_ROOT_KEY "HKLM"
  !Define COMPANY_KEY             "Software\Hinacom"
  !Define PRODUCT_KEY             "Software\Hinacom\Hinacom MIIS"
!MacroEnd ;COMMON_DEFINE

!Macro COMMON_VARIABLE
  !IfNDef COMMON_VARIABLE_DEFINE
  !Define COMMON_VARIABLE_DEFINE
    ; Variables used between multipage
    Var SQLInstance
    Var SQLUserName
    Var SQLDatabaseName
    Var SQLUserpass
    Var SQLWinAuth
    Var SQLDBFilePath
    Var SQLClearDBBeforeInstall
    Var LicKey
    Var dotNet20Root
    Var ProductWebSite
    Var ProductMIISSite
  !EndIf  ;COMMON_VARIABLE_DEFINE
!MacroEnd ;COMMON_VARIABLE

!Macro COMMON_UI_PRE_SETTING
  ;---------------------------------
  ; nsdialog related
  XPStyle On

  ; MUI Settings
  !Define MUI_ABORTWARNING
  !Define MUI_ICON   "Docs\miPlatform.ico"
;  !define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
  !Define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

  ; Language Selection Dialog Settings
  !Define MUI_LANGDLL_REGISTRY_ROOT      "${PRODUCT_UNINST_ROOT_KEY}"
  !Define MUI_LANGDLL_REGISTRY_KEY       "${PRODUCT_UNINST_KEY}"
  !Define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"
!MacroEnd ;COMMON_UI_PRE_SETTING

!Macro COMMON_UI_POST_SETTING
  ; Language files
  !InsertMacro MUI_LANGUAGE "English"
;  !InsertMacro MUI_LANGUAGE "SimpChinese"

  BrandingText "${PRODUCT_PUBLISHER}"
!MacroEnd ;COMMON_UI_POST_SETTING

!Macro COMMON_NSIS_SETTING

  Name "${PRODUCT_NAME}"
  InstallDir "C:\miPlatform"
  ;Name "${PRODUCT_NAME}"
  ;InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"

  ;InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
  ShowInstDetails show
  ShowUnInstDetails Show

  !InsertMacro SET_INSTALLER_VESION
!MacroEnd ;COMMON_NSIS_SETTING

;!Macro INSTALL_MIIS_SERVICE
;  ExecWait '"$INSTDIR\DicomServiceWrapper.exe" -i'
;  ExecWait '"$INSTDIR\ImageServiceWrapper.exe" -i'
;  ExecWait '"$INSTDIR\DicomPrintServiceWrapper.exe" -i'
;  ExecWait '"$INSTDIR\DicomBuilderServiceWrapper.exe" -i'
;  ExecWait '"$INSTDIR\ResumeTransferServiceWrapper.exe" -i'
;  ExecWait '"$INSTDIR\VideoTalkServiceWrapper.exe" -i'
  ;ExecWait '"$INSTDIR\InstallUtil.exe" -i "$INSTDIR\MIISMonitorService.exe"'
;!MacroEnd ;INSTALL_MIIS_SERVICE

;!Macro START_MIIS_SERVICE
;  ExecWait '"$INSTDIR\DicomServiceWrapper.exe" -s'
;  ExecWait '"$INSTDIR\ImageServiceWrapper.exe" -s'
;  ExecWait '"$SYSDIR\net" start MIIS_Image_Service'
;  ExecWait '"$INSTDIR\DicomPrintServiceWrapper.exe" -s'
;  ExecWait '"$INSTDIR\DicomBuilderServiceWrapper.exe" -s'
;  ExecWait '"$INSTDIR\ResumeTransferServiceWrapper.exe" -s'
;  ExecWait '"$INSTDIR\VideoTalkServiceWrapper.exe" -s'
;  ExecWait '"$SYSDIR\net" start MIIS_Monitor_Service'
;!MacroEnd ;START_MIIS_SERVICE

!Macro STOP_MIIS_SERVICE
  ExecWait '"$SYSDIR\net" stop MIIS_Monitor_Service'
  ExecWait '"$INSTDIR\DicomServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\ImageServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\Hina3DLauncherServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\DicomBuilderServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\DicomPrintServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\ResumeTransferServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\VideoTalkServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\SessionServiceWrapper.exe" -k'
  ExecWait '"$INSTDIR\DicomModifierServerServiceWrapper.exe" -k'
  
;  ExecWait '"$SYSDIR\net" stop "miPlatform Session Service"'
!MacroEnd ;STOP_MIIS_SERVICE

!Macro STOP_MIIS_MONITOR_SERVICE
  ExecWait '"$SYSDIR\net" stop MIIS_Monitor_Service'
!MacroEnd ;STOP_MIIS_SERVICE

!Macro UNINSTALL_MIIS_SERVICE
  ;ExecWait '"$INSTDIR\InstallUtil.exe" -u "$INSTDIR\MIISMonitorService.exe"'
  ExecWait '"$INSTDIR\DicomServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\ImageServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\Hina3DLauncherServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\DicomBuilderServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\DicomPrintServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\ResumeTransferServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\VideoTalkServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\SessionServiceWrapper.exe" -r'
  ExecWait '"$INSTDIR\DicomModifierServerServiceWrapper.exe" -r'
;  KillProcDLL::KillProc "miPlatform Session Service"
;  ExecWait 'net stop "miPlatform Session Service"'
;  ExecWait '"$INSTDIR\SessionService.exe" /uninstall'
!MacroEnd ;UNINSTALL_MIIS_SERVICE

!Macro UNINSTALL_MIIS_MONITOR_SERVICE
  ExecWait '"$INSTDIR\InstallUtil.exe" -u "$INSTDIR\MIISMonitorService.exe"'
!MacroEnd ;UNINSTALL_MIIS_SERVICE

!Macro UNREG_HINALICLIB
  # remove hinalib com interface
  DeleteRegKey HKCR 'CLSID\{DE62061D-3115-4C89-A8EB-B37B73D9930C}'
  DeleteRegKey HKCR 'Typelib\{B5130167-3691-4885-9439-C1A17B231F10}'
  DeleteRegKey HKCR 'HinaLicLib.LicDecoder'
!MacroEnd ;UNREG_HINALICLIB

!Macro INSTALL_VS_REDISTRIBUTION_PACKAGE
  SetOutPath "$INSTDIR"
  File "..\projects\bin\MSVCRuntime\vcredist_x86.exe"
  ExecWait '"$INSTDIR\vcredist_x86.exe" /Q /T:C:\temp'
  Delete "$INSTDIR\vcredist_x86.exe"
!MacroEnd ;INSTALL_VS_REDISTRIBUTION_PACKAGE

!Macro INSTALL_VS_REDISTRIBUTION_PACKAGE_VS2012
  SetOutPath "$INSTDIR"
  File "..\projects\bin\MSVCRuntime\vcredist_2012_x86.exe"
  ExecWait '"$INSTDIR\vcredist_2012_x86.exe" /Q /T:C:\temp'
  Delete "$INSTDIR\vcredist_2012_x86.exe"
!MacroEnd ;INSTALL_VS_REDISTRIBUTION_PACKAGE_VS2012

!Macro INSTALL_VS_REDISTRIBUTION_PACKAGE_VS2012_x64
  SetOutPath "$INSTDIR"
  File "..\projects\bin\MSVCRuntime\vcredist_2012_x64.exe"
  ExecWait '"$INSTDIR\vcredist_2012_x64.exe" /Q /T:C:\temp'
  Delete "$INSTDIR\vcredist_2012_x64.exe"
!MacroEnd ;INSTALL_VS_REDISTRIBUTION_PACKAGE_VS2012_x64

!EndIf  ; MIIS_COMMON_INCLUDE
