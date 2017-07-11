extern BOOL g_tflashCardExist;
/*
* log trace 
* save log to Tcard
*
*/
void SaveLogToTcard(char* buf)
{
	FS_HANDLE fs;
	INT32 filesize,num;


	UINT8 dir[100] = {0};
	UINT8 full_dir[100] = {0};
	char temp_dir[50] = {0};
	U8 ret_drv;
	
	if(g_tflashCardExist)//T card
	 ret_drv = MMI_FS_GetDrive(FS_DRIVE_V_REMOVABLE , 1, FS_NO_ALT_DRIVE);
	else//phone 
     ret_drv = MMI_FS_GetDrive( FS_DRIVE_V_NORMAL, 2, FS_DRIVE_I_SYSTEM | FS_DRIVE_V_NORMAL);
	
	sprintf(temp_dir, "%c:",ret_drv);
	strcat(temp_dir,"\\LensunTest");
	
    AnsiiToUnicodeString(dir, temp_dir);//"E:\\LensunTest");
	fs = MMI_FS_CreateDir(dir);
	if(fs == ERR_SUCCESS || fs == FS_FILE_EXISTS)
	{
		strcat(temp_dir, "\\log.txt");
		AnsiiToUnicodeString(full_dir, temp_dir);
		
		fs = MMI_FS_Open(full_dir, FS_CREATE | FS_READ_WRITE);

		
		MMI_FS_GetFileSize(fs, &filesize);
		MMI_FS_Seek(fs, filesize, FS_FILE_BEGIN);

		MMI_FS_Write(fs, buf, strlen(buf), &num);
	}
	else
	{
		// failed
	}
	FS_Close(fs);
}
