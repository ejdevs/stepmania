////////////////////////////////////////////////////////////////////////////////
// $Workfile: ZipPlatform.h $
// $Archive: /ZipArchive/ZipPlatform.h $
// $Date$ $Author$
////////////////////////////////////////////////////////////////////////////////
// This source file is part of the ZipArchive library source distribution and
// is Copyright 2000-2002 by Tadeusz Dracz (http://www.artpol-software.com/)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// For the licensing details see the file License.txt
////////////////////////////////////////////////////////////////////////////////

/**
* \file ZipPlatform.h
* ZipPlatform namespace declaration.
*
*/
#if !defined(AFX_ZipPlatform_H__E2FE6343_9D03_4F3C_A1F7_706C9F0ED978__INCLUDED_)
#define AFX_ZipPlatform_H__E2FE6343_9D03_4F3C_A1F7_706C9F0ED978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CZipFileHeader;
class CZipAutoBuffer;
#include "ZipString.h"
#include "ZipPathComponent.h"
#include <sys/types.h>

/**
	Interface to the system API.
	All functions have a system - specific implementation .
*/
namespace ZipPlatform
{

	/**
		return the default system case-sensitivity
	*/
	bool GetSystemCaseSensitivity();

	/**
		\return A current system name tag. 
		May be one of ZipCompatibility::ZipPlatforms values.
		\see CZipArchive::GetSystemCompatibility
	*/
	int GetSystemID();

/**
	\return	the default file attributes for the current system
*/
	DWORD GetDefaultAttributes(); 

/**
	\return	the default directory attributes for the current system
*/
	DWORD GetDefaultDirAttributes();

/**
	Get the free space on the device pointed by \e lpszPath
*/
	DWORD GetDeviceFreeSpace(LPCTSTR lpszPath);

/**
	Return the temporary file name ensuring there is enough size in the destination directory,.
	Checking for the size is disabled by default.
*/
	CZipString GetTmpFileName(LPCTSTR lpszPath = NULL, DWORD iSizeNeeded = DWORD(-1));
/**
	\name Various operations on files and directories.
	All the functions which are returning a \c bool value,
	return \c true when the operation was successful.
*/
	//@{
	bool GetCurrentDirectory(CZipString& sz);	///< Get the current directory and store it in \e sz
	bool ChangeDirectory(LPCTSTR lpDirectory);
	bool SetFileAttr(LPCTSTR lpFileName, DWORD uAttr);
	bool GetFileAttr(LPCTSTR lpFileName, DWORD& uAttr);
	bool GetFileModTime(LPCTSTR lpFileName, time_t & ttime); ///< get the file modification time
	bool GetFileSize(LPCTSTR lpszFileName, DWORD& dSize);
	bool SetFileModTime(LPCTSTR lpFileName, time_t ttime);	 ///< set the file modification time
	bool CreateDirectory(LPCTSTR lpDirectory);
	bool SetVolLabel(LPCTSTR lpszPath, LPCTSTR lpszLabel); ///< \c lpszPath may point to a file on the device
	bool ForceDirectory(LPCTSTR lpDirectory);	///< create nested directories at once
	bool RemoveFile(LPCTSTR lpszFileName, bool bThrow = true);
	bool RenameFile( LPCTSTR lpszOldName, LPCTSTR lpszNewName, bool bThrow = true);

#ifndef _MFC_VER
	bool TruncateFile(int iDes, DWORD iSize);
	int OpenFile(LPCTSTR lpszFileName, UINT iMode, int iShareMode);
	bool FlushFile(int iDes);	///< flush the file to the disk.
	int GetFileSystemHandle(int iDes); ///< return the underlying system handle 
#endif
	//@}

/**
	\param	lpszDir
		
	\return	\c true, if \e lpszDir directory exists; otherwise \c false;
*/
	bool DirectoryExists(LPCTSTR lpszDir);
/**
	\param	lpszFilePath
		may point to a file path or a directory on the device
	\return	\c true if the drive is removable. 
	Implemented only on Windows system, in all others always returns \c true.
*/
	bool IsDriveRemovable(LPCTSTR lpszFilePath);
/**
	\param	uAttr
		attributes value to test		
	\return	\c true if the attributes are the directory attributes
*/
	bool IsDirectory(DWORD uAttr);

/**
	Perform the translation between ANSI and OEM character sets.
	\remark
	- The conversion is performed only for the zip archives created under Windows platform.
	- Windows archiving programs convert a filename to OEM before adding it to the archive.
	- OEM conversion only influences the ANSI values above 126, so it
	affects only strings containing international characters.

	\param	buffer
		buffer to be translated		
	\param	bAnsiToOem
		if \c true, convert ANSI to OEM
		if \c false, OEM to ANSI
*/
	void AnsiOem(CZipAutoBuffer& buffer, bool bAnsiToOem);
/**
	Check if the given file or directory exists.
	\param	lpszName
		
	\return	
	- -1 if the given file is a directory
	- 1 a file
	- 0 if there is no such a file
*/
	int FileExists(LPCTSTR lpszName);


#ifdef _UNICODE	
/**
	Convert wide character string to single character string.
	\param	lpWide
		Wide string to convert
	\param	szSingle
		buffer to receive converted string (without the terminating NULL character)
	\return	
		the \e szSingle buffer length, or \c -1 when not succeeded
	\note Only in UNICODE version.
*/
	int WideToSingle(LPCTSTR lpWide, CZipAutoBuffer &szSingle);
/**
	Convert single character string to wide character string.
	\param	szSingle
		single string to convert (no terminating NULL character at the end)
	\param	szWide
		receives the wide string after the conversion	
	\return	\e the length of the string after the conversion (without the NULL character),
	or \c -1 when not succeeded
	\note Only in UNICODE version.
*/
	int SingleToWide(const CZipAutoBuffer &szSingle, CZipString& szWide);
#endif
};


#endif // !defined(AFX_ZipPlatform_H__E2FE6343_9D03_4F3C_A1F7_706C9F0ED978__INCLUDED_)
