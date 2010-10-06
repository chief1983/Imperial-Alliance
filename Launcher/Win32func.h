#ifndef __WIN32_H__
#define __WIN32_H__

bool browse_for_save_file(HWND hwnd, char *filename, char *ext, char *title);
bool browse_for_open_file(HWND hwnd, char *filename, char *ext, char *title);
FILE *browse_for_and_open_save_file(HWND hwnd, char *filename, char *ext, char *title);
FILE *browse_for_and_open_open_file(HWND hwnd, char *filename, char *ext, char *title);
bool browse_for_dir(char *result);
bool run_file(char *app_name, char *app_path, char *comm_line);

HKEY reg_open_dir(const char *reg_path);
bool reg_create_dir(char *path);

bool reg_set_sz(const char *reg_path, const char *keyname, const char *string);
bool reg_set_dword(const char *reg_path, const char *keyname, DWORD value);

bool reg_get_sz(const char *reg_path, const char *keyname, char *string, unsigned long length);
bool reg_get_dword(const char *reg_path, const char *keyname, DWORD *value);

bool reg_del_value(const char *reg_path, const char *valname);



enum
{
	OS_FAILED,
	OS_WIN_NT3,
	OS_WIN_NT4,
	OS_WIN_95,
	OS_WIN_98,
	OS_WIN_ME,
	OS_WIN_2000,
	OS_WIN_XP,
	OS_WIN_SERVER_2003,
	OS_WIN_UNKNOWN,
	OS_MAX
};

void os_get_type_text(char *buffer);
int os_get_type(char *service_pack = NULL);

int memory_get_ammount();

#endif


