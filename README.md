# FileSwapper

Windows 7/8/8.1 (x64) shell extension for swapping the file names of two files.

![alt FileSwapper](https://raw.github.com/lukasniemeier/fileswapper/master/promo.jpg)

## Install

0. Install the [Visual C++ Redistributable Packages for Visual Studio 2013](http://www.microsoft.com/en-us/download/details.aspx?id=40784)
1. Copy FileSwapper.exe and FileSwapperState.dll in some folder you remember.
2. Open your command line
3. Execute "FileSwapper.exe /RegServerPerUser"
4. Execute "regsvr32 /n /i:user FileSwapperState.dll"
5. Select **2** items in your explorer and right click

## Uninstall

1. Open your command line
2. Execute "regsvr32 /u /n /i:user FileSwapperState.dll"
3. Execute "FileSwapper.exe /UnregServerPerUser"
4. Remove both files (because FileSwapperState.dll is loaded by explorer.exe you need to restart explorer.exe before you are able to remove the file)

## Building

Build this shell extension with Visual Studio 2013 and Windows SDK 8.1, there are no third-party libraries used.