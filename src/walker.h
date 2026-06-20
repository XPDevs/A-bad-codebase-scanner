/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef WALKER_H
#define WALKER_H
#include "code_scan.h"
typedef int(*FileFilter)(const char*path);
typedef struct{char**dirs;int ndirs;int dir_cap;char**files;int nfiles;int file_cap;FileFilter filter;int recursive;int follow_symlinks;int max_depth;int depth;int total_size;int total_files;int skipped_files;int binary_files;char**ignore_dirs;int nignore;int ignore_cap;char**ignore_patterns;int npatterns;}Walker;
void walker_init(Walker*w);void walker_add_dir(Walker*w,const char*path);void walker_add_ignore(Walker*w,const char*dir);void walker_set_filter(Walker*w,FileFilter f);void walker_walk(Walker*w);int walker_default_filter(const char*path);void walker_free(Walker*w);
#endif
